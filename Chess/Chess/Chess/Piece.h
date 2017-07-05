#pragma once
#include<string>

using namespace std;


class Piece
{
public:
	Piece(string, int);	//type constructor

	Piece(void);
	~Piece(void);
	string name;
	int player;
private:
	

	
};

/**
Same as with Square.h, you don't to define destructors if they do nothing

--------

If you're going to categorise pieces using a name, use enums, strings take more processor
time to handle, especially with lots of string::compare calls

Something like: enum PieceName{ Pawn, King, ... etc };
enum just replace with an integer which means comparisons are cheap, it also gives compiler errors
if you mispell a pieces name where using string names wont
you could do the same with 'player', it'll remove the chance of erroneous comparisons

	// Header
		Piece( PieceName pn, PlayerSomething ps )

Also the constuctor with no arguments should still initialise the variables, otherwise doing comparisons
will give undefined behaviour

--------

Same as with Square.h, dont leave member variables public

**/
