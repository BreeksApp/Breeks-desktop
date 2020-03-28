#include "russiandictionary.h"

#include <QDebug>
#include <QFile>

RussianDictionary::RussianDictionary()
{
//.DIC
	QFile fDic("/home/yaroslav/PROJECTS/Breeks-App/src/RusDic/Russian.dic");
	if (!fDic.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "FILE OPENING CRASHED!";
	}
	QString sDic = fDic.readAll();
	QTextStream sourceDic(&sDic);
	int nWords = 0;
	sourceDic >> nWords;
	QString word = "";
//---------
	for (int i = 0; i < nWords - 1; ++i) {
		sourceDic >> word;
		word = word.left(word.indexOf('/'));
		const int index = QChar(word.at(0).toLower()).unicode() - RUS_A_UNICODE;
		const int length = word.length();

		arrDic_[index][length].push_back(word);
	}
}

bool RussianDictionary::isCorrectWord(const QString &word)
{
	const int indexFirstLetter = QChar(word.at(0).toLower()).unicode() - RUS_A_UNICODE;
	const int length = word.length();

	for(QString dicWord : arrDic_[indexFirstLetter][length]) {
		if (word == dicWord) {
			return true;
		}
	}

	return false;
}

void RussianDictionary::printAllWords()
{
	for (int i = 0; i < N_LETTERS; ++i) {
		for (int j = 0; j < MAX_WORD_LEN; ++j) {
			for(QString word : arrDic_[i][j]) {
				qDebug() << word;
			}
		}
	}
}
