#ifndef UNDOREDOTEXT_H
#define UNDOREDOTEXT_H

#include <QVector>
#include <QStack>

#include "Front/datastructures.h"

enum command {
	insertStr,
	deleteStr,
	changeStyle,
	changeColor
};

struct commandInfo_t {
	command commandName;
	int pos; //last char
	QVector< charStyle_t > charStyleVector;
	QString text;
};

class UndoRedoText
{
public:
	UndoRedoText();

	bool isUndoEmpty();
	void pushUndoCommand(const commandInfo_t command);
	void popUndoCommand(commandInfo_t& command);

	bool isRedoEmpty();
	void pushRedoCommand(const commandInfo_t command);
	void popRedoCommand(commandInfo_t& command);

private:
	QStack< commandInfo_t > undoStack;
	QStack< commandInfo_t > redoStack;
};

#endif // UNDOREDOTEXT_H
