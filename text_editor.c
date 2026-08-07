#include "text_editor.h"


// Global objects
int undoRedoFlag = 0;
//0 normal editing operation
//1 undo or redo in progress

TextEditor editor;

Stack undoStack;

Stack redoStack;

// Initialize editor before any operation
void initializeEditor()
{
    editor.head = NULL;

    editor.tail = NULL;

    editor.cursor = NULL;

    editor.cursorPos = 0;

    undoStack.top = -1;

    redoStack.top = -1;
}

// Free linked list
void freeEditor()
{
    Node *temp;//temporarily store the address of the current node before deleting

    while(editor.head != NULL)//runs untill all nodes are deleted
    {
        temp = editor.head;

        editor.head = editor.head->next;

        free(temp);
    }

    editor.tail = NULL;

    editor.cursor = NULL;

    editor.cursorPos = 0;
}

// Count total characters
int getLength()
{
    Node *temp;

    int count = 0;

    temp = editor.head;//temp point to first node of linklist

    while(temp != NULL)
    {
        count++;

        temp = temp->next;
    }

    return count;
}
void moveCursorToPosition(int pos)
{
    Node *temp;

    if(pos <= 0)
    {
        editor.cursor = NULL;
        editor.cursorPos = 0;
        return;
    }

    temp = editor.head;//traverse from first node
    editor.cursorPos = 1;

    while(temp != NULL && editor.cursorPos < pos)
    {
        temp = temp->next;
        editor.cursorPos++;
    }

    editor.cursor = temp;
}