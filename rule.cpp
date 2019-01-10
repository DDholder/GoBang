#include "rule.h"

Rule::Rule()
{
	board = new ChessBoard;
}

void Rule::set_board(ChessBoard *chessboard)
{
	board = chessboard;
}

Rule::CheckResult Rule::judge() const
{
	if (judge_next(Chess::black, down) || judge_next(Chess::black, right) || judge_next(Chess::black, up_right) || judge_next(Chess::black, down_right))
		return black_win;
	if (judge_next(Chess::white, down) || judge_next(Chess::white, right) || judge_next(Chess::white, up_right) || judge_next(Chess::white, down_right))
		return white_win;
	return no_win;
}

bool Rule::judge_next(const Chess::color color, const JudgeDir dir) const
{
	QVector<Chess> chesses = color == Chess::black ? QVector<Chess>(board->BlackChesses) : QVector<Chess>(board->WhiteChesses);
	for (int i = 0; i < chesses.length(); i++)
	{
		if (judge_step(color, dir, i))return true;
	}
	return false;
}

bool Rule::judge_step(const Chess::color color, const JudgeDir dir, const int at, int num) const
{
	QVector<Chess> chesses = color == Chess::black ? QVector<Chess>(board->BlackChesses) : QVector<Chess>(board->WhiteChesses);
	int x = chesses[at].x;
	int y = chesses[at].y;
	const int length = chesses.length();
	for (int i = 0; i < length; i++)
	{
		Chess::color next_color;
		{
			switch (dir)
			{
			case Rule::down:y++;
				break;
			case Rule::right:x++;
				break;
			case Rule::up_right:x++; y--;
				break;
			case Rule::down_right:x++; y++;
				break;
			default:
				break;
			}
			next_color = board->map[x][y];
		}
		if (next_color == color)
		{
			int j;
			for (j = 0; j < length; j++)
				if (chesses[j].x == x && chesses[j].y == y)
					break;
			if (++num >= 4)
				return true;
			if (judge_step(color, dir, j, num))
				return true;
		}
		else
			return false;
	}
	return false;
}
