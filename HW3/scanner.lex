%{
#include <stdio.h>
#include "node.cpp"
#define YYSTYPE Node*
#include "parser.tab.hpp"
#include "hw3_output.hpp"
%}

%option yylineno
%option noyywrap
digit ([0-9])
positive ([1-9])
letter ([a-zA-Z])
whitespace ([ \r\n\t])
zero 0

%%

int             {yylval = new TypeNode(yylineno, yytext); return INT;}
byte            {yylval = new TypeNode(yylineno, yytext); return BYTE;}
b               {yylval = new TypeNode(yylineno, yytext); return B;}
bool            {yylval = new TypeNode(yylineno, yytext); return BOOL;}
and             {return AND;}
or              {return OR;}
not             {return NOT;}
true            {yylval = new BoolNode(yylineno, yytext); return TRUE;}
false           {yylval = new BoolNode(yylineno, yytext); return FALSE;}
return          {return RETURN;}
if              {return IF;}
else            {return ELSE;}
while           {return WHILE;}
break           {yylval = new Node(yylineno, yytext); return BREAK;}
continue        {yylval = new Node(yylineno, yytext); return CONTINUE;}
;               {return SC;}
\(              {yylval = new Node(yylineno, yytext); return LPAREN;}
\)              {yylval = new Node(yylineno, yytext); return RPAREN;}
\{              {return LBRACE;}
\}              {return RBRACE;}
=               {return ASSIGN;}
\<=|\>=|\>|\<   {yylval = new OperatorRelop(yylineno, yytext); return RELOPFIRST;}
==|!=           {return RELOPSECOND;}
[\*\/]          {return BINOPFIRST;}
[\+\-]          {return BINOPSECOND;}
{letter}+[a-zA-Z0-9]*       {yylval = new Identifier(yylineno, yytext); return ID;}
{positive}{digit}*             {yylval = new Num(yylineno, yytext); return NUM;}
{zero}          {yylval = new Num(yylineno, yytext); return NUM;}
{whitespace}    {yylval = new Node(yylineno, yytext);}
\/\/[^\r\n]*[\r|\n|\r\n]?   ;

\"([^\n\r\"\\]|\\[rnt"\\])+\"  {yylval = new StringNode(yylineno, yytext); return STRING;}
.               {output::errorLex(yylval->line_number); exit(0);}
%%
