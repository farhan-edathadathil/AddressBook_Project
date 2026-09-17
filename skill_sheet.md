# Address Book Management System

## Name

**Address Book Management System**

## Description

A menu-driven **Address Book Management System developed in C** to create, search, edit, delete, list, and store contact information.

The project manages contact details such as:

* Name
* Phone Number
* Email Address

The application uses **structures, arrays, pointers, functions, strings, input validation, `stdin` buffer handling, file handling, CSV storage, searching, sorting, and modular programming**.

Contact data is stored in `contacts.csv` so that contacts can be loaded when the program starts and saved when the user exits.

---

# Menu Options

The application provides the following options:

```text
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save and Exit
7. Exit
```

---

# Project Structure

```text
AddressBook_Project/
│
├── main.c
├── contact.c
├── contact.h
├── file.c
├── file.h
├── populate.c
├── populate.h
├── contacts.csv
└── README.md
```

### `main.c`

Controls the main program flow and menu.

It handles:

* Displaying the menu
* Reading menu choices
* Checking invalid menu input
* Clearing unwanted input from `stdin`
* Calling the required contact operation
* Save and Exit
* Exit with save/no-save confirmation

### `contact.c`

Contains the main address-book operations:

* Create contact
* Search contact
* Edit contact
* Delete contact
* List contacts
* Input functions
* Validation functions
* Search functions
* Sorting functions
* Display function
* Custom number conversion functions

### `contact.h`

Contains the contact/address-book declarations and function prototypes.

### `file.c`

Handles:

* Saving contacts to `contacts.csv`
* Loading contacts from `contacts.csv`
* Checking file-opening errors

### `file.h`

Contains file-handling declarations.

### `populate.c / populate.h`

Contains address-book population-related functionality.

### `contacts.csv`

Stores the saved contact information.

---

# Features

## 1. Create Contact

The Create Contact option takes:

```text
Name
Phone Number
Email
```

Each input is validated before the contact is stored.

The program also checks whether the entered phone number or email already exists.

The contact is first stored using the temporary contact structure and is added to the main contacts array only after the required information has been successfully validated.

---

# 2. Search Contact

Contacts can be searched using:

```text
1. Search by name
2. Search by phone number
3. Search by email
```

### Name Search

The program uses `strncasecmp()` to perform a **case-insensitive partial name search**.

For example, searching:

```text
rah
```

can match a contact whose name starts with:

```text
Rahul
```

Multiple matching contacts can be displayed.

### Phone Search

The entered phone number is converted to a numeric value and then converted back to a string for comparison.

The program uses `strncasecmp()` with the length of the entered number, allowing a **partial/prefix phone-number search**.

### Email Search

Email searching also uses `strncasecmp()` and allows a **case-insensitive partial email search**.

---

# 3. Edit Contact

The Edit Contact operation first searches for the required contact.

The user selects the contact using its displayed index.

The program asks for confirmation before modifying the contact.

The following fields can be edited:

```text
1. Edit name
2. Edit phone number
3. Edit email
```

The new value is validated before updating the contact.

When changing the phone number or email, the program also checks for duplicate values.

---

# 4. Delete Contact

The Delete Contact operation first searches for the required contact.

The user selects the contact using its index.

The program displays the selected contact and asks for confirmation.

If deletion is confirmed:

```text
Selected contact
       ↓
Remove contact
       ↓
Shift remaining contacts one position left
       ↓
Decrease contactCount
```

This maintains the contacts array without leaving a gap.

---

# 5. List Contacts

The List option allows contacts to be sorted and displayed using:

```text
1. List by name
2. List by phone number
3. List by email
```

The project implements **Bubble Sort**.

### Sort by Name

Contacts are compared using `strcasecmp()` and arranged in ascending alphabetical order.

### Sort by Phone Number

Phone numbers are compared numerically and arranged in ascending order.

### Sort by Email

Email addresses are compared using `strcasecmp()` and arranged alphabetically.

When sorting by phone number or email, the contacts are sorted back by name after displaying the requested sorted list.

---

# 6. Save and Exit

The Save and Exit option saves all contacts into:

```text
contacts.csv
```

The file contains:

```text
contactCount
name,phone,email
name,phone,email
...
```

The program displays a saving progress indicator and then saves the contacts before exiting.

---

# 7. Exit

When the user selects Exit, the program asks:

```text
You are going to exit -> do you want to save the changes before exit?

Enter (YES -Y or NO -N)
```

The user can choose:

```text
Y/y → Save contacts and exit
N/n → Exit without saving
```

Invalid confirmation input is rejected and the program asks again.

---

# Input Handling and Validation

A major focus of this project is reliable user-input handling.

The program does not simply assume that the user enters the expected data.

It checks whether the **complete input was received** and whether the input follows the required format.

---

# Challenge 1 – Choice Input Handling

A major challenge was handling menu choices.

For example, when the program expects:

```text
1
```

the user may enter:

```text
1 2
```

or:

```text
abc
```

or:

```text
1abc
```

or another data type.

Using `scanf()` directly can leave unwanted characters in `stdin`.

### Logic Used

```text
Take choice
    ↓
Check scanf() result
    ↓
Is input a valid integer?
    │
    ├── NO → Clear stdin → Ask again
    │
    └── YES
          ↓
       getchar()
          ↓
   Check next character
          ↓
      Is it '\n'?
       /       \
     YES       NO
      ↓         ↓
   Valid     Invalid
                ↓
           Clear stdin
                ↓
            Ask again
```

For example:

```c
if(scanf("%d", &choice) != 1)
{
    while ((ch = getchar()) != '\n' && ch != EOF);
    continue;
}

ch = getchar();

if(ch != '\n' && ch != EOF)
{
    while ((ch = getchar()) != '\n' && ch != EOF);
    continue;
}
```

This prevents additional input from remaining in `stdin`.

The same type of checking is used for menu selections inside Search, Edit, and List operations.

---

# Challenge 2 – Name, Phone Number and Email Validation

Another important challenge was ensuring that every contact field entered by the user is actually valid.

The program does not immediately store the data.

The flow is:

```text
Take input
    ↓
Check complete input
    ↓
Remove '\n'
    ↓
Validate
    ↓
Valid?
  /     \
YES     NO
 ↓       ↓
Store   Ask again
```

Each input has its own validation function.

```text
name_input()
num_input()
mail_input()
```

These functions call:

```text
validname()
validnum()
validmail()
```

---

# Name Validation Logic

The name:

* Cannot be empty.
* Can contain uppercase alphabets.
* Can contain lowercase alphabets.
* Can contain spaces.
* Cannot contain numbers or other special characters.

Logic:

```text
Name
 ↓
Is empty?
 ↓
Reject if empty
 ↓
Check every character
 ↓
Alphabet or space?
 ├── YES → Continue
 └── NO  → Reject
```

---

# Phone Number Validation Logic

The phone number is first read as a string using `fgets()`.

The program then converts it using the custom `my_atoi()` function.

The value is valid only when:

```text
1000000000 <= phone <= 9999999999
```

Therefore:

* It must contain 10 digits.
* The first digit cannot be zero.

Example:

```text
987766788
```

→ Invalid because it contains only 9 digits.

```text
0877667889
```

→ Invalid because the first digit is zero.

```text
9877667889
```

→ Valid.

---

# Email Validation Logic

The email validation is implemented manually using string operations and `strtok()`.

The email is divided around:

```text
@
```

### Username validation

The username:

* Must exist.
* Must contain at least 8 characters.
* Must be less than 65 characters.
* Cannot start with `.`
* Cannot end with `.`
* Cannot contain consecutive `..`
* Can contain lowercase alphabets.
* Can contain digits.
* Can contain `.`

### Domain validation

The domain:

* Must exist.
* Must contain domain parts separated by `.`
* Each domain part must contain characters.
* Each domain part must be less than 64 characters.
* Can contain lowercase alphabets.
* Can contain digits.
* Can contain `.`

The program rejects characters that do not satisfy these conditions.

---

# Challenge 3 – Keeping `stdin` Clean

A recurring challenge throughout the project was ensuring that unwanted input does not remain in `stdin`.

For example:

```text
Expected:
123
```

but the user enters:

```text
123abc
```

The integer may be read successfully while:

```text
abc
```

remains in the input stream.

If the program immediately requests another input, the leftover characters can affect the next operation.

### Solution

The program checks for the newline character:

```c
ch = getchar();

if(ch != '\n' && ch != EOF)
{
    while((ch = getchar()) != '\n' && ch != EOF);
}
```

The remaining characters are removed until:

```text
'\n'
```

or:

```text
EOF
```

is reached.

This keeps the input stream ready for the next input operation.

---

# Challenge 4 – Using `fgets()` and Checking Complete Input

`fgets()` was used for string input because it allows the program to specify the maximum number of characters that can be read.

However, `fgets()` creates an important question:

**How can we know whether the entire input was actually received?**

The program checks for:

```c
strchr(input, '\n')
```

### If `'\n'` is present

The complete input was received.

The newline is removed:

```c
*(strchr(input, '\n')) = '\0';
```

Then the input is validated.

### If `'\n'` is not present

The input may be longer than the available buffer.

The remaining characters are cleared from `stdin`:

```c
while ((ch = getchar()) != '\n' && ch != EOF);
```

The input is rejected and the user is asked to enter it again.

This logic is used for:

* Name
* Phone number
* Email

---

# Duplicate Contact Checking

While creating or editing a contact, the program checks whether:

* Phone number already exists
* Email already exists

For example:

```text
Enter phone number
       ↓
Validate phone
       ↓
Search existing contacts
       ↓
Already exists?
   /          \
 YES          NO
  ↓            ↓
Ask again    Continue
```

This prevents duplicate phone numbers and email addresses from being stored.

---

# Searching Logic

The search functions maintain a pointer inside the contacts array.

The search functions are:

```text
name_search()
num_search()
mail_search()
```

The search starts from the beginning of the contact array.

When a match is found, the matching contact is returned and the pointer is advanced.

Calling the search function again allows the program to find subsequent matching contacts.

This is how multiple matching contacts can be displayed.

---

# Sorting Logic

The project uses **Bubble Sort**.

## Name

```text
Compare contact[i].name
with
contact[i+1].name

If first > second
        ↓
Swap complete Contact structures
```

Comparison uses:

```c
strcasecmp()
```

so the comparison is case-insensitive.

## Phone

Phone numbers are compared numerically:

```text
contact[i].phone > contact[i+1].phone
```

If true, the complete structures are swapped.

## Email

Email addresses are compared using:

```c
strcasecmp()
```

and the complete contact structures are swapped when required.

---

# Delete Logic

When a contact is deleted, the program does not simply clear the element.

Instead, it shifts all contacts after the deleted index one position toward the beginning of the array.

Example:

```text
Before:

0 → A
1 → B
2 → C
3 → D
```

Delete `B`:

```text
0 → A
1 → C
2 → D
```

Then:

```c
--addressBook->contactCount;
```

is used to update the number of contacts.

---

# File Handling Logic

## Loading

At program initialization:

```text
Initialize AddressBook
        ↓
Set contactCount = 0
        ↓
Open contacts.csv
        ↓
File exists?
    /          \
  YES           NO
   ↓             ↓
Read count    Start with
   ↓           0 contacts
Read contacts
   ↓
Close file
```

If `contacts.csv` does not exist, the program sets the contact count to zero and starts the address book without previously saved contacts.

---

## Saving

When saving:

```text
Open contacts.csv in "w" mode
        ↓
Check fopen()
        ↓
Write contact count
        ↓
Write every contact
        ↓
Close file
```

Each contact is stored as:

```text
name,phone,email
```

The program uses:

```c
fprintf()
```

to write the contact information.

---

# Custom Number Conversion

The project also implements its own:

```text
my_atoi()
my_itoa()
```

functions.

## `my_atoi()`

Converts a numeric string into an unsigned long integer.

The logic processes each digit:

```text
num = num * 10 + digit
```

For example:

```text
9876

9
98
987
9876
```

## `my_itoa()`

Converts an unsigned long integer into a string.

The digits are extracted using division and modulus operations and then arranged into the correct order.

These functions are used instead of relying entirely on the standard conversion functions.

---

# Programming Concepts Used

* C Programming
* Structures
* Arrays
* Pointers
* Pointer arithmetic
* Functions
* Function prototypes
* Header files
* Modular programming
* Character arrays
* String manipulation
* `strlen()`
* `strcpy()`
* `strchr()`
* `strcmp()` / `strcasecmp()`
* `strncasecmp()`
* `strtok()`
* `fgets()`
* `scanf()`
* `getchar()`
* File handling
* CSV file storage
* `fopen()`
* `fprintf()`
* `fscanf()`
* `fclose()`
* Bubble sort
* Searching
* Input validation
* Error handling
* `stdin` buffer management
* Pointer arithmetic
* Custom `atoi` / `itoa` implementation

---

# Challenges

### 1. Choice Input Handling

Handling cases where the user enters:

```text
Multiple values
Wrong datatype
Extra characters
Invalid menu choices
```

and ensuring that the unwanted data is cleared from `stdin`.

### 2. Input Validation

Implementing separate validation for:

```text
Name
Phone number
Email
```

and repeatedly requesting input until valid data is entered.

### 3. `stdin` Management

Ensuring that leftover characters from one input operation do not become unwanted input for the next operation.

### 4. Complete Input Detection with `fgets()`

Using `fgets()` safely and checking for `'\n'` to determine whether the complete input was received.

If the newline is absent, the remaining input is cleared and the user is asked to enter the value again.

### 5. Duplicate Data

Checking existing contacts before accepting a new phone number or email address.

### 6. Multiple Search Results

Maintaining a search pointer so that multiple contacts matching the same name, phone prefix, or email prefix can be displayed.

### 7. Array Management During Delete

Removing a contact by shifting all subsequent contacts and updating `contactCount`.

### 8. Sorting Complete Structures

When sorting contacts, the complete `Contact` structure must be exchanged so that the name, phone number, and email remain associated with the correct person.

---

# Learnings

## C Programming

* Practical use of structures and arrays.
* Working with pointers and pointer arithmetic.
* Passing structures using pointers.
* Creating reusable functions.
* Splitting a large program into multiple `.c` and `.h` files.
* Working with character arrays and strings.

## Input Handling

Learned that user input must be validated instead of assuming that the user always enters the expected value.

Learned to:

* Detect invalid data types.
* Detect extra input.
* Clear `stdin`.
* Use `fgets()` for controlled string input.
* Check for `'\n'`.
* Detect incomplete input.
* Prevent leftover input from affecting the next operation.

## Validation

Learned how to build separate validation logic for different types of data.

```text
Name
 ↓
Character validation

Phone
 ↓
Digit / range validation

Email
 ↓
Username + @ + domain validation
```

## File Handling

Learned how to:

* Open files using `fopen()`.
* Check whether a file was opened successfully.
* Read data using `fscanf()`.
* Write data using `fprintf()`.
* Close files using `fclose()`.
* Store structured information in CSV format.
* Load previously saved data when the program starts.

## Searching

Learned how to:

* Traverse an array using pointers.
* Perform case-insensitive comparisons.
* Implement partial searches.
* Return matching structure pointers.
* Continue searching for multiple matches.

## Sorting

Learned how Bubble Sort works with structures and how to swap complete structures while maintaining the relationship between name, phone number, and email.

## Debugging

The project improved my ability to identify problems caused by:

* Incorrect input types
* Extra characters in `stdin`
* Incomplete `fgets()` input
* Buffer limitations
* Invalid strings
* Duplicate contacts
* Array indexing
* Pointer movement
* File-opening errors
* String comparison
* Structure manipulation

The main learning was to trace the complete flow of data from **input → validation → processing → storage → output**, instead of fixing only the visible error.

---

# Key Skills

**C | Structures | Arrays | Pointers | Pointer Arithmetic | Functions | Strings | String Manipulation | Input Validation | `stdin` Management | `fgets()` | `scanf()` | File Handling | CSV | Searching | Sorting | Bubble Sort | Modular Programming | Debugging | Error Handling**
