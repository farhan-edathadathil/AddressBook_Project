#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[25];
    unsigned long int phone;
    char email[256];
} Contact;

typedef struct {
    Contact contacts[100];
    Contact temp;
    int contactCount;
    Contact *ptr;
} AddressBook;

void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
int validname(char *name);
int validnum(Contact *arr,int count,long unsigned int *phone);
int validmail(Contact *arr,int count,char *email);
unsigned long int my_atoi(char *s);
void my_itoa(long unsigned int num, char str[]);
int name_input(char *name);
int num_input(Contact *arr,int count,long unsigned int *phone);
int mail_input(Contact *arr,int count,char *email);
Contact *name_search(AddressBook *addressBook,Contact *arr,char *name);
Contact *num_search(AddressBook *addressBook,Contact *arr,long unsigned int *phone);
Contact *mail_search(AddressBook *addressBook,Contact *arr,char *email);
void display(Contact *contact);
#endif
