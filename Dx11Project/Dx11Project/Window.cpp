#include "Window.h"
#include <tchar.h> 

// singleton ptr
Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept
	: hInst( GetModuleHandle( nullptr))
{
	// register windows class
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = handleMsgSetup;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = getInstace();
	wcex.hIcon = nullptr;
	wcex.hCursor = nullptr;
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = getName();
	wcex.hIconSm = nullptr;
	RegisterClassEx(&wcex);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass( wndClassName, getInstace());
}

const char* Window::WindowClass::getName() noexcept
{
	return wndClassName;
}

HINSTANCE Window::WindowClass::getInstace() noexcept
{
	return wndClass.hInst;
}

Window::Window(int width, int height, const char* name)  noexcept
	:
	width(width),
	height(height)
{
	// calculate windows size
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	// adjust size except title and bar
	AdjustWindowRect( &wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
	// create windows instance
	HWND hWnd = CreateWindow(WindowClass::getName(),
		name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		wr.right - wr.left, wr.bottom - wr.top,
		nullptr,
		nullptr,
		WindowClass::getInstace(),
		this);
	// show windos 
	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

LRESULT WINAPI Window::handleMsgSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
	// use crate parameter passed in from CreateWindow() to store window class ptr
	if (uMsg == WM_CREATE)
	{
		// extract ptr to window class from creation data
		const CREATESTRUCT* const pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		// set WinAPI-managed user-Data to store ptr to window class
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// set Message Proc to normal(non-setup) handler now that setup is finished
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::handleMsgSetup));
		// forward message to window class handler
		return pWnd->handleMsg(hWnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT WINAPI Window::handleMsgThunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	return pWnd->handleMsg(hWnd, uMsg, wParam, lParam);
}

LRESULT Window::handleMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch ( uMsg )
	{
	default:
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}