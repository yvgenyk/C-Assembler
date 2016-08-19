/* Name: Yvgeny Konrad id: 312737620*/	

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXLINELENGTH 80
#define LABLEMAXLENGTH 31
#define ZERO 0
#define ONE 1
#define MAXREGISTERNAMEL 2
#define MAXNUMOFDIGITS 74
#define MAXCHARLENGTH 2

struct sign /*This structure will hold the signs table.*/
{
	char name[LABLEMAXLENGTH]; /*The name of the sign.*/
	int loc; /*The location of the sign.*/
	int type;
};

int sign_check(char *);/*Check if the word is a sign or a number/register.*/
int wordcmp(struct sign *,char *,int);/*Searching the sign table for existing signs. 
										If there is an existing sign will retun zero*/

char *comma_sep_after(char *,int *,int); /*Returns the sign after the comma.*/
char *comma_sep_before(char *,int);/*Returns the sign before the comma.*/
void insert_word(struct sign *,char *,int *,int,int,int,int *,int);/*Inserts a sign word into the sign table.*/
int *digitsDataHendler(char *,int *,int *,int,int *);/*Inserts the digit into the data array.*/
int *charDataHendler(char *word,int *data_table,int *d_index);/*Inserts the chars into the data array.*/
void lable_name_check(char *,int *,int);/*Checking if the name of the lable coteins aproved characters.*/