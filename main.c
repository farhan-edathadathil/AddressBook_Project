#include <stdio.h>
#include "contact.h"
#include <unistd.h>
#include "file.h"

int main() 
{
    int choice,ch;
    char save;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\n*** %d contacts are available ***\n",addressBook.contactCount);
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save and Exit\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        if(scanf("%d", &choice)!=1)
        {
            printf("\nInvalid input !!\n\n");
            while ((ch = getchar()) != '\n' && ch != EOF);
            continue;
        }
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                listContacts(&addressBook);
                break;
            case 6:
                for(int i=0;i<=100;i++)
                {
                    printf("Saving changes........%d%%]\r",i);
                    usleep(10000);
                    fflush(stdout);
                }
                printf("\n\nChanges successfully saved !!\n");
                saveAndExit(&addressBook);
                break;
            case 7:
                again:
                printf("\nYou are going to exit -> do you want to save the changes before exit?\n");
                printf("\nEnter (YES -Y or NO -N) : ");
                scanf(" %c",&save);
                if(save=='Y' || save=='y')
                {
                    for(int i=0;i<=100;i++)
                    {
                        printf("Saving and Exiting........%d%%]\r",i);
                        usleep(10000);
                        fflush(stdout);
                    }
                    saveContactsToFile(&addressBook);
                    printf("\n\nContacts successfully saved !!\n");
                }
                else if(save=='N' || save=='n')
                {
                    printf("\nExit without saving changes !!\n");
                }
                else
                {
                    printf("\nINVALID INPUT !!\n");
                    while ((ch = getchar()) != '\n' && ch != EOF);
                    goto again;
                }
                break;   
            default:
                printf("\n\nInvalid choice. Please try again.\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
        }
    } while (choice != 7);
    
       return 0;
}
