#pragma once
#include "GameEngine/InputEvents/InputManager.h"
#include <bx/math.h>
#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <iostream>

namespace GameEngine {
	enum Direction { RIGHT, LEFT, FORWARD, BACKWARD, UP, DOWN };


	class Camera {
	private:
		bx::Vec3 _at = { 0.0f, 0.0f, 0.0f };
		bx::Vec3 _eye = { 0.0f, 0.0f, 10.0f };
		bx::Vec3 _up = { 0.0f, 1.0f, 0.0f };
		
		float camera_speed = 0.5f;
		static Camera* m_Instance;

		void At(float x, float y, float z);
		void Eye(float x, float y, float z);
		void Up(float x, float y, float z);
		void Reset();
		void ListenEvent(GameEngine::InputManager* im);

		void Translate(float x, float y, float z);
		void Translate_Direction(GameEngine::Direction direction, float speed);
	public:
		static Camera* CreateInstance();
		static void Terminate();

		
		
		
		void Update(GameEngine::InputManager* im, int view_port_id, uint16_t screen_width, uint16_t screen_height);
		float _view[16];
		float _proj[16];
	};

}