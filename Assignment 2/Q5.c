/*Code for university library managment system */

#include<stdio.h>
#include<string.h>

#define MAX_BOOKS 4
#define MAX_BORROW 3
// function to display Menu
void displayMenu(){
    printf("\n==== UNIVERSITY LIBRARY MANAGEMENT SYSTEM =====\n");
    printf("1. Display Avaliable Books\n");
    printf("2. Borrow a Book\n");
    printf("3. Return a Book\n");
    printf("4. Display Member Record\n");
    printf("5. Exit\n ENter you choice:");
}

// function to register valid member
void registerMember(char name[], int *studentID, int *memberType){
    printf("ENter Member Name:");
    scanf("%[^\n]s", name);
    printf("Enter Student /Faculity ID: ");
    scanf("%d", studentID);
    printf("Enter Membership Type(1 for student, 2 for faculity ):");
    scanf("%d",memberType);

    while(*memberType != 1 && *memberType !=2){
        printf("Invalid! Enter 1 for Student, 2 for faculity: ");
        scanf("%d", memberType);
    }
}

// function to display book by its title and avaliable copies
void displayBooks(int bookIDs[], char bookTitles[][50], int avaliableCopies[], int totalBooks ){
    printf("\n %-5s | %-25s  | %-8s\n","ID","Title", "Copies" );
    printf("---------------------------\n");
    for(int i=0; i<totalBooks; i++){
         printf("\n %-5s | %-25s  | %-8s\n", bookIDs[i], bookTitles[i], avaliableCopies[i]);
    }
}

void borrowBook(int bookIDs[], char bookTitles[][50], int avaliableCopies[],
     int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType){
        if(*borrowedCount>= MAX_BORROW){
            printf("\n Borrowing Limit Exceeded! Maximum 3 books allowed[cite: 8].\n");\
            return;
        }
        int bookID, days;
        printf("enter Book ID to borrow[cite: 8]: ");
        scanf("%d", & bookID);

        int bookIndex = -1;
        for(int i=0;i<totalBooks; i++){
            if(bookIDs[i]==bookID){
                bookIndex=1;
                break;
            }
        }

        if(bookIndex == -1){
            printf("Invalid Book Id[cite: 8]!\n");
            return;
        }

        if(avaliableCopies[bookIndex]<= 0){
            printf("Transcation Declined: No copies avaliable[cite: 8].\n");
            return;
        }

        do{
            printf("Enter number of days to keep (positive)[cite: 9]: ");
            scanf("%d",&days);
            if(days<=0){
                printf("Days must be positive[cite: 9]!\n");
            }
        }while(days<= 0);

        borrowedBookIDs[&borrowedCount]= bookID;
        (*borrowedCount)++;
        avaliableCopies[bookIndex]--;

        printf("Successfully Borrowed '%s !\n",bookTitles[bookIndex]);
}

float returnBook(int bookIDs[], int avaliableCopies[], int totalBooks, int borrowedBooksIDs[],
int *borrowedCount, int memberType, float*totalFine){
    int bookID, actualDays;
    printf("Enter Book ID to return[cite: 8]: ");
    scanf("%d", &bookID);

    int borrowedIndex = -1;
    for(int i=0; i< *borrowedCount; i++){
        if(borrowedBooksIDs[i] == bookID){
            borrowedIndex = i;
            break;
        }
    }

    if(borrowedIndex == -1){
        printf("Error: You have not borrowed this book[cite: 9]!\n");
        return 0.0;
    }

    do{
        printf("Enter actaul number of days kept (positive)[cite: 9]: ");
        scanf("%d",&actualDays);
        if(actualDays <= 0){
            printf("Days must be Positive[cite: 9]!\n");
        }
    }while(actualDays <= 0);

    int bookIndex = -1;
    for(int i=0; i< totalBooks; i++){
        if(bookIDs[i] == bookID){
            bookIndex = i;
            break;
        }
    }

    int allowedDays = (memberType==1) ? 14: 30;  //14 for student[cite: 7], 30 for faculity[cite: 8]
    float fine=0.0;

    if(actualDays> allowedDays){
        int extraDays = actualDays - allowedDays;
        float rate = (memberType == 1) ? 20.0: 10.0; //Rs 20 for student[cite: 8]. Rs 10 for faculity[cite: 8]
        fine = extraDays*rate;
        printf("Bppk returned late by %d days. fine: Rs. %.2f\n",extraDays,fine);}
        else{ 
            printf("Book returned on time. No fine\n");
        }

        *totalFine +=fine;
        float payableFine= fine;

        if(fine > 0.0){
            char code[20];
            printf("enter membership code(or press enter if none):");
            scanf("%[^\n]s",code);
            if(strcmp(code,"LIB2026")== 0){
                payableFine = fine * 0.5;
                printf("Membership code verified! 50% waiver applied[cite: 9]. Payable: Rs.%.2f\n",payableFine);
            }else{
                printf("Invalid/missing code. Full fine applies: Rs.%.2f\n",payableFine);
            }// end inner else
        }// end outer if

        for(int i = borrowedIndex; i < *borrowedCount - 1; i++){
            borrowedBooksIDs[i] = borrowedBooksIDs[i+1];
        }
        (*borrowedCount)--;
        return payableFine;
    }// end function 


void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[], int borrowedCount, float totalFine, float fineAfterWaiver){
    printf("\n==========MEMBER RECORD==================\n");
    printf("Name            : %s\n",name);
    printf("ID              : %d\n",studentID);
    printf("Membership type: %s[cite: 7,8]\n",(memberType == 1)? "Student": "Faculity");
    printf("Currently Borowed Book IDs (%d/3): ",borrowedCount);
    if(borrowedCount == 0){
        printf("None");
    }else{
        for(int i =0; i< borrowedCount; i++){
            printf("%d",borrowedBookIDs[i]);
        }//end for
    }//end else

    printf("\n Total Fine Charged (before waiver): Rs.%.2f[cote: 9]\n",totalFine);
    printf("Final Fine Payable (After Waiver) : Rs. %.2f[cite: 9]\n",fineAfterWaiver);
    printf("===================================\n");
}// function

int main(){
    //Invalid book inventory
    int bookIDs[MAX_BOOKS]={101,102,103,104};
    char bookTitles[MAX_BOOKS][50]={"Programming in C,Data structures,Database Systems,Computer Networks"};
    int availableCopies[MAX_BOOKS]={5,3,0,4};

    // member variables
    char name[50]="";
    int studentID = 0;
    int memberType = 0; // 1 for student and 2 for faculity
    int borrowedBookIDs[MAX_BORROW]={0};
    int borrowedCount = 0;
    float totalFineBeforeWaiver = 0.0;
    float totalFineAfterWaiver = 0.0;
    int registered = 0;

    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                registerMember(name, &studentID, &memberType);
                registered = 1;
                break;
            case 2:
                displayBooks(bookIDs, bookTitles, availableCopies, MAX_BOOKS);
                break;
            case 3:
                if (!registered) {
                    printf("\nPlease register a member first (Option 1).\n");
                    break;
                }
                borrowBook(bookIDs, bookTitles, availableCopies, MAX_BOOKS, borrowedBookIDs, &borrowedCount, memberType);
                break;
            case 4:
                if (!registered) {
                    printf("\nPlease register a member first (Option 1).\n");
                    break;
                }
                if (borrowedCount == 0) {
                    printf("\nYou have not borrowed any books.\n");
                    break;
                }
                float currentFine = returnBook(bookIDs, availableCopies, MAX_BOOKS, borrowedBookIDs, &borrowedCount, memberType, &totalFineBeforeWaiver);
                totalFineAfterWaiver += currentFine;
                break;
            case 5:
                if (!registered) {
                    printf("\nPlease register a member first (Option 1).\n");
                    break;
                }
                displayMemberRecord(name, studentID, memberType, borrowedBookIDs, borrowedCount, totalFineBeforeWaiver, totalFineAfterWaiver);
                break;
            case 6:
                printf("\nExiting University Library Management System. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice! Please select between 1 and 6.\n");
        }
    } while (choice != 6);

    return 0;

}
