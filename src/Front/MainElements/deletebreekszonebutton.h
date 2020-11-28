#ifndef DELETEBREEKSZONEBUTTON_H
#define DELETEBREEKSZONEBUTTON_H

#include <QPushButton>
#include <QObject>

class DeleteBreeksZoneButton : public QPushButton
{
	Q_OBJECT
public:
	DeleteBreeksZoneButton(int, QWidget *parent = nullptr);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void setZoneIndex(int);

signals:
	void deleteZone(int);

private:
	int zoneIndex_;
};

#endif // DELETEBREEKSZONEBUTTON_H
