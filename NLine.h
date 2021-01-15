#pragma once
#include <iostream>
#include <memory>
#include <string>
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
	size_t max_depth(const node<_Tx>* _root)const;
	size_t min_depth(const node<_Tx>* _root)const;
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
	bool isBST()const;
	size_t max_depth()const { return max_depth(root.get()); }
	size_t min_depth()const { return min_depth(root.get()); }
};

class Show
{
public:
	static void show();
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
size_t BST<_Tx>::max_depth(const node<_Tx>* _root)const
{
	if (_root == nullptr)
		return 0;
	return max(max_depth(_root->left.get()), max_depth(_root->right.get())) + 1;
}

template<class _Tx>
size_t BST<_Tx>::min_depth(const node<_Tx>* _root)const
{
	if (_root == nullptr)
		return 0;
	if (_root->left.get() == nullptr && _root->right.get() == nullptr)
		return 1;
	size_t mindepth = UINT_MAX;
	if (_root->left.get() != nullptr)
		mindepth = min(min_depth(_root->left.get()), mindepth);

	if (_root->right.get() != nullptr)
		mindepth = min(min_depth(_root->right.get()), mindepth);
	return mindepth + 1;
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
	q.emplace(root.get());
	while (!q.empty())
	{
		for (int i = 0, n = q.size(); i < n; i++)
		{
			auto temp = q.front();
			q.pop();
			std::cout << temp->val << "   ";
			if (temp->left.get())
				q.emplace(temp->left.get());
			if (temp->right.get())
				q.emplace(temp->right.get());
		}
		std::cout << std::endl;
	}
}

template<class _Tx>
bool BST<_Tx>::isBST()const
{
	auto temp = root.get();
	if (temp == nullptr)
		return true;
	std::stack<node<_Tx>*> s;
	std::vector<_Tx> v;
	while (!s.empty() || temp)
	{
		while (temp)
		{
			s.emplace(temp);
			temp = temp->left.get();
		}
		temp = s.top();
		s.pop();
		v.emplace_back(temp->val);
		temp = temp->right.get();
	}

	for (auto i = 1, n = v.size(); i < n; i++)
		if (v[i] <= v[i - 1])
			return false;

	return true;
}

void Show::show()
{
	BST<std::string> tree;
	while (1)
	{
		std::cout << "\t\t\t--------------------------------------------------" << std::endl;
		std::cout << "\t\t\t**********        1、插入元素           **********" << std::endl;
		std::cout << "\t\t\t*********         2、连续插入元素       **********" << std::endl;
		std::cout << "\t\t\t**********        3、层序遍历           **********" << std::endl;
		std::cout << "\t\t\t**********        4、前序遍历           **********" << std::endl;
		std::cout << "\t\t\t**********        5、中序遍历           **********" << std::endl;
		std::cout << "\t\t\t**********        6、后序遍历           **********" << std::endl;
		std::cout << "\t\t\t**********        7、判断二叉树         **********" << std::endl;
		std::cout << "\t\t\t**********        0、退出               **********" << std::endl;
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
			std::cout << "空格分隔，回车结束\n";
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
		case 7:
			tree.isBST() ? std::cout << "是二叉搜索树\n" : std::cout << "不是二叉搜索树\n";
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