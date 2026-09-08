#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr=fopen("contacts.csv","w");
    if (fptr == NULL)
        return;
    fprintf(fptr,"%d\n",addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++)
        fprintf(fptr,"%s,%lu,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook)
{
    char new;
    FILE *fptr=fopen("contacts.csv","r");
    if (fptr == NULL)
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
