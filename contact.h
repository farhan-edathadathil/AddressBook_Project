#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct 
{
    char name[25];
    unsigned long int phone;
    char email[256];
} Contact;

typedef struct 
{
    Contact contacts[100];
    int contactCount;
    Contact temp;     //to store temporary data to validate,search,edit etc.
    Contact *ptr;     //to store the while searching.
} AddressBook;

void createContact(AddressBook *addressBook);
void saveAndExit(AddressBook *addressBook);
int searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
int validname(char *name);
int validnum(long unsigned int *phone);
int validmail(char *email);
int name_input(char *name);
int num_input(long unsigned int *phone);
int mail_input(char *email);
Contact *name_search(AddressBook *addressBook,Contact *arr,char *name);
Contact *num_search(AddressBook *addressBook,Contact *arr,long unsigned int *phone);
Contact *mail_search(AddressBook *addressBook,Contact *arr,char *email);
void sortName(AddressBook *addressBook);
void sortNum(AddressBook *addressBook);
void sortMail(AddressBook *addressBook);
void display(Contact *contact);
unsigned long int my_atoi(char *s);
void my_itoa(long unsigned int num, char str[]);
#endif
