#include <stdio.h>
#include "contact.h"
#include <unistd.h>
#include "file.h"

int main() 
{
    int choice,sortChoice,ch;
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
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
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
                printf("\nChanges successfully saved\n");
                saveContactsToFile(&addressBook);
                break;
            case 7:
                for(int i=0;i<=100;i++)
                {
                    printf("Saving and Exiting........%d%%]\r",i);
                    usleep(10000);
                    fflush(stdout);
                }
                saveContactsToFile(&addressBook);
                printf("\nContacts successfully saved\n");
                break;   
            default:
                printf("\nInvalid choice. Please try again.\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
        }
    } while (choice != 7);
    
       return 0;
}
