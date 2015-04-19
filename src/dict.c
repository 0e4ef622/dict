#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include "defs.h"

dict *dict_new(int size) {
    dict *newdict = (dict *) malloc(sizeof(dict));

    int bucketsize = sizeof(dict_ent *) * (size / .75);
    newdict->bucket = (dict_ent **) malloc(bucketsize);
    memset(newdict->bucket, 0, bucketsize);

    newdict->size = size;
    newdict->used = 0;
    return newdict;
}

int dict_add(dict *it, char *key, void *data) {
    if (it->used >= it->size)
        return 1;

    dict_ent *entry = (dict_ent *) malloc(sizeof(dict_ent));
    entry->key = strdup(key);
    entry->data = data;

    unsigned int index = hash(key) % it->size;
    while (it->bucket[index] != NULL) index++;
    it->bucket[index] = entry;
    it->used++;

    return 0;
}

int dict_reassign(dict *it, char *key, void *data) {
    unsigned int index = hash(key) % it->size;
    dict_ent *entry = it->bucket[index];
    if (entry == NULL)
        return dict_add(it, key, data);

    while (strcmp(it->bucket[index]->key, key) != 0) {
        if (it->bucket[index] == NULL) return dict_add(it, key, data);
        index++;
    }

    entry = it->bucket[index];
    entry->data = data;
    return 0;
}

void *dict_get(dict *it, char *key) {
    unsigned int index = hash(key) % it->size;
    dict_ent *entry = it->bucket[index];

    if (entry == NULL) return NULL;

    while (strcmp(entry->key, key) != 0) {
        printf("COLLISION :P\n");
        entry = it->bucket[++index];
    }
    
    return entry->data;
}

int dict_remove(dict *it, char *key) {
    unsigned int index = hash(key) % it->size;
    dict_ent *entry = it->bucket[index];

    if (entry == NULL) return 1;

    it->bucket[index] = NULL;
    it->used--;
    return 0;
}
