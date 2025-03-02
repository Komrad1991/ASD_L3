#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include <queue>

template<typename T, typename comparator = std::less<T>>
class bdp
{
	struct node
	{
		T data;
		node* parent;
		node* left;
		node* right;
		node(T d) :data(d)
		{
			parent = nullptr;
			left = nullptr;
			right = nullptr;
		}
	};
	
	comparator comp = comparator{};

public:

	node* _head;

	bdp()
	{
		_head = nullptr;
	}

	void add(T value)
	{
		if (!_head)
		{
			_head = new node(value);
		}
		else if (comp(value,_head->data))
			rec_add_l(value, _head);
		else rec_add_r(value, _head);
	}

	void print_levels()
	{
		if (!_head) return;
		std::queue<node*> q;
		q.push(_head);
		while (!q.empty())
		{
			int size = q.size();
			for (int i = 0; i < size; i++)
			{
				node* nod = q.front();
				q.pop();
				if (nod->left) q.push(nod->left);
				if (nod->right) q.push(nod->right);
				std::cout << nod->data << " ";
			}
			std::cout << std::endl;
		}
	}

	void print_ltr()
	{
		if (!_head) return;
		else print_ltr_rec(_head);
	}

	void print_rtl()
	{
		if (!_head) return;
		std::stack<node*> st;
		std::stack<node*> out;
		st.push(_head);
		while (!st.empty())
		{
			node* curr = st.top();
			st.pop();
			if (curr->right) st.push(curr->right);
			if (curr->left) st.push(curr->left);
			out.push(curr);
		}
		while (!out.empty())
		{
			auto curr = out.top();
			out.pop();
			std::cout << curr->data << " ";
		}
	}

	node* find(T value)
	{
		if (!_head) return nullptr;
		else if (comp(value,_head->data)) return find_rec(value,_head->left);
		else return find_rec(value,_head->right);
	}

	T max()
	{
		if (!_head) return T();
		else if (_head->right) return max_rec(_head->right);
		else return _head->data;
	}

	T min()
	{
		if (!_head) return T();
		else if (_head->left) return min_rec(_head->left);
		else return _head->data;
	}

	void erase(T value)
	{
		node* elem = this->find(value);
		if (!elem) return;
		bdp subTree;
		std::stack<node*> sub;
		if (elem->left) sub.push(elem->left);
		if (elem->right) sub.push(elem->right);
		while (!sub.empty())
		{
			node* out = sub.top();
			sub.pop();
			if (out->right) sub.push(out->right);
			if (out->left) sub.push(out->left);
			subTree.add(out->data);
		}
		if (elem == _head) _head = subTree._head;
		else if (comp(value, elem->parent->data))
		{
			elem->parent->left = subTree._head;
			subTree._head = elem->parent;
		}
		else
		{
			elem->parent->right = subTree._head;
			subTree._head = elem->parent;
		}
	}

	node* lower(T value)
	{
		if (!_head) return nullptr;
		return lower_rec(value, _head);
	}

	node* upper(T value)
	{
		if (!_head) return nullptr;
		return upper_rec(value, _head);
	}

	bool equal(bdp other)
	{
		if (_head)
		{
			if (other._head)
			{
				if (!comp(_head->data, other._head->data) && !comp(other._head->data, _head->data))
				{
					return equal_rec(_head->left, other._head->left) && equal_rec(_head->right, other._head->right);
				}
				else return false;
			}
			else return false;
		}
		else if (other._head)
		{
			return false;
		}
		else return true;
	}

	node* next(node* n)
	{
		return upper(n->data);
	}

	node* prev(node* n)
	{
		return lower(n->data);
	}

private:

	bool equal_rec(node* curr, node* other)
	{
		if (curr)
		{
			if (other)
			{
				if (!comp(curr->data, other->data) && !comp(other->data, curr->data))
				{
					return equal_rec(curr->left, other->left) && equal_rec(curr->right, other->right);
				}
				else return false;
			}
			else return false;
		}
		else if (other)
		{
			return false;
		}
		else return true;
	}

	node* lower_rec(T value,node* curr)
	{
		if (!curr) return nullptr;
		if (comp(curr->data, value)) return curr;
		else lower_rec(value, curr->left);
	}

	node* upper_rec(T value, node* curr)
	{
		if (!curr) return nullptr;
		if (comp(value, curr->data)) return curr;
		else upper_rec(value, curr->right);
	}

	T max_rec(node* curr)
	{
		if (!curr->right) return curr->data;
		else return max_rec(curr->right);
	}
	T min_rec(node* curr)
	{
		if (!curr->left) return curr->data;
		else return min_rec(curr->left);
	}

	node* find_rec(T value, node* curr)
	{
		if (!curr) return nullptr;
		else if (comp(value,curr->data)) 
		{
			return find_rec(value, curr->left);
		}
		else 
		{
			if (!(comp(curr->data,value))) return curr;
			return find_rec(value, curr->right);
		}
	}

	void print_ltr_rec(node* n)
	{
		if (!n) return;
		else
		{
			print_ltr_rec(n->left);
			std::cout << n->data << " ";
			print_ltr_rec(n->right);
		}
	}

	void rec_add_l(T value, node* prev)
	{
		if (!prev->left)
		{
			node* curr = new node(value);
			curr->parent = prev;
			prev->left = curr;
		}
		else 
		if (comp(value,prev->left->data))
			rec_add_l(value, prev->left);
		else 
		{
			if (!comp(prev->left->data,value)) return;
			rec_add_r(value, prev->left);
		}
	}

	void rec_add_r(T value, node* prev)
	{
		if (!prev->right)
		{
			node* curr = new node(value);
			curr->parent = prev;
			prev->right = curr;
		}
		else
			if (comp(value,prev->right->data))
				rec_add_l(value, prev->right);
			else 
			{
				if (!comp(prev->right->data,value)) return;
				rec_add_r(value, prev->right);
			}
	}
	
};