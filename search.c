#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N_BOOKS 100

struct book
{
    char book_id[10];
    char title[100];
    char auth[50];
    char publ[50];
    int n_copies;
} books[N_BOOKS];

// reads books from file
void initialize()
{
    FILE *fp;
    char str[1000];
    char* filename1 = "/home/ashwini/my_stuff/C/books.txt";
    fp = fopen(filename1, "r");
    if (fp == NULL)
    {
        printf("Library is closed! Come again later. %s",filename1);
        return;
    }
    int i = 0;
    
    while (fgets(str, 1000, fp) != NULL)
    {
        char* token = strtok(str, ";");
        // each issue needs unique id
        strcpy(books[i].book_id,token);
        token = strtok(NULL, ";");
        strcpy(books[i].title,token);
        token = strtok(NULL, ";");
        strcpy(books[i].auth,token);
        token = strtok(NULL, ";");
        strcpy(books[i].publ,token);
        token = strtok(NULL, ";");
        books[i].n_copies = atoi(token);
        token = strtok(NULL, ";");
        i++;
    }
    fclose(fp);
}
    //Now we have a list of books which contain struct book




char* separate(char word[100])  //function for separating out words from strings
{
	static char wordlist[30][100];
	int k=0;
	char *ptr = strtok(word, " ");
	while(ptr != NULL)
	{
		strcpy(wordlist[k], ptr);
		k = ++k;
		ptr = strtok(NULL, " ");
	}
	return wordlist;
}






void search()  // search function
{
	char query[100];
	int j=0;
	printf("Input search term :  ");
	scanf("%s", &query);
	printf("Book ID    Book Title    Author    Publisher    Available Copies\n");
	for (int i = 0; i < N_BOOKS; i++)
	{
		if (strcasecmp(books[i].book_id, query) == 0 || strcasecmp(books[i].title, query) == 0 || strcasecmp(books[i].auth, query) == 0 || strcasecmp(books[i].publ, query) == 0)
		{
			printf("Matched Results : \n %s    %s    %s    %s    %d", books[i].book_id, books[i].title, books[i].auth, books[i].publ, books[i].n_copies);
		}
	}
}