#ifndef DESCRIPTIONZONEDAYBUTTON_H
#define DESCRIPTIONZONEDAYBUTTON_H

#include <QPushButton>

class DescriptionZoneDayButton : public QPushButton
{
  Q_OBJECT

public:
  DescriptionZoneDayButton(int, int);
  void mousePressEvent(QMouseEvent *event) override;
  int getZoneIndex();
  void setZoneIndex(int);

public slots:
  void sendPutRequestBl();

signals:
  void singleClick();
  void singleClick(int);
  void doubleClick(int, int);

  void changeZoneIndex(int);

private:
  int zoneIndex_;
  int dayIndex_;
};

#endif // DESCRIPTIONZONEDAYBUTTON_H
