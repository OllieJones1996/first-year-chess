#include <iostream>
#include <sstream>
#include <ctype.h>
#include <cmath>
#include <Windows.h>
#include "Piece.h"
#include "Square.h"

using namespace std;

void playGame();
bool validateMoveFormat(string);
bool validateMoveRules(string, Piece* [8][8], int);
void Display(Piece* [8][8]);

int main() 
{
	playGame();
}

void playGame()
{
///////////////////////////////	

//array declaration of pointer piece
	Piece* board[8][8];

//setting all the pointers to null

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[i][j] = nullptr;
		}
	}

//placing the pieces on the board
	board[0][0] = new Piece ("Rook", 1);
	board[0][1] = new Piece ("Knight", 1);
	board[0][2] = new Piece ("Bishop", 1);
	board[0][3] = new Piece ("Queen", 1);
	board[0][4] = new Piece ("King", 1);
	board[0][5] = new Piece ("Bishop", 1);
	board[0][6] = new Piece ("Knight", 1);
	board[0][7] = new Piece ("Rook", 1);

	board[1][0] = new Piece ("Pawn", 1);
	board[1][1] = new Piece ("Pawn", 1);
	board[1][2] = new Piece ("Pawn", 1);
	board[1][3] = new Piece ("Pawn", 1);
	board[1][4] = new Piece ("Pawn", 1);
	board[1][5] = new Piece ("Pawn", 1);
	board[1][6] = new Piece ("Pawn", 1);
	board[1][7] = new Piece ("Pawn", 1);

	//player2's pieces...
	board[7][0] = new Piece ("Rook", 2);
	board[7][1] = new Piece ("Knight", 2);
	board[7][2] = new Piece ("Bishop", 2);
	board[7][3] = new Piece ("Queen", 2);
	board[7][4] = new Piece ("King", 2);
	board[7][5] = new Piece ("Bishop", 2);
	board[7][6] = new Piece ("Knight", 2);
	board[7][7] = new Piece ("Rook", 2);

	board[6][0] = new Piece ("Pawn", 2);
	board[6][1] = new Piece ("Pawn", 2);
	board[6][2] = new Piece ("Pawn", 2);
	board[6][3] = new Piece ("Pawn", 2);
	board[6][4] = new Piece ("Pawn", 2);
	board[6][5] = new Piece ("Pawn", 2);
	board[6][6] = new Piece ("Pawn", 2);
	board[6][7] = new Piece ("Pawn", 2);



	int currentPlayer = 2;	//starts on p2 so start on p1 when switched

	int p1Pieces = 16;	//When count is 0 game is over
	int p2Pieces = 16;

	string move;	

	

	//Game loop
	while (true) 
	{
		//after a move swap the active player
		if (currentPlayer == 1)
			currentPlayer = 2;
		else
			currentPlayer = 1;

		system("cls");

		Display(board);
		cout << "P" << currentPlayer << " please enter your move: ";
		getline(cin, move);

		while (!validateMoveFormat(move)) 
		{
			cout << "Invalid move. Please re-enter." << endl;
			getline(cin, move);
		}

		while (!validateMoveRules(move, board, currentPlayer)) 
		{
			cout << "Please re-enter your move." << endl;
			getline(cin, move);
		}
	}

	delete[] board;
}

//this function makes sure that the user has entered a potentially correct move based on formatting alone
bool validateMoveFormat(string move) 
{
	//a valid move has 8 characters
	if (move.length() != 8) 
	{
		return false;
	}

	//these checks check to see if the user has input within a valid range
	if (!(move[0] >= int('a') && move[0] <= int('h'))) 
	{
		return false;
	}

	//make sure the number of the board index is valid ***********
	if (move[1] != '0' && move[1] != '1' && move[1] != '2' && move[1] != '3' && move[1] != '4' && move[1] != '5' && move[1] != '6' && move[1] != '7')
	{
		return false;
	}
	
	if (move[3] != 't' || move[4] != 'o')
	//if (move.substr(2, 3).compare("to") != 0)
	{
		return false;
	}

	//valid range of letters for destination index
	if (!(move[6] >= int('a') && move[6] <= int('h')))
	{
		return false;
	}

	//valid range of numbers for destination index
	if (move[7] != '0' && move[7] != '1' && move[7] != '2' && move[7] != '3' && move[7] != '4' && move[7] != '5' && move[7] != '6' && move[7] != '7')
	{
		return false;
	}

	else return true;
}

//this function performs all chess rules validation of the previously correctly-formatted move
bool validateMoveRules(string move, Piece* board[8][8], int currentPlayer) 
{
	stringstream stream;
	int l1;	
	int n1;

	stream << move[1];
	stream >> n1;
	stream.clear();	

	int l2;
	int n2;
	stream << move[7];
	stream >> n2;

	//stattements change input into usable index
	if (move[0] == 'a')
		l1 = 0;
	else if (move[0] == 'b')
		l1 = 1;
	else if (move[0] == 'c')
		l1 = 2;
	else if (move[0] == 'd')
		l1 = 3;
	else if (move[0] == 'e')
		l1 = 4;
	else if (move[0] == 'f')
		l1 = 5;
	else if (move[0] == 'g')
		l1 = 6;
	else
		l1 = 7;


	if (move[6] == 'a')
		l2 = 0;
	else if (move[6] == 'b')
		l2 = 1;
	else if (move[6] == 'c')
		l2 = 2;
	else if (move[6] == 'd')
		l2 = 3;
	else if (move[6] == 'e')
		l2 = 4;
	else if (move[6] == 'f')
		l2 = 5;
	else if (move[6] == 'g')
		l2 = 6;
	else
		l2 = 7;
	

	if (board[n1][l1] == nullptr) 
	{
		cout << "There's no piece at the specified location." << endl << endl;
		return false;
	}

	//checks if the piece belongs to the player (if player ID matches with ID on piece)
	if (board[n1][l1] != nullptr && currentPlayer != board[n1][l1]->player) 
	{
		cout << "That's the opponants piece." << endl << endl;
		return false;
	}

	//checks to see if the player already has a piece of their own in the position
	if (board[n2][l2] != nullptr && currentPlayer == board[n2][l2]->player) 
	{
		cout << "You already have a piece there." << endl << endl;
		return false;
	}

	//shows the difference in row and cols
	int rowDiff = n1 - n2;
	int colDiff = l1 - l2;

	//player 1 pawn movement rules
	if (board[n1][l1]->name.compare("Pawn") == 0 && currentPlayer == 1) 
	{
		//if first move of the pawn then it can move 2 spaces, however if after first move then it cannot
		if (n1 != 1 && rowDiff <= -2) 
		{
			cout << "Pawns can't move like that." << endl << endl;
			return false;
		}
		//if the user tries to move a pawn more than 2 spaces on first movement
		else if (n1 == 1 && rowDiff < -2) 
		{
			cout << "Pawns may move 2 spaces forward their first move." << endl << endl;
			return false;
		}
		//rowDiff has be negative as there is no backwards or sideways movement for a pawn
		else if (rowDiff >= 0) 
		{
			cout << "Pawns can't move like that." << endl << endl;
			return false;
		}
		//even when taking another piece a pawn can only move a maximum of 1 col
		else if (abs(colDiff) > 1)
		{		
			cout << "Pawns can't move like that." << endl << endl;
			return false;
		}
		//the is if the user tries to move the pawn diagonally when not taking an opposing piece
		else if (abs(colDiff) == 1 && rowDiff == -1 && board[n2][l2] == nullptr) 
		{
			cout << "There must be an enemy piece at " << l2 << n2 << " for you to move there." << endl << endl;
			return false;
		}
		//check for moving forward but a cloision happens
		else if (rowDiff == -1 && colDiff == 0 && board[n2][l2] != nullptr && board[n2][l2]->player == 2) 
		{
			cout << "An enemy piece is blocking your move!" << endl << endl;
			return false;
		}
		//if they try to move diagonally to a space and there's an enemy piece there...
		else if (rowDiff == -1 && abs(colDiff) == 1 && board[n2][l2]->player == 2) 
		{
			cout << "You have taken the enemy's " << board[n2][l2]->name << "!" << endl << endl;
			board[n2][l2] = board[n1][l1];	//piece taken
			board[n1][l1] = nullptr;
			Sleep(2000);
			return true;
		}
		//valid movement
		else 
		{
			cout << "Move successful!" << endl << endl;
			board[n2][l2] = board[n1][l1];
			board[n1][l1] = nullptr;
			Sleep(2000);
			return true;
		}
	}
	//Player 2 pawn movement
	else if (board[n1][l1]->name.compare("Pawn") == 0 && currentPlayer == 2) 
	{
		if (n1 != 6 && rowDiff >= 2) 
		{
			cout << "Pawns can't move like that." << endl << endl;
			return false;
		}
		else if (n1 == 6 && rowDiff > 2) 
		{
			cout << "Pawns may move 2 spaces forward their first move." << endl << endl;
			return false;
		}
		else if (rowDiff <= 0) 
		{
			cout << "Pawns can't move like that." << endl << endl;
			return false;
		}
		else if (abs(colDiff) > 1) 
		{
			cout << "Pawns can't move like that." << endl << endl;
			return false;
		}
		else if (abs(colDiff) == 1 && rowDiff == 1 && board[n2][l2] == nullptr) 
		{
			cout << "There must be an enemy piece at " << l2 << n2 << " for you to move there." << endl << endl;
			return false;
		}
		else if (rowDiff == 1 && colDiff == 0 && board[n2][l2] != nullptr && board[n2][l2]->player == 1) 
		{
			cout << "An enemy piece is blocking your move!" << endl << endl;
			return false;
		}
		else if (rowDiff == 1 && abs(colDiff) == 1 && board[n2][l2]->player == 1) 
		{
			cout << "You have taken the enemy's " << board[n2][l2]->name << "!" << endl << endl;
			board[n2][l2] = board[n1][l1];
			board[n1][l1] = nullptr;
			Sleep(2000);
			return true;
		}
		else 
		{
			cout << "Move successful!" << endl << endl;
			board[n2][l2] = board[n1][l1];
			board[n1][l1] = nullptr;
			Sleep(2000);
			return true;
		}
	}
	else if (board[n1][l1]->name.compare("King") == 0) //king movement checking
	{
		//king can only move 1 space at a time
		if (abs(rowDiff) > 1 || abs(colDiff) > 1) {
			cout << "Kings may only move one space at a time." << endl << endl;
			return false;
		}
		if (board[n2][l2] != nullptr && board[n2][l2]->player != currentPlayer) 
		{
			cout << "You have taken the enemy's " << board[n2][l2]->name << "!" << endl << endl;
			board[n2][l2] = board[n1][l1];	//piece taken
			board[n1][l1] = nullptr;
			Sleep(2000);
			return true;
		}
		else 
		{
			cout << "Move successful!" << endl << endl;
			board[n2][l2] = board[n1][l1];
			board[n1][l1] = nullptr;
			Sleep(2000);
			return true;
		}
	}


	else if (board[n1][l1]->name.compare("Queen") == 0) //queen movement checking
	{
		//statement is used to see whether piece is being moved to a random place
		if (abs(rowDiff) != abs(colDiff) && rowDiff != 0 && colDiff != 0) 
		{
			cout << "Queens are able to move straight or diagonally only." << endl << endl;
			return false;
		}
		//checks for collisions between moving pieces
		if (rowDiff > 0 && colDiff > 0) 
		{
			for (int i = n1 - 1; i > n2; i--) 
			{
				for (int j = l1 - 1; j > l2; j--) 
				{
					if (board[i][j] != nullptr) 
					{
						cout << "There's a piece blocking your move!" << endl << endl;
						return false;
					}
				}
			}
		}
		else if (rowDiff < 0 && colDiff < 0) 
		{
			for (int i = n1 + 1; i < n2; i++) 
			{
				for (int j = l1 + 1; j < l2; j++) 
				{
					if (board[i][j] != nullptr) 
					{
						cout << "There's a piece blocking your move!" << endl << endl;
						return false;
					}
				}
			}
		}
		else if (rowDiff > 0 && colDiff < 0) 
		{
			for (int i = n1 - 1; i > n2; i--) 
			{
				for (int j = l1 + 1; j < l2; j++) 
				{
					if (board[i][j] != nullptr) 
					{
						cout << "There's a piece blocking your move!" << endl << endl;
						return false;
					}
				}
			}
		}
		else if (rowDiff < 0 && colDiff > 0) 
		{
			for (int i = n1 + 1; i < n2; i++) 
			{
				for (int j = l1 - 1; j > l2; j--) 
				{
					if (board[i][j] != nullptr) 
					{
						cout << "There's a piece blocking your move!" << endl << endl;
						return false;
					}
				}
			}
		}
		else if (rowDiff == 0 && colDiff > 0) 
		{
			for (int i = l1 - 1; i > l2; i--) 
			{
				if (board[n1][i] != nullptr) 
				{
					cout << "There's a piece blocking your move!" << endl << endl;
					return false;
				}
			}
		}
		else if (rowDiff == 0 && colDiff < 0) 
		{
			for (int i = l1 + 1; i < l2; i++) 
			{
				if (board[n1][i] != nullptr) 
				{
					cout << "There's a piece blocking your move!" << endl << endl;
					return false;
				}
			}
		}
		else if (rowDiff > 0 && colDiff == 0) 
		{
			for (int i = n1 - 1; i > n2; i--) 
			{
				if (board[i][l1] != nullptr) 
				{
					cout << "There's a piece blocking your move!" << endl << endl;
					return false;
				}
			}
		}
		else if (rowDiff < 0 && colDiff == 0) 
		{
			for (int i = n1 + 1; i < n2; i++) 
			{
				if (board[i][l1] != nullptr) 
				{
					cout << "There's a piece blocking your move!" << endl << endl;
					return false;
				}
			}
		}
		if (board[n2][l2] != nullptr && board[n2][l2]->player != currentPlayer) 
		{
			cout << "You have taken the enemy's " << board[n2][l2]->name << "!" << endl << endl;
			board[n2][l2] = board[n1][l1];	//piece taken
			board[n1][l1] = nullptr;
			Sleep(2000);
			return true;
		}
		else 
		{
			cout << "Move successful!" << endl << endl;
			board[n2][l2] = board[n1][l1];
			board[n1][l1] = nullptr;
			Sleep(2000);
			return true;
		}
	}
	else if (board[n1][l1]->name.compare("Knight") == 0) //knight movement checking
	{
		if (abs(rowDiff)*abs(colDiff) != 2) 
		{
			cout << "Knights can't move like that." << endl << endl;
			return false;
		}
		if (board[n2][l2] != nullptr && board[n2][l2]->player != currentPlayer)
		{
			cout << "You have taken the enemy's " << board[n2][l2]->name << "!" << endl << endl;
			board[n2][l2] = board[n1][l1];	//piece taken
			board[n1][l1] = nullptr;
			Sleep(2000);
			return true;
		}
	
		else 
		{
			cout << "Move successful!" << endl << endl;
			board[n2][l2] = board[n1][l1];
			board[n1][l1] = nullptr;
			Sleep(2000);
			return true;
		}
	}
	else if (board[n1][l1]->name.compare("Bishop") == 0) //bishop movement check
	{
		//specifies bishops can only move diagonally
		if (abs(rowDiff) != abs(colDiff)) 
		{
			cout << "Bishops can't move like that." << endl;
			return false;
		}
		//checks for colisions between pieces
		if (rowDiff > 0 && colDiff > 0) 
		{
			for (int i = n1 - 1; i > n2; i--) 
			{
				for (int j = l1 - 1; j > l2; j--) 
				{
					if (board[i][j] != nullptr) 
					{
						cout << "There's a piece blocking your move!" << endl << endl;
						return false;
					}
				}
			}
		}
		else if (rowDiff < 0 && colDiff < 0) 
		{
			for (int i = n1 + 1; i < n2; i++) 
			{
				for (int j = l1 + 1; j < l2; j++) 
				{
					if (board[i][j] != nullptr) 
					{
						cout << "There's a piece blocking your move!" << endl << endl;
						return false;
					}
				}
			}
		}
		else if (rowDiff > 0 && colDiff < 0) 
		{
			for (int i = n1 - 1; i > n2; i--) 
			{
				for (int j = l1 + 1; j < l2; j++) 
				{
					if (board[i][j] != nullptr) 
					{
						cout << "There's a piece blocking your move!" << endl << endl;
						return false;
					}
				}
			}
		}
		else if (rowDiff < 0 && colDiff > 0) 
		{
			for (int i = n1 + 1; i < n2; i++) 
			{
				for (int j = l1 - 1; j > l2; j--) 
				{
					if (board[i][j] != nullptr) 
					{
						cout << "There's a piece blocking your move!" << endl << endl;
						return false;
					}
				}
			}
		}
		//standard piece taking code for player 1
		if (board[n2][l2] != nullptr && board[n2][l2]->player != currentPlayer) 
		{
			cout << "You have taken the enemy's " << board[n2][l2]->name << "!" << endl << endl;
			board[n2][l2] = board[n1][l1];	//piece taken
			board[n1][l1] = nullptr;
			Sleep(2000);
			return true;
		}
		else 
		{
			cout << "Move successful!" << endl << endl;
			board[n2][l2] = board[n1][l1];
			board[n1][l1] = nullptr;
			Sleep(2000);
			return true;
		}
	}
	else if (board[n1][l1]->name.compare("Rook") == 0) //rook movement checks
	{
		if (rowDiff != 0 && colDiff != 0) 
		{
			cout << "Rooks can't move like that." << endl << endl;
			return false;
		}
		//these statements check piece collision
		if (rowDiff == 0 && colDiff > 0) 
		{
			for (int i = l1 - 1; i > l2; i--) 
			{
				if (board[n1][i] != nullptr) 
				{
					cout << "There's a piece blocking your move!" << endl << endl;
					return false;
				}
			}
		}
		else if (rowDiff == 0 && colDiff < 0) 
		{
			for (int i = l1 + 1; i < l2; i++) 
			{
				if (board[n1][i] != nullptr) 
				{
					cout << "There's a piece blocking your move!" << endl << endl;
					return false;
				}
			}
		}
		else if (rowDiff > 0 && colDiff == 0) 
		{
			for (int i = n1 - 1; i > n2; i--) 
			{
				if (board[i][l1] != nullptr) 
				{
					cout << "There's a piece blocking your move!" << endl << endl;
					return false;
				}
			}
		}
		else if (rowDiff < 0 && colDiff == 0) 
		{
			for (int i = n1 + 1; i < n2; i++) 
			{
				if (board[i][l1] != nullptr) 
				{
					cout << "There's a piece blocking your move!" << endl << endl;
					return false;
				}
			}
		}
		if (board[n2][l2] != nullptr && board[n2][l2]->player != currentPlayer) 
		{
			cout << "You have taken the enemy's " << board[n2][l2]->name << "!" << endl << endl;
			board[n2][l2] = board[n1][l1];	//piece taken
			board[n1][l1] = nullptr;
			Sleep(2000);
			return true;
		}
		else 
		{
			cout << "Move successful!" << endl << endl;
			board[n2][l2] = board[n1][l1];
			board[n1][l1] = nullptr;

			Sleep(2000);

			return true;
		}
	}
	else return false;
}


void Display(Piece* board[8][8]) 
{
	char displayBoard[38][53] = 
	{

		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'a', ' ', ' ', ' ', ' ', ' ', 'b', ' ', ' ', ' ', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', 'd', ' ', ' ', ' ', ' ', ' ', 'e', ' ', ' ', ' ', ' ', ' ', 'f', ' ', ' ', ' ', ' ', ' ', 'g', ' ', ' ', ' ', ' ', ' ', 'h', ' ', ' ', ' ' },
		{ ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
		{ ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
		{ ' ', ' ', '7', ' ', '#', ' ', ' ', 'r', ' ', ' ', '#', ' ', ' ', 'n', ' ', ' ', '#', ' ', ' ', 'b', ' ', ' ', '#', ' ', ' ', 'q', ' ', ' ', '#', ' ', ' ', 'k', ' ', ' ', '#', ' ', ' ', 'b', ' ', ' ', '#', ' ', ' ', 'n', ' ', ' ', '#', ' ', ' ', 'r', ' ', ' ', '#' },
		{ ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
		{ ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
		{ ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
		{ ' ', ' ', '6', ' ', '#', ' ', ' ', 'p', ' ', ' ', '#', ' ', ' ', 'p', ' ', ' ', '#', ' ', ' ', 'p', ' ', ' ', '#', ' ', ' ', 'p', ' ', ' ', '#', ' ', ' ', 'p', ' ', ' ', '#', ' ', ' ', 'p', ' ', ' ', '#', ' ', ' ', 'p', ' ', ' ', '#', ' ', ' ', 'p', ' ', ' ', '#' },
		{ ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
		{ ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
		{ ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
		{ ' ', ' ', '5', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
		{ ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
		{ ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
		{ ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
		{ ' ', ' ', '4', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
		{ ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
		{ ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
		{ ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
		{ ' ', ' ', '3', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
		{ ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
		{ ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
		{ ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
		{ ' ', ' ', '2', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
		{ ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
		{ ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
		{ ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
		{ ' ', ' ', '1', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#' },
		{ ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
		{ ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
		{ ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
		{ ' ', ' ', '0', ' ', '#', ' ', ' ', 'R', ' ', ' ', '#', ' ', ' ', 'N', ' ', ' ', '#', ' ', ' ', 'B', ' ', ' ', '#', ' ', ' ', 'Q', ' ', ' ', '#', ' ', ' ', 'K', ' ', ' ', '#', ' ', ' ', 'B', ' ', ' ', '#', ' ', ' ', 'N', ' ', ' ', '#', ' ', ' ', 'R', ' ', ' ', '#' },
		{ ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
		{ ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },


	};

	//"displayRow"
	int dR0 = 31;
	int dR1 = 27;
	int dR2 = 23;
	int dR3 = 19;
	int dR4 = 15;
	int dR5 = 11;
	int dR6 = 7;
	int dR7 = 3;

	//"displayColumn"
	int dC0 = 7;
	int dC1 = 13;
	int dC2 = 19;
	int dC3 = 25;
	int dC4 = 31;
	int dC5 = 37;
	int dC6 = 43;
	int dC7 = 49;

	int tempRow = 0;
	int tempColumn = 0;

	//updates real piece locations on the display board
	for (int i = 0; i < 8; i++) 
	{
		if (i == 0)
			tempRow = dR0;
		else if (i == 1)
			tempRow = dR1;
		else if (i == 2)
			tempRow = dR2;
		else if (i == 3)
			tempRow = dR3;
		else if (i == 4)
			tempRow = dR4;
		else if (i == 5)
			tempRow = dR5;
		else if (i == 6)
			tempRow = dR6;
		else
			tempRow = dR7;

		for (int j = 0; j < 8; j++) 
		{

			if (j == 0)
				tempColumn = dC0;
			else if (j == 1)
				tempColumn = dC1;
			else if (j == 2)
				tempColumn = dC2;
			else if (j == 3)
				tempColumn = dC3;
			else if (j == 4)
				tempColumn = dC4;
			else if (j == 5)
				tempColumn = dC5;
			else if (j == 6)
				tempColumn = dC6;
			else
				tempColumn = dC7;

			//update display board to what the state of the actual board is

			Piece* temp = board[i][j];

			if (board[i][j] == nullptr)
				displayBoard[tempRow][tempColumn] = ' ';

			else if ((board[i][j]->name.compare("Pawn") == 0))
				displayBoard[tempRow][tempColumn] = 'P';

			else if (board[i][j]->name.compare("King") == 0)
				displayBoard[tempRow][tempColumn] = 'K';

			else if (board[i][j]->name.compare("Queen") == 0)
				displayBoard[tempRow][tempColumn] = 'Q';

			else if (board[i][j]->name.compare("Bishop") == 0)
				displayBoard[tempRow][tempColumn] = 'B';

			else if (board[i][j]->name.compare("Knight") == 0)
				displayBoard[tempRow][tempColumn] = 'N';

			else
				displayBoard[tempRow][tempColumn] = 'R';
		}
	}

	for (int i = 0; i < 34; i++) 
	{
		cout << endl;
		for (int j = 0; j < 53; j++) 
		{
			cout << displayBoard[i][j];
		}
	}
	cout << endl << endl;
}
