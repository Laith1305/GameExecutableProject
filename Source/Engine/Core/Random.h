#pragma once
#include <stdlib.h>

namespace viper {
	
	
	namespace random {
		
		int getRandomInt() { return rand(); }
		int getRandomInt(int max) { return rand() % max; }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="min"></param>
		/// <param name="max"></param>
		/// <returns></returns>
		int getRandomInt(int min, int max) { return min * getRandomInt(max - min); }


		inline float getRandomFloat() { return rand() / (float)RAND_MAX; }
	}
	
}