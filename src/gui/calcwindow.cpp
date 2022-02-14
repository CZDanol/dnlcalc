#include "calcwindow.h"
#include "ui_calcwindow.h"

#include <QKeyEvent>

#include "expr/parser/parser.h"
#include "expr/parser/rule/expressionrule.h"
#include "expr/parser/rule/errorrule.h"

#include "expr/exec/executioncontext.h"
#include "expr/exec/executionerror.h"

CalcWindow::CalcWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::CalcWindow) {
	ui->setupUi(this);

	setWindowTitle(PROGRAM_NAME_VERSION);

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
		static const QRegularExpression r("^([a-z]+|[0-9]+|[^a-z0-9]+)", QRegularExpression::CaseInsensitiveOption);
		ui->lblError->setText(tr("(%1): Unexpected \"%2\".").arg(QString::number(p.pos()), r.match(src.mid(p.pos()).trimmed()).captured(0)));
	}

	auto &r = dynamic_cast<const Rules::Expression &>(*rr);
	assert(&r);

	ExecutionContext ctx;
	QString result;

	try {
		result = r.exec(ctx).displayString(ctx);
	}
	catch(const ExecutionError &e) {
		ui->lblError->setText(e.msg);
		return;
	}

	ui->lblResult->setText(result);
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

void CalcWindow::showEvent(QShowEvent *event) {
	QWidget::showEvent(event);

	if(event->isAccepted()) {
		ui->teExpression->setFocus();
		ui->teExpression->selectAll();
	}
}
