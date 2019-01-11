#ifndef CHESS_H
#define CHESS_H


class Chess
{

public:
	enum color
	{
		black = 2,
		white = 1,
		null=0,
		line=4
	};
	Chess();
	int x,y;
	color kind;
	Chess(int posx, int posy, color thiskind = black);
};

#endif // CHESS_H
