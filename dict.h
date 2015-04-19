#ifndef DICT_H
#define DICT_H

typedef struct {
    char *key;
    void *data;
} dict_ent;

typedef struct {
    dict_ent **bucket;
    int size;
    int used;
} dict;

dict *dict_new(int size);
int dict_add(dict *it, char *key, void *data);
int dict_reassign(dict *it, char *key, void *data);
void *dict_get(dict *it, char *key);
int dict_remove(dict *it, char *key);

#endif /* DICT_H */
