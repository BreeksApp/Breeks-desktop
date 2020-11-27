#ifndef ADDBREEKGB_H
#define ADDBREEKGB_H

#include <QGroupBox>
#include <QWidget>

class AddBreekGB : public QGroupBox
{
	Q_OBJECT
public:
	AddBreekGB(QWidget *parent = nullptr);

	void keyPressEvent(QKeyEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;

signals:
	void focusOut();
};

#endif // ADDBREEKGB_H
