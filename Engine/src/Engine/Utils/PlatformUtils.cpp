#include "PlatformUtils.h"
#include <Windows.h>
#include "Engine/Window/Window.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <commdlg.h>

namespace ArcanaTools {
	namespace Utils {
		std::optional<std::string> FileDialog::OpenFile(const char* filter)
		{
			OPENFILENAMEA open;
			CHAR szFILE[260] = { 0 };
			CHAR currentDir[256] = { 0 };
			ZeroMemory(&open, sizeof(OPENFILENAME));
			open.lStructSize = sizeof(OPENFILENAME);
			open.hwndOwner = glfwGetWin32Window((GLFWwindow*)Window::GetGLFWWindow());
			open.lpstrFile = szFILE;
			open.nMaxFile = sizeof(szFILE);
			if (GetCurrentDirectoryA(256, currentDir)) {
				open.lpstrInitialDir = currentDir;
			}
			open.lpstrFilter = filter;
			open.nFilterIndex = 1;
			open.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

			if (GetOpenFileNameA(&open) == TRUE)
				return open.lpstrFile;


			return std::nullopt;


		}
		std::optional<std::string> FileDialog::SaveFile(const char* filter)
		{
			OPENFILENAMEA open;
			CHAR szFILE[260] = { 0 };
			CHAR currentDir[256] = { 0 };
			ZeroMemory(&open, sizeof(OPENFILENAME));
			open.lStructSize = sizeof(OPENFILENAME);
			open.hwndOwner = glfwGetWin32Window((GLFWwindow*)Window::GetGLFWWindow());
			open.lpstrFile = szFILE;
			open.nMaxFile = sizeof(szFILE);
			if (GetCurrentDirectoryA(256, currentDir)) {
				open.lpstrInitialDir = currentDir;
			}
			open.lpstrFilter = filter;
			open.nFilterIndex = 1;
			open.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

			open.lpstrDefExt = strchr(filter, '\0')+1;

			if (GetOpenFileNameA(&open) == TRUE)
				return open.lpstrFile;


			return std::optional<std::string>();
		}
	}
}