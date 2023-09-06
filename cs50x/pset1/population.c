#include <stdio.h>
#include<ctype.h>
#include<stdlib.h>

int is_int(const char *input) {
    if (input == NULL || input[0] == '\0') {
        return 0;
    }
    for (int i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i])) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    char start[50];
    printf("Starting Population Size: ");
    scanf("%s", start);
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // input buffer gave me a lot of trouble

    while (!is_int(start) || atoi(start) < 9) {
            printf("Starting size must be a number greater than 8.\n");
            printf("Starting Population Size: ");
            scanf("%s", start);
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

    char end[50];
    printf("Ending Population Size: ");
    scanf("%s", end);
    while ((c = getchar()) != '\n' && c != EOF);

    while (!is_int(end) || atoi(end) < atoi(start)) {
        printf("Ending size must be a number greater than starting size (%s).\n", start);
        printf("Starting Population Size: ");
        scanf("%s", end);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    } 
    
    
    int n = atoi(start);
    int m = atoi(end);
    int years = 0;
    int gain;
    int lose;

    while (n < m) {
        gain = n /3;
        lose = n /4;
        n = n + gain - lose;
        years++;
    }

    printf("Years to target population: %d\n", years);
    
}