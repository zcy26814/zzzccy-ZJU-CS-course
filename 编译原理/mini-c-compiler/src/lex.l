%{
    #include<string.h>
    #include"ast.h"
    #include "grammar.hpp"
%}

%option yylineno

not "!"|"~"

if "if"
else "else"
while "while"
return "return"

type "int"|"float"|"char"|"boolean"

integer 0|[1-9][0-9]*
float {integer}\.[0-9]+
string \"(\\.|[^"\\])*\"
char \'.\'
bool "true"|"false"|"True"|"False"

a_c_op "+="|"-="|"*="|"/="|"%="

id [a-zA-Z_][a-zA-Z0-9_]*

relop ">"|"<"|">="|"<="|"=="|"!="
space [ \t]+
enter [\n]

commits \/\*([^\*]|(\*)*[^\*/])*(\*)*\*\/ 
commit  \/\/[^\n]*

else_sym .

%%
{not}       {yylval.node = new Node(yytext, "NOT", 0); return NOT;}
{type}      {yylval.node = new Node(yytext, "TYPE", 0); return TYPE;}

{char}      {yylval.node = new Node(yytext, "CHAR", 0); return CHAR;}
{bool}      {yylval.node = new Node(yytext, "BOOLEAN", 0); return BOOLEAN;}
{float}     {yylval.node = new Node(yytext, "FLOAT", 0); return FLOAT;}
{string}    {yylval.node = new Node(yytext, "STRING", 0); return STRING;}
{integer}   {yylval.node = new Node(yytext, "INTEGER", 0); return INTEGER; }

{if}        {yylval.node = new Node(yytext, "IF", 0); return IF;}
{else}      {yylval.node = new Node(yytext, "ELSE", 0); return ELSE;}
{while}     {yylval.node = new Node(yytext, "WHILE", 0); return WHILE;}
{return}    {yylval.node = new Node(yytext, "RETURN", 0); return RETURN;}

{id}        {yylval.node = new Node(yytext, "ID", 0); return ID;}

{relop}     {yylval.node = new Node(yytext, "RELOP", 0); return RELOP;}
{a_c_op}    {yylval.node = new Node(yytext, "ACOP", 0); return ACOP;}

{space}     {}
{enter}     {}
{commit}    {}
{commits}   {}

"=" {yylval.node = new Node(yytext, "ASSIGNOP", 0); return ASSIGNOP;}
"+" {yylval.node = new Node(yytext, "PLUS", 0); return PLUS;}
"-" {yylval.node = new Node(yytext, "MINUS", 0); return MINUS;}
"*" {yylval.node = new Node(yytext, "STAR", 0); return STAR;}
"/" {yylval.node = new Node(yytext, "DIV", 0); return DIV;}
"%" {yylval.node = new Node(yytext, "MODULO", 0); return MODULO;}

"||" {yylval.node = new Node(yytext, "OR", 0); return OR;}
"&&" {yylval.node = new Node(yytext, "AND", 0); return AND;}

";" {yylval.node = new Node(yytext, "SEMI", 0); return SEMI;}
"(" {yylval.node = new Node(yytext, "LBRACKET", 0); return LBRACKET;} //Left Bracket
")" {yylval.node = new Node(yytext, "RBRACKET", 0); return RBRACKET;}
"[" {yylval.node = new Node(yytext, "LSB", 0); return LSB;} //Left Square Bracket
"]" {yylval.node = new Node(yytext, "RSB", 0); return RSB;}
"," {yylval.node = new Node(yytext, "COMMA", 0); return COMMA;}
"{" {yylval.node = new Node(yytext, "LBRACE", 0); return LBRACE;} //Left Brace
"}" {yylval.node = new Node(yytext, "RBRACE", 0); return RBRACE;}

{else_sym}  {cout << "sym error" << endl;}

%%

int yywrap() {
    return 1;
}
