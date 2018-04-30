/* Infix notation calculator.  */

%{
  #include <math.h>
  #include <stdlib.h>
  #include <stdio.h>
	#include <string.h>
  #include "asm4.tab.h"
  extern int yylex();
  int yyparse(void);

  void yyerror (char *);
  void error(int error);
  int checkerr=0;
  int var[26];

%}

/* Bison declarations.  */

%union
{
    int intValue;
    char *stringValue;
}

%start  input
%token  NUM REG UNK PRINT PRINTLN IF LOOP STRING DEC HEX ELSE/* tokens */
%left   '-' '+'
%left   '*' '/' '\\'
%precedence NEG       /* negation--unary minus */

%type<intValue> NUM exp REG if 
%type<stringValue> STRING print println


%% /* The grammar follows.  */

input:
  %empty
| input line 
;

line: /* map stack operation or expression*/
  '\n'
| assign ';'					{ }
| print ';'						{ printf("%s ",$1); }
| println ';'					{ printf("%s\n",$1); }
| if									{ }
| loop								{ }
;



exp: /* expressions */
  NUM 								{ $$ = $1;}
| REG									{ $$ = var[$1]; }
| exp '+' exp        	{ $$ = $1 + $3; }
| exp '-' exp        	{ $$ = $1 - $3; }
| exp '*' exp        	{ $$ = $1 * $3; }
| exp '/' exp        	{ if($3==0) {
													error(2);  		/*check if divide by 0 */
													checkerr =1;			
			  								}			  
			  								else
													$$ = $1 / $3;
											}
| exp '%' exp       	{ if($3==0) { 			/*check if modulo by 0 */
													error(3); 
													checkerr =1;			
												}			  
												else
												$$ = $1 % $3;
											}
| '-' exp  %prec NEG 	{ $$ =-$2; }
| '(' exp ')'        	{ $$ = $2; }
;


assign: /*assign value to register*/
  REG '=' exp					{ var[$1] = $3; }
;

print: /*print*/
  PRINT '(' exp ','  DEC ')'						{ char str[30];
																					sprintf(str, "%d", $3);
																					$$=str;
																				}
| PRINT '(' exp ','  HEX ')' 						{ char str[30];
																					sprintf(str, "%x", $3);
																					for(int i=0;i<strlen(str);i++){
																						if(str[i] > '9')
																							str[i] = str[i] - 32; 
																						}
																					$$=strcat(str,"h");
																			  }
| PRINT '('  STRING ')' 								{ $$ = $3; }
;

println: /*print line*/
  PRINTLN '(' exp ','  DEC ')' 				 { char str[30];
																				 sprintf(str, "%d", $3);
																				 $$=str; 
																			 }
| PRINTLN '(' exp ','  HEX ')' 				{ char str[30];
																				sprintf(str, "%x", $3);
																				for(int i=0;i<strlen(str);i++){
																					if(str[i] > '9')
																						str[i] = str[i] - 32; 
																				}
																				$$=strcat(str,"h"); 
																		  }
| PRINTLN '('  STRING ')' 						{ $$ = $3; }
;

if: 
  IF '(' exp ',' exp ')' '{' stmt '}' else { if($3==$5){
																								$$=$8;
																											
																				} 
																			}
;
else:
	%empty															{printf("no else\n");}
| ELSE '{' stmt '}'										{}
;


stmt: 
	%empty
| stmt line {}
;

loop:
  LOOP '(' exp ',' exp ')' '{' stmt '}'  { }
;
%%

void yyerror(char *s) 
{
	fprintf(stderr, "%s\n",s );
}

void error(int error) /* error checking */
{
	switch(error){
		case 1:
			printf("ERROR OCCURED !\n");
			break;
		case 2:
			printf("DIVIDED BY ZERO !\n");
			break;
		case 3:
			printf("MODULO BY ZERO !\n");
			break;
		case 4:
			printf("SYNTAX ERROR !\n");
			break;
		case 5:
			printf("STACK EMPTY !\n");
			break;
	}
}

int main(){
	printf("> ");
	while(1)
		yyparse();
	return 0;
}

