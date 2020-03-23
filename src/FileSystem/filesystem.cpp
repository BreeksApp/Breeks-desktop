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
  QSqlQuery query;
  query.exec(queryString);
	QString data;

  while (query.next()) {
    QSqlRecord record = query.record();
    data = record.value(0).toString();
  }

  return data;
}

void filesystem::writeTextEditToDB(textInfo_t &info, const int currentFile)
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

void filesystem::pushDataToDB(QJsonDocument &jDoc, QJsonObject &jObject, QJsonObject &notes, QJsonObject &note,
															textInfo_t &info, const int currentFile)
{
	note.insert("charStyleVector", info.jArr);
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

QJsonObject filesystem::readTextEdidFromDB(const int currentFile)
{
  QJsonDocument jDoc = QJsonDocument::fromJson(getDataFromDB().toUtf8());
  QJsonObject jObject = jDoc.object();
  QJsonObject notes = jObject.value("textEdit").toObject();

  parseDataBase(notes);

  switch (currentFile) {
		case 1 :
      return note1_;
		case 2 :
      return note2_;
		case 3 :
      return note3_;
		case 4 :
      return note4_;
		case 5 :
      return note5_;
		case 6 :
      return note6_;

		default :
			return  note1_;
  }
}


