#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char ch;
    if(addressBook->contactCount<MAX_CONTACTS)
    {
        getchar();
        name:
        if(fgets((*addressBook).contacts[addressBook->contactCount].name,50,stdin) != NULL)
        {
            if (strchr((*addressBook).contacts[addressBook->contactCount].name, '\n') == NULL)
            {
                printf("\nINVALID :- Input may be too long!\n\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
                goto name;
            }
            *(strchr((*addressBook).contacts[addressBook->contactCount].name, '\n'))='\0';
            if(validname((addressBook->contacts+(addressBook->contactCount))->name)==0)
                goto name;
        }
        else 
            goto name;
        
        char num[12];
        num:
        printf("Enter the 10 digit phone number : ");
        if(fgets(num,12,stdin) != NULL)
        {
            if (strchr(num, '\n') == NULL)
            {
                printf("\nINVALID PHONE NUMBER :- Input must be 10 digits!\n\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
                goto num;
            }
            (addressBook->contacts+(addressBook->contactCount))->phone=my_atoi(num);
            if(validnum((*addressBook).contacts ,addressBook->contactCount)==0)
                goto num;
        }
        else
            goto num;
        
        mail:
        printf("Enter the mail id : ");
        if(fgets((*addressBook).contacts[addressBook->contactCount].email,256,stdin) != NULL)
        {
            if (strchr((*addressBook).contacts[addressBook->contactCount].email, '\n') == NULL)
            {
                printf("\nINVALID MAIL ID :- Input may be too long!\n\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
                goto mail;
            }
            
            *(strchr((*addressBook).contacts[addressBook->contactCount].email, '\n'))='\0';
            if(validmail((*addressBook).contacts,addressBook->contactCount)==0)
                goto mail;
        }
        else 
            goto mail;
        addressBook->contactCount++;
    }
    else
        printf("\nAddress book memmory full, you can edit,search and delete contacts !!\n\n");

}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
   
}

int validname(char *name)
{
    if(*name=='\0')
    {
        printf("\nINVALID NAME :- Name cannot be empty\n\n");
        return 0;
    }
    while(*name)
    {
        if((*name>='A' && *name<='Z') || (*name>='a' && *name<='z') || *name==' ')
            name++;
        else
        {
            printf("\nINVALID NAME\n\n");
            return 0;
        }
    }
    return 1;
}

int validnum(Contact *num,int count)
{
    if((num+count)->phone < 1000000000L || (num+count)->phone > 9999999999L)
    {
        printf("\nINVALID PHONE NUMBER :- must contain 10 digits and first digit can't be zero !!\n\n");
        return 0;
    }
    for(int i=0;i<count;i++)
        if((num+count)->phone == (num+i)->phone)
        {
            printf("\nEntered phone number alredy exists !!!\n\n");
            return 0;
        }
    return 1;
}

int validmail(Contact *mail,int count)
{
    char temp[256],*token;
    strcpy(temp,(mail+count)->email);
    token=strtok(temp,"@");
    if(token == NULL)
    {
        printf("\nINVALID MAIL ID :- mail id must contain a '@' charecter !!!\n\n");
        return 0;
    }
    int length=strlen(token);
    if(token[length-1]=='.' || token[0]=='.')
    {
        printf("\nINVALID MAIL ID :- Username of mail id can't start or end with '.'!!\n\n");
        return 0;
    }
    if(length<8 || length>64)
    {
        printf("\nINVALID MAIL ID :- Username of mail atleast contain 8 characters and should be less than 65 charecters !!!\n\n");
        return 0;
    }
    for(int i=0;i<length;i++)
    {
        if((token[i]>='a' && token[i]<='z') || token[i]=='.' || (token[i]>='0' && token[i]<='9'))
        {
            if(token[i]=='.' && token[i+1]=='.')
            {
                printf("\nINVALID MAIL ID :- Username of mail can't have adjacent '.' character!!\n\n");
                return 0;
            }
        }
        else
        {
            printf("\nINVALID MAIL ID :- Username of mail can only have lower case, digits and '.' character !!\n\n");
            return 0;
        }
    }
    token=token+length+1;
    length=strlen(token);
    if(token[length-1]=='.' || token[0]=='.')
    {
        printf("\nINVALID MAIL ID :- Each domain of mail atleast contain 1 characters\n\n");
        return 0;
    }
    if(length<3)
    {
        printf("\nINVALID MAIL ID :- Mail id should contain atleast two domain part !! \n\n");
        return 0;
    }
    int nch=0;
    for(int i=0;i<length;i++)
    {
        if((token[i]>='a' && token[i]<='z') || (token[i]>='0' && token[i]<='9'))
            nch++;
        else if(token[i]=='.')
        {
            if(nch<1 || nch>63)
            {
                printf("\nINVALID MAIL ID :- Domain of mail atleast contain 1 characters and should be less than 64 charecters !!\n\n");
                return 0;
            }
            nch=0;
        }
        else
        {
            printf("\nINVALID MAIL ID :- Mail id can only have digits, lower case character,'.' and one '@' !!\n\n");
            return 0;
        }
    }

    for(int i=0;i<count;i++)
    {
         if(strcmp((mail+i)->email,(mail+count)->email)==0)
        {
            printf("\nEntered email already exist !!\n\n");
            return 0;
        }
    }
    return 1;
}
unsigned long int my_atoi(char *s)
{
    unsigned long int num = 0;
    char *temp=s;
    while(*s)
    {
        if(*s>='0' && *s<='9')
            num=num*10+(*s-'0');
        else if((s[0]=='-' || s[0]=='+') && (&temp[0])==s)
            num=num;
        else if(num==0)
            return 0;
        s++;
    }
    if(temp[0]=='-')
        return -1*num;
    else
        return num;
}