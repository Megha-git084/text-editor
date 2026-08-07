#include "undo_redo.h"
#include "text_operations.h"
#include "cursor_navigation.h"
#include "text_editor.h"

// Undo last operation
void undo()
{
    Action action;

    if(isEmpty(&undoStack))
    {
        printf("\nNothing to Undo.\n");
        return;
    }

    action = pop(&undoStack);//removes the most recent action

    undoRedoFlag = 1;

    // Restore cursor position
    moveCursorToPosition(action.cursorPos);

    if(strcmp(action.operation,"insert") == 0)
    {
        deleteText();
    }
    else if(strcmp(action.operation,"delete") == 0)
    {
        insertCharacter(action.text[0]);
    }
    else if(strcmp(action.operation,"left") == 0)
    {
        moveCursorRight();
    }
    else if(strcmp(action.operation,"right") == 0)
    {
        moveCursorLeft();
    }
    else if(strcmp(action.operation,"up") == 0)
    {
        moveCursorDown();
    }
    else if(strcmp(action.operation,"down") == 0)
    {
        moveCursorUp();
    }

    undoRedoFlag = 0;

    push(&redoStack, action);

    printf("\nUndo Successful.\n");
}


// Redo last operation
void redo()
{
    Action action;

    if(isEmpty(&redoStack))
    {
        printf("\nNothing to Redo.\n");
        return;
    }

    action = pop(&redoStack);

    undoRedoFlag = 1;

    // Restore cursor position
    moveCursorToPosition(action.cursorPos);

    if(strcmp(action.operation,"insert") == 0)
    {
        insertCharacter(action.text[0]);
    }
    else if(strcmp(action.operation,"delete") == 0)
    {
        deleteText();
    }
    else if(strcmp(action.operation,"left") == 0)
    {
        moveCursorLeft();
    }
    else if(strcmp(action.operation,"right") == 0)
    {
        moveCursorRight();
    }
    else if(strcmp(action.operation,"up") == 0)
    {
        moveCursorUp();
    }
    else if(strcmp(action.operation,"down") == 0)
    {
        moveCursorDown();
    }

    undoRedoFlag = 0;

    push(&undoStack, action);

    printf("\nRedo Successful.\n");
}