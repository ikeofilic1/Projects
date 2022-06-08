#ifndef _HASH_TESTS_H
#define _HASH_TESTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LF 0.75

typedef struct node{
    char *word;
    char *antonym;
    struct node *next;
} node;

typedef struct {
    node *data;
} hash_table;

void test_function(FILE *, int, int(*)(char *, int), int(*)(int *, int, hash_table *));
int base_hash(char *key, int M, int base);
int twos_hash(char *key, int M);
int length_hash(char *key, int M);
int prime_hash(char *key, int M);
int ascii_hash(char *key, int M);

int linear_probe(int *, int, hash_table *);
int quad_rehash(int *, int, hash_table *);
int plus_n_rehash(int *hv, int M, hash_table *table, int N);
int plus_3(int *hv, int M, hash_table *table);
int plus_5(int *hv, int M, hash_table *table);
void free_table(hash_table *, int M);

#endif
