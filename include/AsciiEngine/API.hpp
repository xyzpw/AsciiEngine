// IWYU pragma: always_keep
#pragma once

/*
 * This contains everything. It is only an API!
 */

// IWYU pragma: begin_keep
#include "engine.hpp"
#include "ascii_object.hpp"
#include "scene.hpp"
#include "components/ascii_renderer.hpp"
#include "components/behaviour.hpp"
#include "components/conditional_action.hpp"
#include "components/controller.hpp"
#include "components/ascii_collider.hpp"
#include "components/ascii_animation.hpp"
#include "core/component.hpp"
#include "core/key_action.hpp"
#include "core/timer.hpp"
#include "core/signal.hpp"
#include "utils/colors.hpp"
#include "utils/display.hpp"
#include "math/vector2.hpp"
#include "math/ray.hpp"
#include "physics/raycast_hit.hpp"
// IWYU pragma: end_keep

#include <string>

namespace AsciiEngine
{
	// version of API
	const std::string version = "0.2.0";
}
