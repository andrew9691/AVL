#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <ostream>

template<typename T>
class AVL
{
	class TreeNode
	{
	public:
		T data;
		TreeNode* left;
		TreeNode* right;
		TreeNode* parent;
		int height;

		TreeNode(TreeNode* p, TreeNode* l, TreeNode* r, T dt, int h = 1) : parent(p), left(l), right(r), data(dt), height(h) {}

		TreeNode(T x)
		{
			data = x;
			height = 1;
			left = nullptr;
			right = nullptr;
			parent = nullptr;
		}

		bool isLeaf()
		{
			if (this == nullptr)
				throw std::out_of_range("Node is nullptr!");
			return (left == nullptr) && (right == nullptr);
		}

		~TreeNode() {}
	};

	TreeNode* root;

	int rotations = 0;

public:
	AVL() : root(nullptr) {}

	AVL(T value) : root(new TreeNode(nullptr, nullptr, nullptr, value)) {}

	~AVL()
	{
		while (root)
			erase(root->data);
	}

	void add(T x)
	{
		root = insert(root, x);
	}

	TreeNode* search(T value) const
	{
		return private_search(value, root);
	}

	void erase(T x)
	{
		root = remove(root, x);
	}

	int get_rotations()
	{
		return rotations;
	}

	void print()
	{
		PrintTree(root);
	}

private:

	int get_height(TreeNode* p)
	{
		return p != nullptr ? p->height : 0;
	}

	int bfactor(TreeNode* p)
	{
		return get_height(p->right) - get_height(p->left);
	}

	void fixheight(TreeNode* p)
	{
		int hl = get_height(p->left);
		int hr = get_height(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}

	TreeNode* rotateright(TreeNode* p)
	{
		TreeNode* q = p->left;
		p->left = q->right;
		if (q->right)
			q->right->parent = p;
		q->right = p;
		q->parent = p->parent;
		p->parent = q;
		fixheight(p);
		fixheight(q);
		rotations++;
		return q;
	}

	TreeNode* rotateleft(TreeNode* q)
	{
		TreeNode* p = q->right;
		q->right = p->left;
		if (p->left)
			p->left->parent = q;
		p->left = q;
		p->parent = q->parent;
		q->parent = p;
		fixheight(q);
		fixheight(p);
		rotations++;
		return p;
	}

	TreeNode* balance(TreeNode* p)
	{
		fixheight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->right) < 0)
				p->right = rotateright(p->right);
			return rotateleft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->left) > 0)
				p->left = rotateleft(p->left);
			return rotateright(p);
		}
		return p;
	}

	TreeNode* findmin(TreeNode* p)
	{
		return p->left != nullptr ? findmin(p->left) : p;
	}

	TreeNode* removemin(TreeNode* p)
	{
		if (p->left == nullptr)
			return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}

	TreeNode* insert(TreeNode* p, T k)
	{
		if (!p)
			return new TreeNode(k);
		if (k < p->data)
		{
			p->left = insert(p->left, k);
			p->left->parent = p;
		}
		else
		{
			p->right = insert(p->right, k);
			p->right->parent = p;
		}
		return balance(p);
	}

	TreeNode* remove(TreeNode* p, int k)
	{
		if (!p)
			return nullptr;
		if (k < p->data)
			p->left = remove(p->left, k);
		else if (k > p->data)
			p->right = remove(p->right, k);
		else //  k == p->key
		{
			TreeNode* q = p->left;
			TreeNode* r = p->right;
			delete p;
			if (!r)
				return q;
			TreeNode* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);
	}

	TreeNode* private_search(T value, TreeNode* node) const
	{
		if (node == nullptr)
			return nullptr;
		else if (node->data == value)
			return node;
		else if (node->data > value)
			return private_search(value, node->left);
		else
			return private_search(value, node->right);
	}

	void PrintTree(TreeNode* x, int h = 0)
	{
		if (x->right != 0)
			PrintTree(x->right, h + 1);
		for (int i = 0; i < h; ++i)
			std::cout << "     ";
		std::cout << x->data << std::endl;
		if (x->left != 0)
			PrintTree(x->left, h + 1);
	}

};

template<typename T>
class AVLSet
{
	AVL<T> tree;

public:

	AVLSet() {};

	void avl_set_add(T x)
	{
		tree.add(x);
	}

	void avl_set_del(T x)
	{
		tree.erase(x);
	}

	void avl_set_print()
	{
		tree.print();
	}

	bool is_in_tree(T x)
	{
		return tree.search(x) != nullptr;
	}
};

#endif
