/**
name : Aviad Ben Hayun   id :***660157
**/

#include<stdio.h>
#include <stdbool.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 20
#define PASS_MAX_SIZE 25
#define PASSWORD "password.txt" //input file

/****************************************variables and structs part ************************/
COORD coord = {0, 0};
/**
	book - book strct : id , name author quantity price rack numer
*/
struct _book
{
	int id;
	char name[20];
	char Author[20];
	int quantity;
	float Price;
	int rackno;
};
typedef struct _book book;
/**
	Node - node struct
	data :pointer for book
	next item : pointer for book
*/
typedef struct _node
{
	book* data;
	struct _node* next;
}Node;

/**
	book_list : linked list
*/
Node* book_list=NULL;
/**************************************** functions declaration part ************************/
/**
input: x and y coordinates
output: the next start cell in the command line
method:go to x y cell in the command line
**/
void gotoxy (int x, int y);
/**
input: File
output: True/False
method: determining whether the file is empty or not
**/
bool isEmpty(FILE *file);
/**
input: void
output: void
method: create new password for the first time
**/
void createPassword(void);
/**
input: void
output: return 0 if password is right
method: the method equals the user's input password with the password inside the file.
**/
int logIn(void);
/**
input: void
output: void
method: sell book
**/
void sellBook(void);
/**
input: void
output: void
method: add new book to the system
**/
void addBook(void);
/**
input: void
output: void
method: delete book from the system only if exist
**/
void deleteBook(void);
/**
input: void
output: void
method: search for book
**/
void searchBook(void);
/**
input: void
output: void
method: update the numbers of books in the system
**/
void updateQuantity(void);
/**
input: void
output: void
method: print books without copies
**/
void printZeroQuantity(void);
/**
input: void
output: void
method: print all the books in the system
**/
void printBooks(void);
/**
input: void
output: void
method: change the password
**/
void changePassword(void);
/**
input: void
output: void
method: logout from the system
**/
void logOut(void);
/**
input: book
output: void
method: print the given book
**/
void printABook(book b);
/**
input: book and price
output: void
method: print the book transaction
**/
void printTransection(book b, float price);

/**************************************** functions implementation part  ************************/

void gotoxy (int x, int y)
{
		coord.X = x; coord.Y = y; // X and Y coordinates
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool isEmpty(FILE *file)
{
	long savedOffset = ftell(file);
	fseek(file, 0, SEEK_END);
	if (ftell(file) == 0) // check if count of chars inside the file is zero
	{
		return true;
	}
	fseek(file, savedOffset, SEEK_SET);
	return false;
}

void createPassword(void){
	FILE*f;

	f=fopen(PASSWORD,"w"); //open file
	if(f==NULL){
		printf("File not open!\n");
		exit(1);
	}
	else
	{
		char password[PASS_MAX_SIZE];
		printf("Please Enter New Password:");
		scanf("%s", password); // get the new password from the user
		fputs(password, f);
		fclose(f);
	}
}

int logIn(void){
	FILE*f;
	char password[PASS_MAX_SIZE], buff[PASS_MAX_SIZE];

	f=fopen(PASSWORD,"r");
	gotoxy(15,15);
	printf("\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB Log in:");
	scanf("%s", password);
	fgets(buff, PASS_MAX_SIZE, f);
	fclose(f);
	return strcmp(password, buff); // return true if the password from the user equals to password within the 'password' file
}
void sellBook(){
	char yesNo; //determine if the user want to sell another book
	int bookId, sellQuantity;
	Node *i;
	bool exist;  // determine if book exists or not

	if(book_list != NULL){ // check if book_list have books
	  do{
		exist = false;
		printf("\n");
		printf("Please Enter Book id:");
		scanf("%d", &bookId); // get book id from user

		// iterate to find the book
		i = book_list;
		while(i != NULL){
			if(bookId == i->data->id){
				printf("Please Enter Book Quantity To Sell:");
				scanf("%d", &sellQuantity);
				if(i->data->quantity >= sellQuantity){
					i->data->quantity -= sellQuantity;
					printTransection(*i->data,i->data->Price*sellQuantity); // print the transaction
					exist = true; // the book is exist
						break;
				}else{
					printf("Sorry The Book Quantity Is Not Sufficient!!"); // print to user
					exist = true;
					break;
				}
			}
			i = i->next;
		}
		// print the proper action result message for the user
		if(!exist){
			printf("\nSorry The Book: %d Does Not Exist",bookId);
		}
		do{
			printf("\nDo You Wish To Remove Another Book?(y/n): ");
			scanf("%s", &yesNo);
		if(yesNo != 'y' && yesNo != 'n' ){
			printf("Unrecognized commend '%c', Please Try Again..\n",yesNo);
		}
		}while(yesNo != 'y' && yesNo != 'n' );

	  }while(yesNo == 'y' );

	}else{
		printf("Sorry The Book List Is Empty!!\n");
	}
}

void addBook(void){
	char yesNo;
	book *pb = NULL;
	Node *pn = NULL;
	Node *i;
	bool exist;

	do{
		exist = false; // initialize book as not exist
		pb = (book*) malloc(sizeof(book)); // allocate space for new book
		pn = (Node*) malloc(sizeof(Node)); // allocate space for new node

		// Book details from user
		printf("\n");
		printf("Please Enter Book id:");
		scanf("%d", &pb->id);

		printf("Please Enter Book Name:");
		scanf("%s", pb->name);

		printf("Please Enter Book Author:");
		scanf("%s", pb->Author);

		printf("Please Enter Book Quantity:");
		scanf("%d", &pb->quantity);

		printf("Please Enter Book Price:");
		scanf("%f", &pb->Price);

		printf("Please Enter Book Shelf Number:");
		scanf("%d", &pb->rackno);

		pn->data = (book*) malloc(sizeof(book));
		pn->data = pb;
		pn->next = NULL;

	if(book_list == NULL){ // check if book_list is empty
		book_list = (Node*) malloc(sizeof(Node)); // allocate space for new Node to book_list
		book_list = pn;  //add the book to the list
		printf("The Book: %d Was Successfully Added",pn->data->id);

	}else{
		for(i = book_list; i->next != NULL ; i = i->next){ // iterate to check if book exist / go to the last node in the list
			if(pb->id == i->data->id){
				exist = true;
				break;
			}
		}
		// print the proper action result message for the user
		if(!exist){
			i->next = pn; // add to the last node in the list
			printf("\nThe Book: %d Was Successfully Added",pn->data->id);
		}else{
			printf("\nSorry The Book: %d Already Exist",pn->data->id);
		}
		}

		do{
			printf("\nDo You Wish To Add Another Book?(y/n): ");
			scanf("%s", &yesNo);

		if(yesNo != 'y' && yesNo != 'n' ){ // check if the commend is y(yes) or n(no)
			printf("Unrecognized commend '%c', Please Try Again..\n",yesNo);
		}

		}while(yesNo != 'y' && yesNo != 'n' ); // while the commend is not y(yes) or n(no)

	}while(yesNo == 'y' ); // while the user want to add another book

}

void deleteBook(void){
	char yesNo;
	int bookId;
	Node *i;
	Node *temp;
	bool exist;

	if(book_list != NULL){ // check if book list isn't null
	  do{
		exist = false;
		printf("\n");
		printf("Please Enter Book id:");
		scanf("%d", &bookId); // get book id from the user

			// check if book exist for the first iteration
			if(bookId == book_list->data->id && book_list->next != NULL){
					book_list = book_list->next;
					exist = true;
			}else if(bookId == book_list->data->id && book_list->next == NULL){
					book_list = NULL;
					exist = true;
			}else{
				i = book_list;
				while(i->next != NULL){ // iterate to find the book
					if(bookId == i->next->data->id){
						temp = i->next;
						i->next = i->next->next;
						exist = true;
						free(temp); // remove book
						break;
					}
				 i = i->next;
				}
			}
		// print the proper action result message for the user
		if(exist){
			printf("\nThe Book: %d Was Successfully Removed",bookId);
		}else{
			printf("\nSorry The Book: %d Does Not Exist",bookId);
		}

		if(book_list != NULL){
		do{
			printf("\nDo You Wish To Remove Another Book?(y/n): ");
			scanf("%s", &yesNo); // check if user want to remove another book

		if(yesNo != 'y' && yesNo != 'n' ){ // check if the commend is y(yes) or n(no)
			printf("Unrecognized commend '%c', Please Try Again..\n",yesNo);
		}

		}while(yesNo != 'y' && yesNo != 'n' ); // while the commend is not y(yes) or n(no)

		}else{
			 printf("Sorry The Book List Is Empty!!\n");
			 yesNo = 'n';
		 }
		}while(yesNo == 'y' );// while the user want to add another book
	}else{
		printf("Sorry The Book List Is Empty!!\n");
	}
}

void searchBook(void){
	char yesNo;
	int bookId;
	Node *i;
	bool exist;

	if(book_list != NULL){ // check if book list isn't null
	  do{
		exist = false;

		printf("\n");
		printf("Please Enter Book id:");
		scanf("%d", &bookId); // get book id from the user

		i = book_list;
		while(i != NULL){
			if(bookId == i->data->id){
				printABook(*i->data);  //print the book
				exist = true;
						break;
						}
				  i = i->next;
				}
		// print the proper action result message for the user
		if(!exist){
			printf("\nSorry The Book: %d Does Not Exist",bookId);
		}

		do{
			printf("\nDo You Wish To Search For Another Book?(y/n): ");
			scanf("%s", &yesNo); // check if user want to remove another book

		if(yesNo != 'y' && yesNo != 'n' ){ // check if the commend is y(yes) or n(no)
			printf("Unrecognized commend '%c', Please Try Again..\n",yesNo);
		}
		}while(yesNo != 'y' && yesNo != 'n' ); // while the commend is not y(yes) or n(no)

	  }while(yesNo == 'y' );// while the user want to add another book

	}else{
		printf("Sorry The Book List Is Empty!!\n");
	}
}

void updateQuantity(void){
	char yesNo;
	int bookId, bookQuantity;
	Node *i;
	bool exist;

	if(book_list != NULL){ // check if book list isn't null
	  do{
		exist = false;
		printf("\n");
		printf("Please Enter Book id:");
		scanf("%d", &bookId); // get book id from the user

		i = book_list;
		while(i != NULL){ // search for the book to update the quantity
			if(bookId == i->data->id){
				printf("Please Enter Book Quantity:");
				scanf("%d", &bookQuantity); // get the book quantity
				i->data->quantity = bookQuantity; // update the new quantity
				exist = true;
						break;
						}
				  i = i->next;
				}
		// print the proper action result message for the user
		if(exist){
			printf("\nThe Quantity Of Book: %d Was Successfully Updated",bookId);
		}else{
			printf("\nSorry The Book: %d Does Not Exist",bookId);
		}

		do{
			printf("\nDo You Wish To update The Quantity Of Another Book?(y/n): ");
			scanf("%s", &yesNo); // check if user want to remove another book

		if(yesNo != 'y' && yesNo != 'n' ){ // check if the commend is y(yes) or n(no)
			printf("Unrecognized commend '%c', Please Try Again..\n",yesNo);
		}
		}while(yesNo != 'y' && yesNo != 'n' ); // while the commend is not y(yes) or n(no)

	  }while(yesNo == 'y' ); // while the user want to add another book

	}else{
		printf("Sorry The Book List Is Empty!!\n");
	}
}

void printZeroQuantity(void){
	Node *i;
	if(book_list != NULL){ // check if book list isn't null
		i  = book_list;
		while(i!=NULL)
		{
			if(i->data->quantity == 0){ // check if quantity is zero
				printABook(*i->data);
			}
		i=i->next;
		}
	}else{
	  printf("Sorry The Book List Is Empty!!\n");
	}
}

void printBooks(void){
	Node *i;
	if(book_list != NULL){ // check if book list isn't null
		i  = book_list;
		while(i!=NULL) // iterate all the books and print them
		{
			printABook(*i->data);
			i=i->next;
		}
	}else{
	  printf("Sorry The Book List Is Empty!!\n");
	}
}

void changePassword(void){
	FILE*f;

	f=fopen(PASSWORD,"w");
	if(f==NULL){ // check if file is null
		printf("File not open!, Please Try Again..\n");
	}
	else
	{
		char password[PASS_MAX_SIZE];
		printf("Please Enter New Password:");
		scanf("%s", password);
		fputs(password, f);
		fclose(f);
	}
}

void logOut(void){
	printf("\n~System Exit Good Bye!!!~\n");
}

void printABook(book b){
	printf("\n ");
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n ");
	printf("\xB2                                       \xB2\n ");
	printf("\xB2  Book Number      : %-15d   \xB2\n ",b.id);
	printf("\xB2  Book Name        : %-15s   \xB2\n ",b.name);
	printf("\xB2  Book Author      : %-15s   \xB2\n ",b.Author);
	printf("\xB2  Book Quantity    : %-15d   \xB2\n ",b.quantity);
	printf("\xB2  Book Price       : %-15.2f   \xB2\n ",b.Price);
	printf("\xB2  Book Shelf Number: %-15d   \xB2\n ",b.rackno);
	printf("\xB2                                       \xB2\n ");
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n ");

}

void printTransection(book b, float price){
	printf("\n ");
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n ");
	printf("\xB2                                       \xB2\n ");
	printf("\xB2  Book Name        : %-15s   \xB2\n ",b.name);
	printf("\xB2                                       \xB2\n ");
	printf("\xB2  Book Quantity    : %-15d   \xB2\n ",b.quantity);
	printf("\xB2                                       \xB2\n ");
	printf("\xB2  Book Price       : %-15.2f   \xB2\n ",price);
	printf("\xB2                                       \xB2\n ");
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n ");

}

/************************************************************************************************/



int main(void){

	int num; //represents the user choice
	FILE*f;

	f=fopen(PASSWORD,"r");
	gotoxy(15,3);
	printf("\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB Welcome to Zeko's Books Store \xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\n\n\n ");

	if(isEmpty(f)){ // if file is empty create new password
		createPassword();
	}

	if(logIn() == 0){
	  do{
		num = 0;
		//print menu
		printf("\n\n--- Menu ---\n"); //print menu
		printf("1.Sell A Book\n");
		printf("2.Add A Book\n");
		printf("3.Delete A Book\n");
		printf("4.Search A Book\n");
		printf("5.Update Quantity\n");
		printf("6.Print Books Out Of Stock\n");
		printf("7.Print All Books \n");
		printf("8.Update Password\n");
		printf("9.Exit\n");
		printf("Your choice:"); //get number of command from user
		scanf("%d",&num);

		switch(num) { // switch to handle user's choice
			case 1 :
				sellBook();
				system("pause");
				system("CLS");
				break;
			case 2 :
				addBook();
				system("CLS");
				break;
			case 3 :
				deleteBook();
				system("CLS");
				break;
			case 4 :
				searchBook();
				system("CLS");
				break;
			case 5 :
				updateQuantity();
				system("CLS");
				break;
			case 6 :
				printZeroQuantity();
				system("pause");
				system("CLS");
				break;
			case 7 :
				printBooks();
				system("pause");
				system("CLS");
				break;
			case 8 :
				changePassword();
				break;
			case 9 :
				logOut();
				break;
			default:
			   printf("Wrong input. please try again\n\n");
				continue;
	   }
	}
	while(num != 9);
	}else{
	   printf("Sorry Invalid Password Good Bye\n");
	  }

return 0 ;
}





