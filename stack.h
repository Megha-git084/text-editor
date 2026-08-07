#ifndef STACK_H
#define STACK_H

#include "text_editor.h"

// Initialize stack
void initializeStack(Stack *stack);

// Check stack is empty
int isEmpty(Stack *stack);

// Check stack is full
int isFull(Stack *stack);

// Push an action
void push(Stack *stack, Action action);

// Pop an action
Action pop(Stack *stack);

// Display stack (Debugging)
void displayStack(Stack *stack);

#endif