#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr=fopen("contacts.txt","w");
    if (fptr == NULL)
        return;
    fwrite(&addressBook->contactCount,sizeof(int),1,fptr);
    fwrite(addressBook->contacts,sizeof(Contact),addressBook->contactCount,fptr);
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr=fopen("contacts.txt","r");
    if (fptr == NULL)
    {
        addressBook->contactCount = 0;
        printf("Contacts loading from files failed \n");
        return;
    }
    fread(&addressBook->contactCount,sizeof(int),1,fptr);
    fread(addressBook->contacts,sizeof(Contact),addressBook->contactCount,fptr);
    fclose(fptr);
}
