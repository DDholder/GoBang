#include "computer.h"


Computer::Computer(ChessBoard *chessboard)
{
	board = chessboard;
	createTree();
	setScore();
	srand(static_cast<int>(time(nullptr)));
}

void Computer::setBoard(ChessBoard *chessboard)
{
	board = chessboard;
	createTree();
}

bool Computer::findTwo(int x, int y, Dir dir, Chess::color kind)
{
	for (size_t i = 0; i < 8; i++)
	{
		switch (Dir(i))
		{
		case Computer::up:if (dir != down && dir != up && board->map[x][y - 1] == kind && board->map[x][y - 2] == kind && board->map[x][y - 3] == Chess::null)return true;
			break;
		case Computer::down:if (dir != up && dir != down && board->map[x][y + 1] == kind && board->map[x][y + 2] == kind && board->map[x][y + 3] == Chess::null)return true;
			break;
		case Computer::left:if (dir != left && dir != right && board->map[x - 1][y] == kind && board->map[x - 2][y] == kind && board->map[x - 3][y] == Chess::null)return true;
			break;
		case Computer::right:if (dir != right && dir != left && board->map[x + 1][y] == kind && board->map[x + 2][y] == kind && board->map[x + 3][y] == Chess::null)return true;
			break;
		case Computer::up_left:if (dir != up_left && dir != down_right && board->map[x - 1][y - 1] == kind && board->map[x - 2][y - 2] == kind && board->map[x - 3][y - 3] == Chess::null)return true;
			break;
		case Computer::up_right:if (dir != up_right && dir != down_left && board->map[x + 1][y - 1] == kind && board->map[x + 2][y - 2] == kind && board->map[x + 3][y - 3] == Chess::null)return true;
			break;
		case Computer::down_left:if (dir != down_left && dir != up_right && board->map[x - 1][y + 1] == kind && board->map[x - 2][y + 2] == kind && board->map[x - 3][y + 3] == Chess::null)return true;
			break;
		case Computer::down_right:if (dir != down_right && dir != up_left && board->map[x + 1][y + 1] == kind && board->map[x + 2][y + 2] == kind && board->map[x + 3][y + 3] == Chess::null)return true;
			break;
		default:
			break;
		}
	}
	return false;
}





Computer::ChessAlignment Computer::checkChessAlignment(int x, int y, Dir dir, Chess::color kind)
{
	QVector<Chess> chesses = kind == Chess::white ? QVector<Chess>(board->WhiteChesses) : QVector<Chess>(board->BlackChesses);
	const int length = chesses.length();
	if (length < 1)return next;
	const ChessAlignment result = checkChessAlignmentAt(x, y, tree, dir, kind);
	bool bOneSide = false;
	if (x + 1 > 20)bOneSide = true;
	if (result == three || result == four || result == oneside_four || result == two)
	{
		switch (dir)
		{
		case up:if (board->map[x][y + 1] != kind && board->map[x][y + 1] != Chess::null)bOneSide = true;
			break;
		case down:if (board->map[x][y - 1] != kind && board->map[x][y - 1] != Chess::null)bOneSide = true;
			break;
		case left:if (board->map[x + 1][y] != kind && board->map[x + 1][y] != Chess::null)bOneSide = true;
			break;
		case right:if (board->map[x - 1][y] != kind && board->map[x - 1][y] != Chess::null)bOneSide = true;
			break;
		case up_left:if (board->map[x + 1][y + 1] != kind && board->map[x + 1][y + 1] != Chess::null)bOneSide = true;
			break;
		case up_right:if (board->map[x - 1][y + 1] != kind && board->map[x - 1][y + 1] != Chess::null)bOneSide = true;
			break;
		case down_left:if (board->map[x + 1][y - 1] != kind && board->map[x + 1][y - 1] != Chess::null)bOneSide = true;
			break;
		case down_right:if (board->map[x - 1][y - 1] != kind && board->map[x - 1][y - 1] != Chess::null)bOneSide = true;
			break;
		default:
			break;
		}
	}
	if (bOneSide)
	{
		if (result == three)
			return oneside_three;
		if (result == four)
			return oneside_four;
		if (result == two)
			return oneside_two;
		return one;
	}
	if (result == two)
	{
		int nullx = x, nully = y;
		switch (dir)
		{
		case Computer::up:nully -= 2;
			break;
		case Computer::down:nully += 2;
			break;
		case Computer::left:nullx -= 2;
			break;
		case Computer::right:nullx += 2;
			break;
		case Computer::up_left:nullx -= 2; nully -= 2;
			break;
		case Computer::up_right:nullx += 2; nully -= 2;
			break;
		case Computer::down_left:nullx -= 2; nully += 2;
			break;
		case Computer::down_right:nullx += 2; nully += 2;
			break;
		default:
			break;
		}
		if (findTwo(nullx, nully, dir, kind))
		{
			return double_two;
		}
	}
	return result;
}

Computer::ChessAlignment Computer::checkChessAlignmentAt(const int x, const int y, BiTNode<ChessAlignment> *node, Dir dir, Chess::color kind) const
{
	int nextx = x, nexty = y;
	switch (dir)
	{
	case up: nexty--;
		break;
	case down: nexty++;
		break;
	case left:nextx--;
		break;
	case right:nextx++;
		break;
	case up_left: nexty--; nextx--;
		break;
	case up_right: nexty--; nextx++;
		break;
	case down_left:nexty++; nextx--;
		break;
	case down_right:nexty++; nextx++;
		break;
	default:
		break;
	}
	if (node->data != next)return node->data;
	BiTNode<ChessAlignment> *nextnode;
	Chess::color nextcolor;
	if (nexty < 0 || nexty>20 || nextx < 0 || nextx>20)
		nextcolor = Chess::line;
	else
		nextcolor = board->map[nextx][nexty];
	if (kind == Chess::white)
	{
		switch (nextcolor)
		{
		case Chess::black:nextnode = node->mchild;
			break;
		case Chess::white:nextnode = node->rchild;
			break;
		case Chess::null:nextnode = node->lchild;
			break;
		case Chess::line:nextnode = node->mchild;
			break;
		default:nextnode = node->mchild;
			break;
		}
	}
	else
	{
		switch (nextcolor)
		{
		case Chess::white:nextnode = node->mchild;
			break;
		case Chess::black:nextnode = node->rchild;
			break;
		case Chess::null:nextnode = node->lchild;
			break;
		case Chess::line:nextnode = node->mchild;
			break;
		default:nextnode = node->mchild;
			break;
		}
	}
	return	checkChessAlignmentAt(nextx, nexty, nextnode, dir, kind);
}

int Computer::getScore(Chess::color kind)
{
	QVector<Chess> chesses = kind == Chess::white ? QVector<Chess>(board->WhiteChesses) : QVector<Chess>(board->BlackChesses);
	int* scoresum_me = new int[9];
	int max_me = 0;
	if (chesses.length() == 0)return 0;
	for (const auto chesse : chesses)
	{
		scoresum_me[8] = 0;
		const int x = chesse.x;
		const int y = chesse.y;
		for (auto i = 0; i < 8; i++)
		{
			scoresum_me[i] = score[checkChessAlignment(x, y, Dir(i), kind)];
			scoresum_me[8] += scoresum_me[i];
		}
		if (scoresum_me[8] > max_me)
		{
			max_me = scoresum_me[8];
		}
	}
	return max_me;
}

QVector<QVector<int>> Computer::getIndex(const QVector<int*>& scoresumList, QVector<int> maxAt, int max)
{
	QVector<QVector<int>>index;
	for (int maxPos : maxAt)
	{
		QVector<int>tempIndex;
		for (auto i = 0; i < 8; i++)
		{
			if (scoresumList.length() <= 0)break;

			if (max == scoresumList.at(maxPos)[i])
				tempIndex.append(i);
		}
		index.append(tempIndex);
	}
	return index;
}

void Computer::getList(QVector<Chess>& chesses, QVector<int*>& scoresumList, QVector<int>& maxWhiteAt, int & max)
{
	for (int chessIndex = 0; chessIndex < chesses.length(); chessIndex++)
	{
		int* scoresum = new int[10];
		scoresum[8] = 0;
		scoresum[9] = 0;
		int maxLine = 0;
		for (auto lineIndex = 0; lineIndex < 8; lineIndex++)
		{
			const int x = chesses.at(chessIndex).x;
			const int y = chesses.at(chessIndex).y;
			scoresum[lineIndex] = score[checkChessAlignment(x, y, Dir(lineIndex), chesses[0].kind)];
			if (scoresum[lineIndex] > maxLine)
			{
				maxLine = scoresum[lineIndex];
				scoresum[9] = lineIndex;
			}
			scoresum[8] += scoresum[lineIndex];
		}
		if (scoresum[scoresum[9]] > max)
		{
			maxWhiteAt.clear();
		}
		if (scoresum[scoresum[9]] >= max)
		{
			maxWhiteAt.append(chessIndex);
			max = scoresum[scoresum[9]];
		}
		scoresumList.append(scoresum);
	}
}



Chess Computer::findPos(QVector<Chess>& chesses, QVector<QVector<int>> index, QVector<int> maxAt, Chess::color kind)
{
	Chess value;
	int nextMax = 0, nextIndex = -1;
	QVector<Chess> valueGroup;
	const Chess::color opositeKind = kind == Chess::white ? Chess::black : Chess::white;
	for (int chessIndex = 0; chessIndex < maxAt.length(); chessIndex++)
	{
		const int atx = chesses.at(maxAt[chessIndex]).x;
		const int aty = chesses.at(maxAt[chessIndex]).y;
		for (int lineIndex = 0; lineIndex < index[chessIndex].length(); lineIndex++)
		{
			value = getNextStep(atx, aty, Dir(index[chessIndex][lineIndex]), kind);
			valueGroup.append(value);
			if (value.x != -1)
			{
				//尝试对手选择做出最大收益落子
				value.kind = opositeKind;
				board->addChess(value);
				const int tempMax = getScore(opositeKind);
				board->removeLast(opositeKind);
				value.kind = kind;
				if (tempMax >= nextMax)
				{
					nextMax = tempMax;
					nextIndex = valueGroup.length() - 1;
				}
				if (chessIndex == maxAt.length() - 1)
					return valueGroup.at(nextIndex);
				continue;
			}
			if (chessIndex == maxAt.length() - 1 && nextIndex != -1)
				return valueGroup.at(nextIndex);
			//搜索完未找到最佳落子
			if (index[chessIndex].length() == 1 && chessIndex == maxAt.length() - 1)
				for (int i = 0; i < 7; i++)
				{
					value = getNextStep(atx, aty, Dir(i), kind);
					if (value.x != -1 && value.y != -1)
						return value;
				}
			//搜索完未找到最佳落子			
			//return getNextStep(atx, aty, Dir(index[chessIndex][lineIndex]) != 7 ? Dir(Dir(index[chessIndex][lineIndex] + 1)) : Dir(0), kind);
			if (lineIndex == index[chessIndex].length() - 1 && lineIndex > 0)
			{
				for (auto lineSelect = 0; lineSelect < 8; lineSelect++)
				{
					for (const auto WhiteChesse : chesses)
					{
						value = getNextStep(WhiteChesse.x, WhiteChesse.y, Dir(lineSelect), kind);
						if (value.x != -1)return value;
					}
				}
			}
		}
	}
	return value;
}

int * Computer::get_Area()
{
	int* area=new int[4];
	int maxx = 0, maxy = 0, minx = 24, miny = 24;
	for (auto& BlackChesse : board->BlackChesses)
	{
		if (BlackChesse.x > maxx)maxx = BlackChesse.x;
		if (BlackChesse.x < minx)minx = BlackChesse.x;
		if (BlackChesse.y > maxy)maxy = BlackChesse.y;
		if (BlackChesse.y < miny)miny = BlackChesse.y;
	}
	for(auto& WhiteChesses:board->WhiteChesses)
	{
		if (WhiteChesses.x > maxx)maxx = WhiteChesses.x;
		if (WhiteChesses.x < minx)minx = WhiteChesses.x;
		if (WhiteChesses.y > maxy)maxy = WhiteChesses.y;
		if (WhiteChesses.y < miny)miny = WhiteChesses.y;
	}
	area[0] = minx-2; area[1] = miny-2; area[2] = maxx+2; area[3] = maxy+2;
	return area;
}
Chess Computer::get_Best_Poses(QVector<Chess>& chesses,Chess::color kind, int&max)
{
	Chess value;
	QVector<Chess> values;
	const Chess::color local_kind = chesses[0].kind;
	value.kind = local_kind;
	int maxSingleLine = 0;
	int* area = get_Area();
	for (int x = 0; x < 25; x++)
	{
		for (int y = 0; y < 25; y++)
		{
			if (x<area[0] || y<area[1] || x>area[2] || y>area[3])
				continue;
			if (board->map[x][y] != Chess::null)
				continue;
			board->addChess({ x,y,local_kind });
			for (int chessIndex = 0; chessIndex < chesses.length(); chessIndex++)
			{
				auto* scoresum = new int[10];
				scoresum[8] = 0;
				scoresum[9] = 0;
				int maxLine = 0;
				for (auto lineIndex = 0; lineIndex < 8; lineIndex++)
				{
					const int tx = chesses.at(chessIndex).x;
					const int ty = chesses.at(chessIndex).y;
					scoresum[lineIndex] = score[checkChessAlignment(tx, ty, Dir(lineIndex), local_kind)];
					if (scoresum[lineIndex] > maxLine)
					{
						maxLine = scoresum[lineIndex];
						scoresum[9] = lineIndex;
					}
					scoresum[8] += scoresum[lineIndex];
				}
				if (scoresum[scoresum[9]] > maxSingleLine)
				{
					maxSingleLine = scoresum[scoresum[9]];
					values.clear();
					max = 0;
				}
				if (scoresum[scoresum[9]] == maxSingleLine)
				{
					if (scoresum[8] > max)
					{
						max = scoresum[8];
						values.clear();
					}
					if (scoresum[8] == max)
					{
						value.x = x; value.y = y;
						values.append(value);
					}
				}
				delete[] scoresum;
			}
			board->removeLast(local_kind);
		}
	}
	delete area;
	return get_Final_Pos(values,kind);
}
Chess Computer::get_Final_Pos(QVector<Chess>& values, Chess::color kind)
{
	int compare_num = values[0].kind == kind?10000:0;
	Chess value;
	for (int i = 0; i < values.length(); i++)
	{
		
		if(values[i].kind==kind)
		{
			board->addChess(values[i]);
			int score = getScore(OPOSITE_KIND(kind));
			if(score < compare_num)
			{
				compare_num = score;
				value = values[i];
			}
			board->removeLast(values[i].kind);
		}
		else
		{
			values[i].kind = kind;
			board->addChess(values[i]);
			int score = getScore(kind);
			if (score > compare_num)
			{
				compare_num = score;
				value = values[i];
			}
			board->removeLast(values[i].kind);
		}
		
	}
	return value;
}
#ifdef VIOLENCE
Chess Computer::getNextChess(Chess::color kind)
{
	const int MeLength = kind == Chess::black ? board->BlackChesses.length() : board->WhiteChesses.length();
	const int YouLength = kind == Chess::black ? board->WhiteChesses.length() : board->BlackChesses.length();
	//################空棋盘第一子处理###################//
	if (MeLength == 0)
	{
		Chess value;
		if (YouLength != 0)
		{
			int randx = random(2) - 1;
			int randy = random(2) - 1;
			while (randx == 0 && randy == 0)
			{
				randx = random(2) - 1;
				randy = random(2) - 1;
			}
			value.x = kind == Chess::black ? board->WhiteChesses.at(YouLength - 1).x + randx : board->BlackChesses.at(YouLength - 1).x + randx;
			value.y = kind == Chess::black ? board->WhiteChesses.at(YouLength - 1).y + randy : board->BlackChesses.at(YouLength - 1).y + randy;

		}
		else
		{
			value.x = 12;
			value.y = 12;
		}
		value.kind = kind;
		return value;
	}
	Chess temp;

	temp.kind = kind;
	int max_Kind = 0;
	int max_OffKind = 0;
	QVector<Chess> ChessMe = kind == Chess::black ? board->BlackChesses : board->WhiteChesses;
	QVector<Chess> ChessYou = kind == Chess::black ? board->WhiteChesses : board->BlackChesses;
	Chess value_Kind = get_Best_Poses(ChessMe,kind, max_Kind);
	Chess value_OppKind = get_Best_Poses(ChessYou,kind, max_OffKind);
	/*for (int x = 0; x < 25; x++)
	{
		for (int y = 0; y < 25; y++)
		{
			if (board->map[x][y] != Chess::null)
				continue;
			temp.x = x; temp.y = y;
			board->addChess(temp);
			int score = getScore(kind);
			if (score > max_Kind)
			{
				max_Kind = score;
				value_Kind.x = temp.x;
				value_Kind.y = temp.y;
			}
			board->removeLast(kind);
		}
	}
	temp.kind = OPOSITE_KIND(kind);
	for (int x = 0; x < 25; x++)
	{
		for (int y = 0; y < 25; y++)
		{
			if (board->map[x][y] != Chess::null)
				continue;
			temp.x = x; temp.y = y;
			board->addChess(temp);
			int score = getScore(OPOSITE_KIND(kind));
			if (score > max_OffKind)
			{
				max_OffKind = score;
				value_OppKind.x = temp.x;
				value_OppKind.y = temp.y;
			}
			board->removeLast(OPOSITE_KIND(kind));
		}
	}*/
	value_Kind.kind = kind; value_OppKind.kind = kind;
	return ((max_Kind >= max_OffKind-500)|| max_Kind>=3000)&&max_OffKind<5000 ? value_Kind : value_OppKind;
	//return { random(12),random(12),kind };
	return value_Kind ;
}

#else
Chess Computer::getNextChess(Chess::color kind)
{
	QVector<int*> scoresumList_White;//白子得分列表 L[n][8]:第n个子的全方向和,L[n][9]:第n个子的最佳方向分数
	QVector<int*> scoresumList_Black;//黑子得分列表 L[n][8]:第n个子的全方向和,L[n][9]:第n个子的最佳方向分数
	QVector<int>maxWhiteAt;//最佳白子的索引
	QVector<int> maxBlackAt;//最佳黑子的索引
	int max_white = 0;//白子最大单方向分数
	int max_black = 0;//黑子最大单方向分数
	if (board->WhiteChesses.length() > 0)
		getList(board->WhiteChesses, scoresumList_White, maxWhiteAt, max_white);
	if (board->BlackChesses.length() > 0)
		getList(board->BlackChesses, scoresumList_Black, maxBlackAt, max_black);
	const QVector<QVector<int>>index_black = getIndex(scoresumList_Black, maxBlackAt, max_black);//黑子最佳方向列表
	const QVector<QVector<int>> index_white = getIndex(scoresumList_White, maxWhiteAt, max_white);//白子最佳方向列表

	int MeLength = kind == Chess::black ? board->BlackChesses.length() : board->WhiteChesses.length();
	int YouLength = kind == Chess::black ? board->WhiteChesses.length() : board->BlackChesses.length();
	//################空棋盘第一子处理###################//
	if (MeLength == 0)
	{
		Chess value;
		if (YouLength != 0)
		{
			int randx = random(2) - 1;
			int randy = random(2) - 1;
			while (randx == 0 && randy == 0)
			{
				randx = random(2) - 1;
				randy = random(2) - 1;
			}
			value.x = kind == Chess::black ? board->WhiteChesses.at(YouLength - 1).x + randx : board->BlackChesses.at(YouLength - 1).x + randx;
			value.y = kind == Chess::black ? board->WhiteChesses.at(YouLength - 1).y + randy : board->BlackChesses.at(YouLength - 1).y + randy;

		}
		else
		{
			value.x = 12;
			value.y = 12;
		}
		value.kind = kind;
		return value;
	}

	//const int wMax = scoresumList_White.at(maxWhiteAt[0])[8];//白子最高得分
	//const int bMax = scoresumList_Black.at(maxBlackAt[0])[8];//黑子最高得分
	const int max_me = kind == Chess::black ? max_black : max_white;
	const int max_you = kind == Chess::black ? max_white : max_black;
	QVector<Chess> ChessMe = kind == Chess::black ? board->BlackChesses : board->WhiteChesses;
	QVector<Chess> ChessYou = kind == Chess::black ? board->WhiteChesses : board->BlackChesses;
	QVector<QVector<int>> index_me = kind == Chess::black ? index_black : index_white;
	QVector<QVector<int>> index_you = kind == Chess::black ? index_white : index_black;
	QVector<int> maxMeAt = kind == Chess::black ? maxBlackAt : maxWhiteAt;
	QVector<int> maxYouAt = kind == Chess::black ? maxWhiteAt : maxBlackAt;
	Chess value;
	if (max_you > max_me && max_me < 2000)
		value = findPos(ChessYou, index_you, maxYouAt, kind);
	else
		value = findPos(ChessMe, index_me, maxMeAt, kind);
	return value;
}
#endif // VIOLENCE
Chess Computer::getNextStep(int x, int y, Dir dir, Chess::color kind) const
{
	QVector<Chess> chesses = kind == Chess::white ? QVector<Chess>(board->WhiteChesses) : QVector<Chess>(board->BlackChesses);
	const int tx = x;
	const int ty = y;
	for (auto stepCount = 0; stepCount < 4; stepCount++)
	{
		switch (dir)
		{
		case up:
			if (board->map[x][y - 1] == Chess::null)
				return { x, y - 1 ,kind };
			if (board->map[x][y - 1] == kind)
				y--;
			else if (board->map[x][y + 1] == Chess::null)
				return getNextStep(x, y, down, kind);

			break;
		case down:
			if (board->map[x][y + 1] == Chess::null)
				return { x, y + 1 ,kind };
			if (board->map[x][y + 1] == kind)
				y++;
			else if (board->map[x][y - 1] == Chess::null)
				return getNextStep(x, y, up, kind);

			break;
		case right:
			if (board->map[x + 1][y] == Chess::null)
				return { x + 1, y ,kind };
			if (board->map[x + 1][y] == kind)
				x++;
			else if (board->map[x - 1][y] == Chess::null)
				return getNextStep(x, y, left, kind);

			break;
		case left:
			if (board->map[x - 1][y] == Chess::null)
				return { x - 1, y ,kind };
			if (board->map[x - 1][y] == kind)
				x--;
			else if (board->map[x + 1][y] == Chess::null)
				return getNextStep(x, y, right, kind);

			break;
		case up_left:
			if (board->map[x - 1][y - 1] == Chess::null)
				return { x - 1, y - 1 ,kind };
			if (board->map[x - 1][y - 1] == kind)
			{
				y--; x--;
			}
			else if (board->map[x + 1][y + 1] == Chess::null)
				return getNextStep(x, y, down_right, kind);

			break;
		case up_right:
			if (board->map[x + 1][y - 1] == Chess::null)
				return { x + 1, y - 1 ,kind };
			if (board->map[x + 1][y - 1] == kind)
			{
				y--; x++;
			}
			else if (board->map[x - 1][y + 1] == Chess::null)
				return getNextStep(x, y, down_left, kind);

			break;
		case down_left:
			if (board->map[x - 1][y + 1] == Chess::null)
				return { x - 1, y + 1 ,kind };
			if (board->map[x - 1][y + 1] == kind)
			{
				y++; x--;
			}
			else if (board->map[x + 1][y - 1] == Chess::null)
				return getNextStep(x, y, up_right, kind);

			break;
		case down_right:
			if (board->map[x + 1][y + 1] == Chess::null)
				return { x + 1, y + 1 ,kind };
			if (board->map[x + 1][y + 1] == kind)
			{
				y++; x++;
			}
			else if (board->map[x - 1][y - 1] == Chess::null)
				return getNextStep(x, y, up_left, kind);

			break;
		default:
			break;
		}
	}
	if (tx == x && ty == y)
		return { -1,-1 ,kind };
	return getNextStep(x, y, dir, kind);
}

void Computer::createTree() const
{
#define LEFT BiTNode<ChessAlignment>::left
#define RIGHT BiTNode<ChessAlignment>::right
#define MID BiTNode<ChessAlignment>::mid
#define R tree->root
#define C Computer
	R->data = C::next;
	R->CreateBiTNode(next, LEFT);
	R->lchild->CreateBiTNode(C::one, LEFT);
	R->lchild->CreateBiTNode(C::one, MID);
	R->lchild->CreateBiTNode(C::next, RIGHT);
	R->lchild->rchild->CreateBiTNode(C::one, LEFT);
	R->lchild->rchild->CreateBiTNode(C::one, MID);
	R->lchild->rchild->CreateBiTNode(C::next, RIGHT);
	R->lchild->rchild->rchild->CreateBiTNode(C::one_skip_two, LEFT);
	R->lchild->rchild->rchild->CreateBiTNode(C::one, MID);
	R->lchild->rchild->rchild->CreateBiTNode(C::three_skip_one, RIGHT);
	R->CreateBiTNode(C::one, MID);
	R->CreateBiTNode(C::next, RIGHT);
	R->rchild->CreateBiTNode(C::next, LEFT);
	R->rchild->lchild->CreateBiTNode(C::two, LEFT);
	R->rchild->lchild->CreateBiTNode(C::two, MID);
	R->rchild->lchild->CreateBiTNode(C::next, RIGHT);
	R->rchild->lchild->rchild->CreateBiTNode(C::one_skip_two, LEFT);
	R->rchild->lchild->rchild->CreateBiTNode(C::two, MID);
	R->rchild->lchild->rchild->CreateBiTNode(C::two_skip_two, RIGHT);
	R->rchild->CreateBiTNode(C::oneside_two, MID);
	R->rchild->CreateBiTNode(C::next, RIGHT);
	R->rchild->rchild->CreateBiTNode(C::next, LEFT);
	R->rchild->rchild->lchild->CreateBiTNode(C::three, LEFT);
	R->rchild->rchild->lchild->CreateBiTNode(C::oneside_three, MID);
	R->rchild->rchild->lchild->CreateBiTNode(C::three_skip_one, RIGHT);
	R->rchild->rchild->CreateBiTNode(C::oneside_three, MID);
	R->rchild->rchild->CreateBiTNode(C::next, RIGHT);
	R->rchild->rchild->rchild->CreateBiTNode(C::four, LEFT);
	R->rchild->rchild->rchild->CreateBiTNode(C::oneside_four, MID);
	R->rchild->rchild->rchild->CreateBiTNode(C::five, RIGHT);
}

void Computer::setScore()
{
	score[one] = 1;
	score[two] = 100;
	score[double_two] = 500;
	score[two_skip_two] = 2000;
	score[three] = 1700;
	score[double_three] = 3500;
	score[oneside_three] = 1000;
	score[double_oneside_three] = 2;
	score[three_skip_one] = 2500;
	score[four] = 3500;
	score[oneside_four] = 3000;
	score[double_oneside_four] = 2;
	score[next] = 0;
	score[one_skip_two] = 1100;
	score[oneside_two] = 10;
	score[five] = 10000;
}

