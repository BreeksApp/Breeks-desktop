#include "Front/mainwindow.h"
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
}

void MainWindow::setAllElementsShadow()
{
	effects::setElementShadow<GenTextEdit>(ui->note);
  effects::setElementShadow<QLabel>(ui->labelImageBackground);
}
