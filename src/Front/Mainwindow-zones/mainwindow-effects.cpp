#include "Front/mainwindow.h"
#include <QGraphicsDropShadowEffect>

void MainWindow::setAllElementsEffects()
{
  paletteSelectedPageButton_.setColor(QPalette::Button, effects::colorSelected); //blue
  paletteDefaultElement_.setColor(QPalette::Button, effects::colorDefault); //grey

	//setAllElementsColor();
	setAllElementsShadow();

	noteMakePageButtonSelectable(ui->note->getNumberCurrentFile());
}

void MainWindow::setAllElementsColor()
{
}

void MainWindow::setAllElementsShadow()
{
	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(10);
	effect->setXOffset(0);
	effect->setYOffset(1);
	effect->setColor("#909090");

	ui->note->setGraphicsEffect(effect);

	QGraphicsDropShadowEffect *effect2 = new QGraphicsDropShadowEffect;
	effect2->setBlurRadius(10);
	effect2->setXOffset(0);
	effect2->setYOffset(1);
	effect2->setColor("#909090");
	ui->labelImageBackground->setGraphicsEffect(effect2);
}
