#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 9

int preferences[MAX][MAX];
int locked[MAX][MAX];

int vote(int rank, char *name, int ranks[], int candidate_count, char *candidates[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void create_strength_array(int strength[]);
void sort(int array[], int start, int end);
void merge(int array[], int start, int middle, int end);
void print_array(int array[], int array_size);
int check_cycle(int winner, int loser);

typedef struct {
    int winner;
    int loser;
} pair;

pair pairs[MAX * (MAX - 1) / 2];
char* candidates[MAX];

int pair_count;
int candidate_count;

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

int vote(int rank, char *name, int ranks[], int candidate_count, char *candidates[]) {
    for (int candidate = 0; candidate < candidate_count; candidate++) {
        if (strcmp(name, candidates[candidate]) == 0) {
            ranks[rank] = candidate;
            return 1;
        }
    }
    return 0;
}

void record_preferences(int ranks[]) {
    int rank_1 = 0;
    int rank_2 = 0;
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            rank_1 = ranks[i];
            rank_2 = ranks[j];
            if (rank_1 != rank_2) {
                preferences[rank_1][rank_2]++;
            }
            else {
                preferences[rank_1][rank_2] = 0;
            }
        }
    }
    return;
}

void add_pairs(void) {
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i; j < candidate_count; j++) {
            int comparison_1 = preferences[i][j];
            int comparison_2 = preferences[j][i];
            if (comparison_1 > comparison_2) {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (comparison_1 < comparison_2) {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

void sort_pairs(void) {
    int strength_array[pair_count];
    create_strength_array(strength_array);
    sort(strength_array, 0, pair_count - 1);
    return;
}

void lock_pairs(void) {
    int winner;
    int loser;
    for (int i = 0; i < pair_count; i++) {
        winner = pairs[i].winner;
        loser= pairs[i].loser;
        if (check_cycle(winner, loser) == 0) {
            locked[winner][loser] = 1;
        }
    }
    return;
}

void print_winner(void) {
    for (int i = 0; i < candidate_count; i++) {
        int is_winner = 1;
        for (int j = 0; j < candidate_count; j++) {
            if (locked[j][i] == 1) {
                is_winner = 0;
                break;
            }
        }
        if (is_winner == 1) {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}

void create_strength_array(int strength[]) {
    int winner;
    int loser;
    for (int i = 0; i < pair_count; i++) {
        winner = pairs[i].winner;
        loser = pairs[i].loser;
        strength[i] = preferences[winner][loser] - preferences[loser][winner];
    }
}

void sort(int array[], int start, int end) {
    if (start < end) {
        int middle = (start + end) / 2;
        sort(array, start, middle);
        sort(array, middle + 1, end);
        merge(array, start, middle, end);
    }
}

void merge(int array[], int start, int middle, int end) {
    int i = start;
    int j = middle + 1;
    int k = 0;

    typedef struct {
        int winner;
        int loser;
    } pair_temp;

    pair_temp pairs_temp[pair_count];

    while (i <= middle && j <= end) {
        if (array[i] >= array[j]) {
            pairs_temp[k].winner = pairs[i].winner;
            pairs_temp[k].loser = pairs[i].loser;
            i++;
            k++;
        }
        else {
            pairs_temp[k].winner = pairs[j].winner;
            pairs_temp[k].loser = pairs[j].loser;
            j++;
            k++;
        }
    }

    while (i <= middle) {
        pairs_temp[k].winner = pairs[i].winner;
        pairs_temp[k].loser = pairs[i].loser;
        i++;
        k++;
    }

    while (j <= end) {
        pairs_temp[k].winner = pairs[j].winner;
        pairs_temp[k].loser = pairs[j].loser;
        j++;
        k++;
    }

    for (i = start; i <= end; i++) {
        pairs[i].winner = pairs_temp[i - start].winner;
        pairs[i].loser = pairs_temp[i - start].loser;
    }
}

void print_array(int array[], int array_size) {
    for (int i = 0; i < array_size; i++) {
        printf("%i ", array[i]);
    }
    printf("\n");
}

int check_cycle(int winner, int loser) {
    if (locked[loser][winner] == 1) {
        return 1;
    }
    for (int i = 0; i < candidate_count; i++) {
        if (locked[i][winner] == 1) {
            return check_cycle(i, loser);
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX) {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++) {
        candidates[i] = argv[i + 1];
    }

    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            locked[i][j] = 0;
        }
    }

    pair_count = 0;
    char voter_count[5];
    int voter_count_int;
    printf("Number of Voters: ");
    fgets(voter_count, sizeof(voter_count), stdin);
    voter_count_int = atoi(voter_count);
    while (voter_count_int < 1) {
        printf("Invalid input. Please enter a positive integer.\n");
        fgets(voter_count, sizeof(voter_count), stdin);
        voter_count_int = atoi(voter_count);
    } 

    for (int i = 0; i < voter_count_int; i++) {
        int ranks[candidate_count];

        for (int j = 0; j < candidate_count; j++) {
            char name[20];
            printf("Rank %i: ", j + 1);
            scanf("%s", name);
            int c;
            while ((c = getchar()) != '\n' && c != EOF);

            int valid_vote = vote(j, name, ranks, candidate_count, candidates);
            if (!valid_vote) {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);
        printf("\n");
    }
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}