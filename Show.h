#pragma once
#include "NLine.h"
#include "Find.h"
#include <string>
#include <fstream>

class Show
{
public:
	static void show();

	void showpark();

	void randpark();

	void showfind();
};

void Show::show()
{
	BST<std::string> tree;
	while (1)
	{
		std::cout << "\t\t\t--------------------------------------------------" << std::endl;
		std::cout << "\t\t\t**********        1������Ԫ��           **********" << std::endl;
		std::cout << "\t\t\t*********         2����������Ԫ��       **********" << std::endl;
		std::cout << "\t\t\t**********        3���������           **********" << std::endl;
		std::cout << "\t\t\t**********        4��ǰ�����           **********" << std::endl;
		std::cout << "\t\t\t**********        5���������           **********" << std::endl;
		std::cout << "\t\t\t**********        6���������           **********" << std::endl;
		std::cout << "\t\t\t**********        0���˳�               **********" << std::endl;
		std::cout << "\t\t\t--------------------------------------------------" << std::endl;
		std::string select;
		std::cin >> select;
		if (select.size() != 1)
		{
			system("cls");
			continue;
		}

		switch (select[0] - '0')
		{
		case 1:
		{
			std::string s;
			std::cin >> s;
			tree.insert(s);
			break;
		}
		case 2:
		{
			std::string _s = "\n";
			std::getline(std::cin, _s);
			std::cout << "�ո�ָ����س�����\n";
			std::string s;
			std::getline(std::cin, s);
			std::string temp = "";
			for (const auto& i : s)
			{
				if (i != ' ')
					temp += i;
				else
				{
					if (!temp.empty())
						tree.insert(temp);
					temp.clear();
				}
			}
			if (!temp.empty())
				tree.insert(temp);
			break;
		}
		case 3:
			tree._print();
			break;
		case 4:
			tree.preorder();
			break;
		case 5:
			tree.inorder();
			break;
		case 6:
			tree.postorder();
			break;
		case 0:
			return;
		default:
			break;
		}
		system("pause");
		system("cls");
	}
}

void Show::showpark()
{
	std::string s;
	int siz;
	while (1)
	{
		std::cout << "����ͣ������С��";
		std::cin >> s;
		bool flag = 1;
		if (s.size() >= 10 || s[0] == '0')
		{
			std::cout << "error\n";
			continue;
		}
		for (const auto& v : s)
		{
			if (v < '0' || v > '9')
			{
				std::cout << "error\n";
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
		std::cout << "\t\t\t��ӣ�add\n";
		std::cout << "\t\t\tɾ����pop\n";
		std::cout << "\t\t\t��ʾ��Ϣ��show\n";
		std::cout << "\t\t\t�˳���exit\n";
		std::string select;
		std::cin >> select;
		if (select == "add")
		{
			std::string id, time, cost;
			while (1)
			{
				bool flag = 1;
				std::cout << "�����복���� ͣ��ʱ��, ���ã�";
				std::cin >> id >> time >> cost;
				for (auto& v : time)
				{
					if (v < '0' || v > '9')
					{
						std::cout << "error\n";
						flag = 0;
						break;
					}
				}
				for (auto& v : cost)
				{
					if (v < '0' || v > '9')
					{
						std::cout << "error\n";
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
			std::string id;
			std::cout << "�����복����";
			std::cin >> id;
			Parking.pop(id);
		}
		else if (select == "show")
		{
			Parking.show();
		}
		else if (select == "exit")
			return;
		else
			std::cout << "error\n";
		system("pause");
		system("cls");
	}
}

void Show::randpark()
{
	std::string s;
	int siz;
	while (1)
	{
		std::cout << "����ͣ������С��";
		std::cin >> s;
		bool flag = 1;
		if (s.size() >= 10 || s[0] == '0')
		{
			std::cout << "error\n";
			continue;
		}
		for (const auto& v : s)
		{
			if (v < '0' || v > '9')
			{
				std::cout << "error\n";
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
			parking.add(Car{ std::to_string(rand() % 10000), std::to_string(rand() % 10000), std::to_string(rand() % 10000) });
		else
			if (parking.getsize() != 0)
				parking.pop(rand() % parking.getsize());
	}
}

void Show::showfind()
{
	std::ofstream s;
	s.open("./1.csv", std::ios::app);
	Find f;
	for (int i = 0; i < 1000; i++)
		f.add(Car{ std::to_string(rand() % 1000), std::to_string(rand() % 1000), std::to_string(rand() % 1000) });

	auto t1 = clock();
	for (int i = 0; i < 1000; i++)
		f.order(std::to_string(rand() % 1000));
	auto t2 = clock();

	auto t5 = clock();
	for (int i = 0; i < 1000; i++)
		f.hashfind(std::to_string(rand() % 1000));
	auto t6 = clock();

	f.sor();

	auto t3 = clock();
	for (int i = 0; i < 1000; i++)
		f.binary(std::to_string(rand() % 1000));
	auto t4 = clock();



	s << "˳�����ʱ�䣺" << "," << t2 - t1 << "," << "ms" << ",";
	s << "���ֲ���ʱ�䣺" << "," << t4 - t3 << "," << "ms" << ",";
	s << "��ϣ����ʱ�䣺" << "," << t6 - t5 << "," << "ms\n";

	s.close();
}