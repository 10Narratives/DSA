#include <stdio.h>
#include "readline/readline.h"
#include <stdlib.h>

#include "structs.h"
#include "models.h"
#include "views.h"


// TODO неуспехи могут быть разные. Так что лучше 
// прописывать отдельной. ERR_DUPLICATE, ERR_еще ччто-нибудь

//все функции спроектированы на примере оформления из пояснительного файла к третьей лабе

int D_add(Table *table){
	char *errmsgs[] = {"FAILURE. DUPLICATE!", "SUCCESS ADD!"};
	char *key = readline("ENTER NEW KEY -->");
	if(!key)
		return ERR_MEM;
	char *info = readline("ENTER NEW INFO -->");
	if(!info)
		return ERR_MEM;
	int rc = add(table, key, info);
	printf("\n%s\n\n", errmsgs[rc]);
	return SUCCESS;
}

int print(Table *target){
	printf("KEY\tINFO\n------------\n");
	for(int i = 0; i < target->msize; i++){
		if(target->data[i].busy == 1){
			printf("|%s\t%s|\n", target->data[i].key, target->data[i].data->data);		
		}
	}
	printf("------------\n");
	return SUCCESS;
}

int D_import(Table *table){
	char *fpath = readline("ENTER PATH TO FILE -->");
	if(!fpath)
		return ERR_MEM;
	FILE *file = fopen(fpath, "r"); free(fpath);
	if(!file){
		printf("FILE DOES NOT EXIST!\n");
		return SUCCESS;
	}
	import(table, file);
	fclose(file);
	return SUCCESS;
}

int D_find(Table *table){ // TODO ф-я поика должна возваращать нову таблицу, которая содержит нужный\нужные элементы 
			  // таким образом, в диплоговой надо воздать новую таьлицу, спросить пользователя, передать это все в ф-ю поиска
			  // полученную таблицу вывести, затем все уничтожить 
	char *errmsgs[] = {"FAILURE. NOT FOUND", "SUCCESS FIND!"};
	char *key = readline("ENTER FIND KEY -->");
	if(!key)
		return ERR_MEM;
	KeySpace *foundKeySpace = find(table, key, NULL);
	int rc = -1;
	if(foundKeySpace){
		rc = SUCCESS;
		Table foundTable = initTable(1);
		foundTable.csize = 1;
		foundTable.data[0] = *foundKeySpace;
		print(&foundTable);
		free(foundTable.data);
	} else
		rc = ERR_NOT_FOUND;
	printf("\n%s\n\n", errmsgs[rc]);
	free(key);
	return SUCCESS;
}

int D_delete(Table *table){
	char *errmsgs[] = {"FAILURE. NOT FOUND", "SUCCESS DELETE!"};
	char *key = readline("ENTER NEW KEY -->");
	if(!key)
		return ERR_MEM;
	int rc = delete(table, key);
	printf("\n%s\n\n", errmsgs[rc]);
	free(key);
	return SUCCESS;
}

