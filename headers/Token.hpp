#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum class TokenType{
    NONE,

    IDN,
    OPR,
    SYM,
    KEY,
    LIT,
    NUM_LIT,
    STR_LIT
};

struct Token{
    // Variables
    TokenType type;
    std::string value;
    // Constructor & Destructor
    Token();
    Token(TokenType type, std::string value);
    ~Token() = default;
};

#endif