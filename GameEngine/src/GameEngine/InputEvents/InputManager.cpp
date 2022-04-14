#include "InputManager.h"

	//Initializing to NULL
	GameEngine::InputManager* GameEngine::InputManager::m_sInstance = NULL;

	GameEngine::InputManager* GameEngine::InputManager::CreateInstance() {

		//Create a new instance if no instance was created before
		if (m_sInstance == NULL)
			m_sInstance = new GameEngine::InputManager();

		return m_sInstance;
	}

	void GameEngine::InputManager::Terminate() {

		delete m_sInstance;
		m_sInstance = NULL;
	}

	GameEngine::InputManager::InputManager() {

		m_KeyBoardStates = SDL_GetKeyboardState(&m_KeyLength);
		//Setting m_PrevKeyBoardState to be the same length as m_KeyBoardStates
		m_PrevKeyBoardState = new Uint8[m_KeyLength];
		//Copying the contents of m_KeyBoardStates into m_PrevKeyboardState so that it contains data on the first frame
		memcpy(m_PrevKeyBoardState, m_KeyBoardStates, m_KeyLength);
	}

	GameEngine::InputManager::~InputManager() {

		//Clearing the previous keyboard state array
		delete[] m_PrevKeyBoardState;
		m_PrevKeyBoardState = NULL;
	}

	bool GameEngine::InputManager::Keydown(SDL_Scancode scanCode) {

		return (m_KeyBoardStates[scanCode] != 0);
	}

	bool GameEngine::InputManager::KeyPressed(SDL_Scancode scanCode) {

		//returning true of the key was not pressed in the previous keyboard state but is pressed in the current one
		return (m_PrevKeyBoardState[scanCode]) == 0 && (m_KeyBoardStates[scanCode] != 0);
	}

	bool GameEngine::InputManager::KeyReleased(SDL_Scancode scanCode) {

		//returning true of the key was pressed in the previous keyboard state but is not pressed in the current one
		return (m_PrevKeyBoardState[scanCode] != 0) && (m_KeyBoardStates[scanCode] == 0);
	}

	GameEngine::Vector2 GameEngine::InputManager::MousePos() {

		//Converting the mouse position into a Vector2 for ease of use since all entities use Vector2
		return Vector2((float)m_MouseXPos, (float)m_MouseYPos);
	}

	bool GameEngine::InputManager::MouseButtonDown(MOUSE_BUTTON button) {

		//mask to be using for bit wise operations
		Uint32 mask = 0;

		switch (button) {

		case left:

			mask = SDL_BUTTON_LMASK;
			break;

		case right:

			mask = SDL_BUTTON_RMASK;
			break;

		case middle:

			mask = SDL_BUTTON_MMASK;
			break;

		case back:

			mask = SDL_BUTTON_X1MASK;
			break;

		case forward:

			mask = SDL_BUTTON_X2MASK;
			break;
		}

		//return true if the mask exists in the current mouse state
		return ((m_MouseState & mask) != 0);
	}

	bool GameEngine::InputManager::MouseButtonPressed(MOUSE_BUTTON button) {

		//mask to be using for bit wise operations
		Uint32 mask = 0;

		switch (button) {

		case left:

			mask = SDL_BUTTON_LMASK;
			break;

		case right:

			mask = SDL_BUTTON_RMASK;
			break;

		case middle:

			mask = SDL_BUTTON_MMASK;
			break;

		case back:

			mask = SDL_BUTTON_X1MASK;
			break;

		case forward:

			mask = SDL_BUTTON_X2MASK;
			break;
		}

		//return true if the mask does not exist in the previous mouse state, but exists in the current one
		return ((m_PrevMouseState & mask) == 0) && ((m_MouseState & mask) != 0);
	}

	bool GameEngine::InputManager::MouseButtonReleased(MOUSE_BUTTON button) {

		Uint32 mask = 0;

		switch (button) {

		case left:

			mask = SDL_BUTTON_LMASK;
			break;

		case right:

			mask = SDL_BUTTON_RMASK;
			break;

		case middle:

			mask = SDL_BUTTON_MMASK;
			break;

		case back:

			mask = SDL_BUTTON_X1MASK;
			break;

		case forward:

			mask = SDL_BUTTON_X2MASK;
			break;
		}

		//return true if the mask exists in the previous mouse state, but does not exist in the current one
		return ((m_PrevMouseState & mask) != 0) && ((m_MouseState & mask) == 0);
	}

	void GameEngine::InputManager::Update() {

		//Updating the mouse state to get the key states of the current frame
		m_MouseState = SDL_GetMouseState(&m_MouseXPos, &m_MouseYPos);
	}

	void GameEngine::InputManager::UpdatePrevInput() {

		//Copying the keyboard state into the previous keyboard state array at the end of the frame
		memcpy(m_PrevKeyBoardState, m_KeyBoardStates, m_KeyLength);
		//Setting the previous mouse state as the current mouse state at the end of the frame
		m_PrevMouseState = m_MouseState;
	}
