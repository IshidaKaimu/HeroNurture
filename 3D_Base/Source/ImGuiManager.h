#pragma once
#include "ImGui\\imgui_impl_dx11.h"
#include "ImGui\\imgui_impl_Win32.h"
#include "CDirectX11.h"

class CImGuiManager
{
public:
	//������
	static void ImGui_NewFrame();

	//�j��
	static void ImGui_Destroy();

	//�`��
	static void Render();

	static bool Init(HWND hwnd,CDirectX11& dx11);

private:
	CImGuiManager();
	~CImGuiManager();
	CImGuiManager(const CImGuiManager& rhs) = delete;
	CImGuiManager& operator = (const CImGuiManager& rhs) = delete;	
};

