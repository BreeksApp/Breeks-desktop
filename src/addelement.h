#ifndef ADDELEMENT_H
#define ADDELEMENT_H

#include "ui_addelement.h"
#include "addbuttonhover.h"
#include "datastructures.h"
#include "effects.hpp"

#include <QWidget>
#include <QKeyEvent>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class AddElement; }
QT_END_NAMESPACE

class AddElement : public QWidget
{
  Q_OBJECT
public:
  AddElement(AddButtonHover *button, QWidget *parent = nullptr);
  ~AddElement();

  void keyPressEvent(QKeyEvent *event);

private slots:
  void on_buttonAdd_clicked();

  void on_buttonMonday_clicked();
  void on_buttonTuesday_clicked();
  void on_buttonWednesday_clicked();
  void on_buttonThursday_clicked();
  void on_buttonFriday_clicked();
  void on_buttonSaturday_clicked();

  void on_buttonTag_clicked();

  void on_pushButtonTimeTableZone_clicked();

  void on_pushButtonBreeksZone_clicked();

signals:
  void sendTimeTableZoneData(bool *, const int, ElementData);
  void sendBreeksZoneData(bool *, const int, BreeksData);

private:
  Ui::AddElement *ui;

  AddButtonHover *mainAddButton_;

  bool areSelectedDays();
  void returnButtonsInitialCondition();

  bool breeksZoneCondition_;
  bool timeTableZoneCondition_;

  const int DAYS_CHECK_COUNT = 6;
  bool daysCheck_[6];

  //-----TAG-----
  struct tagElement {
    bool condition;
    QPalette pallete;
  };
  const int TAGS_COUNT = 6;
  tagElement arrTags_[6];

  QPalette currentTagPalette_;
  //

  //-----EMOJI-----
  struct emojiElement {
    bool condition;
    QString emojiAdress;
  };

  void setEmoji(const int index);

  const int EMOJI_COUNT = 11;
  emojiElement arrEmoji_[11];

  int currentEmoji;
  //

  QPalette paletteSelectedElement_;
  QPalette paletteDefaultElement_;

  void setAllElementsEffects();
};

#endif // ADDELEMENT_H
