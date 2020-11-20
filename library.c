#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N_BOOKS 100
#define N_USERS 10
#define N_ALLOWED_F 6
#define N_ALLOWED_S 3

struct book
{
    char book_id[10];
    char title[100];
    char auth[50];
    char publ[50];
    int n_copies;
} books[N_BOOKS];

struct user
{
    char user_id[10]; 
    char issued[N_ALLOWED_F][10];
} users[N_USERS];

//=======================================AGNI START==============================================================
// reads books and users from file (ignore this function for now)
void initialize()
{
    FILE *fp;
    char str[1000];
    char* filename1 = "D:\\OneDrive\\Desktop\\Programs\\CS3101\\My Tries\\books.txt";
    char* filename2 = "D:\\OneDrive\\Desktop\\Programs\\CS3101\\My Tries\\users.txt";
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
}

// gets number of copies of book x still in library
int n_available(struct book x)
{
    int count = 0;
    for(int i = 0; i < N_USERS; i++)
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
        if(strcmp(x.issued[i],"\0")!=0)
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

// book return
struct user book_return(struct user x, struct book y)
{
    for(int i = 0; i < N_ALLOWED_F; i++)
    {
        if(strcmp(x.issued[i],y.book_id)==0)
        {
            strcpy(x.issued[i],"\0");
            //add something to check if late return
        }
    }
    return(x);
}

//book issue
struct user book_issue(struct user x, struct book y)
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
       strcpy(x.issued[n_issued(x)],y.book_id);
       printf("Book succesfully issued.\n");
    }
    else
    {
        printf("%s",err_msg);
    }
    return(x);
}

// Returns position at which book is at
int which_book(char bookid[])
{
    int pos = -1;
    // searching for the position the requested book is located at
    for (int i = 0; i < N_BOOKS; i++)
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
    for (int i = 0; i < N_USERS; i++)
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
//===================================================AGNI END================================================================

//=================================================PANDA START=============================================================

/**
 * Reads a file character by character 
 * and prints on console.
 * 
 * @fPtr    Pointer to FILE to read.
 */
void readFile(FILE * fP)
{
    char ch;
    do 
    {
        ch = fgetc(fP);

        putchar(ch);

    } while (ch != EOF);
}

void add_book()
{
    int pos = 0;
    //get number of books already in records
    for(int i = 0; i < N_BOOKS; i++)
    {
        if (books[i].book_id==NULL)
        {
            pos = i;
            break;
        }
    }
    if (pos == N_BOOKS-1)
    {
        printf("\nLibrary is Full.\n");
        return;
    }

    /* Input data to append from user */
    char str[1000];
    printf("\nEnter details of the book:\n ID ; Title ; Author ; Publisher ; Number of Copies\n ");
    scanf("%s",str);

    char* token = strtok(str, ";");
    strcpy(books[pos+1].book_id,token);
    token = strtok(NULL, ";");
    strcpy(books[pos+1].title,token);
    token = strtok(NULL, ";");
    strcpy(books[pos+1].auth,token);
    token = strtok(NULL, ";");
    strcpy(books[pos+1].publ,token);
    token = strtok(NULL, ";");
    books[pos+1].n_copies = atoi(token);

    /* Print file contents after appending string */
    printf("\nSuccessfully added the Book to the Library. \n");
}

void delete_book()
{
    printf("Enter book id to be deleted\n");
    char bookid[10];
    scanf("%s",bookid);
    int pos = which_book(bookid);
    //deleting the book from our records
    //this is done by shifting all elements to the left from the required position 
    for (int i = pos; i < N_BOOKS-1; i++)
    {
        if (books[i].book_id!=NULL)
        {
            strcpy(books[i].book_id,books[i+1].book_id);
            strcpy(books[i].title,books[i+1].title);
            strcpy(books[i].auth,books[i+1].auth);
            strcpy(books[i].publ,books[i+1].publ);
            books[i].n_copies = books[i+1].n_copies;
        }
    }

}

void update_records()
{
    /* File pointer to hold reference of input file */
    FILE *fp;

    char* filename1 = "D:\\OneDrive\\Desktop\\Programs\\CS3101\\My Tries\\books.txt";
    char* filename2 = "D:\\OneDrive\\Desktop\\Programs\\CS3101\\My Tries\\users.txt";

    fp = fopen(filename1, "w");
    if (fp == NULL)
    {
        printf("Could not open file %s",filename1);
        return;
    }
    int i = 0;
    fprintf(fp,"ID;Title;Author;Publisher;Number\n");

    while (books[i].book_id != NULL)
    {
        fprintf(fp,"%s;%s;%s;%s;%d\n",books[i].book_id,books[i].title,books[i].auth,books[i].publ,books[i].n_copies);
        i++;
    }
    fclose(fp);
    printf("Updated list of Books:\n\n");
    readFile(fp);

    /* Done with file, hence close file. */
    fclose(fp);

    i = 0;
    int j = 0;
    fp = fopen(filename2, "w");
    fprintf(fp,"ID;Issued\n");

    if (fp == NULL)
    {
        printf("Could not open file %s",filename2);
        return;
    }
    while (users[i].user_id != NULL)
    {
        fprintf(fp,"%s;",users[i].user_id);
        j = 0;
        while(users[i].issued[j] != NULL)
        {
            fprintf(fp,"%s|",users[i].issued[j]);
            j++;
        }
        fprintf(fp,"\n");
        i++;
    }

    fclose(fp);

    printf("Updated list of Users:\n\n");
    readFile(fp);

    /* Done with file, hence close file. */
    fclose(fp);
}
//==================================================PANDA END==============================================================

//========================================ANKIT START===========================================================
// checks if user x is admin or not
int is_admin(struct user x)
{
    if(x.user_id[0]=='A')
        return(1);
    return(0);
}

int login(char userid[]) //to check against list the input username (0 for not found, 1 for user, 2 for admin)
{
    
    int var_login = 0; //binary variable that decides if login happens or not, default is logged out
    for(int i = 0; i < N_USERS; i++)
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
//=======================================ANKIT END===============================================================


//=======================================PARRY START=============================================================
void search()
{
    //some shit
}
//========================================PARRY END================================================================


//========================================VK START===============================================================
void main()
{
    initialize();

    char option_ad , user_id[10];
    int login_access = 0;
	
	printf("IISER Kolkata Library Catalogue \n");

    while(login_access==0)
    {
        printf("\nEnter your ID to Log In\n");
        scanf(" %s" , user_id);
        // Check if the provided id matches that in the file 
        login_access = login(user_id);
    }
	printf("Welcome  %s\n", user_id);
    printf("Login Successful!!\n");
    printf("Logged in as %s\n" , user_id);
    int user_pos = which_user(user_id);
    int book_pos;

    while(1)
    {
        switch (login_access)
        {
            case 1:  //USER
                printf("Privilege : User\n\n");
                printf("1 : Issue Book\n"); 
                printf("2 : Return Book\n");
                printf("3 : Search Book\n");
                printf("Enter your choice : ");
                scanf(" %c" , &option_ad);
                switch(option_ad)
                {
                    case '1' :
                        printf("Issue book\n");
                        printf("Enter Books ID of book to be issued\n");
                        scanf(" %s" , book_id);
                        book_pos = which_book(book_id);
                        book_issue(users[user_pos],books[book_pos]);
                        break;
                    case '2' :
                        printf("Return book\n");
                        printf("Enter Books ID of book to be returned\n");
                        scanf(" %s" , book_id);
                        book_pos = which_book(book_id);
                        book_return(users[user_pos],books[book_pos]);
                        break;
                    case '3' :
                        // Add function to search book - TBD : Perry
                        //printf
                        break;
                    default:
                        printf("Please choose a valid option\n");
                        break;
                }
                break;
            
            case 2:  //ADMIN
                printf("Privilege : Admin\n\n");
                printf("1 : Add Book\n"); 
                printf("2 : Delete Book\n");
                printf("3 : Edit Book\n");
                printf("4 : Search Book\n");
                printf("Enter your choice : ");
                scanf(" %c" , &option_ad);
                switch(option_ad)
                {
                    case '1' :
                        printf("Add book\n");
                        add_book();
                        break;
                    case '2' :
                        printf("Delete book\n");
                        delete_book();
                        break;
                    case '3' :
                        printf("Updating book\n");
                        printf("Delete previous record\n");
                        delete_book();
                        printf("Enter new record\n");
                        add_book();
                        break;
                    case '4' :
                        // Add function to search book - TBD : Perry
                        //printf
                        break;
                    default:
                        printf("Please choose a valid option\n");
                        break;
                }
                break;
            default:
                break;
        }
        printf("Do you want to do anything else? If yes, enter 1. If no, enter 2");
        int n;
        scanf("%d",&n);
        if (n==2)
            break;
    }
    update_records();
}
//========================================VK END=================================================================
