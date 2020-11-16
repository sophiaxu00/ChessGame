#Jianing Fang jfang25; Fanbo Xu fxu13; Ruixuan Zhai rzhai2
CC=g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

chess: main.o CreatePiece.o Chess.o Board.o Bishop.o Knight.o King.o Queen.o Pawn.o Rook.o
	$(CC) $(CFLAGS) -o chess main.o CreatePiece.o Chess.o Board.o Bishop.o Knight.o King.o Queen.o Pawn.o Rook.o

CreatePiece.o: CreatePiece.h Pawn.h Rook.h Knight.h Mystery.h Bishop.h Queen.h King.h CreatePiece.cpp
	$(CC) $(CFLAGS) -c CreatePiece.cpp

Chess.o: Chess.h CreatePiece.h Chess.cpp
	$(CC) $(CFLAGS) -c Chess.cpp

main.o: Chess.h main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Board.o: Board.h CreatePiece.h Board.cpp
	$(CC) $(CFLAGS) -c Board.cpp

Bishop.o: Bishop.h Bishop.cpp
	$(CC) $(CFLAGS) -c Bishop.cpp

Knight.o: Knight.h Knight.cpp
	$(CC) $(CFLAGS) -c Knight.cpp

King.o: King.h King.cpp
	$(CC) $(CFLAGS) -c King.cpp

Queen.o: Queen.h Queen.cpp
	$(CC) $(CFLAGS) -c Queen.cpp

Pawn.o: Pawn.h Pawn.cpp
	$(CC) $(CFLAGS) -c Pawn.cpp

Rook.o: Rook.h Rook.cpp
	$(CC) $(CFLAGS) -c Rook.cpp

clean:
	rm -f *.o chess *~
