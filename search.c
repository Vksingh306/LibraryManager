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




void search()  
{
	char query_long[100];   //initializing a char array
	printf("Input search term :  ");       //prompt for inputing search string
	scanf("%s", query_long);               // taking user inputed string and storing in the variable query_long
	printf("Book ID    Book Title    Author    Publisher    Available Copies\n");
	for (int i = 0; i < N_BOOKS; i++)     //a for loop to continuously compare the strings irrespective of case
	{
		if (strcasecmp(books[i].book_id, query_long) == 0 || strcasecmp(books[i].title, query_long) == 0 || strcasecmp(books[i].auth, query_long) == 0 || strcasecmp(books[i].publ, query_long) == 0)
		{
			printf("Exactly Matched Results : \n %s    %s    %s    %s    %d\n", books[i].book_id, books[i].title, books[i].auth, books[i].publ, books[i].n_copies);
		}

        // Searching in parts for Title, Author and Publisher fields
        char query_title_c[100], query_auth_c[100], query_publ_c[100];
        strcpy(query_title_c,books[i].title);
        strcpy(query_auth_c,books[i].auth);
        strcpy(query_publ_c,books[i].publ);

        char* token = strtok(query_title_c, " ");  //seperating strings from whitespaces
        while(token != NULL)
        {
            if (strcasecmp(query_long, token) == 0) //if condition for comparing inputed search string and the seperated string using whitespace
            {
                printf("Matched Results in Title : \n %s    %s    %s    %s    %d\n", books[i].book_id, books[i].title, books[i].auth, books[i].publ, books[i].n_copies);
            }
            token = strtok(NULL, " ");    //srtok needs NULL element to extract the next element in the string being splitted
        }

        char* token1 = strtok(query_auth_c, " ");
        while(token1 != NULL)  // strtok function returns NULL when pointer reaches the end. When that happens the while condition becomes false.
        {
            if (strcasecmp(query_long, token1) == 0) // looking for search term in authors column of database
            {
                printf("Matched Results in Author : \n %s    %s    %s    %s    %d\n", books[i].book_id, books[i].title, books[i].auth, books[i].publ, books[i].n_copies);
            }
            token1 = strtok(NULL, " ");    //srtok needs NULL element to extract the next element in the string being splitted
        }

        char* token2 = strtok(query_publ_c, " ");
        while(token2 != NULL)
        {
            if (strcasecmp(query_long, token2) == 0)    // looking for search term in publisher column of database.
            {
                printf("Matched Results in Publisher : \n %s    %s    %s    %s    %d\n", books[i].book_id, books[i].title, books[i].auth, books[i].publ, books[i].n_copies);
            }
            token2 = strtok(NULL, " ");       //srtok needs NULL element to extract the next element in the string being splitted
        }
	}
}
