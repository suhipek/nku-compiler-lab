%option noyywrap
%{
    #define YY_NO_UNPUT
    #define YY_NO_INPUT
    #include <string>

    #include "parser.h"
    #include <sstream>
    #include <iomanip>
    #include <ostream>
    #include <fstream>
    using namespace std;

    extern FILE *yyin; 
    extern FILE *yyout;
    extern bool dump_tokens;

    void DEBUG_FOR_LAB4(std::string s){
        std::string DEBUG_INFO = "[DEBUG LAB4]: \t" + s + "\n";
        fputs(DEBUG_INFO.c_str(), yyout);
    }
%}

DECIMIAL ([1-9][0-9]*|0)
HEX (0[xX][0-9a-fA-F]+)
OCT (0[0-7]+)
ID [[:alpha:]_][[:alpha:][:digit:]_]*
EOL (\r\n|\n|\r)
WHITE [\t ]
commentbegin "/*"
commentend "*/"
commentline "//"
commentelement [^\n]

%x BLOCKCOMMENT
%x LINECOMMENT

%%

"int" {
    /*
    * Questions: 
    *   Q1: Why we need to return INT in further labs?
    *   Q2: What is "INT" actually?
    */
    if(dump_tokens)
        DEBUG_FOR_LAB4("INT\tint");
    return INT;
}
"bool" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("BOOL\tbool");
    return BOOL;
}
"const" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("CONST\tconst");
    return CONST;
}
"void" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("VOID\tvoid");
    return VOID;
}
"while" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("WHILE\twhile");
        return WHILE;
}
"for" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("FOR\tfor");
        return FOR;
}
"if" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("IF\tif");
    return IF;
};
"else" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ELSE\telse");
    return ELSE;
};
"return" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RETURN\treturn");
    return RETURN;
}

"=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ASSIGN\t=");
    return ASSIGN;
}
"<" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LESS\t<");
    return LESS;
}
">" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("GREATER\t>");
    return GREATER;
}
"==" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("EQ\t==");
        return EQ;
}
"!=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("NEQ\t!=");
        return NEQ;
}
"<=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LEQ\t<=");
        return LEQ;
}
">=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("GEQ\t>=");
        return GEQ;
}
"&&" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("AND\t&&");
        return AND;
}
"||" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("OR\t||");
        return OR;
}

"+" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ADD\t+");
    return ADD;
}
"-" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("SUB\t-");
        return SUB;
}
"*" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("STAR\t*");
        return STAR;
}
"/" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("DIV\t/");
        return DIV;
}
"%" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("MOD\t%");
        return MOD;
}
"!" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("NOT\t!");
        return NOT;
}


";" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("SEMICOLON\t;");
    return SEMICOLON;
}
"(" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LPAREN\t(");
    return LPAREN;
}
")" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RPAREN\t)");
    return RPAREN;
}
"{" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LBRACE\t{");
    return LBRACE;
}
"}" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RBRACE\t}");
    return RBRACE;
}
"," {
    if(dump_tokens)
        DEBUG_FOR_LAB4("COMMA\t,");
    return COMMA;
}

{HEX} {
    stringstream conv;
    uint32_t tmp;
    conv << hex << yytext;
    conv >> tmp; 
    yylval.itype = (int)tmp;
    if(dump_tokens)
    {
        fprintf(stderr, "HEX: %s covert to %d\n", yytext, yylval.itype);
        DEBUG_FOR_LAB4("HEX");
    }
    return INTEGER;
}
{OCT} {
    stringstream conv;
    uint32_t tmp;
    conv << oct << yytext;
    conv >> tmp; 
    yylval.itype = (int)tmp;
    if(dump_tokens)
    {
        fprintf(stderr, "OCT: %s covert to %d\n", yytext, yylval.itype);
        DEBUG_FOR_LAB4("OCT");
    }
    return INTEGER;
}
{DECIMIAL} {
    yylval.itype = atoi(yytext);
    if(dump_tokens)
    {
        fprintf(stderr, "DEC: %s covert to %d\n", yytext, yylval.itype);
        DEBUG_FOR_LAB4("DEC");
    }
    return INTEGER;
}

{ID} {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme;
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    return ID;
}
{commentbegin} {
    BEGIN BLOCKCOMMENT;
}
<BLOCKCOMMENT>{commentelement} {
}
<BLOCKCOMMENT>{EOL} {
    yylineno++;
}
<BLOCKCOMMENT>{commentend} {
    BEGIN INITIAL;
}

{commentline} {
    BEGIN LINECOMMENT;
}
<LINECOMMENT>{commentelement} {
}
<LINECOMMENT>{EOL} {
    yylineno++;
    BEGIN INITIAL;
}

{EOL} yylineno++;
{WHITE}
%%
