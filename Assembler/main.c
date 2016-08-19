/* Name: Yvgeny Konrad id: 312737620*/	

/* This is an assembler program. The program scans from command line the name of the file to open.					*/
/* After the file is found the program scans the file ones and creates two arrys.									*/
/*																													*/
/*	 1.Array of all the lables, their address and type appearing in the file.										*/
/*	 2.Array of the defined data appearing in the file.																*/
/* On second scan the program creates the final array. The array size difined by the number of orrders in the file 	*/
/* and it's an int array. Only the firs 12 bits of the int are important by definition of the task. 				*/
/* After the final table is complited the program changes the bunary code to 4 base and put's everithing 			*/
/* in output file named "file_name".ob . The program creates two more files if needed.								*/
/*	 1. Entry file of all the entries in the file.File name "file_name".ent .										*/
/* 	 2. External of all the externals in the file. file name "file_name".ext .										*/

#include "main.h"

int main(int argc,char const *argv[])
{
	char name[MAXLENGTHOFFILENAME];/*This char array will hold the scanned file name.*/
	char *dotname=".as";/*The user enters only the name of the file, this is the extension.*/

	int i;
	int PC;/*Program Counter*/
	int SP;/*Stack pointer*/
	int IC,DC;/*All the counters of the program.*/
	int error;/*In case there are errors in the original code,the program won't create the files and print an error massege.*/
	int lableTableIndex;/*This is an index counter to know how many enteries we have at the lable table.*/
	signed int *data_table=malloc(ONE*sizeof(int));/*Creating one cell for data table, will allocate more with the data.*/
	signed int *final_table;/*This is the final table with which i create the output file .ob*/

	struct sign lable_table[MAXLABLENUMBER];/*Creating an array of struct sign to hold the lables data. Set to max 100.*/

	for(i=1;i<argc;i++)
	{
		IC=ZERO;		     /*										 */
		DC=ZERO;		     /*										 */
		SP=STARTADRESSLINE;  /*Initializing all the counters to zero.*/
		PC=ZERO;		     /*										 */
		error=ZERO;		     /*										 */
		lableTableIndex=ZERO;/*							   			 */

		strcpy(name,argv[i]);
		strcat(name,dotname);
		data_table=first_read(name,&IC,&DC,data_table,lable_table,&lableTableIndex,SP,&error);/*The first read is counting the number of orders that will be writen at the end and creates the data table.*/

		final_table=calloc((IC+DC),sizeof(int));/*Creating the final table. IC and DC holds the exact number of lines i need.*/

		final_table=second_read(name,lable_table,data_table,final_table,IC,DC,&PC,SP,lableTableIndex,&error);/*The second read creates the final table.*/
	
		if(error==ZERO)
			file_otput(final_table,IC,DC,SP,name);/*Creates the file .ob.*/

		
	}
		free(final_table);
		free(data_table);

	return ZERO;
}
