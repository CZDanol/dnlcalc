#pragma once

#include <QWidget>
#include <QMainWindow>

namespace Ui {
	class CalcWindow;
}

class CalcWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit CalcWindow(QWidget *parent = nullptr);
	~CalcWindow();

public slots:
	void updateExpressionInputHeight();
	void processInput();

protected:
	virtual bool eventFilter(QObject *o, QEvent *e) override;
	virtual void showEvent(QShowEvent *event) override;

private:
	Ui::CalcWindow *ui;
};

