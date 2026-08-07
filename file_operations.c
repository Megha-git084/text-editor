#include "file_operations.h"
#include "text_operations.h"

// Store current file name
char fileName[100];

// Open a text file
void openFile()
{
    FILE *fp;
    char ch;//Stores one character at a time while reading the file.

    printf("\nEnter File Name : ");
    scanf("%s", fileName);
    getchar();

    fp = fopen(fileName, "r");

    if(fp == NULL)
    {
        printf("\nFile Not Found.\n");
        return;
    }

    // Clear previous editor contents
    freeEditor();
    initializeEditor();

    // Read every character
    while((ch = fgetc(fp)) != EOF)
    {
        insertCharacter(ch);
    }

    fclose(fp);

    printf("\nFile Opened Successfully.\n");
}

// Save editor contents
void saveFile()
{
    FILE *fp;

    Node *temp;

    if(strlen(fileName) == 0)//checks whether file name already stored
    {
        printf("\nEnter File Name : ");
        scanf("%s", fileName);
        getchar();
    }

    fp = fopen(fileName, "w");

    if(fp == NULL)
    {
        printf("\nUnable to Save File.\n");
        return;
    }

    temp = editor.head;

    while(temp != NULL)
    {
        fputc(temp->ch, fp);//writes one charcter into file
        temp = temp->next;//moves next node
    }

    fclose(fp);

    printf("\nFile Saved Successfully.\n");
}

// Close current file
void closeFile()
{
    freeEditor();//delete all nodes from memory

    initializeEditor();

    fileName[0] = '\0';//clears the stored filename

    printf("\nFile Closed Successfully.\n");
}