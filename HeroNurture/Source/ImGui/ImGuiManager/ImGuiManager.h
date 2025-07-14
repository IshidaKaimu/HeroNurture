#pragma once
#include "ImGui\imgui_impl_dx11.h"
#include "ImGui\imgui_impl_Win32.h"
#include "Global\Global.h"
#include "CDirectX11.h"

//=====================================
// ImGuiマネージャークラス
// 制作者:石田櫂夢
//=====================================

class CImGuiManager
{
public:
	//初期化
	static void ImGui_NewFrame();

	//破棄
	static void ImGui_Destroy();

	//描画
	static void Render();

	static bool Init(HWND hwnd,CDirectX11& dx11);

private:
	CImGuiManager();
	~CImGuiManager();
	CImGuiManager(const CImGuiManager& rhs) = delete;
	CImGuiManager& operator = (const CImGuiManager& rhs) = delete;	
};

