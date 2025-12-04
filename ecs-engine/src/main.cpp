#include<iostream>
#include "core/Application.hpp"
#include "ecs/components/Position.hpp"

class MyApp : public Engine::Application {
	void OnInit() override {
		std::cout << "Engine Initialized!" << std::endl;

		auto entity = m_Registry.CreateEntity();

		auto& pos = m_Registry.AddComponent<Engine::ECS::Position>(entity);
		pos.x = 10.5f;
		pos.y = -3.2f;

		std::cout << "[Init] Entity created with Position (" << pos.x << ", " << pos.y << ")" << std::endl;

		if (auto* p = m_Registry.GetComponent<Engine::ECS::Position>(entity)) {
			std::cout << "[Init] Retrieved Position: (" << p->x << ", " << p->y << ")\n";
		}

		bool hasPos = m_Registry.HasComponent<Engine::ECS::Position>(entity);
		std::cout << "[Init] Has Position? " << (hasPos ? "YES" : "NO") << "\n";

		m_Registry.RemoveComponent<Engine::ECS::Position>(entity);
		std::cout << "[Init] Removed Position\n";

		bool hasAfterRemove = m_Registry.HasComponent<Engine::ECS::Position>(entity);
		std::cout << "[Init] Has Position after remove? " << (hasAfterRemove ? "YES" : "NO") << "\n";

		m_Registry.DestroyEntity(entity);
		std::cout << "[Init] Entity destroyed\n";

		std::cout << "[Init] Entity valid? " << (m_Registry.IsEntityValid(entity) ? "YES" : "NO") << "\n";

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