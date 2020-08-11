//VIEW

#ifndef EFFECTS_HPP
#define EFFECTS_HPP

//#include <Qt>
#include <QColor>
#include <QPalette>
#include <QGraphicsDropShadowEffect>

namespace effects {
  const QColor colorDefault = "#eceaec"; //grey
  const QColor colorSelected = "#abdfff"; //blue

  template<typename T>
  void setElementColor(T *element, const QPalette color); //defenition is below of class

  template<typename T>
  void setElementShadow(T *element, const int radius = 20, const QColor color = Qt::black);
};

//----------TEMPLATE IMPLEMENTATION----------
template<typename T>
void effects::setElementColor(T *element, const QPalette color)
{
  element->setPalette(color);
}

template<typename T>
void effects::setElementShadow(T *element, const int radius, const QColor color)
{
  QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;

  effect->setBlurRadius(radius);
  effect->setXOffset(1);
  effect->setYOffset(1);
  effect->setColor(color);

  element->setGraphicsEffect(effect);
}

#endif //EFFECTS_HPP
