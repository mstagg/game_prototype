
#define WINDOWS 0
#define MAC 1
#define UNIX 2

#if defined(_WIN32)
    #define OPERATING_SYS WINDOWS
#elif defined(__APPLE__)
    #define OPERATING_SYS MAC
#else
    #define OPERATING_SYS UNIX
#endif

// If compiling to windows, SDL_MAIN_HANDLED must be defined before including SDL.h
#if OPERATING_SYS == WINDOWS
    #define SDL_MAIN_HANDLED
#endif

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>

#define GL3_PROTOTYPES 1

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

SDL_Window* window;
SDL_Surface* windowSurface;
SDL_GLContext windowContext;

bool initSDL()
{
	printf("%s\n", "\tIntializing SDL...");
	if(SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		return true;
	}
}

bool initWindow()
{
	printf("%s\n", "\tIntializing Main Window...");
	//Create window arguments = (TITLE OF WINDOW, X WINDOW POS, Y WINDOW POS, SCREEN WIDTH, SCREEN HEIGHT, CREATION FLAGS)
	window = SDL_CreateWindow("Prototype", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	if(window == NULL)
	{
		char c[256];
		sprintf(c, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error", c, NULL);
		return false;
	}
	else
	{
		return true;
	}
}

bool initOpenGL()
{
	printf("%s\n", "\tIntializing OpenGL...");
	windowContext = SDL_GL_CreateContext(window);
	if(windowContext == NULL)
	{
		char c[256];
		sprintf(c, "OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error", c, NULL);
		return false;
	}

	// Set our OpenGL version.
    // SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    // Turn on double buffering with a 24bit Z buffer.
    // You may need to change this to 16 or 32 for your system
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // This makes our buffer swap syncronized with the monitor's vertical refresh
    SDL_GL_SetSwapInterval(1);

    return true;
}

bool init()
{
	printf("%s\n", "Starting Intialization...");
	if(!initSDL()) return false;
	if(!initWindow()) return false;
	if(!initOpenGL()) return false;
	return true;
}

void quit()
{
	printf("%s\n", "Shutting down...");

	// Destroy OpenGL context
	SDL_GL_DeleteContext(windowContext);

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	if(init())
	{
		// Clear window to black
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);

		// Clear window to red
		glClearColor(1.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);

		SDL_Delay(2000);

		// Clear window to green
		glClearColor(0.0, 1.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);

		SDL_Delay(2000);

		// Clear window to blue
		glClearColor(0.0, 0.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);

		SDL_Delay(2000);
	}

	quit();
	return 0;
}

