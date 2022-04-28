#pragma once
#include <vector>
#include <cstdint>

namespace GameEngine {
	class IdGenerationPool {
	private:
		uint32_t* idPool;
		uint32_t* generations;
		static IdGenerationPool* m_Instance;

	public:
		IdGenerationPool();
		~IdGenerationPool(); 
		static IdGenerationPool* CreateInstance();
		void Terminate();
		bool Allocate();
		void Deallocate();
		bool IsValid();
	};
}