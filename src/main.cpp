
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

int main( int argc, char* args[] )
{
	if(init())
	{

float points[] = {
   0.0f,  0.5f,  0.0f,
   0.25f, -0.25f,  0.0f,
  -0.25f, -0.25f,  0.0f
};

float morePoints[] = {
   0.0f,  0.25f,  0.0f,
   0.125f, -0.125f,  0.0f,
  -0.125f, -0.125f,  0.0f
};

GLuint vbo = 0;
glGenBuffers (1, &vbo);
glBindBuffer (GL_ARRAY_BUFFER, vbo);
glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), points, GL_STATIC_DRAW);

GLuint vbo1 = 1;
glGenBuffers (1, &vbo1);
glBindBuffer (GL_ARRAY_BUFFER, vbo1);
glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), morePoints, GL_STATIC_DRAW);

GLuint vao = 0;
glGenVertexArrays (1, &vao);
glBindVertexArray (vao);
glEnableVertexAttribArray (0);
glBindBuffer (GL_ARRAY_BUFFER, vbo);
glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

GLuint vao1 = 1;
glGenVertexArrays (1, &vao1);
glBindVertexArray (vao1);
glEnableVertexAttribArray (0);
glBindBuffer (GL_ARRAY_BUFFER, vbo1);
glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

const char* vertex_shader =
"#version 400\n"
"in vec3 vp;"
"void main () {"
"  gl_Position = vec4 (vp, 1.0);"
"}";

const char* fragment_shader =
"#version 400\n"
"out vec4 frag_colour;"
"void main () {"
"  frag_colour = vec4 (1.0, 1.0, 0.0, 1.0);"
"}";

const char* fragment_shader2 =
"#version 400\n"
"out vec4 frag_colour;"
"void main () {"
"  frag_colour = vec4 (1.0, 0.0, 0.0, 1.0);"
"}";

GLuint vs = glCreateShader (GL_VERTEX_SHADER);
glShaderSource (vs, 1, &vertex_shader, NULL);
glCompileShader (vs);
GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
glShaderSource (fs, 1, &fragment_shader, NULL);
glCompileShader (fs);
GLuint fs2 = glCreateShader (GL_FRAGMENT_SHADER);
glShaderSource (fs2, 1, &fragment_shader2, NULL);
glCompileShader (fs2);

GLuint shader_programme = glCreateProgram ();
glAttachShader (shader_programme, fs);
glAttachShader (shader_programme, vs);
glLinkProgram (shader_programme);

GLuint shader_programme2 = glCreateProgram ();
glAttachShader (shader_programme2, fs2);
glAttachShader (shader_programme2, vs);
glLinkProgram (shader_programme2);

// wipe the drawing surface clear
glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glUseProgram (shader_programme);
glBindVertexArray (vao);
// draw points 0-3 from the currently bound VAO with current in-use shader
glDrawArrays (GL_TRIANGLES, 0, 3);

glUseProgram (shader_programme2);
glBindVertexArray (vao1);
// draw points 0-3 from the currently bound VAO with current in-use shader
glDrawArrays (GL_TRIANGLES, 0, 3);

SDL_GL_SwapWindow(window);

/*

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
*/
		SDL_Delay(5000);
	}

	quit();
	return 0;
}

