#pragma once

namespace viper {
	const float pi = 3.14;
	const float twoPi = 2 * pi;
	const float halfPit = pi / 2;

	constexpr float degToRad(float deg) { return deg * (pi / 180); }

	constexpr int wrap(int value, int min, int max) {
		int range = max - min;
		int result = (value - min) % range;
		if (result < 0) result += range;

		return min + result;

	}

	/*inline float wrap(float value, float min, float max) {

		float range = max - min;
		float result = (value - min) % range;
		if (result < 0) result += range;

		return min + result;

	}*/

}