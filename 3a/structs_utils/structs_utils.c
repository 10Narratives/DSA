#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../structs.h"

int have_key(Table *table, char* checking_key, int *index){
	int curr_size = (*table).csize;
	int i = - 1, flag = 0;
	for(i = 0; i < curr_size; i++){
		if(strcmp((*table).ks[i].key, checking_key) == 0){
			flag = 1;
			break;
		}
	} 
	if(flag){
		*index = i;
		return 1;
	} else {
		return 0;
	}
}

int have_version(List *list, int vers){
	Node *ptr = list->head;
		int counter = -1;
		while(ptr){
			ptr = ptr->next;
			counter++;
			if(vers == counter){
				return 1;
			}
		}		
		return 0;
}

int delete_list(List *list){
	if(!list) return 1;
    Node *ptr = list->head, *ptr_prev = NULL;
	while (ptr) {
        ptr_prev = ptr;
        ptr = ptr->next;
        free(ptr_prev->data);
        free(ptr_prev);
    }
    free(list);
    return 0;
}

int list_delete_node(List *list, int vers){
	Node *ptr = list->head, *ptr_prev = NULL;
	while(ptr && ptr->version != vers){
		ptr_prev = ptr;
		ptr = ptr->next;
	}
	Node *ptr_r = NULL;
	if(ptr->version == vers){
		if(ptr == list->head){
			list->head = ptr->next;
			free(ptr->data);
			free(ptr);
			list->size--;
			ptr_r = list->head;
		} else{
			ptr_prev->next = ptr->next;
			free(ptr->data);
			free(ptr);
			list->size--;
			ptr_r = ptr_prev->next;		
		}
	}
	while(ptr_r){
		ptr_r->version--;
		ptr_r = ptr_r->next;
	}
	return 1;
}


int list_push(List *list, char* data){
	list->size += 1;
	Node *new_record = calloc(1, sizeof(Node));
	new_record->data = data;
	if(!list->head){
		new_record->version = 0;
		list->head = new_record;	
	} else{
		Node *tmp = list->head;
		new_record->version = tmp->version + 1;
		list->head = new_record;
		new_record->next = tmp;				
	}
	return 1;
}

List *copy_list(List *source){
	List *copy_l = calloc(1, sizeof(List));
	Node *ptr = source->head;

	while(ptr){
		list_push(copy_l, strdup(ptr->data));
		ptr = ptr->next;
	}
	
	return copy_l;
}

Node *copy_node(Node *source){
	Node *copy_n = calloc(1, sizeof(List));
	copy_n->version = source->version;
	copy_n->data = strdup(source->data);
	return copy_n;
}

int find_node(List *list, Node **buf, int vers){
	Node *ptr = list->head;
	while(ptr){
		if(ptr->version == vers){
			*buf = ptr;
			return 1;
		} 
		ptr = ptr->next;
	}
	return 0;
}
