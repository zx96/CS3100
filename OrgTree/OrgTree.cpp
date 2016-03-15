//
// Created by jonathan on 3/8/16.
//

#include "OrgTree.h"
#include <iostream>

#define ORGTREE_DEFAULT_CAPACITY 10

OrgTree::OrgTree()
{
	// allocate the tree array on the heap
	tree = new struct TreeNode[ORGTREE_DEFAULT_CAPACITY];
	capacity = ORGTREE_DEFAULT_CAPACITY;
}

/*
 * Destructs the OrgTree
 * Pre:  None.
 * Post: None.
 */
OrgTree::~OrgTree()
{
	// avoid leaking memory
	delete[] tree;
}

void OrgTree::addRoot(std::string title, std::string name)
{
	// insert the root node in the array
	ensureCapacity();
	// use size as the index for the new node (last spot in array)
	tree[size] = TreeNode{title, name, TREENULLPTR, TREENULLPTR, TREENULLPTR};
	// if we previously had a different root, fix parent and child pointers
	if (root != TREENULLPTR)
	{
		tree[size].leftmostChild = root;
		tree[root].parent = size;
	}
	// acknowledge the new root
	root = size;
	size++;
}

unsigned int OrgTree::getSize()
{
	return size;
}

TREENODEPTR OrgTree::getRoot()
{
	return root;
}

TREENODEPTR OrgTree::leftmostChild(TREENODEPTR node)
{
	return tree[node].leftmostChild;
}

TREENODEPTR OrgTree::rightSibling(TREENODEPTR node)
{
	return tree[node].rightSibling;
}

TREENODEPTR OrgTree::parent(TREENODEPTR node)
{
	return tree[node].parent;
}


std::string OrgTree::title(TREENODEPTR node)
{
	return tree[node].title;
}

std::string OrgTree::name(TREENODEPTR node)
{
	return tree[node].name;
}

/*
 * Performs a traversal of the tree and prints the contents to stdout
 * Precondition:  None.
 * Postcondition: None.
 * Performance:   O(n), n is the total number of nodes in the tree
 */
void OrgTree::printSubTree(TREENODEPTR subTreeRoot, int level = 0)
{
	// reached a leaf node
	if (subTreeRoot == TREENULLPTR) return;
	// indent appropriately
	for (int i = 0; i < level; i++) std::cout << "\t";
	// print the current node
	std::cout << tree[subTreeRoot].title << ": " << tree[subTreeRoot].name << std::endl;

	// print all of the child trees
	for (TREENODEPTR currentChild = tree[subTreeRoot].leftmostChild;
	     currentChild != TREENULLPTR; currentChild = tree[currentChild].rightSibling)
	{
		printSubTree(currentChild, level + 1);
	}
}

void OrgTree::printTree()
{
	printSubTree(root);
}

TREENODEPTR OrgTree::find(std::string title)
{
	for (int i = 0; i < size; i++)
	{
		if (tree[i].title == title) return i;
	}
	return -1;
}

bool OrgTree::read(std::string filename)
{
	return false;
}

void OrgTree::write(std::string filename)
{

}

/*
 * Inserts a new employee into the tree as the rightmost child of supervisor.
 * Pre:  supervisor is a valid index to a node in the tree.
 * Post: The new employee is inserted into the tree.
 */
void OrgTree::hire(TREENODEPTR supervisor, std::string title, std::string name)
{
	// insert the new hire as the rightmost child
	ensureCapacity();
	tree[size] = TreeNode{title, name, supervisor, TREENULLPTR, TREENULLPTR};

	if (tree[supervisor].leftmostChild == TREENULLPTR) // this is the first child
	{
		tree[supervisor].leftmostChild = size;
	}
	else // find the rightmost child and add the new hire on
	{
		TREENODEPTR currentChild = tree[supervisor].leftmostChild;
		while (tree[currentChild].rightSibling != TREENULLPTR)
		{
			currentChild = tree[currentChild].rightSibling;
		}
		std::cout << "Current child: " << currentChild << std::endl << std::endl;
		tree[currentChild].rightSibling = size;
	}

	size++;
}

/*
 * Removes an employee from the tree.
 * If the employee
 */
bool OrgTree::fire(std::string title)
{
	// cannot fire root node or nonexistent employee
	// parent pointer will never be null because we can't fire the root node
	int index = find(title);
	if (index == TREENULLPTR || index == root) return false;

	// update parent indices of children
	for (TREENODEPTR currentChild = tree[index].leftmostChild;
	     currentChild != TREENULLPTR; currentChild = tree[currentChild].rightSibling)
	{
		// update parent index
		tree[currentChild].parent = tree[index].parent;
	}

	// skip to rightmost child
	TREENODEPTR currentChild = tree[tree[index].parent].leftmostChild;
	while (tree[currentChild].rightSibling != TREENULLPTR)
	{
		currentChild = tree[currentChild].rightSibling;
	}
	// append deleted node's children to parent node's children
	tree[currentChild].rightSibling = tree[index].leftmostChild;

	// fix pointers to deleted node
	if (tree[tree[index].parent].leftmostChild == index)
	{
		// we are the leftmost child
		tree[tree[index].parent].leftmostChild = tree[index].rightSibling;
	}
	else
	{
		// we are a right sibling
		currentChild = tree[tree[index].parent].leftmostChild;
		while (tree[currentChild].rightSibling != index)
		{
			currentChild = tree[currentChild].rightSibling;
		}
		tree[currentChild].rightSibling = tree[index].rightSibling;
	}



	// move last element in place of removed element
	// this makes fire even more computationally expensive than it already is,
	// but we don't have to keep track of empty slots in the array
	tree[index] = tree[size - 1];
	// try to just fix parent's leftmost child index
	if (tree[tree[index].parent].leftmostChild == (size - 1))
	{
		tree[tree[index].parent].leftmostChild = index;
	}
	else // we have to fix a child's right sibling index
	{
		currentChild = tree[tree[index].parent].leftmostChild;
		while (currentChild != index)
		{
			if (tree[currentChild].rightSibling == (size - 1))
			{
				tree[currentChild].rightSibling = index;
			}
			currentChild = tree[currentChild].rightSibling;
		}
	}
	// we can now pretend the last element is gone
	size--;

	return true;
}

/*
 * Ensures that there is room in the underlying array to insert another item
 * Precondition:  The tree has a capacity of at least 2
 * Postcondition: There is enough room to insert at least one more item in the array.
 * Performance:   Best: Θ(1), Worst: Θ(n)
 */
void OrgTree::ensureCapacity()
{
	// we only need to worry if the capacity is too small
	if (capacity < size + 1)
	{
		// create a new tree with 1.5 times the capacity
		// this fails if the initial capacity is 1
		capacity = capacity + (capacity >> 1);
		TreeNode *newTree = new TreeNode[capacity];
		// copy the tree contents
		for (int i = 0; i < size; i++)
		{
			newTree[i] = tree[i];
		}
		// point to the new tree
		delete[] tree;
		tree = newTree;
	}
}