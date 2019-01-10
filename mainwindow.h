#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"chessboard.h"
#include"computer.h"
#include "rule.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	ChessBoard *board=new ChessBoard;
	Computer com_b;
	Computer com_w;
	Rule rule;
private slots:
	 void on_pushButton_clicked();
	void BoardBeChicked() ;
private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
