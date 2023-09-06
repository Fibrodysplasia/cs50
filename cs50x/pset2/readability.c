#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(char *text);
int count_words(char *text);
int count_sentences(char *text);
int readability_index(int letters, int words, int sentences);

int count_letters(char *text) {
    int count = 0;
    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            count++;
        }
    }
    return count;
}

int count_words(char *text) {
    int count = 0;
    for (int i = 0; i < strlen(text); i++) {
        if (isspace(text[i])) {
            count++;
        }
    }
    return count + 1;
}

int count_sentences(char *text) {
    int count = 0;
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
            count++;
        }
    }
    return count;
}

int readability_index(int letters, int words, int sentences) {
    float words_per_100 = (float) words / 100;
    float L = (float) letters / (float) words_per_100;
    float S = (float) sentences / (float) words_per_100;
    float index = round(0.0588 * L - 0.296 * S - 15.8);
    return round(index);
}

int main(void) {
    char text[1000];
    printf("Text: ");
    fgets(text, 1000, stdin);
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    int index = readability_index(letters, words, sentences);
    if (index < 1) {
        printf("Before Grade 1\n");
    } else if (index >= 16) {
        printf("Grade 16+\n");
    } else {
        printf("Grade %i\n", index);
    }
}