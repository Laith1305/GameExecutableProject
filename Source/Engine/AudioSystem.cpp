#include "AudioSystem.h"
#include <fmod.hpp>

namespace viper {
	bool AudioSystem::Initialize() {

		//FMOD_RESULT::System_Create(&audio);

		void* extradriverdata = nullptr;
		//audio->init(32, FMOD_INIT_NORMAL, extradriverdata);
		return true;
	}

	void Shutdown() {


	};

	void Update() {

	}


}