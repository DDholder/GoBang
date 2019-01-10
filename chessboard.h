#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QMainWindow>
#include <chess.h>
class ChessBoard
{
public:
	ChessBoard();
	QVector<Chess> BlackChesses;
	QVector<Chess> WhiteChesses;
	Chess::color map[21][21];
	void addChess(Chess chess);
	void reset();
	void removeLast(Chess::color kind=Chess::black);
};

#endif // CHESSBOARD_H
