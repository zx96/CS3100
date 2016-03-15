//
// Created by jonathan on 3/8/16.
//

#ifndef ORGTREE_H
#define ORGTREE_H

#define TREENODEPTR int
#define TREENULLPTR -1

#include <string>
#include <iostream>

struct TreeNode
{
	std::string title;
	std::string name;
	int parent;
	int leftmostChild;
	int rightSibling;
};

class OrgTree
{
private:
	unsigned int size = 0;
	unsigned int capacity = 0;
	TREENODEPTR root = TREENULLPTR;
	TreeNode *tree;

	void ensureCapacity();

public:
	OrgTree();

	~OrgTree();

	void addRoot(std::string title, std::string name);

	unsigned int getSize();

	TREENODEPTR getRoot();

	TREENODEPTR leftmostChild(TREENODEPTR node);

	TREENODEPTR rightSibling(TREENODEPTR node);

	TREENODEPTR parent(TREENODEPTR node);

	std::string title(TREENODEPTR node);

	std::string name(TREENODEPTR node);

	void printSubTree(TREENODEPTR subTreeRoot, int level);

	void printTree();

	TREENODEPTR find(std::string title);

	bool read(std::string filename);

	void write(std::string filename);

	void hire(TREENODEPTR supervisor, std::string title, std::string name);

	bool fire(std::string title);

	//debug function
	void printAll()
	{
		for (int i = 0; i < size; i++)
			std::cout << i << std::endl << tree[i].title << std::endl << tree[i].name << std::endl << tree[i].parent <<
			std::endl << tree[i].leftmostChild << std::endl << tree[i].rightSibling << std::endl << std::endl;
	}
};


#endif //ORGTREE_H
