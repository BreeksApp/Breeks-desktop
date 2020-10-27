#include "russiandictionary.h"

#include <QDebug>
#include <QFile>

RussianDictionary::RussianDictionary()
{
//.DIC
    QFile fDic("/Users/ruby/Desktop/BR/Breeks-desktop/src/Front/RusDic/RusDic.txt");
	if (!fDic.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "FILE OPENING CRASHED!";
	}
	QString sDic = fDic.readAll();
	QTextStream sourceDic(&sDic);
	size_t nWords = 0;
	sourceDic >> nWords;
	QString word = "";
//---------
	for (size_t i = 0; i < nWords - 1; ++i) {
		sourceDic >> word;
		detailsAddWord(word);
	}
}

bool RussianDictionary::isCorrectWord(const QString &word)
{
	const int indexFirstLetter = QChar(word.at(0).toLower()).unicode() - RUS_A_CODE;
	const int length = word.length();

	for(QString dicWord : arrDic_[indexFirstLetter][length]) {
		if (word == dicWord) {
			return true;
		}
	}

	return false;
}

void RussianDictionary::addNewWord(const QString word)
{
	if (word.length() < MAX_WORD_LEN) {
		detailsAddWord(word);
	}
}

void RussianDictionary::detailsAddWord(QString word)
{
	word = word.toLower();
	while (!word.isEmpty() && !(word.at(0) >= "а" && word.at(0) <= "я")) {
		word = word.right(word.length() - 1);
	}
	if (!word.isEmpty()) {
		const int index = (word.at(0) != QChar(YO_UNICODE)) ?
					QChar(word.at(0).toLower()).unicode() - RUS_A_CODE : YO_POS;
		const int length = word.length();
		arrDic_[index][length].push_back(word);
	}
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
