#include "mainwindow.h"
#include <QGraphicsDropShadowEffect>

void MainWindow::setAllElementsEffects()
{
  paletteSelectedPageButton_.setColor(QPalette::Button, effects::colorSelected); //blue
  paletteDefaultElement_.setColor(QPalette::Button, effects::colorDefault); //grey

  setAllElementsColor();
  setAllElementsShadow();

  noteMakePageButtonSelectable(ui->note->getNumberCurrentFile());
}

void MainWindow::setAllElementsColor()
{
  effects::setElementColor<QPushButton>(ui->buttonMakeBold, paletteDefaultElement_);
  effects::setElementColor<QPushButton>(ui->buttonMakeItalic, paletteDefaultElement_);
  effects::setElementColor<QPushButton>(ui->buttonMakeUnderline, paletteDefaultElement_);
  effects::setElementColor<QPushButton>(ui->buttonMakeStrike, paletteDefaultElement_);
  effects::setElementColor<QPushButton>(ui->buttonAddTodoList, paletteDefaultElement_);

  effects::setElementColor<QPushButton>(ui->buttonPage1, paletteDefaultElement_);
  effects::setElementColor<QPushButton>(ui->buttonPage2, paletteDefaultElement_);
  effects::setElementColor<QPushButton>(ui->buttonPage3, paletteDefaultElement_);
  effects::setElementColor<QPushButton>(ui->buttonPage4, paletteDefaultElement_);
  effects::setElementColor<QPushButton>(ui->buttonPage5, paletteDefaultElement_);
  effects::setElementColor<QPushButton>(ui->buttonPage6, paletteDefaultElement_);
}

void MainWindow::setAllElementsShadow()
{
  effects::setElementShadow<NoteTextEdit>(ui->note);
  effects::setElementShadow<QLabel>(ui->labelImageBackground);
}
