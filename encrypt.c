#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main (int argc ,char *argv[])					//declaring main function with arguments passed by parameters
{
	char i , *name;			//declaring a char and a pointer to char 
	FILE *fp , *fp2 ;		//declaring two files 
	name = strdup(argv[1]);		//taking the parameter passed by user and saving it at name which will be the file name 
	strcat(name , ".enc");		//adding '.enc' to the nmae 

	int shift = atoi(argv[2]);			// taking the other parameter and transfering it to an integer 
		if (shift > 25 || shift < 1)			//checking if the user used the programm in a right way 
		{
			printf("ERROR: Shift amount should be in range (1 - 25 inclusive)\n");		//printing error msg
			exit(1);
		}


	fp = fopen(argv[1] ,"r");												//opening the file that the user provided nmae for it
			if (fp == NULL)													//if it returns NULL there was a problem opening the file 
			{
				printf("ERROR opening the file Make sure file exists \n");		//error msg 
				exit (1);
			}

	fp2 = fopen(name , "w");										//opening a new file to write into 
			if (fp2 == NULL)									//if it returns NULL there was an error opening the file 
			{
				printf("ERROR opening the file\n");				//error msg
				fclose(fp);					//closes the first opened file 
				exit (1) ;					//exit 
			}
							
	while ((i = getc(fp)) != EOF)				//reading the first file char by char until it reaches end of file 
		{
			if (i >= 'a' && i <= 'z')				//checks if the char is within the lower case range 
			{
				i = (((i - 'a') + shift) % 26 + 'a');		//encrptys the char by adding the shift amount to it which resaults in a new letter in ascii table 
			}
	 		if (i >= 'A' && i <= 'Z')				//checks if the char is within the upper case range 
			{
				i = (((i - 'A') + shift) % 26 + 'A');			//it encrypts the char by adding the shift amount to it 
			}	
				putc(i , fp2);							//it adds the vhar in the new file 
		}
		fclose(fp);				//closes first file 
		fclose(fp2);			//closes second file 
		return 0;				//retunrs 0 for rught termination 

}
