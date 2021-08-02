#include "LayerStack.h"

namespace ArcanaTools {
	std::vector<Layer*> LayerStack::m_layers{};
	unsigned int LayerStack::m_insertIndex = 0;

	void LayerStack::AddLayer(Layer* layer)
	{
		m_layers.emplace(m_layers.begin() + m_insertIndex, layer);
		m_insertIndex++;
	}

	void LayerStack::AttachLayer(Layer* layer)
	{
		m_layers.emplace(m_layers.begin() + m_insertIndex, layer);
		m_insertIndex++;
		layer->OnAttach();
	}
	void LayerStack::AttachLayers(std::initializer_list<Layer*> layers)
	{
		for (auto layer : layers) {
			m_layers.emplace(m_layers.begin() + m_insertIndex, layer);
			m_insertIndex++;
			layer->OnAttach();
		}

	}
	void LayerStack::AddOverlay(Layer* overlay)
	{
		m_layers.emplace_back(overlay);
	}

	void LayerStack::AttachOverlay(Layer* overlay)
	{
		m_layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::AttachOverlays(std::initializer_list<Layer*> overlays)
	{
		for (auto overlay : overlays)
		{
			m_layers.emplace_back(overlay);
			overlay->OnAttach();
		}
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.begin() + m_insertIndex, layer);
		if (it != m_layers.begin() + m_insertIndex)
		{
			layer->OnDetach();
			m_layers.erase(it);
			m_insertIndex--;
		}
	}
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_layers.begin() + m_insertIndex, m_layers.end(), overlay);
		if (it != m_layers.end())
		{
			overlay->OnDetach();
			m_layers.erase(it);
		}
	}
	void LayerStack::UpdateLayers(TimeStep ts)
	{
		for (size_t i = 0; i < m_layers.size(); i++)
		{
			m_layers[i]->OnUpdate(ts);
		}
	}

	void LayerStack::RenderGUILayers()
	{
		for (size_t i = 0; i < m_layers.size(); i++)
		{
			m_layers[i]->OnImGuiRender();
		}
	}

	void LayerStack::RenderLayers()
	{
		for (int i = m_layers.size() - 1; i >= 0; i--)
		{
			m_layers[i]->OnRender();
		}
	}

	void LayerStack::OnEvent(Event& _event)
	{
		for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it) 
		{
			if (_event.Handled)
				break;
			(*it)->OnEvent(_event);
		}
	}

	void LayerStack::Cleanup()
	{
		for (int i= m_layers.size()- 1; i >= 0; i--)
		{
			m_layers[i]->OnDetach();
			delete m_layers[i];
			m_layers.pop_back();
		}

	}

}