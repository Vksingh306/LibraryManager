#include <stdio.h>
#include <string.h> 
struct user   //defines user
{
	char user_id[10];  //maximum length of id is 10 characters
} users[1000];         // maximum length of the list is 1000 entries

 
char username[10];     // input login id of max 10 characters

int is_faculty(char username[]) //function to check user or admin
	{
		
		int var_admin=0;        //binary variable that decides the outcome, default user
		
    	if(username[0]=='A'){    //admin ids begin with A
		    var_admin=1;         //changes the output
        	printf("\nAdmin");
    	}else{
			var_admin=var_admin;  // does not change the output
			printf("\nUser");
		}
		return var_admin;     //returns the output binary variable
		
	}
 
 
int login(char username[]) //to check against list the input username
{ 
    FILE *fp;      
    
    char str[1000];    
    char* filename2 = "C:\\Users\\User\\Desktop\\users.txt"; //the file path
    int i; //a variable that changes for each entry in the list
    i = 0;
    fp = fopen(filename2, "r"); //opens the list
	
    int var_login=0; //binary variable that decides if login happens or not, default is logged out
	    
    if (fp == NULL)
    {
        	printf("Could not open file %s",filename2); // in case the file path is wrong
        	return 0;
    }
    while (fgets(str, 1000, fp) != NULL)//till the end of the list entries
    {
       	char* token = strtok(str, ";"); // breaks the string into a set of smaller strings using the ; delimiter
       	strcpy(users[i].user_id,token);  //copies the strings that are formed to users.user_id
       	
       	if(strcmp(username,users[i].user_id)==0){  // checks id the username and user id are same,if same login   
           	var_login=1;
       		printf("\nLogin Success!");         	
       	}else{ 
        	var_login=var_login;            
       	}     
    	token = strtok(NULL, ";");  //jumps to next line after ";"
		i++;
    }
    if (var_login==0)
	{
    	printf("\nUser doesn't exist");
	}
	return var_login;
}

int main()
{
	int a,b;
	printf("Enter your userid:\n"); //input
    scanf("%s",&username); //username is stored
    a = login(username); //takes the var_login
    if (a==1)
    {
    	b = is_faculty(username); //if login happens, stores the binary variable for user/admin
	}
	return a;
	return b;
    
}


