#ifndef COMPUTER_H
#define COMPUTER_H
#include <QMouseEvent>
#include"chessboard.h"
#include"BinaryTree.h"
#include"chess.h"
#include <ctime>
#define OPOSITE(dir) dir==Chess::black?Chess::white:dir==Chess::white?Chess::black:dir==Chess::null?Chess::line:Chess::null
template<typename T>
constexpr auto OPOSITE_KIND(T kind) { return kind==Chess::black?Chess::white:Chess::black; }
#define random(x) (rand()%(x+1))
#define VIOLENCE
class Computer
{
public:
	enum ChessAlignment
	{
		one,                       // 0
		two,                       // 1
		double_two,                // 2
		two_skip_two,              // 3
		three,                     // 4
		double_three,              // 5
		oneside_three,             // 6
		double_oneside_three,      // 7
		three_skip_one,            // 8
		four,                      // 9
		oneside_four,              // 10
		double_oneside_four,       // 11
		next,                      // 12
		one_skip_two,			   // 13
		oneside_two,
		five

	};
	enum Dir
	{
		up,							// 1					
		down,						// 2
		left,						// 3
		right,						// 4
		up_left,					// 5
		up_right,					// 6
		down_left,					// 7
		down_right					// 8
	};
	Computer(ChessBoard *chessboard = new ChessBoard);
	ChessBoard *board;
	void setBoard(ChessBoard *chessboard);
	//获取棋子排列种类
	ChessAlignment checkChessAlignment(int x, int y, Dir dir, Chess::color kind) ;
	BiTNode<ChessAlignment> *tree = new BiTNode<ChessAlignment>;

	//获取全局最佳分数
	int getScore(Chess::color kind) ;

	//获取下一步落子位置
	Chess getNextChess(Chess::color kind);

private:
	//递归获取下一节点棋子种类
	ChessAlignment checkChessAlignmentAt(int x, int y, BiTNode<ChessAlignment>* node, Dir dir, Chess::color kind) const;
	void createTree() const;
	int score[20]{ 0,0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 };
	void setScore();

	//获取指定位置指定方位的落子位置
	Chess getNextStep(int x, int y, Dir dir, Chess::color kind) const;

	//获取最佳得分方向
	static QVector<QVector<int>> getIndex(const QVector<int*> &scoresumList, QVector<int> maxAt, int max);

	//获取得分列表、最佳棋子位置、最佳分数
	void getList(QVector<Chess> &chesses, QVector<int*> &scoresumList, QVector<int> &maxWhiteAt, int &max);

	Chess get_Best_Poses(QVector<Chess>& chesses, Chess::color kind, int&max);

	Chess get_Final_Pos(QVector<Chess>&values, Chess::color kind);
	//寻找最佳落子位置
	Chess findPos(QVector<Chess>& chesses, QVector<QVector<int>> index, QVector<int> maxAt, Chess::color kind) ;

	bool findTwo(int x, int y, Dir dir, Chess::color kind);

	void get_max_line(QVector<Chess>& max_chesses,Chess::color kind);
};

#endif // COMPUTER_H
