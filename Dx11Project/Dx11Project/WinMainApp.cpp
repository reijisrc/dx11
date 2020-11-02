#include <Windows.h>


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	const LPCSTR pClassName = "dx11_3d";
	const LPCWSTR pwClassName = L"dx11_3d";
	// register windows class
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = nullptr;
	wcex.hCursor = nullptr;
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = pClassName;
	wcex.hIconSm = nullptr;
	RegisterClassEx(&wcex);
	// create windows instance
	HWND hWnd = CreateWindowExW(0,
		pwClassName,
		L"Dx11_3d",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200,
		640, 480,
		nullptr,
		nullptr,
		hInstance,
		nullptr);
	// show windos 
	ShowWindow(hWnd, SW_SHOW);
 
	MSG msg;
	// massage loop
	while (GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// PostQuitMessage value
	return (INT)msg.wParam;
}
