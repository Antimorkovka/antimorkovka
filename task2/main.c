#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


//read from FILE*, returns token
char* read(FILE*);

//Adds a contact
void add(char*, char*);

//Changes name or number of the contact
void change(int, char*, char*);

//Deletes contact
void delete(int);

//Finds contact by ID
int findid(int);

//Finds by string
void find(char*);

//Changes all symbols to lowercase
char* makelower(char*);

//Error print
bool checkinput(char*);

//Rewrite the file
void makeupdate();


//One contact:
typedef struct
{
	int id;
	char *name;
	char *number;
} record;

//Contacts:
typedef struct
{
	int size;
	record *contacts;
} book;



FILE *source;
char *filename;
book phonebook;
int id_current;



char *read(FILE *inputfile)
{
	getc(inputfile);
	char *token = malloc(0 * sizeof(char)), c = fgetc(inputfile);
	int i = 0, j = 0;
	while ((c != EOF) && (c != ' ') && (c != '\n'))
	{
		if (!(i % 128))
		{
			j++;
			token = realloc(token, (j * 128) * sizeof(char));
		}
		token[i++] = c;
		c = fgetc(inputfile);
	}
	token[i] = '\0';
	ungetc(' ', inputfile);
	return token;
}



void add(char *name, char *number)
{
	phonebook.size++;
	phonebook.contacts = realloc(phonebook.contacts, phonebook.size * sizeof(record));
	phonebook.contacts[phonebook.size - 1].id = id_current;
	phonebook.contacts[phonebook.size - 1].name = name;
	phonebook.contacts[phonebook.size - 1].number = number;
	fprintf(source, "%d %s %s\n", id_current++, name, number);
	return;
}



void change(int id, char *action, char *newValue)
{
	int i = findid(id);
	if (i >= 0)
	{
		if (!strcmp(action, "number"))
		{
			strcpy(phonebook.contacts[i].number, newValue);
		}
		else if (!strcmp(action, "name"))
		{
			strcpy(phonebook.contacts[i].name, newValue);
		}
		else
		{
			printf("Error: don't understand command \"%s\".\n", action);
			return;
		}
		makeupdate();
	}
	return;
}



void delete(int id)
{
	int i = findid(id);
	if (i >= 0)
	{
		phonebook.contacts[i].id = 0;
		makeupdate();
	}
	return;
}



int findid(int id)
{
	int i;
	for (i = 0; i < phonebook.size; i++)
	{
		if (phonebook.contacts[i].id == id)
		{
			return i;
		}
	}
	return -1;
}



void find(char *input)
{
	int i;
	bool found = false;
	input = makelower(input);
	if (isdigit(input[0]))
	{
		for (i = 0; i < phonebook.size; i++)
		{
			if ((phonebook.contacts[i].id) && (!strcmp(makelower(phonebook.contacts[i].number), input)))
			{
				printf("%d %s %s\n", phonebook.contacts[i].id, phonebook.contacts[i].name, phonebook.contacts[i].number);
				found = true;
			}
		}
	}
	else
	{
		for (i = 0; i < phonebook.size; i++)
		{
			if ((phonebook.contacts[i].id) && (strstr(makelower(phonebook.contacts[i].name), input)))
			{
				printf("%d %s %s\n", phonebook.contacts[i].id, phonebook.contacts[i].name, phonebook.contacts[i].number);
				found = true;
			}
		}
	}
	if (!found)
	{
		printf("Error: no such contact.\n");
	}
	return;
}



char *makelower(char *input)
{
	int i = 0;
	bool isname = (isalpha(input[0]) ? true : false);
	char *answer = malloc(strlen(input) * sizeof(char));

	i = 0;
	int j = 0;
	if (!isname)
	{
		while (input[i] != '\0')
		{
			if (isdigit(input[i]))
			{
				answer[j++] = input[i];
			}
			i++;
		}
		answer[j] = '\0';
	}
	else
	{
		while (input[i] != '\0')
		{
			answer[i] = tolower(input[i++]);
		}
		answer[i] = '\0';
	}
	return answer;
}



bool checkinput(char *input)
{
	if (!strcmp(input, ""))
	{
		printf("Error:empty input\n");
		return false;
	}

	int i = 0;
	if (isalpha(input[0]))
	{
		while (input[i] != '\0')
		{
			if (!isalpha(input[i++]))
			{
				printf("Error:use only allowed letters.\n");
				return false;
			}
		}
	}
	else
	{
		while (input[i] != '\0')
		{
			if (isdigit(input[i++]))
			{
				return true;
			}
		}
		printf("Error:phone number don't contain any digit.\n");
		return false;
	}
	return true;
}



void makeupdate()
{
	freopen(filename, "w", source);
	int i;
	for (i = 0; i < phonebook.size; i++)
	{
		if (phonebook.contacts[i].id)
		{
			fprintf(source, "%d %s %s\n", phonebook.contacts[i].id, phonebook.contacts[i].name, phonebook.contacts[i].number);
		}
	}
	freopen(filename, "a+", source);
	return;
}


int main(int argc, const char *argv[])
{
	filename = argv[1];
	source = fopen(filename, "a+");
	if (source == NULL)
	{
		perror("Error!");
	}

	phonebook.size = 0;
	phonebook.contacts = malloc(phonebook.size * sizeof(record));

	int id;
	rewind(source);
	while (fscanf(source, "%d", &id) == 1)
	{
		phonebook.size++;
		phonebook.contacts = realloc(phonebook.contacts, phonebook.size * sizeof(record));
		phonebook.contacts[phonebook.size - 1].id = id;
		phonebook.contacts[phonebook.size - 1].name = read(source);
		phonebook.contacts[phonebook.size - 1].number = read(source);
	}
	id_current = (phonebook.size ? (phonebook.contacts[phonebook.size - 1].id + 1) : 1);

	char *command = malloc(16 * sizeof(char)), *input, *name, *number;
	while (1)
	{
		scanf("%s", command);

		if (!strcmp(command, "find"))
		{
			input = read(stdin);
			if (checkinput(input))
			{
				find(input);
			}
		}
		else if (!strcmp(command, "create"))
		{
			name = read(stdin);
			number = read(stdin);
			if (checkinput(name) && checkinput(number))
			{
				add(name, number);
			}
		}
		else if (!strcmp(command, "delete"))
		{
			scanf("%d", &id);
			delete(id);
		}
		else if (!strcmp(command, "change"))
		{
			scanf("%d%s", &id, command);
			input = read(stdin);
			if (checkinput(input))
			{
				change(id, command, input);
			}
		}
		else if (!strcmp(command, "exit"))
		{
			fclose(source);

			free(name);
			free(number);
			free(command);
			free(input);
			free(phonebook.contacts);

			return 0;
		}
		else
		{
			printf("Error:invalid command \"%s\".\n", command);
		}
		fflush(stdout);
	}
}
