
// Used for stdin and stdout
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Used for access to booleans
#include<stdbool.h>
#include <unistd.h>

#define INVALID 0

struct vendingMachine{
    int index;
    char name[8];
    int pin;
    bool status;
    char Location[16];
};

struct vendingMachine vendingMachines[256];
int numOfRecords = 0;

void updateStatus(){
    int selection;

    while(true){
        printf("Please select the index of the vending machine that you would like to access: ");

        scanf("%d",&selection);

        // Check that selection is digit too??
        if(selection >= 0 && selection < numOfRecords){
            break;
        }

        // reference this.
        int c;
        /* discard all characters up to and including newline */
        while ((c = getchar()) != '\n' && c != EOF);
    }

    bool validStatus = false;
    do{
        printf("Please enter 0 or 1 for machine status: ");
        int status = -1;
        scanf("%d",&status);

        // reference this.
        int c;
        /* discard all characters up to and including newline */
        while ((c = getchar()) != '\n' && c != EOF);

        switch(status){
            case 0:
                vendingMachines[selection].status = true;
                validStatus = true;
                break;
            case 1:
                vendingMachines[selection].status = false;
                validStatus = true;
                break;
            default:
                validStatus = false;
                break;
        }
    }while(validStatus == false);

    char *Vendstatus = (vendingMachines[selection].status == true) ? "true" : "false";

    printf("%d %s %d %s %s",vendingMachines[selection].index, vendingMachines[selection].name, vendingMachines[selection].pin,Vendstatus, vendingMachines[selection].Location);
}

void displayIndividualRecord(){
    int selection;

    while(true){
        printf("Please select the index of the vending machine that you would like to access: ");

        scanf("%d",&selection);

        // Check that selection is digit too??
        if(selection >= 0 && selection < numOfRecords){
            break;
        }

        // reference this.
        int c;
        /* discard all characters up to and including newline */
        while ((c = getchar()) != '\n' && c != EOF);
    }

    printf("Index  Name  Pin  Status  Location\n\n");

    char *status = (vendingMachines[selection].status == true) ? "true" : "false";
    printf("%d %s %d %s %s",vendingMachines[selection].index, vendingMachines[selection].name, vendingMachines[selection].pin,status, vendingMachines[selection].Location);
}

void displayRecords(){
    printf("Index  Name  Pin  Status  Location\n\n");
    for(int i =0 ;i < numOfRecords; i++){
        char *status = (vendingMachines[i].status == true) ? "true" : "false";
        printf("%d %s %d %s %s",vendingMachines[i].index, vendingMachines[i].name, vendingMachines[i].pin,status, vendingMachines[i].Location);
    }
    printf("\n\n");
}

void updateRecords(){
    memset(&vendingMachines, 0, sizeof(vendingMachines));

    // https://stackoverflow.com/questions/11198305/segmentation-fault-upon-input-with-getline
    char* line_buf = NULL;
    int line_buf_size = 0;
    int idx = 0;

    // Throws seg fault if no file present....
    // Read file
    FILE *fp = fopen("machineData.txt","rw");

    if(fp == NULL){
        printf("Unable to read file.");
    }

    // Potential bug here if machineData.txt is empty??
    int lineSize = getline(&line_buf, &line_buf_size, fp);

    do{
        vendingMachines[idx].index = idx;

        char *ptr = strtok(line_buf,",");
        strcpy(vendingMachines[idx].name,ptr);

        ptr = strtok(NULL,",");
        vendingMachines[idx].pin = atoi(ptr);

        ptr = strtok(NULL,",");

        if(strcmp(ptr,"true") == 0){
            vendingMachines[idx].status = true;
        }else{
            vendingMachines[idx].status = false;
        }

        ptr = strtok(NULL,",");
        strcpy(vendingMachines[idx].Location, ptr);
        idx++;
        lineSize = getline(&line_buf, &line_buf_size, fp);
    }while(lineSize != -1);

    numOfRecords = idx+1;

    fclose(fp);
}

/**
    Adds a vending machine to a csv that contains machine data called machineData.txt
**/
void addVendingMachine(){
    struct vendingMachine newMachine;

    printf("Name of vending machine: ");
    scanf("%s",newMachine.name);

    while(true){
        system("clear");
        printf("Enter machine pin: ");
        scanf("%d",&newMachine.pin);

        // ask lecture about pin validation...
        if(newMachine.pin > 0 && newMachine.pin < 10000){
            break;
        }

        // reference this.
        int c;
        /* discard all characters up to and including newline */
        while ((c = getchar()) != '\n' && c != EOF);
    }

    bool validStatus = false;
    do{
        system("clear");
        printf("Please enter 0 or 1 for machine status: ");
        int status = -1;
        scanf("%d",&status);

        // reference this.
        int c;
        /* discard all characters up to and including newline */
        while ((c = getchar()) != '\n' && c != EOF);

        switch(status){
            case 0:
                newMachine.status = true;
                validStatus = true;
                break;
            case 1:
                newMachine.status = false;
                validStatus = true;
                break;
            default:
                validStatus = false;
                break;
        }
    }while(validStatus == false);

    system("clear");
    printf("Please enter room number of the Vending Machine: ");
    scanf("%s",&newMachine.Location);

    char *status = (newMachine.status == true) ? "true" : "false";

    char test[256];
    sprintf(test, "echo %s,%d,%s,%s >> machineData.txt", newMachine.name,newMachine.pin,status,newMachine.Location);
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
                    valid = true;
                    addVendingMachine();
                    updateRecords();
                    break;
                case '2':
                    displayRecords();
                    valid = true;
                    break;
                case '3':
                    displayIndividualRecord();
                    valid = true;
                    break;
                case '4':
                    printf("Delete Machine\n");
                    valid = true;
                    break;
                case '5':
                    updateStatus();
                    valid = true;
                    break;
                case '9':
                    printf("Exiting program...\n");
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

    if(access(".",R_OK) != 0 && access(".",W_OK) != 0){
        printf("You do no have permissions to write to the current directory. Please contact your system administrator.\n");
        exit(-1);
    }

    updateRecords();

    // TODO Check if user has read/write permissions.
    while(true){
        displayMenu();
    }
}
