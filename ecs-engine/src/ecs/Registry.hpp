#pragma once
#include<unordered_map>
#include<typeindex>
#include<memory>

#include "Entity.hpp"
#include "ComponentPool.hpp"

namespace Engine::ECS {
	class Registry {
	public:
		Entity CreateEntity();
		void DestroyEntity(Entity entity);
		bool IsEntityValid(Entity entity) const;

		template<typename T>
		T& AddComponent(Entity entity) {
			auto& pool = GetPool<T>();
			return pool.Add(entity.id);
		}

		template<typename T>
		T& AddComponent(Entity entity, const T& component) {
			auto& pool = GetPool<T>();
			return pool.Add(entity.id, component);
		}

		template<typename T>
		T* GetComponent(Entity entity) {
			auto &pool = GetPool<T>();
			return pool.Get(entity.id);
		}

		template<typename T>
		bool HasComponent(Entity entity) {
			auto &pool = GetPool<T>();
			return pool.Get(entity.id) != nullptr;
		}

		template<typename T>
		void RemoveComponent(Entity entity) {
			auto &pool = GetPool<T>();
			pool.Remove(entity.id);
		}
	private:
		std::vector<uint32_t> m_Generations;
		std::vector<uint32_t> m_FreeList;

		std::unordered_map<std::type_index, std::unique_ptr<IComponentPool>> m_Pools;

		template<typename T>
		ComponentPool<T>& GetPool() {
			std::type_index type = typeid(T);

			if (!m_Pools.contains(type)) {
				m_Pools[type] = std::make_unique<ComponentPool<T>>();
			}

			return *static_cast<ComponentPool<T>*>(m_Pools[type].get());
		}
	};
}