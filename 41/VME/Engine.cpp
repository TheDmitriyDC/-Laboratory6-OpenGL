#include "Engine.h"

Engine::Engine() {}

int Engine::Process(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
    #pragma region Context & Window Initialization
        // Context & Window Initialization
        WND.Initialize(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
        if (!gladLoadGL())
        {
            OutputDebugStringA("gladLoadGL() Failed!\n");
            PostQuitMessage(48);
        }
        if (!gladLoadWGL(WND.DC))
        {
            OutputDebugStringA("gladLoadWGL() Failed!\n");
            PostQuitMessage(48);
        }
        WND.Setup(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
        Window::Set(WND);
        // -------------------------------
    #pragma endregion

    #pragma region OpenGL Parameters Configuration
        // OpenGL Parameters Configuration
        Engine::Configure();
        // -------------------------------
    #pragma endregion

    #pragma region Scene Initialization
        // Scene Initialization
        scene.Initialize();
        // --------------------
    #pragma endregion

    #pragma region Buffers Initialization
        // Buffers
        VB.Load("Shaders\\Velocity-Map.vert", "Shaders\\Velocity-Map.frag");
        VB.Setup();
        VB.Initialize();
        IB.Load("Shaders\\Screen.vert", "Shaders\\Screen.frag");
        IB.Setup();
        IB.Initialize();
        MB.Load("Shaders\\Motion-Blur.vert", "Shaders\\Motion-Blur.frag");
        MB.Setup();
        MB.Initialize();
        GB.Load();
        GB.Initialize();
        // -------
    #pragma endregion

    DF.Load("Shaders\\Default.vert", "Shaders\\Default.frag");

    #pragma region Screen-Quad Generation
        // Screen Quad
        glGenVertexArrays(1, &QVAO);
        glGenBuffers(1, &QVBO);
        glBindVertexArray(QVAO);
        glBindBuffer(GL_ARRAY_BUFFER, QVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(QV), &QV, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        // -----------
    #pragma endregion

    #pragma region Texture Binding
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, VB.Texture);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, GB.Normal);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, GB.Position);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, IB.Texture);
    #pragma endregion

    while (true)
    {
        time.Start();

        MSG Message{};
        while (PeekMessageW(&Message, nullptr, 0, 0, PM_REMOVE))
        {
            if (Message.message == WM_QUIT)
            {
                return Message.wParam;
            }
            TranslateMessage(&Message);
            DispatchMessageW(&Message);
        }

        // Updates scene
        scene.Update(time.deltaTime);
        // -------------

        #pragma region Framebuffer Chain
            glEnable(GL_DEPTH_TEST);
            // Geometry Buffer
            GB.Bind(camera);
            scene.Render(camera, GB.Shader);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            // ---------------

            // Velocity Buffer
            VB.Bind();
            scene.Render(camera, VB.Shader);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            // ---------------

            // Default Render
            IB.Bind();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // glClear(GL_DEPTH_BUFFER_BIT);
            scene.Render(camera, DF);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            // --------------

            Utilities::Combine(IB.FBO, MB.FBO);

            // Motion Blur
            MB.Bind();
            glClear(GL_DEPTH_BUFFER_BIT);
            Utilities::Bufferize(QVAO, MB.Texture);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            // -----------
            glDisable(GL_DEPTH_TEST);
        #pragma endregion

        glBindVertexArray(QVAO);
        glBindTexture(GL_TEXTURE_2D, MB.Texture);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Window Functions
        Window::Swap(WND);
        Window::Update(WND);
        // ----------------

        // Gather information for next frame
        scene.Gather();
        camera.Gather();
        // ---------------------------------

        OutputDebugStringA("Current framerate: ");
        OutputDebugStringA(std::to_string(time.frame_count).c_str());
        OutputDebugStringA("\n");

        time.End();
    }

	return 0;
}

void Engine::Configure()
{
    glEnable(GL_DEPTH_TEST);
    glDepthRange(0.0, 1.0);

    glEnable(GL_MULTISAMPLE);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DITHER);

    glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
}

Engine::~Engine() {}