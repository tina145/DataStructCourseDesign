#pragma once
#include <iostream>
#include <memory>
#include <stack>
#include <vector>
#include <queue>

template<class _Tx>
class BST
{
private:
	template<class _Ty>
	struct node
	{
		node() {}
		node(_Ty m_val) : val(m_val) {}
		~node() {}
		_Ty val;
		std::unique_ptr<node<_Ty>> left;
		std::unique_ptr<node<_Ty>> right;
	};
	void preOrder(const node<_Tx>* _root)const;
	void inOrder(const node<_Tx>* _root)const;
	void postOrder(const node<_Tx>* _root)const;
	std::unique_ptr<node<_Tx>> root;
public:
	void preOrder()const;
	void inOrder()const;
	void postOrder()const;
	void preorder()const;
	void inorder()const;
	void postorder()const;
	void insert(const _Tx& _val);
	void _print()const;
};

template<class _Tx>
void BST<_Tx>::preOrder(const node<_Tx>* _root)const
{
	if (_root == nullptr)
		return;
	std::cout << _root->val << "   ";
	preOrder(_root->left.get());
	preOrder(_root->right.get());
}

template<class _Tx>
void BST<_Tx>::inOrder(const node<_Tx>* _root)const
{
	if (_root == nullptr)
		return;
	inOrder(_root->left.get());
	std::cout << _root->val << "   ";
	inOrder(_root->right.get());
}

template<class _Tx>
void BST<_Tx>::postOrder(const node<_Tx>* _root)const
{
	if (_root == nullptr)
		return;
	postOrder(_root->left.get());
	postOrder(_root->right.get());
	std::cout << _root->val << "   ";
}

template<class _Tx>
void BST<_Tx>::preOrder()const
{
	preOrder(root.get());
	std::cout << std::endl;
}

template<class _Tx>
void BST<_Tx>::inOrder()const
{
	inOrder(root.get());
	std::cout << std::endl;
}

template<class _Tx>
void BST<_Tx>::postOrder()const
{
	postOrder(root.get());
	std::cout << std::endl;
}

template<class _Tx>
void BST<_Tx>::preorder()const
{
	if (root.get() == nullptr)
		return;
	std::stack<node<_Tx>*> s;
	s.emplace(root.get());
	while (!s.empty())
	{
		auto temp = s.top();
		s.pop();
		std::cout << temp->val << "   ";
		if (temp->right.get())
			s.emplace(temp->right.get());
		if (temp->left.get())
			s.emplace(temp->left.get());
	}
	std::cout << std::endl;
}

template<class _Tx>
void BST<_Tx>::inorder()const
{
	if (root.get() == nullptr)
		return;
	std::stack<node<_Tx>*> s;
	auto temp = root.get();
	while (!s.empty() || temp)
	{
		while (temp)
		{
			s.emplace(temp);
			temp = temp->left.get();
		}
		temp = s.top();
		s.pop();
		std::cout << temp->val << "   ";
		temp = temp->right.get();
	}
	std::cout << std::endl;
}

template<class _Tx>
void BST<_Tx>::postorder()const
{
	if (root.get() == nullptr)
		return;
	std::stack<node<_Tx>*> s;
	std::vector<_Tx> out;
	s.emplace(root.get());
	while (!s.empty())
	{
		auto temp = s.top();
		s.pop();
		out.emplace_back(temp->val);
		if (temp->left.get())
			s.emplace(temp->left.get());
		if (temp->right.get())
			s.emplace(temp->right.get());
	}
	std::reverse(out.begin(), out.end());
	for (const auto& i : out)
		std::cout << i << "   ";
	std::cout << std::endl;
}

template<class _Tx>
void BST<_Tx>::insert(const _Tx& _val)
{
	if (root.get() == nullptr)
	{
		root = std::make_unique<node<_Tx>>(_val);
		return;
	}
	auto temp = root.get();
	auto cur = temp;
	while (temp != nullptr)
	{
		if (temp->val < _val)
		{
			cur = temp;
			temp = temp->right.get();
		}
		else
		{
			cur = temp;
			temp = temp->left.get();
		}
	}
	if (cur->val < _val)
		cur->right = std::make_unique<node<_Tx>>(_val);
	else
		cur->left = std::make_unique<node<_Tx>>(_val);
}

template<class _Tx>
void BST<_Tx>::_print()const
{
	if (root.get() == nullptr)
		return;
	std::queue<node<_Tx>*> q;
	std::vector<std::vector<node<_Tx>*>> container;
	q.emplace(root.get());
	while (!q.empty())
	{
		std::vector<node<_Tx>*> TheWorld;
		for (int i = 0, n = q.size(); i < n; i++)
		{
			auto temp = q.front();
			q.pop();
			if (!temp)
			{
				TheWorld.emplace_back(nullptr);
				continue;
			}
			TheWorld.emplace_back(temp);
			q.emplace(temp->left.get());
			q.emplace(temp->right.get());
		}
		container.emplace_back(TheWorld);
	}
	bool flag = 1;
	for (int i = 0, j = container[container.size() - 1].size(); i < j; i++)
		if (container[container.size() - 1][i])
			flag = 0;
	if (flag)
		container.pop_back();

	int k = 0;
	int n = container.size();
	auto m = pow(2, n - 1) * 4 - 4;

	while (k < n)
	{
		for (int i = 0, j = container[k].size(); i < j; i++)
		{
			if (i == 0)
				for (int i = 0; i < (pow(2, n - k - 1) * 4 - 4) * 2; i++)
					std::cout << " ";
			else
				for (int i = 0; i < (4 * pow(2, n - k - 1) - 1) * 4; i++)
					std::cout << " ";
			
			if (!container[k][i])
				std::cout << "NULL";
			else
				std::cout << container[k][i]->val;
		}
		std::cout << std::endl;
		k++;
	}

	
}