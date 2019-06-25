/*
 *  * Saad Arshad 00857432
 *   * CS 262 section 004
 *    * Project 1
 *     */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BSIZE 1000
#define MAX_CHAIN_BYTES 100
#define ASIZE 401

typedef struct _Chain
{
	size_t SeqLen;
	unsigned char Sequence[MAX_CHAIN_BYTES];
} Chain;

int getPrintMenu(char[]);
void getOpenFile(char[]);
void saveFile(char[]);
void spliceAdd(char[]);
void removeSeq(char[]);
void replace(char[]);

int main()
{
	int x = 0;
	int choice1;
	char mainArray[ASIZE];
	char Buffer[BSIZE];
	int choice;

	while(x != 7)
	{

		choice = getPrintMenu(Buffer);
		switch (choice)
		{
			case 1:
				getOpenFile(mainArray);
				choice1 = 1;
				break;
			case 2:
				if(choice1 == 1)
				{
					saveFile(mainArray);
				}
				else
				{
					printf("\n Please chose 1 before continueing!\n");
					choice = 9;
				}
				break;
			case 3:	
				if(choice1 == 1)
				{
					printf("\n%lu", strlen(mainArray));
					printf("\n%s\n", mainArray);
				}
				else
				{
					printf("\n Please chose 1 before continueing!\n");
					choice = 9;
				}
				break;
			case 4:
				if(choice1 == 1)
				{
					spliceAdd(mainArray);	
				}
				else 
				{
					printf("\n Please chose 1 before Continueing!\n");
					choice = 9;
				}
				break;
			case 5:	
				if(choice1 == 1)
				{
					removeSeq(mainArray);
				}
				else
				{
					printf("\n Please chose 1 before Continueing!\n");
					choice = 9;
				}
				break;
			case 6:
				if(choice1 == 1)
				{
					replace(mainArray);
				}
				else
				{
					printf("\n Please chose 1 before Contineing!\n");
					choice = 9;
				}
				break;
			case 7:
				x = 7;
				break;
			case 9:
				choice = getPrintMenu(Buffer);
				break;
			default:
				printf("Invalid input.\n");
				break;

		}//switch


	}//while

}

int getPrintMenu(char Buffer[]) 
{
	int choice = 0;

	printf("\nRead a DNA sequence from a file\n");
	printf("Save the current sequence to a file\n");
	printf("Print the current sequence\n");
	printf("Splice and insert a sub-sequence\n");
	printf("Remove a sub-sequence\n");
	printf("Replace a sub-sequence with another sub-sequence\n");
	printf("Exit the program\n");

	fgets(Buffer, BSIZE, stdin);
	sscanf(Buffer, "%d", &choice);
	return choice;
	
}

void saveFile(char mainArray[])
{
	Chain data1;
	FILE *outfile = NULL;
	char Buff[BSIZE];
	char Fileout[BSIZE];
	int i = 0, count = 0;
	unsigned char holder = 0; 
	
	printf("\nwhat file do you want to save to?\n");
	fgets(Buff, BSIZE, stdin);
	sscanf(Buff, "%s", Fileout);
	
	outfile = fopen(Fileout, "wb");
	if(outfile == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}	
		
	data1.SeqLen = strlen(mainArray);
	
	for (int j=0; j<data1.SeqLen; j++)
	{
		data1.Sequence[j] = 0;
	}

	while(i < data1.SeqLen)
	{	
		if((mainArray[i]) == 'T')
		{
			holder = 192;
		}
		else if((mainArray[i]) == 'G')
		{
			holder = 128;
		}
		else if((mainArray[i]) == 'C')
		{
			holder = 64;
		}
		else if((mainArray[i]) == 'A')
		{
			holder = 0;
		}
		
		holder = holder >> ((count%4)*2);
		data1.Sequence[count/4] = data1.Sequence[count/4] | holder;
		holder = 0;
		count++;
		i++;	
	}

	fwrite(&data1, sizeof(Chain), 1, outfile);

	fclose(outfile);
}

void getOpenFile(char mainArray[])
{
	Chain data;
	FILE *infile = NULL;
	char Buf[BSIZE];
	char Filein[BSIZE];
 	unsigned char holder = 192;
	int count = 0;
	int i = 0;
	unsigned char singleByte;
	mainArray[0] = '\0';

	printf("\nWhat file do you want to open?\n");
	fgets(Buf, BSIZE, stdin);
	sscanf(Buf, "%s", Filein);
	
	infile = fopen(Filein, "r");
	if(infile == NULL)
	{
		printf("Error opening file \n");
		exit(1);
	}
	
	fread(&data, sizeof(Chain), 1, infile);
	if(feof(infile))
	{
		printf("Error with file\n");
		exit(1);
	}

	while(i < data.SeqLen)
	{
		singleByte = data.Sequence[i/4];
		singleByte = singleByte << ((i%4)*2);
		
		if((singleByte & holder) == 192)
		{
			mainArray[count] = 'T';
		}
		else if((singleByte & holder) == 128)
		{
			mainArray[count] = 'G';
		}
		else if((singleByte & holder) == 64)
		{
			mainArray[count] = 'C';
		}
		else if((singleByte & holder) == 0)
		{
			mainArray[count] = 'A';
		}
		count++;
		i++;
	}
	mainArray[count] = '\0';	
	fclose(infile);
}

void spliceAdd(char mainArray[])
{
	char Find[BSIZE];
	char Add[BSIZE];
	int findC = 0;
	int addC = 0;
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	
	Find[0] = '\0';
	Add[0] = '\0';
	
	printf("What place would you like to insert a new sequence?\n");
	fgets(Find, BSIZE, stdin);
	while(Find[findC])
	{
		Find[findC] = toupper(Find[findC]);
		findC++;
	}
	Find[strlen(Find)-1] = '\0';
	for(i = 0; i < strlen(Find); i++)
	{
		if(Find[i] == 'A')
		{		
			x = 1;
		}
		else if(Find[i] == 'C') 
		{
			x = 1;
		}
		else if(Find[i] == 'G')
		{
			x = 1;
		}
		else if(Find[i] == 'T')
		{
			x = 1;
		}	
		else 
		{
			x = 2;
		}
		i++; 
	}
	
	if(x == 2)
	{
		printf("Wrong character was inputed for finding where to insert a new Sequence. Try again\n");		
	}

	printf("What new sequence would you like to add?\n");
	fgets(Add, BSIZE, stdin);
	while(Add[addC])
	{
		Add[addC] = toupper(Add[addC]);
		addC++;
	}
	Add[strlen(Add)-1] = '\0';
	for(j = 0; j < strlen(Add); j++)
	{
		if(Add[j] == 'A')
		{		
			y = 1;
		}
		else if(Add[j] == 'C') 
		{
			y = 1;
		}
		else if(Add[j] == 'G')
		{
			y = 1;
		}
		else if(Add[j] == 'T')
		{
			y = 1;
		}	
		else 
		{
			y = 2;
		}
		j++; 
	}
	
	if(y == 2)
	{
		printf("Wrong character was inputed for inserting the new Sequence. Try again\n");
	}
	
	if(x == 1 && y == 1)
	{
		printf("\nWe are finding %s and adding %s\n", Find, Add);
		char *ptr = NULL;
		char *holder = mainArray;	
                char holderArray[BSIZE];

		memset(holderArray, '\0', BSIZE);
		
		ptr = strstr(holder,Find);
		while(ptr != NULL) 
		{// if the string is found, copy to holderarray 
			strncpy(holderArray+strlen(holderArray),holder,(ptr-holder));
			strcat(holderArray, Find);
			strcat(holderArray, Add);
			
			if(strlen(holderArray) > ASIZE-1)//concatenate if less then max size 401
			{
				holderArray[ASIZE-1] = '\0';
			}
   			
			holder = ptr+strlen(Find);
      			ptr = strstr(holder, Find); 
		}          
		strcat(holderArray , holder);    
		strcpy(mainArray, holderArray);                                                  
	}
}

void removeSeq(char mainArray[])
{
	char Find[BSIZE];
	int findC = 0;
	int i = 0;
	int x = 0;
	
	Find[0] = '\0';
	
	printf("What sequence would you like to remove?\n");
	fgets(Find, BSIZE, stdin);
	while(Find[findC])
	{
		Find[findC] = toupper(Find[findC]);
		findC++;
	}
	Find[strlen(Find)-1] = '\0';
	for(i = 0; i < strlen(Find); i++)
	{
		if(Find[i] == 'A')
		{		
			x = 1;
		}
		else if(Find[i] == 'C') 
		{
			x = 1;
		}
		else if(Find[i] == 'G')
		{
			x = 1;
		}
		else if(Find[i] == 'T')
		{
			x = 1;
		}	
		else 
		{
			x = 2;
		}
		i++; 
	}
	
	if(x == 2)
	{
		printf("Wrong character was inputed for finding where to insert a new Sequence. Try again\n");		
	}
	if(x == 1)
	{
		printf("\nWe are removing %s\n", Find);
		char *ptr = NULL;
		char *holder = mainArray;	
                char holderArray[BSIZE];

		memset(holderArray, '\0', BSIZE);
		
		ptr = strstr(holder,Find);
		while(ptr != NULL) 
		{// if the string is found, copy to holderarray 
			strncpy(holderArray+strlen(holderArray),holder,(ptr-holder));
		
			if(strlen(holderArray) > ASIZE-1)//concatenate if less then max size 401
			{
				holderArray[ASIZE-1] = '\0';
			}
   			
			holder = ptr+strlen(Find);
      			ptr = strstr(holder, Find); 
		}          
		strcat(holderArray , holder);    
		strcpy(mainArray, holderArray);                                                  
	}




}

void replace(char mainArray[])
{
	char Find[BSIZE];
	char Add[BSIZE];
	int findC = 0;
	int addC = 0;
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	
	Find[0] = '\0';
	Add[0] = '\0';
	
	printf("What sequence would you like to replace?\n");
	fgets(Find, BSIZE, stdin);
	while(Find[findC])
	{
		Find[findC] = toupper(Find[findC]);
		findC++;
	}
	Find[strlen(Find)-1] = '\0';
	for(i = 0; i < strlen(Find); i++)
	{
		if(Find[i] == 'A')
		{		
			x = 1;
		}
		else if(Find[i] == 'C') 
		{
			x = 1;
		}
		else if(Find[i] == 'G')
		{
			x = 1;
		}
		else if(Find[i] == 'T')
		{
			x = 1;
		}	
		else 
		{
			x = 2;
		}
		i++; 
	}
	
	if(x == 2)
	{
		printf("Wrong character was inputed for finding where to insert a new Sequence. Try again\n");		
	}

	printf("What sequence to replace with?\n");
	fgets(Add, BSIZE, stdin);
	while(Add[addC])
	{
		Add[addC] = toupper(Add[addC]);
		addC++;
	}
	Add[strlen(Add)-1] = '\0';
	for(j = 0; j < strlen(Add); j++)
	{
		if(Add[j] == 'A')
		{		
			y = 1;
		}
		else if(Add[j] == 'C') 
		{
			y = 1;
		}
		else if(Add[j] == 'G')
		{
			y = 1;
		}
		else if(Add[j] == 'T')
		{
			y = 1;
		}	
		else 
		{
			y = 2;
		}
		j++; 
	}
	
	if(y == 2)
	{
		printf("Wrong character was inputed for inserting the new Sequence. Try again\n");
	}
	
	if(x == 1 && y == 1)
	{

		printf("\nWe are replacing %s with %s\n", Find, Add);
		char *ptr = NULL;
		char *holder = mainArray;	
                char holderArray[BSIZE];

		memset(holderArray, '\0', BSIZE);
	
		while(NULL!= (ptr = strstr(holder,Find))) 
		{// if the string is found, copy to holderarray 
			strncpy(holderArray+strlen(holderArray),holder,(ptr-holder));
			strcat(holderArray, Add);
	
			if(strlen(holderArray) > ASIZE-1)//concatenate if less then max size 401
			{
				holderArray[ASIZE-1] = '\0';
			}
			holder = ptr + strlen(Find);
      			ptr = strstr(holder, Find); 
		}          
		strcat(holderArray , holder);    
		strcpy(mainArray, holderArray);    
	}
}












