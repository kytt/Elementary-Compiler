/* Infix notation calculator.  */

%{
  #include <math.h>
  #include <stdlib.h>
  #include <stdio.h>
  #include <string.h>
  #include "asm4.tab.h"
  
  typedef struct node {
		char data[1000];
		struct node* next;
	} node;
	typedef struct stack {
		int data;
		struct stack* next;
	} stack;
		
  extern int yylex();
  extern int yyin;
  int yyparse(void);

  void yyerror (char *);
  void error(int error);
  int checkerr=0;
  int var[26];
	stack *hstack = NULL;
	node *hcode = NULL;
	node *tcode = NULL;
	node *hdata = NULL;
	node *tdata = NULL;
	node *global = NULL;
	int checkfn[4] = {0,0,0,0};
	int check =0;
	int labelNUM = 1 ;
	int strNUM = 1;

void push(int data){
	stack *stk = (stack*)malloc(sizeof(stack));
	stk->data = data;
	stk->next = hstack;
	hstack = stk;
	
	
}

void init(){
	node *tmp = (node*)malloc(sizeof(node));
	sprintf(tmp->data , "segment .bss\n");
	hcode=tmp;
	tcode=tmp;
	for(int i=0;i<26;i++){
		node *tmp = (node*)malloc(sizeof(node));
		sprintf(tmp->data,"reg%d\tresb\t8\n",i);
		tcode -> next = tmp;
		tcode = tcode->next;
	}
	node *tmpl = (node*)malloc(sizeof(node));
	sprintf(tmpl->data,"decstr\tresb\t10\nct1\tresd\t1\n\nsection .text\n\nglobal _start\n\n_start:\n");
	tcode -> next = tmpl;
	tcode = tcode->next;
	tcode->next = NULL;
	node *tmpdata = (node*)malloc(sizeof(node));
	sprintf(tmpdata->data,"section .data\n");
	hdata = tmpdata;
	tdata = tmpdata;
	tdata -> next = tmpdata;
	tdata = tdata->next;
	tdata->next = NULL;
	
}
void addString(char *string){
	node *tmp = (node*)malloc(sizeof(node));
	sprintf(tmp->data , "str%d db \"%s\"\n",strNUM,string);
	tmp->next = NULL;
	if(hdata == NULL){
		hdata = tmp;
		tdata = tmp;
	}
	else{
	tdata->next = tmp;
	tdata = tdata->next;
	}
}

int pop(){
	if(hstack==NULL)
		return 0;
	stack *tmp;
	int data;
	tmp = hstack;
	hstack = hstack->next;
	data = tmp->data;
	free(tmp);
	return data;
	
}
void print(){
	node *tmp = (node*)malloc(sizeof(node));
	sprintf(tmp->data , "\tmov\teax,1\n\tint\t0x80\n");
	tmp->next = NULL;
	tcode->next = tmp;
	tcode = tcode->next;
	FILE *fout=fopen("asm4.asm","w");
	node* run=hcode;
	if(checkfn[0] ==1)
		printDEC();
	if(checkfn[1] ==1)
		printHEX();
	if(checkfn[2] ==1)
		printString();
	if(checkfn[3] ==1)
		printLn();
	
	tcode->next = hdata;
	while(run){
		fprintf(fout,"%s",run->data);
		run = run->next;
	}
}

void movValtoReg(int value){
	node *tmp = (node*)malloc(sizeof(node));
	if(check==0){
		sprintf(tmp->data , "\tmov\teax,%d\n",value);
		//printf("\tmov\teax,%d\n",value);
		check =1;
	}
	else{
		sprintf(tmp->data , "\tpush\teax\n\tmov\teax,%d\n",value);
		//printf("\tpush\teax\n\tmov\teax,%d\n",value);
	}
	tmp->next = NULL;
	if(hcode == NULL){
		hcode = tmp;
		tcode = tmp;
	}
	else{
	tcode->next = tmp;
	tcode = tcode->next;
	}
	
}
void movVartoReg(int reg){
	node *tmp = (node*)malloc(sizeof(node));
	if(check==0){
		sprintf(tmp->data , "\tmov\teax,[reg%d]\n",reg);
		//printf("\tmov\teax,reg%d\n",reg);
		check =1;
	}
	else{
		sprintf(tmp->data , "\tpush\teax\n\tmov\teax,[reg%d]\n",reg);
		//printf("\tpush\teax\n\tmov\teax,reg%d\n",reg);
	}
	tmp->next = NULL;
	if(hcode == NULL){
		hcode = tmp;
		tcode = tmp;
	}
	else{
	tcode->next = tmp;
	tcode = tcode->next;
	}
}
void movRegtoVar(int reg){
	node *tmp = (node*)malloc(sizeof(node));
	sprintf(tmp->data , "\tmov\t[reg%d],eax\n",reg);
	//printf("\tmov\treg%d,eax\n",reg);
	tmp->next = NULL;
	if(hcode == NULL){
		hcode = tmp;
		tcode = tmp;
	}
	else{
	tcode->next = tmp;
	tcode = tcode->next;
	}
}


void add(){
	node *tmp = (node*)malloc(sizeof(node));
	sprintf(tmp->data , "\tmov\tebx,eax\n\tpop\teax\n\tadd\teax,ebx\n");	
	//printf("\tmov\tebx,eax\n\tpop\teax\n\tadd\teax,ebx\n");
	tmp->next = NULL;
	tcode->next = tmp;
	tcode = tcode->next;
}
void sub(){
	node *tmp = (node*)malloc(sizeof(node));
	sprintf(tmp->data , "\tmov\tebx,eax\n\tpop\teax\n\tsub\teax,ebx\n");	
	//printf("\tmov\tebx,eax\n\tpop\teax\n\tsub\teax,ebx\n");
	tmp->next = NULL;
	tcode->next = tmp;
	tcode = tcode->next;
}
void mul(){
	node *tmp = (node*)malloc(sizeof(node));
	sprintf(tmp->data , "\tmov\tebx,eax\n\tpop\teax\n\timul\tebx\n");	
	//printf("\tmov\tebx,eax\n\tpop\teax\n\tmul\tebx\n");
	tmp->next = NULL;
	tcode->next = tmp;
	tcode = tcode->next;
}
void idiv(){
	node *tmp = (node*)malloc(sizeof(node));
	sprintf(tmp->data , "\tmov\tebx,eax\n\tpop\teax\n\tidiv\tebx\n");	
	//printf("\tmov\tebx,eax\n\tpop\teax\n\tidiv\tebx\n");
	tmp->next = NULL;
	tcode->next = tmp;
	tcode = tcode->next;
}
void mod(){
	node *tmp = (node*)malloc(sizeof(node));
	sprintf(tmp->data , "\tmov\tebx,eax\n\tpop\teax\n\tidiv\tebx\n\tmov\teax,edx\n");	
	//printf("\tmov\tebx,eax\n\tpop\teax\n\tidiv\tebx\n\tmov\teax,edx\n");
	tmp->next = NULL;
	tcode->next = tmp;
	tcode = tcode->next;
}
void neg(){
node *tmp = (node*)malloc(sizeof(node));
	sprintf(tmp->data , "\tneg\teax\n");	
	//printf("\tmov\tebx,eax\n\tpop\teax\n\tidiv\tebx\n\tmov\teax,edx\n");
	tmp->next = NULL;
	tcode->next = tmp;
	tcode = tcode->next;
}
void printDEC(){
node *tmp = (node*)malloc(sizeof(node));
	sprintf(tmp->data ,"_printDec:\n\tpushad\n\tmov\tdword[ct1],0\n\tmov\tedi,decstr\n\tadd\tedi,9\n\txor\tedx,edx\n\n\tpush\t0\n\tcmp\teax,0\n\tjge\twhileNotZeroD\n\tpop\tebx\n\tpush\t'-'\n\tneg\teax\nwhileNotZeroD:\n\tmov\tebx,10\n\tdiv\tebx\n\tadd\tedx,'0'\n\tmov\tbyte[edi],dl\n\tdec\tedi\n\tinc\tdword[ct1]\n\txor\tedx,edx\n\tcmp\teax,0\n\tjne\twhileNotZeroD\n\tpop\tedx\n\tcmp\tedx,0\n\tje\tskip\n\n\tmov\tbyte[edi],dl\n\tdec\tedi\n\tinc\tdword[ct1]\n\txor\tedx,edx\n\nskip:\n\tinc\tedi\n\tmov\tecx, edi\n\tmov\tedx,[ct1]\n\tmov\teax, 4\n\tmov\tebx, 1\n\tint\t0x80\n\n\tpopad\n\tret\n ");	
	//printf("\tmov\tebx,eax\n\tpop\teax\n\tidiv\tebx\n\tmov\teax,edx\n");
	tmp->next = NULL;
	if(hcode == NULL){
		hcode = tmp;
		tcode = tmp;
	}
	else{
		tcode->next = tmp;
		tcode = tcode->next;
	}
}

void printHEX(){
node *tmp = (node*)malloc(sizeof(node));
	sprintf(tmp->data ,"_printHex:\n\tpushad\n\tmov\tdword[ct1],0\n\tmov\tedi,decstr\n\tadd\tedi,9\n\txor\tedx,edx\n\tpush\t'0'\n\tpush\t'x'\n\nwhileNotZeroH:\n\tmov\tebx,16\n\tdiv\tebx\n\tcmp\tedx,9\n\tjg\ttoAscii\n\tadd\tedx,'0'\n\tjmp\tputStr\ntoAscii:\n\tadd\tedx,55\nputStr:\n\tmov\tbyte[edi],dl\n\tdec\tedi\n\tinc\tdword[ct1]\n\txor\tedx,edx\n\tcmp\teax,0\n\tjne\twhileNotZeroH\n\n\tpop\tedx\n\tmov\tbyte[edi],dl\n\tdec\tedi\n\tinc\tdword[ct1]\n\txor\tedx,edx\n\n\tpop\tedx\n\tmov\tbyte[edi],dl\n\tdec\tedi\n\tinc\tdword[ct1]\n\txor\tedx,edx\n\n\tinc\tedi\n\tmov\tecx, edi\n\tmov\tedx,[ct1]\n\tmov\teax, 4\n\tmov\tebx, 1\n\tint\t0x80\n\n\tpopad\n\tret\n ");	
	//printf("\tmov\tebx,eax\n\tpop\teax\n\tidiv\tebx\n\tmov\teax,edx\n");
	tmp->next = NULL;
	if(hcode == NULL){
		hcode = tmp;
		tcode = tmp;
	}
	else{
		tcode->next = tmp;
		tcode = tcode->next;
	}
	labelNUM++;
}

void printLn(){
	node *tmpdata = (node*)malloc(sizeof(node));
	sprintf(tmpdata->data,"nl\tdb\t10\n");
	node *tmp = (node*)malloc(sizeof(node));
	tdata -> next = tmpdata;
	tdata = tdata->next;
	tdata->next = NULL;
	sprintf(tmp->data ,"_printLn:\n\tpush\tecx\n\tpush\tedx\n\n\tmov\tecx, nl\n\tmov\tedx, 1\n\tcall\t_printString\n\n\tpop\tedx\n\tpop\tecx\n\tret\n");	
	//printf("\tmov\tebx,eax\n\tpop\teax\n\tidiv\tebx\n\tmov\teax,edx\n");
	tmp->next = NULL;
	if(hcode == NULL){
		hcode = tmp;
		tcode = tmp;
	}
	else{
		tcode->next = tmp;
		tcode = tcode->next;
	}
}

void printString(char *string){
	node *tmp = (node*)malloc(sizeof(node));
	sprintf(tmp->data ,"_printString:\n\tpush\teax\n\tpush\tebx\n\n\tmov\teax,4\n\tmov\tebx,1\n\tint\t0x80\n\n\tpop\tebx\n\tpop\teax\n\tret\n");	
	//printf("\tmov\tebx,eax\n\tpop\teax\n\tidiv\tebx\n\tmov\teax,edx\n");
	tmp->next = NULL;
	if(hcode == NULL){
		hcode = tmp;
		tcode = tmp;
	}
	else{
		tcode->next = tmp;
		tcode = tcode->next;
	}
}

void conif(int first,int sec){
	node *tmp = (node*)malloc(sizeof(node));
	sprintf(tmp->data ,"\tmov\tebx,eax\n\tpop\teax\n\tcmp\teax,ebx\n\tjne\tlabel%d\n\n",labelNUM);	
	//printf("\tmov\tebx,eax\n\tpop\teax\n\tcmp\teax,ebx\n\tjne\teax,edx\n");
	tmp->next = NULL;
	if(hcode == NULL){
		hcode = tmp;
		tcode = tmp;
	}
	else{
		tcode->next = tmp;
		tcode = tcode->next;
	}
	
}

void conelse(){
	node *tmp = (node*)malloc(sizeof(node));
	sprintf(tmp->data , "\tjmp\tlabel%d\n\nlabel%d:\n",labelNUM,pop(labelNUM));
	//printf("\tmov\tr%d,eax\n",reg);
	tmp->next = NULL;
	if(hcode == NULL){
		hcode = tmp;
		tcode = tmp;
	}
	else{
		tcode->next = tmp;
		tcode = tcode->next;
	}
}
void loop(){
	push(labelNUM);
	node *tmp = (node*)malloc(sizeof(node));
	sprintf(tmp->data ,"\tmov\tebx,eax\n\tpop\teax\n\tcmp\teax,ebx\n\tjg\tlabel%d\n\n\tsub\tebx,eax\n\tmov\tecx,ebx\n\tinc\tecx\nlabel%d:\n\tpush\tecx\n",labelNUM,labelNUM+1);
	labelNUM++;
	push(labelNUM);
	//printf("\tmov\tr%d,eax\n",reg);
	tmp->next = NULL;
	if(hcode == NULL){
		hcode = tmp;
		tcode = tmp;
	}
	else{
		tcode->next = tmp;
		tcode = tcode->next;
	}
}
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

%type<intValue> NUM exp REG  
%type<stringValue> STRING print println //if stmt line


%% /* The grammar follows.  */

input:
  %empty
| input line { check=0;}
;

line: /* map stack operation or expression*/
  '\n'
| assign ';'					{ check=0; }
| print ';'						{ check=0; }
| println ';'					{ check=0; }
| if									{ check=0;
												node *tmp = (node*)malloc(sizeof(node));
												sprintf(tmp->data , "\nlabel%d:\n",pop());
												//printf("\tmov\tr%d,eax\n",reg);
												tmp->next = NULL;
												if(hcode == NULL){
													hcode = tmp;
													tcode = tmp;
												}
												else{
													tcode->next = tmp;
													tcode = tcode->next;
												} 
											}
| loop								{ check=0;
												node *tmp = (node*)malloc(sizeof(node));
												int pop1=pop();
												int pop2=pop();
												sprintf(tmp->data , "\tpop\tecx\n\tloop\tlabel%d\nlabel%d:\n",pop1,pop2);
												//printf("\tmov\tr%d,eax\n",reg);
												tmp->next = NULL;
												if(hcode == NULL){
													hcode = tmp;
													tcode = tmp;
												}
												else{
													tcode->next = tmp;
													tcode = tcode->next;
												} 
											}
;


exp: /* expressions */
  NUM 								{ movValtoReg($1);
  											$$ = $1;
  										}
| REG									{ movVartoReg($1-48);
												$$ = var[$1]; }
| exp '+' exp        	{ add();
											}
| exp '-' exp        	{ sub(); 
											}
| exp '*' exp        	{ mul(); 
											}
| exp '/' exp        	{ if($3==0) {
													error(2);  		/*check if divide by 0 */
													checkerr =1;			
			  								}			  
			  								else{
													idiv();
												}
											}
| exp '%' exp       	{ if($3==0) { 			/*check if modulo by 0 */
													error(3); 
													checkerr =1;			
												}			  
												else
													mod();
											}
											
| '-' exp  %prec NEG 	{ neg();
												 }
| '(' exp ')'        	{ $$ = $2; }
;


assign: /*assign value to register*/
  REG '=' exp					{ movRegtoVar($1-48);
  											var[$1] = $3; }
;

print: /*print*/
  PRINT '(' exp ','  DEC ')'						{ node *tmp = (node*)malloc(sizeof(node));
																					sprintf(tmp->data , "\tcall\t _printDec\n");
																					//printf("\tmov\tr%d,eax\n",reg);
																					tmp->next = NULL;
																					if(hcode == NULL){
																						hcode = tmp;
																						tcode = tmp;
																					}
																					else{
																						tcode->next = tmp;
																						tcode = tcode->next;
																					}
																					checkfn[0] =1;
																				}
| PRINT '(' exp ','  HEX ')' 						{ node *tmp = (node*)malloc(sizeof(node));
																					sprintf(tmp->data , "\tcall\t _printHex\n");
																					//printf("\tmov\tr%d,eax\n",reg);
																					tmp->next = NULL;
																					if(hcode == NULL){
																						hcode = tmp;
																						tcode = tmp;
																					}
																					else{
																						tcode->next = tmp;
																						tcode = tcode->next;
																					}
																					checkfn[1] =1;
																			  }
| PRINT '('  STRING ')' 								{ node *tmp1 = (node*)malloc(sizeof(node));
																					sprintf(tmp1->data ,"\tmov\tecx,str%d\n\tmov\tedx,%d\n\tcall\t_printString\n",strNUM,strlen($3));
																					tmp1->next = NULL;
																					if(hcode == NULL){
																						hcode = tmp1;
																						tcode = tmp1;
																					}
																					else{
																						tcode->next = tmp1;
																						tcode = tcode->next;
																					}
																					
																					node *tmp = (node*)malloc(sizeof(node));
																					sprintf(tmp->data ,"str%d\tdb\t\"%s\"\n",strNUM,$3);
																					tmp->next = NULL;
																					if(hdata == NULL){
																						hdata = tmp;
																						tdata = tmp;
																					}
																					else{
																						tdata->next = tmp;
																						tdata = tdata->next;
																					}
																					strNUM++;
																					checkfn[2] =1;
																				}

;

println: /*print line*/
  PRINTLN '(' exp ','  DEC ')' 				 { node *tmp = (node*)malloc(sizeof(node));
																					sprintf(tmp->data , "\tcall\t _printDec\n\tcall\t _printLn\n");
																					//printf("\tmov\treg%d,eax\n",reg);
																					tmp->next = NULL;
																					if(hcode == NULL){
																						hcode = tmp;
																						tcode = tmp;
																					}
																					else{
																						tcode->next = tmp;
																						tcode = tcode->next;
																					}
																					checkfn[0] =1;
																					checkfn[2] =1;
																					checkfn[3] =1;
																			 }
| PRINTLN '(' exp ','  HEX ')' 				{ node *tmp = (node*)malloc(sizeof(node));
																					sprintf(tmp->data , "\tcall\t _printHex\n\tcall\t _printLn\n");
																					//printf("\tmov\treg%d,eax\n",reg);
																					tmp->next = NULL;
																					if(hcode == NULL){
																						hcode = tmp;
																						tcode = tmp;
																					}
																					else{
																						tcode->next = tmp;
																						tcode = tcode->next;
																					}
																					checkfn[1] =1;
																					checkfn[3] =1;
																					
																		  }
| PRINTLN '('  STRING ')' 						{ node *tmp1 = (node*)malloc(sizeof(node));
																					sprintf(tmp1->data ,"\tmov\tecx,str%d\n\tmov\tedx,%d\n\tcall\t_printString\n\tcall\t _printLn\n",strNUM,strlen($3));
																					tmp1->next = NULL;
																					if(hcode == NULL){
																						hcode = tmp1;
																						tcode = tmp1;
																					}
																					else{
																						tcode->next = tmp1;
																						tcode = tcode->next;
																					}
																					
																					node *tmp = (node*)malloc(sizeof(node));
																					sprintf(tmp->data ,"str%d\tdb\t\"%s\"\n",strNUM,$3);
																					tmp->next = NULL;
																					if(hdata == NULL){
																						hdata = tmp;
																						tdata = tmp;
																					}
																					else{
																						tdata->next = tmp;
																						tdata = tdata->next;
																					}
																					strNUM++;
																					checkfn[2] =1;
																					checkfn[3] =1; }
;

if: 
  IF if_compare '{' stmt '}' else 				{ }
;
if_compare:
 '(' exp ',' exp ')' 											{	check=0;
 																						conif($2,$4);
																						push(labelNUM);	
																						labelNUM++;}
 ;
else:
	%empty															{}
| else_compare '{' stmt '}'					{ }
;
else_compare:
ELSE												{ check=0;
															conelse();
													 		push(labelNUM);	
  														labelNUM++; }
;


stmt: 
	%empty
| stmt line {  }
;

loop:
  LOOP loop_compare '{' stmt '}'  {  }
;
loop_compare:
 '(' exp ',' exp ')' {			check=0;
 														loop();
  													
  													labelNUM++;
  										}
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

int main(int argc,char** argv){
	
	if(argc>1){
		FILE *fp=fopen(argv[1],"r");
		if(!fp){
			printf("file not found\n");
			exit(1);
		}
		yyin = fp;
	}
	else{
		printf("No input file");
		exit(1);
	}
	
	init();
	yyparse();
	print();
	
	return 0;
}

