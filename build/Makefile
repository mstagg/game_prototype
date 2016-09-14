#OBJS specifies which files to compile as part of the project 
OBJS = ../src/main.cpp ../src/imgui_impl_sdl_gl3.cpp ../src/libs/imgui/imgui*.cpp

#CC specifies which compiler we're using 
CC = g++ 

#COMPILER_FLAGS specifies the additional compilation options we're using 
# -w suppresses all warnings 
COMPILER_FLAGS = -w 

ifeq ($(OS),Windows_NT)
    #LINKER_FLAGS specifies the libraries we're linking against 
    LINKER_FLAGS = -lglew32s -lopengl32 -lSDL2
else
    LINKER_FLAGS = -lSDL2 -lGL -lGLEW
endif

#OBJ_NAME specifies the name of our exectuable 
OBJ_NAME = prototype

#This is the target that compiles our executable 
all : $(OBJS) 
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)