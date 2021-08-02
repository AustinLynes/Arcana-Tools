#pragma once
#include "../Layer.h"
namespace ArcanaTools {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		
		virtual void OnEvent(Event& e);
		
		void SetStyle();


		void Begin();
		void End();
	
	private: 
		bool m_BlockEvents = false;
		void BackupContext();
	};
}

