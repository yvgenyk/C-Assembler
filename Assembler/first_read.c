/* Name: Yvgeny Konrad id: 312737620*/	

#include "first_read.h"

#define SignToTable_two()/*This macro will divide the two prarameters, then will check if whats the type of the operator and then calculate the amount of lines needed.*/\
{\
	word[0]='\0';/*In case of blank spaces or tabs i am scanning the two operands after the order leter by leter, then combine them into one string.*/\
	c=fgetc(text);\
	do{\
		if(c!=' '&&c!='\t')\
		{\
			word[strlen(word)+1]='\0';\
			word[strlen(word)]=c;\
		}\
\
		if(c==EOF)\
			break;\
		c=fgetc(text);\
\
	}while(c!='\n');\
\
	strcpy(tempword,comma_sep_after(word,error,rowcounter));/*Extracts the sign after the comma.*/\
\
	strcpy(word,comma_sep_before(word,strlen(tempword)));/*Extracts the sign before the comma.*/\
\
	if(((word[0]=='r')&&(word[1]<'0'||word[1]>'7')&&(strlen(word)==2))||((tempword[0]=='r')&&(tempword[1]<'0'||tempword[1]>'7')&&(strlen(tempword)==2)))\
	{\
		printf("Error: The rigisters number at line %d is ilegal, it should be 0-7.\n",rowcounter);\
		*error=ONE;\
	}\
\
	if(strcmp(word,"$$")==ZERO)\
		strcpy(word,prevword);\
\
	for(i=ZERO;i<=flag_number_of_orders;i++)/*If the flag is on, this set of orders will execute twice, else once.*/\
	{\
	if((word[ZERO]=='r'&&word[ONE]>='0'&&word[ONE]<='7'&&strlen(word)==MAXREGISTERNAMEL)&&(tempword[ZERO]=='r'&&tempword[ONE]>='0'&&tempword[ONE]<='7'&&strlen(tempword)==MAXREGISTERNAMEL))\
		(*IC)++;\
	else\
		(*IC)+=TWOLINES;\
	}\
	if(strcmp(word,"$$")!=ZERO)\
		strcpy(prevword,word);\
}

#define Scan_next() /*Some orders can pass only one parameter with it so for counting the number of rows 
					  i am skipping the next parameter and moving on with two scans.*/\
{\
	c=fscanf(text,"%s",word);\
	strcpy(prevword,word);\
	c=fscanf(text,"%s",word);\
}


int *first_read(char *prog_name,int *IC,int *DC,int *data_table,struct sign *sign_table,int *lableTableIndex,int SP,int *error)
{

	int flag_number_of_orders=ZERO,i;
	int quotesflag=ZERO;
	int rowcounter=ONE;/*In case there is an error in the original code provided. I am counting the rows to provide a proper error messege.*/
	int c;
	char word[MAXLINELENGTH],tempword[MAXLINELENGTH],prevword[MAXLINELENGTH]="\0";/*Creating temporarry words to work with the orders.*/

	FILE *text;
	text=fopen(prog_name,"r");

	if(text==NULL)
	{
		printf("No file found with the name: %s\n",prog_name);
		*error=ONE;
	}
	else
		c=fscanf(text,"%s",word);/*Scans the firs word from the file.*/


do{
		if(word[0]==';')/*Incase there is a note in the code.*/
		{
			while(c!='\n')
				c=fgetc(text);

			c=fscanf(text,"%s",word);
		}
		/*Checking all the possible orders.*/
		if(strcmp(word,"mov1")==ZERO||strcmp(word,"mov2")==ZERO)
		{
			if(word[strlen(word)-ONE]=='2')/*In case the order should execute twise.*/
			{
				flag_number_of_orders=ONE;/*If there is an order to run this line twice than i will turn on the flag.*/
				*IC+=TWOLINES;/*Two lines order needs 2 lines.*/
			}
			else
				*IC+=ONELINE;/*One line order needs one line.*/

			SignToTable_two();

			if(strcmp(tempword,"$$")==0||tempword[ZERO]=='#')
			{
				printf("Error: Invalid destination operand line %d\n",rowcounter);
				*error=ONE;
			}

			flag_number_of_orders=ZERO;/*Setting the flag to zero for next orders.*/
			c=fscanf(text,"%s",word);
			rowcounter++;
			
		}
		else if(strcmp(word,"cmp1")==ZERO||strcmp(word,"cmp2")==ZERO)
		{
			if(word[strlen(word)-ONE]=='2')
			{
				flag_number_of_orders=ONE;
				*IC+=TWOLINES;
			}
			else
				*IC+=ONELINE;

			SignToTable_two();
			flag_number_of_orders=ZERO;
			c=fscanf(text,"%s",word);
			rowcounter++;
		}

		else if(strcmp(word,"add1")==ZERO||strcmp(word,"add2")==ZERO)
		{
			if(word[strlen(word)-ONE]=='2')
			{
				flag_number_of_orders=ONE;
				*IC+=TWOLINES;
			}
			else
				*IC+=ONELINE;

			SignToTable_two();

			if(strcmp(tempword,"$$")==0||tempword[ZERO]=='#')
			{
				printf("Error: Invalid destination operand line %d\n",rowcounter);
				*error=ONE;
			}

			flag_number_of_orders=ZERO;
			c=fscanf(text,"%s",word);
			rowcounter++;
		}
		else if(strcmp(word,"sub1")==ZERO||strcmp(word,"sub2")==ZERO)
		{
			if(word[strlen(word)-ONE]=='2')
			{
				flag_number_of_orders=ONE;
				*IC+=TWOLINES;
			}
			else
				*IC+=ONELINE;

			SignToTable_two();

			if(strcmp(tempword,"$$")==0||tempword[ZERO]=='#')
			{
				printf("Error: Invalid destination operand line %d\n",rowcounter);
				*error=ONE;
			}

			flag_number_of_orders=ZERO;
			c=fscanf(text,"%s",word);
			rowcounter++;
		}
		else if(strcmp(word,"not1")==ZERO||strcmp(word,"not2")==ZERO)
		{
			if(word[strlen(word)-ONE]=='2')
				*IC+=FOURLINES;
			else
				*IC+=TWOLINES;
			c=fscanf(text,"%s",word);

			if(!(sign_check(word)))
			{
				printf("Error: Invalid destination operand line %d\n",rowcounter);
				*error=ONE;
			}

			strcpy(prevword,word);
			c=fscanf(text,"%s",word);
			rowcounter++;
		}
		else if(strcmp(word,"clr1")==ZERO||strcmp(word,"clr2")==ZERO)
		{
			if(word[strlen(word)-ONE]=='2')
				*IC+=FOURLINES;
			else
				*IC+=TWOLINES;
			
			c=fscanf(text,"%s",word);

			if(strcmp(word,"$$")==0||word[ZERO]=='#')
			{
				printf("Error: Invalid destination operand line %d\n",rowcounter);
				*error=ONE;
			}

			strcpy(prevword,word);
			c=fscanf(text,"%s",word);
			rowcounter++;
		}

		else if(strcmp(word,"lea1")==ZERO||strcmp(word,"lea2")==ZERO)
		{
			if(word[strlen(word)-ONE]=='2')
			{
				flag_number_of_orders=ONE;
				*IC+=TWOLINES;
			}
			else
				*IC+=ONELINE;

			SignToTable_two();

			if(strcmp(word,"$$")==0||word[ZERO]=='#'||sign_check(word))
			{
				printf("Error: Invalid first operand line %d\n",rowcounter);
				*error=ONE;
			}

			if(strcmp(tempword,"$$")==0||tempword[ZERO]=='#')
			{
				printf("Error: Invalid destination operand line %d\n",rowcounter);
				*error=ONE;
			}

			flag_number_of_orders=ZERO;
			c=fscanf(text,"%s",word);
			rowcounter++;
		}
		else if(strcmp(word,"inc1")==ZERO||strcmp(word,"inc2")==ZERO)
		{
			if(word[strlen(word)-ONE]=='2')
				*IC+=FOURLINES;
			else
				*IC+=TWOLINES;
			
			c=fscanf(text,"%s",word);

			if(strcmp(word,"$$")==0||word[ZERO]=='#')
			{
				printf("Error: Invalid destination operand line %d\n",rowcounter);
				*error=ONE;
			}
			
			strcpy(prevword,word);
			c=fscanf(text,"%s",word);

			rowcounter++;
		}
		else if(strcmp(word,"dec1")==ZERO||strcmp(word,"dec2")==ZERO)
		{
			if(word[strlen(word)-ONE]=='2')
				*IC+=FOURLINES;
			else
				*IC+=TWOLINES;
			
			c=fscanf(text,"%s",word);

			if(strcmp(word,"$$")==0||word[ZERO]=='#')
			{
				printf("Error: Invalid destination operand line %d\n",rowcounter);
				*error=ONE;
			}
			
			strcpy(prevword,word);
			c=fscanf(text,"%s",word);

			rowcounter++;
		}
		else if(strcmp(word,"jmp1")==ZERO||strcmp(word,"jmp2")==ZERO)
		{
			if(word[strlen(word)-ONE]=='2')
				*IC+=FOURLINES;
			else
				*IC+=TWOLINES;
			
			c=fscanf(text,"%s",word);

			if(word[ZERO]=='#')
			{
				printf("Error: Invalid destination operand line %d\n",rowcounter);
				*error=ONE;
			}
			
			strcpy(prevword,word);
			c=fscanf(text,"%s",word);

			rowcounter++;
		}

		else if(strcmp(word,"bne1")==ZERO||strcmp(word,"bne2")==ZERO)
		{
			if(word[strlen(word)-ONE]=='2')
				*IC+=FOURLINES;
			else
				*IC+=TWOLINES;
			
			c=fscanf(text,"%s",word);

			if(word[ZERO]=='#')
			{
				printf("Error: Invalid destination operand line %d\n",rowcounter);
				*error=ONE;
			}
			
			strcpy(prevword,word);
			c=fscanf(text,"%s",word);

			rowcounter++;
		}
		else if(strcmp(word,"red1")==ZERO||strcmp(word,"red2")==ZERO)
		{
			if(word[strlen(word)-ONE]=='2')
				*IC+=FOURLINES;
			else
				*IC+=TWOLINES;
			
			c=fscanf(text,"%s",word);

			if(word[ZERO]=='#')
			{
				printf("Error: Invalid destination operand line %d\n",rowcounter);
				*error=ONE;
			}
			
			strcpy(prevword,word);
			c=fscanf(text,"%s",word);

			rowcounter++;
		}
		else if(strcmp(word,"jsr1")==ZERO||strcmp(word,"jsr2")==ZERO)
		{
			if(word[strlen(word)-ONE]=='2')
				*IC+=FOURLINES;
			else
				*IC+=TWOLINES;
			
			c=fscanf(text,"%s",word);

			if(strcmp(word,"$$")==0||word[ZERO]=='#'||sign_check(word))
			{
				printf("Error: Invalid destination operand line %d\n",rowcounter);
				*error=ONE;
			}
			
			strcpy(prevword,word);
			c=fscanf(text,"%s",word);

			rowcounter++;
		}
		else if(strcmp(word,"rts1")==ZERO||strcmp(word,"rts2")==ZERO)
		{
			if(word[strlen(word)-ONE]=='2')
				*IC+=TWOLINES;
			else
				*IC+=ONELINE;
			c=fscanf(text,"%s",word);
			rowcounter++;
		}

		else if(strcmp(word,"stop1")==ZERO||strcmp(word,"stop2")==ZERO)
		{
			if(word[strlen(word)-ONE]=='2')
				*IC+=TWOLINES;
			else
				*IC+=ONELINE;
			c=fscanf(text,"%s",word);
			rowcounter++;
		}
		else if(strcmp(word,"prn1")==ZERO||strcmp(word,"prn2")==ZERO)
		{
			if(word[strlen(word)-ONE]=='2')
				*IC+=FOURLINES;
			else
				*IC+=TWOLINES;
			Scan_next();
			rowcounter++;
		}
		else if(strcmp(word,".data")==ZERO)/*Collecting the data of numbers. again i will collect it char by char because there mught be blank spaces or tabs inbetween the numbers.*/
		{
			word[0]='\0';
			c=fgetc(text);

			do{
				if(c!=' '&&c!='\t'&&c!=EOF)
				{
					word[strlen(word)+1]='\0';
					word[strlen(word)]=c;
				}

				if(c==EOF)/*Incase i reach end of file.*/
					break;

				c=fgetc(text);

			}while(c!='\n');

			data_table=digitsDataHendler(word,data_table,DC,rowcounter,error);

			if(c==EOF)
				break;
			else
				c=fscanf(text,"%s",word);

			rowcounter++;
		}
		else if(strcmp(word,".string")==ZERO)
		{

			word[0]='\0';							/*I am reading char by char in case there are  */
													/*blank spaces in the string. fscanf is ending */
			do{										/*tehe string on blank spaces.				   */
				c=fgetc(text);

				if(c=='"')/*I already wrote the function to handle quotes signs, this is why they are included in the string.*/
				{
					if(quotesflag==ONE)
						quotesflag=3;
					else
						quotesflag=ONE;

					word[strlen(word)+1]='\0';
					word[strlen(word)]=c;
				}
				else if(quotesflag==ONE)
				{
					word[strlen(word)+1]='\0';
					word[strlen(word)]=c;
				}
				
			}while(c!=EOF&&c!='\n'&&quotesflag!=3);

			data_table=charDataHendler(word,data_table,DC);

			if(c==EOF)
				break;
			else
				c=fscanf(text,"%s\n",word);

			rowcounter++;
		}
		else if(word[(strlen(word)-ONE)]==':')	/*Checking if there is a colon sign at the end of the word*/
		{
			word[(strlen(word)-ONE)]='\0';

			lable_name_check(word,error,rowcounter);/*Checking lable name.*/

			strcpy(tempword,word);
			c=fscanf(text,"%s",word);

			if((strcmp(word,".string")==ZERO)||(strcmp(word,".data")==ZERO))
				insert_word(sign_table,tempword,lableTableIndex,*DC,SP,TYPEDATA,error,rowcounter);
			else
				insert_word(sign_table,tempword,lableTableIndex,*IC,SP,TYPEORDER,error,rowcounter);
		}
		else if(strcmp(word,".extern")==ZERO)
		{
			c=fscanf(text,"%s",word);
			insert_word(sign_table,word,lableTableIndex,0,SP,TYPEEXTERN,error,rowcounter);/*The 0 here should represent the adress of the lable but its an extern lable so no adress is provided.*/
			c=fscanf(text,"%s",word);
			rowcounter++;
		}
		else if(strcmp(word,".entry")==0)
		{
			rowcounter++;
			Scan_next();
		}
		else if(text==NULL)
			break;
		else
		{
			printf("Error: Line %4d\tInvalid order: %s\n",rowcounter,word);
			*error=ONE;
			rowcounter++;
			Scan_next();
		}

	}while(c!=EOF);

if(text!=NULL)
	fclose(text);

return data_table;


}
