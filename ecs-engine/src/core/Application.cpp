#include "Application.hpp"
#include "Time.hpp"

namespace Engine {
	void Application::Run() {
		OnInit();

		m_Running = true;

		while (m_Running) {
			Time::Update();

			float dt = Time::DeltaTime();
			OnUpdate(dt);
		}

		OnShutdown();
	}

	void Application::Quit() {
		m_Running = false;
	}
}