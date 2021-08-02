#pragma once
#include "Engine/Event/Event.h"
#include "Engine/Input/KeyCodes.h"

namespace ArcanaTools {
	class KeyEvent : public Event {
	public:
		KeyCode GetKeyCode() const { return m_keyCode; }

		EVENT_CLASSIFICATION(Events::Classification::Keyboard | Events::Classification::Input)
		KeyEvent(const KeyCode& keycode) :m_keyCode(keycode) {}

	protected:
		KeyCode m_keyCode;
	};


	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(const KeyCode& keycode, uint16_t repeatCount) : KeyEvent(keycode), m_repeatCount(repeatCount) {}
		
		uint16_t GetRepeatCount() const { return m_repeatCount; }
		
		EVENT_TYPE(KeyPressed)
		

	private:
		uint16_t m_repeatCount;

	};
	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(const KeyCode& keycode) : KeyEvent(keycode) {}

		EVENT_TYPE(KeyReleased)

	};
	class KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(const KeyCode& keycode) : KeyEvent(keycode) {}

		EVENT_TYPE(KeyTyped)

	};
}