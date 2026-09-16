#pragma once

#include "../nikaide.h"

enum _TokenType
{
    Identifier,
    Number,
    Keyword,

    Plus,
    Minus,
    Equals,

    Semicolon,

    LeftParen,
    RightParen,

    LeftBrace,
    RightBrace
};

struct Token
{
    _TokenType type;
    std::string text;

    int column;
};

class Lexer {
public:
    Lexer(const std::string& source);

    bool IsIdentifierStart(char letter);
    bool IsIdentifierPart(char letter);
    Token ReadIdentifier();
    Token ReadNumber();

    std::vector<Token> Tokenize();

private:
    std::string source;
    size_t position;
};