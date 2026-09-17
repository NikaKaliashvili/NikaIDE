#pragma once

#include "../nikaide.h"

enum _TokenType
{
    Identifier,
    Number,
    Keyword,
    Comment,
    Hash,
    Dot,
    Exclamation,
    Dash,

    Plus,
    Minus,
    Equals,

    Semicolon,

    LeftParen,
    RightParen,

    LeftBrace,
    RightBrace,

    AngleLeft,
    AngleRight
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
    bool IsKeyword(const std::string& text);

    Token ReadIdentifier();
    Token ReadNumber();

    std::vector<Token> Tokenize();

private:
    std::string source;
    size_t position;
};