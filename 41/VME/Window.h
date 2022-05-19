#pragma once
#include "GL-Linker.h"

#if defined (_WIN32) || defined (_WIN64)
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <optional>
#include <shellapi.h>
#endif

#include <iostream>

/// <summary>
/// Base window.
/// </summary>
class Window
{
public:
	Window();
	/// <summary>
	/// Creates temporary context.
	/// </summary>
	/// <param name="hInstance"></param>
	/// <param name="hPrevInstance"></param>
	/// <param name="lpCmdLine"></param>
	/// <param name="nCmdShow"></param>
	void Initialize(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow);
	/// <summary>
	/// Sets attributes, creates actual window.
	/// </summary>
	/// <param name="hInstance"></param>
	/// <param name="hPrevInstance"></param>
	/// <param name="lpCmdLine"></param>
	/// <param name="nCmdShow"></param>
	void Setup(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow);
	~Window();
private:
	LPTSTR WC = nullptr;
	HWND FWD = nullptr; // Temporary Window
	HDC FDC = nullptr; // Temporary Context
	HGLRC FRC = nullptr;
public:
	HWND WND = nullptr; // Actual Window
	HDC DC = nullptr; // Actual Context
	HGLRC RC = nullptr;
private:
	/// <summary>
	/// Window message loop.
	/// </summary>
	/// <param name="hWnd"></param>
	/// <param name="message"></param>
	/// <param name="wParam"></param>
	/// <param name="lParam"></param>
	/// <returns></returns>
	static LRESULT CALLBACK Procedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	/// <summary>
	/// Window registrat„Š„‹„„.
	/// </summary>
	/// <param name="hInstance"></param>
	/// <returns></returns>
	ATOM Register(HINSTANCE hInstance);
public:
	/// <summary>
	/// Swaps window buffers.
	/// </summary>
	/// <param name="wnd"></param>
	static void Swap(Window& wnd)
	{
		SwapBuffers(wnd.DC);
	}
	/// <summary>
	/// Sets window as active context.
	/// </summary>
	/// <param name="wnd"></param>
	static void Set(Window& wnd)
	{
		wglMakeCurrent(wnd.DC, wnd.RC);
	}

	/// <summary>
	/// Resets window context.
	/// </summary>
	static void Reset()
	{
		wglMakeCurrent(NULL, NULL);
	}

	/// <summary>
	/// Updates given window.
	/// </summary>
	/// <param name="wnd"></param>
	static void Update(Window& wnd)
	{
		UpdateWindow(wnd.WND);
	}
};