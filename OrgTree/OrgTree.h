/**
 * Organization Tree
 *
 * Stores a set of nodes representing employees in an organization.
 * Space overhead: 3n+4 words for a full array
 *                 (~16% overhead assuming 16 words of data per node)
 *
 * Author: Jonathan Zentgraf
 */

#ifndef ORGTREE_H
#define ORGTREE_H

#define TREENODEPTR int
#define TREENULLPTR -1

#include <string>

struct TreeNode
{
	std::string title;
	std::string name;
	TREENODEPTR parent;
	TREENODEPTR leftmostChild;
	TREENODEPTR rightSibling;
};

class OrgTree
{
private:
	unsigned int size = 0;
	unsigned int capacity = 0;
	TREENODEPTR root = TREENULLPTR;
	TreeNode *tree;

	void ensureCapacity();

	void _printSubTree(TREENODEPTR subTreeRoot, int level) const;

	void _writeSubTree(std::ofstream& file, TREENODEPTR subTreeRoot) const;

public:
	OrgTree();

	~OrgTree();

	TREENODEPTR addRoot(std::string title, std::string name);

	unsigned int getSize() const;

	TREENODEPTR getRoot() const;

	TREENODEPTR leftmostChild(TREENODEPTR node) const;

	TREENODEPTR rightSibling(TREENODEPTR node) const;

	TREENODEPTR parent(TREENODEPTR node) const;

	std::string title(TREENODEPTR node) const;

	std::string name(TREENODEPTR node) const;

	void print() const;

	void printSubTree(TREENODEPTR subTreeRoot) const;

	TREENODEPTR find(std::string title) const;

	bool read(std::string filename);

	void write(std::string filename) const;

	void writeSubTree(std::string filename, TREENODEPTR subTreeRoot) const;

	TREENODEPTR hire(TREENODEPTR supervisor, std::string title, std::string name);

	bool fire(std::string title);
};


#endif //ORGTREE_H
