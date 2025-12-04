#pragma once
#include<cstdint>

namespace Engine::ECS {
	struct Entity {
		uint32_t id = 0;
		uint32_t generation = 0;

		bool operator==(const Entity& other) const {
			return id == other.id && generation == other.generation;
		}

		static Entity Invalid() {
			return Entity{ 0xFFFFFFFF, 0 };
		}

		bool IsValid() const {
			return id != 0xFFFFFFFF;
		}
	};
}