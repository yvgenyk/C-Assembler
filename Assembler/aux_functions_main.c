/* Name: Yvgeny Konrad id: 312737620*/	

#include "aux_functions_main.h"

/*Changes the number sent to it from desimal base to 4 base with recursion.
  Can only work with positive numbers. Handles only the adress lines.*/
int number_to_four_base(int num,int helpindex)
{

	int base=FOURBASE;
	int result=ZERO;

	if(num>ZERO)
	{
		result=(num%base)*helpindex;
		helpindex=helpindex*10;
		result+=number_to_four_base(num/base,helpindex);
	}
	
	return result;

}

/*Handles all the output lines from the final table.
  Use strings to calculate the 4 base from the binnary base.*/
char *number_to_four(int num,char *result)
{
	int j;
	result[ZERO]='\0';

	for(j=11;j>=ZERO;j--)
	{
		if(num&(ONE<<j))
		{
			j--;
			if(num&(ONE<<j))
				strcat(result,"3");
			else
				strcat(result,"2");
		}
		else
		{
			j--;
			if(num&(ONE<<j))
				strcat(result,"1");
			else
				strcat(result,"0");
		}
	}

	strcat(result,"\0");
	return result;

}

/*Creates a file with the .ob extension and the source file name.*/
void file_otput(signed int *table,int IC,int DC,int SP,char *name)
{
	int i=ZERO;
	char result[7]="\0";
	FILE *output_file;

	name[strlen(name)-3]='\0';
	strcat(name,".ob");

	output_file=fopen(name,"w");
	
	if(output_file==NULL)
		printf("There was a problem creating the output file.\n");
	else
	{
		fprintf(output_file,"Base 4 Address\tBase 4 machine code\n%d\t\t\t\t%d\n",number_to_four_base(IC,ONE),number_to_four_base(DC,ONE));

		for(i=ZERO;i<IC+DC;i++)
		{
			fprintf(output_file,"%d\t",number_to_four_base(i+SP,ONE));
			fprintf(output_file,"\t\t%s\n",	number_to_four(table[i],result));
		}
	}

	fclose(output_file);
}