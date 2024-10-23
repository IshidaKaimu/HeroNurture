#include "ImGuiManager.h"

constexpr char  FONT_FILE_PATH[] = "Data\\Font\\NotoSansJP-SemiBold.ttf";
constexpr float FONT_SIZE = 18.0f;

CImGuiManager::~CImGuiManager()
{
}

void CImGuiManager::ImGui_NewFrame()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void CImGuiManager::ImGui_Destroy()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void CImGuiManager::Render()
{
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::Render();

    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

//初期化関数
bool CImGuiManager::Init(HWND hwnd,CDirectX11& dx11)
{
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;            // ドッキングを有効にする.
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    io.DeltaTime = 1.0f / 60.0f;                                // set the time elapsed since the previous frame (in seconds)
    io.DisplaySize.x = WND_W;                                    // 横の画面サイズ.
    io.DisplaySize.y = WND_H;                                    // 縦の画面サイズ.

    // フォントを読み込む.
    ImFont* font = io.Fonts->AddFontFromFileTTF(
        FONT_FILE_PATH,
        FONT_SIZE,
        NULL,
        io.Fonts->GetGlyphRangesJapanese());

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    if (ImGui_ImplWin32_Init(hwnd) == false) { return E_FAIL; };
    if (ImGui_ImplDX11_Init(dx11.GetDevice(), dx11.GetContext()) == false) { return E_FAIL; }

    return true;
}
