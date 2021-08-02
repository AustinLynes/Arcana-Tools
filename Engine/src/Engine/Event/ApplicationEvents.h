#pragma once
#include "Event.h"

namespace ArcanaTools {
	class WindowResizeEvent : public Event {
	public: 
		WindowResizeEvent(unsigned int width, unsigned int height): m_width(width), m_height(height) {}
		
		unsigned int GetWidth() const { return m_width; };
		unsigned int GetHeight() const { return m_width; }

		EVENT_TYPE(WindowResize)
		EVENT_CLASSIFICATION(Events::Application)

	private:
		unsigned int m_width;
		unsigned int m_height;

	};
	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}

		EVENT_TYPE(WindowClose)
		EVENT_CLASSIFICATION(Events::Application)

	
	};
}