#pragma once


#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/misc/cpp/imgui_stdlib.h>
#include <imguizmo/ImGuizmo.h>

#ifdef WIN32

#include <glad/glad.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

#endif
