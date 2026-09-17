#include "../../include/nikaide.h"

std::vector<std::string> keywords = {
	"int",
	"char",
	"float",
	"double",
	"bool",
	"void",
	"if",
	"else",
	"for",
	"while",
	"return",
	"class",
	"struct",
	"public",
	"private",
	"protected",
	"const"
};

bool Lexer::IsKeyword(const std::string& text)
{
	return std::find(keywords.begin(), keywords.end(), text) != keywords.end();
}

Lexer::Lexer(const std::string& source) {
	this->source = source;
	this->position = 0;
}

bool Lexer::IsIdentifierStart(char letter) {
	return std::isalpha(letter) || letter == '_';
}

bool Lexer::IsIdentifierPart(char letter) {
	return std::isalnum(letter) || letter == '_';
}

Token Lexer::ReadIdentifier()
{
	size_t start = position;

	while (position < source.length()) {
		char current = source[position];

		if (IsIdentifierPart(current)) {
			position++;
		}
		else {
			break;
		}
	}

	std::string text = source.substr(start, position - start);

	if (IsKeyword(text)) {
		return {
			_TokenType::Keyword,
			text,
			static_cast<int>(start)
		};
	}

	return {
		_TokenType::Identifier,
		source.substr(start,position - start),
		static_cast<int>(start)
	};

}

Token Lexer::ReadNumber() {
	size_t start = position;

	while (position < source.length()) {
		char current = source[position];

		if (std::isdigit(current)) {
			position++;
		}
		else {
			break;
		}
	}

	return {
		_TokenType::Number,
		source.substr(start, position - start),
		static_cast<int>(start)
	};

}

std::vector<Token> Lexer::Tokenize() {
	std::vector<Token> tokens;

	while (position < source.length())
	{
		char current = source[position];

		// if its empty space just skip it
		if (std::isspace(current))
		{
			position++;
			continue;
		}

		// if it starts with letter or _
		if (IsIdentifierStart(current))
		{
			tokens.push_back(ReadIdentifier());
			continue;
		}

		// if its a number
		if (std::isdigit(current)) {
			tokens.push_back(ReadNumber());
			continue;
		}

		// if its equals symbol
		// TEMPORARY! will need to update for double equals
		if (current == '=') {
			tokens.push_back(Token(_TokenType::Equals, "=",static_cast<int>(position)));
			position++;
			continue;
		}

		if (current == '"' && position + 1 >= source.length()){
			tokens.push_back(Token(_TokenType::String, "\"", static_cast<int>(position)));
			position++;
		}

		if (current == '"')
		{
			size_t start = position;

			position++;

			while (position < source.length() &&
				source[position] != '"')
			{
				position++;
			}

			if (position < source.length())
			{
				position++; // include closing "
			}

			tokens.push_back(
				Token(
					_TokenType::String,
					source.substr(start, position - start),
					static_cast<int>(start)
				)
			);

			continue;
		}

		if (current == '#') {
			tokens.push_back(Token(_TokenType::Hash, "#", static_cast<int>(position)));
			position++;
			continue;
		}

		if (current == '.') {
			tokens.push_back(Token(_TokenType::Dot, ".", static_cast<int>(position)));
			position++;
			continue;
		}

		if (current == '!') {
			tokens.push_back(Token(_TokenType::Exclamation, "!", static_cast<int>(position)));
			position++;
			continue;
		}

		if (current == '<') {
			tokens.push_back(Token(_TokenType::AngleLeft, "<", static_cast<int>(position)));
			position++;
			continue;
		}

		if (current == '>') {
			tokens.push_back(Token(_TokenType::AngleRight, ">", static_cast<int>(position)));
			position++;
			continue;
		}

		if (current == '+') {
			tokens.push_back(Token(_TokenType::Plus, "+", static_cast<int>(position)));
			position++;
			continue;
		}

		if (current == '-') {
			tokens.push_back(Token(_TokenType::Minus, "-", static_cast<int>(position)));
			position++;
			continue;
		}

		if (current == '{') {
			tokens.push_back(Token(_TokenType::LeftBrace, "{", static_cast<int>(position)));
			position++;
			continue;
		}

		if (current == '}') {
			tokens.push_back(Token(_TokenType::RightBrace, "}", static_cast<int>(position)));
			position++;
			continue;
		}

		if (current == '/' && position + 1 < source.length() && source[position + 1] == '/') {

			size_t start = position;

			position += 2;

			while (position < source.length())
				position++;

			tokens.push_back(Token(_TokenType::Comment, source.substr(start, position - start), static_cast<int>(start)));
			continue;
		}

		if (current == '/' && source[position+1] != '/') {
			tokens.push_back(Token(_TokenType::Dash, "/", static_cast<int>(position)));
			position++;
			continue;
		}

		if (current == '(') {
			tokens.push_back(Token(_TokenType::LeftParen, "(", static_cast<int>(position)));
			position++;
			continue;
		}

		if (current == ')') {
			tokens.push_back(Token(_TokenType::RightParen, ")", static_cast<int>(position)));
			position++;
			continue;
		}

		if (current == ';') {
			tokens.push_back(Token(_TokenType::Semicolon, ";", static_cast<int>(position)));
			position++;
			continue;
		}

		position++;
	}

	return tokens;
}