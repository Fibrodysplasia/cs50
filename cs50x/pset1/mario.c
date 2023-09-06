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
    char input[10];
    int direction = 0;
    printf("What's the height of the pyramid?");
    scanf("%s", input);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    while (!is_int(input) || atoi(input) < 1 || atoi(input) > 8) {
        printf("Height must be a number between 1 and 8.\n");
        printf("What's the height of the pyramid?");
        scanf("%s", input);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    int height = atoi(input);

    for (int i = 0; i < height; i++) {
        for (int j = height -1; j >=0 ; j--) {
            if (j <= i) {
                printf("#");
            } else if (j > i && direction == 0) {
                printf(" ");
            }

            if (j <= 0 && direction == 0) {
                printf(" ");
                direction = 1;
                j = height;
            }
        }
        direction = 0;
        printf("\n");
    }


}