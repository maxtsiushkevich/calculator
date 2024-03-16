#pragma once

#include <string>
#include "Error.hpp"
#include <map>
#include <stdexcept>
#include "Token.hpp"
#include "MyString.hpp"

#pragma pack(push, 1)

class Token {
public:
    // Тип
    enum Type : unsigned char {
        OPERATOR,      // унарный/бинарный оператор
        L_PARANTHESIS, // открывающая скобка
        R_PARANTHESIS, // закрывающая скобка
        INT_LITERAL,   // целое число
        FLOAT_LITERAL, // число с плавающей точкой 
        FUNCTION,      // функция
        SEPARATOR      // разделитель аргументов функции
    };

    // Ассоциативность
    enum OperatorAssociativity : unsigned char {
        NONE,  // токен - не оператор
        RIGHT, // правоассоциативный
        LEFT   // левоассоциативный
    };

    Token(MyString token, Type type, OperatorAssociativity asc = NONE);

    Token() : str(), type(OPERATOR), opAsc(NONE) {}

    Token(const Token &other)
            : type(other.type), opAsc(other.opAsc), str(other.str) {
    }

    Token &operator=(const Token &other) {
        if (this != &other) { // Проверка на самоприсваивание
            type = other.type;
            opAsc = other.opAsc;
            str = other.str;
        }
        return *this;
    }


    // Приоритет
    short getPrecendance() const;

    const Type &getType() const { return type; }

    const OperatorAssociativity &getAsc() const { return opAsc; }

    const MyString &getStr() const { return str; }

private:
    Type type;
    OperatorAssociativity opAsc;
    MyString str;
};


Token::Token(MyString token, Type type, OperatorAssociativity asc) : type{type}, str{token}
{
    if (type == OPERATOR && asc == NONE)
        throw std::logic_error("Associativity required!");

    else if (type != OPERATOR && asc != NONE)
        throw std::logic_error("Non-operator token can't have an associativity!");

    opAsc = asc;
}

struct OperatorPrecedence {
    MyString op;
    int precedence;
};

const OperatorPrecedence op_leftassociative[] = {
        {"+", 2},
        {"-", 2},
        {"/", 3},
        {"*", 3},
        {"^", 5}
};

const OperatorPrecedence op_rightassociative[] = {
        {"-", 4} // унарное отрицание
};

short Token::getPrecendance() const {
    for (const auto &op_prec: op_leftassociative) {
        if (op_prec.op == str)
            return op_prec.precedence;
    }

    for (const auto &op_prec: op_rightassociative) {
        if (op_prec.op == str)
            return op_prec.precedence;
    }

    throw Error("Unknown Operator!", Error::Syntax);
}

#pragma pack(pop)