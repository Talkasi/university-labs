#include "associative_array.h"
#include <stdlib.h>
#include <string.h>

#define CAPACITY 2

typedef struct
{
    const char *key;
    int num;
} data_t;

struct assoc_array_type
{
    data_t *data;
    size_t size;
    size_t alloced;
    size_t capacity;
};


/**
 * Создает объект ассоциативный массив.
 *
 * \return Созданный объект или NULL
 */
assoc_array_t assoc_array_create(void)
{
    assoc_array_t tmp = calloc(1, sizeof(struct assoc_array_type));

    if (tmp != NULL)
        tmp->capacity = CAPACITY;

    return tmp;
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
            free((*arr)->data);

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

    for (size_t i = 0; i < arr->size; ++i)
        if (strcmp(arr->data[i].key, key) == 0)
            return ASSOC_ARRAY_KEY_EXISTS;

    if (arr->size + 1 > arr->alloced)
    {
        data_t *tmp = realloc(arr->data, (arr->size + arr->capacity) * sizeof(data_t));
        if (tmp == NULL)
            return ASSOC_ARRAY_MEM;
        arr->data = tmp;
        arr->alloced += arr->capacity;
    }

    arr->data[arr->size].key = key;
    arr->data[arr->size].num = num;
    ++arr->size;

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

    for (size_t i = 0; i < arr->size; ++i)
        if (strcmp(arr->data[i].key, key) == 0)
        {
            *num = &arr->data[i].num;
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

    for (size_t i = 0; i < arr->size; ++i)
        if (strcmp(arr->data[i].key, key) == 0)
        {
            for (size_t j = i; j < arr->size - 1; ++j)
                arr->data[j] = arr->data[j + 1];
            --arr->size;
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

    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->alloced = 0;
    arr->capacity = CAPACITY;

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

    for (size_t i = 0; i < arr->size; ++i)
        action(arr->data[i].key, &arr->data[i].num, param);

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

    if (arr->data == NULL || arr->size == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    const char *min_key = arr->data[0].key;
    int *min_num = &arr->data[0].num;

    for (size_t i = 0; i < arr->size; ++i)
        if (strcmp(arr->data[i].key, min_key) < 0)
        {
            min_key = arr->data[i].key;
            min_num = &arr->data[i].num;
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

    if (arr->data == NULL || arr->size == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    const char *max_key = arr->data[0].key;
    int *max_num = &arr->data[0].num;

    for (size_t i = 0; i < arr->size; ++i)
        if (strcmp(arr->data[i].key, max_key) > 0)
        {
            max_key = arr->data[i].key;
            max_num = &arr->data[i].num;
        }

    *num = max_num;
    return ASSOC_ARRAY_OK;
}
