#include <stdio.h>
#include <string.h> 
#include <conio.h>
 
 
int main() 
{ 
    FILE *fp;
    
    struct user
{
    char user_id[10];
    
} users[1000];
    
    char str[1000];
    char* filename2 = "C:\\Users\\hp\\Desktop\\users.txt";
    int i;
    i = 0;
    fp = fopen(filename2, "r");
	char username[10]; 
    int var_login=0;
    printf("Enter your userid:\n"); 
    scanf("%s",&username); 
    
    
    if (fp == NULL)
    {
        printf("Could not open file %s",filename2);
        return;
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
    if (var_login==0){
    	printf("\nUser doesn't exist");
	}
return var_login;
}

    
 
 
    
 
   
 
     
 
 
 
