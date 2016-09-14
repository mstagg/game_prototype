#include "com/Broker.h"

#include <stdio.h>

//TODO: Build a consumer on a new thread

int main()
{
	Broker* b = new Broker();

	b->addSubscription("test 1");
	b->addSubscription("test 2");

	Message* m = new Message("msg 1");
	b->addMessage("test 1", m);

	printf("%s\r\n", b->getMessage("test 1")->payload.c_str());
	printf("%s\r\n", b->getMessage("test 1")->payload.c_str());

	delete m;

	delete b;

	return 0;
}

/*
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
    #define GLEW_STATIC
#endif

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>

#include "libs/imgui/imgui.h"
#include "imgui_impl_sdl_gl3.h"

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
		ImGui_ImplSdlGL3_Init(window);
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
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    // Turn on double buffering with a 24bit Z buffer.
    // You may need to change this to 16 or 32 for your system
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // This makes our buffer swap syncronized with the monitor's vertical refresh
    SDL_GL_SetSwapInterval(1);

	glewExperimental = GL_TRUE;
	glewInit();

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

const char* vertexShader =
"#version 430\r\n"
""
"in layout(location=0) vec2 position;"
"in layout(location=1) vec3 vertexColor;"
""
"out vec3 theColor;"
""
"void main()"
"{"
"gl_Position = vec4(position, 0.0, 1.0);"
"theColor = vertexColor;"
"}";

const char* fragmentShader =
"#version 430\r\n"
""
"in vec3 theColor;"
"out vec4 color;"
""
"void main()"
"{"
"color = vec4(theColor, 1.0);"
"}";

void installShaders()
{
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	const char* adapter[1];
	adapter[0] = vertexShader;
	glShaderSource(vertexShaderId, 1, adapter, 0);
	adapter[0] = fragmentShader;
	glShaderSource(fragmentShaderId, 1, adapter, 0);

	glCompileShader(vertexShaderId);
	glCompileShader(fragmentShaderId);

	GLint err1, err2;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &err1);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &err2);

	if(err1 != GL_TRUE)
	{
		GLint infoLogLength;
		glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		glGetShaderInfoLog(vertexShaderId, infoLogLength, &bufferSize, buffer);
		printf("VERTEX SHADER ERROR: %i, '%s'", err1, buffer);

		delete buffer;
	}

	if(err2 != GL_TRUE)
	{
		GLint infoLogLength;
		glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		glGetShaderInfoLog(fragmentShaderId, infoLogLength, &bufferSize, buffer);
		printf("FRAGMENT SHADER ERROR: %i, '%s'", err2, buffer);

		delete buffer;
	}

	glGetProgramiv(vertexShaderId, GL_COMPILE_STATUS, &err1);
	if(err1 != GL_TRUE)
	{
		GLint infoLogLength;
		glGetProgramiv(vertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		glGetProgramInfoLog(vertexShaderId, infoLogLength, &bufferSize, buffer);
		printf("LINKER ERROR: %i, '%s'", err1, buffer);

		delete buffer;
	}

	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	glUseProgram(programId);
}

int main( int argc, char* args[] )
{
	if(init())
	{
		installShaders();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		SDL_GL_SwapWindow(window);

		GLfloat verts[]
		{
			0.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			1.0f, 1.0f,
			0.0f, 1.0f, 0.0f,
			-1.0f, 1.0f,
			1.0f, 0.0f, 0.0f
		};

		GLuint bufferId;
		GLuint indexBufferID;
		bool done = false;
		bool show_test_window = true;

		while(!done)
		{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glGenBuffers(1, &bufferId);
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (char *)(sizeof(GLfloat) * 2));

		GLushort indices[] = {0, 1, 2, 0, 3, 4};
		glGenBuffers(1, &indexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSdlGL3_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
        }
ImGui_ImplSdlGL3_NewFrame(window);
            ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiSetCond_FirstUseEver);
            ImGui::Begin("Another Window", &show_test_window);
            ImGui::Text("Hello");
            ImGui::End();

		glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
		ImGui::Render();
		SDL_GL_SwapWindow(window);

		SDL_Delay(16);
		}
	}

ImGui_ImplSdlGL3_Shutdown();
	quit();
	return 0;
}
*/
