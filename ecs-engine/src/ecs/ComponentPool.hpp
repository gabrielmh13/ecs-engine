#pragma once

#include <unordered_map>
#include <cstdint>

namespace Engine::ECS {
	class IComponentPool {
	public:
		virtual ~IComponentPool() = default;
		virtual void Remove(uint32_t entityID) = 0;
	};

	template<typename T>
	class ComponentPool : public IComponentPool {
	public:
		std::unordered_map<uint32_t, T> data;

		T& Add(uint32_t entityID) {
			data[entityID] = T();
			return data[entityID];
		}

		T& Add(uint32_t entityID, const T& component) {
			data[entityID] = component;
			return data[entityID];
		}

		T* Get(uint32_t entityID) {
			auto it = data.find(entityID);
			return it != data.end() ? &it->second : nullptr;
		}

		void Remove(uint32_t entityID) override {
			data.erase(entityID);
		}
	};
}