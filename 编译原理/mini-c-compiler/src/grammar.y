%{
    #include<stdio.h>
    #include"ast.h"
    #include"type.h"
    extern int yylineno;
    extern char* yytext;
    extern Node *ROOT;

    extern int yylex();

    void yyerror(const char* msg) {
        printf("Error: %s Line:%d String:%s\n", msg, yylineno, yytext);
    }
%}

%union{
    struct Node* node;
}

%token <node> INTEGER FLOAT CHAR STRING BOOLEAN RETURN
%token <node> LBRACKET RBRACKET LSB RSB LBRACE RBRACE
%token <node> TYPE ID COMMA WHILE IF ELSE SEMI
%token <node> ASSIGNOP ACOP
%token <node> RELOP 
%token <node> AND OR NOT
%token <node> PLUS MINUS
%token <node> STAR DIV MODULO


%left COMMA
%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV MODULO
%right NOT
%left LBRACKET RBRACKET LSB RSB


%type <node> program  declaration_funct_list  declaration_funct  declaration  funct
%type <node> var_declaration  var_list  var  
%type <node> funct_declaration  para_list  para
%type <node> comp_statement  statements  statement  ret_statement  expr_statement  loop_statement  select_statement
%type <node> arithmetic_statement  declaration_statement  assignment  funct_call
%type <node> elem  args

%%

program: 
    declaration_funct_list {
        $$ = new Node("", "program", 1, $1);
        ROOT = $$; 
    }
    ;

declaration_funct_list: 
    declaration_funct declaration_funct_list {
        $$ = new Node("", "declaration_funct_list", 2, $1, $2);
    }
    | {
        $$ = nullptr;
    }
    ;

declaration_funct: 
    declaration {
        $$ = new Node("", "declaration_funct", 1, $1);
    }
    | funct {
        $$ = new Node("", "declaration_funct", 1, $1);
    }
    ;

declaration: 
    var_declaration SEMI {
        $$ = new Node("", "declaration", 2, $1, $2);
    }
    | funct_declaration SEMI {
        $$ = new Node("", "declaration", 2, $1, $2);
    }
    ;

var_declaration: 
    TYPE var_list {
        $$ = new Node("", "var_declaration", 2, $1, $2);
    }
    ;

var_list: 
    var COMMA var_list {
        $$ = new Node("", "var_list", 3, $1, $2, $3);
    }
    | var {
        $$ = new Node("", "var_list", 1, $1);
    }
    ;

var: 
    var LSB INTEGER RSB {
        $$ = new Node("", "var", 4, $1, $2, $3, $4);
    }
    | ID {
        $$ = new Node("", "var", 1, $1);
    }
    ;

funct_declaration:
    TYPE ID LBRACKET para_list RBRACKET {
        $$ = new Node("", "funct_declaration", 5, $1, $2, $3, $4, $5);
    }
    | TYPE ID LBRACKET RBRACKET {
        $$ = new Node("", "funct_declaration", 4, $1, $2, $3, $4);
    }
    ;

para_list: 
    para COMMA para_list {
        $$ = new Node("", "para_list", 3, $1, $2, $3);
    }
    | para {
        $$ = new Node("", "para_list", 1, $1);
    }
    ;

para: 
    TYPE ID {
        $$ = new Node("", "para", 2, $1, $2);
    }
    ;

funct: 
    funct_declaration comp_statement {
        $$ = new Node("", "funct", 2, $1, $2);
    }
    ;

comp_statement: 
    LBRACE statements RBRACE {
        $$ = new Node("", "comp_statement", 3, $1, $2, $3);
    }
    ;

statements: 
    statement statements {
        $$ = new Node("", "statements", 2, $1, $2);
    }
    | {
        $$ = nullptr;
    }
    ;

statement: 
    ret_statement {
        $$ = new Node("", "statement", 1, $1);
    }
    | expr_statement {
        $$ = new Node("", "statement", 1, $1);
    }
    | comp_statement {
        $$ = new Node("", "statement", 1, $1);
    }
    | loop_statement {
        $$ = new Node("", "statement", 1, $1);
    }
    | select_statement {
        $$ = new Node("", "statement", 1, $1);
    }
    ;

ret_statement: 
    RETURN arithmetic_statement SEMI {
        $$ = new Node("", "ret_statement", 3, $1, $2, $3);
    }
    ;

expr_statement: 
    declaration_statement SEMI {
        $$ = new Node("", "expr_statement", 2, $1, $2);
    }
    | arithmetic_statement SEMI {
        $$ = new Node("", "expr_statement", 2, $1, $2);
    }
    /* arithmetic_statement includes arithmetichmatic and logical operation */
    | assignment SEMI {
        $$ = new Node("", "expr_statement", 2, $1, $2);
    }
    | funct_call SEMI {
        $$ = new Node("", "expr_statement", 2, $1, $2);
    }
    ;

declaration_statement: 
    var_declaration {
        $$ = new Node("", "declaration_statement", 1, $1);
    }
    | var_declaration ASSIGNOP arithmetic_statement {
        $$ = new Node("", "declaration_statement", 3, $1, $2, $3);
    }
    ;

arithmetic_statement: 
    arithmetic_statement AND arithmetic_statement {
        $$ = new Node("", "arithmetic_statement", 3, $1, $2, $3);
        $$->set_value_type($1->get_value_type());
    }
    | arithmetic_statement OR arithmetic_statement {
        $$ = new Node("", "arithmetic_statement", 3, $1, $2, $3);
        $$->set_value_type($1->get_value_type());
    }
    | NOT arithmetic_statement {
        $$ = new Node("", "arithmetic_statement", 2, $1, $2);
        $$->set_value_type($2->get_value_type());
    }
    | arithmetic_statement RELOP arithmetic_statement {
        $$ = new Node("", "arithmetic_statement", 3, $1, $2, $3);
        $$->set_value_type(TYPE_BOOL);
        // cout << "RELOP has been arrived" << endl;
    }
    | arithmetic_statement PLUS arithmetic_statement {
        $$ = new Node("", "arithmetic_statement", 3, $1, $2, $3);
        $$->set_value_type($1->get_value_type());
    }
    | arithmetic_statement MINUS arithmetic_statement {
        $$ = new Node("", "arithmetic_statement", 3, $1, $2, $3);
        $$->set_value_type($1->get_value_type());
    }
    | arithmetic_statement STAR arithmetic_statement {
        $$ = new Node("", "arithmetic_statement", 3, $1, $2, $3);
        $$->set_value_type($1->get_value_type());
    }
    | arithmetic_statement DIV arithmetic_statement {
        $$ = new Node("", "arithmetic_statement", 3, $1, $2, $3);
        $$->set_value_type($1->get_value_type());
    }
    | arithmetic_statement MODULO arithmetic_statement {
        $$ = new Node("", "arithmetic_statement", 3, $1, $2, $3);
        $$->set_value_type($1->get_value_type());
    }
    | MINUS arithmetic_statement {
        $$ = new Node("", "arithmetic_statement", 2, $1, $2);
        $$->set_value_type($2->get_value_type());
    }
    | LBRACKET arithmetic_statement RBRACKET {
        $$ = new Node("", "arithmetic_statement", 3, $1, $2, $3);
        $$->set_value_type($2->get_value_type());
    }
    | elem {
        $$ = new Node("", "arithmetic_statement", 1, $1);
        $$->set_value_type($1->get_value_type());
    }
    ;

elem: 
    ID {
        $$ = new Node("", "elem", 1, $1);
        $$->set_value_type($1->get_value_type());
    }
    | ID LSB arithmetic_statement RSB {
        $$ = new Node("", "elem", 4, $1, $2, $3, $4);
        $$->set_value_type($1->get_value_type() - IS_ARRAY);
    }
    | INTEGER {
        $$ = new Node("", "elem", 1, $1);
        $$->set_value_type(TYPE_INTEGER);
    }
    | FLOAT {
        $$ = new Node("", "elem", 1, $1);
        $$->set_value_type(TYPE_FLOAT);
    }
    | STRING {
        $$ = new Node("", "elem", 1, $1);
        $$->set_value_type(TYPE_CHAR_ARRAY);
    }
    | CHAR {
        $$ = new Node("", "elem", 1, $1);
        $$->set_value_type(TYPE_CHAR);
    }
    | BOOLEAN {
        $$ = new Node("", "elem", 1, $1);
        $$->set_value_type(TYPE_BOOL);
    }
    | funct_call {
        $$ = new Node("", "elem", 1, $1);
        $$->set_value_type($1->get_value_type());
    }
    ;

assignment: 
    elem ASSIGNOP arithmetic_statement {
        $$ = new Node("", "assignment", 3, $1, $2, $3);
        $$->set_value_type($3->get_value_type());
        $1->set_value_type($3->get_value_type());
    }
    | elem ACOP arithmetic_statement {
        $$ = new Node("", "assignment", 3, $1, $2, $3);
        $$->set_value_type($3->get_value_type());
        $1->set_value_type($3->get_value_type());
    }
    ;

funct_call: 
    ID LBRACKET args RBRACKET {
        $$ = new Node("", "funct_call", 4, $1, $2, $3, $4);
        $$->set_value_type($1->get_value_type());
    }
    | ID LBRACKET RBRACKET {
        $$ = new Node("", "funct_call", 3, $1, $2, $3);
        $$->set_value_type($1->get_value_type());
    }
    ;

args: 
    arithmetic_statement COMMA args {
        $$ = new Node("", "args", 3, $1, $2, $3);
    }
    | arithmetic_statement {
        $$ = new Node("", "args", 1, $1);
    }
    ;

loop_statement: 
    WHILE LBRACKET arithmetic_statement RBRACKET statement {
        $$ = new Node("", "loop_statement", 5, $1, $2, $3, $4, $5);
    }
    ;

select_statement: 
    IF LBRACKET arithmetic_statement RBRACKET statement {
        $$ = new Node("", "select_statement", 5, $1, $2, $3, $4, $5);
    }
    | IF LBRACKET arithmetic_statement RBRACKET statement ELSE statement {
        $$ = new Node("", "select_statement", 7, $1, $2, $3, $4, $5, $6, $7);
    }
    ;

%%