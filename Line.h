#pragma once
//ͣ������ģ�⣩
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <Windows.h>

//��������
class Car
{
	//����
	std::string id;
	//ͣ��ʱ��
	std::string time;
	//ͣ������
	std::string cost;
public:
	Car(const std::string& ID, const std::string& Time, const std::string& Cost);
	Car() {}
	bool operator==(Car car);

	std::string getid()const
	{
		return id;
	}
};

//ͣ��������
class Line
{
	//ͣ����
	std::stack<Car> container;
	//��ʱ����
	std::stack<Car> temp;
	//������ȴ��ĳ���
	std::queue<Car> wait;
	//ͣ��������ݻ�
	int maxsize;
public:
	//ͣһ����
	virtual void add(Car car);
	//����һ����
	void pop(std::string car);
	void pop(int index);

	size_t getsize() 
	{ 
		return container.size(); 
	}

	Line(int max_size);
	Line() {}

	virtual ~Line();

	virtual void show()const;
};

Car::Car(const std::string& ID, const std::string& Time, const std::string& Cost) : id(ID), time(Time), cost(Cost) {}

Line::~Line() {}

bool Car::operator==(Car car)
{
	return this->cost == car.cost && this->id == car.id && this->time == car.time;
}

Line::Line(int max_size) : maxsize(max_size) {}


void Line::add(Car car)
{
	system("cls");
	
	show();
	Sleep(100);
	system("cls");
	//�п�λֱ��ͣ��ȥ��û����ͣ������ȴ�
	int n = container.size();
	if (n >= maxsize)
	{
		wait.emplace(car);
		show();
		std::cout << "��λ���㣬�ȴ���\n";
	}
	else
	{
		container.emplace(car);
		show();
		std::cout << "ͣ���ɹ�\n";
	}
	
}

void Line::pop(std::string car)
{
	if (container.empty())
	{
		std::cout << "ͣ����Ϊ��\n";
		return;
	}
	system("cls");

	show();
	Sleep(100);
	system("cls");
	while (!container.empty())
	{
		auto tmp = container.top();
		container.pop();
		if (tmp.getid() == car)
		{
			while (!temp.empty())
			{
				container.emplace(temp.top());
				temp.pop();
			}
			if (!wait.empty())
			{
				container.emplace(wait.front());
				wait.pop();
			}
			break;
		}
		temp.emplace(tmp);
		
	}
	if (!temp.empty())
	{
		while (!temp.empty())
		{
			container.emplace(temp.top());
			temp.pop();
		}
	}
	show();
	std::cout << "����ɹ�\n";
}

void Line::show()const
{
	auto tp = container;
	std::stack<Car> t1;
	while (!tp.empty())
	{
		t1.emplace(tp.top());
		tp.pop();
	}
	auto t2 = wait;
	std::cout << "\t\t\tͣ�����ڣ�" << "\t\t\t�ȴ��У�\n";
	while (!t1.empty() || !t2.empty())
	{
		std::cout << "\t\t\t";

		if (!t1.empty())
		{
			std::cout << t1.top().getid();
			t1.pop();
		}

		std::cout << "\t\t\t\t";

		if (!t2.empty())
		{
			std::cout << t2.front().getid();
			t2.pop();
		}
			
		std::cout << std::endl;
	}
}

void Line::pop(int index)
{
	auto t = container;
	if (t.empty())
		return;
	while (index--)
		t.pop();
	pop(t.top().getid());
}