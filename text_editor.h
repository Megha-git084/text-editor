#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT 1000 //maximum text buffer
#define STACK_SIZE 50

// Node of doubly linked list
//represent one character in text editor
typedef struct Node
{
    char ch;
    struct Node *prev;
    struct Node *next;

} Node;


// Text Editor
typedef struct
{
    Node *head;//first character
    Node *tail;//last character
    Node *cursor;//current cursor position

    int cursorPos;//store cursor index

} TextEditor;

// Action for Undo/Redo
typedef struct
{
    char operation[20];//stores operation name
    char text[2];//stores one character plus null terminator
    int cursorPos;//stores the cursor position when action happens

} Action;

// Stack
typedef struct
{
    Action actions[STACK_SIZE];//array to store action
    int top;

} Stack;

// Global variables
extern TextEditor editor;
extern Stack undoStack;
extern Stack redoStack;
extern int undoRedoFlag;

// Function declarations
void initializeEditor();
void freeEditor();//frees all dynamically allocated nodes before exiting
int getLength();//returns total number of character
void moveCursorToPosition(int pos);//moves cursor to specified position

#endif