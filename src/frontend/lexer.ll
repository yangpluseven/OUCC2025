%option c++
%option noyywrap
%option yylineno

%{
    #include <string>
    #include <iostream>

    #include "ast.hpp"
    #include "generated/parser.tab.hpp"

    namespace Compiler {
        class Lexer;
    }

    #undef YY_DECL
    #define YY_DECL \
        Compiler::Parser::token_type Compiler::Lexer::yylex( \
            Compiler::Parser::semantic_type* yylval, \
            Compiler::Parser::location_type* yylloc \
        )

    #undef YY_USER_ACTION
    #define YY_USER_ACTION \
        yylloc->begin.line = yylloc->end.line = yylineno; \
        yylloc->begin.column = this->yycolumn; \
        yylloc->end.column = this->yycolumn + yyleng - 1; \
        this->yycolumn += yyleng;

    using token = yy::parser::token;
%}

ID [a-z_A-Z][a-z_A-Z0-9]*

INT_LIT ([1-9][0-9]*|0[0-7]*|(0x|0X)[0-9a-fA-F]+)

FLOAT_SUFFIX [fFlL]

DEC_EXP ([Ee][-+]?[0-9]+)
DEC_FLOAT_LIT_HAVE_POINT_HAVE_RIGHT ([0-9]*\.[0-9]+{DEC_EXP}?{FLOAT_SUFFIX}?)
DEC_FLOAT_LIT_HAVE_POINT_NO_RIGHT ([0-9]+\.{DEC_EXP}?{FLOAT_SUFFIX}?)
DEC_FLOAT_LIT_NO_POINT ([0-9]+{DEC_EXP}{FLOAT_SUFFIX}?)
DEC_FLOAT_LIT ({DEC_FLOAT_LIT_HAVE_POINT_HAVE_RIGHT}|{DEC_FLOAT_LIT_HAVE_POINT_NO_RIGHT}|{DEC_FLOAT_LIT_NO_POINT})

HEX_EXP ([Pp][-+]?[0-9]+)
HEX_FLOAT_LIT_HAVE_POINT_HAVE_RIGHT ((0[xX])[a-fA-F0-9]*\.[a-fA-F0-9]+{HEX_EXP}{FLOAT_SUFFIX}?)
HEX_FLOAT_LIT_HAVE_POINT_NO_RIGHT ((0[xX])[a-fA-F0-9]+\.{HEX_EXP}{FLOAT_SUFFIX}?)
HEX_FLOAT_LIT_NO_POINT ((0[xX])[a-fA-F0-9]+{HEX_EXP}{FLOAT_SUFFIX}?)
HEX_FLOAT_LIT ({HEX_FLOAT_LIT_HAVE_POINT_HAVE_RIGHT}|{HEX_FLOAT_LIT_HAVE_POINT_NO_RIGHT}|{HEX_FLOAT_LIT_NO_POINT})

FLOAT_LIT ({DEC_FLOAT_LIT}|{HEX_FLOAT_LIT})

SL_COMMENT "//".*
%x ML_COMMENT

%%

<INITIAL>{
    "/*"                        { BEGIN(ML_COMMENT); }
    {SL_COMMENT}                { /* Ignore single line comments */ }

    {INT_LIT}                   { yylval->emplace<int>(std::stoi(yytext, nullptr, 0)); return token::INT; }
    {FLOAT_LIT}                 { yylval->emplace<float>(std::stof(yytext, nullptr)); return token::FLOAT; }

    "int"                       { return token::T_INT; }
    "float"                     { return token::T_FLOAT; }
    "void"                      { return token::T_VOID; }
    "const"                     { return token::T_CONST; }
    "return"                    { return token::T_RETURN; }
    "if"                        { return token::T_IF; }
    "else"                      { return token::T_ELSE; }
    "while"                     { return token::T_WHILE; }
    "break"                     { return token::T_BREAK; }
    "continue"                  { return token::T_CONTINUE; }

    {ID}                        { yylval->emplace<std::string>(yytext); return token::ID;  }

    ">="                        { return token::T_GE; }
    "<="                        { return token::T_LE; }
    "=="                        { return token::T_EQ; }
    "!="                        { return token::T_NEQ; }
    "&&"                        { return token::T_AND; }
    "||"                        { return token::T_OR; }

    [-+*/%(){}[\];=,<>!]        { return yy::parser::symbol_type(yytext[0]); }

    \n                          { this->yycolumn = 1; }
    [ \t\r]+                    { /* Ignore blank characters */ }

    .                           { std::cerr << "[Lex] Error: Unknown character '" << *yytext << "' on line " << yylineno << std::endl; return token::T_ERROR; }
}

<ML_COMMENT>{
    "*/"                        { BEGIN(INITIAL); }
    [^*\n]+                     { /* Ignore content inside multi-line comments */ }
    \n                          { /* Ignore newlines inside multi-line comments */ }
    "*"                         { /* Ignore '*' inside multi-line comments */ }
}

%%

Compiler::Lexer::Lexer(std::istream& in) : yycolumn(1) {
    this->switch_streams(in);
}
