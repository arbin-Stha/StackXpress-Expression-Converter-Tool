#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <cmath>  // For pow function
#include <sstream>  // For stringstream
#include <cstdlib>

using namespace std;

// Function to check if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Function to get the precedence of an operator
int getPrecedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;  // Default precedence for non-operators
}

// Function to perform an operation
int performOperation(int operand1, int operand2, char op) {
    switch (op) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 != 0)
                return operand1 / operand2;
            else {
                cout << "Error: Division by zero." << endl;
                exit(1);
            }
        case '^':
            return static_cast<int>(pow(operand1, operand2));
        default:
            cout << "Error: Invalid operator." << endl;
            exit(1);
    }
}

// Function to convert infix to postfix
string infixToPostfix(const string& infix) {
    string postfix = "";
    stack<char> operators;
    vector<pair<string, string> > steps;

    for (int i = 0; i < infix.length(); ++i) {
        char c = infix[i];
        if (isalnum(c)) {
            postfix += c;
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            if (!operators.empty() && operators.top() == '(') {
                operators.pop();
            }
        } else if (isOperator(c)) {
            while (!operators.empty() && getPrecedence(c) <= getPrecedence(operators.top())) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
        steps.push_back({string(1, c), postfix});
    }

    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    cout << "Step\tInput\tOutput" << endl;
    for (int i = 0; i < steps.size(); ++i) {
        cout << i + 1 << "\t" << steps[i].first << "\t" << steps[i].second << endl;
    }

    return postfix;
}

// Function to convert infix to prefix
string infixToPrefix(const string& infix) {
    string prefix = "";
    stack<char> operators;
    vector<pair<string, string> > steps;

    for (int i = 0; i < infix.length(); ++i) {
        char c = infix[i];
        if (isalnum(c)) {
            prefix = c + prefix;  // Reverse order for operands
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                prefix = operators.top() + prefix;
                operators.pop();
            }
            if (!operators.empty() && operators.top() == '(') {
                operators.pop();
            }
        } else if (isOperator(c)) {
            while (!operators.empty() && getPrecedence(c) <= getPrecedence(operators.top())) {
                prefix = operators.top() + prefix;
                operators.pop();
            }
            operators.push(c);
        }
        steps.push_back({string(1, c), prefix});
    }

    while (!operators.empty()) {
        prefix = operators.top() + prefix;
        operators.pop();
    }

    cout << "Step\tInput\tOutput" << endl;
    for (int i = 0; i < steps.size(); ++i) {
        cout << i + 1 << "\t" << steps[i].first << "\t" << steps[i].second << endl;
    }

    return prefix;
}
//Function to convert prefix to infix
string prefixToInfix(const string& prefix) {
    stack<string> operandStack;
    vector<pair<string, string> > steps;

    for (int i = prefix.size() - 1; i >= 0; --i) {
        char c = prefix[i];
        if (isalnum(c)) {
            string operand(1, c);
            operandStack.push(operand);
        } else if (isOperator(c)) {
            string operand1 = operandStack.top();
            operandStack.pop();
            string operand2 = operandStack.top();
            operandStack.pop();
            string result = "(" + operand1 + c + operand2 + ")";
            operandStack.push(result);
        }
        steps.push_back({string(1, c), operandStack.top()});
    }

    string infixExpression = operandStack.top();

    cout << "Step\tInput\tOutput" << endl;
    for (int i = 0; i < steps.size(); ++i) {
        cout << i + 1 << "\t" << steps[i].first << "\t" << steps[i].second << endl;
    }

    return infixExpression;
}

// Function to convert postfix to infix
string postfixToInfix(const string& postfix) {
    stack<string> operandStack;
    vector<pair<string, string> > steps;

    for (int i = 0; i < postfix.length(); ++i) {
        char c = postfix[i];
        if (isalnum(c)) {
            operandStack.push(string(1, c));
        } else if (isOperator(c)) {
            string operand2 = operandStack.top();
            operandStack.pop();
            string operand1 = operandStack.top();
            operandStack.pop();
            string result = "(" + operand1 + c + operand2 + ")";
            operandStack.push(result);
        }
        steps.push_back({string(1, c), operandStack.top()});
    }

    string infixExpression = operandStack.top();

    cout << "Step\tInput\tOutput" << endl;
    for (int i = 0; i < steps.size(); ++i) {
        cout << i + 1 << "\t" << steps[i].first << "\t" << steps[i].second << endl;
    }

    return infixExpression;
}

// Function to convert prefix to postfix
string prefixToPostfix(const string& prefix) {
    stack<string> operandStack;
    vector<pair<string, string> > steps;

    for (int i = prefix.size() - 1; i >= 0; --i) {
        char c = prefix[i];
        if (isalnum(c)) {
            string operand(1, c);
            operandStack.push(operand);
        } else if (isOperator(c)) {
            string operand1 = operandStack.top();
            operandStack.pop();
            string operand2 = operandStack.top();
            operandStack.pop();
            string result = operand1 + operand2 + c;
            operandStack.push(result);
        }
        steps.push_back({string(1, c), operandStack.top()});
    }

    cout << "Step\tInput\tOutput" << endl;
    for (int i = steps.size() - 1; i >= 0; --i) {
        cout << steps.size() - i << "\t" << steps[i].first << "\t" << steps[i].second << endl;
    }

    return operandStack.top();
}

// Function to evaluate a postfix expression
int evaluatePostfix(const string& postfix) {
    stack<int> operandStack;
    vector<pair<string, string> > steps;

    for (int i = 0; i < postfix.length(); ++i) {
        char c = postfix[i];
        if (isdigit(c)) {
            int operand = c - '0';
            operandStack.push(operand);
        } else if (isOperator(c)) {
            int operand2 = operandStack.top();
            operandStack.pop();
            int operand1 = operandStack.top();
            operandStack.pop();
            int result = performOperation(operand1, operand2, c);
            operandStack.push(result);
        }
        stringstream ss;
        ss << operandStack.top();
        string operandStr = ss.str();
        steps.push_back(pair<string, string>(string(1, c), operandStr));
    }

    cout << "Step\tInput\tOutput" << endl;
    for (int i = 0; i < steps.size(); ++i) {
        cout << i + 1 << "\t" << steps[i].first << "\t" << steps[i].second << endl;
    }

    return operandStack.top();
}

int main() {
    int choice;
    string expression;
    do
    {
    

    cout << "Choose an option:" << endl;
    cout << "1. Infix to Postfix" << endl;
    cout << "2. Infix to Prefix" << endl;
    cout << "3. Prefix to Infix" << endl;
    cout << "4. Postfix to Infix" << endl;
    cout << "5. Prefix to Postfix" << endl;
    cout << "6. Postfix Evaluation" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    cout << "Enter the expression: ";
    cin.ignore();  // Clear the newline character
    getline(cin, expression);

    string result;

    switch (choice) {
        case 1:
            result = infixToPostfix(expression);
            cout << "Postfix Expression: " << result << endl;
            break;
        case 2:
            result = infixToPrefix(expression);
            cout << "Prefix Expression: " << result << endl;
            break;
        case 3:
            result = prefixToInfix(expression);
            cout << "Infix Expression: " << result << endl;
            break;
        case 4:
            result = postfixToInfix(expression);
            cout << "Infix Expression: " << result << endl;
            break;
        case 5:
            result = prefixToPostfix(expression);
            cout << "Postfix Expression: " << result << endl;
            break;
        case 6:
            result = (evaluatePostfix(expression));
            cout << "Evaluation Result: " << result << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
            return 1;
    }
    cout << "\nDo you want to perform another operation? (y/n)";

        cin >>stopApp;

    }while (toupper(stopApp) == 'Y');
    

    return 0;
}
