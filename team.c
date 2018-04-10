//
// team.c
//
// Program for maintaining a personal team.
//
//
// Uses a linked list to hold the team players.
//
// Author: Rayyan Albaz


    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>
    #include <assert.h>

//**********************************************************************

    struct player 			//defining the linked list node 
    {
        char *familyName;		//pointer to point to the name type char 
        char *firstName;		//pointer to point to the name type char 
        char position;			//char to store position 
        int value;				//int to store value  
        struct player *next;	//pointer to point to the next node from type struct player
    };
    struct player *team = NULL ; //declaring the linked list head and its NULL 

//**********************************************************************
// Linked List Function Declarations

    void add(void);								//declaring an insertion function add();
    void print(void);							//declaring printing function print();
    void searchFamily(char familyName[]);		//declaring a search function that takes a string as a parameter 
    void searchValue(int value);				//declaring a search function that takes an int as a parameter
    void deleteFamily(char familyName[]);		//declaring a delete function that takes a string as a parameter


//**********************************************************************
// Support Function Declarations
//

    void safegets (char s[], int arraySize);        // gets without buffer overflow
    void familyNameDuplicate (char familyName[]);   // marker/tester friendly 
    void familyNameFound (char familyName[]);       //   functions to print
    void familyNameNotFound (char familyName[]);    //     messages to user
    void familyNameDeleted (char familyName[]);
    void printTeamEmpty (void);
    void printTeamTitle(void);
    void printNoPlayersWithLowerValue(int value);

//**********************************************************************
// Program-wide Constants
//

    const int MAX_LENGTH = 1023;
    const char NULL_CHAR = '\0';
    const char NEWLINE = '\n';
    const char GOALKEEPER = 'G';
    const char DEFENDER = 'D';
    const char MIDFIELDER = 'M';
    const char STRIKER = 'S';


//**********************************************************************
// Main Program
//

int main (void)
{ 
    const char bannerString[]
        = "Personal Team Maintenance Program.\n\n";
    const char commandList[]
        = "Commands are I (insert), D (delete), S (search by name),\n"
          "  V (search by value), P (print), Q (quit).\n";

 
    // announce start of program
    printf("%s",bannerString);
    printf("%s",commandList);
    int value;            	//declaring an int to use in loops 
    struct player *p;		//declaring a struct player pointer to use in loops for pointing to nodes 
    char *vl;				//declaring a char pointer 
    char response;
    char input[MAX_LENGTH+1];
    do
    {
        printf("\nCommand?: ");
        safegets(input,MAX_LENGTH+1);
        // Response is first char entered by user.  
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);

        if (response == 'I')
        {
            
            // Insert a player entry into the linked list.
            // Maintain the list in correct order (G, D, M, S).

            add();   //calling the insertion function add();

 
        }
        else if (response == 'D')
        {
            // Delete a player from the list.
    
            printf("\nEnter family name for entry to delete: ");
            safegets(input, MAX_LENGTH+1);		//reading the user input
            deleteFamily(input);				//calling a delete function with user input as a parameter
           

        }
        else if (response == 'S')
        {
            // Search for a player by family name.
            
            printf("\nEnter family name to search for: ");
            safegets(input, MAX_LENGTH+1);			//reading the user input
            searchFamily(input);					//calling a delete function with user input as a parameter

        }
        else if (response == 'V')
        {
            // Search for players that are worth less than or equal a value.
            

            printf("\nEnter value: ");
            safegets(input , MAX_LENGTH+1);		//getting user input 
            vl = &input[0];						
            value = atoi(vl);					//converting the user input from char to int 
            searchValue(value);					//calling search function with user input as a parameter 

        }
        else if (response == 'P')
        {
            // Print the team.
         
            print();							//calling the print function


        }
        else if (response == 'Q')
        {
            ; // do nothing, we'll catch this case below
        }
        else 
        {
            // do this if no command matched ...
            printf("\nInvalid command.\n%s\n",commandList);
        }
    } while (response != 'Q');
  
    // Delete the whole linked list that hold the team.
   
        while (team != NULL) 			//declaring a loop that goes through all nodes untill team is NULL
    {
        p = team->next;					//pointing to the next node
        free(team);						//freeing the node memory 
        team = p;						
    }

          
    // Print the linked list to confirm deletion.
   
        print();						//calling print function print();

    return 0;
}

//**********************************************************************
// Support Function Definitions

// Function to get a line of input without overflowing target char array.
void safegets (char s[], int arraySize)
{
    int i = 0, maxIndex = arraySize-1;
    char c;
    while (i < maxIndex && (c = getchar()) != NEWLINE)
    {
        s[i] = c;
        i = i + 1;
    }
    s[i] = NULL_CHAR;
}

// Function to call when user is trying to insert a family name 
// that is already in the book.
void familyNameDuplicate (char familyName[])
{
    printf("\nAn entry for <%s> is already in the team!\n"
           "New entry not entered.\n",familyName);
}

// Function to call when a player with this family name was found in the team.
void familyNameFound (char familyName[])
{
    printf("\nThe player with family name <%s> was found in the team.\n",
             familyName);
}

// Function to call when a player with this family name was not found in the team.
void familyNameNotFound (char familyName[])
{
    printf("\nThe player with family name <%s> is not in the team.\n",
             familyName);   
}

// Function to call when a family name that is to be deleted
// was found in the team.
void familyNameDeleted (char familyName[])
{
    printf("\nDeleting player with family name <%s> from the team.\n",familyName);
}

// Function to call when printing an empty team.
void printTeamEmpty (void)
{
    printf("\nThe team is empty.\n");
}

// Function to call to print title when whole team being printed.
void printTeamTitle (void)
{
    printf("\nMy Team: \n");
}

// Function to call when no player in the team has lower or equal value to the given value
void printNoPlayersWithLowerValue(int value)
{
    printf("\nNo player(s) in the team is worth less than or equal to <%d>.\n", value);
}

//**********************************************************************
// Add your functions below this line.

//function for insertion a new node into the list
void add(void)

{
    char input[MAX_LENGTH+1];					//array of char ith max lenght + 1 size
    int value;									//an int 
    char *vl;									//pointer to char 
    struct player *cur,*prev,*new_node;			//pointers to nodes of type struct player 
    new_node = malloc(sizeof(struct player));				//allocating enough memory for the new node as a size of the struct player node
    new_node->familyName = malloc(sizeof(MAX_LENGTH+1));	//alloacting enough memory for the pointer for the name 
    new_node->firstName = malloc(sizeof(MAX_LENGTH+1));		//alloacting enough memory for the pointer for the name 


    if (new_node == NULL) 									//if the new node returns NULL there was an error in creating the node 
    {
        printf("Error adding a new player \n");				//printing error massege 
        return;
    }

    printf("  family name: ");								//PROMPTING user to enter a name 
    safegets(new_node->familyName , MAX_LENGTH+1);			//getting user input and saving it in the memory we allocated previosley
      
    printf("  first name: ");								//PROMPTING user to enter a name
    safegets(new_node->firstName , MAX_LENGTH+1);			//getting user input and saving it in the memory we allocated previosley

    printf("  position: ");									//PROMPTING user to enter a char for the position 
    safegets(input , MAX_LENGTH+1);							//getting the user input and saving it in an array we declared before 
    new_node->position = input[0] ; 						//adding the postion char in the node position 

    printf("  value: ");									//PROMPTING user to enter an integer
    safegets(input , MAX_LENGTH+1);							//getting the user input and saving it in an array we declared before 
    vl = &input[0];											//pointing to the saved value we got from the user 
    value = atoi(vl);										//converting from char to int 
    new_node->value = value;								//adding the value the user entered in the node value 

    for(cur = team , prev = NULL ; cur != NULL ; prev = cur , cur = cur->next) //for loop to go through each node with a pointer to keep track of the previous node 
    {

            if(strcmp(cur->familyName , new_node->familyName) == 0 )	//cheacks if th given name is already in the list if so it will free the memory for th node and node wont be added 
            { 
            familyNameDuplicate(cur->familyName);
            free(new_node);
            return;
            } 

            if(new_node->position == GOALKEEPER)		//keeping the order of the GOALKEEPERs in the list
            {
                if(cur->position != GOALKEEPER)
                {
                new_node->next = cur ;
                if(prev ==NULL)
                team = new_node;
                else 
                prev->next = new_node;
                return;
                }
            }

            if(new_node->position == DEFENDER) 				//keeping the order of the DEFENDERs in the list
            {
                if(cur->position != DEFENDER && cur->position != GOALKEEPER)
                {
                new_node->next = cur ;
                if(prev ==NULL)
                team = new_node;
                else 
                prev->next = new_node;
                return;    
                }
            }

            if(new_node->position == MIDFIELDER )			//keeping the order of the MIDFIELDERs in the list
            {    
                if(cur->position != MIDFIELDER && cur->position != GOALKEEPER && cur->position != DEFENDER)
                {
                new_node->next = cur ;
                if(prev ==NULL)
                team = new_node;
                else 
                prev->next = new_node;
                return;    
                }
            }

            if(new_node->position == STRIKER )				//keeping the order of the STRIKERs in the list
            {
                if(cur->position != GOALKEEPER && cur->position != DEFENDER && cur->position != MIDFIELDER && cur->position != STRIKER)
                {
                new_node->next = cur ;
                if(prev ==NULL)
                team = new_node;
                else 
                prev->next = new_node;
                return;    
                }
            }
    }
        	new_node->next = cur;			//adding the node to the list 
            if(prev ==NULL)
            team = new_node;
            else 
            prev->next = new_node;	
}

void print(void)					//defining the print function 
{
    struct player *p ;
    if(team == NULL)		//if the team is empty 
    {	
    printTeamEmpty();	//calling printTeamEmpty();
    }
    else
    {
    printTeamTitle();   //calling printTeamTitle();
    for (p=team; p != NULL; p=p->next)		//iterating through each nod and printing them
    printf(" %s \n %s \n %c \n %d \n\n", p->familyName, p->firstName , p->position , p->value);
    }
}


void searchFamily(char familyName[])			//defining search by family name function 
{
    
    struct player *q;
    for (q=team; q != NULL; q=q->next)				//cheaching each node 
    {
        if (strcmp(q->familyName, familyName) == 0)		//comparing the given name with each node's family name 
        {
        familyNameFound(familyName);						//calling familyNameFound();
        printf(" %s \n %s \n %c \n %d \n\n", q->familyName, q->firstName , q->position , q->value); 	//printing the node we found 
        return;
        }
    }										//if no name matches 
    familyNameNotFound(familyName);			//calling familyNameNotFound();
    return;
}


void searchValue(int value)				//defining search by value function 
{
	int j=0;
    struct player *p;
	
    for (p=team; p != NULL; p=p->next)			//checking each node if its value is less than or equal to the given value it will print it 
    {
        if (p->value <= value)
        {
        printf(" %s \n %s \n %c \n %d \n\n", p->familyName, p->firstName , p->position , p->value);  
        j++;							//j is initially 0 it inctrements every time a node is printed 
        }
	}
	if (j==0 && team != NULL)				//if j is still 0 that means the value range in not in the team prints msg
	{
	printNoPlayersWithLowerValue(value);
	}
	if (team == NULL)						// if team is NULL  prints msg 
    {
	printTeamEmpty();
    }

}

void deleteFamily(char familyName[])		//defining delete with family name function 
{

    struct player *cur , *prev;
    for(cur = team , prev = NULL ; cur != NULL ; prev = cur , cur = cur->next)
    {
        if (strcmp(cur->familyName, familyName) == 0) //checks if the given name is in the list 
        {
        if (prev == NULL)							// if its frist node it makes next node the head and deletes the node 
            {
            team = cur->next;
            familyNameDeleted(familyName);
            free(cur);
            return;
            }
        familyNameDeleted(familyName);			//if node is in any other postion it will link prev with next and delete cur 
        prev->next = cur->next;
        free(cur);
        return;
        }
    }
        familyNameNotFound(familyName);
        return;
}