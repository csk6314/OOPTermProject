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
	cout << "���� : ";
	getline(cin,ops);
	try {
		postfix = convert_to_postFix(ops);
		//cout << postfix << endl;
		result = getResult(postfix);
	}
	catch (int e) {
		switch (e) {
		case 0:
			cout << "���� �߻� : 0���� ���� �� �����ϴ�."<< endl;
			exit(0);
			break;
		case 1:
			cout << "���� �߻� : �ǿ����ڸ� ã�� �� �����ϴ�.(�ǿ����� ���� �����մϴ�)" << endl;
			exit(0);
			break;
		case 2:
			cout << "���� �߻� : �ǿ����ڿ� ���ڰ� �ƴ� ���� �����Ǿ����ϴ�." << endl;
			exit(0);
			break;
		case 3:
			cout << "���� �߻� : ��ȣ���� ���� �ʽ��ϴ�." << endl;
			exit(0);
			break;
		default:
			break;
		}
	}
	catch (std::out_of_range& e) {
		cout << "���� �߻� : " <<"���� ������ �ʰ��Ͽ����ϴ�. ( "<<e.what() << " )" << endl;
	}
	catch (std::invalid_argument& e) {
		cout << "���� �߻� : " << "�ǿ����ڿ� ���������� ���� �����մϴ�. ( "<<e.what()<<" )" << endl;
	}
	cout << "��� : " <<result << endl;
}	