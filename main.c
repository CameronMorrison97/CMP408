#include <stdio.h>
#include <stdlib.h>

#define INVALID 0

/**
    Validates user input and returns the first character of the array.
    @Param char input[2] - returns the input array which the user input their selection.
    @Returns input[0] - The first character of the input array.
**/
bool validateInput(char input[2]){
    int inputSize = sizeof(input);

    if(sizeof(input) > 1 && input[1] != '\0'){
        return false;
    }

    return true;
}

void displayMenu(){
    char input[2];
    bool valid = false;

    printf("***************************************************************\n");
    printf("*Vending Machine Control Console                              *\n");
    printf("*                               Submitted By: Cameron Morrison*\n");
    printf("*                                          Student ID: 1702366*\n");
    printf("*                                          Abertay University *\n");
    printf("***************************************************************\n");
    printf("1. Add Machine\n");
    printf("2. Show All Machines\n");
    printf("3. Search By Index\n");
    printf("4. Delete Machine\n");
    printf("5. Update Status\n");
    printf("9. Exit\n");
    printf("**************************************************************\n");
    printf("Enter your Choice: ");
    scanf("%s", &input);

    valid = validateInput(input);

    char firstChar = input[0];

    switch(firstChar){
        case '1':
            printf("Add Machine\n");
            break;
        case '2':
            printf("Show All Machines\n");
            break;
        case '3':
            printf("Search By Index\n");
            break;
        case '4':
            printf("Delete Machine\n");
            break;
        case '5':
            printf("Update Status\n");
            break;
        case '9':
            printf("Exit\n");
            break;
        default:
            system("clear");
            displayMenu();
    }



}

void main(){
    displayMenu();
}
