//���α׷� ���� <������� ���� ���α׷�>

//��� 1. ���°���
//��� 2. �Ա�
//��� 3. ���
//��� 4. ��ü�� �ܾ���ȸ\

//���� 1. ������ ���¹�ȣ�� ��ø���� �ʴ´� (�ߺ��˻縦 ���� �ʴ´�)
//���� 2. �Ա� �� ��ݾ��� ������ 0���� ũ�� (�Ա� �� ��ݾ��� �����˻縦 ���� �ʴ´�)
//���� 3. ���� ���������� ���¹�ȣ, ���̸�, ���� �ܾ��� ���� �� �����Ѵ�.
//���� 4. �� �̻��� �� ���� ������ ���� �迭�� ����Ѵ�.
//���� 5. ���¹�ȣ�� ������ �����̴�.

#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN = 20;//const�� ������ �ʴ� ������ ������ �� ����.

void ShowMenu();//�޴����
void MakeAccount();//���°����� ���� �Լ�
void DepositMoney();//�Ա�
void WithdrawMoney();//���
void ShowAllAccInfo();//�ܾ���ȸ

enum {MAKE=1, DEPOSIT, WITHDRAW, INQUIRE, EXIT};//constó�� ������ �ʴ� ������ �����ϵ�, ������ ������ �ʿ並 �����ִ� ���
//MAKE=1, DEPOSIT=2, ..., EXIT=5���� �ϳ��� ����. ó�� MAKE�� 1�� �ʱ�ȸ�ϸ� �˾Ƽ� +1�ϸ鼭 �����Ѵ�.

typedef struct//�͸� ����ü
{
	int accID;//���¹�ȣ
	int balance;//�ܾ�
	char cusName[NAME_LEN];//���̸�
} Account;//����ü�ǻ��ο��̸�

Account accArr[100];//Account ������ ���� �迭. 100���� ���¸� ���� �� �ִ�.
int accNum = 0;//����� Account ��

//����ü ����
//struct ����ü�̸�
//{
//�������1��Ÿ�� �������1�̸�
//�������2��Ÿ�� �������2�̸�
//...
//} ����ü�����̸�;

//����ü ���� : ����ü�����̸�.��������̸�
//����ü �ʱ�ȭ : ����ü�����̸�={.�������1�̸�=�ʱ갪, .�������2�̸�=�ʱ갪, ...};, ����ü�����̸�={�������1�ʱ갪, �������2�ʱ갪, ...};

int main()
{
	int choice;

	while (1)//�׻� ��. �ڵ尡 ���ѷ����Ѵ�. �ݸ�, while (0)�� ���, �׻� �����̱⿡ �ڵ尡 ������� �ʴ´�.
	{
		ShowMenu();
		cout << "����: ";
		cin >> choice;
		cout << endl;

		switch (choice)//switch���� ��� ��ȣ �ȿ� ������ �ְ� ������ �ְ� �̿� �ش��ϴ� case�� ���� �Լ��� �ߵ��Ѵ�. if������ �����ϴ�.
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
			cout << "Illegal selection.." << endl;//�˻���?
		}
	}
	return 0;
}

void ShowMenu()
{
	cout << "------Menu------" << endl;
	cout << "1. ���°���" << endl;
	cout << "2. �Ա�" << endl;
	cout << "3. ���" << endl;
	cout << "4. �������� ��ü ���" << endl;
	cout << "5. ���α׷� ����" << endl;
}

void MakeAccount()
{
	int id;
	char name[NAME_LEN];
	int balance;

	for (int i = 0; i < 1; i++)
	{
		cout << "[���°���]" << endl;
		cout << "����ID: "; cin >> id;//���� ���缭 ���ü��� ���� �ϴ� ���
		for (int j = 0; j < accNum; j++)//���� id����
		{
			if (accArr[j].accID == id)
			{
				cout << "�̹� ������ ID�� �ֽ��ϴ�." << endl << endl;
				i -= 1;
				continue;
			}
		}
		if (i == 0)
		{
			cout << "�̸�: "; cin >> name;
			cout << "�Աݾ�: "; cin >> balance;
			cout << endl;
		}
	}

	accArr[accNum].accID = id;
	accArr[accNum].balance = balance;
	strcpy_s(accArr[accNum].cusName, name);//Visual Studio�� Ư¡ �� strcpy, scanf, fopen ���� �Լ��� ������ ���ܼ� �����ϵ��� �ʴ´�. �̴� ������ �����̴�.
	//�����ذ���1 : strcpy_s�� �ٲ㾴��. �� ���, ���� ��� ���.
	//�����ذ���2 : ó���� #define _CRT_SECURE_NO_WARNINGS�� �����Ѵ�. �̴� �������� ���ȿ� ���� ��� �����ϴ� �����̴�.
	//�����ذ���3 : ó���� #pragma warning(disable:4996)�� �����Ѵ�. �̴� �ش� ������ �����ϴ� �����̴�.
	accNum++;
}

void DepositMoney()
{
	int money;
	int id;
	cout << "[�Ա�]" << endl;
	cout << "����ID: "; cin >> id;
	cout << "�Աݾ�: "; cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i].accID == id)
		{
			accArr[i].balance += money;
			cout << "�ԱݿϷ�" << endl << endl;
			return;//�����Լ��� ���ư���. 0�� ������ �ʾұ� ������ �ʱ�ȭ���� �ʴ´�.
		}
	}
	cout << "��ȿ���� ���� ID�Դϴ�." << endl << endl;
}

void WithdrawMoney()
{
	int money;
	int id;
	cout << "[���]" << endl;
	cout << "����ID: "; cin >> id;
	cout << "��ݾ�: "; cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i].accID == id)
		{
			if (accArr[i].balance < money)
			{
				cout << "�ܾ׺���" << endl << endl;
				return;
			}
			accArr[i].balance -= money;
			cout << "��ݿϷ�" << endl << endl;
			return;
		}
	}
	cout << "��ȿ���� ���� ID�Դϴ�." << endl << endl;
}

void ShowAllAccInfo()
{
	for (int i = 0; i < accNum; i++)
	{
		cout << "����ID: " << accArr[i].accID << endl;
		cout << "�̸�: " << accArr[i].cusName << endl;
		cout << "�ܾ�: " << accArr[i].balance << endl << endl;
	}
}