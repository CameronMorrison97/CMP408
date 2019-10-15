
// Used for stdin and stdout
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Used for access to booleans
#include<stdbool.h>
#include <unistd.h>

#define NONE 0
#define NUMBEROFMACHINES 5
#define PINNUM 40

struct vendingMachine{
    int index;
    char name[8];
    int pin;
    bool status;
    char Location[16];
};

struct vendingMachine vendingMachines[NUMBEROFMACHINES];
int numOfRecords = 0;

/**
    code adapted from Addison-Wesley please refer to 1.0 in readme.txt for more information
**/
void flushStdin(){

        int c;
        /* discard all characters up to and including newline */
        while ((c = getchar()) != '\n' && c != EOF);
}

/**
    Deletes a record from machineData.txt
**/
void deleteRecord(){
    int selection;

    while(true){
        printf("Please select the index of the vending machine that you would like to delete: ");

        scanf("%d",&selection);

        // Checks that the user has entered a valid selection.
        if(selection >= 0 && selection < numOfRecords){
            break;
        }

        flushStdin();
    }

    /**
        Code adapted from stack overflow please refer to 2.0 in readme.txt

        Opens a file called machineData.txt in the append mode. This mode allows
        the user to read and append to the end of files.
    **/
    FILE *fp = fopen("machineData.txt","a+");

    /**
        code adapted from tutorialspoint please refer to 2.0 in readme.txt
        checks that there wasn't an error when opening the file

        If there was an error with opening the file machineData.txt then the execution of the program is terminated.
    **/
    if(fp == NULL){
        printf("Unable to write to file.");
        exit(-1);
    }

    // The selection that the user enters is given an index of -1.
    // This highlights that the selection will be deleted.
    vendingMachines[selection].index = -1;

    /**
        system() function code taken from tutorials point please refer to 3.0 in readme.txt
        truncate command taken from stack overflow user nono please refer to 4.0 in readme.txt

        empties the contents of a file to zero bytes.
    **/
    system("truncate -s 0 machineData.txt");

    /**
        Goes through the number of active records writes them into machineData.txt
        except for the vending machine that has an index of -1 this is skipped over.
    **/
    for(int i =0; i < numOfRecords; i++){
        // mark for delete
        if(vendingMachines[i].index == -1){
            continue;
        }

        char *Vendstatus = (vendingMachines[i].status == true) ? "true" : "false";
        fprintf(fp, "%s,%d,%s,%s",vendingMachines[i].name, vendingMachines[i].pin,Vendstatus, vendingMachines[i].Location);
    }

    /**
        Code taken from tutorialspoint please refer to 2.0 in readme.txt

        Closes the file pointer if the file pointer isn't closed this can lead to a seg fault.
    **/
    fclose(fp);
}

/**
    Updates the status of the pin for the vending machine that the user enters
    Can change from false to true and visa versa.
**/
void updateStatus(){
    int selection;

    while(true){
        printf("Please select the index of the vending machine that you would like to access: ");

        scanf("%d",&selection);

        /**
            checks that the selection that the user enters is between the first element and how ever many records are in machineData.txt
        **/
        if(selection >= 0 && selection < numOfRecords){
            break;
        }

        flushStdin();
    }

    bool validStatus = false;
    do{
        printf("Please enter 0(false) or 1(true) for machine status: ");
        int status = -1;
        scanf("%d",&status);

        flushStdin();

        /**
            Returns true of false depend on whether the user an entered 0 or 1
            if the user enters anything other than 0 or 1 the user is then prompted
            for their answer again.
        **/
        switch(status){
            case 1:
                vendingMachines[selection].status = true;
                validStatus = true;
                break;
            case 0:
                vendingMachines[selection].status = false;
                validStatus = true;
                break;
            default:
                validStatus = false;
                break;
        }
    }while(validStatus == false);

    /**
        system() function code taken from tutorials point please refer to 3.0 in readme.txt
        truncate command taken from stack overflow user nono please refer to 4.0 in readme.txt

        empties the contents of a file to zero bytes.
    **/
    system("truncate -s 0 machineData.txt");

    /**
        Code adapted from stack overflow please refer to 2.0 in readme.txt

        Opens a file called machineData.txt in the append mode. This mode allows
        the user to read and append to the end of files.
    **/
    FILE *fp = fopen("machineData.txt","a+");

    /**
        code adapted from tutorialspoint please refer to 2.0 in readme.txt
        checks that there wasn't an error when opening the file

        If there was an error with opening the file machineData.txt then the execution of the program is terminated.
    **/
    if(fp == NULL){
        printf("Unable to write to file.");
        exit(-1);
    }

    /**
        loop through the number of records in machineData.txt
    **/
    for(int i =0 ; i < numOfRecords; i++){
        char *Vendstatus = (vendingMachines[i].status == true) ? "true" : "false";

        /**
            Code taken from tutorials point please refer to 5.0 in readme.txt
        **/
        fprintf(fp, "%s,%d,%s,%s",vendingMachines[i].name, vendingMachines[i].pin,Vendstatus, vendingMachines[i].Location);
    }

    /**
        Code taken from tutorialspoint please refer to 2.0 in readme.txt

        Closes the file pointer if the file pointer isn't closed this can lead to a seg fault.
    **/
    fclose(fp);
}


/**
    Gets an individual record of the users choice.
**/
void displayIndividualRecord(){
    int selection;

    /**
        Prompt the user for a valid choice.
    **/
    while(true){
        printf("Please select the index of the vending machine that you would like to access: ");

        scanf("%d",&selection);

        // Check that selection is digit too??
        if(selection >= 0 && selection < numOfRecords){
            break;
        }

        flushStdin();
    }

    printf("Index  Name  Pin  Status  Location\n\n");

    /**
        Print out the users choice.
    **/
    char *status = (vendingMachines[selection].status == true) ? "true" : "false";
    printf("%d %s %d %s %s",vendingMachines[selection].index, vendingMachines[selection].name, vendingMachines[selection].pin,status, vendingMachines[selection].Location);
}

/**
    Display all of the records in machineData.txt
**/
void displayRecords(){
    printf("Index  Name  Pin  Status  Location\n\n");
    for(int i =0 ;i < numOfRecords; i++){
        char *status = (vendingMachines[i].status == true) ? "true" : "false";
        printf("%d %s %d %s %s",vendingMachines[i].index, vendingMachines[i].name, vendingMachines[i].pin,status, vendingMachines[i].Location);
    }
    printf("\n\n");
}

/**
    Update machineData.txt to match what is in the struct array vendingMachines
**/
void updateRecords(){
    /**
        Code taken from stack overflow user emplatetypedef please refer to 6.0
    **/
    memset(&vendingMachines, 0, sizeof(vendingMachines));

    // https://stackoverflow.com/questions/11198305/segmentation-fault-upon-input-with-getline
    char* line_buf = NULL;
    int line_buf_size = 0;
    int idx = 0;

    /**
        Code adapted from stack overflow please refer to 2.0 in readme.txt

        Opens a file called machineData.txt in the append mode. This mode allows
        the user to read a file the file must be open
    **/
    FILE *fp = fopen("machineData.txt","r+");

    /**
        code adapted from tutorialspoint please refer to 2.0 in readme.txt
        checks that there wasn't an error when opening the file

        If there was an error with opening the file machineData.txt then the execution of the program is terminated.
    **/
    if(fp == NULL){
        printf("Unable to read file.");
        exit(-1);
    }

    // Reads the next line of a file.
    /**
        Code taken from riptutorial.com please refer to 7.0 in readme.txt
    **/
    int lineSize = getline(&line_buf, &line_buf_size, fp);

    while(lineSize != -1){
        vendingMachines[idx].index = idx;

        /**
            Splits the array holding the current line by the delimiter ','

            Code taken from tutorialspoint.com please refer to 8.0 in readme.txt
        **/
        char *ptr = strtok(line_buf,",");
        strcpy(vendingMachines[idx].name,ptr);

        /**
            Splits the pointer ptr by the delimiter ','
        **/
        ptr = strtok(NULL,",");
        vendingMachines[idx].pin = atoi(ptr);

        ptr = strtok(NULL,",");

        if(strcmp(ptr,"true") == 0){
            vendingMachines[idx].status = true;
        }else{
            vendingMachines[idx].status = false;
        }

        ptr = strtok(NULL,",");
        /**
            copies the contents of ptr and places it in location please refer to 9.0 in readme.txt
        **/
        strcpy(vendingMachines[idx].Location, ptr);

        /**
            Gets the nextline
            and iterates the index by 1
        **/
        idx++;
        lineSize = getline(&line_buf, &line_buf_size, fp);
    }

    numOfRecords = idx;

    /**
        Code taken from tutorialspoint please refer to 2.0 in readme.txt

        Closes the file pointer if the file pointer isn't closed this can lead to a seg fault.
    **/
    fclose(fp);
}

/**
    Adds a vending machine to a csv that contains machine data called machineData.txt
**/
void addVendingMachine(){
    // create a struct for the new vending machine.
    struct vendingMachine newMachine;

    printf("Name of vending machine: ");
    scanf("%7s",newMachine.name);
    flushStdin();

    /**
        Get the user to enter the pin number they want to control
        if the pin number is higher or lower or isn't valid than the number of pins on a pi then ask again.
    **/
    while(true){
        system("clear");
        printf("Enter machine pin: ");
        scanf("%d",&newMachine.pin);

        if(newMachine.pin > 0 && newMachine.pin <= PINNUM){
            break;
        }

        flushStdin();
    }

    /**
        Ask user for status if invalid ask again if 1 then true and 0 then false.
    **/
    bool validStatus = false;
    do{
        system("clear");
        printf("Please enter 0(false) or 1(true) for machine status: ");
        int status = -1;
        scanf("%d",&status);

        flushStdin();

        switch(status){
            case 1:
                newMachine.status = true;
                validStatus = true;
                break;
            case 0:
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
    scanf("%14s",&newMachine.Location);
    flushStdin();

    char *status = (newMachine.status == true) ? "true" : "false";

    /**
        Code adapted from stack overflow please refer to 2.0 in readme.txt

        Opens a file called machineData.txt in the append mode. This mode allows
        the user to read and append text to the end of the file.
    **/
    FILE *fp = fopen("machineData.txt","a+");

    /**
        code adapted from tutorialspoint please refer to 2.0 in readme.txt
        checks that there wasn't an error when opening the file

        If there was an error with opening the file machineData.txt then the execution of the program is terminated.
    **/
    if(fp == NULL){
        printf("Unable to write to file.");
        exit(-1);
    }

    /**
            Code taken from tutorials point please refer to 5.0 in readme.txt
        **/
    fprintf(fp,"%s,%d,%s,%s\n",newMachine.name,newMachine.pin,status,newMachine.Location);

    /**
        Code taken from tutorialspoint please refer to 2.0 in readme.txt

        Closes the file pointer if the file pointer isn't closed this can lead to a seg fault.
    **/
    fclose(fp);
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
        scanf("%2s", &input);
        flushStdin();

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

                    if(numOfRecords < NUMBEROFMACHINES){
                        addVendingMachine();
                        updateRecords();
                    }else{
                        printf("Too many vending machines entered please delete one.\n");
                    }
                    break;
                case '2':
                    if(numOfRecords != NONE){
                     displayRecords();
                    }else{
                        printf("My records are empty. Please add a vending machine\n");
                    }

                    valid = true;
                    break;
                case '3':
                    if(numOfRecords != NONE){
                     displayIndividualRecord();
                    }else{
                        printf("My records are empty. Please add a vending machine\n");
                    }
                    valid = true;
                    break;
                case '4':

                    if(numOfRecords != NONE){
                     deleteRecord();
                     updateRecords();
                    }else{
                        printf("My records are empty. Please add a vending machine\n");
                    }
                    valid = true;
                    break;
                case '5':
                    if(numOfRecords != NONE){
                     updateStatus();
                    }else{
                        printf("My records are empty. Please add a vending machine\n");
                    }
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

    /**
        Please refer to 10.0 in readme.txt code adapted from ibm.com

        determines whether the user can read and write to the current directory of the executable.
    **/
    if(access(".",R_OK) != 0 && access(".",W_OK) != 0){
        printf("You do no have permissions to write to the current directory. Please contact your system administrator.\n");
        exit(-1);
    }

    system("touch machineData.txt");
    updateRecords();

    // TODO Check if user has read/write permissions.
    while(true){
        displayMenu();
    }
}
