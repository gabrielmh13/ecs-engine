#include<iostream>
#include "core/Application.hpp"
#include "ecs/components/Position.hpp"

class MyApp : public Engine::Application {
	void OnInit() override {
		std::cout << "Engine Initialized!" << std::endl;

		auto entity = m_Registry.CreateEntity();

		auto& pos = m_Registry.AddComponent<Engine::ECS::Position>(entity);
		pos.x = 0.0f;
		pos.y = 0.0f;

		std::cout << "Entity created with Position (" << pos.x << ", " << pos.y << ")" << std::endl;
	}

	void OnUpdate(float dt) override {
		std::cout << "Frame dt = " << dt << " seconds" << std::endl;

		static float totalTime = 0.0f;

		totalTime += dt;

		if (totalTime >= 1.0f) {
			Quit();
		}
	}

	void OnShutdown() override {
		std::cout << "Engine finished" << std::endl;
	}
};

int main() {
	MyApp app;

	app.Run();

	return 0;
}