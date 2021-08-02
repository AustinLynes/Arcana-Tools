#include "ImGuiLayer.h"

#include <Platform/ImGui/ImGuiBuild.h>
#include <Engine/Window/Window.h>

namespace ArcanaTools{
    ImGuiLayer::ImGuiLayer() : Layer("ImGui") {}
   
	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		//io.ConfigDockingWithShift = true;

		io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;
		io.BackendFlags |= ImGuiBackendFlags_RendererHasViewports;
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;

		io.BackendPlatformName = "imgui_impl_win64";

        // LOAD FONTS 

        // SET STYLE 
        SetStyle();

		ImGui_ImplGlfw_InitForOpenGL(Window::GetGLFWWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 460");

	}
 
    void ImGuiLayer::OnDetach()
	{
		
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
	
	}

    void ImGuiLayer::OnEvent(Event& e)
    {
        if (m_BlockEvents) {
            ImGuiIO& io = ImGui::GetIO();
            e.Handled |= e.HasClassification(Events::Classification::Mouse) & io.WantSetMousePos;
            e.Handled |= e.HasClassification(Events::Classification::Keyboard) & io.WantCaptureKeyboard;
        }

    }

	void ImGuiLayer::BackupContext()
	{
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

    void ImGuiLayer::Begin()
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGuizmo::BeginFrame();
    }

    void ImGuiLayer::End()
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)Window::GetWidth(), (float)Window::GetHeight());

        // rendering 
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        BackupContext();
    }


#pragma region THEMES

    void ImGuiLayer::SetStyle()
    {
        ImGuiStyle* style = &ImGui::GetStyle();
        ImVec4* colors = style->Colors;

        ImVec4 font_color = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);




        // window colors
        ImVec4 window_background_color = { 0.1, 0.1, 0.1, 1.00 };  // WINDOW BACKGROUND 


        ImVec4 child_window_background_color = ImVec4(0.100f, 0.100f, 0.120f, 0.6500f);
        ImVec4 modal_background_color = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);

        // style colors
        ImVec4 border_color = ImVec4(0.08f, 0.08f, 0.08f, 1.000f);
        ImVec4 border_shadow_color = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);

        // widgit color
        //      header
        ImVec4 header_background_color = ImVec4(0.313f, 0.313f, 0.313f, 1.000f); //
        //      scrollbar
        ImVec4 scrollbar_background_color = ImVec4(0.160f, 0.160f, 0.460f, 1.000f); //
        //      title
        ImVec4 title_background_color = ImVec4(0.0500f, 0.050f, 0.050f, 1.000f); // hmmm
        //      menu bar
        ImVec4 menu_bar_background_color = ImVec4(0.0500f, 0.050f, 0.050f, 1.000f);
        //      frame
        ImVec4 frame_background_color = ImVec4(0.10f, 0.10f, 0.10f, 1.000f); // NO 
        ImVec4 active_frame_color = ImVec4(0.160f, 0.160f, 0.260f, 1.000f);

        ImVec4 theme_color = ImVec4(0.20f, 0.200f, 0.220f, 1.000f);


        colors[ImGuiCol_Text] = font_color;
        colors[ImGuiCol_TextDisabled] = ImVec4(0.5f, 0.5f, 0.5f, 0.5f);

        colors[ImGuiCol_WindowBg] = window_background_color;
        colors[ImGuiCol_ChildBg] = window_background_color;
        colors[ImGuiCol_PopupBg] = window_background_color;

        colors[ImGuiCol_Border] = border_color;
        colors[ImGuiCol_BorderShadow] = border_shadow_color;

        colors[ImGuiCol_FrameBg] = window_background_color;
        colors[ImGuiCol_FrameBgHovered] = theme_color;
        colors[ImGuiCol_FrameBgActive] = theme_color;

        colors[ImGuiCol_TitleBg] = window_background_color;
        colors[ImGuiCol_TitleBgActive] = window_background_color;
        colors[ImGuiCol_TitleBgCollapsed] = window_background_color;

#pragma region MENU

        colors[ImGuiCol_MenuBarBg] = window_background_color;

#pragma endregion
        // scrollbar
        colors[ImGuiCol_ScrollbarBg] = theme_color;
        colors[ImGuiCol_ScrollbarGrab] = theme_color;
        colors[ImGuiCol_ScrollbarGrabHovered] = theme_color;
        colors[ImGuiCol_ScrollbarGrabActive] = theme_color;
        colors[ImGuiCol_CheckMark] = font_color;

        colors[ImGuiCol_SliderGrab] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
        colors[ImGuiCol_SliderGrabActive] = theme_color;

        colors[ImGuiCol_Button] = ImVec4(1.000f, 1.000f, 1.000f, 0.000f);
        colors[ImGuiCol_ButtonHovered] = theme_color;
        colors[ImGuiCol_ButtonActive] = theme_color;

        colors[ImGuiCol_Header] = window_background_color;
        colors[ImGuiCol_HeaderHovered] = theme_color;
        colors[ImGuiCol_HeaderActive] = theme_color;

        colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
        colors[ImGuiCol_SeparatorHovered] = theme_color;
        colors[ImGuiCol_SeparatorActive] = theme_color;

        colors[ImGuiCol_ResizeGrip] = ImVec4(1.000f, 1.000f, 1.000f, 0.050f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.170f);
        colors[ImGuiCol_ResizeGripActive] = theme_color;
#pragma region TABS
        ImVec4 tab = ImVec4{ .16,.16,.16,1.0 };

        colors[ImGuiCol_Tab] = window_background_color;
        colors[ImGuiCol_TabHovered] = window_background_color;
        colors[ImGuiCol_TabActive] = window_background_color;
        colors[ImGuiCol_TabUnfocused] = window_background_color;
        colors[ImGuiCol_TabUnfocusedActive] = window_background_color;

#pragma endregion
        colors[ImGuiCol_DockingPreview] = theme_color;
        colors[ImGuiCol_DockingEmptyBg] = window_background_color;
        colors[ImGuiCol_DragDropTarget] = theme_color;

        colors[ImGuiCol_PlotLines] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
        colors[ImGuiCol_PlotLinesHovered] = theme_color;
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.586f, 0.586f, 0.586f, 1.000f);
        colors[ImGuiCol_PlotHistogramHovered] = theme_color;

        colors[ImGuiCol_TextSelectedBg] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);

        colors[ImGuiCol_NavHighlight] = { 0,0,0,0 };
        colors[ImGuiCol_NavWindowingHighlight] = { 0,0,0,0 };
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);

        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);

#pragma region PADDING

        style->FramePadding = { 30, 10 };
        style->CellPadding = { 0,0 };
        style->WindowPadding = { 5,5 };

#pragma endregion
#pragma region BORDERS

        style->FrameBorderSize = 1.0f;
        style->ChildBorderSize = 1.0f;
        style->PopupBorderSize = 1.0f;
        style->TabBorderSize = 1.0f;

#pragma endregion
#pragma region ROUNDING
        style->FrameRounding = 12.0f;
        style->ChildRounding = 0.0f;
        style->PopupRounding = 12.0f;
        style->TabRounding = 12.0f;
        style->ScrollbarRounding = 12.0f;
        style->WindowRounding = 0.0f;

#pragma endregion



        style->GrabMinSize = 10.0f;
        style->ItemSpacing = { 20.0f, 10.0f };
        style->ItemInnerSpacing = { 10.0f, 10.0f };
        //style->TabMinWidthForCloseButton = FLT_MAX;
        style->ScrollbarSize = 6.0f;



    }

  

#pragma endregion


}