#pragma once
#include"mystack.h"
#include"stack"

template<typename T> class BiTNode
{
public:   
	enum operate
	{
		delect,
		visit_forward,
		visit_mid,
		visit_back
	};
	enum dir
	{
		left,
		right,
		mid
	};
	T data;
	BiTNode<T> *lchild, *mchild, *rchild;
	BiTNode(T value)
	{
		root = this;
		lchild = nullptr;
		rchild = nullptr;
		mchild = nullptr;
		data = value;
	}
	BiTNode()
	{
		root = this;
		lchild = nullptr;
		rchild = nullptr;
		mchild = nullptr;
		data = static_cast<T>(0);
	}
	void CreateBiTNode(T value, dir child)
	{
		if (child == left)
			this->lchild = new BiTNode(value);
		if (child == right)
			this->rchild = new BiTNode(value);
		if (child == mid)
			this->mchild = new BiTNode(value);
	}
	virtual~BiTNode() { visit(delect); }
	static bool  CreateBiTree(BiTNode * &t, T data)
	{
		if (t == nullptr)
		{
			t = new BiTNode;
			t->data = data;
			return true;
		}
		return false;
	}
	void visit(operate op)
	{
		visit(root, op);
	}
	BiTNode * root;

private:
	void visit(BiTNode *&pos, operate op)
	{
		if (pos->lchild != nullptr)
		{
			s += pos;
			visit(pos->lchild, op);
		}
		else
		{
			if (s.empty())
			{
				if (op == delect)
				{
					delete pos;
					pos = nullptr;
				}
				return;
			}
			visit(s.mypop()->rchild, op);
		}
		if (op == delect)
		{
			delete pos;
			pos = nullptr;
		}
	}
	mystack<BiTNode*> s;
};
