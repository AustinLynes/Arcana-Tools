#pragma once
#include <vector>
#include "Layer.h"
#include <Engine/Time/TimeStep.h>
#include "Engine/Event/Event.h"

namespace ArcanaTools {
	class LayerStack {
	public:
		// Add A layer to the front of the container
		static void AddLayer(Layer* layer);
		// same as add layer except it calls attach immediatly afert adding it to the 
		// container
		static void AttachLayer(Layer* layer);
		// want to attach multiple layers in one call.. no worries...
		// here you go
		static void AttachLayers(std::initializer_list<Layer*> layers);

		// add an overlay to the end of the container
		static void AddOverlay(Layer* overlay);

		// same as Add Overlay except it attaches the overlay immediatly afert
		static void AttachOverlay(Layer* overlay);

		// add multiple overlays at once.. remember overlays are added to the back
		// and they will renderer backwords.. so the last overlay to insert will 
		// be the first one rendererd
		static void AttachOverlays(std::initializer_list<Layer*> overlays);

		// remove the target layer from the container
		static void PopLayer(Layer* layer);

		// remove the target overlay from the container
		static void PopOverlay(Layer* overlay);

		static void UpdateLayers(TimeStep ts);
		static void RenderGUILayers();
		static void RenderLayers();
		static void OnEvent(Event& _event);

		static void Cleanup();

	private:
		static std::vector<Layer*> m_layers;
		static unsigned int m_insertIndex;

	};
}