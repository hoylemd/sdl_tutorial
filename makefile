#OBJS specifies which files to compile as part of the project
OBJS = 01_hello_SDL.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = 01_hello_SDL

clean:
	rm a.out *.o $(OBJ_NAME)

#This is the target that compiles our executable
all : $(OBJS)
		g++ $(OBJS) -w -lSDL2 -o $(OBJ_NAME)
