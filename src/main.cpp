#include <iostream>
#include "RPN.hpp"
#include "Tokenizer.hpp"

int main()
{
//    std::vector<Token> tokensInfix, tokensRPN;
//    std::vector<Token> tokensRPN;
    MyVector tokensInfix, tokensRPN;


    MyString expr = "log2(23)+(-2/(3.14))*(sqrt(0.1*10^(-3)/0.02))";
    std::cout << "Expression: " << expr.getString() << std::endl;

    try
    {
        tokenize(expr, tokensInfix);
        for(int j = 0; j < tokensInfix.getSize(); j++)
        {
            Token i = tokensInfix[j];
//            std::string type, asc;
            MyString type, asc;
            switch(i.getType())
            {
                case Token::OPERATOR:
                    type = "OPERATOR";
                    break;
                case Token::L_PARANTHESIS:
                    type = "L_PARANTHESIS";
                    break;
                case Token::R_PARANTHESIS:
                    type = "R_PARANTHESIS";
                    break;
                case Token::INT_LITERAL:
                    type = "INT_LITERAL";
                    break;
                case Token::FLOAT_LITERAL:
                    type = "FLOAT_LITERAL";
                    break;
                case Token::FUNCTION:
                    type = "FUNCTION";
                    break;
                case Token::SEPARATOR:
                    type = "SEPARATOR";
                    break;
            }

            switch(i.getAsc())
            {
                case Token::NONE:
                    asc = "NONE";
                    break;
                case Token::RIGHT:
                    asc = "RIGHT";
                    break;
                case Token::LEFT:
                    asc = "LEFT";
                    break;
            }
            std::cout << i.getStr().getString() << "\t" << type.getString() << "\t" << asc.getString() << "\n";
        }
//        shuntingYard(tokensInfix, tokensRPN);
//        std::cout << "Answer: " << countRPN(tokensRPN) << "\n";
    }
    catch(Error &e)
    {
        std::cerr << e.what() << "\n";
        exit(-1);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(-1);
    }

    return 0;
}