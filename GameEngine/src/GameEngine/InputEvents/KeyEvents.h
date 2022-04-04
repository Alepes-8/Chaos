#pragma once

#include "EventMain.h"
#include <sstream>

namespace GameEngine {


	/* -KeyEvent base, used to create the keyEvent-
	* 
	* This is the base key event that all other key events will 
	* be inherenting from.
	*/
	class GE_API KeyEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput) // Places it into the two catagorys that it is relevent to

		inline int GetKeyCode() const { return m_KeyCode; }

	protected:
		int m_KeyCode;

		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}
	};






	/* -KeyEvent when pressing the key down-
	* 
	* m_RepeatCount:	How much have we printed from holding a key down
	* 
	*/
	class GE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};






	/* -KeyEvent when Released the key-
	*
	*/
	class GE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}