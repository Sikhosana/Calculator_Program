// EvaluatingMathematicalExpressions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//this program evaluates mathematical expressions including parentesized ones of the type
// 4 - 7 + (4 * 6) etc
#include "pch.h"
#include <iostream>
#include "myStack.h"
#include <cctype>
#include <cstring>
using namespace sikhosana;
using namespace std;

int precedence(char op)
{
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
	return 0;
}
void evaluateTops(STACK<double>& nums, STACK<char>& operators)
{
	double num1 = nums.top();
	nums.pop();
	double num2 = nums.top();
	nums.pop();
	switch (operators.top())
	{
	case '+':
		nums.push(num2 + num1);
		break;
	case '-':
		nums.push(num2 - num1);
		break;
	case '*':
		nums.push(num2 * num1);
		break;
	case '/':
		nums.push(num2 / num1);
		break;
	}
	operators.pop();
}
double readAndEvaluate(istream& ins)
{
	char DECIMAL = '.';
	double num;
	char symbol;
	STACK<double> numbers;
	STACK<char> operations;

	while (ins && ins.peek() != '\n')
	{
		if (isdigit(ins.peek()) || (ins.peek() == DECIMAL))
		{
			ins >> num;
			numbers.push(num);
		}
		else if (ins.peek() == '(')
		{
			ins >> symbol;
			operations.push(symbol);
		}
		else if (ins.peek() == ')')
		{
			while (operations.top() != '(')
			{
				evaluateTops(numbers, operations);
			}
			ins >> symbol; //note that not removing the ')' from the stream will cause a fatal recursion that will 
						   //result in stack overflow or underflow
			operations.pop(); //this is us popping the left parenthesis
		}
		else if (strchr("+-/*", ins.peek()) != NULL)
		{
			while (!operations.empty() && (precedence(operations.top()) >= precedence(ins.peek())))
			{
				evaluateTops(numbers, operations);
			}
			ins >> symbol;
			operations.push(symbol);
		}
		else
			ins.ignore();
	}
	while (!operations.empty())
	{
		evaluateTops(numbers, operations);
	}
	return numbers.top();
}
int main()
{
	char reply;
	do
	{
		system("CLS");
		std::cout << "Enter your problem: " << std::endl;
		cout << readAndEvaluate(cin) << endl;
		cout << "Do you have another problem? y/n" << std::endl;
		cin >> reply;
		cin.ignore();
	} while (reply == 'y' || reply == 'Y');

	return 0;
}