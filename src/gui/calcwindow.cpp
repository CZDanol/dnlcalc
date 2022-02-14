#include "calcwindow.h"
#include "ui_calcwindow.h"

#include <QKeyEvent>

#include "expr/parser.h"
#include "expr/executioncontext.h"
#include "expr/rule/expressionrule.h"
#include "expr/rule/errorrule.h"

CalcWindow::CalcWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::CalcWindow) {
	ui->setupUi(this);

	ui->teExpression->installEventFilter(this);
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

void CalcWindow::processInput() {
	ui->lblError->clear();
	ui->lblResult->clear();

	const QString src = ui->teExpression->toPlainText();

	Parser p;
	p.setup(src);
	p.skipWhitespace();
	RuleSP rr = p.parse<Rules::Expression>();
	p.skipWhitespace();

	if(rr->isErrorRule()) {
		auto &e = dynamic_cast<const Rules::Error &>(*rr);
		ui->lblError->setText(tr("(%1): %2").arg(QString::number(e.pos()), e.msg()));
		return;
	}

	if(p.pos() != src.length()) {
		static const QRegularExpression r("^([a-z]+|[0-9]+|[^a-z0-9]+)");
		ui->lblError->setText(tr("(%1): Unexpected \"%2\".").arg(QString::number(p.pos()), r.match(src.mid(p.pos()).trimmed()).captured(0)));
	}

	auto &r = dynamic_cast<const Rules::Expression &>(*rr);
	assert(&r);

	ExecutionContext ctx;
	Value result = r.exec(ctx);

	ui->lblResult->setText(result.displayString());
}

bool CalcWindow::eventFilter(QObject *o, QEvent *e) {
	if(o == ui->teExpression && e->type() == QEvent::KeyPress) {
		QKeyEvent *ke = static_cast<QKeyEvent *>(e);
		if((ke->key() == Qt::Key_Return || ke->key() == Qt::Key_Enter) && !(ke->modifiers() & Qt::SHIFT)) {
			processInput();
			return true;
		}
	}

	return false;
}
