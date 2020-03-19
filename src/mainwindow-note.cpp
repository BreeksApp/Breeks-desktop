#include "mainwindow.h"

/*void MainWindow::noteMakePageButtonSelectable(QPushButton *button)
{
  //set previous button in default state
  switch (ui->note->getNumberCurrentFile()) {
    case 1 :
      effects::setElementColor<QPushButton>(ui->buttonPage1, paletteDefaultElement_);
      break;
    case 2 :
     effects::setElementColor<QPushButton>(ui->buttonPage2, paletteDefaultElement_);
      break;
    case 3 :
     effects::setElementColor<QPushButton>(ui->buttonPage3, paletteDefaultElement_);
      break;
    case 4 :
     effects::setElementColor<QPushButton>(ui->buttonPage4, paletteDefaultElement_);
      break;
    case 5 :
     effects::setElementColor<QPushButton>(ui->buttonPage5, paletteDefaultElement_);
      break;
    case 6 :
     effects::setElementColor<QPushButton>(ui->buttonPage6, paletteDefaultElement_);
      break;
  }
  //make selected
 effects::setElementColor<QPushButton>(button, paletteSelectedPageButton_);
}

void MainWindow::noteMakePageButtonSelectable(int nPage)
{
  switch (nPage) {
    case 1 :
     effects::setElementColor<QPushButton>(ui->buttonPage1, paletteSelectedPageButton_);
      break;
    case 2 :
     effects::setElementColor<QPushButton>(ui->buttonPage2, paletteSelectedPageButton_);
      break;
    case 3 :
     effects::setElementColor<QPushButton>(ui->buttonPage3, paletteSelectedPageButton_);
      break;
    case 4 :
     effects::setElementColor<QPushButton>(ui->buttonPage4, paletteSelectedPageButton_);
      break;
    case 5 :
     effects::setElementColor< QPushButton >(ui->buttonPage5, paletteSelectedPageButton_);
      break;
    case 6 :
     effects::setElementColor<QPushButton>(ui->buttonPage6, paletteSelectedPageButton_);
      break;
  }
}

void MainWindow::noteChangePage(const int n)
{
  ui->note->setNumberCurrentFile(n);
  ui->note->clear();
  ui->note->readFromDB(ui->note->getNumberCurrentFile());
}

//-------------------------BUTTONS-------------------------
void MainWindow::on_buttonMakeBold_clicked()
{
  ui->note->setFontStyle(ui->note->fontStyleValue_t::Bold);
  //ui->note->writeToFile();
}
void MainWindow::on_buttonMakeItalic_clicked()
{
  ui->note->setFontStyle(ui->note->fontStyleValue_t::Italic);
  //ui->note->writeToFile();
}
void MainWindow::on_buttonMakeUnderline_clicked()
{
  ui->note->setFontStyle(ui->note->fontStyleValue_t::Underline);
  //ui->note->writeToFile();
}
void MainWindow::on_buttonMakeStrike_clicked()
{
  ui->note->setFontStyle(ui->note->fontStyleValue_t::Strike);
  //ui->note->writeToFile();
}
void MainWindow::on_buttonAddTodoList_clicked()
{
  ui->note->addTodoList();
  //ui->note->writeToFile();
}

void MainWindow::on_buttonPage1_clicked()
{
  ui->note->writeToDB(ui->note->getNumberCurrentFile());

  const int nButton = 1;
  noteMakePageButtonSelectable(ui->buttonPage1);
  noteChangePage(nButton);

  writeDataToFileLastVisit();
}
void MainWindow::on_buttonPage2_clicked()
{
  ui->note->writeToDB(ui->note->getNumberCurrentFile());

  const int nButton = 2;
  noteMakePageButtonSelectable(ui->buttonPage2);
  noteChangePage(nButton);

  writeDataToFileLastVisit();
}
void MainWindow::on_buttonPage3_clicked()
{
  ui->note->writeToDB(ui->note->getNumberCurrentFile());

  const int nButton = 3;
  noteMakePageButtonSelectable(ui->buttonPage3);
  noteChangePage(nButton);

  writeDataToFileLastVisit();
}
void MainWindow::on_buttonPage4_clicked()
{
  ui->note->writeToDB(ui->note->getNumberCurrentFile());

  const int nButton = 4;
  noteMakePageButtonSelectable(ui->buttonPage4);
  noteChangePage(nButton);

  writeDataToFileLastVisit();
}
void MainWindow::on_buttonPage5_clicked()
{
  ui->note->writeToDB(ui->note->getNumberCurrentFile());

  const int nButton = 5;
  noteMakePageButtonSelectable(ui->buttonPage5);
  noteChangePage(nButton);

  writeDataToFileLastVisit();
}
void MainWindow::on_buttonPage6_clicked()
{
  ui->note->writeToDB(ui->note->getNumberCurrentFile());

  const int nButton = 6;
  noteMakePageButtonSelectable(ui->buttonPage6);
  noteChangePage(nButton);

  writeDataToFileLastVisit();
}*/
