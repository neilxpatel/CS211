#include <stdio.h>
#include <stdlib.h>
#include <string.h>

short add ( short x,  short y) {  //will add x and y and place output in y
    return x + y;
} 
 short sub ( short x,  short y) { //will subtract x from y, place result in y
     return y - x;
}
 short mul ( short x,  short y) { //will multiply x and y, place result in y
     return x * y;
}
 short divide ( short x,  short y) { //will divide x by y, result in y (discard remainder)
     return x / y;
}
int registerIndex(char reg[]) {
    if(strcmp(reg, "ax") == 0) {
        return 0;
    }
    else if(strcmp(reg, "bx") == 0) {
        return 1;
    } 
    else if(strcmp(reg, "cx") == 0) {
        return 2;
    }
    else if(strcmp(reg, "dx") == 0) {
        return 3;
    }
    else {
        return -1; //not in any of the registers
    }
}
int main(int argc, char* argv[])
{
    FILE* inputFile;
    inputFile = fopen(argv[1], "r");
   if(inputFile == NULL) {
        printf("error\n");
        return 0;
    } 
    
    int totalNumberofLines = 0;
    char readInstruction[101][101] = {0};
    while(fgets(readInstruction[totalNumberofLines], 101, inputFile) != NULL) {
        totalNumberofLines++;
    }

    short reg[4] = {0}; //4 registers
    
    for(int i = 0; i < totalNumberofLines; i++) {
        char command[100];
        if(sscanf(readInstruction[i], "%s", command) != 1) { //no command
            continue;
        }
        if(strcmp(command, "read") == 0) {
            char firstArg[100];
            short input;
            sscanf(readInstruction[i], "%s %s", command, firstArg);
            scanf("%hd", &input);
            reg[registerIndex(firstArg)] = input;
        }
        else if(strcmp(command, "print") == 0) {
            char firstArg[100];
            sscanf(readInstruction[i], "%s %s", command, firstArg);
            int output = registerIndex(firstArg);
            if(output == -1) {
                printf("%d", atoi(firstArg));
            }
            else {
                printf("%d", reg[output]);
            }
        }
        else if(strcmp(command, "mov") == 0) {
            char firstArg[100];
            char secondArg[100];
            sscanf(readInstruction[i], "%s %s %s", command, firstArg, secondArg);
            int checkReg = registerIndex(firstArg);
            if(checkReg == -1) {
                reg[registerIndex(secondArg)] = atoi(firstArg);
            }
            else {
                reg[registerIndex(secondArg)] = reg[checkReg];
            }
        } 
        else if(strcmp(command, "add") == 0) {
            char firstArg[100];
            char secondArg[100];
            sscanf(readInstruction[i], "%s %s %s", command, firstArg, secondArg);
            int checkReg = registerIndex(firstArg);
            short x = 0;
            if(checkReg == -1) {
                 x = atoi(firstArg);
            }
            else {
                 x = reg[registerIndex(firstArg)];
            }
            short y = reg[registerIndex(secondArg)];
            reg[registerIndex(secondArg)] = add(x,y);
        }
        else if(strcmp(command, "sub") == 0) {
            char firstArg[100];
            char secondArg[100];
            sscanf(readInstruction[i], "%s %s %s", command, firstArg, secondArg);
            int checkReg = registerIndex(firstArg);
            short x = 0;
            if(checkReg == -1) {
                 x = atoi(firstArg);
            }
            else {
                 x = reg[registerIndex(firstArg)];
            }
            short y = reg[registerIndex(secondArg)];
            reg[registerIndex(secondArg)] = sub(x,y);
        }
        else if(strcmp(command, "mul") == 0) {
            char firstArg[100];
            char secondArg[100];
            sscanf(readInstruction[i], "%s %s %s", command, firstArg, secondArg);
            int checkReg = registerIndex(firstArg);
            short x = 0;
            if(checkReg == -1) {
                 x = atoi(firstArg);
            }
            else {
                 x = reg[registerIndex(firstArg)];
            }
            short y = reg[registerIndex(secondArg)];
            reg[registerIndex(secondArg)] = mul(x,y);
        }
        else if(strcmp(command, "div") == 0) {
            char firstArg[100];
            char secondArg[100];
            sscanf(readInstruction[i], "%s %s %s", command, firstArg, secondArg);
            int checkReg = registerIndex(firstArg);
            short x = 0;
            if(checkReg == -1) {
                 x = atoi(firstArg);
            }
            else {
                 x = reg[registerIndex(firstArg)];
            }
            short y = reg[registerIndex(secondArg)];
            reg[registerIndex(secondArg)] = divide(x,y);
        }
        else if(strcmp(command, "jmp") == 0) {
            int lineJump;
            sscanf(readInstruction[i], "%s %d", command, &lineJump);
            i = lineJump - 1; // -1 since index starts from 0
        }
        else if(strcmp(command, "je") == 0) {
            int lineJump;
            char firstArg[100];
            char secondArg[100];
            short x;
            short y;
            sscanf(readInstruction[i], "%s %d %s %s", command, &lineJump, firstArg, secondArg);
            short checkFirstReg = registerIndex(firstArg);
            short checkSecondReg = registerIndex(secondArg);
            if(checkFirstReg == -1) {
                x = atoi(firstArg);
            } 
            else {
                x = reg[registerIndex(firstArg)];
            }
            if(checkSecondReg == -1) {
                y = atoi(secondArg);
            } 
            else {
                y = reg[registerIndex(secondArg)];
            }
            if(x == y) {
                i = lineJump - 1;
            }
        }
        else if(strcmp(command, "jne") == 0) {
            int lineJump;
            char firstArg[100];
            char secondArg[100];
            short x;
            short y;
            sscanf(readInstruction[i], "%s %d %s %s", command, &lineJump, firstArg, secondArg);
            short checkFirstReg = registerIndex(firstArg);
            short checkSecondReg = registerIndex(secondArg);
            if(checkFirstReg == -1) {
                x = atoi(firstArg);
            } 
            else {
                x = reg[registerIndex(firstArg)];
            }
            if(checkSecondReg == -1) {
                y = atoi(secondArg);
            } 
            else {
                y = reg[registerIndex(secondArg)];
            }
            if(x != y) {
                i = lineJump - 1;
            }
        }
        else if(strcmp(command, "jg") == 0) {
            int lineJump;
            char firstArg[100];
            char secondArg[100];
            short x;
            short y;
            sscanf(readInstruction[i], "%s %d %s %s", command, &lineJump, firstArg, secondArg);
            short checkFirstReg = registerIndex(firstArg);
            short checkSecondReg = registerIndex(secondArg);
            if(checkFirstReg == -1) {
                x = atoi(firstArg);
            } 
            else {
                x = reg[registerIndex(firstArg)];
            }
            if(checkSecondReg == -1) {
                y = atoi(secondArg);
            } 
            else {
                y = reg[registerIndex(secondArg)];
            }
            if(x > y) {
                i = lineJump - 1;
            }
        }

        else if(strcmp(command, "jge") == 0) {
            int lineJump;
            char firstArg[100];
            char secondArg[100];
            short x;
            short y;
            sscanf(readInstruction[i], "%s %d %s %s", command, &lineJump, firstArg, secondArg);
            short checkFirstReg = registerIndex(firstArg);
            short checkSecondReg = registerIndex(secondArg);
            if(checkFirstReg == -1) {
                x = atoi(firstArg);
            } 
            else {
                x = reg[registerIndex(firstArg)];
            }
            if(checkSecondReg == -1) {
                y = atoi(secondArg);
            } 
            else {
                y = reg[registerIndex(secondArg)];
            }
            if(x >= y) {
                i = lineJump - 1;
            }
        }
        else if(strcmp(command, "jl") == 0) {
            int lineJump;
            char firstArg[100];
            char secondArg[100];
            short x;
            short y;
            sscanf(readInstruction[i], "%s %d %s %s", command, &lineJump, firstArg, secondArg);
            short checkFirstReg = registerIndex(firstArg);
            short checkSecondReg = registerIndex(secondArg);
            if(checkFirstReg == -1) {
                x = atoi(firstArg);
            } 
            else {
                x = reg[registerIndex(firstArg)];
            }
            if(checkSecondReg == -1) {
                y = atoi(secondArg);
            } 
            else {
                y = reg[registerIndex(secondArg)];
            }
            if(x < y) {
                i = lineJump - 1;
            }
        }
        else if(strcmp(command, "jle") == 0) {
            int lineJump;
            char firstArg[100];
            char secondArg[100];
            short x;
            short y;
            sscanf(readInstruction[i], "%s %d %s %s", command, &lineJump, firstArg, secondArg);
            short checkFirstReg = registerIndex(firstArg);
            short checkSecondReg = registerIndex(secondArg);
            if(checkFirstReg == -1) {
                x = atoi(firstArg);
            } 
            else {
                x = reg[registerIndex(firstArg)];
            }
            if(checkSecondReg == -1) {
                y = atoi(secondArg);
            } 
            else {
                y = reg[registerIndex(secondArg)];
            }
            if(x <= y) {
                i = lineJump - 1;
            }
        }
        else {
            printf("No Valid Commmand");
            return 0;
        }
    }
fclose(inputFile);
return 0;
}

 
