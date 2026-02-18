#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_video.h>
#include <include/glad.h>
#include <GL/gl.h>
#include <iostream>
#include <thread>

// Window size
constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

bool running = false;

int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_GLContext context;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
        return -1;
    }

    SDL_GL_LoadLibrary(NULL);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create the window with proper dimensions
    window = SDL_CreateWindow("Klein", WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    if (!window) {
        fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    context = SDL_GL_CreateContext(window);
    if (!context) {
        fprintf(stderr, "OpenGL context creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Check OpenGL properties
    if (!gladLoadGL(SDL_GL_GetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        SDL_GL_DestroyContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    printf("OpenGL loaded\n");
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));

    // Main loop
    while (!running) {
        SDL_Event e;
        // Handle all pending events
        while (SDL_PollEvent(&e)) {
            // User has pressed a key?
            if (e.type == SDL_EVENT_KEY_DOWN) {
                // The pressed key was Escape?
                if (e.key.key == SDLK_ESCAPE) {
                    running = true;
                }
            }
            // Also handle window close events
            else if (e.type == SDL_EVENT_QUIT) {
                running = true;
            }
        }

        // Render after handling events
        glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers to display rendered content
        SDL_GL_SwapWindow(window);

        // Optional: Small delay to prevent high CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }

    // Cleanup
    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
