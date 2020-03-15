#include "filesystem.h"

QJsonObject filesystem::note1_;
QJsonObject filesystem::note2_;
QJsonObject filesystem::note3_;
QJsonObject filesystem::note4_;
QJsonObject filesystem::note5_;
QJsonObject filesystem::note6_;

filesystem::filesystem()
{}

QString filesystem::getDataFromDB()
{
  QString queryString = "SELECT Notes FROM Employee WHERE Username='1'";
  QString data;
  QSqlQuery query;
  query.exec(queryString);
  while (query.next()) {
    QSqlRecord record = query.record();
    data = record.value(0).toString();
  }

  return data;
}

void filesystem::writeTextEditToDB(NoteInfo &info, const int currentFile)
{
  QJsonDocument jDoc = QJsonDocument::fromJson(getDataFromDB().toUtf8());
  QJsonObject jObject = jDoc.object();
  QJsonObject notes = jObject.value("textEdit").toObject();

  parseDataBase(notes);

  switch (currentFile) {
    case 1:
      pushDataToDB(jDoc, jObject, notes, note1_, info, currentFile);
      break;
    case 2:
      pushDataToDB(jDoc, jObject, notes, note2_, info, currentFile);
      break;
    case 3:
      pushDataToDB(jDoc, jObject, notes, note3_, info, currentFile);
      break;
    case 4:
      pushDataToDB(jDoc, jObject, notes, note4_, info, currentFile);
      break;
    case 5:
      pushDataToDB(jDoc, jObject, notes, note5_, info, currentFile);
      break;
    case 6:
      pushDataToDB(jDoc, jObject, notes, note6_, info, currentFile);
      break;
    }
}

void filesystem::pushDataToDB(QJsonDocument &jDoc, QJsonObject &jObject, QJsonObject &notes, QJsonObject &note, NoteInfo &info, const int currentFile)
{
  note.insert("charCount", info.charCount);
  note.insert("charState", info.charState);
  note.insert("text", info.text);

  notes.insert("note" + QString::number(currentFile), note);
  jObject.insert("textEdit", notes);
  jDoc.setObject(jObject);
  QString strJson(jDoc.toJson(QJsonDocument::Compact));
  QSqlQuery query("UPDATE Employee SET Notes ='"+strJson+"' WHERE Username ='1'");
}

void filesystem::parseDataBase(QJsonObject &notes)
{
  note1_ = notes.value("note1").toObject();
  note2_ = notes.value("note2").toObject();
  note3_ = notes.value("note3").toObject();
  note4_ = notes.value("note4").toObject();
  note5_ = notes.value("note5").toObject();
  note6_ = notes.value("note6").toObject();
}

QString filesystem::readNote(QJsonObject& object)
{
  int charCount = object.value("charCount").toInt();
  QString chars = QString::number(charCount);
  QString charState = object.value("charState").toString();
  QString textChar = object.value("text").toString();
  QString info = chars;
  info.append(" ");
  info.append(charState);
  info.append(" ");
  info.append(textChar);
  return info;
}

QString filesystem::readTextEdidFromDB(const int currentFile)
{
  QJsonDocument jDoc = QJsonDocument::fromJson(getDataFromDB().toUtf8());
  QJsonObject jObject = jDoc.object();
  QJsonObject notes = jObject.value("textEdit").toObject();

  parseDataBase(notes);
  //qDebug() << nCurrentFile_;
  switch (currentFile) {
    case 1:
      return readNote(note1_);
    case 2:
      return readNote(note2_);
    case 3:
      return readNote(note3_);
    case 4:
      return readNote(note4_);
    case 5:
      return readNote(note5_);
    case 6:
      return readNote(note6_);
    }
  return "";
}


