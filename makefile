#OBJS specifies which files to compile as part of the project
OBJS = 01_hello_SDL.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
#  COMPILER_FLAGS = -w
#
#  #LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -framework SDL2

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = sdl_is_go

all: go

#This is the target that compiles our executable
compile : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

go: compile
	./$(OBJ_NAME)


clean:
	rm a.out *.o $(OBJ_NAME)
