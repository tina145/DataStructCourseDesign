#pragma once
//停车场（模拟）
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <Windows.h>

//车的属性
class Car
{
	//车名
	std::string id;
	//停车时间
	std::string time;
	//停车费用
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

//停车场属性
class Line
{
	//停车场
	std::stack<Car> container;
	//临时容器
	std::stack<Car> temp;
	//在外面等待的车辆
	std::queue<Car> wait;
	//停车场最大容积
	int maxsize;
public:
	//停一辆车
	virtual void add(Car car);
	//开走一辆车
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
	//有空位直接停进去，没有则停在外面等待
	int n = container.size();
	if (n >= maxsize)
	{
		wait.emplace(car);
		show();
		std::cout << "车位不足，等待中\n";
	}
	else
	{
		container.emplace(car);
		show();
		std::cout << "停车成功\n";
	}
	
}

void Line::pop(std::string car)
{
	if (container.empty())
	{
		std::cout << "停车场为空\n";
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
	std::cout << "出库成功\n";
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
	std::cout << "\t\t\t停车场内：" << "\t\t\t等待中：\n";
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