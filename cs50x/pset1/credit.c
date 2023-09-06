#include <stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

void removeNonNumerics(char *input) {
    // this removes them from the array without a copy
    if (input == NULL) {
        return;
    }
    int destinationIndex = 0;

    for (int sourceIndex = 0; input[sourceIndex] != '\0'; sourceIndex++) {
        if (isdigit(input[sourceIndex])) {
            input[destinationIndex] = input[sourceIndex];
            destinationIndex++;
        }
    }

    input[destinationIndex] = '\0'; // Null-terminate when done
}

int checkLuhn(char *input) {
    if (input == NULL) {
        return 0;
    }
    
    int length = strlen(input);
    int sum1 = 0;
    int sum2 = 0;
    for (int i = length -1; i >= 0; i--) {
        int digit = input[i] - '0';
        if (i % 2 == 0) {
            int doubled = digit * 2;
            if (doubled > 9) {
                sum2 += doubled - 9; // same as adding digits (i.e. 12 - 9 = 1 + 2 = 3)
            } else {
                sum2 += doubled;
            }
        } else {
            sum1 += digit;
            
        }
    }
    int total = sum1 + sum2;
    return total % 10 == 0;
}

int getCardType(char *input) {
    int length = strlen(input);
    printf("length: %i\n", length);
    if (input == NULL) {
        return 0;
    }
    if (length == 15) {
        if (input[0] == '3' && (input[1] == '4' || input[1] == '7')) {
            return 1;
        }
    } else if (length == 16 || length == 13) {
        if (input[0] == '5' && (input[1] == '1' || input[1] == '2' || input[1] == '3' || input[1] == '4' || input[1] == '5')) {
            return 2;
        } else if (input[0] == '4') {
            return 3;
        }
    }
    return 0;
}

// 1 amex start 34 37
// 2 mc 51 52 53 54 55
// 3 visa 4

int main(void) {

    char input[50] = {'\0'};
    
    printf("Credit Card Number: ");
    scanf("%s", input);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    removeNonNumerics(input);
    if (checkLuhn(input)) {
        int cardType = getCardType(input);
        switch (cardType) {
            case 1:
                printf("AMEX\n");
                break;
            case 2:
                printf("MASTERCARD\n");
                break;
            case 3:
                printf("VISA\n");
                break;
            default:
                printf("INVALID\n");
                break;
        }
    }
    else {
        printf("checksum: INVALID\n");
    }
}