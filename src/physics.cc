#include "AsciiEngine/engine.hpp"
#include "AsciiEngine/ascii_object.hpp"
#include "AsciiEngine/components/ascii_renderer.hpp"
#include "AsciiEngine/components/ascii_collider.hpp"
#include "AsciiEngine/components/ascii_body.hpp"
#include "AsciiEngine/math/vector2.hpp"
#include "AsciiEngine/math/ray.hpp"
#include "AsciiEngine/physics/raycast_hit.hpp"
#include "AsciiEngine/utils/display.hpp"
#include "AsciiEngine/utils/math.hpp"
#include <functional>
#include <algorithm>

using namespace AsciiEngine::Math;
using namespace AsciiEngine::Physics;
using namespace AsciiEngine::Utils;

namespace AsciiEngine
{
	std::vector<RaycastHit> Engine::rayCircle(const Vector2 &origin, float distance)
	{
		if (distance < 0)
			return {};

		std::vector<RaycastHit> hits;

		float distSqr = distance * distance;

		callOnAllActiveObjects([&](AsciiObject *ao) {
			auto rend = ao->getComponent<AsciiRenderer>();

			Vector2 p(rend->col, rend->row);
			float diffSqrMag = (p - origin).sqrMagnitude();

			if (diffSqrMag > distSqr)
				return;

			RaycastHit hit;
			hit.distance = (p - origin).magnitude();
			hit.layer = ao->layer;
			hit.object = ao;

			hits.push_back(hit);
		}, Utils::hasVisibleRenderer);

		/* sort closest first */
		std::sort(hits.begin(), hits.end(),
				[](RaycastHit &a, RaycastHit &b) {
					return a.distance < b.distance;
				});

		return hits;
	}

	bool Engine::raycast(const Ray &ray, float distance, RaycastHit &out)
	{
		if (distance < 0)
			return false;

		const auto &[origin, direction] = ray;
		float distSqr = distance * distance;
		AsciiObject *hit = nullptr;

		for (int i = 1; i < maxColumns*maxRows; ++i) {
			Vector2 p = origin + direction * i;
			Vector2 diff = p - origin;

			if (!isInDisplay(p) || diff.sqrMagnitude() > distSqr)
				break;

			hit = getAsciiObjectAt(p);

			if (hit != nullptr && Utils::hasVisibleRenderer(hit)) {
				out.object = hit;
				out.layer = hit->layer;
				out.distance = diff.magnitude();

				return true;
			}
		}

		return false;
	}

	std::vector<RaycastHit> Engine::raycastAll(const Ray &ray, float distance)
	{
		if (distance < 0)
			return {};

		std::vector<RaycastHit> hits;

		const auto &[origin, direction] = ray;
		float distSqr = distance * distance;

		for (int i = 1; i < maxColumns*maxRows; ++i) {
			Vector2 p = origin + direction * i;
			Vector2 diff = p - origin;

			if (!isInDisplay(p.x, p.y) || diff.sqrMagnitude() > distSqr)
				break;

			callOnAllActiveObjects([&](AsciiObject *ao) {
				auto rend = ao->getComponent<AsciiRenderer>();
				if (!Utils::isPointInSprite(rend, p))
					return;

				RaycastHit h;
				h.object = ao;
				h.layer = ao->layer;
				h.distance = diff.magnitude();

				hits.push_back(h);
			}, Utils::hasVisibleRenderer);
		}

		/* sort closest first */
		std::sort(hits.begin(), hits.end(),
				[](RaycastHit &a, RaycastHit &b) {
					return a.distance < b.distance;
				});

		return hits;
	}

	void Engine::checkSpriteColliders()
	{
		auto hasComp = [&](AsciiObject *ao) {
			auto c = ao->getComponent<AsciiCollider>();
			return c != nullptr && c->isEnabled()
				&& Utils::hasVisibleRenderer(ao);
		};

		callOnAllActiveObjects([&](AsciiObject *ao) {
			auto collider = ao->getComponent<AsciiCollider>();
			auto rendA = ao->getComponent<AsciiRenderer>();

			auto &hits = collider->getContacts();
			hits.clear();

			callOnAllActiveObjects([&](AsciiObject *contact) {
				if (contact == ao)
					return;
				else if (ao->layer != contact->layer)
					return;

				auto rendB = contact->getComponent<AsciiRenderer>();

				if (Utils::spritesOverlap(rendA, rendB)) {
					hits.push_back(contact);
				}
			}, hasComp);
		}, hasComp);

		callOnAllActiveObjects([&](AsciiObject *ao) {
			auto coll = ao->getComponent<AsciiCollider>();
			if (coll->hasContacts())
				coll->onContact();
		}, hasComp);
	}

	void Engine::checkPhysicsBodies()
	{
		auto cond = [&](AsciiObject *a) {
			if (deltaTime <= 0)
				return false;

			return a->hasEnabledComponent<AsciiBody>();
		};

		/* set sprite position */
		auto tryFixSprite = [&](AsciiObject *a) {
			auto *rend = a->getComponent<AsciiRenderer>();
			auto *body = a->getComponent<AsciiBody>();

			if (rend == nullptr)
				return;

			rend->col = body->bounds.left();
			rend->row = body->bounds.top();
		};

		callOnAllActiveObjects([&](AsciiObject *ao) {
			tryFixSprite(ao);
		}, cond);

		callOnAllActiveObjects([&](AsciiObject *ao) {
			auto *body = ao->getComponent<AsciiBody>();
			Bounds &bounds = body->bounds;
			auto &pos = body->getPosition();
			auto &size = body->getSize();
			auto &velocity = body->velocity;

			if (body->isStatic)
				return;

			// change velocity due to gravity
			velocity.y += gravity.y * body->gravityModifier * deltaTime;

			float dx = velocity.x * deltaTime;
			Bounds moved = bounds;
			moved.position.x += dx;

			bool finished = false;
			callOnAllActiveObjects([&](AsciiObject *other) {
				if (ao == other || finished)
					return;

				auto *otherBody = other->getComponent<AsciiBody>();
				auto &otherBounds = otherBody->bounds;

				if (!boundsOverlap(moved, otherBounds))
					return;

				if (dx > 0) {
					float f = otherBounds.left() -
						size.x;
					moved.position.x = f;
				} else if (dx < 0) {
					moved.position.x = otherBounds.right();
				}

				velocity.x = 0;
				finished = true;
			}, cond);
			finished = false;

			pos.x = moved.position.x;
			float dy = velocity.y * deltaTime;
			moved = bounds;
			moved.position.y += dy;

			callOnAllActiveObjects([&](AsciiObject *other) {
				if (ao == other || finished)
					return;

				auto *otherBody = other->getComponent<AsciiBody>();
				auto &otherBounds = otherBody->bounds;

				if (!boundsOverlap(moved, otherBounds))
					return;

				if (dy > 0) {
					moved.position.y = otherBounds.top()
						- size.y;
				} else if (dy < 0) {
					moved.position.y = otherBounds.bottom();
				}

				velocity.y = 0;
				finished = true;
			}, cond);

			pos.y = moved.position.y;
		}, cond);
	}
}
