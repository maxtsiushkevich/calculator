#pragma once
#include <vector>
#include "Token.hpp"
#include "Error.hpp"
#include "MyVector.hpp"
#include <iostream>
#include <stack>
#include <cmath>
#include <tuple>
#include <format>
#include <cstdlib>

void shuntingYard(MyVector &expr, MyVector &outQueue)
{
    std::stack<Token> stack;
    auto fromStackToQueue = [&]() { outQueue.push_back(stack.top()); stack.pop(); };

    for(int j = 0; j < expr.getSize(); j++)
    {
        Token token = expr[j];
        switch(token.getType())
        {
            case Token::INT_LITERAL:
            case Token::FLOAT_LITERAL:
                outQueue.push_back(token);
                break;
            case Token::L_PARANTHESIS:
            case Token::FUNCTION:
                stack.push(token);
                break;
            case Token::OPERATOR:
                if(!stack.empty())
                {
                    while(stack.top().getType() == Token::OPERATOR && ((stack.top().getPrecendance() > token.getPrecendance())
                                                                       || (stack.top().getPrecendance() == token.getPrecendance() && token.getAsc() == Token::LEFT)))
                    {
                        fromStackToQueue();
                        if(stack.empty())
                            break;
                    }
                }
                stack.push(token);
                break;

            case Token::R_PARANTHESIS:
                if(stack.empty())
                    throw Error("Non-balanced on paranthesis expression!", Error::Syntax);
                while (stack.top().getType() != Token::L_PARANTHESIS)
                {
                    fromStackToQueue();
                    if (stack.empty())
                        throw Error("Non-balanced on paranthesis expression!", Error::Syntax);
                }
                stack.pop();
                if(!stack.empty() && stack.top().getType() == Token::FUNCTION)
                    fromStackToQueue();
                break;

            case Token::SEPARATOR:
                if(stack.empty())
                    throw Error("Paranthesis or separator missed!", Error::Syntax);
                while(stack.top().getType() != Token::L_PARANTHESIS)
                {
                    fromStackToQueue();
                    if(stack.empty())
                        throw Error("Paranthesis-unbalanced expression!", Error::Syntax);
                }
                break;
        }
    }
    while(!stack.empty())
    {
        if(stack.top().getType() == Token::L_PARANTHESIS)
            throw Error("Paranthesis-unbalanced expression!", Error::Syntax);
        else
            fromStackToQueue();
    }
}

double countRPN(MyVector &expr)

{
    std::stack<double> stack;
    auto getOneToken = [&]()
    {
        if(stack.empty()) throw Error("Not enough arguments in function!", Error::Syntax);
        double x = stack.top();
        stack.pop();
        return x;
    };
    auto getTwoTokens = [&]()
    {
        double x = getOneToken(), y = getOneToken();
        return std::tuple{y,x};
    };

    auto checkedDivision = [&](double a, double b)
    {
        if(b == 0.f) throw Error("Division by zero", Error::Math);
        return a / b;
    };

    double res;

    for(int j = 0; j < expr.getSize(); j++)
    {
        Token token = expr[j];
        const MyString &str = token.getStr();
        switch(token.getType())
        {
            case Token::INT_LITERAL:
                stack.push(atof(str.getString()));
                break;
            case Token::FLOAT_LITERAL:
                stack.push(atof(str.getString()));
                break;
            case Token::OPERATOR:
                switch(token.getAsc())
                {
                    case Token::LEFT:
                    {
                        auto [a,b] = getTwoTokens();
                        if      (str == MyString("+")) res = a + b;
                        else if (str == MyString("-")) res = a - b;
                        else if (str == MyString("*")) res = a * b;
                        else if (str == MyString("/")) res = checkedDivision(a, b);
                        else if (str == MyString("^")) res = std::pow(a,b);
                        else    throw Error("Unknown operator!", Error::Syntax);
                        break;
                    }
                    case Token::RIGHT:
                    {
                        auto a = getOneToken();
                        if   (str == MyString("-")) res = -a;
                        else throw Error("Unknown operator!", Error::Syntax);
                        break;
                    }
                    case Token::NONE:
                        throw std::logic_error("Operator must have associativity!");
                        break;
                }
                stack.push(res);
                break;
            case Token::FUNCTION:
                if(str == MyString("log"))
                {
                    auto [a,b] = getTwoTokens();
                    if(a <= 0.f || a == 1.0f) throw Error("log(a,x): not defined for a", Error::Math);
                    if(b <= 0.f) throw Error("log(a,x): out of function's domain", Error::Math);
                    res = std::log(b) / std::log(a);
                }
                else if (str == MyString("log2"))
                {
                    auto a = getOneToken();
                    if(a <= 0.f) throw Error("log2(x): out of function's domain", Error::Math);
                    res = std::log2(a);
                }
                else if(str == MyString("ln"))
                {
                    auto a = getOneToken();
                    if(a <= 0.f) throw Error("ln(x): out of function's domain", Error::Math);
                    res = std::log(a);
                }
                else if(str == MyString("lg"))
                {
                    auto a = getOneToken();
                    if(a <= 0.f) throw Error("lg(x): out of function's domain", Error::Math);
                    res = std::log10(a);
                }
                else if(str == MyString("max"))
                {
                    auto[a,b] = getTwoTokens();
                    res = a > b ? a : b;
                }
                else if(str == MyString("min"))
                {
                    auto[a,b] = getTwoTokens();
                    res = a < b ? a : b;
                }
                else if(str == MyString("sqrt"))
                {
                    auto a = getOneToken();
                    res = std::sqrt(a);
                }
                else if(str == MyString("sin"))
                {
                    auto a = getOneToken();
                    res = std::sin(a);
                }
                else if(str == MyString("cos"))
                {
                    auto a = getOneToken();
                    res = std::cos(a);
                }
                else if (str == MyString("tg"))
                {
                    auto a = getOneToken();
                    res = std::tan(a);
                }
                else if (str == MyString("ctg"))
                {
                    auto a = getOneToken();
                    res = 1 / std::tan(a);
                }
                else
                    throw Error("Unknown function!", Error::Syntax);
                stack.push(res);
                break;
            default:
                break;
        }
    }
    return stack.top();
}
