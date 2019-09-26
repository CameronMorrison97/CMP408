
// Used for stdin and stdout
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Used for access to booleans
#include<stdbool.h>

#define INVALID 0

struct vendingMachine{
    int index;
    char *name;
    int pin;
    bool status;
    int Location;
};

void addVendingMachine(){
    struct vendingMachine newMachine;
    newMachine.index = 2;
    newMachine.name = "Hacklab";
    newMachine.pin = 1;
    newMachine.status = false;
    newMachine.Location = 4511;

    char *status = (newMachine.status == true) ? "true" : "false";

    char test[100];
    sprintf(test, "echo %d,%s,%d,%s,%d > machineData.txt",newMachine.index, newMachine.name,newMachine.pin,status,newMachine.Location);
    system(test);
}

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

/**
    Displays the menu to the user.
**/
void displayMenu(){
    char input[2];
    bool valid;

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

    do{
        // Get User Input
        printf("Enter your Choice: ");
        scanf("%s", &input);

        // Check if the user input is valid
        valid = validateInput(input);

        // Once the user input is valid and is a one digit character
        if(valid == true){

            // Take the first character and then check that it matches 1-5 and 9.
            // If the user enters a number that isn't between 1 and 5 or number 9 then valid becomes false.
            // The user is then prompted again for their new input.
            char firstChar = input[0];

            switch(firstChar){
                case '1':
                    printf("Add Machine\n");
                    valid = true;
                    addVendingMachine();
                    break;
                case '2':
                    printf("Show All Machines\n");
                    valid = true;
                    break;
                case '3':
                    printf("Search By Index\n");
                    valid = true;
                    break;
                case '4':
                    printf("Delete Machine\n");
                    valid = true;
                    break;
                case '5':
                    printf("Update Status\n");
                    valid = true;
                    break;
                case '9':
                    printf("Exit\n");
                    valid = true;
                    exit(0);
                    break;
                default:
                    valid = false;
                    break;
            }
        }
    }while(valid == false);
}

void main(){
    // TODO Check if user has read/write permissions.

    displayMenu();
}
