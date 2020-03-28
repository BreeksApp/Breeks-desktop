#ifndef RUSSIANDICTIONARY_H
#define RUSSIANDICTIONARY_H

#include <QVector>

class RussianDictionary
{
public:
	RussianDictionary();

	bool isCorrectWord(const QString& word);
	void addNewWord(const QString word);
	void printAllWords();

private:
	void detailsAddWord(const QString word);

	struct wordsLenght_t {
		int length;
		QVector< QString > words;
	};
	static const int N_LETTERS = 33;
	static const int MAX_WORD_LEN = 37;
	const int RUS_A_UNICODE = 1072;

	QVector< QString > arrDic_[N_LETTERS][MAX_WORD_LEN];
};

#endif // RUSSIANDICTIONARY_H
