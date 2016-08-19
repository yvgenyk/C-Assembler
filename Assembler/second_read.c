/* Name: Yvgeny Konrad id: 312737620*/	

#include "second_read.h"

#define two_operand_order(opcode)\
{\
	if(word[strlen(word)-ONE]=='2')/*In case the order should execute twise.*/\
		flag_number_of_orders=ONE;\
\
	word[0]='\0';/*In case of blank spaces or tabs i am scanning the two operands after the order leter by leter, then combine them into one string.*/\
	c=fgetc(text);\
	do{\
		if(c!=' '&&c!='\t')\
		{\
			word[strlen(word)+1]='\0';\
			word[strlen(word)]=c;\
		}\
\
		c=fgetc(text);\
\
	}while(c!='\n');\
\
	strcpy(secondword,comma_sep_after(word,error,rowcounter));/*Seperating the string into two words, one for each operand.*/\
	strcpy(word,comma_sep_before(word,strlen(secondword)));\
\
	for(i=ZERO;i<=flag_number_of_orders;i++)\
	{\
		final_table[*PC]=order_line_fill(word,secondword,prevword,opcode,PC,rowcounter);/*Filling the order line.*/\
		final_table[*PC]=ZERO;\
		final_table[*PC]=line_fill(final_table[*PC],word,prevword,sign_table,IC,lableTableIndex,&registerflag,PC,7,SP,&external_flag,externalfile_name,error,rowcounter);/*Inserting the first operand line.*/\
\
		if(registerflag==ONE&&(secondword[ZERO]=='r'&&secondword[ONE]>='0'&&secondword[ONE]<='7'&&strlen(secondword)==2))/*If the operands are two registers, the stack pointer isn't progressing.*/\
			(*PC)--;\
		else\
			final_table[*PC]=ZERO;\
\
	final_table[*PC]=line_fill(final_table[*PC],secondword,prevword,sign_table,IC,lableTableIndex,&registerflag,PC,2,SP,&external_flag,externalfile_name,error,rowcounter);/*Inserting the second operand.*/\
	registerflag=ZERO;/*Reseting the register flag.*/\
	}\
\
	flag_number_of_orders=ZERO;\
	strcpy(prevword,word);/*Saving the first operand, in case of $$ in the next order line.*/\
\
	rowcounter++;\
}

#define one_operand_order(opcode)\
{\
	if(word[strlen(word)-ONE]=='2')/*In case the order should execute twise.*/\
		flag_number_of_orders=ONE;\
\
	c=fscanf(text,"%s",secondword);\
\
	for(i=ZERO;i<=flag_number_of_orders;i++)\
	{\
		word[ZERO]='#';\
		final_table[*PC]=order_line_fill(word,secondword,prevword,opcode,PC,rowcounter);\
		final_table[*PC]=ZERO;\
		final_table[*PC]=line_fill(final_table[*PC],secondword,prevword,sign_table,IC,lableTableIndex,&registerflag,PC,2,SP,&external_flag,externalfile_name,error,rowcounter);\
	}\
\
	registerflag=ZERO;\
	flag_number_of_orders=ZERO;\
	strcpy(prevword,secondword);\
	rowcounter++;\
}

int *second_read(char *prog_name,struct sign *sign_table,int *data_table,int *final_table,int IC,int DC,int *PC,int SP,int lableTableIndex,int *error)
{
	int i,registerflag=ZERO,flag_number_of_orders=ZERO,entryfile_flag=ZERO,external_flag=ZERO;/*Creating flags for the program and two others for the output files .ent and .ext.*/
	int rowcounter=ONE;
	int c;

	char word[MAXLINELENGTH],secondword[MAXLINELENGTH],prevword[MAXLINELENGTH]="\0";
	char entryfile_name[MAXLENGTHOFFILENAME],externalfile_name[MAXLENGTHOFFILENAME];

	FILE *text;
	FILE *entryFile;
	text=fopen(prog_name,"r");

	strcpy(entryfile_name,prog_name);
	entryfile_name[strlen(prog_name)-3]='\0';/*The name provided is with the extensio .as. I am ending the strig at the dot place and replasing it with (if needed) other extansions.*/
	strcpy(externalfile_name,entryfile_name);
	strcat(entryfile_name,".ent");
	strcat(externalfile_name,".ext");

	for(i=ZERO;i<DC;i++)/*Copying the data table into the final table.*/
		final_table[IC+i]=data_table[i];

	if(text==NULL)
		*error=ONE;
	else
		c=fscanf(text,"%s",word);/*Scans the firs word from the file.*/

do{
		
		if(text==NULL)
			break;

		if(word[0]==';')/*Incase there is a note in the code.*/
		{
			while(c!='\n')
				c=fgetc(text);

			rowcounter++;
			c=fscanf(text,"%s",word);
		}

		if(strcmp(word,"mov1")==ZERO||strcmp(word,"mov2")==ZERO)
		{
			two_operand_order(MOV);
		}
		else if(strcmp(word,"cmp1")==ZERO||strcmp(word,"cmp2")==ZERO)
		{
			two_operand_order(CMP);
		}

		else if(strcmp(word,"add1")==ZERO||strcmp(word,"add2")==ZERO)
		{
			two_operand_order(ADD);
		}
		else if(strcmp(word,"sub1")==ZERO||strcmp(word,"sub2")==ZERO)
		{
			two_operand_order(SUB);
		}
		else if(strcmp(word,"not1")==ZERO||strcmp(word,"not2")==ZERO)
		{
			one_operand_order(NOT);
		}
		else if(strcmp(word,"clr1")==ZERO||strcmp(word,"clr2")==ZERO)
		{
			one_operand_order(CLR);
		}

		else if(strcmp(word,"lea1")==ZERO||strcmp(word,"lea2")==ZERO)
		{
			two_operand_order(LEA);
		}
		else if(strcmp(word,"inc1")==ZERO||strcmp(word,"inc2")==ZERO)
		{
			one_operand_order(INC);
		}
		else if(strcmp(word,"dec1")==ZERO||strcmp(word,"dec2")==ZERO)
		{
			one_operand_order(DEC);
		}
		else if(strcmp(word,"jmp1")==ZERO||strcmp(word,"jmp2")==ZERO)
		{
			one_operand_order(JMP);
		}

		else if(strcmp(word,"bne1")==ZERO||strcmp(word,"bne2")==ZERO)
		{
			one_operand_order(BNE);
		}
		else if(strcmp(word,"red1")==ZERO||strcmp(word,"red2")==ZERO)
		{
			one_operand_order(RED);
		}
		else if(strcmp(word,"jsr1")==ZERO||strcmp(word,"jsr2")==ZERO)
		{
			one_operand_order(JSR);
		}
		else if(strcmp(word,"rts1")==ZERO||strcmp(word,"rts2")==ZERO)
		{
			final_table[*PC]=ZERO;
			final_table[*PC]=final_table[*PC]|(ZERO<<10);
			final_table[*PC]=final_table[*PC]|(RTS<<6);
			(*PC)++;
		}

		else if(strcmp(word,"stop1")==ZERO||strcmp(word,"stop2")==ZERO)
		{
			final_table[*PC]=ZERO;
			final_table[*PC]=final_table[*PC]|(ZERO<<10);
			final_table[*PC]=final_table[*PC]|(STOP<<6);
			(*PC)++;
		}
		else if(strcmp(word,"prn1")==ZERO||strcmp(word,"prn2")==ZERO)
		{
			one_operand_order(PRN);
		}
		else if(strcmp(word,".entry")==ZERO)
		{
			c=fscanf(text,"%s",word);
			
			for(i=ZERO;i<lableTableIndex;i++)
			{
				if(strcmp(word,sign_table[i].name)==ZERO)
				{
					if(entryfile_flag==ZERO)/*First time opening the file, else every order it will delete the previose file.*/
					{
						if(*error==0)
						{
							entryFile=fopen(entryfile_name,"w");

							if(entryFile==NULL)/*Incase there was a problem oppening the file.*/
							{
								printf("Error: There was a problem opening the entry file.\n");
								*error=ONE;
							}
							else
								entryfile_flag=ONE;
						}
					}

					if(*error==0)
					{
						if(sign_table[i].type==ONE)/*Checking the type of the lable data/order.*/
							fprintf(entryFile,"%s\t%d\n",sign_table[i].name,number_to_four_base(sign_table[i].loc+IC,ONE));
						else
							fprintf(entryFile,"%s\t%d\n",sign_table[i].name,number_to_four_base(sign_table[i].loc,ONE));
					}
					
				}
			}
			rowcounter++;
		}
		else if(strcmp(word,".extern")==ZERO)
			rowcounter++;

		c=fscanf(text,"%s",word);
		

	}while(c!=EOF);

if(entryfile_flag==ONE)
	fclose(entryFile);

if(text!=NULL)
	fclose(text);

return final_table;


}