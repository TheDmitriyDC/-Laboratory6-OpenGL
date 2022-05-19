#include "Window.h"

Window::Window() {}

void Window::Initialize(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	WC = MAKEINTATOM(Register(hInstance));
	if (WC == nullptr)
	{
		OutputDebugStringA("Instance Class Registration has Failed!\n");
	}
	FWD = CreateWindowW(WC, L"VME", WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 624 / 2, 480 / 2, 624, 480, NULL, NULL, hInstance, NULL);
	FDC = GetDC(FWD);

	PIXELFORMATDESCRIPTOR FPFD;
	ZeroMemory(&FPFD, sizeof(FPFD));
	FPFD.nSize = sizeof(FPFD);
	FPFD.nVersion = 1;
	FPFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	FPFD.iPixelType = PFD_TYPE_RGBA;
	FPFD.cColorBits = 32;
	FPFD.cAlphaBits = 8;
	FPFD.cDepthBits = 24;

	int FPFDID = ChoosePixelFormat(FDC, &FPFD);
	if (FPFDID == NULL)
	{
		OutputDebugStringA("ChoosePixelFormat has Failed!\n");
	}

	if (SetPixelFormat(FDC, FPFDID, &FPFD) == false)
	{
		OutputDebugStringA("SetPixelFormat has Failed!\n");
	}

	FRC = wglCreateContext(FDC);

	if (FRC == nullptr)
	{
		OutputDebugStringA("wglCreateContext has Failed!\n");
	}
	else
	{
		if (wglMakeCurrent(FDC, FRC) == false)
		{
			OutputDebugStringA("wglMakeCurrent has Failed!\n");
		}
	}
}

void Window::Setup(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	RECT primaryDisplaySize;
	SystemParametersInfoW(SPI_GETWORKAREA, 0, &primaryDisplaySize, 0);
	int posX = (primaryDisplaySize.right - 624) / 2;
	int posY = (primaryDisplaySize.bottom - 480) / 2;

	RECT rect = { 0, 0, 624, 480 };

	AdjustWindowRectEx(&rect, WS_CAPTION | WS_SYSMENU | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_BORDER | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, false, 0);
	//AdjustWindowRect(&rect, WS_CAPTION | WS_SYSMENU | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_BORDER | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, false);
	int TW = rect.right - rect.left;
	int TH = rect.bottom - rect.top;
	WND = CreateWindowW(WC, L"VME", WS_CAPTION | WS_SYSMENU | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_BORDER | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, posX, posY, TW, TH, NULL, NULL, hInstance, NULL);
	DC = GetDC(WND);

	const int Attributes[] =
	{
	WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
	WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
	WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
	WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
	WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
	WGL_COLOR_BITS_ARB, 32,
	WGL_ALPHA_BITS_ARB, 8,
	WGL_DEPTH_BITS_ARB, 24,
	WGL_STENCIL_BITS_ARB, 8,
	WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
	WGL_SAMPLES_ARB, 4, 0
	};

	int pixelFormatID = 0; unsigned int numFormats = 0;

	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARBT = nullptr;
	wglChoosePixelFormatARBT = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(wglGetProcAddress("wglChoosePixelFormatARB"));

	bool ST = false;
	ST = wglChoosePixelFormatARBT(DC, Attributes, NULL, 1, &pixelFormatID, &numFormats);

	if (ST == false || numFormats == 0)
	{
		OutputDebugStringA("wglChoosePixelFormatARBT has Failed!\n");
	}

	PIXELFORMATDESCRIPTOR PFD;
	DescribePixelFormat(DC, pixelFormatID, sizeof(PFD), &PFD);
	SetPixelFormat(DC, pixelFormatID, &PFD);

	const int Major_Minimum = 3, Minor_Minimum = 3;
	const int Context[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, Major_Minimum,
		WGL_CONTEXT_MINOR_VERSION_ARB, Minor_Minimum,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		#ifdef _DEBUG
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB, 0
		#else
			0
		#endif
	};

	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARBT = nullptr;
	wglCreateContextAttribsARBT = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
	RC = wglCreateContextAttribsARBT(DC, 0, Context);

	if (RC == nullptr)
	{
		OutputDebugStringA("wglCreateContextAttribsARBT has Failed!\n");
	}

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(FRC);
	ReleaseDC(FWD, FDC);
	DestroyWindow(FWD);
	if (!wglMakeCurrent(DC, RC))
	{
		OutputDebugStringA("wglMakeCurrent has Failed!\n");
	}

	ShowWindow(WND, nCmdShow);
}

Window::~Window() {}

LRESULT Window::Procedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hWnd, message, wParam, lParam);
	}
	return NULL;
}

ATOM Window::Register(HINSTANCE hInstance)
{
	TCHAR iName[MAX_PATH];
	int iChars = 0;
	iChars = GetModuleFileName(NULL, iName, MAX_PATH);
	HICON icon = ExtractIconW(hInstance, iName, 0);

	WNDCLASSEX WCEX;
	RtlZeroMemory(&WCEX, sizeof(WCEX));
	WCEX.cbSize = sizeof(WCEX);
	WCEX.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	WCEX.lpfnWndProc = Window::Procedure;
	WCEX.hIcon = icon;
	WCEX.hInstance = hInstance;
	WCEX.hCursor = LoadCursor(NULL, IDC_ARROW);
	WCEX.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WCEX.lpszClassName = L"Core";

	return RegisterClassExW(&WCEX);
}
