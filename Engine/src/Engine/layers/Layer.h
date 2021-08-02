#pragma once
#include <Engine/Time/TimeStep.h>
#include "Engine/Event/Event.h"

namespace ArcanaTools {
	class Layer {
	
	public:
		Layer(const char* name) : m_name(name) {}
		
		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;

		////////////////////////////////////////////
		// <ImGui> /////////////////////////////////
		////////////////////////////////////////////
		virtual void OnImGuiRender() {};

		////////////////////////////////////////////
		////<Runtime>///////////////////////////////
		////////////////////////////////////////////

		// Update
		virtual void OnUpdate(TimeStep ts) {};
		// Render
		virtual void OnRender() {}
		// Events
		virtual void OnEvent(Event& _event) {};

	private:
		const char* m_name;
	};
}