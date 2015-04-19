#ifndef DICT_DEFS_H
#define DICT_DEFS_H

typedef struct {
    char *key;
    void *data;
} dict_ent;

typedef struct {
    dict_ent **bucket;
    int size;
    int used;
} dict;

#endif /* DICT_DEFS_H */
