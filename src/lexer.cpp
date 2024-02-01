#include <list>
#include <string>

#include "token.h"
#include "lexer.h"

// Lexer constructor method
Lexer::Lexer(std::string source) {
  _source = source;
}

/******************
 * HELPER METHODS *
 ******************
 * atEnd()
 * find()
 * isDigit()
 */

// Check if we are at the end of the program
bool Lexer::atEnd() {
  return (start >= _source.length());
}

// Advance only if we find the correct character
bool Lexer::find(char ch) {
  if (atEnd()) {
    return false;
  } else if (_source[curr] != ch) {
    return false;
  }

  curr++;
  return true; 
}

// Check if the character is a valid digit
bool isDigit(char ch) {
  return (ch >= '0' && ch <= '9');
}

// Check if the character is a valid character
bool isAlpha(char ch) {
  return (ch >= 'a' && ch <= 'z') ||
         (ch >= 'A' && ch <= 'Z') ||
         (ch == '_');
}

// Check if the character is a valid digit or character
bool isAlphaNumeric(char ch) {
  return isDigit(ch) || isAlpha(ch);
}


/*********************
 * LOOKAHEAD METHODS *
 *********************
 * advance()
 * peek()
 * peekTwo()
 */

// Moves our scanning "pointer" forward
char Lexer::advance() {
  return _source[curr++];
}

// Looks at where the scanning pointer is
char Lexer::peek() {
  if (atEnd()) {
    return '\0';
  }
  return _source[curr];
}

// Looks a character ahead of the scanning pointer
char Lexer::peekTwo() {
  if (curr + 1 >= _source.length()) {
    return '\0';
  }
  return _source[curr + 1];
}

void Lexer::scanString() {
  while (peek() != '"' && not(atEnd())) {
    if (peek() == '\n') {
      line++;
      advance();
    }
  }

  if (atEnd()) {
    // unterminated string error
    return;
  }

  advance();

  std::string literal = _source.substr(start + 1, curr);
  appendToken(STRING, literal);
}

void Lexer::scanNumber() {
  while (isDigit(peek())) {
    advance();
  }

  if (peek() == '.' && isDigit(peekTwo())) {
    advance();
    while (isDigit(peek())) {
      advance();
    }
  }

  // Add a token by slicing up the substring and converting to float
  appendToken(NUM, std::stod(_source.substr(start, curr + 1)));
}

void Lexer::scanIdentifier() {
  while (isAlphaNumeric(peek())) {
    advance();
  }

  std::string text = _source.substr(start, curr + 1);
  TokenType type;

  if (_keywords.find(text) == _keywords.end()) {
    type = IDENTIFIER;
  } else {
    type = _keywords.at(text);
  }

  appendToken(type, "");
}

void Lexer::appendToken(TokenType type, std::any literal) {
  std::string lexeme = _source.substr(start, curr + 1);
  Token newToken(type, literal, lexeme, line);
  _tokens.push_back(newToken);
}

std::list<Token> Lexer::scanSource() {
  while(not(atEnd())) {
    start = curr;
    scanToken();
  }

  Token EOFToken(EF, "", NULL, line);
  _tokens.push_back(EOFToken);
  return _tokens;
}

Token Lexer::scanToken() {
  char c = advance();
  switch (c) {
    case '(': appendToken(LEFT_PAREN, ""); break;
    case ')': appendToken(RIGHT_PAREN, ""); break;
    case '{': appendToken(LEFT_BRACE, ""); break;
    case '}': appendToken(RIGHT_BRACE, ""); break;
    case ',': appendToken(COMMA, ""); break;
    case '.': appendToken(DOT, ""); break;
    case '-': appendToken(MINUS, ""); break;
    case '+': appendToken(PLUS, ""); break;
    case '*': appendToken(STAR, ""); break;
    case ';': appendToken(SEMICOLON, ""); break;
    case '"': scanString(); break;
    case '=':
      appendToken(find('=') ? EQUAL_EQUAL : EQUAL, "");
      break;
    case '!':
      appendToken(find('=') ? EXCLAMATION_EQUAL : EXCLAMATION, "");
      break;
    case '>':
      appendToken(find('=') ? GREATER_EQUAL : GREATER, "");
      break;
    case '<':
      appendToken(find('=') ? LESS_EQUAL : LESS, "");
      break;
    case '/':
      if (find('/')) {
        while (peek() != '\n' && not(atEnd())) {
          advance();
        }
      } else {
        appendToken(FORWARD_SLASH, "");
      }
    case ' ':
    case '\r':
    case '\t':
      break;
    case '\n':
      line++;
      break;
    default:
      if (isDigit(c)) {
        scanNumber();
      } else if (isAlpha(c))) {
        scanIdentifier();
      } else {
        // some error here
        break;
      }
  }
}
