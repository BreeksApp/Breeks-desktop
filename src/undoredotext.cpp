#include "undoredotext.h"

UndoRedoText::UndoRedoText()
{}

//-----UNDO
bool UndoRedoText::isUndoEmpty()
{
	return undoStack.isEmpty();
}

void UndoRedoText::pushUndoCommand(const commandInfo_t command)
{
	undoStack.push(command);
}

void UndoRedoText::popUndoCommand(commandInfo_t& command) {
	command = undoStack.top();
	undoStack.pop();
}

//-----REDO
bool UndoRedoText::isRedoEmpty()
{
	return redoStack.isEmpty();
}

void UndoRedoText::pushRedoCommand(const commandInfo_t command)
{
	redoStack.push(command);
}

void UndoRedoText::popRedoCommand(commandInfo_t& command) {
	command = redoStack.top();
	redoStack.pop();
}
