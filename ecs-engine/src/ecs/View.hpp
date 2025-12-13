#pragma once
#include <tuple>
#include <utility>
#include <cstdint>

#include "ComponentPool.hpp"
#include "Entity.hpp"

namespace Engine::ECS {

	class Registry;

	template<typename... Components>
	class View {
	public:
		View(Registry& registry, ComponentPool<Components>&... pools)
			: m_Registry(registry), m_Pools(pools...)
		{
		}

		template<typename Func>
		void Each(Func func) {
			auto& basePool = std::get<0>(m_Pools);

			for (auto& [entityID, _] : basePool.data) {

				if (!HasAllComponents(entityID))
					continue;

				Entity e{
					entityID,
					m_Registry.GetGeneration(entityID)
				};

				Invoke(func, entityID, std::index_sequence_for<Components...>{}, e);
			}
		}

	private:
		Registry& m_Registry;
		std::tuple<ComponentPool<Components>&...> m_Pools;

		template<std::size_t... I>
		bool HasAllComponents(uint32_t entityID, std::index_sequence<I...>) {
			return (... && std::get<I>(m_Pools).data.contains(entityID));
		}

		bool HasAllComponents(uint32_t entityID) {
			return HasAllComponents(entityID, std::index_sequence_for<Components...>{});
		}

		template<typename Func, std::size_t... I>
		void Invoke(Func& func, uint32_t entityID, std::index_sequence<I...>, Entity& e) {
			func(
				e,
				std::get<I>(m_Pools).data.at(entityID)...
			);
		}
	};

}
