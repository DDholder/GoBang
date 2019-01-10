#include "chess.h"

Chess::Chess()
{
	x = 0;
	y = 0;
	kind = black;
}

Chess::Chess(int posx, int posy, color thiskind)
{
	x = posx;
	y = posy;
	kind = thiskind;
}
