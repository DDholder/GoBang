#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->widget->setChessBorad(board);
	com_b.setBoard(board);
	com_w.setBoard(board);
	MainWindow::connect(ui->widget, &myPainter::clicked, this, &MainWindow::BoardBeChicked);

	ui->label->setText(QString::number(OPOSITE(Chess::line)));
	rule.set_board(board);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::BoardBeChicked()
{
	ui->label->setText(QString::number(com_b.getScore(Chess::black)));
	ui->widget->winner = rule.judge();
	if (ui->checkBox->isChecked())
		board->addChess(com_b.getNextChess(Chess::black));
	if (ui->widget->winner == Rule::no_win)
		ui->widget->winner = rule.judge();
	ui->widget->update();
}

void MainWindow::on_pushButton_clicked()
{
	static bool bBlack = true;
	if (bBlack)
		board->addChess(com_b.getNextChess(Chess::black));
	else
		board->addChess(com_w.getNextChess(Chess::white));
	bBlack = !bBlack;
	ui->widget->winner = rule.judge();
	ui->widget->update();
}