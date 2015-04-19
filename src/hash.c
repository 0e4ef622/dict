unsigned int hash(const char *s) {
    unsigned int hash = 0;
    while (*s)
        hash += hash * 101 + *s++;
    return hash;
}
