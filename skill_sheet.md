# Address Book Management System – Skill Sheet

## 1. Name

**Address Book Management System**

**Programming Language:** C
**Interface:** Command-Line Interface (CLI)
**Storage:** CSV File Handling

---

# 2. Description

The **Address Book Management System** is a menu-driven application developed in **C** to manage contact information such as **name, phone number, and email address**.

The application provides the following operations:

* Create contact
* Search contact
* Edit contact
* Delete contact
* List contacts
* Save contacts
* Exit with or without saving

The project uses **structures and arrays** to store contacts and is divided into multiple `.c` and `.h` files for modular programming.

The application also uses a CSV file (`contacts.csv`) to permanently store contact information.

The project mainly focuses on implementing reliable **user input handling, input validation, searching, sorting, array manipulation, pointers, and file handling**.

---

# 3. Logic

## 3.1 Program Initialization

The program starts by creating and initializing the `AddressBook` structure.

The initialization logic is:

```text
Start Program
      ↓
Initialize AddressBook
      ↓
Set contactCount
      ↓
Load contacts from contacts.csv
      ↓
Display Main Menu
```

The saved contacts are loaded into the contacts array when the program starts.

---

## 3.2 Main Menu Choice Logic

The main menu provides options for different address-book operations.

```text
1. Create Contact
2. Search Contact
3. Edit Contact
4. Delete Contact
5. List All Contacts
6. Save and Exit
7. Exit
```

The choice input is carefully checked because the user may enter:

```text
1
```

or invalid inputs such as:

```text
1 2
abc
1abc
```

or another datatype.

### Logic

```text
Take choice
    ↓
Check whether scanf() successfully read integer
    ↓
If invalid
    ↓
Clear stdin
    ↓
Ask again

If valid integer
    ↓
Read next character
    ↓
Is it '\n'?
   /      \
 YES      NO
  ↓        ↓
Valid    Extra input
           ↓
       Clear stdin
           ↓
        Ask again
```

This ensures that only a **complete and valid menu choice** is accepted.

---

# 3.3 `stdin` Cleaning Logic

A common input-handling requirement throughout the project is to make sure that `stdin` is clean before taking the next input.

If unwanted characters remain in the input stream, they may be consumed by the next input operation.

The program clears the input stream until either:

```c
'\n'
```

or:

```c
EOF
```

is encountered.

Conceptually:

```text
Previous Input
      ↓
Check for unwanted characters
      ↓
Clear remaining stdin data
      ↓
Take next input
```

This logic is applied wherever required throughout the program.

---

# 3.4 String Input Using `fgets()`

For string inputs such as:

* Name
* Phone number
* Email

the program uses `fgets()`.

The reason is that `fgets()` allows the program to control the maximum number of characters read and helps avoid unsafe uncontrolled string input.

After reading the input, the program checks whether `'\n'` exists.

### If `'\n'` exists

The complete input was received within the buffer.

```text
fgets()
  ↓
'\n' found
  ↓
Remove '\n'
  ↓
Validate input
```

### If `'\n'` does not exist

The input may be longer than the buffer.

```text
fgets()
  ↓
'\n' not found
  ↓
Input may be incomplete
  ↓
Clear remaining stdin
  ↓
Ask user again
```

This ensures that incomplete input is not accepted and leftover characters do not affect the next input.

---

# 3.5 Name Input Logic

The name is taken using `fgets()`.

```text
Take name
    ↓
Check complete input
    ↓
Remove '\n'
    ↓
Validate name
    ↓
Valid?
 /     \
YES     NO
 ↓       ↓
Store   Clear/Retry
```

The validation checks that the name contains only the allowed characters.

The program rejects invalid names and asks the user to enter the name again.

---

# 3.6 Phone Number Input Logic

The phone number is first taken as a string.

```text
Take phone number
       ↓
Check complete input
       ↓
Remove '\n'
       ↓
Validate characters
       ↓
Convert string to number
       ↓
Check 10-digit range
       ↓
Check first digit
       ↓
Valid?
```

The phone number must:

* Contain exactly 10 digits.
* Have a first digit other than `0`.

The program also checks whether the phone number already exists.

If it is invalid or already present, the user is asked to enter it again.

---

# 3.7 Email Input Logic

The email address is taken using `fgets()`.

```text
Take email
    ↓
Check complete input
    ↓
Remove '\n'
    ↓
Validate email
    ↓
Check username
    ↓
Check '@'
    ↓
Check domain
    ↓
Valid?
```

The email validation uses string operations and `strtok()` to separate and validate the different parts of the email.

The program also checks whether the email already exists.

---

# 3.8 Create Contact Logic

When creating a contact, the program collects each field one by one.

```text
Create Contact
      ↓
Take Name
      ↓
Validate Name
      ↓
Take Phone
      ↓
Validate Phone
      ↓
Check Duplicate Phone
      ↓
Take Email
      ↓
Validate Email
      ↓
Check Duplicate Email
      ↓
Store Contact
      ↓
Increment contactCount
```

The contact is added only after the required information has passed validation.

---

# 3.9 Search Logic

The project implements separate search logic for:

* Name
* Phone number
* Email

The important implementation detail is that the search function **returns the address of the matching contact**.

The search function does not simply return an index or a success/failure value.

### Search flow

```text
Start from contacts array
        ↓
Compare current contact
        ↓
Match?
   /          \
 YES          NO
  ↓            ↓
Return       Move to
address      next contact
of contact      ↓
              Continue
```

When a matching contact is found:

```text
return &addressBook->contacts[i];
```

The returned value is therefore the **address/pointer of the matching `Contact` structure**.

### Multiple matches

The search pointer is moved forward after finding a match.

This allows the program to find subsequent matching contacts.

Conceptually:

```text
Contact 0
   ↓
Contact 1 ← Match → return address
   ↓
Continue from next contact
   ↓
Contact 2 ← Match → return address
   ↓
Continue
```

### No match

When the search reaches the end of the contacts array without finding another matching contact:

```text
return NULL;
```

Therefore:

```text
Matching contact
      ↓
Return address of Contact

No matching contact remaining
      ↓
Return NULL
```

This use of a **pointer return value and `NULL`** is an important part of the search implementation.

---

# 3.10 Name Search Logic

Name searching uses case-insensitive comparison.

The search allows matching based on the entered part of the name.

```text
Enter name/search string
        ↓
Traverse contacts
        ↓
Case-insensitive comparison
        ↓
Match?
   /       \
 YES       NO
  ↓         ↓
Return    Continue
address
```

If another matching contact exists, the search continues from the next contact.

When no further match is found, the function returns `NULL`.

---

# 3.11 Phone Search Logic

The phone search accepts the entered phone digits and checks them against the stored phone numbers.

The entered number is converted and processed for comparison.

The search supports matching using the entered portion of the phone number.

```text
Enter phone/search digits
        ↓
Convert/process input
        ↓
Traverse contacts
        ↓
Compare required digits
        ↓
Match?
```

If a contact matches:

```text
Return address of matching Contact
```

If there are no more matches:

```text
Return NULL
```

---

# 3.12 Email Search Logic

Email search uses case-insensitive comparison and allows matching against the entered email/search text.

```text
Enter email/search text
        ↓
Traverse contacts
        ↓
Case-insensitive comparison
        ↓
Match?
   /       \
 YES       NO
  ↓         ↓
Return    Continue
address
```

Again, the search function returns the **address of the matching contact** and returns `NULL` when no matching contact remains.

---

# 3.13 Edit Contact Logic

The edit operation first searches for the required contact.

```text
Search Contact
      ↓
Search function
      ↓
Returns Contact address
      ↓
Is pointer NULL?
   /          \
 NO           YES
 ↓             ↓
Display       No match
contact
 ↓
Ask confirmation
 ↓
Select field
```

The user can edit the required contact information.

The new value is passed through the same validation process before updating the contact.

For phone number and email, duplicate checking is also performed.

---

# 3.14 Delete Contact Logic

The delete operation first identifies the contact to be deleted.

After confirmation, the selected contact is removed by **shifting every contact after it one position to the left**.

Example:

```text
Before deletion:

Index 0 → A
Index 1 → B
Index 2 → C
Index 3 → D
```

If `B` is deleted:

```text
Index 0 → A
Index 1 → C
Index 2 → D
```

### Logic

```text
Find contact index
       ↓
Confirm deletion
       ↓
Start from deleted index
       ↓
contacts[i] = contacts[i + 1]
       ↓
Continue until last contact
       ↓
Decrease contactCount
```

So the array remains continuous without an empty position.

---

# 3.15 List Contacts Logic

The List operation allows contacts to be listed according to:

```text
Name
Phone Number
Email
```

Before sorting, the program compares adjacent contacts.

The sorting algorithm used is **Bubble Sort**.

---

# 3.16 Bubble Sort Logic

The project uses Bubble Sort to arrange contacts.

The basic logic is:

```text
Start from first contact
       ↓
Compare adjacent contacts
       ↓
Is first greater than second?
       /          \
     YES          NO
      ↓            ↓
    Swap         Continue
      ↓
Compare next pair
       ↓
Repeat passes
       ↓
Sorted contacts
```

The complete `Contact` structures are swapped so that the name, phone number, and email remain together.

### Sorting by Name

The names of adjacent contacts are compared using case-insensitive comparison.

If the first name should come after the second name, the complete structures are swapped.

### Sorting by Phone

Phone numbers are compared numerically.

If:

```text
phone[i] > phone[i + 1]
```

the complete contact structures are swapped.

### Sorting by Email

Email addresses are compared using case-insensitive string comparison.

If the first email comes after the second email, the complete structures are swapped.

---

# 3.17 Save Logic

The contacts are saved to:

```text
contacts.csv
```

The saving process is:

```text
Open contacts.csv
       ↓
Check fopen()
       ↓
Write contact count
       ↓
Write every contact
       ↓
Close file
```

The contact data is written in CSV format.

---

# 3.18 Load Logic

When the program starts, it attempts to load the existing contacts.

```text
Start
 ↓
Open contacts.csv
 ↓
Read contact count
 ↓
Read contact information
 ↓
Store in contacts array
 ↓
Close file
```

If the file does not exist, the address book starts with no previously stored contacts.

---

# 3.19 Save and Exit / Exit Logic

The program provides two ways to leave the application.

### Save and Exit

```text
Select Save and Exit
        ↓
Save contacts
        ↓
Close file
        ↓
Exit program
```

### Exit

The program asks whether the user wants to save the changes.

```text
Exit
 ↓
Ask confirmation
 ↓
YES → Save → Exit
NO  → Exit without saving
```

Invalid confirmation input is rejected and the user is asked again.

---

# 4. Challenges

## Challenge 1 – Choice Input Handling

One of the main challenges was handling menu choices correctly.

The user may enter:

```text
1
```

but may also enter:

```text
1 2
abc
1abc
```

or another datatype.

Using `scanf()` directly can leave unwanted characters in `stdin`.

### Solution

The program checks:

* Whether `scanf()` successfully read the expected datatype.
* Whether additional characters remain.
* Whether the next character is `'\n'`.
* Clears `stdin` when unwanted characters are found.
* Repeats the input until a valid complete choice is entered.

This logic is important for **all option selections**, not just the main menu.

---

## Challenge 2 – Name, Phone and Email Validation

The program must ensure that every piece of contact information entered by the user is valid.

The challenge was not only validating the data but also ensuring that the **complete input entered by the user was actually received**.

### Solution

Each input follows:

```text
Input
 ↓
Check complete input
 ↓
Clear stdin if necessary
 ↓
Validate
 ↓
Valid?
 ↓
YES → Continue
NO  → Ask again
```

Separate validation functions are used for name, phone number, and email.

---

## Challenge 3 – Keeping `stdin` Clean Before Every Input

Another major challenge was preventing unwanted data from one input operation from affecting the next input.

The program therefore ensures that `stdin` is clean before taking the next input whenever required.

This prevents situations where leftover characters are accidentally consumed as the next input.

---

## Challenge 4 – Using `fgets()` and Detecting Complete Input

`fgets()` was used to safely control the amount of string data being read.

However, another problem had to be solved:

**How do we know whether the complete user input was received?**

The solution was to check for:

```c
'\n'
```

If `'\n'` is present, the input was completely received within the buffer.

If it is absent, the input may have exceeded the buffer.

The remaining characters are then cleared from `stdin`, and the user is asked to enter the value again.

---

## Challenge 5 – Search Function Returning a Contact Address

The search logic required the function to return the **address of the matching contact** rather than simply returning an index.

This required understanding:

* Pointers
* Structure addresses
* Pointer return values
* `NULL`
* Pointer traversal

The function returns:

```text
Address of matching Contact
```

and:

```text
NULL
```

when no matching contact remains.

This also makes it possible to continue searching for multiple matches.

---

## Challenge 6 – Handling Multiple Search Results

A search may produce more than one matching contact.

The challenge was to avoid stopping after the first result.

The search pointer is therefore advanced after finding a match, allowing the next call to continue searching from the next contact.

When no further match is found, `NULL` is returned.

---

## Challenge 7 – Deleting Contacts From an Array

Since contacts are stored in an array, deleting an element creates a gap.

The solution was to shift **every contact after the deleted contact one position to the left**.

```text
Deleted index
      ↓
Copy next contact to current position
      ↓
Continue until last contact
      ↓
Decrease contactCount
```

This keeps the array continuous.

---

## Challenge 8 – Sorting Structures

Sorting contacts is more complicated than sorting a simple integer array because each contact contains:

```text
Name
Phone
Email
```

When two contacts need to be swapped, the **complete Contact structure** must be swapped.

Otherwise, the name could become associated with another person's phone number or email.

Bubble Sort was implemented to handle this.

---

## Challenge 9 – Duplicate Phone Numbers and Emails

The program also checks whether a phone number or email already exists.

This is particularly important during:

* Contact creation
* Contact editing

If a duplicate is detected, the user is asked to enter a different value.

---

## Challenge 10 – File Handling

The program needs to preserve contacts between executions.

The challenge was handling:

* File opening
* File reading
* File writing
* Missing files
* Correct CSV formatting
* Closing files properly

The program checks whether `fopen()` succeeds before performing file operations.

---

# 5. Learnings

## 5.1 C Structures

Learned how to create and work with structures for storing related information.

A contact groups:

```text
Name
Phone
Email
```

into one `Contact` structure.

The address book then maintains an array of these structures.

---

## 5.2 Pointers

The project provided practical experience with pointers.

Particularly:

* Passing structures using pointers.
* Accessing structure members using `->`.
* Returning the address of a structure.
* Storing the returned address in a pointer.
* Checking whether a returned pointer is `NULL`.
* Moving a pointer through an array.

The search implementation was especially useful for understanding that a function can return:

```text
Address of a structure
```

rather than only a numeric index.

---

## 5.3 `NULL` and Pointer-Based Searching

Learned how `NULL` can be used to indicate that no matching contact was found.

The search flow became:

```text
Match found
    ↓
Return Contact address

No match
    ↓
Return NULL
```

This is useful for controlling repeated searches and detecting the end of the search process.

---

## 5.4 Input Buffer / `stdin` Management

One of the most important learnings was understanding how input remains in `stdin`.

Learned how to:

* Detect leftover input.
* Clear unwanted characters.
* Handle invalid datatypes.
* Detect extra input.
* Ensure `stdin` is clean before another input operation.
* Prevent one invalid input from affecting the next input.

---

## 5.5 `fgets()` and Buffer Handling

Learned why `fgets()` is useful for controlled string input.

Also learned that simply using `fgets()` is not enough.

It is necessary to check whether:

```c
'\n'
```

was read.

This allows the program to detect whether the complete input was received or whether additional characters remain in `stdin`.

---

## 5.6 Input Validation

Learned how to build dedicated validation functions for different types of data.

```text
Name
 ↓
Character validation

Phone
 ↓
Digit + length + first-digit validation

Email
 ↓
Username + @ + domain validation
```

This makes the application more reliable.

---

## 5.7 Searching

Learned how to implement searching through an array of structures using pointers.

Important concepts learned:

* Traversing arrays.
* String comparison.
* Case-insensitive comparison.
* Partial matching.
* Returning structure addresses.
* Returning `NULL` when no match exists.
* Continuing a search from a later position.

---

## 5.8 Bubble Sort

Learned how **Bubble Sort** works with an array of structures.

The important concept is that when two contacts are exchanged, the **entire structure** must be swapped.

This preserves the relationship between:

```text
Name ↔ Phone ↔ Email
```

---

## 5.9 Array Manipulation

Learned how to delete an element from an array by shifting all subsequent elements to the left.

```text
Before:

A B C D

Delete B

After:

A C D
```

Also learned to update `contactCount` after deletion.

---

## 5.10 File Handling

Learned practical file-handling operations:

* `fopen()`
* `fscanf()`
* `fprintf()`
* `fclose()`
* Checking `fopen()` failure
* Reading stored data
* Writing updated data
* Maintaining persistent data using CSV

---

## 5.11 Modular Programming

Learned how to split a C project into multiple source and header files.

```text
main.c
contact.c
contact.h
file.c
file.h
populate.c
populate.h
```

This makes the program easier to:

* Understand
* Debug
* Maintain
* Modify
* Reuse

---

## 5.12 Debugging and Problem Solving

The project improved practical debugging skills by solving issues involving:

* `stdin`
* `scanf()`
* `fgets()`
* Buffer limits
* Newline handling
* String validation
* Pointers
* `NULL`
* Structure addresses
* Array shifting
* Bubble Sort
* Duplicate checking
* File handling
* Function interaction

The major learning was to understand the **complete data flow**:

```text
User Input
    ↓
Input Handling
    ↓
stdin Check
    ↓
Validation
    ↓
Processing
    ↓
Structure / Array
    ↓
Search / Sort / Edit / Delete
    ↓
File Storage
```

This project strengthened my understanding of how individual C concepts work together to build a complete application.
