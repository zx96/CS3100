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
 *
 * Returns:       The index of the new root node of the tree.
 */
int OrgTree::addRoot(std::string title, std::string name)
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
	return size++;
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
		std::cerr << "(leftmostChild) Node " << node << " does not exist." << std::endl;
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
		std::cerr << "(rightSibling) Node " << node << "does not exist." << std::endl;
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
		std::cerr << "(parent) Node " << node << " does not exist." << std::endl;
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
		std::cerr << "(title) Node " << node << " does not exist." << std::endl;
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
		std::cerr << "(name) Node " << node << " does not exist." << std::endl;
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
	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cerr << "(read) Could not open file: " << filename << "." << std::endl;
		return false;
	}

	// "erase" the tree's contents
	size = 0;

	// get the root node
	int lineNumber = 1;
	std::string line;
	std::getline(file, line);

	// parse the root node's data
	size_t commaIndex = line.find(", ");
	if (commaIndex == std::string::npos)
	{
		std::cerr << "(read) Malformed file: " << filename << "." << std::endl;
		std::cerr << "       Root node is not valid.  Nodes must be of the format: '[title], [name]'." << std::endl;
		return false;
	}
	std::string title = line.substr(0, commaIndex);
	std::string name = line.substr(commaIndex + 2, line.length());
	TREENODEPTR currentParent = addRoot(title, name);

	// iterate through the file
	while (std::getline(file, line))
	{
		// keep track of the line we are processing (for error output)
		lineNumber++;

		// if the parent is null, we've already reached the end of the tree (but still had more to read from the file)
		if (currentParent == TREENULLPTR)
		{
			std::cerr << "(read) Malformed file: " << filename << "." << std::endl;
			std::cerr << "       Reached end of tree before end of file.  (Too many ')')." << std::endl;
			std::cerr << "       (line " << lineNumber << ")" << std::endl;
			return false;
		}

		// each ) tells us to go back up a level (end of subtree)
		if (line == ")")
		{
			currentParent = tree[currentParent].parent;
		}
		else // descend into tree, adding new nodes as we go
		{
			// validate and extract name and title
			commaIndex = line.find(", ");
			if (commaIndex == std::string::npos)
			{
				std::cerr << "(read) Malformed file: " << filename << "." << std::endl;
				std::cerr << "       Node is not valid.  Nodes must be of the format: '[title], [name]'." << std::endl;
				std::cerr << "       (line " << lineNumber << ")" << std::endl;
				return false;
			}
			title = line.substr(0, commaIndex);
			name = line.substr(commaIndex + 2, line.length());
			// hire and descend a level
			currentParent = hire(currentParent, title, name);
		}
	}

	// the final parent should be TREENULLPTR (meaning we ended up back at the root node)
	if (currentParent != TREENULLPTR)
	{
		std::cerr << "(read) Malformed file: " << filename << "." << std::endl;
		std::cerr << "       Reached end of file before end of tree.  (Too few ')')." << std::endl;
		std::cerr << "       (line " << lineNumber << ")" << std::endl;
		return false;
	}

	return true;
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
	}

	// signify that we've reached the end of our subtree
	file << ")" << std::endl;
}

/**
 * Inserts a new node into the tree as the rightmost child of supervisor.
 *
 * Precondition:  None.
 * Postcondition: The new node is inserted into the tree.
 * Performance:   Θ(n), n = number of child nodes of supervisor
 *
 * Returns:       The index of the newly added node, or -1 if the node couldn't be added.
 */
int OrgTree::hire(TREENODEPTR supervisor, std::string title, std::string name)
{
	// check that the supervisor is a valid node
	if (supervisor >= size)
	{
		std::cerr << "(hire) Supervisor node " << supervisor << " does not exist" << std::endl;
		return -1;
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

	return size++;
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
		std::cerr << "(fire) Node with title \"" << title << "\" does not exist." << std::endl;
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

	// fix pointers to deleted node
	if (tree[tree[index].parent].leftmostChild == index)
	{
		// we are the leftmost child
		tree[tree[index].parent].leftmostChild = tree[index].rightSibling;
	}
	else
	{
		// we are a right sibling
		TREENODEPTR currentChild = tree[tree[index].parent].leftmostChild;
		while (tree[currentChild].rightSibling != index)
		{
			currentChild = tree[currentChild].rightSibling;
		}
		tree[currentChild].rightSibling = tree[index].rightSibling;
	}

	// skip to rightmost sibling
	TREENODEPTR currentChild = tree[tree[index].parent].leftmostChild;
	while (tree[currentChild].rightSibling != TREENULLPTR)
	{
		currentChild = tree[currentChild].rightSibling;
	}
	// append deleted node's children to parent node's children
	tree[currentChild].rightSibling = tree[index].leftmostChild;



	// move last element in place of removed element
	// this makes fire even more computationally expensive than it already is,
	// but we don't have to keep track of empty slots in the array
	tree[index] = tree[size - 1];
	// if we move the root, we don't have to worry about parent or right sibling indices
	if (tree[index].parent == TREENULLPTR) root = index;
	else // fix indices
	{
		// try to just fix parent's leftmost child index
		if (tree[tree[index].parent].leftmostChild == (size - 1))
		{
			tree[tree[index].parent].leftmostChild = index;
		}
		else // we have to fix a child's right sibling index
		{
			currentChild = tree[tree[index].parent].leftmostChild;
			// loop until we either reach the end of the children or we've fixed the index
			while (currentChild != index && currentChild != -1)
			{
				// fix the right sibling index
				if (tree[currentChild].rightSibling == (size - 1))
				{
					tree[currentChild].rightSibling = index;
				}
				currentChild = tree[currentChild].rightSibling;
			}
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