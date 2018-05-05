/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 3 "asm4.y" /* yacc.c:339  */

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
  extern int yylineno;
  extern char  yytext[80];
  
  int yyparse(void);
  void yyerror (char *);
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
	sprintf(tmp->data , "\txor\tedx,edx\n\tmov\tebx,eax\n\tpop\teax\n\tidiv\tebx\n");	
	//printf("\tmov\tebx,eax\n\tpop\teax\n\tidiv\tebx\n");
	tmp->next = NULL;
	tcode->next = tmp;
	tcode = tcode->next;
}
void mod(){
	node *tmp = (node*)malloc(sizeof(node));
	sprintf(tmp->data , "\txor\tedx,edx\n\tmov\tebx,eax\n\tpop\teax\n\tidiv\tebx\n\tmov\teax,edx\n");	
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

#line 407 "asm4.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "asm4.tab.h".  */
#ifndef YY_YY_ASM4_TAB_H_INCLUDED
# define YY_YY_ASM4_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUM = 258,
    REG = 259,
    UNK = 260,
    PRINT = 261,
    PRINTLN = 262,
    IF = 263,
    LOOP = 264,
    STRING = 265,
    DEC = 266,
    HEX = 267,
    ELSE = 268,
    NEG = 269
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 347 "asm4.y" /* yacc.c:355  */

    int intValue;
    char *stringValue;

#line 467 "asm4.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_ASM4_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 484 "asm4.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   447

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  28
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  140

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   269

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      20,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    18,     2,     2,
      22,    23,    16,    15,    25,    14,     2,    17,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    21,
       2,    24,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    27,     2,    26,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    19
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   364,   364,   365,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   392,   413,   415,   417,   418,   419,   420,
     421,   422,   423,   424,   425,   426,   427,   428,   429,   437,
     438,   439,   446,   449,   451,   452,   457,   459,   460,   464,
     465,   466,   467,   468,   469,   470,   487,   502,   530,   531,
     532,   533,   534,   535,   536,   551,   552,   553,   554,   555,
     570,   571,   572,   600,   601,   602,   604,   608,   609,   610,
     611,   612,   618,   619,   620,   621,   625,   632,   633,   637,
     638,   639,   643,   649,   650
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "REG", "UNK", "PRINT", "PRINTLN",
  "IF", "LOOP", "STRING", "DEC", "HEX", "ELSE", "'-'", "'+'", "'*'", "'/'",
  "'%'", "NEG", "'\\n'", "';'", "'('", "')'", "'='", "','", "'}'", "'{'",
  "$accept", "input", "line", "exp", "assign", "print", "println", "if",
  "if_compare", "else", "else_compare", "stmt", "loop", "loop_compare", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,    45,    43,    42,    47,    37,   269,
      10,    59,    40,    41,    61,    44,   125,   123
};
# endif

#define YYPACT_NINF -95

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-95)))

#define YYTABLE_NINF -35

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -95,    34,   -95,   -22,   240,   249,   -15,   -12,   -95,   -95,
     265,   -95,    -9,    -5,     9,   -95,   -95,   265,   -95,   -95,
     -95,   265,   265,   265,   265,   265,    49,   323,    10,    89,
     335,   105,    12,   121,    30,   265,   371,   -95,   -95,   -95,
     371,   301,   424,    28,    28,    28,    38,   -95,    13,   311,
     274,   274,     1,     1,     1,   -95,    51,   -95,   283,   -95,
      -3,   298,    24,   -95,    65,   347,   -95,   149,   -95,    47,
     359,   -95,   170,   381,   -95,    50,    53,   -95,     3,   424,
     424,    28,    28,    28,    54,   -95,    55,    61,    62,    63,
      33,    66,    71,   -95,   391,   224,   141,    82,   -95,   -95,
     265,   177,   -95,   -95,   -95,    74,    75,   -95,   -95,   -95,
     -95,   -95,   -95,    78,    79,   -95,   -95,   -95,   401,   -95,
     411,   -95,    82,   -95,    83,   -95,   421,   -95,   -95,   -95,
     -95,   -95,   401,   -95,   -95,   198,   401,   205,   -95,   -95
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,    66,     0,     4,     5,
       0,     3,     6,     8,    10,    12,    13,    37,    14,    15,
      16,     0,     0,     0,     0,     0,     0,     0,    16,     0,
       0,     0,    77,     0,    77,     0,    38,     7,     9,    11,
      36,    21,    18,    24,    27,    30,    16,    39,     0,     0,
      20,    17,    23,    26,    29,    34,     0,    60,    61,    48,
       0,     0,     0,    70,     0,     0,    77,     0,    84,     0,
       0,    77,     0,    35,    47,     0,     0,    33,     0,    22,
      19,    25,    28,    31,     0,    62,     0,     0,     0,     0,
       0,     0,     0,    69,     0,     0,    72,    72,    78,    83,
       0,    80,    79,    43,    41,    42,     0,    44,    40,    52,
      58,    50,    56,    51,    57,    53,    49,    55,    67,    68,
       0,    76,    72,    64,    77,    63,     0,    81,    45,    46,
      54,    59,    71,    65,    77,     0,    82,    74,    73,    75
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -95,   -95,   112,    -4,   -95,   -95,   -95,   -95,   -95,   -94,
     -95,   -34,   -95,   -95
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    98,    27,    12,    13,    14,    15,    32,   123,
     124,    67,    16,    34
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      72,    30,    17,   125,    18,    19,    36,    31,    86,    87,
      33,    20,    37,    40,   105,   106,    38,    41,    42,    43,
      44,    45,    49,    35,    75,    61,   107,    65,   133,    70,
      39,    73,    96,    57,     2,    91,    92,   101,     3,    66,
       4,     5,     6,     7,   113,   114,    79,    80,    81,    82,
      83,    55,    18,    19,     8,     9,   115,    71,    10,    46,
      94,    74,    84,    21,    22,    23,    24,    25,    18,    19,
      99,    35,    47,   103,    48,    20,   104,   108,   109,    21,
      22,    23,    24,    25,   110,   111,   112,    35,    93,   116,
     135,   120,    18,    19,   117,   121,   126,   128,   129,    58,
     137,   130,   131,    21,    22,    23,    24,    25,    18,    19,
     134,    35,    59,    11,    60,    20,     0,     0,     0,    21,
      22,    23,    24,    25,    18,    19,     0,    35,    63,     0,
      64,    20,     0,     0,     0,    21,    22,    23,    24,    25,
       0,     0,     0,    35,    68,     3,    69,     4,     5,     6,
       7,     0,     0,     3,   121,     4,     5,     6,     7,     0,
       0,     8,     9,     0,     0,    10,     0,   122,     0,     8,
       9,     0,     0,    10,     3,    97,     4,     5,     6,     7,
       0,     3,     0,     4,     5,     6,     7,     0,     0,     0,
       8,     9,     0,     0,    10,     0,   102,     8,     9,     0,
       0,    10,     3,   127,     4,     5,     6,     7,     0,     3,
       0,     4,     5,     6,     7,     0,     0,     0,     8,     9,
       0,     0,    10,     0,   138,     8,     9,    18,    19,    10,
       0,   139,     0,     0,    20,     0,     0,     0,    21,    22,
      23,    24,    25,    18,    19,     0,    35,   119,     0,     0,
      20,     0,    18,    19,    21,    22,    23,    24,    25,    28,
       0,     0,    26,    21,    22,    23,    24,    25,    18,    19,
       0,    29,     0,     0,     0,    20,     0,    18,    19,    21,
      22,    23,    24,    25,    20,     0,     0,    35,     0,     0,
      23,    24,    25,     0,   -16,   -16,    35,   -16,   -16,   -16,
     -16,   -16,     0,     0,     0,     0,    85,     0,   -16,    88,
      89,     0,    50,    51,    52,    53,    54,   -32,   -32,   -32,
       0,    77,    76,    90,    55,    50,    51,    52,    53,    54,
       0,     0,     0,     0,    77,     0,    78,    50,    51,    52,
      53,    54,     0,     0,     0,     0,    55,     0,    56,    50,
      51,    52,    53,    54,     0,     0,     0,     0,    55,     0,
      62,    50,    51,    52,    53,    54,     0,     0,     0,     0,
      55,     0,    95,    50,    51,    52,    53,    54,     0,     0,
       0,     0,    55,     0,   100,    50,    51,    52,    53,    54,
       0,     0,     0,     0,    55,    50,    51,    52,    53,    54,
       0,     0,     0,     0,    77,    50,    51,    52,    53,    54,
       0,     0,     0,     0,   118,   -34,   -34,   -34,   -34,   -34,
       0,     0,     0,     0,   -34,    50,    51,    52,    53,    54,
       0,     0,     0,     0,   132,    50,    51,    52,    53,    54,
      52,    53,    54,     0,   136,     0,     0,    55
};

static const yytype_int16 yycheck[] =
{
      34,     5,    24,    97,     3,     4,    10,    22,    11,    12,
      22,    10,    21,    17,    11,    12,    21,    21,    22,    23,
      24,    25,    26,    22,    11,    29,    23,    31,   122,    33,
      21,    35,    66,    23,     0,    11,    12,    71,     4,    27,
       6,     7,     8,     9,    11,    12,    50,    51,    52,    53,
      54,    23,     3,     4,    20,    21,    23,    27,    24,    10,
      64,    23,    11,    14,    15,    16,    17,    18,     3,     4,
      23,    22,    23,    23,    25,    10,    23,    23,    23,    14,
      15,    16,    17,    18,    23,    23,    23,    22,    23,    23,
     124,    95,     3,     4,    23,    13,   100,    23,    23,    10,
     134,    23,    23,    14,    15,    16,    17,    18,     3,     4,
      27,    22,    23,     1,    25,    10,    -1,    -1,    -1,    14,
      15,    16,    17,    18,     3,     4,    -1,    22,    23,    -1,
      25,    10,    -1,    -1,    -1,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    22,    23,     4,    25,     6,     7,     8,
       9,    -1,    -1,     4,    13,     6,     7,     8,     9,    -1,
      -1,    20,    21,    -1,    -1,    24,    -1,    26,    -1,    20,
      21,    -1,    -1,    24,     4,    26,     6,     7,     8,     9,
      -1,     4,    -1,     6,     7,     8,     9,    -1,    -1,    -1,
      20,    21,    -1,    -1,    24,    -1,    26,    20,    21,    -1,
      -1,    24,     4,    26,     6,     7,     8,     9,    -1,     4,
      -1,     6,     7,     8,     9,    -1,    -1,    -1,    20,    21,
      -1,    -1,    24,    -1,    26,    20,    21,     3,     4,    24,
      -1,    26,    -1,    -1,    10,    -1,    -1,    -1,    14,    15,
      16,    17,    18,     3,     4,    -1,    22,    23,    -1,    -1,
      10,    -1,     3,     4,    14,    15,    16,    17,    18,    10,
      -1,    -1,    22,    14,    15,    16,    17,    18,     3,     4,
      -1,    22,    -1,    -1,    -1,    10,    -1,     3,     4,    14,
      15,    16,    17,    18,    10,    -1,    -1,    22,    -1,    -1,
      16,    17,    18,    -1,    11,    12,    22,    14,    15,    16,
      17,    18,    -1,    -1,    -1,    -1,    23,    -1,    25,    11,
      12,    -1,    14,    15,    16,    17,    18,    16,    17,    18,
      -1,    23,    11,    25,    23,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    -1,    23,    -1,    25,    14,    15,    16,
      17,    18,    -1,    -1,    -1,    -1,    23,    -1,    25,    14,
      15,    16,    17,    18,    -1,    -1,    -1,    -1,    23,    -1,
      25,    14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,
      23,    -1,    25,    14,    15,    16,    17,    18,    -1,    -1,
      -1,    -1,    23,    -1,    25,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    -1,    23,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    -1,    23,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    -1,    23,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    -1,    23,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    -1,    23,    14,    15,    16,    17,    18,
      16,    17,    18,    -1,    23,    -1,    -1,    23
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    29,     0,     4,     6,     7,     8,     9,    20,    21,
      24,    30,    32,    33,    34,    35,    40,    24,     3,     4,
      10,    14,    15,    16,    17,    18,    22,    31,    10,    22,
      31,    22,    36,    22,    41,    22,    31,    21,    21,    21,
      31,    31,    31,    31,    31,    31,    10,    23,    25,    31,
      14,    15,    16,    17,    18,    23,    25,    23,    10,    23,
      25,    31,    25,    23,    25,    31,    27,    39,    23,    25,
      31,    27,    39,    31,    23,    11,    11,    23,    25,    31,
      31,    31,    31,    31,    11,    23,    11,    12,    11,    12,
      25,    11,    12,    23,    31,    25,    39,    26,    30,    23,
      25,    39,    26,    23,    23,    11,    12,    23,    23,    23,
      23,    23,    23,    11,    12,    23,    23,    23,    23,    23,
      31,    13,    26,    37,    38,    37,    31,    26,    23,    23,
      23,    23,    23,    37,    27,    39,    23,    39,    26,    26
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    28,    29,    29,    30,    30,    30,    30,    30,    30,
      30,    30,    30,    30,    31,    31,    31,    31,    31,    31,
      31,    31,    31,    31,    31,    31,    31,    31,    31,    31,
      31,    31,    31,    31,    31,    31,    32,    32,    32,    33,
      33,    33,    33,    33,    33,    33,    33,    33,    34,    34,
      34,    34,    34,    34,    34,    34,    34,    34,    34,    34,
      34,    34,    34,    35,    35,    35,    36,    36,    36,    36,
      36,    36,    37,    37,    37,    37,    38,    39,    39,    40,
      40,    40,    41,    41,    41
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     2,     1,     2,
       1,     2,     1,     1,     1,     1,     1,     2,     2,     3,
       2,     2,     3,     2,     2,     3,     2,     2,     3,     2,
       2,     3,     2,     3,     2,     2,     3,     2,     2,     3,
       5,     5,     5,     5,     5,     6,     6,     4,     3,     5,
       5,     5,     5,     5,     6,     5,     5,     5,     5,     6,
       3,     3,     4,     5,     5,     6,     0,     4,     4,     3,
       2,     5,     0,     3,     3,     4,     1,     0,     2,     4,
       4,     5,     5,     3,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 365 "asm4.y" /* yacc.c:1646  */
    { check=0;}
#line 1708 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 372 "asm4.y" /* yacc.c:1646  */
    { yyerror("MISSING ';'");}
#line 1714 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 373 "asm4.y" /* yacc.c:1646  */
    { check=0; }
#line 1720 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 374 "asm4.y" /* yacc.c:1646  */
    { yyerror("MISSING ';'");}
#line 1726 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 375 "asm4.y" /* yacc.c:1646  */
    { check=0; }
#line 1732 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 376 "asm4.y" /* yacc.c:1646  */
    { yyerror("MISSING ';'");}
#line 1738 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 377 "asm4.y" /* yacc.c:1646  */
    { check=0; }
#line 1744 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 378 "asm4.y" /* yacc.c:1646  */
    { check=0;
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
#line 1763 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 392 "asm4.y" /* yacc.c:1646  */
    { check=0;
		node *tmp = (node*)malloc(sizeof(node));
		int pop1=pop();
		int pop2=pop();
		sprintf(tmp->data , "\tpop\tecx\n\tdec\tecx\n\tjnz\tlabel%d\nlabel%d:\n",pop1,pop2);
		//sprintf(tmp->data , "\tpop\tecx\n\tloop\tlabel%d\nlabel%d:\n",pop1,pop2);
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
#line 1785 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 413 "asm4.y" /* yacc.c:1646  */
    { movValtoReg((yyvsp[0].intValue));
  		          (yyval.intValue) = (yyvsp[0].intValue);}
#line 1792 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 415 "asm4.y" /* yacc.c:1646  */
    { movVartoReg((yyvsp[0].intValue));
			  (yyval.intValue) = var[(yyvsp[0].intValue)]; }
#line 1799 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 417 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED NUM OR REG");}
#line 1805 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 418 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED EXP + EXP");}
#line 1811 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 419 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED EXP + EXP");}
#line 1817 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 420 "asm4.y" /* yacc.c:1646  */
    { add(); }
#line 1823 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 421 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED EXP - EXP");}
#line 1829 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 422 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED EXP - EXP");}
#line 1835 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 423 "asm4.y" /* yacc.c:1646  */
    { sub(); }
#line 1841 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 424 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED EXP * EXP");}
#line 1847 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 425 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED EXP * EXP");}
#line 1853 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 426 "asm4.y" /* yacc.c:1646  */
    { mul(); }
#line 1859 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 427 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED EXP / EXP");}
#line 1865 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 428 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED EXP / EXP");}
#line 1871 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 429 "asm4.y" /* yacc.c:1646  */
    { if((yyvsp[0].intValue)==0) {				/*check if divide by 0 */
				yyerror("DIVIDED BY ZERO");  		
				checkerr =1;			
			  }			  
			  else{
			  	idiv();
			 }
			}
#line 1884 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 437 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED EXP %% EXP");}
#line 1890 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 438 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED EXP %% EXP");}
#line 1896 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 439 "asm4.y" /* yacc.c:1646  */
    { if((yyvsp[0].intValue)==0) { 				/*check if modulo by 0 */
				yyerror("MODULO BY ZERO");  
				checkerr =1;			
			  }else
				mod();
			}
#line 1907 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 446 "asm4.y" /* yacc.c:1646  */
    { neg();
			}
#line 1914 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 449 "asm4.y" /* yacc.c:1646  */
    { (yyval.intValue) = (yyvsp[-1].intValue); }
#line 1920 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 451 "asm4.y" /* yacc.c:1646  */
    { yyerror("MISSING '('"); }
#line 1926 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 452 "asm4.y" /* yacc.c:1646  */
    { yyerror("MISSING ')'"); }
#line 1932 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 457 "asm4.y" /* yacc.c:1646  */
    { movRegtoVar((yyvsp[-2].intValue));
  			  var[(yyvsp[-2].intValue)] = (yyvsp[0].intValue); }
#line 1939 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 459 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED REG = EXP"); }
#line 1945 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 460 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED REG = EXP"); }
#line 1951 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 464 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED PRINT(EXP)"); }
#line 1957 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 465 "asm4.y" /* yacc.c:1646  */
    { yyerror("MISSING '('"); }
#line 1963 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 466 "asm4.y" /* yacc.c:1646  */
    { yyerror("MISSING ','"); }
#line 1969 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 467 "asm4.y" /* yacc.c:1646  */
    { yyerror("MISSING ')'"); }
#line 1975 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 468 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED PRINT(EXP, DEC)"); }
#line 1981 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 469 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED PRINT(EXP, [DEC/HEX])"); }
#line 1987 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 470 "asm4.y" /* yacc.c:1646  */
    { node *tmp = (node*)malloc(sizeof(node));
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
				checkfn[0] =1; }
#line 2005 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 487 "asm4.y" /* yacc.c:1646  */
    { node *tmp = (node*)malloc(sizeof(node));
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
				checkfn[1] =1; }
#line 2023 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 502 "asm4.y" /* yacc.c:1646  */
    { node *tmp1 = (node*)malloc(sizeof(node));
				sprintf(tmp1->data ,"\tmov\tecx,str%d\n\tmov\tedx,%d\n\tcall\t_printString\n",strNUM,strlen((yyvsp[-1].stringValue)));
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
				sprintf(tmp->data ,"str%d\tdb\t\"%s\"\n",strNUM,(yyvsp[-1].stringValue));
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
#line 2053 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 530 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED PRINTLN(EXP)"); }
#line 2059 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 531 "asm4.y" /* yacc.c:1646  */
    { yyerror("MISSING '('"); }
#line 2065 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 532 "asm4.y" /* yacc.c:1646  */
    { yyerror("MISSING ','"); }
#line 2071 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 533 "asm4.y" /* yacc.c:1646  */
    { yyerror("MISSING ')'"); }
#line 2077 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 534 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED PRINTLN(EXP, DEC)"); }
#line 2083 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 535 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED PRINTLN(EXP, [DEC/HEX])"); }
#line 2089 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 536 "asm4.y" /* yacc.c:1646  */
    { node *tmp = (node*)malloc(sizeof(node));
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
				checkfn[3] =1; }
#line 2109 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 551 "asm4.y" /* yacc.c:1646  */
    { yyerror("MISSING '('"); }
#line 2115 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 552 "asm4.y" /* yacc.c:1646  */
    { yyerror("MISSING ','"); }
#line 2121 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 553 "asm4.y" /* yacc.c:1646  */
    { yyerror("MISSING ')'"); }
#line 2127 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 554 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED PRINTLN(EXP, HEX)"); }
#line 2133 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 555 "asm4.y" /* yacc.c:1646  */
    { node *tmp = (node*)malloc(sizeof(node));
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
				checkfn[1] =1;
				checkfn[2] =1;
				checkfn[3] =1; }
#line 2153 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 570 "asm4.y" /* yacc.c:1646  */
    { yyerror("MISSING '('"); }
#line 2159 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 571 "asm4.y" /* yacc.c:1646  */
    { yyerror("MISSING ')'"); }
#line 2165 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 572 "asm4.y" /* yacc.c:1646  */
    { node *tmp1 = (node*)malloc(sizeof(node));
				sprintf(tmp1->data ,"\tmov\tecx,str%d\n\tmov\tedx,%d\n\tcall\t_printString\n\tcall\t _printLn\n",strNUM,strlen((yyvsp[-1].stringValue)));
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
				sprintf(tmp->data ,"str%d\tdb\t\"%s\"\n",strNUM,(yyvsp[-1].stringValue));
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
#line 2195 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 600 "asm4.y" /* yacc.c:1646  */
    { yyerror("MISSING '{'"); }
#line 2201 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 601 "asm4.y" /* yacc.c:1646  */
    { yyerror("MISSING '}'"); }
#line 2207 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 602 "asm4.y" /* yacc.c:1646  */
    { }
#line 2213 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 608 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED IF(EXP, EXP)"); }
#line 2219 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 609 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED IF(EXP, EXP)"); }
#line 2225 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 610 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED IF(EXP, EXP)"); }
#line 2231 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 611 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED IF(EXP, EXP)"); }
#line 2237 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 612 "asm4.y" /* yacc.c:1646  */
    { check=0;
				 conif((yyvsp[-3].intValue),(yyvsp[-1].intValue));
				 push(labelNUM);
				 labelNUM++; }
#line 2246 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 618 "asm4.y" /* yacc.c:1646  */
    { }
#line 2252 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 619 "asm4.y" /* yacc.c:1646  */
    { yyerror("MISSING '{'"); }
#line 2258 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 620 "asm4.y" /* yacc.c:1646  */
    { yyerror("MISSING '}'"); }
#line 2264 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 621 "asm4.y" /* yacc.c:1646  */
    { }
#line 2270 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 625 "asm4.y" /* yacc.c:1646  */
    { check=0;
				conelse();
		 		push(labelNUM);	
				labelNUM++; }
#line 2279 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 633 "asm4.y" /* yacc.c:1646  */
    {  }
#line 2285 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 637 "asm4.y" /* yacc.c:1646  */
    { yyerror("MISSING '{'"); }
#line 2291 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 638 "asm4.y" /* yacc.c:1646  */
    { yyerror("MISSING '}'"); }
#line 2297 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 639 "asm4.y" /* yacc.c:1646  */
    {  }
#line 2303 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 643 "asm4.y" /* yacc.c:1646  */
    { check=0;
			  	  loop();
			  	  labelNUM++; }
#line 2311 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 649 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED LOOP(EXP, EXP)"); }
#line 2317 "asm4.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 650 "asm4.y" /* yacc.c:1646  */
    { yyerror("EXPECTED LOOP(EXP, EXP)"); }
#line 2323 "asm4.tab.c" /* yacc.c:1646  */
    break;


#line 2327 "asm4.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 653 "asm4.y" /* yacc.c:1906  */


void yyerror(char *s) /* error checking */
{
	fprintf(stderr, "line : %d : %s\n", yylineno - 1, s);
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

