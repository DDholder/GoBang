#include "mypainter.h"

myPainter::myPainter(QWidget *parent) : QWidget(parent)
{
	board = new ChessBoard;
}

void myPainter::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	Q_UNUSED(event);
	for (int i = 0; i < 21; i++)
	{
		painter.drawLine(QPointF(offset + 0, offset + i * 25), QPointF(offset + 500, offset + i * 25));
		painter.drawLine(QPointF(offset + i * 25, offset + 0), QPointF(offset + i * 25, offset + 500));
	}
	for (const auto black_chesse : board->BlackChesses)
	{
		painter.setBrush(QBrush(QColor("black")));
		painter.drawEllipse(QPoint((black_chesse.x + 1) * 25, (black_chesse.y + 1) * 25), 12, 12);
	}
	for (const auto white_chesse : board->WhiteChesses)
	{
		painter.setBrush(QBrush(QColor("white")));
		painter.drawEllipse(QPoint((white_chesse.x + 1) * 25, (white_chesse.y + 1) * 25), 12, 12);
	}
	if (winner == Rule::black_win)
	{
		painter.setPen(QColor("red"));
		painter.setFont(QFont("Microsoft YaHei", 20, QFont::Normal));
		painter.drawText(100, 100, "Black Win!");
	}
	if (winner == Rule::white_win)
	{
		painter.setPen(QColor("red"));
		painter.setFont(QFont("Microsoft YaHei", 20, QFont::Normal));
		painter.drawText(100, 100, "White Win!");
	}
}

void myPainter::mousePressEvent(QMouseEvent *event)
{
	const int x = (event->x() - 12) / 25;
	const int y = (event->y() - 12) / 25;
	if (x < 0 || x>20 || y < 0 || y>20)return;
	if (board->map[x][y] != Chess::null)return;
	Chess item;
	item.x = x;
	item.y = y;
	item.kind = event->button() == Qt::LeftButton ? Chess::black : Chess::white;
	board->addChess(item);
	this->update();
	emit clicked();
}

void myPainter::setChessBorad(ChessBoard *chessboard)
{
	board = chessboard;
}

void myPainter::setChessBorad(ChessBoard chessboard)
{
	board = &chessboard;
}
