/*
    strdup, strndup, sprintf, getline
*/

char *strdup(const char *s)
{
    void *p = malloc(strlen(s) + 1);
    if (p)
        strcpy(p, s);

    return p;
}

char *strndup(const char *s, size_t n)
{
    void *p = malloc(n + 1);
    if (p)
        memcpy(p, s, n + 1);

    return p;
}

ssize_t getline(void **p, size_t *n, FILE *f)
{
    size_t size = *n;
    ssize_t read = 0;
    int ch;

    while ((ch = fgetc(f)) != EOF)
    {
        if (read >= (ssize_t)size - 1)
        {
            size += 16;
            char *tmp = (char *)realloc(*p, size);
            if (tmp == NULL)
                return -1;
            *p = tmp;
            *n = size;
        }
        (*p)[read++] = (char)ch;
        if (ch == '\n')
            break;
    }

    if (read > 0)
    {
        (*p)[read] = '\0';
        return read;
    }

    return -1;
}
