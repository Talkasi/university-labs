#include "associative_array.h"
#include <stdlib.h>
#include <string.h>

typedef struct node node_t;

struct node
{
    const char *key;
    int num;

    node_t *next;
};

struct assoc_array_type
{
    node_t *head;
};

/**
 * Создает объект ассоциативный массив.
 *
 * \return Созданный объект или NULL
 */
assoc_array_t assoc_array_create(void)
{
    return calloc(1, sizeof(struct assoc_array_type));
}

/**
 * Удаляет объект ассоциативный массив.
 *
 * \param[in,out] arr - описатель массив
 *
 * После вызова этой функции переменная, переданная в качестве параметра, имеет
 * значение NULL.
 */
void assoc_array_destroy(assoc_array_t *arr)
{
    if (arr != NULL)
    {
        if (*arr != NULL)
            for (node_t *cur = (*arr)->head; cur;)
            {
                node_t *tmp = cur->next;
                free(cur);
                cur = tmp;
            }

        free(*arr);
        *arr = NULL;
    }
}

/**
 * Добавляе пару "ключ-значение" в ассоциативный массив.
 *
 * \param[in,out] arr - описатель массива
 * \param[in] key - ключ
 * \param[in] num - значение
 *
 * \note Ключ не может быть пустой строкой.
 *
 * \return ASSOC_ARRAY_OK или код ошибки (ASSOC_ARRAY_INVALID_PARAM, ASSOC_ARRAY_MEM, ASSOC_ARRAY_KEY_EXISTS)
 */
assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (arr == NULL || key == NULL || *key == '\0')
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *cur = arr->head;
    if (cur != NULL)
    {
        for (; cur->next; cur = cur->next)
            if (strcmp(cur->key, key) == 0)
                return ASSOC_ARRAY_KEY_EXISTS;

        if (strcmp(cur->key, key) == 0)
            return ASSOC_ARRAY_KEY_EXISTS;
    }

    node_t *tmp = calloc(1, sizeof(node_t));
    if (tmp == NULL)
        return ASSOC_ARRAY_MEM;

    tmp->num = num;
    tmp->key = key;
    tmp->next = NULL;

    if (cur == NULL)
        arr->head = tmp;
    else
        cur->next = tmp;

    return ASSOC_ARRAY_OK;
}

/**
 * Возвращает значение по ключу.
 *
 * \param[in] arr - описатель массива
 * \param[in] key - ключ
 * \param[out] num - указатель на значение, соответствующее ключу (в случае успеха)
 *
 * \note Ключ не может быть пустой строкой.
 *
 * \return ASSOC_ARRAY_OK или код ошибки (ASSOC_ARRAY_INVALID_PARAM, ASSOC_ARRAY_NOT_FOUND)
 */
assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (arr == NULL || key == NULL || *key == '\0' || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (node_t *cur = arr->head; cur; cur = cur->next)
        if (strcmp(cur->key, key) == 0)
        {
            *num = &cur->num;
            return ASSOC_ARRAY_OK;
        }

    return ASSOC_ARRAY_NOT_FOUND;
}

/**
 * Удаляет значение по ключу.
 *
 * \param[in,out] arr - описатель массива
 * \param[in] key - ключ
 *
 * \return ASSOC_ARRAY_OK или код ошибки (ASSOC_ARRAY_INVALID_PARAM, ASSOC_ARRAY_MEM, ASSOC_ARRAY_NOT_FOUND)
 */
assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (arr == NULL || key == NULL || *key == '\0')
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *parent = NULL;
    for (node_t *cur = arr->head; cur; parent = cur, cur = cur->next)
        if (strcmp(cur->key, key) == 0)
        {
            if (parent != NULL)
            {
                parent->next = cur->next;
                free(cur);
            }
            else
            {
                node_t *tmp = arr->head;
                arr->head = cur->next;
                free(tmp);
            }

            return ASSOC_ARRAY_OK;
        }

    return ASSOC_ARRAY_NOT_FOUND;
}

/**
 * Очищает ассоциативный массив (т.е. массив становится пустым).
 *
 * \param[in,out] arr - описатель массива
 *
 * \return ASSOC_ARRAY_OK или код ошибки (ASSOC_ARRAY_INVALID_PARAM)
 */
assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (arr == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (node_t *cur = arr->head; cur;)
    {
        node_t *tmp = cur->next;
        free(cur);
        cur = tmp;
    }

    arr->head = NULL;
    return ASSOC_ARRAY_OK;
}

/**
 * Применяет к значениям указанное действие.
 *
 * \param[in] arr - описатель массива
 * \param[in] action - указатель на функцию обратного вызова для обработки очередного значения
 * \param[in] param - параметр функции обратного вызова (может быть NULL)
 *
 * \return ASSOC_ARRAY_OK или код ошибки (ASSOC_ARRAY_INVALID_PARAM)
 */

typedef void (*action_t)(const char *key, int *num, void *param);
assoc_array_error_t assoc_array_each(const assoc_array_t arr, action_t action, void *param)
{
    if (arr == NULL || action == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (node_t *cur = arr->head; cur; cur = cur->next)
        action(cur->key, &cur->num, param);

    return ASSOC_ARRAY_OK;
}

/**
 * Возвращает значение соответствующее минимальному ключу.
 *
 * \param[in] arr - описатель массива
 * \param[out] num - указатель на значение, соответствующее минимальному ключу (в случае успеха)
 *
 * \return ASSOC_ARRAY_OK или код ошибки (ASSOC_ARRAY_INVALID_PARAM, ASSOC_ARRAY_NOT_FOUND - т.е. массив пустой)
 */
assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (arr->head == NULL)
        return ASSOC_ARRAY_NOT_FOUND;

    const char *min_key = arr->head->key;
    int *min_num = &arr->head->num;

    for (node_t *cur = arr->head->next; cur; cur = cur->next)
        if (strcmp(cur->key, min_key) < 0)
        {
            min_key = cur->key;
            min_num = &cur->num;
        }

    *num = min_num;
    return ASSOC_ARRAY_OK;
}

/**
 * Возвращает значение соответствующее максимальному ключу.
 *
 * \param[in] arr - описатель массива
 * \param[out] num - указатель на значение, соответствующее максимальному ключу (в случае успеха)
 *
 * \return ASSOC_ARRAY_OK или код ошибки (ASSOC_ARRAY_INVALID_PARAM, ASSOC_ARRAY_NOT_FOUND - т.е. массив пустой)
 */
assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (arr->head == NULL)
        return ASSOC_ARRAY_NOT_FOUND;

    const char *max_key = arr->head->key;
    int *max_num = &arr->head->num;

    for (node_t *cur = arr->head->next; cur; cur = cur->next)
        if (strcmp(cur->key, max_key) > 0)
        {
            max_key = cur->key;
            max_num = &cur->num;
        }

    *num = max_num;
    return ASSOC_ARRAY_OK;
}
