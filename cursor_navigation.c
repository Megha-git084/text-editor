#include "cursor_navigation.h"
#include "stack.h"

// Move cursor left
void moveCursorLeft()
{
    if(editor.cursor == NULL)//checks wheter the cursor is already before the first character
    //editor.cursor stores the current cursor node
    //if it is NULL the cursor cannot move further left
    {
        printf("\nAlready at Beginning.\n");
        return;
    }

    // Move before first character
    if(editor.cursor->prev == NULL)
    {
        editor.cursor = NULL;
        editor.cursorPos = 0;//update cursor index
    }
    else
    {
        editor.cursor = editor.cursor->prev;
        editor.cursorPos--;
    }

    if(undoRedoFlag == 0)//checks whether this movement was done by user
                         //if its 1 the movement happened during undo redo
    {
        Action action;

        strcpy(action.operation,"left");
        action.cursorPos = editor.cursorPos;//stores new cursor position

        push(&undoStack,action);//save

        initializeStack(&redoStack);
    }

    printf("\nCursor Moved Left.\n");
}


// Move cursor right
void moveCursorRight()
{
    // Cursor before first character
    if(editor.cursor == NULL)//no text
    {
        if(editor.head == NULL)
        {
            printf("\nEditor Empty.\n");
            return;
        }

        editor.cursor = editor.head;//move to first character
        editor.cursorPos++;

        printf("\nCursor Moved Right.\n");
        return;
    }

    if(editor.cursor->next != NULL)
    {
        editor.cursor = editor.cursor->next;
        editor.cursorPos++;

        if(undoRedoFlag == 0)
        {
            Action action;

            strcpy(action.operation,"right");
            action.cursorPos = editor.cursorPos;

            push(&undoStack,action);

            initializeStack(&redoStack);
        }

        printf("\nCursor Moved Right.\n");
    }
    else
    {
        printf("\nAlready at End.\n");
    }
}


// Move cursor up
void moveCursorUp()
{
    Node *temp;

    if(editor.cursor == NULL)
    {
        printf("\nEditor Empty.\n");
        return;
    }

    temp = editor.cursor->prev;//move one node backward

    while(temp != NULL && temp->ch != '\n')
        temp = temp->prev;

    if(temp == NULL)
    {
        printf("\nAlready at First Line.\n");
        return;
    }

    temp = temp->prev;

    while(temp != NULL && temp->ch != '\n')
        temp = temp->prev;//move before new line

    if(temp == NULL)
        editor.cursor = editor.head;//first line
    else
        editor.cursor = temp->next;//move to first character of previous line

    if(undoRedoFlag == 0)
    {
        Action action;

        strcpy(action.operation,"up");
        action.cursorPos = editor.cursorPos;

        push(&undoStack,action);

        initializeStack(&redoStack);
    }

    printf("\nCursor Moved Up.\n");
}


// Move cursor down
void moveCursorDown()
{
    Node *temp;

    if(editor.cursor == NULL)
    {
        printf("\nEditor Empty.\n");
        return;
    }

    temp = editor.cursor;//start from current node

    while(temp != NULL && temp->ch != '\n')//move forward untill newline
        temp = temp->next;

    if(temp == NULL)
    {
        printf("\nAlready at Last Line.\n");
        return;
    }

    if(temp->next == NULL)
    {
        printf("\nAlready at Last Line.\n");
        return;
    }

    editor.cursor = temp->next;//move cursor to first character of next line

    if(undoRedoFlag == 0)
    {
        Action action;

        strcpy(action.operation,"down");
        action.cursorPos = editor.cursorPos;

        push(&undoStack,action);

        initializeStack(&redoStack);
    }

    printf("\nCursor Moved Down.\n");
}