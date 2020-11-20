#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 100000


void readFile(FILE * fPtr);


int main()
{
    /* File pointer to hold reference of input file */
    FILE *fP;
    
    char *filename = "library.txt";

    char dataToAppend[BUFFER_SIZE];


    
   
   

    /*  Open all file in append mode. */
    fP = fopen(filename, "a");


   
    

    /* Input data to append from user */
    printf("\nEnter details of the book:\n ID ; Name of the Book ; Author ; Publisher ; Number of Copies\n ");
    fflush(stdin);          // To clear extra white space characters in stdin
    fgets(dataToAppend, BUFFER_SIZE, stdin);


    /* Append data to file */
    fputs(dataToAppend, fP);


    /* Reopen file in read mode to print file contents */
    fP = freopen(filename, "r", fP);

    /* Print file contents after appending string */
    printf("\n		Successfully added the Book to the Library. \n");
    printf("Updated list of Books:\n\n");
    readFile(fP);


    /* Done with file, hence close file. */
    fclose(fP);

    return 0;
}



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
