#pragma once

#include "ecs/Registry.hpp"

namespace Engine {
	class Application {
	public:
		Application() = default;
		virtual ~Application() = default;

		void Run();
		void Quit();

	protected:
		virtual void OnInit() {}
		virtual void OnUpdate(float dt) {}
		virtual void OnShutdown() {}

		Engine::ECS::Registry m_Registry;

	private:
		bool m_Running = true;
	};
}