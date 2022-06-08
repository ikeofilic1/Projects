#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <string.h>

void get_probability(int pots, int pans, double prob[][10], char *guess) {
    char ones[4] = {0};
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            ones[i] += prob[i][guess[j]-48]?1:0;

    int ptr = 0;
    char ones2[4] = {0}, rem[6];
    for (int i = 0; i < 10; ++i) {
        int ok = 1;
        for (int j = 0; j < 4 && ok; ++j)
            if (i == (guess[j]-48)) ok = 0;

        if (ok) {
            for (int j = 0; j < 4; ++j)
                ones2[j] += prob[j][i]?1:0;
            rem[ptr++] = i;
        }

    }

    for (int i = 0; i < 4; ++i) {
        for (int l = i+3; l^i; --l)
            prob[l%4][guess[i]-48] = ((double)pans)/ones[l%4];

        prob[i][guess[i]-48] = (double)pots/ones[i];

        if (ones2[i]) {
            for (int j = 0; j < ptr; ++j) 
                if (prob[i][rem[j]]) 
                    prob[i][rem[j]] = (4.0f-pots-pans)/ones2[i];
        }
    }
    printf("    ");
    for (int i = 0; i < 10; ++i)
        printf("|%5d", i);

    printf("|\n-----------------------------------------------------------------\n");
    for (int i = 0; i < 5; ++i) {
        printf("%4d|", i);
        for (int j = 0; j < 10; ++j) 
            printf(" %4.2f|", prob[i][j]);

        printf("\n-----------------------------------------------------------------\n");
    }
    putchar('\n');
}

void play(char code[]) {
    double prob[5][10];
    int won = 0, pots, pans;

    for (int i = 0; i < 10; ++i) {
        prob[4][i] = 0;
        for (int j = 0; j < 4; ++j)
            prob[j][i] = 0.1f;
    }


    while(!won) {
        char ok = 1, guess[5] = {0};
        pots = 0, pans = 0;
        printf("Enter your guess: ");
        scanf("%4s", guess);

        while(getchar() != '\n');
        if (strlen(guess)!=4) continue;

        for(int i = 0; i < 4 && ok; ++i) {
            if (guess[i] < 48 || guess[i] > 57) {
                printf("%c is not a number. Try again\n\n", guess[i]);
                ok = 0;
                break;
            }

            for (int j = 0; j < 4; ++j) {
                if (i^j && guess[i]==guess[j]) {
                    printf("Repetition not allowed.\n\n");
                    ok = 0;
                    break;
                }
                if(code[j] == guess[i]) {
                    if (i == j) ++pots;
                    else ++pans;
                }
            }           
        }

        if (!ok) continue;
        if ((!pots&&!pans) || pots) printf("%d pot%c", pots, pots==1?'\0':'s');
        if ((!pots&&!pans) || pans) printf("%d pan%c", pans, pans==1?'\0':'s');
        printf("\n\n"); 
        get_probability(pots, pans, prob, guess);      

        if (pots == 4) won = 1;
    }

    if (won) printf("You won!! The code was: %s\n", code);
}

int main(int argc, char const **argv) {
    srand(time(0));
    int B = 0;
    scanf("%d", &B);

    if (B) {
        printf("**Version 1**\n");        
        char code[5] = {0};

        unsigned char is_used[10] = {0};
        for (int j = 0; j < 4; ++j) {
            int r = rand()%10;

            while (is_used[r]) {
                r = rand()%10;
            }
            code[j] = r+48;
            is_used[r] = 1;
        }

        printf("\n%s\n", code);
        play(code);
        
    } else {
        printf("\n**Version 2**\n");
         //have to permute
        char code[5] = {0};

        unsigned char is_used[10] = {0};
        int i = 6, j = 0;
        for (; i < 10; ++i) {
            int r = rand()%(i+1);

            if (is_used[r]) {
                r = i;
            }
            code[j++] = r+48;
            is_used[r] = 1;
        }
        printf("\n%s\n", code);
        play(code);
    }

    return 0;
}