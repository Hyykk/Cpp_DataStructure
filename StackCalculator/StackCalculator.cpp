// 2020741067 홍윤교 자료구조 HW2
// Visual Studio 2022

#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

string InfixToPostfix(string input);
void Calculate(string postfix);
int priority(char op);

int main(void) {
	string input;

	while (1) {
		cin >> input;
		// if input is "EOI", break the while
		if (input == "EOI" || input == "eoi") {
			break;
		}
		// print postfix to test that program run correctly
		// cout << InfixToPostfix(input) << endl;
		Calculate(InfixToPostfix(input));
	}
	return 0;
}
// infix -> postfix
string InfixToPostfix(string input) {
	stack<char> operations;
	string postfix;
	char ch;

	for (int i = 0; i < input.length(); i++) {
		ch = input[i];

		// if number or .
		if (isdigit(ch) || ch == '.') {
			postfix += ch;
		}
		// if left parenthesis
		else if (ch == '(') {
			// push left parenthesis
			operations.push(ch);
		}
		// if right parenthesis
		else if (ch == ')') {
			while (!operations.empty() && operations.top() != '(') {
				// if operations stack has {, [ not a (
				// unbalanced parenthesis
				if (operations.top() == '{' || operations.top() == '[' || operations.empty()) {
					return "unbalanced parenthesis";
				}
				postfix += operations.top();
				operations.pop();
				// if no '('
				if (operations.empty()) {
					return "unbalanced parenthesis";
				}
			}
			// if no '('
			if (operations.empty()) {
				return "unbalanced parenthesis";
			}
			operations.pop();	// pop '('
		}
		// if left parenthesis
		else if (ch == '{') {
			operations.push(ch);
		}
		// if right parenthesis
		else if (ch == '}') {
			while (operations.top() != '{') {
				if (operations.top() == '(' || operations.top() == '[' || operations.empty()) {
					return "unbalanced parenthesis";
				}
				postfix += operations.top();
				operations.pop();
				if (operations.empty()) {
					return "unbalanced parenthesis";
				}
			}
			if (operations.empty()) {
				return "unbalanced parenthesis";
			}
			operations.pop();	// pop '{'
		}
		// if left parenthesis
		else if (ch == '[') {
			operations.push(ch);
		}
		// if right parenthesis
		else if (ch == ']') {
			while (operations.top() != '[') {
				if (operations.top() == '(' || operations.top() == '{' || operations.empty()) {
					return "unbalanced parenthesis";
				}
				postfix += operations.top();
				operations.pop();
				if (operations.empty()) {
					return "unbalanced parenthesis";
				}
			}
			if (operations.empty()) {
				return "unbalanced parenthesis";
			}
			operations.pop();	// pop '['
		}
		// if symbol
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
			postfix += ' ';
			// if operations is empty
			if (operations.empty()) {
				operations.push(ch);
			}
			else {
				// push symbol to operations stack according to symbol priority
				while (!operations.empty() && priority(operations.top()) >= priority(ch)) {
					postfix += operations.top();
					operations.pop();
				}
				operations.push(ch);
			}
		}
	}
	// if operations remain
	while (!operations.empty()) {
		if (operations.top() == '(' || operations.top() == '{' || operations.top() == '[') {
			return "unbalanced parenthesis";
		}
		postfix.push_back(operations.top());
		operations.pop();
	}
	return postfix;
}
// calculate postfix
void Calculate(string postfix) {
	if (postfix == "unbalanced parenthesis") {
		cout << "Error!: unbalanced parenthesis" << endl;
		return;
	}
	int i = 0, j = 0;
	stack<double> numbers;
	char number[100];
	char symbol;
	double num1, num2;
	double answer;

	while (postfix[i] != NULL) {
		// if number
		if (isdigit(postfix[i]) || postfix[i] == '.') {
			j = 0;
			while (isdigit(postfix[i])|| postfix[i] == '.') {
				number[j++] = postfix[i++];
			}
			numbers.push(atof(number));
			// reset number
			for (j = 0; j < 100; j++) {
				number[j] = NULL;
			}
		}
		// calculate according to symbol
		else if(postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/') {
			symbol = postfix[i++];
			num1 = numbers.top();
			numbers.pop();
			num2 = numbers.top();
			numbers.pop();
			switch(symbol){
				case '+': answer = num2 + num1; break;
				case '-': answer = num2 - num1; break;
				case '*': answer = num2 * num1; break;
				case '/':
					// if
					if (num1 == 0) {
						cout << "Error!: divide by zero" << endl;
						return;
					}
					answer = num2 / num1; break;
			}
			// push answer to numbers stack
			numbers.push(answer);
		}
		// if wrong input, ignore
		else {
			i++;
		}
	}
	// round off to the nearest thousandth and print answer
	cout << fixed;
	cout.precision(3);
	cout << answer << endl;
}
//get priority of symbol
int priority(char op) {
	switch (op) {
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return 0;
}