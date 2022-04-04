#pragma once

#include "GameEngine/Core.h"

#include <string>
#include <functional>

namespace GameEngine {

	
	/*-- Describes the different event types ang give int ID--
	* 
	* Is used in the respecive header files:
	* WindowEvents.h	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	* ----N/A----		AppTick, AppUpdate, AppRender,
	* KeyEvent.h		KeyPressed, KeyReleased,
	* MouseEvent.h		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	*
	*/
	enum class EventType 
	{
		None = 0,
		WindowClose, WindowResize, WindowMoved, /*WindowFocus, WindowLostFocus,*/
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
	


	/*-- Sorts the events into different event catagorys
	* 
	* This is so that you will only need to look if the event is a
	* eventCatagoryMouse instead of  MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled.
	* 
	*/
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};


	/*--The main event class handled by the different event headers--
	* 
	* ToString():			Return the name of the event
	* IsInCategory:			Checks if is within the catagory that is sent in
	* 
	* m_Handled:  is to keep track if an event has occured or not
	*/

	class GE_API Event	
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	protected:
		bool m_Handled = false;
	};

	/*-----------------------------------------------------------------------
	*Macros created to make it so that we don't need to write them each time.
	*-----------------------------------------------------------------------*/
	#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
	#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
									virtual EventType GetEventType() const override { return GetStaticType(); }\
									virtual const char* GetName() const override { return #type; }


	/*
	* 
	* This is to check that the event is the catagorised as the correct 
	* event and then when it is correct it will run the corolating application.
	* 
	*/
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	/*-This makes the logging much easier-*/
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}