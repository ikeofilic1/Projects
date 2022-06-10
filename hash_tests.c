#include "hash_tests.h"

int main(int argc, char const *argv[]) {
    if (argc == 1) {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }

    FILE *fp = fopen(argv[1], "r");
    if(!fp) {
        printf("Could not open file, try again\n");
        return -1;
    }

    int M = 0;
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp)) {
        if (c == '\n') M++;
    }

    int size = M/LF;
    printf("Load Factor: %f, elements: %d, size: %d\n", LF, M, size);

    //Tests

    //#1
    printf("89^x hash (prime hashing): \n");

    printf("\nwith linear probing:\n");
    rewind(fp);
    test_function(fp, size, prime_hash, linear_probe);

    printf("\nWith quad probing:\n");
    rewind(fp);
    test_function(fp, size, prime_hash, quad_rehash);

    //#2
    printf("\n\nAscii hash: \n");

    printf("\nWith quad probing: \n");
    rewind(fp);
    test_function(fp, size, ascii_hash, quad_rehash);

    printf("\n\nAscii with linear:\n");
    rewind(fp);
    test_function(fp, size, ascii_hash, linear_probe);

    printf("\n\nAscii with +5 rehash:\n");
    rewind(fp);
    test_function(fp, size, ascii_hash, plus_5);

    //printf("%c\n", 5["C is so foolish, lmao"]);

    fclose(fp);
    return 0;
}

void test_function(FILE *fp, int M, int (*hf)(char *, int), int (*rhf)(int *, int, hash_table*)) {
    hash_table *table = calloc(M, sizeof(hash_table));

    char *delim = " \n", *use;
    char *line = malloc(51*sizeof(char));
    size_t size = sizeof line;
    int max = 0, count = 0, count_re = 0, hwc = 0, LC = 0, coll = 0;

    while (getline(&line, &size, fp) != -1) {
        use = strtok(line, delim);
        int index = hf(use, M);

        if (table[index].data != NULL) { //&& data->word != NULL
            /*if (!strcmp(table[index].data->word, use)) {
                printf("%s has already been used as a key\n", use);
                continue;
            }*/
            int check = rhf(&index, M, table);
            if (check == -1) {
                printf("Something very terrible happened\n");
                continue;
            }
            coll += check;
            if (check > max) max = check;

            if (count - LC > hwc) hwc = count - LC;
            LC = count;
            count_re++;
        }

        node *nd = malloc(sizeof(node));
        nd->word = malloc((strlen(use) + 1)*sizeof(char));
        strcpy(nd->word, use);

        use = strtok(NULL, delim);
        nd->antonym = malloc((strlen(use) + 1)*sizeof(char));
        strcpy(nd->antonym, use);

        nd->next = NULL;
        table[index].data = nd;
        count++;
    }

    free(line);
    int probes = coll + count;

    printf("Expected LF: %.3f, Real LF: %.3f", LF, count*1.0/M);
    printf("\nTotal number of probes: %d\n", probes);
    printf("Mean number of probes per insertion: %.5f\n", probes*1.0/count);
    printf("Total number of collisions: %d\n", coll);
    printf("Cells with collisions (counting duplicates): %d\n", count_re);
    printf("Longest streak without collisions: %d\n", hwc);
    printf("Max collisions in any one cell: %d\n", max);
    printf("Mean collisions (only counting collided cells): %.5f\n", coll*1.0/count_re);
    free_table(table, M);
}

int base_hash(char *key, int M, int base) {
    int h = 0, size = strlen(key);
    for(int i = 0; i < size; ++i) 
        h = (base * h + key[i]) % M;
    return h;
}

int prime_hash(char *key, int M) {
    return base_hash(key, M, 89);
}
int twos_hash(char *key, int M) {
    return base_hash(key, M, 2);    
}
int length_hash(char *key, int M) {
    return base_hash(key, M, strlen(key));    
}

int ascii_hash(char *key, int M) {
    int size = strlen(key), sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += key[i];
        sum %= M;
    }
    return sum;
}

int quad_rehash(int *hv, int M, hash_table *table) {
    for (int i = 1; i < M; ++i) {
        int idx = (*hv + i*i) % M;

        if (table[idx].data == NULL) { //if implement delete, || data->word == NULL
            *hv = idx;
            return i;
        }
    }
    return -1;
}

int plus_n_rehash(int *hv, int M, hash_table *table, int N) {
    int probes = 0;
    do {
        probes++;
        *hv = (*hv + N) % M;
    } while(table[*hv].data != NULL); // && data->word != NULL

    return probes;
}

int linear_probe(int *hv, int M, hash_table *table) {
    return plus_n_rehash(hv, M, table, 1);
}

int plus_5(int *hv, int M, hash_table *table) {
    return plus_n_rehash(hv, M, table, 5);
}

void free_table(hash_table *table, int M) {
    node *nd;
    for (int i = 0; i < M; ++i) { 
        nd = table[i].data;
        //printf("table[%d] = ", i);       
        while (nd != NULL) {
            //printf("Word: %s Antonym: %s", nd->word, nd->antonym);
            node *temp = nd->next;
            free(nd->word);
            free(nd->antonym);
            free(nd);
            nd = temp;
        }
        //printf("\n");
    }
    free(table);
}
