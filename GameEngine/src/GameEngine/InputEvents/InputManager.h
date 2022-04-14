#pragma once
#include "SDL.h"
#include <string.h>
#include <vector>
#include "GameEngine/MathHelper.h"

namespace GameEngine {
	class InputManager {
	public:
		enum MOUSE_BUTTON { left = 0, right, middle, back, forward };

	private:
		static InputManager* m_sInstance;

		Uint8* m_PrevKeyBoardState;
		const Uint8* m_KeyBoardStates;
		int m_KeyLength;

		Uint32 m_PrevMouseState;
		Uint32 m_MouseState;

		int m_MouseXPos;
		int m_MouseYPos;

	public:
		static InputManager* CreateInstance();
		static void Terminate();

		bool Keydown(SDL_Scancode scanCode);
		bool KeyPressed(SDL_Scancode scanCode);
		bool KeyReleased(SDL_Scancode scanCode);

		bool MouseButtonDown(MOUSE_BUTTON button);
		bool MouseButtonPressed(MOUSE_BUTTON button);
		bool MouseButtonReleased(MOUSE_BUTTON button);

		struct Vector2 MousePos();

		void Update();
		void UpdatePrevInput();
	private:
		InputManager();
		~InputManager();
	};
}

