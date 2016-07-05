#OBJS specifies which files to compile as part of the project
OBJS = main.o assets.o

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -c

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -framework SDL2 -framework SDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = sdl_is_go

all: go

main.o: main.cpp main.h
	$(CC) main.cpp $(COMPILER_FLAGS) -o main.o

assets.o: assets.cpp assets.h
	$(CC) assets.cpp $(COMPILER_FLAGS) -o assets.o

compile : $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm -f *.o $(OBJ_NAME)

go: clean compile
	./$(OBJ_NAME)

