#include <iostream>
#include <stack>
#include <string>
#include "func.h"
using namespace std;
int main() {
	string ops;
	string postfix;
	string seperator;
	int result = 0;
	cout << "계산식 : ";
	getline(cin,ops);
	try {
		postfix = convert_to_postFix(ops);
		//cout << postfix << endl;
		result = getResult(postfix);
	}
	catch (int e) {
		switch (e) {
		case 0:
			cout << "오류 발생 : 0으로 나눌 수 없습니다."<< endl;
			exit(0);
			break;
		case 1:
			cout << "오류 발생 : 피연산자를 찾을 수 없습니다.(피연산자 수가 부족합니다)" << endl;
			exit(0);
			break;
		case 2:
			cout << "오류 발생 : 피연산자에 숫자가 아닌 값이 감지되었습니다." << endl;
			exit(0);
			break;
		case 3:
			cout << "오류 발생 : 괄호쌍이 맞지 않습니다." << endl;
			exit(0);
			break;
		default:
			break;
		}
	}
	catch (std::out_of_range& e) {
		cout << "오류 발생 : " <<"값의 범위를 초과하였습니다. ( "<<e.what() << " )" << endl;
	}
	catch (std::invalid_argument& e) {
		cout << "오류 발생 : " << "피연산자에 비정상적인 값이 존재합니다. ( "<<e.what()<<" )" << endl;
	}
	cout << "결과 : " <<result << endl;
}	