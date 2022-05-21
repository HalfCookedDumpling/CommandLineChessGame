#include <stdio.h>

#include <stdlib.h>

#include "Pieces.h"


static Square *squares[8][8];

static char *input; 

static char turn;

static int whiteKingMoved; 

static int blackKingMoved;

static int whiteKingRookMoved;

static int whiteQueenRookMoved;

static int blackKingRookMoved;

static int blackQueenRookMoved;


int abs (const int num) {

	if (num < 0) {

		return num * -1;

	}

	return num;

} 

int length (const char *str) {

	int i;

	for (i = 0; str[i] != '\0'; i++);

	return i;

}

int indexOf (const char *str1, const char a) {

	int i;

	for (i = 0; i < length(str1); i++) {

		if (str1[i] == a) {
	
			return i;

		}

	}

	return -1;

}

int strEquals (const char *str1, const char *str2) {

	if (length(str1) != length(str2)) {

		return 0;

	}

	int i;

	for (i = 0; i < length(str1); i++) {

		if (str1[i] != str2[i]) {

			return 0;

		}

	}

	return 1;

}

int getRow (char a) {

	char *nums = "12345678";

	int i;
	
	for (i = 0; i < 8; i++) {

		if (a == nums[i]) {

			return i; 

		}

	}

	return -1;

} 

int getColumn (char a) {

	char *columns = "abcdefgh";

	int i;

	for (i = 0; i < 8; i++) {

		if (a == columns[i]) {

			return i;

		}

	}

	return -1;

}

int isOccupied (Square *s) {

	char o = s->occupied;

	if (o == ' ') {

		return 0;

	} else if (o == 'p' || o == 'n' || o == 'b' || o == 'r' || o == 'q' || o == 'k') {

		return 1;

	}

	return 2;

}

void setup (void) {

	int i, j;

	for (i = 0; i < 8; i++) {

		for (j = 0; j < 8; j++) {

			squares[i][j] = (Square *) (malloc(sizeof(Square)));

			squares[i][j]->row = i;

			squares[i][j]->column = j;

			squares[i][j]->occupied = ' ';

		}

	}	

	for (i = 0; i < 8; i++) {

		squares[1][i]->occupied = 'p'; 

		squares[6][i]->occupied = 'P';

	}

	squares[0][0]->occupied = 'r';

	squares[0][7]->occupied = 'r';

	squares[7][0]->occupied = 'R';

	squares[7][7]->occupied = 'R';

	squares[0][1]->occupied = 'n';

	squares[0][6]->occupied = 'n';

	squares[7][1]->occupied = 'N';

	squares[7][6]->occupied = 'N';

	squares[0][2]->occupied = 'b';

	squares[0][5]->occupied = 'b';

	squares[7][2]->occupied = 'B';

	squares[7][5]->occupied = 'B';

	squares[0][3]->occupied = 'q';

	squares[0][4]->occupied = 'k';

	squares[7][3]->occupied = 'Q';

	squares[7][4]->occupied = 'K';

	input = (char *) (malloc(10 * sizeof(char)));

	turn = 'w';

	whiteKingMoved = 0;

	blackKingMoved = 0;

	whiteKingRookMoved = 0;

	whiteQueenRookMoved = 0;

	blackKingRookMoved = 0;

	blackQueenRookMoved = 0;

}

void endGame (void) {

	int i, j;

	for (i = 0; i < 8; i++) {

		for (j = 0; j < 8; j++) {

			free(squares[i][j]);

		}

	}

	free(input);

}

/*

---------------------------------
|   |   |   |   |   |   |   |   |
---------------------------------
|   |   |   |   |   |   |   |   |
---------------------------------
|   |   |   |   |   |   |   |   |
---------------------------------
|   |   |   |   |   |   |   |   |
---------------------------------
|   |   |   |   |   |   |   |   |
---------------------------------
|   |   |   |   |   |   |   |   |
---------------------------------
|   |   |   |   |   |   |   |   |
---------------------------------
|   |   |   |   |   |   |   |   |
---------------------------------

*/

void printGame (void) {

	int i, j;

	printf("\n  ");

	for (i = 0; i < 33; i++) {

		printf("-");

	}			

	printf("\n");

	for (i = 7; i >= 0; i--) {

		printf("%d ", i + 1);
		
		for (j = 0; j < 8; j++) {
	
			printf("| %c ", squares[i][j]->occupied);

		}

		printf("|\n  ");

		for (j = 0; j < 33; j++) {

			printf("-");

		}

		printf("\n");

	}

	printf("    a   b   c   d   e   f   g   h\n\n");

}

void movePiece (Square *start, Square *end) {

	end->occupied = start->occupied;

	start->occupied = ' ';

}

/*

Function to move pawn to specified square. Returns 1 if it is successful.
Otherwise, it returns 0 to denote that either the square is occupied already or that they can't move there. Still need to implement capturing pieces and en 
passant. Also, make it so that it can't move due to being pinned.

*/

int canMovePawn (Pawn *p, Square *s, const int isCapturing) {

	if (isCapturing == 0 && isOccupied(s) != 0) {

		return 0;

	}

	if (p->color == 'w') {

		if (isCapturing == 0) {

			if (p->s->row + 1 == s->row) {

				return 1;

			} else if (p->s->row == 1 && s->row == 3) {

				if (isOccupied(squares[2][s->column]) == 0) { 

					return 1; 
	
				}

			}

		} else if (isCapturing == 1) {

			if (p->s->row + 1 == s->row && abs(p->s->column - s->column) == 1 && isOccupied(s) == 2) {

				return 1; 

			}

		}

	} else if (p->color == 'b') {

		if (isCapturing == 0) {

			if (p->s->row - 1 == s->row) {

				return 1;

			} else if (p->s->row == 6 && s->row == 4) {

				if (isOccupied(squares[5][s->column]) == 0) {

					return 1;

				}

			}
		
		} else if (isCapturing == 1) {

			if (p->s->row - 1 == s->row && abs(p->s->column - s->column) == 1 && isOccupied(s) == 1) {

				return 1; 

			}

		}



	}

	return 0;

}

int canMoveKnight (Knight *n, Square *s, const int isCapturing) {

	int r = n->s->row;

	int c = n->s->column;

	int sr = s->row;

	int sc = s->column;

	if (n->color == 'w' && isOccupied(s) == 1) {

		return 0;

	} 

	if (n->color == 'b' && isOccupied(s) == 2) {

		return 0;

	}

	if (r - sr == 2 || r - sr == -2) {

		if (c - sc == 1 || c - sc == -1) {

			return 1; 

		}

	} else if (c - sc == 2 || c - sc == -2) {

		if (r - sr == 1 || r - sr == -1) {

			return 1;

		}

	}

	return 0;

}

int canMoveBishop (Bishop *b, Square *s, const int isCapturing) {

	if (b->color == 'w' && isOccupied(s) == 1) {

		return 0;

	}

	if (b->color == 'b' && isOccupied(s) == 2) {

		return 0; 

	}

	int r = b->s->row;

	int c = b->s->column;

	int sr = s->row;

	int sc = s->column;

	if (abs(r - sr) != abs (c - sc)) {

		return 0;

	}

	int i;

	if (r > sr && c > sc) {

		for (i = 1; i < r - sr; i++) {

			if (isOccupied(squares[r - i][c - i]) != 0) {

				return 0;

			}

		}

	} else if (r > sr && c < sc) {

		for (i = 1; i < r - sr; i++) {

			if (isOccupied(squares[r - i][c + i]) != 0) {

				return 0;

			}

		}

	} else if (r < sr && c > sc) {

		for (i = 1; i < sr - r; i++) {

			if (isOccupied(squares[r + i][c - i]) != 0) {

				return 0;

			}

		}

	} else if (r < sr && c < sc) {

		for (i = 1; i < sr - r; i++) {

			if (isOccupied(squares[r + i][c + i]) != 0) {

				return 0;

			}

		}

	}

	return 1;	

}

int canMoveRook (Rook *r, Square *s, const int isCapturing) {

	if (r->color == 'w' && isOccupied(s) == 1) {

		return 0;

	}

	if (r->color == 'b' && isOccupied(s) == 2) {

		return 0; 

	}

	int i;

	int row = r->s->row;

	int col = r->s->column;
	
	int sr = s->row;

	int sc = s->column;

	if (row - sr != 0 && col - sc != 0) {

		return 0;

	}	

	if (row < sr) {

		for (i = 1; i < sr - row; i++) {
		
			if (isOccupied(squares[row + i][col]) != 0) {

				return 0;

			}

		}	

	} else if (row > sr) {

		for (i = 1; i < row - sr; i++) {
		
			if (isOccupied(squares[row - i][col]) != 0) {

				return 0;

			}

		}	


	} else if (col < sc) {

		for (i = 1; i < sc - col; i++) {
		
			if (isOccupied(squares[row][col + i]) != 0) {

				return 0;

			}

		}	

	} else if (col > sc) {

		for (i = 1; i < col - sc; i++) {
		
			if (isOccupied(squares[row][col - i]) != 0) {

				return 0;

			}

		}	

	}

	return 1;

}

int canMoveQueen (Queen *q, Square *s, const int isCapturing) {

	Bishop *b = (Bishop *) (malloc(sizeof(Bishop)));

	Rook *r = (Rook *) (malloc(sizeof(Rook)));

	b->s = q->s;

	r->s = q->s;

	b->color = q->color;

	r->color = q->color;

	int bishop = canMoveBishop(b, s, 0);

	int rook = canMoveRook(r, s, 0);

	free(b);

	free(r);

	if (bishop == 1 || rook == 1) {

		return 1;

	}

	return 0;

}

int kingInCheck (King *k) {

	if (k->color == 'w') {

		int i, j;

		for (i = 0; i < 8; i++) {

			for (j = 0; j < 8; j++) {

				if (squares[i][j]->occupied == 'P') {

					Pawn *p = (Pawn *) (malloc(sizeof(Pawn)));

					p->s = squares[i][j];

					p->color = 'b';

					if (canMovePawn(p, k->s, 1) == 1) {

						free(p);	

						return 1;

					}	

					free(p);
					
				} else if (squares[i][j]->occupied == 'N') {

					Knight *n = (Knight *) (malloc(sizeof(Knight)));

					n->s = squares[i][j];

					n->color = 'b';	

					if (canMoveKnight(n, k->s, 1) == 1) {

						free(n);

						return 1;

					}
				
					free(n);

				} else if (squares[i][j]->occupied == 'B') {

					Bishop *b = (Bishop *) (malloc(sizeof(Bishop)));

					b->s = squares[i][j];

					b->color = 'b';

					if (canMoveBishop(b, k->s, 1) == 1) {
		
						free(b);

						return 1;

					}	

					free(b);

				} else if (squares[i][j]->occupied == 'R') {

					Rook *r = (Rook *) (malloc(sizeof(Rook)));

					r->s = squares[i][j];

					r->color = 'b';

					if (canMoveRook(r, k->s, 1) == 1) {

						free(r);
	
						return 1;

					}

					free(r);

				} else if (squares[i][j]->occupied == 'Q') {

					Queen *q = (Queen *) (malloc(sizeof(Queen)));

					q->s = squares[i][j];

					q->color = 'b';

					if (canMoveQueen(q, k->s, 1) == 1) {

						free(q);

						return 1;

					}			

					free(q);

				}

			}

		}

	} else if (k->color == 'b') {

		int i, j;

		for (i = 0; i < 8; i++) {
	
			for (j = 0; j < 8; j++) {

				if (squares[i][j]->occupied == 'p') {

					Pawn *p = (Pawn *) (malloc(sizeof(Pawn)));

					p->s = squares[i][j];

					p->color = 'w';

					if (canMovePawn(p, k->s, 1) == 1) {

						free(p);	

						return 1;

					}	

					free(p);

				} else if (squares[i][j]->occupied == 'n') {

					Knight *n = (Knight *) (malloc(sizeof(Knight)));

					n->s = squares[i][j];

					n->color = 'w';	

					if (canMoveKnight(n, k->s, 1) == 1) {

						free(n);

						return 1;

					}
				
					free(n);

				} else if (squares[i][j]->occupied == 'b') {
					
					Bishop *b = (Bishop *) (malloc(sizeof(Bishop)));

					b->s = squares[i][j];

					b->color = 'w';

					if (canMoveBishop(b, k->s, 1) == 1) {
		
						free(b);

						return 1;

					}	

					free(b);

				} else if (squares[i][j]->occupied == 'r') {

					Rook *r = (Rook *) (malloc(sizeof(Rook)));

					r->s = squares[i][j];

					r->color = 'w';

					if (canMoveRook(r, k->s, 1) == 1) {

						free(r);
	
						return 1;

					}

					free(r);

				} else if (squares[i][j]->occupied == 'q') {

					Queen *q = (Queen *) (malloc(sizeof(Queen)));

					q->s = squares[i][j];

					q->color = 'w';

					if (canMoveQueen(q, k->s, 1) == 1) {

						free(q);

						return 1;

					}			

					free(q);
				}

			}

		}


	}

	return 0;

}

void getKing (King *k, const char c) {

	if (c == 'w') {

		int i, j;

		for (i = 0; i < 8; i++) {

			for (j = 0; j < 8; j++) {

				if (squares[i][j]->occupied == 'k') {

					k->s = squares[i][j];

					k->color = 'w';	

					return;

				}

			}

		}

	} else if (c == 'b') {

		int i, j;

		for (i = 0; i < 8; i++) {
		
			for (j = 0; j < 8; j++) {

				if (squares[i][j]->occupied == 'K') {
	
					k->s = squares[i][j];

					k->color = 'b'; 

					return;

				}

			}

		}

	}

}

int putsOwnKingInCheck (Square *start, Square *end) {

	King *k = (King *) (malloc(sizeof(King)));

	char color = 'w';

	if (isOccupied(start) == 2) {

		color = 'b';	

	}	

	getKing(k, color);

	char endO = end->occupied;

	end->occupied = start->occupied;

	start->occupied = ' ';

	int check = kingInCheck(k);

	start->occupied = end->occupied;

	end->occupied = endO;

	free(k);

	if (check == 1) {

		return 1;

	}

	return 0;

}

int canMoveKing (King *k, Square *s) {

	if (k->color == 'w' && isOccupied(s) == 1) {

		return 0;

	}	

	if (k->color == 'b' && isOccupied(s) == 2) {

		return 0;

	}

	int r = k->s->row;

	int c = k->s->column;

	int sr = s->row;

	int sc = s->column;

	if (abs(r - sr) > 1 || abs(c - sc) > 1) {

		return 0;

	}
	
	King *kOpp = (King *) (malloc(sizeof(King)));

	if (k->color == 'w') {

		getKing(kOpp, 'b');

	} else {

		getKing(kOpp, 'w');

	}		

	if (abs(sr - kOpp->s->row) < 2 && abs(sc - kOpp->s->column) < 2) {

		free(kOpp);

		return 0;	

	}

	free(kOpp);

	King *k2 = (King *)(malloc(sizeof(King)));

	k2->s = s;

	k2->color = k->color;

	char destO = s->occupied;

	k2->s->occupied = k->s->occupied;

	k->s->occupied = ' ';

	int check = kingInCheck(k2);

	k->s->occupied = k2->s->occupied;

	k2->s->occupied = destO;	

	free(k2);

	if (check == 1) {

		return 0;

	}

	return 1;

}

void getMove (void) {

	if (turn == 'w') {

		printf("White to move: ");

	} else if (turn == 'b') {

		printf("Black to move: ");

	}

	scanf("%s", input);

}

int makeMove (char color) {

	/* Check for if it is a pawn move */
	
	if (getColumn(input[0]) != -1) {

		int isCapturing = 0;

		Square *dest;

		if (indexOf(input, 'x') == 1) {

			isCapturing = 1;

			dest = squares[getRow(input[3])][getColumn(input[2])];

		} else if (indexOf(input, 'x') != -1) {

			return 0;

		} else {

			dest = squares[getRow(input[1])][getColumn(input[0])];

		}

		int pawnRow = -1;

		char id = 'p';

		if (color == 'b') {

			id = 'P';

		}

		int i = 0;

		int moveSuccessful = 0;

		while (i < 8 && moveSuccessful == 0) {

			for (; i < 8; i++) {

				if (squares[i][getColumn(input[0])]->occupied == id) {

					pawnRow = i;

					i++;

					break;

				}

			}	

			if (pawnRow == -1) {

				return 0;

			}

			Pawn *p = (Pawn *) (malloc(sizeof(Pawn)));

			p->s = squares[pawnRow][getColumn(input[0])];

			p->color = color; 

			moveSuccessful = canMovePawn(p, dest, isCapturing);			
			if (moveSuccessful == 1) {

				if (putsOwnKingInCheck(p->s, dest) == 0) {

					movePiece(p->s, dest);		

				} else {

					moveSuccessful = 0;

				}

			}

			free(p);

		}

		return moveSuccessful;

	} else if (input[0] == 'N') {

		int i, j, nColumn, nRow, moveSuccessful = 0;

		Knight *n = (Knight *) (malloc(sizeof(Knight)));

		char id = 'n';

		if (color == 'b') {

			id = 'N';

		}
	
		for (i = 0; i < 8; i++) {

			for (j = 0; j < 8; j++) {

				if (squares[i][j]->occupied == id) {

					nColumn = j;

					nRow = i;
	
					goto foundKnight;
	
				}

			}

		}	

		foundKnight:

		n->s = squares[nRow][nColumn];

		n->color = color;

		Square *dest = squares[getRow(input[2])][getColumn(input[1])];

		moveSuccessful = canMoveKnight(n, dest, 0);

		if (moveSuccessful == 0 && i < 8) {

			for (; i < 8; i++) {

				if (j == 8) {

					j = -1;

				}

				for (j++; j < 8; j++) {


					if (squares[i][j]->occupied == id) {

						nColumn = j;

						nRow = i;

						goto foundKnight;
					
					}

				}

			}	

		}

		if (moveSuccessful == 1) {
	
			if (putsOwnKingInCheck(n->s, dest) == 0) {

				movePiece(n->s, dest);		

			} else {

				moveSuccessful = 0;

			}

		}

		free(n);

		return moveSuccessful;

	} else if (input[0] == 'B') {

		int i, j, bRow, bColumn, moveSuccessful = 0;

		Bishop *b = (Bishop *) (malloc(sizeof(Bishop)));	 

		char id = 'b';

		if (color == 'b') {

			id = 'B';

		}

		for (i = 0; i < 8; i++) {

			for (j = 0; j < 8; j++) {

				if (squares[i][j]->occupied == id) {

					bRow = i;

					bColumn = j;

					goto foundBishop;

				}

			}

		}

		foundBishop:

		b->s = squares[bRow][bColumn];

		b->color = color;

		Square *dest = squares[getRow(input[2])][getColumn(input[1])];
	
		moveSuccessful = canMoveBishop(b, dest, 0);

		if (moveSuccessful == 0 && i < 8) {

			for (; i < 8; i++) {

				if (j == 8) {

					j = -1;

				}

				for (j++; j < 8; j++) {


					if (squares[i][j]->occupied == id) {

						bRow = i;

						bColumn = j;

						goto foundBishop;

					}

				}

			}	

		}

		if(moveSuccessful == 1) {

			if (putsOwnKingInCheck(b->s, dest) == 0) {

				movePiece(b->s, dest);		

			} else {

				moveSuccessful = 0;

			}

		}

		free(b);

		return moveSuccessful;

	} else if (input[0] == 'R') {

		int i, j, rRow, rColumn, moveSuccessful = 0;

		Rook *r = (Rook *) (malloc(sizeof(Rook)));	 

		char id = 'r';

		if (color == 'b') {

			id = 'R';

		}

		for (i = 0; i < 8; i++) {

			for (j = 0; j < 8; j++) {

				if (squares[i][j]->occupied == id) {

					rRow = i;

					rColumn = j;

					goto foundRook;

				}

			}

		}

		foundRook:

		r->s = squares[rRow][rColumn];

		r->color = color;

		Square *dest = squares[getRow(input[2])][getColumn(input[1])];
	
		moveSuccessful = canMoveRook(r, dest, 0);

		if (moveSuccessful == 0 && i < 8) {

			for (; i < 8; i++) {

				if (j == 8) {

					j = -1;

				}

				for (j++; j < 8; j++) {


					if (squares[i][j]->occupied == id) {

						rRow = i;

						rColumn = j;

						goto foundRook;

					}

				}

			}	

		}

		if(moveSuccessful == 1) {

			if (putsOwnKingInCheck(r->s, dest) == 0) {

				if (r->s == squares[0][0] && whiteQueenRookMoved == 0) {

					whiteQueenRookMoved = 1;	

				} else if (r->s == squares[0][7] && whiteKingRookMoved == 0) {
	
					whiteKingRookMoved = 1;

				} else if (r->s == squares[7][0] && blackQueenRookMoved == 0) {

					blackQueenRookMoved = 1; 

				} else if (r->s == squares[7][7] && blackKingRookMoved == 0) {

					blackKingRookMoved = 1;

				}

				movePiece(r->s, dest);		

			} else {

				moveSuccessful = 0;

			}

		}

		free(r);

		return moveSuccessful;

	} else if (input[0] == 'Q') {

		int i, j, qRow, qColumn, moveSuccessful = 0;

		Queen *q = (Queen *) (malloc(sizeof(Queen)));	 

		char id = 'q';

		if (color == 'b') {

			id = 'Q';

		}

		for (i = 0; i < 8; i++) {

			for (j = 0; j < 8; j++) {

				if (squares[i][j]->occupied == id) {

					qRow = i;

					qColumn = j;

					goto foundQueen;

				}

			}

		}

		foundQueen:

		q->s = squares[qRow][qColumn];

		q->color = color;

		Square *dest = squares[getRow(input[2])][getColumn(input[1])];
	
		moveSuccessful = canMoveQueen(q, dest, 0);

		if (moveSuccessful == 0 && i < 8) {

			for (; i < 8; i++) {

				if (j == 8) {

					j = -1;

				}

				for (j++; j < 8; j++) {


					if (squares[i][j]->occupied == id) {

						qRow = i;

						qColumn = j;

						goto foundQueen;

					}

				}

			}	

		}

		if(moveSuccessful == 1) {

			if (putsOwnKingInCheck(q->s, dest) == 0) {

				movePiece(q->s, dest);		

			} else {

				moveSuccessful = 0;

			}

		}

		free(q);

		return moveSuccessful;

	} else if (input[0] == 'K') {

		King *k = (King *) (malloc(sizeof(King)));

		getKing(k, color);

		Square *dest = squares[getRow(input[2])][getColumn(input[1])];

		int canMove = canMoveKing(k, dest); 

		if (canMove ==  1) {

			movePiece(k->s, dest);	

			if (color == 'w' && whiteKingMoved == 0) {

				whiteKingMoved++;	

			}

			if (color == 'b' && blackKingMoved == 0) {

				blackKingMoved++;

			}

		}

		free(k);

		return canMove;

	} else if (strEquals(input, "O-O")) {

		if (color == 'w') {

			if (whiteKingMoved == 0 && whiteKingRookMoved == 0) {
	
				King *k = (King *) (malloc(sizeof(King)));

				getKing(k, color);

				int moveSuccessful = 1;

				if (isOccupied(squares[0][5]) != 0 || isOccupied(squares[0][6]) != 0) {

					moveSuccessful = 0;

				} else if (kingInCheck(k) == 1) {

					moveSuccessful = 0;	

				} else if (putsOwnKingInCheck(k->s, squares[0][5]) == 1) {

					moveSuccessful = 0;
	
				} else if (putsOwnKingInCheck(k->s, squares[0][6]) == 1) {

					moveSuccessful = 0;	

				}

				if (moveSuccessful == 1) {

					movePiece(k->s, squares[0][6]);

					movePiece(squares[0][7], squares[0][5]);

				}

				free(k);

				return moveSuccessful;

			}

		} else if (color == 'b') {

			if (blackKingMoved == 0 && blackKingRookMoved == 0) {
	
				King *k = (King *) (malloc(sizeof(King)));

				getKing(k, color);

				int moveSuccessful = 1;

				if (isOccupied(squares[7][5]) != 0 || isOccupied(squares[7][6]) != 0) {

					moveSuccessful = 0;

				} else if (kingInCheck(k) == 1) {

					moveSuccessful = 0;	

				} else if (putsOwnKingInCheck(k->s, squares[7][5]) == 1) {

					moveSuccessful = 0;	

				} else if (putsOwnKingInCheck(k->s, squares[7][6]) == 1) {

					moveSuccessful = 0;

				}

				if (moveSuccessful == 1) {

					movePiece(k->s, squares[7][6]);

					movePiece(squares[7][7], squares[7][5]);

				}

				free(k);

				return moveSuccessful;

			}

		}


	}

	return 0;

}

void startGame (void) {

	setup();

	while (strEquals(input, "quit") != 1) {

		getMove();

		while (strEquals(input, "quit") != 1 && makeMove(turn) == 0) {

			printf("That was an illegal move. Please try again.\n\n");
		
			getMove();

		}

		if (turn == 'w') {

			turn = 'b';

		} else if (turn == 'b') {

			turn = 'w';

		}	

		printGame();

	}

	endGame();

}

int main (void) {

	startGame();

	return 0;

}
