/* Name: Yvgeny Konrad id: 312737620*/																	


#include "aux_functions_firstread.h"


/*This function compares the scaned word with the signs 
  already in the signs table to avoid duplicates.*/
int wordcmp(struct sign *table,char *word2,int index)
{
	int i=ZERO;
	int found=ZERO;
	for(i=ZERO;i<index;i++)
	{
		if(strcmp(table[i].name,word2)==ZERO)/*Search throgh the table for duplicates.*/
			found=ONE;
	}

	if(found==ZERO)
	{
		return found;
	}
	else
		return found;
}

/*This function checks the provided word if its a register.
  If its a register, returns 1,else returns 0.*/
int sign_check(char *word)
{

	if(word[ZERO]=='r'&&word[ONE]>='0'&&word[ONE]<='7'&&strlen(word)==MAXREGISTERNAMEL)
		return ONE;


	return ZERO;

}


/*Checks if the lable is already in the table, if not will add it.*/
void insert_word(struct sign *table,char *word,int *index,int loc,int SP,int type,int *error,int rowcounter)
{

	if(*index!=ZERO)/*In case the table is empty*/
	{
		if(!(wordcmp(table,word,*index)))/*Checking if there is a lable like that already.*/
		{
			strcpy(table[*index].name,word);
			table[*index].loc=loc+SP;
			table[*index].type=type;
			(*index)++;
		}
		else
		{
			printf("Error: the lable %s in line : %d is already defined\n",word,rowcounter);
			*error=ONE;
		}
	}
	else
	{	
		strcpy(table[*index].name,word);/*In case the scanned word is the first in the file.*/
		table[*index].loc=loc+SP;
		table[*index].type=type;
		(*index)++;
	}
}


/*Returns the word after the comma.*/
char *comma_sep_after(char *express,int *error,int rowcounter)
{
	if(!(strpbrk(express,",")))
	{
		printf("Error: Not enough operand suplied, line %d\n",rowcounter);
		*error=ONE;
		return express;
	}
	else
		return strpbrk(express,",")+ONE;/*Returns the word after the comma.*/
}
	


/*Returns the word before the comma.*/
char *comma_sep_before(char *express,int n)/*Returns the word before comma by inserting \0 
											 in place of the comma, by that ending the string.*/
{
	express[strlen(express)-(n+ONE)]='\0';
	return express;
}


/*This function will recive a data array to create it, 
  a word that will contain the information after the .data string and the index 
  that points to the DC counter of data. Then the function will insert the data 
  into the array. Every number is increasing the array size.*/
int *digitsDataHendler(char *word,int *data_table,int *d_index,int rowcounter,int *error)
{
	char num[MAXNUMOFDIGITS];

	while ((strpbrk(word,",")))/*Checking if there is more than one digit.*/
	{
		if((*d_index)!=ZERO)/*Checking if it's the first digit, if it is no need to increase the size of the array.*/
			data_table=realloc(data_table,(*d_index+ONE)*sizeof(int));

		strcpy(num,word);
		strcpy(word,comma_sep_after(word,error,rowcounter));/*Seperating the first digit from the string.*/
		strcpy(num,comma_sep_before(num,strlen(word)));

		if(strcmp(num,"0")!=0&&atoi(num)==0)
		{
			printf("Error: Invalid number:%s entered in line: %d\n",num,rowcounter);
			*error=ONE;
		}
		else if(atoi(num)>=((-1)*(pow(2,11)))&&atoi(num)<=(pow(2,11)-1))/*Checking the size of the number.*/
		{
			data_table[*d_index]=atoi(num);/*Inserting the digit into the array.*/
			(*d_index)++;
		}
		else
		{
			printf("Error: Invalid number:%d entered in line: %d\n",atoi(num),rowcounter);
			*error=ONE;
		}

	}

	if((*d_index)!=ZERO)
		data_table=realloc(data_table,(*d_index+ONE)*sizeof(int));

	/*if there is only one digit, no need for seperation.*/
	if(strcmp(word,"0")!=0&&atoi(word)==0)
	{
		printf("Error: Invalid number:%s entered in line: %d\n",word,rowcounter);
		*error=ONE;
	}
	else if(atoi(word)>=((-1)*(pow(2,11)))&&atoi(word)<=(pow(2,11)-1))/*Checking the size of the number.*/
	{
		data_table[*d_index]=atoi(word);/*Inserting the digit into the array.*/
		(*d_index)++;
	}
	else
	{
		printf("Error: Invalid number:%d entered in line: %d\n",atoi(word),rowcounter);
		*error=ONE;
	}

return data_table;

}



/*Inserts the characters into the data table.*/
int *charDataHendler(char *word,int *data_table,int *d_index)
{
	int i;
	char temp[MAXCHARLENGTH];/*Temporary char to insert into the data table.*/

	for(i=ONE;i<=strlen(word)-2;i++)/*The quotes arent needed in the data table, 
									this is why the for loop runs the length of the string minus 2.*/
	{
		if((*d_index)!=ZERO)/*If its the first value that goes into the data table no need for array size increase.*/
			data_table=realloc(data_table,(*d_index+1)*sizeof(int));
		
			strncpy(temp,word+i,ONE);/*Copyes one character at a time.*/
			temp[ONE]='\0';
			data_table[*d_index]=(int)temp[0];/*Inserts the character into the data table.*/
			(*d_index)++;
			

	}

	if((*d_index)!=ZERO)
	{

		data_table=realloc(data_table,(*d_index+1)*sizeof(int));
	}


	
	data_table[*d_index]=ZERO;/*End's the string in the data table with 0 as requasted.*/
	(*d_index)++;

	if((*d_index)==ZERO)
			(*d_index)++;

	return data_table;
}

void lable_name_check(char *word,int *error,int rowcounter)
{
	int i;

	if(strlen(word)>=30)/*Checking if the name is to long.*/
	{
		printf("Error: Length of lable at line %d is to long.\n",rowcounter);
		*error=ONE;
	}

	if(sign_check(word)==1)/*Checking if the lable name is a register name.*/
	{
		printf("Error: Name of lable in line %d is a registers name.\n",rowcounter);
		*error=ONE;
	}
		/*Checking if the lable name is an orders name.*/
		if(strcmp(word,"mov1")==ZERO||strcmp(word,"mov2")==ZERO)
		{
			printf("Error: The name of lable in line %d is %s, its ilegal to use orders as lables.\n",rowcounter,word);
			*error=ONE;
		}
		else if(strcmp(word,"cmp1")==ZERO||strcmp(word,"cmp2")==ZERO)
		{
			printf("Error: The name of lable in line %d is %s, its ilegal to use orders as lables.\n",rowcounter,word);
			*error=ONE;
		}

		else if(strcmp(word,"add1")==ZERO||strcmp(word,"add2")==ZERO)
		{
			printf("Error: The name of lable in line %d is %s, its ilegal to use orders as lables.\n",rowcounter,word);
			*error=ONE;
		}
		else if(strcmp(word,"sub1")==ZERO||strcmp(word,"sub2")==ZERO)
		{
			printf("Error: The name of lable in line %d is %s, its ilegal to use orders as lables.\n",rowcounter,word);
			*error=ONE;
		}
		else if(strcmp(word,"not1")==ZERO||strcmp(word,"not2")==ZERO)
		{
			printf("Error: The name of lable in line %d is %s, its ilegal to use orders as lables.\n",rowcounter,word);
			*error=ONE;
		}
		else if(strcmp(word,"clr1")==ZERO||strcmp(word,"clr2")==ZERO)
		{
			printf("Error: The name of lable in line %d is %s, its ilegal to use orders as lables.\n",rowcounter,word);
			*error=ONE;
		}

		else if(strcmp(word,"lea1")==ZERO||strcmp(word,"lea2")==ZERO)
		{
			printf("Error: The name of lable in line %d is %s, its ilegal to use orders as lables.\n",rowcounter,word);
			*error=ONE;
		}
		else if(strcmp(word,"inc1")==ZERO||strcmp(word,"inc2")==ZERO)
		{
			printf("Error: The name of lable in line %d is %s, its ilegal to use orders as lables.\n",rowcounter,word);
			*error=ONE;
		}
		else if(strcmp(word,"dec1")==ZERO||strcmp(word,"dec2")==ZERO)
		{
			printf("Error: The name of lable in line %d is %s, its ilegal to use orders as lables.\n",rowcounter,word);
			*error=ONE;
		}
		else if(strcmp(word,"jmp1")==ZERO||strcmp(word,"jmp2")==ZERO)
		{
			printf("Error: The name of lable in line %d is %s, its ilegal to use orders as lables.\n",rowcounter,word);
			*error=ONE;
		}

		else if(strcmp(word,"bne1")==ZERO||strcmp(word,"bne2")==ZERO)
		{
			printf("Error: The name of lable in line %d is %s, its ilegal to use orders as lables.\n",rowcounter,word);
			*error=ONE;
		}
		else if(strcmp(word,"red1")==ZERO||strcmp(word,"red2")==ZERO)
		{
			printf("Error: The name of lable in line %d is %s, its ilegal to use orders as lables.\n",rowcounter,word);
			*error=ONE;
		}
		else if(strcmp(word,"jsr1")==ZERO||strcmp(word,"jsr2")==ZERO)
		{
			printf("Error: The name of lable in line %d is %s, its ilegal to use orders as lables.\n",rowcounter,word);
			*error=ONE;
		}
		else if(strcmp(word,"rts1")==ZERO||strcmp(word,"rts2")==ZERO)
		{
			printf("Error: The name of lable in line %d is %s, its ilegal to use orders as lables.\n",rowcounter,word);
			*error=ONE;
		}

		else if(strcmp(word,"stop1")==ZERO||strcmp(word,"stop2")==ZERO)
		{
			printf("Error: The name of lable in line %d is %s, its ilegal to use orders as lables.\n",rowcounter,word);
			*error=ONE;
		}
		else if(strcmp(word,"prn1")==ZERO||strcmp(word,"prn2")==ZERO)
		{
			printf("Error: The name of lable in line %d is %s, its ilegal to use orders as lables.\n",rowcounter,word);
			*error=ONE;
		}

	if(isdigit(word[0]))
	{
		printf("Error: Line %d lable name: %s can not begin with a digit.\n",rowcounter,word);
			*error=ONE;
	}

	for(i=0;i<strlen(word);i++)
		if(!(isalnum(word[i])))
		{
			printf("Error: The name of lable in line %d is %s, it contains iligal characters.\n",rowcounter,word);
			*error=ONE;
		}
}