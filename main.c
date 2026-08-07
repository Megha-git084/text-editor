#include <stdio.h>

#include "text_editor.h"
#include "text_operations.h"
#include "cursor_navigation.h"
#include "display.h"
#include "file_operations.h"
#include "undo_redo.h"
#include "stack.h"

int main()
{
    int choice;

    // Initialize editor
    initializeEditor();

    // Initialize Undo Stack
    initializeStack(&undoStack);

    // Initialize Redo Stack
    initializeStack(&redoStack);
printf("%zu\n", sizeof(Node));
    while(1)
    {
        printf("\n======================================");
        printf("\n      TEXT EDITOR USING DSA");
        printf("\n======================================");

        printf("\n1. Open File");
        printf("\n2. Save File");
        printf("\n3. Close File");
        printf("\n4. Display");

        printf("\n5. Insert Text");
        printf("\n6. Delete Character");

        printf("\n7. Move Left");
        printf("\n8. Move Right");
        printf("\n9. Move Up");
        printf("\n10. Move Down");

        printf("\n11. Copy");
        printf("\n12. Cut");
        printf("\n13. Paste");

        printf("\n14. Search");
        printf("\n15. Replace");

        printf("\n16. Undo");
        printf("\n17. Redo");

        printf("\n18. Exit");

        printf("\n\nEnter Choice : ");
        scanf("%d",&choice);
        getchar();

        switch(choice)
        {
            case 1:
                openFile();
                break;

            case 2:
                saveFile();
                break;

            case 3:
                closeFile();
                break;

            case 4:
                displayText();
                break;

            case 5:
                insertText();
                break;

            case 6:
                deleteText();
                break;

            case 7:
                moveCursorLeft();
                break;

            case 8:
                moveCursorRight();
                break;

            case 9:
                moveCursorUp();
                break;

            case 10:
                moveCursorDown();
                break;

            case 11:
                copyText();
                break;

            case 12:
                cutText();
                break;

            case 13:
                pasteText();
                break;

            case 14:
                findText();
                break;

            case 15:
                replaceText();
                break;

            case 16:
                undo();
                break;

            case 17:
                redo();
                break;

            case 18:
                freeEditor();
                printf("\nThank You...\n");
                return 0;

            default:
                printf("\nInvalid Choice.\n");
        }
    }
    

    return 0;
}