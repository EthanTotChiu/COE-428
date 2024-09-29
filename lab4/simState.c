#include <stdlib.h>
#include <string.h>
#include <stdio.h>
// Ethan Chiu State Machine
/*A B H
  B G A
  C F B
  D C G
  E D F
  F A D
  G H C
  H E H
  starting state is: F
*/
char stateTransitions[][3] = {
    {'A', 'B', 'H'},
    {'B', 'G', 'A'},
    {'C', 'F', 'B'},
    {'D', 'C', 'G'},
    {'E', 'D', 'F'},
    {'F', 'A', 'D'},
    {'G', 'H', 'C'},
    {'H', 'E', 'H'}
};

char currentState = 'F';

int charToInt(char state){
    switch (state){
        case 'A': return 0;
        case 'B': return 1;
        case 'C': return 2;
        case 'D': return 3;
        case 'E': return 4;
        case 'F': return 5;
        case 'G': return 6;
        case 'H': return 7;

        default: return 999;
    }
}

char intToChar(int state){
    switch (state) {
        case 0: return 'A';
        case 1: return 'B';
        case 2: return 'C';
        case 3: return 'D';
        case 4: return 'E';
        case 5: return 'F';
        case 6: return 'G';
        case 7: return 'H';

        default: return 'A';
    }
};

int reachable[8]={0};
void heapSearchReachable(int stateIndex) {

    reachable[stateIndex] = 1;

    for (int i = 1; i < 3; i++) {
        char nextState = stateTransitions[stateIndex][i];
        int nextStateIndex = charToInt(nextState);

        if (reachable[nextStateIndex] == 0) {
            heapSearchReachable(nextStateIndex);
        }
    }
}

// Command Functions---------------------------------------------------------------------------------

void next(char* currentState, int transition){
    int currentStateIndex = charToInt(*currentState);
    char nextState = stateTransitions[currentStateIndex][transition+1];
    if(nextState == 'x'){
        printf("next state does not exist\n");
    }
    else{
        *currentState = nextState;
    }
}

void change(char* currentState, int transition, char newState){
    int currentStateIndex = charToInt(*currentState);
    if (currentStateIndex < 8){
    stateTransitions[currentStateIndex][transition+1] = newState;
    }
    else{
        printf("Final argument disallowed\n");
    }
}

void print(){
    for(int i=0; i < 8 ;i++){
        for(int j=0; j<3 ; j++){
            printf("%c ",stateTransitions[i][j]);
        }
        printf("%c",'\n');
    }
}

void garbage(char state){
    for (int i = 0; i < 8; i++) {
        reachable[i] = 0;
    }
    int currentStateIndex = charToInt(state);
    reachable[currentStateIndex] = 1;
    heapSearchReachable(currentStateIndex);

    int all_reachable = 1;
    for (int i = 0; i < 8; i++) {
        if (reachable[i] == 0) {
            all_reachable = 0;
            break;
        }
    }
    if (all_reachable) {
        printf("No garbage\n");
    }
    else {
        printf("Garbage states: ");
        for (int i = 0; i < 8; i++) {
            if (reachable[i] == 0) {
                printf("%c ", intToChar(i));
            }
        }
    }
}

void delete(char deleteState){
    if (deleteState == '\0'){
        if(reachable == 0){
            printf("No states deleted.");
        }else{
            printf("Deleted: ");
            for (int i = 0; i < 8; i++){  // If the state is not reachable, delete it
                if (reachable[i] == 0){
                    printf("%c ", intToChar(i));
                    for (int j = 0; j < 3; j++) {
                        stateTransitions[i][j] = 'x';
                    }
                }
            }
        }
    }
    else{
        printf("Deleted: %c", deleteState);
        for (int j = 0; j < 3; j++) {
            stateTransitions[charToInt(deleteState)][j] = 'x';
        }
    }
}


// Main-----------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    printf("The initial state is %c\n", currentState);
    printf("Enter command ('0', '1', 'c', 'p', 'g', or 'd'): ");
    while(1){
        char command[10];
        if (fgets(command, 10, stdin) == NULL) {
            printf("Error reading input");
            return 1;
        }

        if (command[0] == '0' && strlen(command) == 2){ // State 0
            next(&currentState,0);
            printf("%c\n",currentState);
        }
        else if(command[0] == '1' && strlen(command) == 2){// State 1
            next(&currentState,1);
            printf("%c\n",currentState);
        }
        else if(command[0] == 'c' && (command[2] == '0' || command[2] == '1') && command[4] >= 'A' && command[4] <= 'H'){// Change `c' followed by a `1' or a `0' followed by the name of a state
            int newTransition;  
            char newState;
            if(sscanf(command+2, "%d %c",&newTransition, &newState) == 2){
                change(&currentState, newTransition, newState);
            }
            else{
                printf("Invalid c command\n");
            }
        }
        else if(command[0] == 'p' && strlen(command) == 2){// Print state machine
            print();
        }
        else if(command[0] == 'g' && strlen(command) == 2){// Identify garbage
            garbage(currentState);

        }
        else if(command[0] == 'd' && (strlen(command) == 2 || strlen(command) == 4)){// Delete optionally followed by the name of a state to delete, without arg delete all unreachable
            char state;
            if(sscanf(command+2, "%c", &state)==1){
                delete(state);
            }
            else{
                delete('\0');
            }
        }
        else{
            printf("invalid command\n");
        }
    }
    return 0;
}

