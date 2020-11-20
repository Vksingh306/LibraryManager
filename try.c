#include <stdio.h>
#include <string.h>

int main(){
	char option , option_ad , option_us , user_id[10] , book_searched[100] , Not_logged;
	int  number_of_issued ;


	printf("IISER Kolkata Library Catalogue \n");
	Login:
		printf("1 : Log In as Admin \n");
		printf("2 : Log In as User \n");
		printf("3 : Search a book \n");	
		printf("4 : Exit\n");
		printf(">>> Enter your Choice : ");
		scanf(" %c" , &option);
		//printf()
		
		switch(option){
	
			case '1' :
				printf(">>> Enter Log In ID : ");
				scanf("%s" , user_id);
				// Check if the provided id matches that in the file - TBD : Ankit
				printf("\nLogin Successful!!\n");
				printf("Logged in as %s\n" , user_id);
				printf("Privilege : Admin\n\n");
				Admin_login:
					printf("1 : Add Book\n"); 
					printf("2 : Delete Book\n");
					printf("3 : Edit Book\n");
					printf("4 : Search Book\n");
					printf("5 : Exit\n");
					printf(">>> Enter your choice : ");
					scanf(" %c" , &option_ad);			
					switch(option_ad){
						case '1' :
							// Add function to add book - TBD : Panda
							printf("Add book");
						break;
						case '2' :
							// Add function to delete book - TBD : Panda
							printf("Delete book");
						break;
						case '3' :
							// Add function to edit book - TBD : Panda
							printf("Edit book");
						break;
						case '4' :
							// Add function to search book - TBD : Perry
							printf("Search book");
						break;
						case'5' :
							printf("Exiting the program....\n");
   							exit(0);
   						break;
						default:
							printf("Please choose a valid option\n\n\n");
							goto Admin_login;
						break;
					}	
			break;
		
			case '2' :
				printf(">>> Enter Log In User ID : ");
				scanf("%s" , user_id);
				// Check if the provided id matches that in the file - TBD : Ankit
				printf("Welcome  %s\n", user_id);
				printf("Login Successful!!\n");
				printf("Logged in as %s\n" , user_id);
				printf("Privilege : User\n\n");
				//number_of_issued = n_issued(user_id);	//Please check if the parameter is as per your function	-	TBD : Agni
				//printf("You have currently %d books issued.\n", number_of_issued);		
				//Also display the book titles that were issued - TBD : Agni (Function not ready)	
				//printf("You currently have these books due")
				User_login:
					printf("\n1 : Issue Book\n"); 
					printf("2 : Return Book\n");
					printf("3 : Search Book\n");
					printf("4 : Exit\n");
					printf(">>> Enter your choice : ");
					scanf(" %c" , &option_us);
				
					switch(option_us){
						case '1' :
							// Add function to issue book - TBD : 
							printf("Issue book");
						break;
						case '2' :
							// Add function to return book - TBD : 
							printf("Return book");
						break;
						case '3' : 
							// Add function to search book - TBD : Perry
							printf("Search book");
						break;
						case '4' :
							printf("Exiting the program....\n");
   							exit(0);
						break;
						default :
							printf("Please enter a valid input\n\n\n");
							goto User_login;
						break;
					}
			break;
		
			case '3' :
				Search:
					printf(">>> Enter the keyword to search for the book :  \n");
					//Please add functionality to search a book. 	- TBD : Perry
					//If such a book exist store the book name in the variable 'book_searched'
					//book_searched = 			;
					printf("1 : Issue this book \n");
					printf("2 : Search for another book\n");
					printf("3 : Exit\n");
					printf(">>> Enter your choice : ");
					scanf(" %c" , &Not_logged);
					switch(Not_logged){
						case '1' :
							printf("Please login first to issue book.\n\n");
							goto Login;
						break;
						
						case '2' :
							goto Search;
						break;
					
						case '3' :
							printf("Exiting the program....\n");
   							exit(0);
						break;
						
						default :
							printf("Please enter a valid input \n\n\n");
							goto Search;
						break;
					}
			break;
				
			case '4' :
				printf("Exiting the program....\n");
   				exit(0);
   			break;
			
		
			default:
			printf("Please enter a valid input \n\n\n");
			goto Login;
			break;
    }
}
	
