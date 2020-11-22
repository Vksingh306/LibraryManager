#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N_BOOKS 100
#define N_USERS 10
#define N_ALLOWED_F 6
#define N_ALLOWED_S 3

static int books_in_lib;
static int users_in_lib;

//Struct object to store book details
struct book
{
    char book_id[10];
    char title[100];
    char auth[50];
    char publ[50];
    int n_copies;
} books[N_BOOKS];

//Struct object to store user details
struct user
{
    char user_id[10]; 
    char issued[N_ALLOWED_F][10];
} users[N_USERS];

//=======================================Agnibha START==============================================================
// reads books and users from file
// Writes them into the structs
void initialize()
{
    FILE *fp;
    char str[1000];
    //Change path names as required
    char* filename1 = "books.txt";
    char* filename2 = "users.txt";
    fp = fopen(filename1, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s",filename1);
        return;
    }
    int i = 0;
    
    while (fgets(str, 1000, fp) != NULL)
    {
        char* token = strtok(str, ";");
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
    books_in_lib = i;
    fclose(fp);

    i = 0;
    int j = 0;
    fp = fopen(filename2, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s",filename2);
        return;
    }
    while (fgets(str, 1000, fp) != NULL)
    {
        char* token = strtok(str, ";");
        strcpy(users[i].user_id,token);
        token = strtok(NULL, ";");

        char* token2 = strtok(token, "|");
        j = 0;
        while(token2 != NULL)
        {
            strcpy(users[i].issued[j],token2);
            token2 = strtok(NULL, "|"); 
            j++;
        }
        token = strtok(NULL, ";");
        i++;
    }
    users_in_lib = i;
}

// Returns position at which book is at
int which_book(char bookid[])
{
    int pos = -1;
    // searching for the position the requested book is located at
    for (int i = 0; i < books_in_lib; i++)
    {
        if (strcmp(bookid,books[i].book_id)==0)
        {
            pos = i;
            break;
        }
    }
    if (pos==-1)
    {
        printf("\nBook not found\n");
    }
    return(pos);
}

// Returns position at which user is at
int which_user(char userid[])
{
    int pos = -1;
    // searching for the position the requested book is located at
    for (int i = 0; i < users_in_lib; i++)
    {
        if (strcmp(userid,users[i].user_id)==0)
        {
            pos = i;
            break;
        }
    }
    if (pos==-1)
    {
        printf("\nUser not found\n");
    }
    return(pos);
}

// gets number of copies of book x still in library
int n_available(struct book x)
{
    int count = 0;
    for(int i = 0; i < users_in_lib; i++)
    {
        for(int j = 0; j < N_ALLOWED_F; j++)
        {
            if (strcmp(x.book_id,users[i].issued[j])==0)
                count++;
        }
    }
    return(x.n_copies - count);
}

// gets number of days book x can be issued for
int available_days(struct book x)
{
    int n_av = n_available(x);
    int days = 0;
    if (n_av < 3)
        days = 10;
    else if (n_av < 6)
        days = 20;
    else
        days = 30;
    
    return (days);
}

// checks if user x is faculty or not
int is_faculty(struct user x)
{
    if(x.user_id[0]=='F')
        return(1);
    return(0);
}

// gets number of books user x has already issued
int n_issued(struct user x)
{
    int count = 0;
    for(int i = 0; i < N_ALLOWED_F; i++)
    {
        if((x.issued[i][0]>=65) && (x.issued[i][0]<=90))
            count++;
    }
    return(count);
}

// checks if user x already has book y
int hasbook(struct user x, struct book y)
{
    for(int i = 0; i < N_ALLOWED_F; i++)
    {
        if(strcmp(x.issued[i],y.book_id)==0)
            return(1);
    }
    return(0);
}

// returns a book issued by the user
void book_return(struct user x, struct book y)
{
    int pos = -1;
    for(int i = 0; i < N_ALLOWED_F; i++)
    {
        if(strcmp(x.issued[i],y.book_id)==0)
        {
            pos = i;
        }
    }
    if (pos==-1)
    {
        printf("\n You have not issued this book.\n");
    }
    else
    {
        for(int i = pos; i < N_ALLOWED_F-1; i++)
        {
            strcpy(users[which_user(x.user_id)].issued[i],users[which_user(x.user_id)].issued[i+1]);
        }
        printf("\nBook has been returned.\n");
    }
    
}

// issues a book for the user
void book_issue(struct user x, struct book y)
{
    int status = 1;
    int days;
    char err_msg[100];

    if(is_faculty(x))
    {
        if(n_issued(x) >= N_ALLOWED_F)
        {
            status = 0;
            strcpy(err_msg,"You have already issued the maximum number of books allowed.\n");
        }
        else if(hasbook(x,y))
        {
            status = 0;
            strcpy(err_msg,"You have already issued a copy of this book.\n");
        }
    }
    else
    {
        if(n_issued(x) >= N_ALLOWED_S)
        {
            status = 0;
            strcpy(err_msg,"You have already issued the maximum number of books allowed.\n");
        }
        else if(y.n_copies < 3)
        {
            status = 0;
            strcpy(err_msg,"Students are not allowed to issue books with less than 3 copies.\n");
        }
        else if(hasbook(x,y))
        {
            status = 0;
            strcpy(err_msg,"You have already issued a copy of this book.\n");
        }
    }

    if(status == 1)
    {
        days = available_days(y);
        strcpy(users[which_user(x.user_id)].issued[n_issued(x)],y.book_id);
        printf("Book succesfully issued.\n");
        printf("You have issued it for %d days\n",days);
    }
    else
    {
        printf("%s",err_msg);
    }
}

//this function is run at the end of every run to store current records into file
void update_records()
{
    /* File pointer to hold reference of input file */
    FILE *fp;

    char* filename1 = "books.txt";
    char* filename2 = "users.txt";

    fp = fopen(filename1, "w");
    if (fp == NULL)
    {
        printf("Could not open file %s",filename1);
        return;
    }
    int i = 0;

    while (i<books_in_lib)
    {
        fprintf(fp,"%s;%s;%s;%s;%d\n",books[i].book_id,books[i].title,books[i].auth,books[i].publ,books[i].n_copies);
        i++;
    }
    fclose(fp);

    i = 0;
    int j = 0;
    fp = fopen(filename2, "w");

    if (fp == NULL)
    {
        printf("Could not open file %s",filename2);
        return;
    }
    while (i<users_in_lib)
    {
        fprintf(fp,"%s;",users[i].user_id);
        j = 0;
        while((users[i].issued[j][0]>=65) && (users[i].issued[j][0]<=90)) //Checking for Caps letter
        {
            fprintf(fp,"%s|",users[i].issued[j]);
            j++;
        }
        fprintf(fp,"\n");
        i++;
    }

    fclose(fp);
}
//===================================================Agnibha END================================================================

//=================================================Prajwal START=============================================================
// admin function to add a book to the library
void add_book()
{
    int pos = books_in_lib;
    if (pos == N_BOOKS)
    {
        printf("\nLibrary is Full.\n");
        return;
    }

    /* Input data to append from user */
    char id[10],title[100],auth[50],publ[50],idc[10];
    int n;
    printf("\nEnter details of the book:\n");
    printf("Enter Here: ");
    fflush(stdin);
    fgets(idc,100,stdin);
    printf("ID: ");
    fflush(stdin);
    fgets(id,100,stdin);
    id[strcspn(id, "\n")] = '\0';
    fflush(stdin);
    printf("\nTitle: ");
    fgets(title,100,stdin);
    title[strcspn(title, "\n")] = '\0';
    fflush(stdin);
    printf("\nAuthor: ");
    fgets(auth,100,stdin);
    auth[strcspn(auth, "\n")] = '\0';
    fflush(stdin);
    printf("\nPublisher: ");
    fgets(publ,100,stdin);
    publ[strcspn(publ, "\n")] = '\0';
    fflush(stdin);
    printf("\nNumber of Copies: (Then enter 1 to exit, 2 to do something else)\n");
    scanf(" %d\n",&n);

    strcpy(books[pos].book_id,id);
    strcpy(books[pos].title,title);
    strcpy(books[pos].auth,auth);
    strcpy(books[pos].publ,publ);
    books[pos].n_copies = n;

    books_in_lib++;
    printf("\nSuccessfully added the Book to the Library. \n");
}

// admin function to delete a book from the library
void delete_book()
{
    int pos = -1;
    printf("Enter book id to be deleted\n");
    char bookid[10];
    scanf("%s",bookid);
    pos = which_book(bookid);
    if(pos==-1)
    {
        printf("Book not found\n");
        return;
    }
    //deleting the book from our records
    //this is done by shifting all elements to the left from the required position 
    for (int i = pos; i < books_in_lib-1; i++)
    {
        strcpy(books[i].book_id,books[i+1].book_id);
        strcpy(books[i].title,books[i+1].title);
        strcpy(books[i].auth,books[i+1].auth);
        strcpy(books[i].publ,books[i+1].publ);
        books[i].n_copies = books[i+1].n_copies;
    }
    printf("Book succesfully deleted.\n");
    books_in_lib--;

}
//==================================================Prajwal END==============================================================

//========================================Ankit START===========================================================
// checks if user x is admin or not
int is_admin(struct user x)
{
    if(x.user_id[0]=='A')
        return(1);
    return(0);
}

//to check against list the input username (0 for not found, 1 for user, 2 for admin)
int login(char userid[]) 
{
    
    int var_login = 0; //binary variable that decides if login happens or not, default is logged out
    for(int i = 0; i < users_in_lib; i++)
    {
        if(strcmp(userid,users[i].user_id)==0) // checks id the username and user id are same,if same login   
        {  
            var_login = 1;
            if (is_admin(users[i])==1)
            {
                var_login = 2;
            }
            printf("\nLogin Success!");         	
        } 
    }    
    	
    if (var_login==0)
	{
    	printf("\nUser doesn't exist");
	}
	return(var_login);
}
//=======================================Ankit END===============================================================


//=======================================Ashwini START=============================================================
// search function that can search for exact or word matches
void search()  
{
	char query_long[100];
	printf("Input search term :  ");
	scanf("%s", query_long);
	printf("Book ID    Book Title    Author    Publisher    Available Copies\n");
	for (int i = 0; i < N_BOOKS; i++)
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

        char* token = strtok(query_title_c, " ");
        while(token != NULL)
        {
            if (strcasecmp(query_long, token) == 0)
            {
                printf("Matched Results in Title : \n %s    %s    %s    %s    %d\n", books[i].book_id, books[i].title, books[i].auth, books[i].publ, books[i].n_copies);
            }
            token = strtok(NULL, " ");
        }

        char* token1 = strtok(query_auth_c, " ");
        while(token1 != NULL)
        {
            if (strcasecmp(query_long, token1) == 0)
            {
                printf("Matched Results in Author : \n %s    %s    %s    %s    %d\n", books[i].book_id, books[i].title, books[i].auth, books[i].publ, books[i].n_copies);
            }
            token1 = strtok(NULL, " ");
        }

        char* token2 = strtok(query_publ_c, " ");
        while(token2 != NULL)
        {
            if (strcasecmp(query_long, token2) == 0)
            {
                printf("Matched Results in Publisher : \n %s    %s    %s    %s    %d\n", books[i].book_id, books[i].title, books[i].auth, books[i].publ, books[i].n_copies);
            }
            token2 = strtok(NULL, " ");
        }
	}
}
//========================================Ashwini END================================================================


//========================================Vivek START===============================================================
// the main interface with which the user/admin interacts with the library
void main()
{
    initialize();
    char option_ad , user_id[10] , choice;
    choice = '0';
    int login_access = 0;
	printf("===================================\n");
	printf("IISER Kolkata Library Catalogue \n");
    	printf("===================================\n");

	printf("1 : Log In\n");
	printf("2 : Search for a book\n");
   	printf("3 : Exit\n");
	printf("Enter your choice : ");
	//Asks the user to log in or search for a book without logging in or to exit
	scanf(" %c" , &choice);

	switch(choice)
    {
	case '1' :	//Log In 
    	while(login_access==0)
    	{
    	    printf("\nEnter your ID to Log In\n");
    	    scanf(" %s" , user_id);
    	    // Check if the provided id matches that in the file 
    	    login_access = login(user_id);
    	}
  	    printf("Welcome  %s\n", user_id);
    	    printf("Login Successful!\n");
  	    printf("Logged in as %s\n" , user_id);
	    //Print the books user currently has issued
    	    int user_pos = which_user(user_id);
    	    printf("Issued books:\n");
    	    for (int i=0; i<N_ALLOWED_F;i++)
        {
            if ((users[user_pos].issued[i][0]>=65) && (users[user_pos].issued[i][0]<=90))
                printf("%s, ",users[user_pos].issued[i]);
        }
    	int book_pos;
	
	    while(1)
    	{
    	    switch (login_access)		//This divides the log in as either User or Admin
    	    {
    	        case 1:  //USER
    	            printf("\nPrivilege : User\n\n");
    	            printf("1 : Issue Book\n"); 
    	            printf("2 : Return Book\n");
    	            printf("3 : Search Book\n");
    	            printf("Enter your choice : \n");
    	            scanf(" %c" , &option_ad);
    	            switch(option_ad)
    	            {
    	                case '1' :	//Issue Books
    	                    printf("Issue book\n");
    	                    printf("Enter Books ID of book to be issued\n");
                            char book_id[10];
    	                    scanf(" %s" , book_id);
    	                    book_pos = which_book(book_id);
    	                    book_issue(users[user_pos],books[book_pos]);
    	                    break;
    	                case '2' :	//Return Books
    	                    printf("Return book\n");
    	                    printf("Enter Books ID of book to be returned\n");
    	                    scanf(" %s" , book_id);
    	                    book_pos = which_book(book_id);
    	                    book_return(users[user_pos],books[book_pos]);
    	                    break;
    	                case '3' :	//Search books
    	                    search();
    	                    break;
    	                default:
    	                    printf("Please choose a valid option\n");
    	                    break;
    	            }
    	            break;
    	        
    	        case 2:  //ADMIN
    	            printf("\nPrivilege : Admin\n\n");
    	            printf("1 : Add Book\n"); 
    	            printf("2 : Delete Book\n");
    	            printf("3 : Edit Book\n");
    	            printf("4 : Search Book\n");
    	            printf("Enter your choice : \n");
    	            scanf(" %c" , &option_ad);
    	            switch(option_ad)
    	            {
    	                case '1' :	//Add book
    	                    printf("Add book\n");
    	                    add_book();
    	                    break;
    	                case '2' :	//Delete book
    	                    printf("Delete book\n");
    	                    delete_book();
    	                    break;
    	                case '3' :	//Update book record
    	                    printf("Updating book\n");
    	                    printf("Delete previous record\n");
    	                    delete_book();
    	                    printf("Enter new record\n");
    	                    add_book();
    	                    break;
    	                case '4' :	//Search a book
    	                    search();
    	                    break;
    	                default:
    	                    printf("Please choose a valid option\n");
    	                    break;
    	            }
    	            break;
                
    	        default:
    	            break;
    	    }
    	    printf("Do you want to exit? If yes, enter 1. If no, enter 2\n");
    	    int n;
    	    scanf("%d",&n);
    	    if (n==1)
    	        break;
    	}
        break;
    
    case '2' :			//this is a case for the very first 'switch' prompting user to search a book without log in
        search();
        break;
	
    case '3':			//Exit
        break;
    
    default :
    	printf("Please choose a valid input\n");
        break;
    }
    update_records();
}
//========================================Vivek END=================================================================
