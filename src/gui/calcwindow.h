#pragma once

#include <QWidget>

namespace Ui {
	class CalcWindow;
}

class CalcWindow : public QWidget
{
	Q_OBJECT

public:
	explicit CalcWindow(QWidget *parent = nullptr);
	~CalcWindow();

public slots:
	void updateExpressionInputHeight();

private:
	Ui::CalcWindow *ui;
};

