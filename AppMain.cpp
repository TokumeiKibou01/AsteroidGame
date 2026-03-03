#include <DxLib.h>
#include <vector>
#include "Manager/ObjectManager.h"
#include "Object/BoxObject.h"
#include "Manager/SceneManager.h"
#include "DebugWindow/Win32/DebugWin32Window.h"
#include <thread>
#include "DebugWindow/ImGUI/imgui.h"
#include "DebugWindow/ImGUI/imgui_impl_dx11.h"
#include "DebugWindow/ImGUI/imgui_impl_win32.h"
#include "Manager/AudioManager.h"
#include "MyDxLib.h"
#include "Library/Input.h"

int InitApp();
int InitDxLib();
int InitImGui();
void ExitApp();

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace {
    SceneManager& sceneManager = SceneManager::GetInstance();
    ObjectManager objManager = ObjectManager::GetInstance();
    AudioManager& audioManager = AudioManager::GetInstance();
    int crrTime; //¡‚ÌŽžŠÔ
    int prevTime; //‘O‚ÌŽžŠÔ
    
}

float DeltaTime = 0.0f;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	if (InitApp() != 0) {
		return -1;
	}

    // DebugWin32Window::GetInstance().runThread(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
    crrTime = GetNowCount();
    prevTime = GetNowCount();
	
	while (true) {
		ClearDrawScreen();

        crrTime = GetNowCount();
        DeltaTime = (crrTime - prevTime) / 1000.0f;
        prevTime = crrTime;

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        Input::KeyStateUpdate();

        sceneManager.UpdateScene();
        sceneManager.DrawScene();

        ImGui::Begin("Debug");
        ImGui::End();

        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        RefreshDxLibDirect3DSetting();
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        ScreenFlip();
        WaitTimer(16);
		if (ProcessMessage() == -1) {
			break;
		}
	}
    ExitApp();
	return 0;
}

int InitApp() {
    InitDxLib();
    InitImGui();

    audioManager.Init();
    sceneManager.InitManager();

	return 0;
}

int InitDxLib() {
    ChangeWindowMode(true);
    SetWindowSizeChangeEnableFlag(false, false);
    SetMainWindowText(DxLibParam::WINDOW_TITLE);
    SetGraphMode(Screen::WIDTH, Screen::HEIGHT, 32);
    SetWindowSizeExtendRate(1.0);
    SetBackgroundColor(DxLibParam::BACKGROUND_COLOR[0], DxLibParam::BACKGROUND_COLOR[1], DxLibParam::BACKGROUND_COLOR[2]);
    ChangeFont(DxLibParam::FONT_NAME);
    ChangeFontType(DxLibParam::FONT_TYPE);

    if (DxLib_Init() == -1) {
        DxLib_End();
        return -1;
    }
    SetDrawScreen(DX_SCREEN_BACK);
    SetAlwaysRunFlag(TRUE);
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);
    SetUseHookWinProcReturnValue(FALSE);

    SetHookWinProc([](HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT {
        return ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
        });
}

int InitImGui() {
    ImGui::CreateContext();
    auto& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(GetMainWindowHandle());
    ID3D11Device* device = (ID3D11Device*)GetUseDirect3D11Device();
    ID3D11DeviceContext* deviceContext = (ID3D11DeviceContext*)GetUseDirect3D11DeviceContext();
    ImGui_ImplDX11_Init(device, deviceContext);

    return 0;
}

void ExitApp() {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    DxLib_End();
}