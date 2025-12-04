#pragma once
#include<chrono>

namespace Engine {
	class Time {
	public:
		static void Update();

		static float DeltaTime();

		static float Elapsed();

		static constexpr float FixedDelta() { return 1.0f / 60.0f; }
	
	private:
		static inline bool s_Initialized = false;

		static inline std::chrono::high_resolution_clock::time_point s_StartTime;
		static inline std::chrono::high_resolution_clock::time_point s_LastFrame;

		static inline float s_DeltaTime = 0.0f;
	};
}