CC = g++
LFLAGS = -o
CFLAGS = -c -g -Wall -Werror
INC = ./inc
IFLAG = -I$(INC)
BIN = ./bin
OBJ = ./obj
SRC = ./src

all: app

app: $(OBJ)/main.o
	$(CC) $(LFLAGS) $(BIN)/main $(OBJ)/main.o

$(OBJ)/main.o: $(SRC)/main.cpp
	$(CC) $(CFLAGS) $(IFLAG) $(SRC)/main.cpp 
	mv *.o $(OBJ)



clean:
	@echo "Cleaning is in Progress"
	rm -f a.out main
	rm -f *.o
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/main
	@echo "Done!"
