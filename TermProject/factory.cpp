#include <string>
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