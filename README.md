# datastructure
for the tutorial

/*지난번 프로그래밍에서 요구사항을 잘못 이해하여
1번을 여러번 선택하여 데이터를 누적할 수 있게 설계하였습니다.
본래의 요구사항도 만족하여 동작합니다.*/

#include<iostream>
#include<iomanip>
#include<cstring>

struct Subject
{
	char sub_name[30];
	char grade[10];
	int lecturehour;
	float gpa;
};

struct Student
{
	char stu_name[30];
	int stu_code;
	Subject subs[3];
	float gpa_avg;
	Student* next;
};

Student* listhead = NULL;

void PrintMenu()
{
	std::cout << "\n\n===== 메뉴 =====\n" << "1. 학생 성적 입력\n"
		<< "2. 전체 학생 성적 보기\n" << "3. 학생 이름 검색\n" << "4. 프로그램 종료\n"
		<< "\n원하는 기능을 입력하세요: ";
}

void CalcGPA(Subject& Sub)
{

	if (strcmp(Sub.grade, "A+") == 0)
		Sub.gpa = 4.5;
	else if (strcmp(Sub.grade, "A") == 0 || strcmp(Sub.grade, "A0") == 0)
		Sub.gpa = 4.0;
	else if (strcmp(Sub.grade, "B+") == 0)
		Sub.gpa = 3.5;
	else if (strcmp(Sub.grade, "B") == 0 || strcmp(Sub.grade, "B0") == 0)
		Sub.gpa = 3.0;
	else if (strcmp(Sub.grade, "C+") == 0)
		Sub.gpa = 2.5;
	else if (strcmp(Sub.grade, "C") == 0 || strcmp(Sub.grade, "C0") == 0)
		Sub.gpa = 2.0;
	else if (strcmp(Sub.grade, "D+") == 0)
		Sub.gpa = 1.5;
	else if (strcmp(Sub.grade, "D") == 0 || strcmp(Sub.grade, "D0") == 0)
		Sub.gpa = 1.0;
	else if (strcmp(Sub.grade, "F") == 0 || strcmp(Sub.grade, "F0") == 0)
		Sub.gpa = 0.0;
}

float CalcAVEGPA(Subject* Sub)
{
	return (Sub[0].gpa + Sub[1].gpa + Sub[2].gpa) / 3;
}

void push_data(Student* data, int i)
{
	std::cout << "\n* " << i << "번째 학생 이름과 학번을 입력하세요.\n" << "이름: ";
	std::cin >> data->stu_name;
	std::cout << "학번: ";
	std::cin >> data->stu_code;
	std::cout << "\n* 수강한 과목3개와 각 교과목명, 과목학점, 과목등급을 입력하세요.\n";
	std::cout << "교과목명: ";
	std::cin >> data->subs[0].sub_name;
	std::cout << "과목학점수: ";
	std::cin >> data->subs[0].lecturehour;
	std::cout << "과목등급(A+ ~ F): ";
	std::cin >> data->subs[0].grade;
	std::cout << "\n교과목명: ";
	std::cin >> data->subs[1].sub_name;
	std::cout << "과목학점수: ";
	std::cin >> data->subs[1].lecturehour;
	std::cout << "과목등급(A+ ~ F): ";
	std::cin >> data->subs[1].grade;
	std::cout << "\n교과목명: ";
	std::cin >> data->subs[2].sub_name;
	std::cout << "과목학점수: ";
	std::cin >> data->subs[2].lecturehour;
	std::cout << "과목등급(A+ ~ F): ";
	std::cin >> data->subs[2].grade;

	int j = 0;
	for (j = 0; j < 3; j++)
	{
		CalcGPA(data->subs[j]);
		data->subs[j].gpa = data->subs[j].lecturehour*data->subs[j].gpa;
	}
	data->gpa_avg = CalcAVEGPA(data->subs);
}

void push()
{
	Student* find = NULL;
	Student *first = (Student*)malloc(sizeof(Student));
	Student *second = (Student*)malloc(sizeof(Student));
	push_data(first, 1);
	push_data(second, 2);
	if (listhead == NULL)
	{
		listhead = first;
		first->next = second;
		second->next = NULL;
	}
	else
	{
		first->next = second;
		second->next = listhead;
		listhead = first;
	}
}

void PrintAllData(const Student* pSt, int StudentNum)
{
	int i = 0;
	std::cout << std::fixed;
	std::cout.precision(2);
	//Student* find = listhead;
	std::cout << "\n전체 학생 성적 보기" << "\n========================================";
	while (pSt != NULL)
	{

		std::cout << "\n이름: " << pSt->stu_name << "   학번: " << pSt->stu_code << "\n========================================\n";
		std::cout.width(10);
		std::cout << "과목명";
		std::cout.width(10);
		std::cout << "과목학점";
		std::cout.width(10);
		std::cout << "과목등급";
		std::cout.width(10);
		std::cout << "과목평점" << "\n========================================\n";
		for (i = 0; i < 3; i++)
		{
			std::cout.width(10);
			std::cout << pSt->subs[i].sub_name;
			std::cout.width(10);
			std::cout << pSt->subs[i].lecturehour;
			std::cout.width(10);
			std::cout << pSt->subs[i].grade;
			std::cout.width(10);
			std::cout << pSt->subs[i].gpa << std::endl;

		}

		std::cout << "========================================" << "\n\t\t\t\t평균평점" << pSt->gpa_avg;

		pSt = pSt->next;
	}
}

Student* StdSearch(Student* pSt, int StudentNum)
{
	char find_name[30];
	std::cout << "\n\n검색 할 학생 이름: ";
	std::cin >> find_name;
	while (pSt != NULL)
	{
		if (strcmp(pSt->stu_name, find_name) != 0)
			pSt = pSt->next;
		else
			return pSt;
	}
	return NULL;
}

void PrintOneData(const Student& rSt)
{
	int i;
	std::cout << "\n이름: " << rSt.stu_name << "   학번: " << rSt.stu_code << "\n========================================\n";
	std::cout.width(10);
	std::cout << "과목명";
	std::cout.width(10);
	std::cout << "과목학점";
	std::cout.width(10);
	std::cout << "과목등급";
	std::cout.width(10);
	std::cout << "과목평점" << "\n========================================\n";
	std::cout.width(10);
	for (i = 0; i < 3; i++)
	{
		std::cout.width(10);
		std::cout << rSt.subs[i].sub_name;
		std::cout.width(10);
		std::cout << rSt.subs[i].lecturehour;
		std::cout.width(10);
		std::cout << rSt.subs[i].grade;
		std::cout.width(10);
		std::cout << rSt.subs[i].gpa << std::endl;
	}
	std::cout << "========================================" << "\n\t\t\t\t평균평점" << rSt.gpa_avg;
}

void delete_list()
{
	Student* temp = listhead;
	while (listhead != NULL)
	{
		listhead = listhead->next;
		free(temp);
		temp = listhead;
	}
}

int main()
{
	int i = 0, menu = 0;

	while (1)
	{
		PrintMenu();
		std::cin >> menu;

		switch (menu)
		{
		case 1:
			push();
			break;
		case 2:
			if (listhead == NULL)
				std::cout << "\n학생이 존재하지 않습니다.\n";
			else
				PrintAllData(listhead, i);
			break;
		case 3:
			Student* search;
			search = StdSearch(listhead, 1);
			if (search == NULL)
				std::cout << "\n찾고자 하는 학생이 존재하지 않습니다.\n";
			else
				PrintOneData(search[0]);
			break;
		case 4:
			std::cout << "\n\n프로그램을 종료합니다.\n";
			delete_list();
			return 0;
		}
	}
}
