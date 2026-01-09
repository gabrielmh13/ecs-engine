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
			std::size_t smallestPoolIndex = FindSmallestPoolIndex();
			IterateSmallestPool(func, smallestPoolIndex, std::index_sequence_for<Components...>{});
		}

	private:
		Registry& m_Registry;
		std::tuple<ComponentPool<Components>&...> m_Pools;

		std::size_t FindSmallestPoolIndex() const {
			return FindSmallestPoolIndexHelper(std::index_sequence_for<Components...>{});
		}

		template<std::size_t... I>
		std::size_t FindSmallestPoolIndexHelper(std::index_sequence<I...>) const {
			std::size_t sizes[] = { std::get<I>(m_Pools).data.size()... };
			std::size_t minIndex = 0;
			std::size_t minSize = sizes[0];

			for (std::size_t i = 1; i < sizeof...(Components); ++i) {
				if(sizes[i] < minSize) {
					minSize = sizes[i];
					minIndex = i;
				}
			}

			return minIndex;
		}

		template<typename Func, std::size_t... I>
		void IterateSmallestPool(Func& func, std::size_t poolIndex, std::index_sequence<I...>) {
			(IterateIfMatch<I>(func, poolIndex), ...);
		}

		template<std::size_t PoolIndex, typename Func>
		void IterateIfMatch(Func& func, std::size_t index) {
			if (index == PoolIndex) {
				IteratePool<PoolIndex>(func, std::index_sequence_for<Components...>{});
			}
		}

		template<std::size_t PoolIndex, typename Func, std::size_t... I>
		void IteratePool(Func& func, std::index_sequence<I...>) {
			auto& basePool = std::get<PoolIndex>(m_Pools);

			for (auto& [entityID, _] : basePool.data) {
				if(!HasAllComponents<PoolIndex>(entityID, std::index_sequence<I...>{}))
					continue;

				Entity e{
					entityID,
					m_Registry.GetGeneration(entityID)
				};

				Invoke(func, entityID, std::index_sequence<I...>{}, e);
			}
		}


		template<std::size_t SkipIndex, std::size_t... I>
		bool HasAllComponents(uint32_t entityID, std::index_sequence<I...>) {
			return (... && (I == SkipIndex || std::get<I>(m_Pools).data.contains(entityID)));
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
