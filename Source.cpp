#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct
{
	int bookNum;
	char bookTitle[30];
	char author[25];
	double price;
}bookT;

void addBook(bookT* books, int size);
void displayBook(bookT* books, int size);
void searchBookNumber(bookT* books, int size);
void editPrice(bookT* books, int size);
void displayList(bookT* books, int size);

void main()
{
	int numberofBooks;
	int userChoice = 0;
	int loginChoice;
	bookT* list;
	FILE* file1;
	FILE* file2;
	char pswrd[30];
	char userPswrd[30];

	printf("Select type of login:\n1.User\n2.Admin\n");
	scanf("%d", &loginChoice);

	if (loginChoice == 1)
	{
		file1 = fopen("BookInfo.txt", "r");
		int i = 0;
		char output[70];

		while (!feof(file1))
		{
			fscanf(file1, "%c\n", &output);
			i++;
		}
		numberofBooks = i;
		list = (bookT*)malloc(numberofBooks * sizeof(bookT));
		printf("LIST OF ALL BOOKS:\n");
		displayList(list, numberofBooks);
		fclose(file1);
	}
	if (loginChoice == 2)
	{
		file2 = fopen("password.txt", "r");
		fscanf(file2, "%s", &pswrd);
		while (strcmp(pswrd, userPswrd) != 0)
		{
			printf("Please enter the valid password:\n");
			scanf("%s", &userPswrd);
		}

		if (strcmp(pswrd, userPswrd) == 0)
		{
			printf("Please enter the number of books in the list:\n");
			scanf("%d", &numberofBooks);

			list = (bookT*)malloc(numberofBooks * sizeof(bookT));

			while (userChoice != 4)
			{
				printf(" Please select one of the following options:\n");
				printf("1.Search for the book\n2.Add a new book\n3.Edit book price\n4.Exit\n");
				scanf(" %d", &userChoice);

				if (userChoice == 1)
				{
					searchBookNumber(list, numberofBooks);
				}
				if (userChoice == 2)
				{
					addBook(list, numberofBooks);
					displayBook(list, numberofBooks);
				}
				if (userChoice == 3)
				{
					editPrice(list, numberofBooks);
				}
			}
		}
	}
}
void displayList(bookT* books, int size)
{
	FILE* file1;
	file1 = fopen("BookInfo.txt", "r");
	int i = 0;
	while (!feof(file1))
	{
		fscanf(file1, "%d %s %s %lf\n", &(books + i)->bookNum, &(books + i)->bookTitle, &(books + i)->author, &(books + i)->price);
		printf("Book ID Number: %d\n Book Title: %s\n Book Author: %s\n Book Price: %.2lf\n----------------\n", (books + i)->bookNum, (books + i)->bookTitle, (books + i)->author, (books + i)->price);
		i++;
	}
	fclose(file1);
}
void addBook(bookT* books, int size)
{
	FILE* file1;
	file1 = fopen("BookInfo.txt", "a");

	for (int i = 0; i < size; i++)
	{
		printf("Please enter the book %d ID number:\n", i + 1);
		scanf(" %d", &(books + i)->bookNum);

		printf("Please enter the book %d title:\n", i + 1);
		scanf(" %s", (books + i)->bookTitle);

		printf("Please enter the book %d author:\n", i + 1);
		scanf(" %s", (books + i)->author);

		printf("Please enter the book %d price:\n", i + 1);
		scanf(" %lf", &(books + i)->price);

		fprintf(file1, "%d %s %s %lf\n", (books + i)->bookNum, (books + i)->bookTitle, (books + i)->author, (books + i)->price);
	}
	fclose(file1);
}
void displayBook(bookT* books, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("Book ID Number: %d\n Book Title: %s\n Book Author: %s\n Book Price: %.2lf\n----------------\n", (books + i)->bookNum, (books + i)->bookTitle, (books + i)->author, (books + i)->price);
	}
}
void searchBookNumber(bookT* books, int size)
{
	FILE* file1;
	file1 = fopen("BookInfo.txt", "r");
	int idNum;
	int i = 0;
	printf("Please enter the book number you are looking for:\n");
	scanf("%d", &idNum);

	while (!feof(file1))
	{
		fscanf(file1, "%d %s %s %lf\n", &(books + i)->bookNum, (books + i)->bookTitle, (books + i)->author, &(books + i)->price);
		//printf("%d %s %s %lf\n", (books + j)->bookNum, (books + j)->bookTitle, (books + j)->author, (books + j)->price);
		if (idNum == (books + i)->bookNum)
		{
			printf("Book ID Number: %d\nBook Title: %s\nBook Author: %s\nBook Price: %.2lf\n----------------\n", (books + i)->bookNum, (books + i)->bookTitle, (books + i)->author, (books + i)->price);
		}
		i++;
	}
}
void editPrice(bookT* books, int size)
{
	FILE* file1;
	file1 = fopen("BookInfo.txt", "r");
	int idNum;
	int i = 0;
	double newPrice;

	printf("Please enter the book number you are looking for:\n");
	scanf("%d", &idNum);

	while (!feof(file1))
	{
		fscanf(file1, "%d %s %s %lf\n", &(books + i)->bookNum, (books + i)->bookTitle, (books + i)->author, &(books + i)->price);
		//printf("%d %s %s %lf\n", (books + j)->bookNum, (books + j)->bookTitle, (books + j)->author, (books + j)->price);
		if (idNum == (books + i)->bookNum)
		{
			printf("Enter the new price for this book:\n");
			scanf("%lf", &newPrice);
			(books + i)->price = newPrice;
			printf("Book Number: %d\nBook Title: %s\nBook Author: %s\nBook Price: %.2lf\n----------------\n", (books + i)->bookNum, (books + i)->bookTitle, (books + i)->author, (books + i)->price);
		}
		i++;
	}
}
