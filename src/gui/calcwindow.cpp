#include "calcwindow.h"
#include "ui_calcwindow.h"

CalcWindow::CalcWindow(QWidget *parent) : QWidget(parent), ui(new Ui::CalcWindow) {
	ui->setupUi(this);

	connect(ui->teExpression->document(), &QTextDocument::contentsChanged, this, &CalcWindow::updateExpressionInputHeight);
	updateExpressionInputHeight();
}

CalcWindow::~CalcWindow() {
	delete ui;
}

void CalcWindow::updateExpressionInputHeight() {
	auto te = ui->teExpression;
	auto h = te->document()->size().height() + 4;
	te->setFixedHeight(qBound(16, int(h), 512));
}
