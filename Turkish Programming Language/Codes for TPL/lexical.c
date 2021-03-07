/* front.c - a lexical analyzer system for simple
arithmetic expressions */
#include <stdio.h>
#include <ctype.h>
/* Global declarations */
/* Variables */
int charClass;
char lexeme [100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp, *fopen();
void addChar();
void getChar();
void getNonBlank();
int lex();
/* Character classes */
#define HARF 0
#define RAKAM 1
#define BILINMEYEN 99
/* Token codes */
#define TAM_SIN 10
#define BELIRTICI 11
#define ATAMA_IS 20
#define TOPLAMA_IS 21
#define CIKARTMA_IS 22
#define CARPMA_IS 23
#define BOLME_IS 24
#define SOL_KAPA 25
#define SAG_KAPA 26
#define SOL_BILDIRI_PAR 27
#define SAG_BILDIRI_PAR 28
#define IKI_NOK 29
#define VE_IS 30
#define YADA_IS 31
#define MOD_IS 32
#define SOL_DIZI_B_P 33
#define SAG_DIZI_B_P 34
#define ESIT 35
#define NOKTALI_VIRGUL 36
#define CIFT_TIRNAK 37
#define ARALIK 38
#define SOL_PARANTEZ 39
#define SAG_PARANTEZ 40
#define VIRGUL 41
#define NOKTA 42
/* main driver */
void main() {
/* Open the input data file and process its contents */
if ((in_fp = fopen("girdi.txt", "r")) == NULL)
printf("ERROR - cannot open front.in \n");
else {
getChar();
do {
lex();
} while (nextToken != EOF);
}
}
/*****************************************************/
/* lookup - a function to lookup operators and parentheses
and return the token */
int lookup(char ch) {
switch (ch) {
case '<':
addChar();
nextToken = SOL_KAPA;
break;
case '>':
addChar();
nextToken = SAG_KAPA;
break;
case '+':
addChar();
nextToken = TOPLAMA_IS;
break;
case '-':
addChar();
nextToken = CIKARTMA_IS;
break;
case '.':
addChar();
nextToken = NOKTA;
break;
case '*':
addChar();
nextToken = CARPMA_IS;
break;
case '/':
addChar();
nextToken = BOLME_IS;
break;
case '~':
addChar();
nextToken= VE_IS;
break;
case '$':
addChar();
nextToken= MOD_IS;
break;
case 'é':
addChar();
nextToken= YADA_IS;
break;
case ':':
addChar();
nextToken= IKI_NOK;
break;
case '[':
addChar();
nextToken= SOL_BILDIRI_PAR;
break;
case ']':
addChar();
nextToken= SAG_BILDIRI_PAR;
break;
case '{':
addChar();
nextToken= SOL_DIZI_B_P;
break;
case '=':
addChar();
nextToken= ESIT;
break;
case '}':
addChar();
nextToken= SAG_DIZI_B_P;
break;
case ';':
addChar();
nextToken= NOKTALI_VIRGUL;
break;
case '"':
addChar();
nextToken= CIFT_TIRNAK;
break;
case '|':
addChar();
nextToken= ARALIK;
break;
case '(':
addChar();
nextToken= SOL_PARANTEZ;
break;
case ')':
addChar();
nextToken= SAG_PARANTEZ;
break;
case ',':
addChar();
nextToken= VIRGUL;
break;

default:
addChar();
nextToken = EOF;
break;
}
return nextToken;
}
/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar() {
if (lexLen <= 98) {
lexeme[lexLen++] = nextChar;
lexeme[lexLen] = 0;
}
else
printf("Error - lexeme is too long \n");
}
/*****************************************************/
/* getChar - a function to get the next character of
input and determine its character class */
void getChar() {
if ((nextChar = getc(in_fp)) != EOF) {
if (isalpha(nextChar))
charClass = HARF;
else if (isdigit(
nextChar))
charClass = RAKAM;
else charClass = BILINMEYEN;
}
else
charClass = EOF;
}
/*****************************************************/
/* getNonBlank - a function to call getChar until it
returns a non-
whitespace
character */
void getNonBlank() {
while (isspace(nextChar))
getChar();
}
/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic
expressions */
int lex() {
lexLen = 0;
getNonBlank();
switch (charClass) {
    /* Parse belirticiler */
case HARF:
addChar();
getChar();
while (charClass == HARF || charClass == RAKAM) {
addChar();
getChar();
}
nextToken = BELIRTICI;
break;
/* Parse tam sýn */
case RAKAM:
addChar();
getChar();
while (charClass == RAKAM) {
addChar();
getChar();
}
nextToken = TAM_SIN;
break;
/* Parentheses and operators */
case BILINMEYEN:
lookup(nextChar);
getChar();
break;
/* EOF */
case EOF:
nextToken = EOF;
lexeme[0] = 'E';
lexeme[1] = 'O';
lexeme[2] = 'F';
lexeme[3] = 0;
break;
} /* End of switch */
printf("Next token is: %d, Next lexeme is %s\n",
nextToken, lexeme);
return nextToken;
} /* End of function lex */
