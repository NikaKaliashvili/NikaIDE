#include "../../include/nikaide.h"

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

	if (source.substr(start, position - start) == "int") {
		return {
		_TokenType::Keyword,
		source.substr(start,position - start),
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