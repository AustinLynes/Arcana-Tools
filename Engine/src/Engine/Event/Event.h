#pragma once
#include <string>
#define BIT(x) x << 1

namespace ArcanaTools {

	// WINDOW 
	//	L RESIZE
	// 	L KEY_PRESS
	// 	L WINDOW_CLOSED
	// 	
	// APP
	// 	L APP_CLOSED
	// 	L 
	// INPUT

	namespace Events {
		enum class Type {
			None = 0,
			WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
			AppTick, AppUpdate, AppRender,
			KeyPressed, KeyReleased, KeyTyped,
			MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
		};
		enum Classification {
			None,
			Application = BIT(1),
			Input = BIT(2),
			Keyboard = BIT(3),
			Mouse = BIT(4),
			MouseButton = BIT(5),
		};
	}

#define EVENT_TYPE(type)		static Events::Type GetStaticType() { return Events::Type:: type; }\
								virtual Events::Type GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASSIFICATION(category) virtual int GetClassificationFlags() const override { return category; }

	class Event
	{
	public:
		virtual ~Event() = default;

		// Type of Event
		virtual Events::Type GetEventType() const = 0;
		// Name of Event
		virtual const char* GetName() const = 0;
		// Classification of event, events can be multiple classifcations
		virtual int GetClassificationFlags() const = 0;
		// Get The Event Returned to string
		virtual std::string ToString() const { return GetName(); };

		bool HasClassification(Events::Classification classifcation) {
			return GetClassificationFlags() & classifcation;
		}

		bool Handled = false;
	protected:

	};


	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event) : m_event(event){
			
		}

		template<typename TEvent, typename Func>
		bool Dispatch(const Func& func) {
			if (m_event.GetEventType() == TEvent::GetStaticType()) {
				m_event.Handled |= func(static_cast<TEvent&>(m_event));
				return true;
			}
			return false;
		}
	private:
		Event& m_event;
	};


	//inline std::ostream& operator <<(std::ostream& _os, const Event& _event) {
	//	return _os << _event.ToString();
	//}
}

