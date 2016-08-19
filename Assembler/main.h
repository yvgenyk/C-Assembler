/* Name: Yvgeny Konrad id: 312737620*/	

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLABLENUMBER 100
#define STARTADRESSLINE 100
#define LABLEMAXLENGTH 31
#define MAXLENGTHOFFILENAME 20
#define ZERO 0
#define ONE 1

struct sign /*This structure will hold the signs table.*/
{
	char name[LABLEMAXLENGTH]; /*The name of the sign.*/
	int loc; /*The location of the sign.*/
	int type;
};

char *number_to_four(int,char *);
signed int number_to_four_base(int,int);
int *first_read(char *,int *,int *,int *,struct sign *,int *,int,int *);
int *second_read(char *,struct sign *,int *,int *,int ,int,int *,int,int,int *);
void file_otput(signed int *,int ,int ,int ,char *);