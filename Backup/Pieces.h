#ifndef __PIECES_H

#define __PIECES_H

typedef struct Square {

	int row;

	int column;

	char occupied;

} Square;


typedef struct Pawn {

	Square *s;

	char color;

} Pawn;

typedef struct Rook {

	Square *s;

	char color;

} Rook;

typedef struct Knight {

	Square *s;

	char color;

} Knight;

typedef struct Bishop {

	Square *s;

	char color;

} Bishop;

typedef struct King {

	Square *s;

	char color;

	int inCheck;

	int checkmated;
	
	int stalemated;

} King;

typedef struct Queen {

	Square *s;

	char color;	

} Queen;

#endif
