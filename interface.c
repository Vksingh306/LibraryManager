#include <stdio.h>
#include <string.h>

int main(){
	char option , option_ad , user_id[10];
	


	printf("IISER Kolkata Library Catalogue \n");
	printf("1 : Log In as Admin \n");
	printf("2 : Log In as User \n");
	printf("Enter your Choice : ");
	scanf("%c" , &option);
	//printf()
	switch(option){
	
		case '1' :
		printf("Enter Log In ID : ");
		scanf("%s" , user_id);
		// Check if the provided id matches that in the file - TBD : Ankit
		printf("Welcome  %s\n", user_id);
		printf("Login Successful!!\n");
		printf("Logged in as %s\n" , user_id);
		printf("Privilege : Admin\n\n");
		printf("1 : Add Book\n"); 
		printf("2 : Delete Book\n");
		printf("3 : Edit Book\n");
		printf("4 : Search Book\n");
		printf("Enter your choice : ");
		scanf("%c" , &option_ad);			//while executing this line not being read
		switch(option_ad){
			case '1' :
				// Add function to add book - TBD : Panda
				printf("Add book");
			break;
			case '2' :
				// Add function to delete book - TBD : Panda
				//printf
			break;
			case '3' :
				// Add function to edit book - TBD : Panda
				//printf
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
		
		//case '2' :
			
			
		
		default:
		printf("Doing");
		break;
    }
}
	
