#pragma once
//˳����ң����ֲ��ң���ϣ�����
#include "Line.h"
#include <vector>
#include <unordered_map>

class Find : public Line
{
	//˳�򡢶��ֲ�������
	std::vector<Car> container;
	//��ϣ����
	std::unordered_map<std::string, Car> hash;
public:
	void add(Car car);

	//˳��O(n)
	void order(std::string s)const;

	//����O(logn)
	void binary(std::string s)const;

	//��ϣO(1)
	void hashfind(std::string s)const;

	//����ǰ����
	void sor()
	{
		sort(container.begin(), container.end(), [&](const auto& a, const auto& b)->bool 
			{
				if (a.getid().size() == b.getid().size())
					return a.getid() < b.getid();
				return a.getid().size() < b.getid().size();
			});
	}
};

void Find::add(Car car)
{
	container.emplace_back(car);
	hash[car.getid()] = car;
}

void Find::order(std::string s)const
{
	for (const auto& i : container)
		if (i.getid() == s)
			return;
}

void Find::binary(std::string s)const
{
	int left = 0, right = container.size() - 1;
	while (left + 1 < right)
	{
		auto mid = left + (right - left) / 2;
		if (container[mid].getid() == s)
			return;
		else if (container[mid].getid() < s)
			left = mid;
		else
			right = mid;
	}
}

void Find::hashfind(std::string s)const
{
	if (hash.count(s))
		return;
}