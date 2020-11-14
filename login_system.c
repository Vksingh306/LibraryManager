#include <stdio.h>
#include <string.h> 
struct user
{
	char user_id[10];
} users[1000];

 
char username[10];

int is_faculty(char [username])
	{
		
		int var_admin=0;
		
    	if(username[0]=='A'){
		    var_admin=1;
        	printf("\nAdmin");
    	}else{
			var_admin=var_admin;
			printf("\nUser");
		}
		return var_admin;
		
	}
 
 
int login(char [username]) 
{ 
    FILE *fp;
    
    char str[1000];
    char* filename2 = "C:\\Users\\User\\Desktop\\users.txt";
    int i;
    i = 0;
    fp = fopen(filename2, "r");
	
    int var_login=0;
	    
    if (fp == NULL)
    {
        	printf("Could not open file %s",filename2);
        	return 0;
    }
    while (fgets(str, 1000, fp) != NULL)
    {
       	char* token = strtok(str, ";");
       	strcpy(users[i].user_id,token);
       	
       	if(strcmp(username,users[i].user_id)==0){     
           	var_login=1;
       		printf("\nLogin Success!");         	
       	}else{ 
        	var_login=var_login;            
       	}     
    	token = strtok(NULL, ";");
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
	printf("Enter your userid:\n"); 
    scanf("%s",&username); 
    a = login(username);
    if (a==1)
    {
    	b = is_faculty(username);
	}
	return a;
	return b;
    
}


