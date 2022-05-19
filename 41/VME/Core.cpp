#include <exception>
#include "Engine.h"

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_opt_ LPSTR lpCmdLine, _In_ INT nCmdShow)
{
	try
	{
		return Engine{}.Process(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	}
	catch (const std::exception& e)
	{
		return 24;
	}
	catch (...)
	{
		return 12;
	}
	return 6;
}