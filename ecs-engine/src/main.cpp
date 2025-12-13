#include<iostream>
#include "core/Application.hpp"

struct Position {
	float x = 0.0f;
	float y = 0.0f;
};

struct Velocity {
	float vx = 0.0f;
	float vy = 0.0f;
};

struct Acceleration {
	float ax = 0.0f;
	float ay = 0.0f;
};

class MyApp : public Engine::Application {
	void OnInit() override {
		std::cout << "Engine Initialized!" << std::endl;

		auto entity = m_Registry.CreateEntity();
		auto entity2 = m_Registry.CreateEntity();
		auto entity3 = m_Registry.CreateEntity();

		auto& pos = m_Registry.AddComponent<Position>(entity, {10.5f, -3.2f});
		m_Registry.AddComponent<Velocity>(entity, { 1.0f, 0.0f });
		m_Registry.AddComponent<Acceleration>(entity, { 0.0f, -9.8f });

		m_Registry.AddComponent<Position>(entity2, { 0.0f, 1.0f });

		m_Registry.AddComponent<Position>(entity3, { 0.0f, 1.0f });
		m_Registry.AddComponent<Velocity>(entity3, { -5.0f, 4.0f });
		m_Registry.AddComponent<Acceleration>(entity3, { 0.0f, 9.8f });

		m_Registry.View<Position, Velocity, Acceleration>().Each(
			[](Engine::ECS::Entity e, Position& pos, Velocity& vel, Acceleration& acc) {
				std::cout << " Entity " << e.id << std::endl;
			}
		);

		std::cout << "[Init] Entity created with Position (" << pos.x << ", " << pos.y << ")" << std::endl;

		if (auto* p = m_Registry.GetComponent<Position>(entity)) {
			std::cout << "[Init] Retrieved Position: (" << p->x << ", " << p->y << ")\n";
		}

		bool hasPos = m_Registry.HasComponent<Position>(entity);
		std::cout << "[Init] Has Position? " << (hasPos ? "YES" : "NO") << "\n";

		m_Registry.RemoveComponent<Position>(entity);
		std::cout << "[Init] Removed Position\n";

		bool hasAfterRemove = m_Registry.HasComponent<Position>(entity);
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