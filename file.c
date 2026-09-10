/*
FARHAN E

09/09/2026

PROJECT 1 :- ADDRESSBOOK
*/

#include <stdio.h>
#include "file.h"

int saveContactsToFile(AddressBook *addressBook)
{
    /*
    saveContactsToFile - Saves all contacts from the address book to a file.

    The function opens the contacts.csv file in write mode.

    If the file cannot be opened, the function returns without saving
    the contacts.

    The total number of contacts is first written to the file.

    Each contact is then written in the following format:

        name,phone number,email address

    Each contact is stored on a separate line in the file.

    After all contacts have been written, the file is closed using
    fclose().

    Parameters:
        addressBook - Pointer to the AddressBook structure containing
                        the contacts to be saved.

    Return:
        None.
    */
    FILE *fptr=fopen("contacts.csv","w");
    if (fptr == NULL)
    {
        perror("Unable to open file");
        printf("Contacts were not saved.\n");
        return 0;
    }
    fprintf(fptr,"%d\n",addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++)
        fprintf(fptr,"%s,%lu,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    fclose(fptr);
    return 1;
}

void loadContactsFromFile(AddressBook *addressBook)
{
    /*
    loadContactsFromFile - Loads saved contacts from a file into the address book.

    The function opens the contacts.csv file in read mode.

    If the file does not exist or cannot be opened, contactCount is set
    to 0 and an error message is displayed. This allows the address book
    to start without any previously saved contacts.

    The function first reads the total number of contacts stored in the
    file.

    It then reads each contact and stores the contact information in the
    contacts array of the AddressBook structure.

    Each contact is expected to contain the following information:

        name,phone number,email address

    After all contacts have been loaded, the file is closed using
    fclose().

    Parameters:
        addressBook - Pointer to the AddressBook structure where the
                        contacts will be loaded.

    Return:
        None.
    */
    FILE *fptr=fopen("contacts.csv","r");
    if(fptr == NULL)
    {
        addressBook->contactCount = 0;
        printf("FILE DOSE NOT EXIST :- Contacts loading from files got failed or newly stating addressbook !!\n");
        return;
    }
    fscanf(fptr,"%d\n",&addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++)
        fscanf(fptr,"%[^,],%lu,%s\n",addressBook->contacts[i].name,&addressBook->contacts[i].phone,addressBook->contacts[i].email);
    fclose(fptr);
}
