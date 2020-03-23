#include "undoredotext.h"

UndoRedoText::UndoRedoText()
{}

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
