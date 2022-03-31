
#include <iostream>
#include "Operands.h"
#include <queue>
#include <stack>
#include <stdexcept>

using namespace std;

//function declaration
double Calculate(queue<Operand*> Q);

int main()
{
    //Main test-run
    queue<Operand*> RPN;
    RPN.push(new Number(6));
    RPN.push(new Number(8));
    RPN.push(new Add());
    RPN.push(new Square());
    RPN.push(new Number(102));
    RPN.push(new Number(53));
    RPN.push(new Subtract());
    RPN.push(new Divide());
    RPN.push(new Number(428));
    RPN.push(new Number(379));
    RPN.push(new Subtract());
    RPN.push(new Number(7));
    RPN.push(new Divide());
    RPN.push(new Add());
    cout << endl << " Input: 6, 8, +, ^2, 102, 53, -, /, 428, 379, -, 7, /, + " << endl;
    cout << " Print 11 Test-run: " << Calculate(RPN) << endl;

    queue<Operand*> a;
    a.push(new Number(2));
    a.push(new Number(1));
    a.push(new Number(6));
    a.push(new Multiply());
    a.push(new Subtract());

    //Prints -4
    cout << endl;
    cout << " Input: 2 1 6 * - = " << Calculate(a) << endl << endl;

    queue<Operand*> b;
    b.push(new Number(1));
    b.push(new Number(2));
    b.push(new Add());

    //prints 3
    cout << " Input: 1 2 + = " << Calculate(b) << endl << endl;

    //Testing exceptions handling
    queue<Operand*> c;
    c.push(new Number(1));
    c.push(new Add());
    cout << " Input: 1 + " << endl;
    try {
        Calculate(c);
    }
    catch (invalid_argument ia) {
        cerr << " Error:" << ia.what() << endl;
    }
    cout << endl;

    queue<Operand*> d;
    d.push(new Number(1));
    d.push(new Number(0));
    d.push(new Divide());

    cout << " Input: 1 0 / " << endl;
    try {
        Calculate(d);
    }
    catch (invalid_argument ia) {
        cerr << " Error:" << ia.what() << endl<< endl;
    }

    queue<Operand*> e;
    e.push(new Divide());

    cout << " Input: / " << endl;
    try {
        Calculate(e);
    }
    catch (invalid_argument ia) {
        cerr << " Error:" << ia.what() << endl;
    }
    cout << endl;

    //Clean and quit
    system("pause>0");
    return 0;
}

//function implementation
double Calculate(queue<Operand*>Q) {

    stack<Number*> Nums;

    //Defining a while loop to keep the program running until the queue is empty.
    while (!Q.empty()) {
        Operand* value = Q.front();
        Q.pop();

        //verify if the inputted value is a number.
        Number* number = dynamic_cast<Number*>(value);
        if (number != NULL) {
            //if number push it to the stack
            Nums.push(number);
            continue;
        }

        //Check for Addition operand, 
        // then pop out the two values in the stack
        //and store the result only.
        Add* add = dynamic_cast<Add*>(value);
        if (add != NULL) {
            if (Nums.size() < 2)
                throw invalid_argument(" invalid input");
            Number* operand02 = Nums.top();
            Nums.pop();
            Number* operand01 = Nums.top();
            Nums.pop();
            Nums.push(new Number(operand01->value + operand02->value));
            continue;
        }


        //Check for Subtraction operand, 
        // then pop out the two values in the stack
        //and store the result only.
        Subtract* subtract = dynamic_cast<Subtract*>(value);
        if (subtract != NULL) {
            if (Nums.size() < 2)
                throw invalid_argument(" invalid input");
            Number* operand02 = Nums.top();
            Nums.pop();
            Number* operand01 = Nums.top();
            Nums.pop();
            Nums.push(new Number(operand01->value - operand02->value));
            continue;
        }

        //Check for Multiplication operand, 
        // then pop out the two values in the stack
        //and store the result only.
        Multiply* multiply = dynamic_cast<Multiply*>(value);
        if (multiply != NULL) {
            if (Nums.size() < 2)
                throw invalid_argument(" invalid input");
            Number* operand02 = Nums.top();
            Nums.pop();
            Number* operand01 = Nums.top();
            Nums.pop();
            Nums.push(new Number(operand01->value * operand02->value));
            continue;
        }

        //Check for Division operand, 
        // then pop out the two values in the stack
        //and store the result only.
        Divide* divide = dynamic_cast<Divide*>(value);
        if (divide != NULL) {
            if (Nums.size() < 2)
                throw invalid_argument(" invalid input");
            Number* operand02 = Nums.top();
            Nums.pop();
            Number* operand01 = Nums.top();
            Nums.pop();
            if (operand02->value == 0)
                throw invalid_argument(" Cannot divide by zero");
            Nums.push(new Number(operand01->value / operand02->value));
            continue;
        }

        //Check for Squaring operand, 
        // then pop out the stored value in the stack
        //and store the result only.
        Square* square = dynamic_cast<Square*>(value);
        if (square != NULL) {
            if (Nums.size() < 1)
                throw invalid_argument(" invalid input");
            Number* operand01 = Nums.top();
            Nums.pop();
            Nums.push(new Number(operand01->value * operand01->value));
            continue;
        }

        //if an invalid Operand is detected throw an exception
        throw invalid_argument("invalid operand");
    }

    if (Nums.size() != 1)
        throw invalid_argument("invalid input");
    else {
        Number* value = Nums.top();
        Nums.pop();
        return value->value;
    }
}