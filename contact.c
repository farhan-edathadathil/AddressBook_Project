#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
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
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
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
    /* Define the logic for search */
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
    getchar();
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
	/* Define the logic for Editcontact */
    int countbackup;
    int index;
    char ch;
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
    scanf(" %c",&ch);
    if(ch=='Y' || ch=='y')
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
        getchar();
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
    else if(ch=='N' || ch=='n')
    {
        printf("\nContact not edited !!\n");
        return;
    }
    else
    {
        printf("\nINVALID INPUT !!\n");
        while ((ch = getchar()) != '\n' && ch != EOF);
        goto again;
    }  
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int index;
    char ch;
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
    scanf(" %c",&ch);
    //getchar();
    if(ch=='Y' || ch=='y')
    {
        for(int i=index;i<addressBook->contactCount;i++)
        {
            addressBook->contacts[i-1]=addressBook->contacts[i];
        }
        addressBook->contactCount--;
        for(int i=0;i<=100;i++)
        {
            printf("Deleting........%d%%]\r",i);
            usleep(8000);
            fflush(stdout);
        }
        printf("\nContact deleted successfully !!\n");
    }
    else if(ch=='N' || ch=='n')
    {
        printf("\nContact not deleted !!\n");
        return;
    }
    else
    {
        printf("\nINVALID INPUT !!\n");
        while ((ch = getchar()) != '\n' && ch != EOF);
        goto again;
    }
    // for(int i=0;i<addressBook->contactCount;i++)
    //     display(addressBook->contacts+i); 
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

int validnum(long unsigned int *phone)
{
    if(*phone < 1000000000L || *phone > 9999999999L)
    {
        printf("\nINVALID PHONE NUMBER :- must contain 10 digits and first digit can't be zero !!\n\n");
        return 0;
    }
    return 1;
}

int validmail(char *email)
{
    char temp[256],*token;
    strcpy(temp,email);
    token=strtok(temp,"@");
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
    char strnum[11];
    my_itoa(*phone,strnum);
    if(arr!=NULL)
        addressBook->ptr=arr;
    for(int i=0;i<addressBook->contactCount;i++)
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
    if(arr!=NULL)
        addressBook->ptr=arr;
    for(int i=0;i<addressBook->contactCount;i++)
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
    if(arr!=NULL)
        addressBook->ptr=arr;
    for(int i=0;i<addressBook->contactCount;i++)
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
    printf("%-25s  %lu  %s\n",contact->name,contact->phone,contact->email);
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

void my_itoa(long unsigned int num, char str[])
{
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
    int rev=0;
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