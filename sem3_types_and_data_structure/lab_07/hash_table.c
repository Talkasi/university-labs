#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_HT_SIZE 17

void insert_to_list(node_entry_t **head, node_entry_t *new_node)
{
    if (*head == NULL)
    {
        *head = new_node;
        return;
    }

	new_node->next = *head;
	*head = new_node;
}

void free_list(node_entry_t **head)
{
	node_entry_t *tmp;
	for (node_entry_t *cur_node = *head; cur_node; cur_node = tmp) {
        tmp = cur_node->next;
        free(cur_node);
	}

	*head = NULL;
}

int hash_good(char *key) {
    int hash = 0;
    for (int i = 0; key[i] != '\0'; ++i)
        hash = (hash * 31 + key[i]) % TABLE_SIZE;
    
    return hash;
}

int hash(char *key, size_t n) {
    int hash = 0;
    for (int i = 0; key[i] != '\0'; ++i)
        hash = (hash + key[i]);
    
    return hash % n;
}


list_hash_table_t *create_list_hash_table() {
    list_hash_table_t *ht = calloc(1, sizeof(list_hash_table_t));
    ht->table = calloc(TABLE_SIZE, sizeof(node_entry_t *));
    ht->cur_size = START_HT_SIZE;
    return ht;
}

void destroy_list_hash_table(list_hash_table_t **ht) {
	if (*ht != NULL) {
		free((*ht)->table);
		free(*ht);
	}

	*ht = NULL;
}


void insert_list_hash_table(list_hash_table_t *ht, char *key) {
    int index = hash(key, ht->cur_size);

    node_entry_t *new_entry = calloc(1, sizeof(node_entry_t));
    memcpy(new_entry->key, key, MAX_WORD_LEN);
    new_entry->next = NULL;

    if (ht->table[index] == NULL) {
        ht->table[index] = new_entry;
    } else {
        node_entry_t *current = ht->table[index];
        while (current->next != NULL)
            current = current->next;
        
        current->next = new_entry;
    }
}

void restruct_list_hash_table(list_hash_table_t *ht)
{
    node_entry_t *list = NULL;
    for (int i = 0; i < ht->cur_size; ++i)
        for (node_entry_t *cur_node = ht->table[i]; cur_node; cur_node = cur_node->next) {
        	node_entry_t *new_node = calloc(1, sizeof(node_entry_t));
        	if (new_node == NULL) {
        		printf("Unable to restruct the table.\n");
        		free_list(&list);
        		return;
        	}

        	strcpy(new_node->key, cur_node->key);
        	insert_to_list(&list, new_node);
        }
    
    ht->cur_size = 997;
    for (node_entry_t *cur_node = list; cur_node; cur_node = cur_node->next)
        insert_list_hash_table(ht, cur_node->key);

    free_list(&list);
}

void create_list_hash_table_from_file(FILE *f, list_hash_table_t *ht) {
    char word[MAX_WORD_LEN];
    fseek(f, 0, SEEK_SET);
    while (fscanf(f, "%s", word) != EOF)
        insert_list_hash_table(ht, word); 
}

void print_list_hash_table(list_hash_table_t *ht) {
	printf("Hash -> Word\n");
	for (int i = 0; i < ht->cur_size; ++i)
		for (node_entry_t *cur_entry = ht->table[i]; cur_entry; cur_entry = cur_entry->next)
			printf("%4d -> %s\n", i, cur_entry->key);

	printf("\n");
}

void delete_list_hash_table(list_hash_table_t *ht, char *key) {
	int cur_hash = hash(key, ht->cur_size);

	if (ht->table[cur_hash] == NULL)
		return;

	if (strcmp(key, ht->table[cur_hash]->key) == 0) {
		if (ht->table[cur_hash]->next == NULL) {
			free(ht->table[cur_hash]);
			ht->table[cur_hash] = NULL;
		} else {
			node_entry_t *tmp = ht->table[cur_hash]->next;
			ht->table[cur_hash]->next = ht->table[cur_hash]->next->next;
			free(tmp);
		}

		return;
	}

	for (node_entry_t *cur_entry = ht->table[cur_hash]; cur_entry; cur_entry = cur_entry->next)
		if (strcmp(key, cur_entry->next->key) == 0) {
			node_entry_t *tmp = cur_entry->next;
			cur_entry->next = cur_entry->next->next;
			free(tmp);
			return;
		}
}

char *search_list_hash_table(list_hash_table_t *ht, char *key) {
	int cur_hash = hash(key, ht->cur_size);
	++ht->n_searches;

	++ht->n_compare;
	if (ht->table[cur_hash] == NULL)
		return NULL;

	for (node_entry_t *cur_entry = ht->table[cur_hash]; cur_entry; cur_entry = cur_entry->next) {
		++ht->n_compare;
		if (strcmp(key, cur_entry->key) == 0)
			return cur_entry->key;
	}

	return NULL;
}

arr_hash_table_t *create_arr_hash_table() {
    arr_hash_table_t *ht = calloc(1, sizeof(arr_hash_table_t));
    ht->cur_size = START_HT_SIZE;
    return ht;
}

void destroy_arr_hash_table(arr_hash_table_t **ht) {
	free(*ht);
	*ht = NULL;
}

void insert_arr_hash_table(arr_hash_table_t *ht, char *key) {
    int index = hash(key, ht->cur_size);

    if (ht->table[index][0] == '\0')
    	memcpy(ht->table[index], key, MAX_WORD_LEN);
    else {
    	int i = index + 1;
    	for (; i != index; i = (i + 1) % ht->cur_size)
    		if (ht->table[i][0] == '\0') {
    			memcpy(ht->table[i], key, MAX_WORD_LEN);
    			break;
    		}

    	if (i == index)
    		printf("There is no space in the hash table.\n");
    }
}

void restruct_arr_hash_table(arr_hash_table_t *ht)
{
    node_entry_t *list = NULL;
    for (int i = 0; i < ht->cur_size; ++i)
        if (ht->table[i][0] != '\0') {
        	node_entry_t *new_node = calloc(1, sizeof(node_entry_t));
        	if (new_node == NULL) {
        		printf("Unable to restruct the table.\n");
        		free_list(&list);
        		return;
        	}

        	strcpy(new_node->key, ht->table[i]);
        	insert_to_list(&list, new_node);
        }
    
    ht->cur_size = 997;
    for (node_entry_t *cur_node = list; cur_node; cur_node = cur_node->next)
        insert_arr_hash_table(ht, cur_node->key);

    free_list(&list);
}

void create_arr_hash_table_from_file(FILE *f, arr_hash_table_t *ht) {
    char word[MAX_WORD_LEN];
    fseek(f, 0, SEEK_SET);

    while (fscanf(f, "%s", word) != EOF)
        insert_arr_hash_table(ht, word); 
}

void print_arr_hash_table(arr_hash_table_t *ht) {
	printf("Hash -> Word\n");
	for (int i = 0; i < ht->cur_size; ++i)
		if (ht->table[i][0] != '\0')
			printf("%4d -> %s\n", hash(ht->table[i], ht->cur_size), ht->table[i]);

	printf("\n");
}

void delete_arr_hash_table(arr_hash_table_t *ht, char *key) {
	int cur_hash = hash(key, ht->cur_size);

	if (ht->table[cur_hash][0] == '\0')
		return;

	if (strcmp(ht->table[cur_hash], key) == 0)
		ht->table[cur_hash][0] = '\0';

	for (int i = cur_hash + 1; i != cur_hash; i = (i + 1) % ht->cur_size)
		if (strcmp(ht->table[i], key) == 0) {
			ht->table[i][0] = '\0';
			break;
		}
}

char *search_arr_hash_table(arr_hash_table_t *ht, char *key) {
	int cur_hash = hash(key, ht->cur_size);
	++ht->n_searches;

	++ht->n_compare;
	if (ht->table[cur_hash][0] == '\0')
		return NULL;

	++ht->n_compare;
	if (strcmp(ht->table[cur_hash], key) == 0)
		return ht->table[cur_hash];

	for (int i = cur_hash + 1; i != cur_hash; i = (i + 1) % ht->cur_size) {
		++ht->n_compare;
		if (strcmp(ht->table[i], key) == 0)
			return ht->table[i];
	}

	return NULL;
}
