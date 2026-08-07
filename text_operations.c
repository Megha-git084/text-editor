#include "text_operations.h"
#include "undo_redo.h"

// Clipboard
char clipboard[MAX_TEXT];//A temporary buffer used to store copied or cut text.

// Insert one character at cursor
void insertCharacter(char ch)
{
    //allocates memory for new node
    Node *newNode;

    newNode = (Node *)malloc(sizeof(Node));

    if(newNode == NULL)
    {
        printf("\nMemory Allocation Failed\n");
        return;
    }

    newNode->ch = ch;//store charater

    newNode->next = NULL;
    newNode->prev = NULL;

    // Empty editor
    if(editor.head == NULL)
    {
        editor.head = newNode;
        editor.tail = newNode;
        editor.cursor = newNode;
    }

    // Insert at beginning
    else if(editor.cursor == NULL)
    {
        newNode->next = editor.head;
        editor.head->prev = newNode;
        editor.head = newNode;//update head pointer
        editor.cursor = newNode;//move the cursor to newly insreted node
    }

    // Insert after cursor
    else
    {
        newNode->next = editor.cursor->next;
        newNode->prev = editor.cursor;

        if(editor.cursor->next != NULL)//checks whether cursor is not last node
            editor.cursor->next->prev = newNode;//if there is another node afterthe cursor ,its prev must be updated
        else
            editor.tail = newNode;//cursor at last node

        editor.cursor->next = newNode;
        editor.cursor = newNode;
    }

    editor.cursorPos++;

    // Save for Undo
    Action action;
    //it stores operation name,character,position of cursor

    strcpy(action.operation,"insert");//store operation name
//stores the inserted character
    action.text[0] = ch;
    action.text[1] = '\0';

    action.cursorPos = editor.cursorPos;

    if(undoRedoFlag == 0)
    {
        push(&undoStack,action);
        initializeStack(&redoStack);
    }
}

// Insert a complete string
void insertText()
{
    char text[MAX_TEXT];//stores string enetred by user

    printf("\nEnter Text : ");

    fgets(text,MAX_TEXT,stdin);//reads an entire line

    text[strcspn(text,"\n")] = '\0';//removes \n added by fgets()
//loops through every character
    for(int i=0;text[i]!='\0';i++)
    {
        insertCharacter(text[i]);
    }

    printf("\nText Inserted Successfully\n");
}
// Delete one character
void deleteText()
{
    Node *temp;//temporary pointer ,it stores the node that will be deleted

    Action action;//stire delete info

    // Check editor is empty
    if(editor.cursor == NULL)
    {
        printf("\nNothing to Delete.\n");
        return;
    }

    temp = editor.cursor;//store current node

    // Store action for Undo
    strcpy(action.operation,"delete");

    action.text[0] = temp->ch;
    action.text[1] = '\0';

    action.cursorPos = editor.cursorPos;//store position

    if(undoRedoFlag == 0)
    {
        push(&undoStack,action);//save delete action
        initializeStack(&redoStack);
    }

    // Only one node
    if(editor.head == editor.tail)
    {
        free(temp);

        editor.head = NULL;
        editor.tail = NULL;
        editor.cursor = NULL;

        editor.cursorPos = 0;

        printf("\nCharacter Deleted Successfully.\n");
        return;
    }

    // Delete first node
    if(temp == editor.head)
    {
        editor.head = temp->next;

        editor.head->prev = NULL;

        editor.cursor = editor.head;
    }

    // Delete last node
    else if(temp == editor.tail)
    {
        editor.tail = temp->prev;

        editor.tail->next = NULL;

        editor.cursor = editor.tail;

        editor.cursorPos--;
    }

    // Delete middle node
    else
    {
        temp->prev->next = temp->next;

        temp->next->prev = temp->prev;

        editor.cursor = temp->prev;//move cursor to previous node after deletion

        editor.cursorPos--;
    }

    free(temp);

    printf("\nCharacter Deleted Successfully.\n");
}
// Copy one character
void copyText()
{
    // Check editor is empty
    if(editor.cursor == NULL)
    {
        printf("\nNothing to Copy.\n");
        return;
    }

    // Copy current character
    clipboard[0] = editor.cursor->ch;
    clipboard[1] = '\0';

    printf("\nCharacter Copied Successfully.\n");
}
// Cut one character
void cutText()
{
    // Check editor is empty
    if(editor.cursor == NULL)
    {
        printf("\nNothing to Cut.\n");
        return;
    }

    // Copy character to clipboard
    clipboard[0] = editor.cursor->ch;
    clipboard[1] = '\0';

    // Delete copied character
    deleteText();

    printf("\nCharacter Cut Successfully.\n");
}
// Paste character
void pasteText()
{
    // Check clipboard
    if(strlen(clipboard) == 0)
    {
        printf("\nClipboard is Empty.\n");
        return;
    }

    // Insert copied character
    insertCharacter(clipboard[0]);

    printf("\nCharacter Pasted Successfully.\n");
}