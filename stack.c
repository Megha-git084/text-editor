#include "stack.h"

// Initialize empty stack
void initializeStack(Stack *stack)
{
    stack->top = -1;
}

// Check whether stack is empty
int isEmpty(Stack *stack)
{
    return (stack->top == -1);
}

// Check whether stack is full
int isFull(Stack *stack)
{
    return (stack->top == STACK_SIZE - 1);
}

// Push action into stack
void push(Stack *stack, Action action)
{
    int i;

    // Remove oldest action if stack is full
    if(isFull(stack))
    {
        for(i = 1; i < STACK_SIZE; i++)
        {
            stack->actions[i - 1] = stack->actions[i];//remove oldest action shift every element toward beginning
        }

        stack->top--;
    }

    stack->actions[++stack->top] = action;
}//

// Pop action from stack
Action pop(Stack *stack)
{
    Action action;

    strcpy(action.operation, "");
    strcpy(action.text, "");
    action.cursorPos = 0;

    if(isEmpty(stack))
        return action;

    action = stack->actions[stack->top];

    stack->top--;

    return action;
}

// Display stack contents
void displayStack(Stack *stack)
{
    int i;

    if(isEmpty(stack))
    {
        printf("\nStack is Empty.\n");
        return;
    }

    printf("\n========== STACK ==========\n");

    for(i = stack->top; i >= 0; i--)
    {
        printf("\nOperation : %s", stack->actions[i].operation);
        printf("\nText      : %s", stack->actions[i].text);
        printf("\nCursorPos : %d", stack->actions[i].cursorPos);
        printf("\n---------------------------");
    }
}