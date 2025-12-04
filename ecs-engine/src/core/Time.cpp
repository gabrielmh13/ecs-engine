#include "Time.hpp"

namespace Engine {
	void Time::Update() {
		auto now = std::chrono::high_resolution_clock::now();

		if (!s_Initialized) {
			s_StartTime = now;
			s_LastFrame = now;
			s_Initialized = true;
			return;
		}

		s_DeltaTime = std::chrono::duration<float>(now - s_LastFrame).count();
		s_LastFrame = now;
	}

	float Time::DeltaTime() {
		return s_DeltaTime;
	}

	float Time::Elapsed() {
		auto now = std::chrono::high_resolution_clock::now();
		return std::chrono::duration<float>(now - s_StartTime).count();
	}
}