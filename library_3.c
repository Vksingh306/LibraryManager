#include <stdio.h>
#include <string.h>

#define N_BOOKS 10
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
    //issue 5 books at a time
    char issued[N_ALLOWED_F][10];
} users[N_USERS];

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

// does the rest
void main()
{
    initialize();
    struct book boo;
    struct user use;
    boo = books[1];
    use = users[1];

    int status = 1;
    int days;
    char err_msg[100];

    if(is_faculty(use))
    {
        if(n_issued(use) >= N_ALLOWED_F)
        {
            status = 0;
            strcpy(err_msg,"You have already issued the maximum number of books allowed.");
        }
        else if(hasbook(use,boo))
        {
            status = 0;
            strcpy(err_msg,"You have already issued a copy of this book.");
        }
    }
    else
    {
        if(n_issued(use) >= N_ALLOWED_S)
        {
            status = 0;
            strcpy(err_msg,"You have already issued the maximum number of books allowed.");
        }
        else if(boo.n_copies < 3)
        {
            status = 0;
            strcpy(err_msg,"Students are not allowed to issue books with less than 3 copies.");
        }
        else if(hasbook(use,boo))
        {
            status = 0;
            strcpy(err_msg,"You have already issued a copy of this book.");
        }
    }

    if(status == 1)
    {
       days = available_days(boo);
       strcpy(use.issued[n_issued(use)],boo.book_id);
    }
    else
    {
        printf("%s",err_msg);
    }
    // printf("%s",use.issued[3]);
}