/* Name: Yvgeny Konrad id: 312737620*/	

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MOV 0
#define CMP 1
#define ADD 2
#define SUB 3
#define NOT 4
#define CLR 5
#define LEA 6
#define INC 7
#define DEC 8
#define JMP 9
#define BNE 10
#define RED 11
#define PRN 12
#define JSR 13
#define RTS 14
#define STOP 15

#define A 0
#define R 2
#define E 1

#define MAXLINELENGTH 80
#define LABLEMAXLENGTH 31
#define ONE 1
#define ZERO 0
#define MAXLENGTHOFFILENAME 20

struct sign /*This structure will hold the signs table.*/
{
	char name[LABLEMAXLENGTH]; /*The name of the sign.*/
	int loc; /*The location of the sign.*/
	int type;
};

int number_to_four_base(int,int);
char *comma_sep_after(char *,int *,int); /*Returns the sign after the comma.*/
char *comma_sep_before(char *,int);/*Returns the sign before the comma.*/
int order_line_fill(char *,char *,char *,int,int *,int);
int line_fill(int,char *,char *,struct sign *,int,int,int *,int *,int,int,int *,char *,int *,int);