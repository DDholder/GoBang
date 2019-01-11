#ifndef MYPAINTER_H
#define MYPAINTER_H
#include <QMainWindow>
#include<QPainter>
#include"chess.h"
#include <QMouseEvent>
#include"chessboard.h"
#include"rule.h"
class myPainter : public QWidget
{
    Q_OBJECT
public:
    explicit myPainter(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void setChessBorad(ChessBoard *chessboard=new ChessBoard);
	void setChessBorad(ChessBoard chessboard);
	Rule::CheckResult winner = Rule::CheckResult::no_win;
signals:
	void clicked();
public slots:
private:
    int offset=25;
    QVector<Chess> chesses;
    ChessBoard *board;
};

#endif // MYPAINTER_H
