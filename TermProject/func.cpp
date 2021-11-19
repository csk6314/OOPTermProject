#include <iostream>
#include <string>
#include <stack>
#include <string>

//Factory Pattern
class Operator {
public:
	virtual int calc(int a, int b) = 0;
};
class Plus :public Operator {
	int calc(int a, int b) {
		return a + b;
	}
};
class Subtract :public Operator {
	int calc(int a, int b) {
		return a - b;
	}
};
class Multiply :public Operator {
	int calc(int a, int b) {
		return a * b;
	}
};
class Divide :public Operator {
	int calc(int a, int b) {
		if (b == 0) { throw 0; }
			return a / b;
	}
};
class OperatorFactory {
public:
	Operator* getOperator(std::string operType) {
		if (!operType.compare("+")) {
			return new Plus();
		}
		else if (!operType.compare("-")) {
			return new Subtract();
		}
		else if (!operType.compare("*")) {
			return new Multiply();
		}
		else if (!operType.compare("/")) {
			return new Divide();
		}
		else {
			return NULL;
		}

	}
};

int priority(char op) {
	if (op == '*' || op == '/') {
		return 2;
	}
	else if (op == '+' || op == '-') {
		return 1;
	}
	else if (op == '(' || op == ')') {
		return 0;
	}
	else {
		return -1;
	}
}

std::string toDemical(std::string op) {
	std::string s = op.substr(0, 2);
	if (!s.compare("0x")) {
		std::string v = op.substr(2);
		for (int i = 0; i < v.length(); i++) {
			if (!isdigit(v[i]) && !(tolower(v[i])>='a'&&tolower(v[i])<='f')) {
				throw 2;
			}
		}
		int a = stoi(v, nullptr, 16);
		return std::to_string(a);
	}
	else if (!s.compare("0b")) {
		int a = stoi(op.substr(2), nullptr, 2);
		return std::to_string(a);
	}
	else {
		for (int i = 0; i < op.length(); i++) {
			if (!isdigit(op[i])) {
				throw 2;
			}
		}
		return op;
	}
	
}

std::string convert_to_postFix(std::string ops) {
	std::string seperator;
	std::string postfix;
	std::stack<char> opStack;
	for (int i = 0; ops[i]; i++) {
		int p = priority(ops[i]);
		if (ops[i] == '+' || ops[i] == '-' || ops[i] == '*' || ops[i] == '/') {
			if (!seperator.empty()) {
				postfix += toDemical(seperator) + " ";
				seperator.clear();
			}
			while (!opStack.empty() && priority(opStack.top()) >= p) {
				postfix.push_back(opStack.top());
				postfix.push_back(' ');
				opStack.pop();
			}
			opStack.push(ops[i]);
		}
		else if (ops[i] == '(') {
			opStack.push(ops[i]);
		}
		else if (ops[i] == ')') {
			if (!seperator.empty()) {
				postfix += toDemical(seperator) + " ";
				seperator.clear();
			}
			while (!opStack.empty() && priority(opStack.top()) != 0) {
				postfix.push_back(opStack.top());
				postfix.push_back(' ');
				opStack.pop();
			}
			if (opStack.empty()) {
				throw 3;
			}
			opStack.pop();
		}
		else {
			seperator.push_back(ops[i]);
		}
	}
	while (!seperator.empty()) {
		postfix += toDemical(seperator) + " ";
		seperator.clear();
	}
	while (!opStack.empty()) {
		if (opStack.top() == '(') {
			throw 3;
		}
		postfix.push_back(opStack.top());
		postfix.push_back(' ');
		opStack.pop();
	}
	return postfix;
}

int getResult(std::string postfix) {
	std::stack<std::string> calc_stack;
	size_t pos = 0;
	std::string token;
	int second = 0;
	int first = 0;
	int res = 0;
	OperatorFactory* factory = new OperatorFactory();
	while ((pos = postfix.find(" ")) != std::string::npos) {
		token = postfix.substr(0, pos);
		Operator* oper;
		if ((oper = factory->getOperator(token)) != NULL) {
			if (calc_stack.empty()) {
				throw 1;
			}
			second = stoi(calc_stack.top(), nullptr, 10);
			calc_stack.pop();
			if (calc_stack.empty()) {
				throw 1;
			}
			first = stoi(calc_stack.top(), nullptr, 10);
			calc_stack.pop();
			res = oper->calc(first,second);
			calc_stack.push(std::to_string(res));
		}
		else {
			calc_stack.push(token);
		}
		postfix.erase(0, pos + 1);
	}
	return stoi(calc_stack.top(),nullptr,10);
}