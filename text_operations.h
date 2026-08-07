#ifndef TEXT_OPERATIONS_H
#define TEXT_OPERATIONS_H

#include "text_editor.h"
#include "stack.h"

// Insert one character
void insertCharacter(char ch);

// Insert a string
void insertText();

// Delete one character
void deleteText();

// Copy text
void copyText();

// Cut text
void cutText();

// Paste text
void pasteText();

#endif