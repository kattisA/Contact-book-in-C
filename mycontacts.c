/*
Author: Katarina Lejonlid, 2016
Task 4 in Exercises 7, create a contact book.
The features of the program include add a new contact, remove
a contact, update a contact, sort the contact in some order,
print the list of contact, search for a contact. 
Katarina Lejonlid 2016-11-18

The contacts are saved in a file called mycontacts.txt
The sorting will sort alphabetically based on the last name.
The search, removal, update is all based on firstname which can be altered
to match both the first and last name.
*/

#include <stdio.h>
#include <string.h>

#define MAX_CON 100
#define STR_SIZE 40

struct contact
{
    char firstname[STR_SIZE], lastname[STR_SIZE];
    int telephone;
};

void menu(int choice, int counter, struct contact c[]);
void add_contact( int counter);
void save_contact( char *firstname, char *lastname, int telephone);
void save_list(struct contact c[], int counter);
int read_contacts(struct contact c[]);
void print_contact( struct contact c[], int i);
void printList( struct contact c[], int counter);
void remove_contact(struct contact c[], int counter, char *name);
void search_contact(struct contact c[], int counter, char *name);
void update_contact(struct contact c[], int counter, char *name);
void sort_list(struct contact c[], int counter);

int main(){

	int choice, counter;
	struct contact c[MAX_CON];
	counter = read_contacts(c);

	do{
		printf(" 1. add contact\n 2. remove contact\n 3. update contact\n");
		printf(" 4. print contacts\n 5. sort contacts\n 6. search contacts\n 7. quit \n");
		printf("Enter your choice:");
		fflush(stdin);
		scanf("%d", &choice);

		menu(choice, counter, c);
	} while(choice != 7);

	return 0;
}
//Menu for the contact book.
void menu(int choice, int counter, struct contact c[]){

	char name[STR_SIZE];


		switch(choice){
		case 1:
		// Check that the maximum size of the addressbook has not been exceeded.
		if (counter == MAX_CON)
			{
				printf("You cannot add more contacts\n");
			}
		else
			{
				add_contact(counter);
			}
		break;
		case 2:
		printf("Enter name of contact to remove:");
		scanf("%19s", name);
		remove_contact(c,counter, name);
		break;
		case 3:
		printf("Enter name of contact to update:");
		scanf("%19s", name);
		update_contact(c, counter, name);
		counter = read_contacts(c);
		break;
		case 4:
		printList(c, counter);
		break;
		case 5:
		sort_list(c, counter);
		counter = read_contacts(c);
		printList(c,counter);
		break;
		case 6:
		printf("Enter name of contact to search:");
		scanf("%19s", name);
		search_contact(c, counter, name);
		break;
		case 7:
		printf("Bye, bye!\n");
		break;
		default:
		printf("Please enter valid choice!\n");
		break;
	}
}

//Add contact by saving it to file.
void add_contact( int counter){

	char firstname[STR_SIZE], lastname[STR_SIZE];
	int telephone;

	printf("Enter the firstname: ");
	scanf("%39s", firstname);
	printf("Enter the last name: ");
	scanf("%39s", lastname);
	printf("Enter the telephone number: ");
	scanf("%d", &telephone);

    save_contact(firstname, lastname, telephone);
    printf("The contact %s %s is now saved\n",firstname, lastname );

}
//Save the contact in a file.
void save_contact( char *firstname, char *lastname, int telephone){
	FILE *fp;
	fp = fopen("mycontacts.txt", "a");

	fprintf(fp, "%s %s %d\n", firstname, lastname, telephone);
	fclose(fp);
}
//Save the structure to the file by overwriting it.
void save_list(struct contact c[], int counter){

	int i;
	FILE *fp;
	fp = fopen("mycontacts.txt", "w");

	for(i=0; i < counter; i++ )
	{
		fprintf(fp, "%s %s %d\n", c[i].firstname, c[i].lastname, c[i].telephone);
	}

	fclose(fp);
}

//Read the results in the structure array.
int read_contacts(struct contact c[])
{
	int i = 0, j;
	char str1[STR_SIZE];
	char str2[STR_SIZE];

	FILE *fp;
	fp = fopen("mycontacts.txt", "r");
	if (fp)
	{
	    while(!feof(fp))
	    {

	    	fscanf(fp, "%s %s %d\n", strcpy(c[i].firstname, str1), strcpy(c[i].lastname, str2), &c[i].telephone);
	    	// Before proceeding check that i is smaller than MAX_CON or it will overflow.
	    	if (i < MAX_CON){
	    		i++;
	    	}
	    	else
	    	{
	    		break;
	    	}
	    }
	    fclose(fp);
	}
	//Return the actual size of the contacts, equal i.
	return i;
}
//Print a single contact given an index.
void print_contact( struct contact c[], int i){

    	printf("First name: %s\n", c[i].firstname);
    	printf("Last name: %s\n", c[i].lastname);
    	printf("Number: 0%d\n", c[i].telephone);
}

//Print list of contacts
void printList( struct contact c[], int counter){
	int i;

	for (i = 0; i < counter; i++){
		printf("\nContact number %d: \n", i);
    	printf("First name: %s\n", c[i].firstname);
    	printf("Last name: %s\n", c[i].lastname);
    	printf("Number: 0%d\n", c[i].telephone);
	}
}

// Given a name, a struct and a counter remove the contact from the list
void remove_contact(struct contact c[], int counter, char *name)
{
	int i,j;
	int result = 0;
	for (i = 0; i < counter; i ++)
	{
		if( strcmp(name, c[i].firstname) == 0)
		{
			for(j= i; j < counter; j++)
			{
				c[j] =c[j + 1];
			}
			save_list(c, counter-1);
			result = 1;
			printf("The contact %s is now successfully removed\n", name );
			break;
		}
	}

	if(!result){
		printf("The contact %s was not found\n", name);
	}
}

//Search for a contact
void search_contact(struct contact c[], int counter, char *name){

	int i;
	int found = 0;
	for (i = 0; i < counter; i ++)
	{
		if( strcmp(name, c[i].firstname) == 0)
		{
			print_contact(c, i);
			found = 1;
		}
	}

	if (!found)
	{
		printf("The contact %s was not found\n", name );
	}
}
//Update a contact
void update_contact(struct contact c[], int counter, char *name)
{
	int i;
	int found = 0;
	int update;
	for (i = 0; i < counter; i ++)
	{
		if( strcmp(name, c[i].firstname) == 0)
		{
			print_contact(c,i);
			printf("To update first name enter 1.");
			scanf("%d", &update);
			if (update == 1){
				printf("Update first name: ");
				scanf("%39s", c[i].firstname);
				update = 0;
			}
			printf("To update last name enter 1.");
			scanf("%d", &update);
			if (update == 1){
				printf("Update last name: ");
				scanf("%39s", c[i].lastname);
				update = 0;
			}
			printf("To update number enter 1.");
			scanf("%d", &update);
			if (update == 1){
				printf("Enter the telephone number: ");
				scanf("%d", &c[i].telephone);
				update = 0;
			}

			save_list(c, counter);
			printf("The contact is updated.\n");
			print_contact(c, i);
			found = 1;
			break;
		}
	}

	if (!found)
	{
		printf("The contact %s was not found\n", name );
	}
}

//Sort the contacts alphabetically
void sort_list(struct contact c[], int counter){

	int i,j,t;
	struct contact tmp;

	for (i = 1; i < counter; i++)
	{
      for (j = 1; j < counter; j++)
      {
         if (strcmp(c[j - 1].lastname, c[j].lastname) > 0)
         {
           tmp = c[j-1];
           c[j-1]=c[j];
           c[j] = tmp;
         }
      }
   }
   save_list(c, counter);

}
