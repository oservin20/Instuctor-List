// Osman Servin
// Write the compiler used: GCC
// Compile Command: gcc -g -Wall hw06q1.c -o output
// Executable Command: ./output



#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define MAX_INSTRUCTORS 20
#define MAX_NAME_LENGTH 50

typedef enum { cs = 0, physics, mathematics, english } departmentEnum; // enum type

struct instructorRecord { // struct for instructor details
	char name[MAX_NAME_LENGTH];
	departmentEnum department;
	unsigned int instructorId;
	unsigned int age;
	struct instructorRecord* next;	// pointer to next node
}*list = NULL;	// declare linked list 'list'

int count = 0;	// the number of instructors currently stored in the list (initialized to 0)


void flushStdIn();
void executeAction(char);
void save(char* fileName);


int add(char* name_input, unsigned int instructorId_input, unsigned int age_input, char* department_input); // WORKS
void sort();					
int delete(unsigned int instructorId_input); 
void load(char* fileName);		 
void display();	
int search(unsigned int instructorId_input, char* name_input);
struct instructorRecord* searchPosition(unsigned int instructorId_input);


int main()
{
	char* fileName = "Instructor_List.txt";
	load(fileName);	// load list of instructors from file (if it exists). Initially there will be no file.
	char choice = 'i'; // initialized to a dummy value
	do
	{
		printf("\nEnter your selection:\n");
		printf("\t a: add a new instructor\n");
		printf("\t d: display instructor list\n");
		printf("\t r: remove an instructor from list\n");
		printf("\t s: sort instructor list by ID\n");
		printf("\t q: quit\n");
		choice = getchar();
		flushStdIn();
		executeAction(choice);
	} while (choice != 'q');

	save(fileName);  // save list of instructors to file (overwrites file, if it exists)
	return 0;
}

// flush out leftover '\n' characters
void flushStdIn()
{
	char c;
	do c = getchar();
	while (c != '\n' && c != EOF);
}

// ask for details from user for the given selection and perform that action
void executeAction(char c)
{
	char name_input[MAX_NAME_LENGTH];
	unsigned int instructorId_input, age_input, add_result = 0;
	char department_input[20];
	switch (c)
	{
	case 'a':
		// input instructor record from user
		printf("\nEnter instructor name: ");
		fgets(name_input, sizeof(name_input), stdin);
		name_input[strlen(name_input) - 1] = '\0';	// discard the trailing '\n' char
		
		printf("Enter instructor department (cs/physics/mathematics/english): ");
		fgets(department_input, sizeof(department_input), stdin);
		department_input[strlen(department_input) - 1] = '\0';	// discard the trailing '\n' char
		
		printf("Please enter instructor ID number: ");
		scanf("%d", &instructorId_input);
		
		printf("Please enter instructor age: ");
		scanf("%d", &age_input);
		flushStdIn();


		// add the instructor to the list
		add_result = add(name_input, instructorId_input, age_input, department_input);
		if (add_result == 0)
			printf("\nInstructor is already on the list! \n\n");
		else if (add_result == 1)
			printf("\nInstructor successfully added to the list! \n\n");
		else
			printf("\nUnable to add. Instructor list is full! \n\n");

		break;

	case 'r':
		printf("Please enter instructor ID to be deleted: ");
		scanf("%d", &instructorId_input);
		flushStdIn();
		int delete_result = delete(instructorId_input);
		if (delete_result == 0)
			printf("\nInstructor not found in the list! \n\n");
		else
			printf("\nInstructor deleted successfully! \n\n");
		break;
	case 'd': display();	break;
	case 's': sort();		break;

	case 'q': break;
	default: printf("%c is invalid input!\n", c);
	}
}



// FUNCTION USED TO SEARCH THROUGH THE LINKED LIST
int search(unsigned int instructorId_input, char* name_input)
{
	struct instructorRecord* tempList = list;

	while(tempList != 0)
	{
		// IF INSTRUCOTR EXIST IN THE LIST RETURN 1
		if(tempList->instructorId == instructorId_input || strcmp(tempList->name, name_input) == 0)
		{
			return 0; // INSTRUCTOR FOUND
		}
		
		// INCREMENT
		//position = tempList;
		tempList = tempList->next;
	}

	// IF THE INSTRUCTOR IS NOT FOUND THEN RETURN 0
	return 1;
} // WORKS




// This function is used to add an instructor into the list. You can simply add the new instructor to the end of list (linked list of structs).
// Do not allow the instructor to be added to the list if it already exists in the list. You can do that by checking instructor names OR IDs already in the list. If either condition matches, return 0 without adding it to the list.
int add(char* name_input, unsigned int instructorId_input, unsigned int age_input, char* department_input)
{
	struct instructorRecord* tempList = list;	// work on a copy of 'list'.

	// Write the code below
	tempList = (struct instructorRecord*) malloc(sizeof(struct instructorRecord));
	if(tempList == 0)
	{
		return 2; // RETURNS 2 IF THE LIST IS ALREADY FULL
	}	
	else
	{
		// USE THE SEARCH FUNCTION
		if(search(instructorId_input, name_input) == 0)
		{
			return 0; // LEAVE FUNCTION IF THE INSTRUCTOR WAS FOUND IN THE LIST
		}
		
		// ADD THE INSTRUCTORS INFORMATION
		strcpy(tempList->name, name_input); 
		
		// CHECK THE DEPARTMENT WHAT DEPARTMENT THE INSTRUCTOR IS IN
		if(strcmp("cs", department_input) == 0)
		{
			tempList->department = cs;
		}
		else if(strcmp("physics", department_input) == 0)
		{
			tempList->department = physics;
		}
		else if(strcmp("mathematics", department_input) == 0)
		{
			tempList->department = mathematics;
		}
		else
		{
			tempList->department = english;
		}
		
		tempList->instructorId = instructorId_input;
		tempList->age = age_input;

		// INSERT THE NEW NODE IN THE FIRST PLACE OF LINKED LIST
		tempList->next = list;
		list = tempList;

		count++; // KEEPS COUNT OF THE AMOUNT OF INSTRUCTORS IN THE LIST

		return 1;
	}	
}




// This function displays the instructor list with the details (struct elements) of each instructor. 
// Display all instructors.
void display()
{
	struct instructorRecord* tempList = list;  // work on a copy of 'list'
	
	// Write the code below
	char* departmentString = "Physics";

	// PARSE THROUGH THE LIST AND DISPLAY THE INSTRUCTOR INFORMATION
	while(tempList != 0)
	{
		//PRINTS THE INSTRUCTOR NAME
		printf("\nInstructor Name: %s", tempList->name);
		
		// CHECK WHAT DEPARTMENT THE INSTRUCTOR IS IN AND CONVERT TO STRING
		if(tempList->department == cs)
		{
			departmentString = "Computer Science";
		}
		else if(tempList->department == physics)
		{
			departmentString = "Physics";
		}
		else if(tempList->department == mathematics)
		{
			departmentString = "Mathematics";
		}
		else
		{
			departmentString = "English";
		}
		
		// PRINTS THE REST OF THE INFORMATION
		printf("\nDepartment: %s", departmentString);
		printf("\nInstructor ID: %d", tempList->instructorId);
		printf("\nInstructor Age: %d", tempList->age);
		printf("\n");

		tempList = tempList->next;
	}
}




// Q3 : sort (10 points)
// This function is used to sort the list(linked list of structs) numerically in ascending order by instructor ID.
void sort()
{
	struct instructorRecord* tempList = list;  // work on a copy of 'list'
	struct instructorRecord* temp = list;

	// IF THE LINKED LIST IS EMPTY OR HAS ONE INSTRUCTOR LEAVE FUNCTION
	if(tempList == NULL)
	{
		return;
	}

	// BUBBLE SORT THE LINKED LIST
	for(int i = 0; i < count; i++)
	{
		tempList = list;
			
		while(tempList->next != NULL)
		{
			if(tempList->instructorId > tempList->next->instructorId)
			{
				// SMALLEST TO NODE BEFORE
				strcpy(tempList->name, temp->next->name);
				tempList->department = temp->next->department;
				tempList->instructorId = temp->next->instructorId;
				tempList->age = temp->next->age;

				// BIGGEST TO NODE AFTER
				strcpy(tempList->next->name, temp->name);
				tempList->next->department = temp->department;
				tempList->next->instructorId = temp->instructorId;
				tempList->next->age = temp->age;				

//				strcpy(tempList->name, list->next->name);
//				tempList->department = list->next->department;
//				tempList->instructorId = list->next->instructorId;
//				tempList->age = list->next->age;
		
				// COPY EVERYTHING TO LIST
				list = tempList;
			}			
		
			// MOVE TO NEXT NODE
			tempList = tempList->next;
			temp = tempList;
		}
	}

	// display message for user to check the result of sorting.
	printf("\nInstructor list sorted! Use display option 'd' to view sorted list.\n");
}



// This function saves the linked list of structures to file.
void save(char* fileName)
{
	struct instructorRecord* tempList = list;	// work on a copy of 'list'

	FILE* file;
	int departmentValue = 0;
	file = fopen(fileName, "wb");		// open file for writing

	fwrite(&count, sizeof(count), 1, file);		// First, store the number of books in the list

	// Parse the list and write instructor record to file
	while (tempList != NULL) {
		fwrite(tempList->name, sizeof(tempList->name), 1, file);
		// convert enum to a number for storing
		// cs = 0, physics = 1, mathematics = 2, english = 3
		if (tempList->department == cs)
			departmentValue = 0;
		else if (tempList->department == physics)
			departmentValue = 1;
		else if (tempList->department == mathematics)
			departmentValue = 2;
		else
			departmentValue = 3;

		fwrite(&departmentValue, sizeof(departmentValue), 1, file);
		fwrite(&tempList->instructorId, sizeof(tempList->instructorId), 1, file);
		fwrite(&tempList->age, sizeof(tempList->age), 1, file);

		tempList = tempList->next;
	}

	fclose(file); // close the file after writing
}



struct instructorRecord* searchPosition(unsigned int instructorId_input)
{
	struct instructorRecord* p = list;
	struct instructotRecord* b = 0;

	while(p != 0)
	{
		if(p->instructorId == instructorId_input)
		{
			return b;
		}
		else
		{
			b = p;
			p = p->next;
		}
	}
	return 1;
}



// This function is used to delete an instructor by ID.
int delete(unsigned int instructorId_input)
{
	struct instructorRecord* tempListCur = list;	// b,  work on a copy of 'list'
	struct instructorRecord* tempListPrev = list;	// t,  work on a copy of 'list'

	// Write the code below
	tempListCur = searchPosition(instructorId_input);

	
	// IF INSTRUCTOR IS NOT FOUND IN THE LINKED LIST
//	if(search(instructorId_input, name_input) != 0)
	if(tempListCur == 1)
	{
		return 0;
	}

	//IF THE INSTRUCTOR IN THE FIRST INDEX
	if(tempListCur == 0)
	{
		tempListPrev = list;
		list = list->next;
		free(tempListPrev);
		count--;
		return 1;
	}
	else
	{
		tempListPrev = tempListCur->next;
		tempListCur->next = tempListPrev->next;
		free(tempListPrev);
		count--;
		return 1;
	}
}




// This function is called in the beginning of main().
// This function reads the instructor list from the saved file and builds the linked list of structures 'list'. 
void load(char* fileName)
{
	struct instructorRecord* tempList = list; // work on a copy of 'list'
	
	// Write the code below
	FILE* file;
	file = fopen(fileName, "rb"); // OPEN FILE TO READ

	// CHECKS IF THE FILE EXISTS
	if(file != NULL)
	{		
		// READ THE NUMBER OF INSTRUCTORS IN THE LIST
		fread(&count, sizeof(count), 1, file);

		// GO THROUGH LIST AND READ INSTRUCTORS INFORMATION
		int i = 0;
		while(i < count)
		{
			// USED TO STORE INFORMATION TO
			struct instructorRecord* newRecord = (struct instructorRecord*)malloc(sizeof(struct instructorRecord));
			
			// READ THE FIRST SET OF INFORMATION
			fread(newRecord->name, sizeof(newRecord->name), 1, file);
			fread(&newRecord->department, sizeof(newRecord->department), 1, file);
			fread(&newRecord->instructorId, sizeof(newRecord->instructorId), 1, file);	
			fread(&newRecord->age, sizeof(newRecord->age), 1, file);

			// MAKE SURE THAT THE LINKED LIST ACTUALLY HAS A NULL
			newRecord->next = NULL;
	

			// LINK THE NEW LIST TO THE GLOBAL LIST
			// IF ITS THE FIRST ELEMENT IN THE LIST THEN DO THE FOLLOWING
			if(list == NULL)
			{
				// ADDS THE NEW INSTRUCTOR THE LIST
				list = newRecord;
				// UPDATE THE TEMPLIST
				tempList = list;
			}
			// IF ITS NOT THE FIRST ELEMENT IN THE LINKED LIST
			else
			{
				// ADDS THE NEW INSTRUCTOR TO THE NEXT NODE
				tempList->next = newRecord;
				tempList = tempList->next;
			}
			
			// INCREMENTS i BY ONE
			i++;
		}

		fclose(file);	// CLOSE THE FILE AFTER READING FROM IT
	}
	else
	{
		printf("%s not found.\n", fileName);
		return;
	}
}



