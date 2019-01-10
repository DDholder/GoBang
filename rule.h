#ifndef RULE_H
#define RULE_H

#include"chessboard.h"
class Rule
{

public:
	enum CheckResult
	{
		no_win = 0,
		black_win = 1,
		white_win = 2
	};
	Rule();
	void set_board(ChessBoard *chessboard = new ChessBoard);
	CheckResult judge() const;
private:
	enum JudgeDir
	{
		down = 0,
		right = 1,
		up_right = 2,
		down_right = 3
	};
	ChessBoard *board;
	bool judge_next(Chess::color color, JudgeDir dir) const;
	bool judge_step(Chess::color color, JudgeDir dir, int at = 0, int num = 0) const;
};

#endif // RULE_H
