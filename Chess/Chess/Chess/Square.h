#pragma once
#include "Piece.h"

class Square
{
public:
	
	Square(Piece *);

	Square(void);
	~Square(void);
	Piece *piece;	//pointer to square, if no piece then it's null
};

/**
You can streamline your constructors by using default arguments
ie,

	// Header
		Square( Piece* p = nullptr );

	// Source
		Square::Square( Peice* p ) {
			piece = p;
		}

This means you only need one constructor instead, as if they give no arugment it defaults to nullptr

--------

Generally, member variables should not be available to change externally,
access should be given via member functions like

	// Header
		public:
			Piece* getPeice();
			void setPiece( Piece* p );

		...

		private:
			Piece* piece;

Classes exist to encapsulate data, so public members should be constants or functions

--------

If you aren't using the destructor for anything, you dont need to include it in your header,
it's defined implicitly as doing nothing already

--------

I dont know if you're going to expand this class with more functionality, but a class with one variable
and only getters/setters doesnt need to be a class
**/



