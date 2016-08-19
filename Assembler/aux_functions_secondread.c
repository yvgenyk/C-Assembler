/* Name: Yvgeny Konrad id: 312737620*/	

#include "aux_functions_secondread.h"


/*This function fills the order line. It get's two word to check the destination operator and the origin operator. 
  The function also get's the first operator from the last order in case there is $$ order, 
  it get's the opcode to fill in the order line and the stack pointer.*/
int order_line_fill(char *word,char *secondword,char *prevword,int opcode,int *PC,int rowcounter)
{
	int temp=ZERO;

	temp=temp|(opcode<<6);/*Inceting opcode into the line.*/

	if(opcode==MOV||opcode==CMP||opcode==ADD||opcode==SUB||opcode==LEA)/*Inserting the amount of operators of the order. Depend's on the order.*/
		temp=temp|(TWOPERANDS<<10);
	else
		temp=temp|(ONEOPERAND<<10);

	if(word[0]=='$'&&word[1]=='$')/*Checking the type of the first operator.*/
	{
		if(prevword[0]=='r'&&prevword[1]>='0'&&prevword[1]<='7'&&strlen(prevword)==2)
			temp=temp|(REGISTOROPERAND<<4);
		else if(prevword[0]!='#')
			temp=temp|(LABLEOPERAND<<4);
	}
	else if(word[0]=='r'&&word[1]>='0'&&word[1]<='7'&&strlen(word)==2)
		temp=temp|(REGISTOROPERAND<<4);
	else if(word[0]!='#')
		temp=temp|(LABLEOPERAND<<4);

	/*Checking the type of the second operator.*/
	if(secondword[0]=='r'&&secondword[1]>='0'&&secondword[1]<='7'&&strlen(secondword)==2)
		temp=temp|(REGISTOROPERAND<<2);
	else if(secondword[0]!='#')
		temp=temp|(LABLEOPERAND<<2);

	(*PC)++;/*Increasing the stack pointer by one after i finished with the line.*/

	return temp;
}

/*Fills the operators lines. Gets the operator(word),previouse order first operator in case of $$ order,
the lable table that contains all the lables that were read by the first read,the number of orders IC,
the number of lable table entries, registerflag incase it is a register, the stack pointer and the place to put a register if there is one.
The temp integer is sent from the main second read function in case the two operands are registers and 
there is only one line to fill.*/
int line_fill(int temp,char *word,char *prevword,struct sign *sign_table,int IC,int lableTableIndex,int *registerflag,int *PC,int regplace,int SP,int *external_flag,char *externalfile_name,int *error,int rowcounter)
{
	int i,foundflag=ZERO;/*The foundflag is for the case there is unrecognizble lable/operand.*/
	FILE *externFile;

	if(word[0]=='$'&&word[1]=='$')/*Checks the type of the operand.If it is a previouse order operand the prevword is supllied.
									Then checking the type of the prevword.*/
	{
		if(strcmp(prevword,"\0")==0)
		{
			printf("Error: The operand $$ requers the first operand of last order. There is no such operand.\n");
			*error=ONE;
		}
		else if(prevword[0]=='r'&&prevword[1]>='0'&&prevword[1]<='7'&&strlen(prevword)==2)
		{
			temp=temp|(atoi(prevword+1)<<regplace);
			*registerflag=1;/*With the flag on i can see on the next operand if there is two registers.*/
		}
		else if(prevword[0]!='#')
		{
			for(i=0;i<lableTableIndex;i++)
			{
				if(strcmp(prevword,sign_table[i].name)==0)
				{
					if(sign_table[i].type==1)/*Checking the type of the lable data/order.*/
					{
						temp=temp|((sign_table[i].loc+IC)<<2);
						temp=temp|(R<<0);
					}
					else if(sign_table[i].type==2)
					{
						temp=temp|((sign_table[i].loc)<<2);
						temp=temp|(R<<0);
					}
					else if(sign_table[i].type==3)
					{
						if(*external_flag==0&&*error==0)
						{
							externFile=fopen(externalfile_name,"w");
							*external_flag=ONE;
						}
						else if(*error==0)
							freopen(externalfile_name,"a",externFile);

						if(externFile==NULL)
						{
							printf("Error: There was a problem openning the external file.\n");
							*error=ONE;
						}
						else if(*error==0)
						{
							temp=temp|(0<<2);
							temp=temp|(E<<0);
						
							fprintf(externFile,"%s\t%d\n",sign_table[i].name,number_to_four_base(*PC+SP,ONE));
						}	

					}

				}
	
			}

		}
		else
		{
			if(atoi(prevword+ONE)>=((-1)*(pow(2,9)))&&atoi(prevword+ONE)<=(pow(2,9)-1))
				temp=temp|(atoi(prevword+1)<<2);
			else
			{
				printf("Error: Invalid number entered line: %d\n",rowcounter);
				*error=ONE;
			}
		}
	}
	else if(word[0]=='r'&&word[1]>='0'&&word[1]<='7'&&strlen(word)==2)/*Checking if it is a register.*/
	{
		temp=temp|(atoi(word+1)<<regplace);
		*registerflag=1;
	}
	else if(word[0]!='#')/*Checking if it's a lable.*/
	{
		for(i=0;i<lableTableIndex;i++)
		{
			if(strcmp(word,sign_table[i].name)==0)
			{
				if(sign_table[i].type==1)/*Checking the type of the lable data/order.*/
				{
					temp=temp|((sign_table[i].loc+IC)<<2);
					temp=temp|(R<<0);
					foundflag=ONE;
				}
				else if(sign_table[i].type==2)
				{
					temp=temp|((sign_table[i].loc)<<2);
					temp=temp|(R<<0);
					foundflag=ONE;
				}
				else if(sign_table[i].type==3)
				{
					if(*external_flag==0&&*error==0)
						{
							externFile=fopen(externalfile_name,"w");
							*external_flag=ONE;
						}
						else if(*error==0)
							freopen(externalfile_name,"a",externFile);

						if(externFile==NULL)
						{
							printf("Error: There was a problem openning the external file.\n");
							*error=ONE;
						}
						else if(*error==0)
						{
							temp=temp|(0<<2);
							temp=temp|(E<<0);
						
							fprintf(externFile,"%s\t%d\n",sign_table[i].name,number_to_four_base(*PC+SP,ONE));
							foundflag=ONE;
						}
				}	
			}
		}

		if(foundflag==ZERO&&(*error)==ZERO)
		   	{
				printf("Error: Invalid operand at line: %d\n",rowcounter);
				*error=ONE;
			}

	}
	else/*This order will execute if the operand is a number.*/
	{
		if(atoi(word+ONE)>=(-(pow(2,9)))&&atoi(word+ONE)<=(pow(2,9)-1))
				temp=temp|(atoi(word+1)<<2);
	}


	(*PC)++;

return temp;
}