//프로그램 구현 <은행계좌 관리 프로그램>

//기능 1. 계좌개설
//기능 2. 입금
//기능 3. 출금
//기능 4. 전체고객 잔액조회\

//조건 1. 통장의 계좌번호는 중첩되지 않는다 (중복검사를 하지 않는다)
//조건 2. 입금 및 출금액은 무조건 0보다 크다 (입금 및 출금액의 오류검사를 하지 않는다)
//조건 3. 고객의 계좌정보는 계좌번호, 고객이름, 고객의 잔액을 저장 및 관리한다.
//조건 4. 둘 이상의 고객 정보 저장을 위해 배열을 사용한다.
//조건 5. 계좌번호는 정수의 형태이다.

#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN = 20;//const는 변하지 않는 변수를 선언할 때 쓴다.

void ShowMenu();//메뉴출력
void MakeAccount();//계좌개설을 위한 함수
void DepositMoney();//입금
void WithdrawMoney();//출금
void ShowAllAccInfo();//잔액조회

enum {MAKE=1, DEPOSIT, WITHDRAW, INQUIRE, EXIT};//const처럼 변하지 않는 변수를 선언하되, 일일히 지정할 필요를 없애주는 기능
//MAKE=1, DEPOSIT=2, ..., EXIT=5으로 하나씩 지정. 처음 MAKE에 1로 초기회하면 알아서 +1하면서 지정한다.

typedef struct//익명 구조체
{
	int accID;//계좌번호
	int balance;//잔액
	char cusName[NAME_LEN];//고객이름
} Account;//구조체의새로운이름

Account accArr[100];//Account 저장을 위한 배열. 100개의 계좌를 만들 수 있다.
int accNum = 0;//저장된 Account 수

//구조체 선언
//struct 구조체이름
//{
//멤버변수1의타입 멤버변수1이름
//멤버변수2의타입 멤버변수2이름
//...
//} 구조체변수이름;

//구조체 접근 : 구조체변수이름.멤버변수이름
//구조체 초기화 : 구조체변수이름={.멤버변수1이름=초깃값, .멤버변수2이름=초깃값, ...};, 구조체변수이름={멤버변수1초깃값, 멤버변수2초깃값, ...};

int main()
{
	int choice;

	while (1)//항상 참. 코드가 무한루프한다. 반면, while (0)의 경우, 항상 거짓이기에 코드가 실행되지 않는다.
	{
		ShowMenu();
		cout << "선택: ";
		cin >> choice;
		cout << endl;

		switch (choice)//switch문의 경우 괄호 안에 변수를 넣고 변수를 넣고 이에 해당하는 case를 나눠 함수를 발동한다. if문보다 간단하다.
		{
		case MAKE:
			MakeAccount();
			break;
		case DEPOSIT:
			DepositMoney();
			break;
		case WITHDRAW:
			WithdrawMoney();
			break;
		case INQUIRE:
			ShowAllAccInfo();
			break;
		case EXIT:
			return 0;
		default:
			cout << "Illegal selection.." << endl;//검색중?
		}
	}
	return 0;
}

void ShowMenu()
{
	cout << "------Menu------" << endl;
	cout << "1. 계좌개설" << endl;
	cout << "2. 입금" << endl;
	cout << "3. 출금" << endl;
	cout << "4. 계좌정보 전체 출력" << endl;
	cout << "5. 프로그램 종료" << endl;
}

void MakeAccount()
{
	int id;
	char name[NAME_LEN];
	int balance;

	for (int i = 0; i < 1; i++)
	{
		cout << "[계좌개설]" << endl;
		cout << "계좌ID: "; cin >> id;//열을 맞춰서 가시성을 좋게 하는 기술
		for (int j = 0; j < accNum; j++)//동일 id방지
		{
			if (accArr[j].accID == id)
			{
				cout << "이미 동일한 ID가 있습니다." << endl << endl;
				i -= 1;
				continue;
			}
		}
		if (i == 0)
		{
			cout << "이름: "; cin >> name;
			cout << "입금액: "; cin >> balance;
			cout << endl;
		}
	}

	accArr[accNum].accID = id;
	accArr[accNum].balance = balance;
	strcpy_s(accArr[accNum].cusName, name);//Visual Studio의 특징 상 strcpy, scanf, fopen 등의 함수에 오류가 생겨서 컴파일되지 않는다. 이는 안정성 때문이다.
	//오류해결방법1 : strcpy_s로 바꿔쓴다. 이 경우, 경고는 계속 뜬다.
	//오류해결방법2 : 처음에 #define _CRT_SECURE_NO_WARNINGS로 선언한다. 이는 안정성과 보안에 대한 경고를 무시하는 선언이다.
	//오류해결방법3 : 처음에 #pragma warning(disable:4996)을 선언한다. 이는 해당 에러를 무시하는 선언이다.
	accNum++;
}

void DepositMoney()
{
	int money;
	int id;
	cout << "[입금]" << endl;
	cout << "계좌ID: "; cin >> id;
	cout << "입금액: "; cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i].accID == id)
		{
			accArr[i].balance += money;
			cout << "입금완료" << endl << endl;
			return;//상위함수로 돌아간다. 0을 붙이지 않았기 때문에 초기화되지 않는다.
		}
	}
	cout << "유효하지 않은 ID입니다." << endl << endl;
}

void WithdrawMoney()
{
	int money;
	int id;
	cout << "[출금]" << endl;
	cout << "계좌ID: "; cin >> id;
	cout << "출금액: "; cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i].accID == id)
		{
			if (accArr[i].balance < money)
			{
				cout << "잔액부족" << endl << endl;
				return;
			}
			accArr[i].balance -= money;
			cout << "출금완료" << endl << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID입니다." << endl << endl;
}

void ShowAllAccInfo()
{
	for (int i = 0; i < accNum; i++)
	{
		cout << "계좌ID: " << accArr[i].accID << endl;
		cout << "이름: " << accArr[i].cusName << endl;
		cout << "잔액: " << accArr[i].balance << endl << endl;
	}
}