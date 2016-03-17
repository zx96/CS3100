#include <iostream>
#include "OrgTree.h"

using namespace std;

int main() {
	OrgTree *t = new OrgTree();
	t->print();
	t->addRoot("CEO", "Fred");
	int root = t->getRoot();
	t->hire(root, "CFO", "George");
	t->hire(t->find("CFO"), "Butts", "Mark");
	t->hire(t->find("CFO"), "Bootymaster", "Miley");
	t->hire(root, "Scrubmaster General", "John");
	t->hire(t->find("Scrubmaster General"), "Scrubmaster Lieutenant", "Daniel");
	t->hire(t->find("Scrubmaster General"), "Scrubmaster Assistant", "Jared");
	t->hire(t->find("Bootymaster"), "Twerking Intern", "Azzy");
	t->hire(t->find("CFO"), "Numbers Guy", "Craigeric");
	t->hire(t->find("CEO"), "Executive of Meme Operations", "Hannah");

	for (int i = 1; i <= 5; i++)
	{
		t->hire(t->find("Numbers Guy"), std::to_string(i), std::to_string(i));
	}

	t->print();
	std::cout << std::endl;

	t->fire("CFO");
	t->addRoot("Super CEO", "Jesus");

	t->print();
	std::cout << std::endl;

	t->write("test");

	delete t;

	OrgTree *t2 = new OrgTree();
	if (!t2->read("test")) return -1;

	t2->print();
	std::cout << std::endl;

	std::cout << t2->getSize() << std::endl;
	std::cout << t2->leftmostChild(t2->getSize()) << std::endl;
	std::cout << std::endl;

	std::cout << t2->title(t2->find("Scrubmaster Assistant")) << std::endl;
	std::cout << t2->name(t2->find("Scrubmaster Assistant")) << std::endl;
	std::cout << t2->parent(t2->find("Scrubmaster Assistant")) << std::endl;
	std::cout << t2->leftmostChild(t2->find("Scrubmaster Assistant")) << std::endl;
	std::cout << t2->rightSibling(t2->find("Scrubmaster Assistant")) << std::endl;
	std::cout << std::endl;

	std::cout << t2->getRoot() << std::endl;
	t2->addRoot("Bob", "Jones");
	std::cout << t2->getRoot() << std::endl;
	std::cout << std::endl;

	t2->print();

	t2->fire("1");
	t2->print();
	t2->fire("4");
	t2->print();
	t2->fire("3");
	t2->print();
	t2->fire("5");
	t2->print();
	t2->fire("Numbers Guy");
	t2->print();
}