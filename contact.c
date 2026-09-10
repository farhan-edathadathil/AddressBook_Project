/*
FARHAN E

09/09/2026

PROJECT 1 :- ADDRESSBOOK
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    /*
    listContacts - Lists all contacts based on the selected sorting criteria.

    The function allows the user to choose how the contacts should be
    listed.

    The available sorting options are:

        1. List contacts by name.
        2. List contacts by phone number.
        3. List contacts by email address.

    Based on the user's choice, the corresponding sorting function is
    called before displaying the contacts:

        sortName() - Sorts contacts alphabetically by name.
        sortNum()  - Sorts contacts in ascending order by phone number.
        sortMail() - Sorts contacts alphabetically by email address.

    After sorting, all contacts in the address book are displayed using
    the display() function.

    When contacts are sorted by phone number or email address, the
    contacts are sorted by name again after displaying them.

    Parameters:
        addressBook - Pointer to the AddressBook structure containing
                        the contacts to be sorted and displayed.

    Return:
        None.
    */
    int sortchoice,ch;
    int arr[MAX_CONTACTS]={0};
    printf("\n How do you want to List contacts ?\n\n");
    printf("1. List by name\n");
    printf("2. List by phone number\n");
    printf("3. List by email\n");
    printf("\nEnter your choice : ");
    if(scanf("%d",&sortchoice)==0)
    {
        printf("\nInvalid input !!\n\n");
        while ((ch = getchar()) != '\n' && ch != EOF);
        return;
    }
    ch = getchar();
    if (ch != '\n' && ch != EOF)
    {
        printf("\nInvalid input !!\n\n");

        while ((ch = getchar()) != '\n' && ch != EOF);
        return;
    }
    switch(sortchoice)
    {
        case 1:
            sortName(addressBook);
            printf("\nSorted All contacts by Name :\n");
            printf("\n%-25s  %-10s  %s\n","NAME ","PHONE no. ","EMAIL");
            for(int i=0;i<addressBook->contactCount;i++)
                display(addressBook->contacts+i);
            break;
        case 2:
            sortNum(addressBook);
            printf("\nSorted All contacts by Phone Number :\n");
            printf("\n%-25s  %-10s  %s\n","NAME ","PHONE no. ","EMAIL");
            for(int i=0;i<addressBook->contactCount;i++)
                display(addressBook->contacts+i);
            sortName(addressBook);
            break;
        case 3:
            sortMail(addressBook);
            printf("\nSorted All contacts by Mail Id :\n");
            printf("\n%-25s  %-10s  %s\n","NAME ","PHONE no. ","EMAIL");
            for(int i=0;i<addressBook->contactCount;i++)
                display(addressBook->contacts+i);
            sortName(addressBook);
            break;
        default:
            printf("\nInvalid input !!\n\n");

    }  
}

void initialize(AddressBook *addressBook) 
{
    /*
    initialize - Initializes the address book and loads saved contacts.

    The function prepares the AddressBook structure for use.

    Initially, the contactCount value is set to 0.

    The function then displays a loading progress indicator while the
    contacts are being loaded.

    After the loading process, loadContactsFromFile() is called to load
    previously saved contacts from a file into the address book.

    Parameters:
        addressBook - Pointer to the AddressBook structure to be
                        initialized.

    Return:
        None.
    */
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    for(int i=0;i<=100;i++)
    {
        printf("Loading contacts from files........%d%%]\r",i);
        usleep(10000);
        fflush(stdout);
    }
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) 
{
    if(saveContactsToFile(addressBook)!=1)
        return; // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

void createContact(AddressBook *addressBook)
{
    /*
    createContact - Creates and adds a new contact to the address book.
    
    The function checks whether there is available space in the address book.
    If space is available, it obtains the name, phone number, and email address
    from the user.
    
    Each input is validated using the corresponding input function:

        name_input() - Validates the contact name.
        num_input()  - Validates the phone number.
        mail_input() - Validates the email address.

    The function also checks for duplicate phone numbers and email addresses
    using num_search() and mail_search().
    
    Valid contact information is first stored temporarily in
    addressBook->temp. After all information has been successfully validated,
    the data is copied to the next available element of the contacts array.
    
    The newly created contact is displayed, and contactCount is incremented.
    
    Parameters:
        addressBook - Pointer to the AddressBook structure in which the
                        new contact will be stored.
    
    Return:
        None.
    */
    char ch;
    if(addressBook->contactCount<MAX_CONTACTS)
    {
        name:
        if(name_input((addressBook->temp).name)==0)
            goto name;
        else
            strcpy((addressBook->contacts+(addressBook->contactCount))->name,(addressBook->temp).name);
        
        num:
        if(num_input(&((addressBook->temp).phone))==0)
            goto num;
        else
        {
            if(num_search(addressBook,(*addressBook).contacts,&((addressBook->temp).phone))!=NULL)
            {
                printf("\nEntered phone number alredy exists !!!\n\n");
                goto num;
            }
            (addressBook->contacts+(addressBook->contactCount))->phone=(addressBook->temp).phone;
        }
        
        mail:
        if(mail_input((addressBook->temp).email)==0)
            goto mail;
        else
        {
            if(mail_search(addressBook,(*addressBook).contacts,(addressBook->temp).email)!=NULL)
            {
                printf("\nEntered email already exist !!\n\n");
                goto mail;
            }
            strcpy((addressBook->contacts+(addressBook->contactCount))->email,(addressBook->temp).email);
        }

        printf("\n%-25s  %-10s  %s\n","NAME ","PHONE no. ","EMAIL");
        display((*addressBook).contacts+addressBook->contactCount);
        printf("\nContact successfully saved !!\n\n");
        addressBook->contactCount++;
    }
    else
        printf("\nAddress book memmory full, you can edit,search and delete contacts !!\n\n");

}

int searchContact(AddressBook *addressBook) 
{
    /*
    searchContact - Searches for contacts in the address book.

    The function allows the user to search for contacts using one of the
    following methods:

        1. Search by name.
        2. Search by phone number.
        3. Search by email address.

    Based on the user's choice, the function obtains the search input and
    validates it before performing the search.

    The corresponding search function is used to find matching contacts:

        name_search() - Searches for contacts using a name.
        num_search()  - Searches for contacts using a phone number.
        mail_search() - Searches for contacts using an email address.

    All matching contacts are displayed along with their index numbers.

    Parameters:
        addressBook - Pointer to the AddressBook structure containing
                        the contacts to be searched.

    Return:
        The number of matching contacts found.

        0 if no matching contact is found or an invalid input is entered.
    */
    int choice,i,num_result=0;
    char ch;
    Contact *temp;
    printf("\nwhat you want to search \n\n");
    printf("1. Search by name\n");
    printf("2. Search by phone number\n");
    printf("3. Search by email\n");
    printf("\nEnter your choice : ");
    if(scanf("%d",&choice)==0)
    {
        printf("\nInvalid input !!\n\n");
        while ((ch = getchar()) != '\n' && ch != EOF);
        return 0;
    }
    
    ch = getchar();
    if (ch != '\n' && ch != EOF)
    {
        printf("\nInvalid input !!\n\n");

        while ((ch = getchar()) != '\n' && ch != EOF);
        return 0;
    }
    switch(choice)
    {
        case 1:
            if(name_input((addressBook->temp).name)==0)
            {
                printf("\nNot found !!\n\n");
                return 0;
            }
            temp=name_search(addressBook,(*addressBook).contacts ,(addressBook->temp).name);
            if(temp==NULL)
                printf("\nName not found !!\n\n");
            else
            {
                printf("\nName found !!\n\n");
                printf("%-5s %-25s  %-10s  %s\n","INDEX","NAME ","PHONE no. ","EMAIL");
                while(temp)
                {
                    num_result++;
                    printf("%-5ld ",(temp-(addressBook->contacts))+1);
                    display(temp);
                    temp=name_search(addressBook,NULL,(addressBook->temp).name);
                }
            }
            break;

        case 2:
            printf("Enter the phone number : ");
            char num[12];
            if(fgets(num,12,stdin) != NULL)
            {
                if (strchr(num, '\n') == NULL)
                {
                    printf("\nPhone no. not found :- Input must be less than 10 digits!!\n\n");
                    while ((ch = getchar()) != '\n' && ch != EOF);
                    return 0;
                }  
                *(strchr(num, '\n'))='\0';
            }
            i=0;
            while(num[i])
            {
                if((num[i]>='0' && num[i]<='9'))
                    i++;
                else
                {
                    printf("\nPhone no. not found !!\n\n");
                    return 0;
                }
            }
            (addressBook->temp).phone=my_atoi(num);
            temp=num_search(addressBook,(*addressBook).contacts ,&((addressBook->temp).phone));
            if(temp==NULL)
                printf("\nPhone no. not found !!\n\n");
            else
            {
                printf("\nPhone no. found !!\n\n");
                 printf("%-5s %-25s  %-10s  %s\n","INDEX","NAME ","PHONE no. ","EMAIL");
                while(temp)
                {
                    num_result++;
                    printf("%-5ld ",(temp-(addressBook->contacts))+1);
                    display(temp);
                    temp=num_search(addressBook,NULL,&(addressBook->temp).phone);
                }
            }
            break;

        case 3:
            printf("Enter the mail id : ");
            if(fgets((addressBook->temp).email,256,stdin) != NULL)
            {
                if (strchr((addressBook->temp).email, '\n') == NULL)
                {
                    printf("\nEmail id not found:- Input may be too long!\n\n");
                    while ((ch = getchar()) != '\n' && ch != EOF);
                    return 0;
                }
                *(strchr((addressBook->temp).email, '\n'))='\0';
            }
            i=0;
            while((addressBook->temp).email[i])
            {
                if(((addressBook->temp).email[i]>='a' && (addressBook->temp).email[i]<='z')||((addressBook->temp).email[i]>='A' && (addressBook->temp).email[i]<='Z'))
                    i++;
                else if(((addressBook->temp).email[i]>='0' && (addressBook->temp).email[i]<='9') || (addressBook->temp).email[i]=='.' || (addressBook->temp).email[i]=='@')
                    i++;
                else
                {
                    printf("\nEmail id not found !!\n\n");
                    return 0;
                }
            }
            temp=mail_search(addressBook,(*addressBook).contacts ,(addressBook->temp).email);
            if(temp==NULL)
                printf("\nEmail id not found !!\n\n");
            else
            {
                printf("\nEmail id found !!\n\n");
                 printf("%-5s %-25s  %-10s  %s\n","INDEX","NAME ","PHONE no. ","EMAIL");
                while(temp)
                {
                    num_result++;
                    printf("%-5ld ",(temp-(addressBook->contacts))+1);
                    display(temp);
                    temp=mail_search(addressBook,NULL,(addressBook->temp).email);
                }
            }
            break;

        default:
            printf("\nInvalid choice \n");
            return 0;
    }
    return num_result;
 
}

void editContact(AddressBook *addressBook)
{
	/*
    editContact - Edits the information of an existing contact.

    The function first allows the user to search for the contact that
    needs to be edited.

    The searchContact() function is used to find and display matching
    contacts.

    The user selects a contact by entering its index and confirms the
    selected contact before editing.

    The function provides the following editing options:

        1. Edit name.
        2. Edit phone number.
        3. Edit email address.

    The new name, phone number, or email address is validated before
    updating the selected contact.

    Duplicate phone numbers and email addresses are checked using
    num_search() and mail_search() before updating the contact.

    Parameters:
        addressBook - Pointer to the AddressBook structure containing
                        the contact to be edited.

    Return:
        None.
    */
    int index;
    char ch,edit;
    printf("search what do you want edit !!\n");
    int ret=searchContact(addressBook);
    if(ret==0)
        return;
    retry:
    printf("\nEnter the index from above that you want to edit: ");
    if(scanf("%d",&index)==0)
    {
        printf("\n\nInvalid index !!\n");
        while ((ch = getchar()) != '\n' && ch != EOF);
        goto retry;
    }
    ch = getchar();
    if (ch != '\n' && ch != EOF)
    {
        printf("\nInvalid input !!\n\n");
        while ((ch = getchar()) != '\n' && ch != EOF);
        goto retry;
    }
    if(index<0 || index>addressBook->contactCount)
    {
        printf("\n\nInvalid index !!\n");
        goto retry;
    }
    again:
    printf("\n!! Confirm that the given contact wants to edit >> !!\n");
    printf("\n%-25s  %-10s  %s\n","NAME ","PHONE no. ","EMAIL");
    display(addressBook->contacts+(index-1));
    printf("\nEnter (YES -Y or NO -N) : ");
    scanf(" %c",&edit);
    ch = getchar();
    if (ch != '\n' && ch != EOF)
    {
        printf("\nInvalid input !!\n\n");
        while ((ch = getchar()) != '\n' && ch != EOF);
        goto again;
    }
    if(edit=='Y' || edit=='y')
    {
        int choice;
        try:
        printf("\nwhat you want to edit in the above contact ? \n\n");
        printf("1. Edit name\n");
        printf("2. Edit phone number\n");
        printf("3. Edit email\n");
        printf("\nEnter your choice : ");
        if(scanf("%d",&choice)==0)
        {
            printf("\nInvalid input !!\n\n");
            while ((ch = getchar()) != '\n' && ch != EOF);
            goto try;
        }
        ch = getchar();
        if (ch != '\n' && ch != EOF)
        {
            printf("\nInvalid input !!\n\n");
            while ((ch = getchar()) != '\n' && ch != EOF);
            goto try;
        }
        switch(choice)
        {
            case 1:
                name:
                if(name_input((addressBook->temp).name)==0)
                    goto name;
                else
                    strcpy((addressBook->contacts+(index-1))->name,(addressBook->temp).name);
                printf("\nName updated successfully !!\n");
                break;

            case 2:
                num:
                if(num_input(&((addressBook->temp).phone))==0)
                    goto num;
                else
                {
                    if(num_search(addressBook,addressBook->contacts,&((addressBook->temp).phone))!=NULL)
                    {
                        printf("\nEntered phone number alredy exists !!!\n\n");
                        goto num;
                    }
                    (addressBook->contacts+(index-1))->phone=(addressBook->temp).phone;
                }
                printf("\nPhone number updated successfully !!\n");
                break;

            case 3:
                mail:
                if(mail_input((addressBook->temp).email)==0)
                    goto mail;
                else
                {
                    if(mail_search(addressBook,addressBook->contacts,(addressBook->temp).email)!=NULL)
                    {
                        printf("\nEntered email already exist !!\n\n");
                        goto mail;
                    }
                    strcpy((addressBook->contacts+(index-1))->email,(addressBook->temp).email);
                }
                printf("\nEmail updated successfully !!\n");
                break;

            default:
                printf("\nInvalid input !!\n\n");
                goto try;
        }
        printf("\n%-25s  %-10s  %s\n","NAME ","PHONE no. ","EMAIL");
        display(addressBook->contacts+index-1);
    }
    else if(edit=='N' || edit=='n')
    {
        printf("\nContact not edited !!\n");
        return;
    }
    else
    {
        printf("\nINVALID INPUT !!\n");
        goto again;
    }  
}

void deleteContact(AddressBook *addressBook)
{
	/*
    deleteContact - Deletes an existing contact from the address book.

    The function first allows the user to search for the contact that
    needs to be deleted.

    The searchContact() function is used to find and display matching
    contacts.

    The user selects a contact by entering its index and confirms the
    selected contact before deletion.

    When the user confirms the deletion, all contacts after the selected
    contact are shifted one position to the left in the contacts array.

    The contactCount value is then decremented to reflect the removal of
    the contact from the address book.

    If the user chooses not to confirm the deletion, the contact remains
    unchanged.

    Parameters:
        addressBook - Pointer to the AddressBook structure containing
                        the contact to be deleted.

    Return:
        None.
    */
    int index;
    char ch,delete;
    printf("search what do you want delete !!\n");
    int ret=searchContact(addressBook);
    if(ret==0)
        return;
    retry:
    printf("\nEnter the index from above that you want to delete : ");
    if(scanf("%d",&index)==0)
    {
        printf("\n\nInvalid index !!\n");
        while ((ch = getchar()) != '\n' && ch != EOF);
        goto retry;
    }
    ch = getchar();
    if (ch != '\n' && ch != EOF)
    {
        printf("\nInvalid input !!!\n\n");
        while ((ch = getchar()) != '\n' && ch != EOF);
        goto retry;
    }
    if(index<0 || index>addressBook->contactCount)
    {
        printf("\n\nInvalid index !!\n");
        goto retry;
    }
    again:
    printf("\n!! Confirm that the given contact wants to delete >> !!\n");
    printf("\n%-25s  %-10s  %s\n","NAME ","PHONE no. ","EMAIL");
    display(addressBook->contacts+(index-1));
    printf("\nEnter (YES -Y or NO -N) : ");
    scanf(" %c",&delete);
    ch = getchar();
    if (ch != '\n' && ch != EOF)
    {
        printf("\nInvalid input !!!\n\n");
        while ((ch = getchar()) != '\n' && ch != EOF);
        goto again;
    }
    if(delete=='Y' || delete=='y')
    {
        for(int i=index;i<addressBook->contactCount;i++)
        {
            addressBook->contacts[i-1]=addressBook->contacts[i];
        }
        --addressBook->contactCount;
        for(int i=0;i<=100;i++)
        {
            printf("Deleting........%d%%]\r",i);
            usleep(8000);
            fflush(stdout);
        }
        printf("\n\nContact deleted successfully !!\n");
    }
    else if(delete=='N' || delete=='n')
    {
        printf("\nContact not deleted !!\n");
        return;
    }
    else
    {
        printf("\nINVALID INPUT !!\n");
        goto again;
    }
}

int validname(char *name)
{
    /*
    validname - Validates a contact name.

    The function checks whether the given name is valid.

    The name must not be empty. Each character in the name must be either
    an uppercase alphabet, a lowercase alphabet, or a space character.

    If an invalid character is found, an error message is displayed and
    the function returns 0.

    Parameters:
        name - Pointer to the null-terminated name string to be validated.

    Return:
        1 - The name is valid.
        0 - The name is invalid.
    */
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
            printf("\nINVALID NAME :- name can only have alphabets\n\n");
            return 0;
        }
    }
    return 1;
}

int validnum(long unsigned int *phone)
{
    /*
    validnum - Validates a phone number.

    The function checks whether the given phone number contains exactly
    10 digits and whether its first digit is not zero.

    The phone number must be within the range of 1000000000 to
    9999999999.

    If the phone number is outside this range, an error message is
    displayed and the function returns 0.

    Parameters:
        phone - Pointer to the phone number to be validated.

    Return:
        1 - The phone number is valid.
        0 - The phone number is invalid.
    */
    if(*phone < 1000000000L || *phone > 9999999999L)
    {
        printf("\nINVALID PHONE NUMBER :- must contain 10 digits and first digit can't be zero !!\n\n");
        return 0;
    }
    return 1;
}

int validmail(char *email)
{
    /*
    validmail - Validates an email address.

    The function validates the format of the given email address.

    The email address must contain a username followed by the '@'
    character and a domain.

    Username validation rules:

        - Must contain at least 8 characters.
        - Must contain fewer than 65 characters.
        - Must not start with a '.' character.
        - Must not end with a '.' character.
        - Must not contain consecutive '.' characters.
        - Can contain only lowercase alphabets, digits, and '.'.

    Domain validation rules:

        - Must contain at least two domain parts separated by '.'.
        - Each domain part must contain at least one character.
        - Each domain part must contain fewer than 64 characters.
        - Can contain only lowercase alphabets, digits, and '.'.

    The function displays an appropriate error message when an invalid
    email format is detected.

    Parameters:
        email - Pointer to the null-terminated email string to be validated.

    Return:
        1 - The email address is valid.
        0 - The email address is invalid.
    */
    char temp[256],*token;
    strcpy(temp,email);
    token=strtok(temp,"@");
    if (token == NULL)
{
    printf("\nINVALID MAIL ID :- mail id can't be empthy !!!\n\n");
    return 0;
}
    int length=strlen(token);
    if(email[length]!='@')
    {
        printf("\nINVALID MAIL ID :- mail id must contain a '@' charecter !!!\n\n");
        return 0;
    }
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
    int nch=0,ndot=0;
    for(int i=0;i<length;i++)
    {
        if((token[i]>='a' && token[i]<='z') || (token[i]>='0' && token[i]<='9'))
            nch++;
        else if(token[i]=='.')
        {
            ndot++;
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
    if(ndot==0)
    {
        printf("\nINVALID MAIL ID :- Mail id should contain atleast two domain part !! \n\n");
        return 0;
    }
    return 1;
}

int name_input(char *name)
{
    /*
    name_input - Reads and validates a contact name from the user.

    The function prompts the user to enter a contact name and stores
    the input in the specified character array.

    The function uses fgets() to read the input. If the input exceeds
    the allowed buffer size, the remaining characters are removed from
    the input buffer and an error message is displayed.

    The newline character added by fgets() is removed before validation.

    The entered name is validated using validname().

    Parameters:
        name - Pointer to the character array where the contact name
                will be stored.

    Return:
        1 - The name was successfully read and validated.
        0 - The input or name validation failed.
    */
    char ch;
    printf("Enter the name of contact : ");
    if(fgets(name,25,stdin) != NULL)
    {
        if (strchr(name, '\n') == NULL)
        {
            printf("\nINVALID :- Input may be too long!\n\n");
            while ((ch = getchar()) != '\n' && ch != EOF);
            return 0;
        }
        *(strchr(name, '\n'))='\0';
        if(validname(name)==0)
            return 0;
        return 1;
    }
    else 
        return 0;
    
}

int num_input(long unsigned int *phone)
{
    /*
    num_input - Reads and validates a phone number from the user.

    The function prompts the user to enter a 10-digit phone number.

    The input is first read as a character string using fgets(). This
    allows the function to check whether the entered input exceeds the
    expected number of characters.

    The remaining characters are removed from the input buffer if the
    input is too long.

    The entered string is converted to an unsigned long integer using
    my_atoi().

    The converted phone number is validated using validnum().

    Parameters:
        phone - Pointer to the unsigned long integer where the valid
                phone number will be stored.

    Return:
        1 - The phone number was successfully read and validated.
        0 - The input or phone number validation failed.
    */
    char temp[12],ch;
    printf("Enter the 10 digit phone number : ");
        if(fgets(temp,12,stdin) != NULL)
        {
            if (strchr(temp, '\n') == NULL)
            {
                printf("\nINVALID PHONE NUMBER :- Input must be 10 digits!\n\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
                return 0;
            }
            *phone=my_atoi(temp);
            if(validnum(phone)==0)
                return 0;
            return 1;
        }
        else
            return 0;
        
}

int mail_input(char *email)
{
    /*
    mail_input - Reads and validates an email address from the user.

    The function prompts the user to enter an email address and stores
    the input in the specified character array.

    The function uses fgets() to read the email address. If the input
    exceeds the allowed buffer size, the remaining characters are
    removed from the input buffer and an error message is displayed.

    The newline character added by fgets() is removed before validation.

    The entered email address is validated using validmail().

    Parameters:
        email - Pointer to the character array where the email address
                will be stored.

    Return:
        1 - The email address was successfully read and validated.
        0 - The input or email validation failed.
    */
    char ch;
    printf("Enter the mail id : ");
    if(fgets(email,256,stdin) != NULL)
    {
        if (strchr(email, '\n') == NULL)
        {
            printf("\nINVALID MAIL ID :- Input may be too long!\n\n");
            while ((ch = getchar()) != '\n' && ch != EOF);
            return 0;
        }
        
        *(strchr(email, '\n'))='\0';
        if(validmail(email)==0)
            return 0;
        return 1;
    }
    else 
        return 0;
}

Contact *num_search(AddressBook *addressBook,Contact *arr,long unsigned int *phone)
{
    /*
    num_search - Searches for a contact using a phone number.

    The function searches through the contacts in the address book for a
    phone number that matches the given phone number.

    The phone number is converted into a string using my_itoa() before
    performing the comparison. This allows the function to perform a
    partial phone number search.

    If the arr parameter is not NULL, the address book pointer is set to
    the given starting address. This allows the function to continue
    searching from a previously used location.

    The function compares the entered phone number with each contact's
    phone number using strncasecmp().

    When a matching contact is found, a pointer to that contact is
    returned. The address book pointer is then moved to the next contact.

    Parameters:
        addressBook - Pointer to the AddressBook structure containing
                        the contacts to be searched.

        arr - Pointer to the contact from which the search should begin.
                If NULL, the search continues from the current pointer
                location.

        phone - Pointer to the phone number to be searched.

    Return:
        Pointer to the matching Contact if a phone number is found.

        NULL if no matching phone number is found.
    */
    char strnum[11];
    my_itoa(*phone,strnum);
    if(arr!=NULL)
        addressBook->ptr=arr;
    Contact *end = addressBook->contacts + addressBook->contactCount;
    while(addressBook->ptr<end)
    {
        char strphone[11];
        my_itoa((addressBook->ptr)->phone,strphone);
        if(strncasecmp(strphone,strnum,strlen(strnum))==0)
        {
            return addressBook->ptr++;
        }
        addressBook->ptr++;
    }
    return NULL;
}

Contact *mail_search(AddressBook *addressBook,Contact *arr,char *email)
{
    /*
    mail_search - Searches for a contact using an email address.

    The function searches through the contacts in the address book for an
    email address that matches the given email string.

    If the arr parameter is not NULL, the address book pointer is set to
    the given starting address. This allows the function to continue
    searching from a previously used location.

    The function compares the entered email address with each contact's
    email address using strncasecmp().

    The comparison is case-insensitive and compares the number of
    characters present in the entered email string. This allows partial
    email searches.

    When a matching contact is found, a pointer to that contact is
    returned. The address book pointer is then moved to the next contact.

    Parameters:
        addressBook - Pointer to the AddressBook structure containing
                        the contacts to be searched.

        arr - Pointer to the contact from which the search should begin.
                If NULL, the search continues from the current pointer
                location.

        email - Pointer to the email string to be searched.

    Return:
        Pointer to the matching Contact if an email address is found.

        NULL if no matching email address is found.
    */
    if(arr!=NULL)
        addressBook->ptr=arr;
    Contact *end = addressBook->contacts + addressBook->contactCount;
    while(addressBook->ptr<end)
    {
        if(strncasecmp((addressBook->ptr)->email,email,strlen(email))==0)
        {
            return addressBook->ptr++;
        }
        addressBook->ptr++;
    }
    return NULL;
}

Contact *name_search(AddressBook *addressBook,Contact *arr,char *name)
{
    /*
    name_search - Searches for a contact using a name.

    The function searches through the contacts in the address book for a
    name that matches the given name string.

    If the arr parameter is not NULL, the address book pointer is set to
    the given starting address. This allows the function to continue
    searching from a previously used location.

    The function compares the entered name with each contact's name using
    strncasecmp().

    The comparison is case-insensitive and compares the number of
    characters present in the entered name string. This allows partial
    name searches.

    When a matching contact is found, a pointer to that contact is
    returned. The address book pointer is then moved to the next contact.

    Parameters:
        addressBook - Pointer to the AddressBook structure containing
                        the contacts to be searched.

        arr - Pointer to the contact from which the search should begin.
                If NULL, the search continues from the current pointer
                location.

        name - Pointer to the name string to be searched.

    Return:
        Pointer to the matching Contact if a name is found.

        NULL if no matching name is found.
    */
    if(arr!=NULL)
        addressBook->ptr=arr;
    Contact *end = addressBook->contacts + addressBook->contactCount;
    while(addressBook->ptr<end)
    {
         if(strncasecmp((addressBook->ptr)->name,name,strlen(name))==0)
        {
            return addressBook->ptr++;
        }
        addressBook->ptr++;
    }
    return NULL;

}

void sortName(AddressBook *addressBook)
{
    /*
    sortName - Sorts contacts alphabetically by name.

    The function sorts all contacts in the address book according to
    their names in ascending alphabetical order.

    The sorting is performed using the bubble sort algorithm. Adjacent
    contacts are compared using strcasecmp(), which performs a
    case-insensitive string comparison.

    When the name of a contact is alphabetically greater than the name
    of the next contact, the complete Contact structures are exchanged.

    Parameters:
        addressBook - Pointer to the AddressBook structure containing
                        the contacts to be sorted.

    Return:
        None.
    */
    Contact temp;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        for(int j=0;j<addressBook->contactCount-1;j++)
        {
            if(strcasecmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)
            {
                temp=addressBook->contacts[j];
                addressBook->contacts[j]=addressBook->contacts[j+1];
                addressBook->contacts[j+1]=temp;
            }
            
        }
    }

}

void sortNum(AddressBook *addressBook)
{
    /*
    sortNum - Sorts contacts in ascending order by phone number.

    The function sorts all contacts in the address book according to
    their phone numbers in ascending numerical order.

    The sorting is performed using the bubble sort algorithm. Adjacent
    phone numbers are compared, and their complete Contact structures
    are exchanged when they are in the wrong order.

    Parameters:
        addressBook - Pointer to the AddressBook structure containing
                        the contacts to be sorted.

    Return:
        None.
    */
    Contact temp;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        for(int j=0;j<addressBook->contactCount-1;j++)
        {
            if(addressBook->contacts[j].phone>addressBook->contacts[j+1].phone)
            {
                temp=addressBook->contacts[j];
                addressBook->contacts[j]=addressBook->contacts[j+1];
                addressBook->contacts[j+1]=temp;
            }
            
        }
    }

}

void sortMail(AddressBook *addressBook)
{
    /*
    sortMail - Sorts contacts alphabetically by email address.

    The function sorts all contacts in the address book according to
    their email addresses in ascending alphabetical order.

    The sorting is performed using the bubble sort algorithm. Adjacent
    email addresses are compared using strcasecmp(), which performs a
    case-insensitive string comparison.

    When an email address is alphabetically greater than the next email
    address, the complete Contact structures are exchanged.

    Parameters:
        addressBook - Pointer to the AddressBook structure containing
                        the contacts to be sorted.

    Return:
        None.
    */
    Contact temp;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        for(int j=0;j<addressBook->contactCount-1;j++)
        {
            if(strcasecmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0)
            {
                temp=addressBook->contacts[j];
                addressBook->contacts[j]=addressBook->contacts[j+1];
                addressBook->contacts[j+1]=temp;
            }
            
        }
    }

}

void display(Contact *contact)
{   
    /*
    display - Displays the information of a contact.

    The function prints the name, phone number, and email address of
    the specified contact in a formatted manner.

    Parameters:
        contact - Pointer to the Contact structure whose information
                    will be displayed.

    Return:
        None.
    */
    printf("%-25s  %lu  %s\n",contact->name,contact->phone,contact->email);
}

unsigned long int my_atoi(char *s)
{
    /*
    my_atoi - Converts a numeric string into an unsigned long integer.

    The function reads the characters of the given string and converts
    each valid digit into its corresponding numeric value.

    The numeric value is constructed by multiplying the current value
    by 10 and adding the value of the next digit.

    The function also checks for an optional '+' or '-' sign at the
    beginning of the string.

    If an invalid character is encountered before a valid number is
    formed, the function returns 0.

    Parameters:
        s - Pointer to the null-terminated string to be converted.

    Return:
        The converted numeric value as an unsigned long integer.

        0 if the input cannot be converted into a valid number.
    */
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

void my_itoa(long unsigned int num, char str[])
{
    /*
    my_itoa - Converts an unsigned long integer into a numeric string.

    The function converts the given unsigned long integer into its
    equivalent null-terminated character string.

    If the number is zero, the function directly stores the character
    '0' in the output string.

    For other numbers, the digits are initially obtained in reverse
    order and stored in the variable rev. The digits are then extracted
    from rev and stored in the output string in their correct order.

    The resulting string is terminated with the null character.

    Parameters:
        num - The unsigned long integer to be converted.

        str - Character array where the converted numeric string will
                be stored.

    Return:
        None.
    */
    if(num==0)
        {
            *str='0';
            str++;
            *str='\0';
            return;
        }
    
    if(num<0)
    {
        *str='-';
        str++;
        num=num*-1;
    }
    long unsigned int rev=0;
    while(num!=0)
    {
        rev=rev*10+num%10;
        num=num/10;
    }
    while(rev!=0)
    {
        *str=(rev%10)+48;
        rev=rev/10;
        str++;
    }
    *str='\0';
    
}