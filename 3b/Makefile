lab3b: main.c dialog.c utils.c structs.c views.c models.c
	gcc -o lab3b main.c dialog.c utils.c structs.c views.c models.c -g -lreadline

start3b: lab3b
	valgrind --leak-check=full ./lab3b
	
