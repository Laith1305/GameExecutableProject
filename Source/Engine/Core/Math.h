#pragma once
#include <algorithm>
#include <SDL3/SDL.h>
#include <cmath>
namespace viper {
	namespace math {

		const float pi = 3.14;
		const float twoPi = 2 * pi;
		const float halfPit = pi / 2;


		constexpr float radToDeg(float rad) { return rad * (180/pi); }
		constexpr float degToRad(float deg) { return deg * (pi/180); }


		using std::min;
		using std::max;
		using std::sqrt;
		using std::sqrtf;
		using std::sin;
		using std::cos;
		//using std::clamp;

	}
}