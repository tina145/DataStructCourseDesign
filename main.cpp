#include <iostream>
#include "Find.h"
#include <ctime>
#include <fstream>
using namespace std;

class Show
{
public:
	void showpark();

	void randpark();

	void showfind();
};

int main()
{
	srand((unsigned int)time(nullptr));
	Show s;
	s.randpark();
	return 0;
}

void Show::showpark()
{
	string s;
	int siz;
	while (1)
	{
		cout << "输入停车场大小：";
		cin >> s;
		bool flag = 1;
		if (s.size() >= 10 || s[0] == '0')
		{
			cout << "error\n";
			continue;
		}
		for (const auto& v : s)
		{
			if (v < '0' || v > '9')
			{
				cout << "error\n";
				flag = 0;
				break;
			}
		}
		if (flag)
		{
			long long rec = 0;
			for (const auto& i : s)
			{
				rec *= 10;
				rec += i - '0';
			}
			if (rec > INT_MAX || rec <= 0)
				flag = 0;
			else
			{
				siz = rec;
				break;
			}
		}
	}
	Line Parking(siz);

	while (1)
	{
		cout << "\t\t\t添加：add\n";
		cout << "\t\t\t删除：pop\n";
		cout << "\t\t\t显示信息：show\n";
		cout << "\t\t\t退出：exit\n";
		string select;
		cin >> select;
		if (select == "add")
		{
			string id, time, cost;
			while (1)
			{
				bool flag = 1;
				cout << "请输入车名， 停车时间, 费用：";
				cin >> id >> time >> cost;
				for (auto& v : time)
				{
					if (v < '0' || v > '9')
					{
						cout << "error\n";
						flag = 0;
						break;
					}
				}
				for (auto& v : cost)
				{
					if (v < '0' || v > '9')
					{
						cout << "error\n";
						flag = 0;
						break;
					}
				}
				if (flag)
					break;
			}

			Car car(id, time, cost);
			Parking.add(car);
		}
		else if (select == "pop")
		{
			string id;
			cout << "请输入车名：";
			cin >> id;
			Parking.pop(id);
		}
		else if (select == "show")
		{
			Parking.show();
		}
		else if (select == "exit")
			return;
		else
			cout << "error\n";
		system("pause");
		system("cls");
	}
}

void Show::randpark()
{
	string s;
	int siz;
	while (1)
	{
		cout << "输入停车场大小：";
		cin >> s;
		bool flag = 1;
		if (s.size() >= 10 || s[0] == '0')
		{
			cout << "error\n";
			continue;
		}
		for (const auto& v : s)
		{
			if (v < '0' || v > '9')
			{
				cout << "error\n";
				flag = 0;
				break;
			}
		}
		if (flag)
		{
			long long rec = 0;
			for (const auto& i : s)
			{
				rec *= 10;
				rec += i - '0';
			}
			if (rec > INT_MAX || rec <= 0)
				flag = 0;
			else
			{
				siz = rec;
				break;
			}
		}
	}
	Line parking(siz);
	while (1)
	{
		auto select = rand() % 2;
		if (select)
			parking.add(Car{ to_string(rand() % 10000), to_string(rand() % 10000), to_string(rand() % 10000) });
		else
			if (parking.getsize() != 0)
				parking.pop(rand() % parking.getsize());
	}
}

void Show::showfind()
{
	ofstream s;
	s.open("./1.csv", ios::app);
	Find f;
	for (int i = 0; i < 1000; i++)
		f.add(Car{ to_string(rand() % 1000), to_string(rand() % 1000),to_string(rand() % 1000) });

	auto t1 = clock();
	for (int i = 0; i < 1000; i++)
		f.order(to_string(rand() % 1000));
	auto t2 = clock();

	auto t5 = clock();
	for (int i = 0; i < 1000; i++)
		f.hashfind(to_string(rand() % 1000));
	auto t6 = clock();

	f.sor();

	auto t3 = clock();
	for (int i = 0; i < 1000; i++)
		f.binary(to_string(rand() % 1000));
	auto t4 = clock();

	

	s << "顺序查找时间：" << "," << t2 - t1 << "," << "ms" << ",";
	s << "二分查找时间：" << "," << t4 - t3 << "," << "ms" << ",";
	s << "哈希查找时间：" << "," << t6 - t5 << "," << "ms" << endl;

	s.close();
}