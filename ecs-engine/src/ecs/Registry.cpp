#include "Registry.hpp"

namespace Engine::ECS {
	Entity Registry::CreateEntity() {
		uint32_t id;

		if (!m_FreeList.empty()) {
			id = m_FreeList.back();
			m_FreeList.pop_back();
		}
		else {
			id = static_cast<uint32_t>(m_Generations.size());
			m_Generations.push_back(0);
		}

		return Entity{ id, m_Generations[id] };
	}

	void Registry::DestroyEntity(Entity entity) {
		if (!IsEntityValid(entity))
			return;

		uint32_t id = entity.id;

		m_Generations[id]++;

		for(auto& [type, pool] : m_Pools) {
			pool->Remove(id);
		}

		m_FreeList.push_back(id);
	}

	bool Registry::IsEntityValid(Entity entity) const {
		uint32_t id = entity.id;
		return id < m_Generations.size() && m_Generations[id] == entity.generation;
	}
}