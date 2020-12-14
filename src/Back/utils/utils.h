#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QJsonArray>
#include <QVector>

#include "Front/datastructures.h"

QJsonObject objectFromString(const QString&);
QJsonArray jsonArrayFromString(const QString&);

void createCharStyleVector(QVector<charStyle_t>&, const QJsonArray&);
void createArrNEmoji(int*,  const unsigned, const QJsonArray&);

#endif // UTILS_H
