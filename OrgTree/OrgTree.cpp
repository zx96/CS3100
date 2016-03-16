/**
 * Organization Tree
 *
 * Stores a set of nodes representing employees in an organization.
 * Space overhead: 3n+4 words for a full array
 *                 (~16% overhead assuming 16 words of data per node)
 *
 * Author: Jonathan Zentgraf
 */

#include "OrgTree.h"
#include <iostream>
#include <fstream>

#define ORGTREE_DEFAULT_CAPACITY 10

/**
 * Constructs the OrgTree with the default capacity.
 *
 * Precondition:  None.
 * Postcondition: The OrgTree is initialized with an empty array.
 * Performance:   Θ(1)
 */
OrgTree::OrgTree()
{
	// allocate the tree array on the heap
	tree = new struct TreeNode[ORGTREE_DEFAULT_CAPACITY];
	capacity = ORGTREE_DEFAULT_CAPACITY;
}

/**
 * Destructs the OrgTree.
 *
 * Precondition:  None.
 * Postcondition: The OrgTree is destroyed and its memory is freed.
 * Performance:   Θ(n), n is the total number of nodes in the tree
 */
OrgTree::~OrgTree()
{
	// avoid leaking memory
	delete[] tree;
}

/**
 * Adds a new root node to the tree.  If another root already exists, it is
 * made a child of the new root node.
 *
 * Precondition:  None.
 * Postcondition: The tree is assigned a new root node.
 * Performance:   Θ(1)
 */
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

/**
 * Returns the number of nodes in the tree.
 *
 * Precondition:  None.
 * Postcondition: None.
 * Performance:   Θ(1)
 *
 * Returns:       The number of nodes in the tree.
 */
unsigned int OrgTree::getSize() const
{
	return size;
}

/**
 * Returns the index of the root node of the tree.
 *
 * Precondition:  None.
 * Postcondition: None.
 * Performance:   Θ(1)
 *
 * Returns:       The root node's index, or -1 if there is no root
 */
TREENODEPTR OrgTree::getRoot() const
{
	return root;
}

/**
 * Returns the index of the leftmost child of a node.
 *
 * Precondition:  None.
 * Postcondition: None.
 * Performance:   Θ(1)
 *
 * Returns:       The index of the leftmost child of node,
 *                or -1 if the node does not exist.
 */
TREENODEPTR OrgTree::leftmostChild(TREENODEPTR node) const
{
	if (node >= size)
	{
		std::cerr << "(leftmostChild) Node does not exist." << std::endl;
		return -1;
	}
	return tree[node].leftmostChild;
}

/**
 * Returns the index of the right sibling of a node.
 *
 * Precondition:  None.
 * Postcondition: None.
 * Performance:   Θ(1)
 *
 * Returns:       The index of the right sibling of node,
 *                or -1 if the node does not exist.
 */
TREENODEPTR OrgTree::rightSibling(TREENODEPTR node) const
{
	if (node >= size)
	{
		std::cerr << "(rightSibling) Node does not exist." << std::endl;
		return -1;
	}
	return tree[node].rightSibling;
}

/**
 * Returns the index of the parent of a node.
 *
 * Precondition:  None.
 * Postcondition: None.
 * Performance:   Θ(1)
 *
 * Returns:       The index of the parent of node,
 *                or -1 if the node does not exist.
 */
TREENODEPTR OrgTree::parent(TREENODEPTR node) const
{
	if (node >= size)
	{
		std::cerr << "(parent) Node does not exist." << std::endl;
		return -1;
	}
	return tree[node].parent;
}

/**
 * Returns the title of the employee represented by a node.
 *
 * Precondition:  None.
 * Postcondition: None.
 * Performance:   Θ(1)
 *
 * Returns:       The title of the employee represented by node,
 *                or nullptr if the node does not exist.
 */
std::string OrgTree::title(TREENODEPTR node) const
{
	if (node >= size)
	{
		std::cerr << "(title) Node does not exist." << std::endl;
		return nullptr;
	}
	return tree[node].title;
}

/**
 * Returns the name of the employee represented by a node.
 *
 * Precondition:  None.
 * Postcondition: None.
 * Performance:   Θ(1)
 *
 * Returns:       The name of the employee represented by node,
 *                or -1 if the node does not exist.
 */
std::string OrgTree::name(TREENODEPTR node) const
{
	if (node >= size)
	{
		std::cerr << "(name) Node does not exist." << std::endl;
		return nullptr;
	}
	return tree[node].name;
}

/**
 * Performs a traversal of the tree and prints the contents to stdout.
 *
 * Precondition:  None.
 * Postcondition: None.
 * Performance:   Θ(n), n is the total number of nodes in the subtree
 */
void OrgTree::printSubTree(TREENODEPTR subTreeRoot) const
{
	_printSubTree(subTreeRoot, 0);
}

/**
 * Performs a traversal of the tree starting at the given level and prints the contents to stdout.
 *
 * Precondition:  None.
 * Postcondition: None.
 * Performance:   Θ(n), n is the total number of nodes in the subtree
 */
void OrgTree::_printSubTree(TREENODEPTR subTreeRoot, int level) const
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
		_printSubTree(currentChild, level + 1);
	}
}

/**
 * Prints the contents of the entire tree to stdout.
 *
 * Precondition:  None.
 * Postcondition: None.
 * Performance:   Θ(n), n is the total number of nodes in the tree
 */
void OrgTree::printTree() const
{
	printSubTree(root);
}

/**
 * Returns the index of the node with a given title in the tree.
 *
 * Precondition:  None.
 * Postcondition: None.
 * Performance:   Best: Θ(1)
 *                Worst: Θ(n), n is the total number of nodes in the tree
 *
 * Returns:       The index of the node with the given title,
 *                or -1 if there is no such node.
 */
TREENODEPTR OrgTree::find(std::string title) const
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

void OrgTree::write(std::string filename) const
{
	std::ofstream file;
	file.open(filename, std::ofstream::out | std::ofstream::trunc);

	_write(file, root);

	file.close();
}

void OrgTree::_write(std::ofstream& file, TREENODEPTR subTreeRoot) const
{
	// reached a leaf node
	if (subTreeRoot == TREENULLPTR) return;
	// write the current node
	file << tree[subTreeRoot].title << ", " << tree[subTreeRoot].name << std::endl;

	// write all of the child trees
	for (TREENODEPTR currentChild = tree[subTreeRoot].leftmostChild;
	     currentChild != TREENULLPTR; currentChild = tree[currentChild].rightSibling)
	{
		_write(file, currentChild);
		file << ")" << std::endl;
	}
}

/**
 * Inserts a new node into the tree as the rightmost child of supervisor.
 *
 * Precondition:  None.
 * Postcondition: The new node is inserted into the tree.
 * Performance:   Θ(n), n = number of child nodes of supervisor
 */
void OrgTree::hire(TREENODEPTR supervisor, std::string title, std::string name)
{
	// check that the supervisor is a valid node
	if (supervisor >= size)
	{
		std::cerr << "(hire) Supervisor node does not exist" << std::endl;
		return;
	}

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
		tree[currentChild].rightSibling = size;
	}

	size++;
}

/**
 * Removes a node from the tree.
 * If the node is the root node or doesn't exist, does nothing.
 * The removed node's children become children of the removed node's parent.
 *
 * Precondition:  None.
 * Postcondition: The employee is removed if valid.
 * Performance:   Θ(n) if employee exists and can be removed, Θ(1) otherwise.
 *
 * Returns:       true if employee was removed, false if the employee was invalid
 */
bool OrgTree::fire(std::string title)
{
	// cannot fire root node or nonexistent employee
	// parent pointer will never be null because we can't fire the root node
	int index = find(title);
	if (index == TREENULLPTR)
	{
		std::cerr << "(fire) Node does not exist." << std::endl;
		return false;
	}
	else if (index == root)
	{
		std::cerr << "(fire) Cannot fire root node." << std::endl;
	}

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

/**
 * Ensures that there is room in the underlying array to insert another item
 *
 * Precondition:  The tree has a capacity of at least 1.
 * Postcondition: The array size is doubled
 * Performance:   Best: Θ(1)
 *                Worst: Θ(n)
 */
void OrgTree::ensureCapacity()
{
	// we only need to worry if the capacity is too small
	if (capacity < size + 1)
	{
		// create a new tree with twice the capacity
		capacity <<= 1;
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