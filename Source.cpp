#include <iostream>
#include <math.h>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <math.h>

using namespace std;

struct Lecsema
{
	char Cheker; // 'c' -cos ; 's' - sin; 't' - tg; 'e' - exp; '^' - степень, 'p' - переменная 
	double value;
};

int Rang(char Operator) {
	if (Operator == '^') {
		return 3;
	}
	if (Operator == 'c' || Operator == 's' || Operator == 't' || Operator == 'e' || Operator == 'l') {
		return 3;
	}
	if (Operator == '/' || Operator == '*') {
		return 2;
	}
	if(Operator == '-' || Operator == '+') {
		return 1;
	}
	else
	{
		return 0;
	}
}

queue<Lecsema> Queue;
stack<Lecsema> Stack;


int main() {
	char symbol;
	int flag = 1;
	cout << "Write some expression:";
	Lecsema Item;
	char firstsymbol;
	bool variable = false;
	bool trig = false;
	while (true)
	{
		symbol = cin.peek();
		if (symbol == '\n') break;
		if ((symbol == '-' && flag) || (symbol >= '0' && symbol <= '9')) {
			if (symbol == '-' && flag) {
				Item.value = -1;
				Item.Cheker = 0;
				Queue.push(Item);
				Item.Cheker = '*';
				Stack.push(Item);
				cin.get();
				continue;
			}
			cin >> Item.value;
			Item.Cheker = 0;
			Queue.push(Item);
			flag = 0;
			continue;
		}
		if (symbol >= 'A' && symbol <= 'z' && symbol != 'x' && symbol != '^') {
			char symb;
			char forwrite;
			string allChar;
			string funct;
			symb = cin.peek();
			firstsymbol = symb;
			while (symb != '(' || (symb < '0' && symb>'9')) {
				cin.get(forwrite);
				if (forwrite != ' ') {
					funct += forwrite;
				}
				allChar += forwrite;
				symb = cin.peek();
			}
			if (allChar != funct && (funct != "cos" || funct != "sin"
				|| funct != "tg" || funct != "log"
				|| funct != "ln" || funct != "exp" || funct != "e")) {
				cerr << "Error from functions!!";
				exit(0);
			}
			Item.Cheker = firstsymbol;
			Stack.push(Item);
			symbol = symb;
		}
		if (symbol == 'x') {
			Item.Cheker = 'p';
			Queue.push(Item);
			variable = true;
			flag = 0;
		}
		if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^') {
			while (true)
			{
				int rang = 0;
				if (Stack.size() > 0) {
					rang = Rang(Stack.top().Cheker);
				}
				if (rang < Rang(symbol) || Stack.size() == 0) {
					Item.Cheker = symbol;
					Stack.push(Item);
					break;
				}

				Queue.push(Stack.top());
				Stack.pop();
			}
			flag = 1;
		}
		if (symbol == '(') {
			Item.Cheker = symbol;
			Stack.push(Item);
			flag = 1;
		}
		if (symbol == ')') {
			if (Stack.size() == 0)
			{
				cerr << "\nError () ";
				return 0;
			}
			bool flag1 = true;
			while (Stack.size() > 0) {
				if (Stack.top().Cheker != '(')
				{
					Queue.push(Stack.top());
					Stack.pop();
					trig = false;
				}
				else {
					Stack.pop();
					flag1 = false;
					break;
				}
			}
			if (flag1)
			{
				cerr << "\nError () ";
				return 0;
			}
			flag = 0;
		}
		if (symbol != ' ' && symbol != '(' && symbol != ')' && 
			!(symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^') && symbol != 'x') {
			cerr << "error from expression!";
			exit(0);
		}
		cin.get();
	}

	double per;

	if (variable) {
		cout << "X=";
		cin >> per;
	}

	queue<Lecsema> NewQueue;
	while (!Queue.empty()) {
		if (Queue.front().Cheker == 'p') {
			Item.Cheker = 0;
			Item.value = per;
			NewQueue.push(Item);
		}
		else
		{
			NewQueue.push(Queue.front());
		}
		Queue.pop();
	}

	while (Stack.size() > 0)
	{
		NewQueue.push(Stack.top());
		Stack.pop();
	}

	auto forprint = NewQueue;

	while (!forprint.empty()) {
		if (forprint.front().Cheker == 0) {
			cout << forprint.front().value;
		}
		else
		{
			cout << forprint.front().Cheker;
		}
		forprint.pop();
	}

	while (!NewQueue.empty()) {
		if (NewQueue.front().Cheker == 0) {
			Stack.push(NewQueue.front());
			NewQueue.pop();
		}

		else
		{
			double x, y, ans;
			if (Stack.empty()) {
				cerr << "Error. We have some problem!!";
				exit(0);
			}

			if (Stack.top().Cheker) {
				cerr << "Error. Fuck this world!!";
				exit(0);
			}
			y = Stack.top().value;
			Stack.pop();


			if (Stack.empty() && (NewQueue.front().Cheker!='c' && NewQueue.front().Cheker != 's' && NewQueue.front().Cheker != 't' && NewQueue.front().Cheker != 'l' && NewQueue.front().Cheker != 'e')) {
				cerr << "Error";
				exit(0);
			}
			if ((NewQueue.front().Cheker == 't' || NewQueue.front().Cheker == 'c' || NewQueue.front().Cheker == 's' || NewQueue.front().Cheker == 'l' || NewQueue.front().Cheker == 'e')) {
				switch (NewQueue.front().Cheker)
				{
				case 'c': ans = cos(y);break;
				case 's': ans = sin(y);break;
				case 't': ans = tan(y);break;
				case 'l': ans = log(y);break;
				case 'e': ans = exp(y);break;
				default:
					cerr << "\nerroe";
					return 0;
				}
				NewQueue.pop();
				Item.Cheker = 0;
				Item.value = ans;
				Stack.push(Item);
				continue;
			}

			x = Stack.top().value;
			Stack.pop();
			switch (NewQueue.front().Cheker)
			{
			case '+': ans = x + y;break;
			case '-': ans = x - y;break;
			case '*': ans = x * y;break;
			case '/': ans = x / y;break;
			case '^': ans = pow(x,y);break;
			default:
				cerr << "\nerroe";
				return 0;
			}
			NewQueue.pop();
			Item.Cheker = 0;
			Item.value = ans;
			Stack.push(Item);
		}
	}

	cout << "\nResult is:" << Stack.top().value;
}