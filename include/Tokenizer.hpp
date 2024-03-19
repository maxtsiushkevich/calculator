#pragma once
#include <vector>
#include "Token.hpp"
#include "Error.hpp"
#include "MyString.hpp"

#include "MyVector.hpp"

enum State : unsigned char
{
    S0, // Стартовое
    S1, // Токенизация скобки/оператора
    S2, // Запись целого числа в буфер
    S3, // Запись floating-point числа в буфер
    S4, // Запись функции в буфер
    S5  // Токенизация записанного числа/функции из буфера
};

//void tokenize(const MyString &expr, MyVector &tokens)
void tokenize(const MyString &expr, MyVector<Token> &tokens)
{
    State state = S0;

    MyString validOperators = "+-*^/";
    bool isDigit, isLetter, isOp, isParanth, isPoint, isSep, isLParanth, isRParanth;

    MyString buffer;

    Token::Type bufferTokenType = Token::INT_LITERAL;

    for (int i = 0; i < expr.getLength(); i++)
    {
        char s = expr.getString()[i];
//        std::cout << s << std::endl;
        // Определяем тип символа
        isDigit = isdigit(s);
        isLetter = isalpha(s);
        isLParanth = s == '(';
        isRParanth = s == ')';
        isParanth = isLParanth || isRParanth;
        isPoint = s == '.';
        isSep = s == ',';
        isOp = validOperators.find(s) != validOperators.npos;

        // Если тип символа неопределен, значит ошибка в синтаксисе
        if(!(isDigit || isLetter || isParanth || isPoint || isSep || isOp))
            throw Error("error aaa", Error::Syntax);

        // Смена состояния
        switch(state)
        {
            case S0:
                if (isOp || isParanth)
                    state = S1;
                else if (isDigit)
                    state = S2;
                else if (isLetter)
                    state = S4;
                else if (isPoint || isSep)
                    throw Error("error", Error::Syntax);
                break;
            case S1:
                if (isDigit)
                    state = S2;
                else if (isLetter)
                    state = S4;
                else if (isPoint || isSep)
                    throw Error("error", Error::Syntax);
                break;
            case S2:
                bufferTokenType = Token::INT_LITERAL;
                if (isPoint)
                    state = S3;
                else if (isParanth || isOp || isSep)
                    state = S5;
                else if (isLetter)
                    throw Error("error", Error::Syntax);
                break;
            case S3:
                bufferTokenType = Token::FLOAT_LITERAL;
                if (isParanth || isOp || isSep)
                    state = S5;
                else if (isPoint)
                    throw Error("error", Error::Syntax);
                break;
            case S4:
                bufferTokenType = Token::FUNCTION;
                if(isLParanth)
                    state = S5;
                else if(isOp || isRParanth || isSep)
                    throw Error("error", Error::Syntax);
                break;
            case S5:
                if (isParanth || isOp)
                    state = S1;
                else if (isDigit)
                    state = S2;
                else if (isLetter)
                    state = S4;
                else if (isPoint || isSep)
                    throw Error("error", Error::Syntax);
                break;
            default:
                break;
        }

        auto tokenize_Op_Paranth_Sep = [&]()
        {
            char temp[2] = {s, '\0'}; // Create a null-terminated string from the character s
            MyString tempStr(temp); // Convert the character to MyString
            if(isOp)
            {
                // обработка unary negation
                if(tokens.getSize() == 0 || tokens[tokens.getSize()-1].getType() == Token::L_PARANTHESIS) {
                    tokens.push_back({tempStr, Token::OPERATOR, Token::RIGHT});
                }
                else {
                    tokens.push_back({tempStr, Token::OPERATOR, Token::LEFT});
                }
            }
            else if(isParanth)
            {
                tokens.push_back({tempStr, isRParanth ? Token::R_PARANTHESIS : Token::L_PARANTHESIS});
            }
            else if(isSep)
            {
                tokens.push_back({tempStr, Token::SEPARATOR});
            }
        };

        // Действия
        switch(state)
        {
            case S1:
                tokenize_Op_Paranth_Sep();
                break;
            case S2: case S3: case S4:
                buffer.push_back(s);
                break;
            case S5:
                tokens.push_back({buffer, bufferTokenType});
                buffer.clear();
                tokenize_Op_Paranth_Sep();
                break;
        }
    }
    if(!buffer.empty())
        tokens.push_back({buffer, bufferTokenType});
}

