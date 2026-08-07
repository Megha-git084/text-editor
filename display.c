#include "display.h"
#include "text_operations.h"

// Display complete editor
void displayText()
{
Node *temp;//temporary pointer to traverse the linked list

    if(editor.head == NULL)
    {
        printf("\nEditor is Empty.\n");
        return;
    }

    printf("\n========== TEXT ==========\n\n");

    temp = editor.head;//start traversal from first node

    if(editor.cursor == NULL)//if cursor before first character
        printf("|");

    while(temp != NULL)//traverse every node
    {
        printf("%c", temp->ch);//print each character

        if(temp == editor.cursor)//if current node is cursor position
            printf("|");

        temp = temp->next;//move to next node
    }

    printf("\n\n==========================\n");
}

// Search a word
void findText()
{
    char word[100];//stores the word entered by user
    char buffer[MAX_TEXT];//stores the entire editor text
    Node *temp;
    int i = 0;

    printf("\nEnter Text to Search : ");
    fgets(word,100,stdin);//read the search word

    word[strcspn(word,"\n")] = '\0';//removes newline

    temp = editor.head;//start traversal

    while(temp != NULL)//convert linked list to string
    {
        buffer[i++] = temp->ch;
        temp = temp->next;
    }

    buffer[i] = '\0';//terminate string

    if(strstr(buffer,word) != NULL)//search for substring
        printf("\nText Found.\n");
    else
        printf("\nText Not Found.\n");
}

// Replace text
void replaceText()
{
    char oldWord[100];//word to replace
    char newWord[100];//replacement word
    char buffer[MAX_TEXT];//complete editor text
    Node *temp;
    char *ptr;//store address where the old word is found
    int i = 0;

    printf("\nEnter Old Text : ");
    fgets(oldWord,100,stdin);
    oldWord[strcspn(oldWord,"\n")] = '\0';

    printf("\nEnter New Text : ");
    fgets(newWord,100,stdin);
    newWord[strcspn(newWord,"\n")] = '\0';

    temp = editor.head;

    while(temp != NULL)//conver linklist to string
    {
        buffer[i++] = temp->ch;
        temp = temp->next;
    }

    buffer[i] = '\0';//terminate

    ptr = strstr(buffer,oldWord);

    if(ptr == NULL)
    {
        printf("\nText Not Found.\n");
        return;
    }

    freeEditor();//delete current link list
    initializeEditor();

    ptr = strstr(buffer,oldWord);//search again

    if(ptr != NULL)
    {
        char result[MAX_TEXT];//store final modified string

        int index = ptr - buffer;//find where word starts

        strncpy(result,buffer,index);//copies everything before old word
        result[index] = '\0';

        strcat(result,newWord);//append
        strcat(result,ptr + strlen(oldWord));//append remaining text

        for(i = 0; result[i] != '\0'; i++)
            insertCharacter(result[i]);

        printf("\nText Replaced Successfully.\n");
    }
}//