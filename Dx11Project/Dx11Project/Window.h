#pragma once

#include "WinDefine.h"

class Window
{
private:
	// singleton class registeration / cleanup of window class
	class WindowClass
	{
	public:
		static const char* getName() noexcept;
		static HINSTANCE getInstace() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass( const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass& ) = delete;
		static constexpr const char* wndClassName = "Directx 3D Engine";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};

public:
	Window(int width, int height, const char* name) noexcept;
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
private:
	static LRESULT CALLBACK handleMsgSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK handleMsgThunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT handleMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
private:
	int width;
	int height;
	HWND hWnd;
};
