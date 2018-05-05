%option noyywrap
%option yylineno

L           [a-zA-Z_]

/*library*/
%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "asm4.tab.h"

#define YY_DECL int yylex()
 
int hex_to_dec(char *);
%}

/*Regular expression*/
%% 
[ \n\t\f\v]                     ;                        /* Ignore */
"print"             { return PRINT; }
"println"           { return PRINTLN; }
"if"                { return IF; }
"else"              { return ELSE; }
"loop"              { return LOOP; }
[r]([0-9]|[1][0-9]|[2][0-5])    { yylval.intValue = yylval.intValue = str_to_dec(yytext); return REG;} /* Variable Token ($rA-$rZ) */
[0-9]+                          { yylval.intValue = atoi(yytext); return NUM;}         /* number Token (0-infinity)*/
[0-9A-Fa-f]+[Hh]                { yylval.intValue = hex_to_dec(yytext); return NUM;}   /* base 16 number Token (15AH) */
[-+*()/=%,";{}]                 { return *yytext;}                           /* operation Token */
"dec"                           { return DEC;} 
"hex"                           { return HEX;} 
L?\"(\\.|[^\\"])*\"     { yylval.stringValue=strndup(yytext+1,strlen(yytext)-2); return STRING; }
.                               { return UNK;}                               

%%

int str_to_dec(char *str) /* convert hexadecimal to decimal */
{
    long long decimalNumber=0;
    char digits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int i, j, power=0 ;

    /* Converting hexadecimal number to decimal number */
    for(i=strlen(str)-1; i > 0; i--)
    {
        /*search current character in hexDigits array */
 	for(j=0; j<10; j++)
        {
            if(str[i]==digits[j])
            {
                decimalNumber += j*pow(10, power);
            }
        }
        power++;
    }
    return decimalNumber;
}

/*function*/
int hex_to_dec(char *hex) /* convert hexadecimal to decimal */
{
    long long decimalNumber=0;
    char hexDigits[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
                          '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    int i, j, power=0, digit;

    /* Converting hexadecimal number to decimal number */
    for(i=strlen(hex)-2; i >= 0; i--)
    {
        /*search current character in hexDigits array */
        for(j=0; j<16; j++)
        {
            if(hex[i] == hexDigits[j])
            {
                decimalNumber += j*pow(16, power);
            }
        }
        power++;
    }
    return decimalNumber;
}
