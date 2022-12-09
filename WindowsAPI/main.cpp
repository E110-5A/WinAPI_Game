#include "Common.h"
#include "WindowsAPI.h"
#include "jsApplication.h"

#define MAX_LOADSTRING 100
// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.


// 전방선언
ATOM                MyRegisterClass(HINSTANCE hInstance, WNDPROC wndProc, LPCWSTR wndName);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ToolWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    AtlasWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSAPI, szWindowClass, MAX_LOADSTRING);

    // 메모리 누수 확인
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(532);

    // wndclass 정의 (초기 세팅설정)
    MyRegisterClass(hInstance, WndProc, szWindowClass);
    MyRegisterClass(hInstance, AtlasWndProc, L"AtlasWindow");


    // 메인 윈도우 생성 및 활성화
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSAPI));
    MSG msg;


    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // 게임 진행
            js::Application::GetInstance().Tick();
        }
    }
    if (msg.message == WM_QUIT)
    {
        // 메모리 해제할 예정
        //js::jsApplication::GetInstance().
    }

    return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance, WNDPROC wndProc, LPCWSTR wndName)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = wndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr; // MAKEINTRESOURCEW(IDC_WINDOWSAPI);
    wcex.lpszClassName  = wndName;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   WindowData windowData;
   windowData.width = Window_Width;
   windowData.height = Window_Height;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


   windowData.hWnd = hWnd;
   windowData.hdc = nullptr;

   if (!hWnd)
   {
      return FALSE;
   }

   SetWindowPos(hWnd, nullptr, 0, 0, windowData.width, windowData.height, 0);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   js::Application::GetInstance().Initialize(windowData);

   eSceneType type = js::Application::GetInstance().GetPlaySceneType();
   if (type != eSceneType::MapTool)
       return TRUE;


   WindowData atlasWindowData;
   hWnd = CreateWindowW(L"AtlasWindow", szTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   atlasWindowData.hWnd = hWnd;
   js::Application::GetInstance().InitializeAtlasWindow(atlasWindowData);

   
}



#include "jsSceneManager.h"
#include "jsScene.h"
#include "jsMapToolScene.h"
#include "jsTilePalette.h"
#include "jsTile.h"
#include "jsImage.h"
#include "jsInput.h"
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        
    }
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case ID_TILE_SAVE:
            {
                js::Scene* scene = js::SceneManager::GetPlayScene();
                js::MapToolScene* toolScene = dynamic_cast<js::MapToolScene*>(scene);
                toolScene->SaveTilePalette();
            }
            break;
            case ID_TILE_LOAD:
            {
                js::Scene* scene = js::SceneManager::GetPlayScene();
                js::MapToolScene* toolScene = dynamic_cast<js::MapToolScene*>(scene);
                // 툴씬 오브젝트 싹 지우기
                toolScene->LoadTilePalette();
            }
            break;
            case ID_COLLISION_SAVE:
            {
                js::Scene* scene = js::SceneManager::GetPlayScene();
                js::MapToolScene* toolScene = dynamic_cast<js::MapToolScene*>(scene);
                toolScene->SaveTilePalette();
            }
            break;
            case ID_COLLISION_LOAD:
            {
                js::Scene* scene = js::SceneManager::GetPlayScene();
                js::MapToolScene* toolScene = dynamic_cast<js::MapToolScene*>(scene);
                // 툴씬 오브젝트 싹 지우기
                toolScene->LoadTilePalette();
            }
            break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}




// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
