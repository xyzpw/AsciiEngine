#include "AsciiEngine/engine.hpp"
#include "AsciiEngine/ascii_object.hpp"
#include "AsciiEngine/components/ascii_renderer.hpp"
#include "AsciiEngine/math/vector2.hpp"
#include "AsciiEngine/math/ray.hpp"
#include "AsciiEngine/physics/raycast_hit.hpp"
#include "AsciiEngine/utils/display.hpp"
#include <functional>
#include <algorithm>

using namespace AsciiEngine::Math;
using namespace AsciiEngine::Physics;

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
}
