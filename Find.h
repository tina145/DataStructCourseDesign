#pragma once
//顺序查找，二分查找，哈希表查找
#include "Line.h"
#include <vector>
#include <unordered_map>

class Find : public Line
{
	//顺序、二分查找容器
	std::vector<Car> container;
	//哈希查找
	std::unordered_map<std::string, Car> hash;
public:
	void add(Car car);

	//顺序O(n)
	void order(std::string s)const;

	//二分O(logn)
	void binary(std::string s)const;

	//哈希O(1)
	void hashfind(std::string s)const;

	//二分前排序
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