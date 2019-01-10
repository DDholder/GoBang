#include "chessboard.h"

ChessBoard::ChessBoard()
{
	for (auto& i : map)
	{
		for (auto& j : i)
		{
			j =Chess::color::null;
		}
	}
}

void ChessBoard::addChess(Chess chess)
{
	if(chess.kind==chess.color::black)
	{
		BlackChesses.append(chess);
		map[chess.x][chess.y]=chess.color::black;
	}
	if(chess.kind==chess.color::white)
	{
		WhiteChesses.append(chess);
		map[chess.x][chess.y]=chess.color::white;
	}
}

void ChessBoard::reset()
{
	BlackChesses.clear();
	WhiteChesses.clear();
	for (auto& i : map)
	{
		for (auto& j : i)
		{
			j = Chess::color::null;
		}
	}
}

void ChessBoard::removeLast(Chess::color kind)
{
	if (kind == Chess::color::black)
	{

		map[BlackChesses[BlackChesses.length() - 1].x][BlackChesses[BlackChesses.length() - 1].y] = Chess::null;
		BlackChesses.removeLast();
	}
	if (kind == Chess::color::white)
	{
		map[WhiteChesses[WhiteChesses.length() - 1].x][WhiteChesses[WhiteChesses.length() - 1].y] = Chess::null;
		WhiteChesses.removeLast();
	}
}
