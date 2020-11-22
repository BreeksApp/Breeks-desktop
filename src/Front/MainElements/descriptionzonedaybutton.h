#ifndef DESCRIPTIONZONEDAYBUTTON_H
#define DESCRIPTIONZONEDAYBUTTON_H

#include <QPushButton>

class DescriptionZoneDayButton : public QPushButton
{
	Q_OBJECT
public:
	DescriptionZoneDayButton(int, int);

	void mousePressEvent(QMouseEvent *event) override;

signals:
	void singleClick();
	void doubleClick(int, int);

private:
	int zoneIndex_;
	int dayIndex_;
};

#endif // DESCRIPTIONZONEDAYBUTTON_H
