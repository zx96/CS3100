#include <iostream>
#include "OrgTree.h"

using namespace std;

int main() {
    OrgTree t;
	t.printTree();
    t.addRoot("CEO", "Fred");
    int root = t.getRoot();
    t.hire(root, "CFO", "George");
    t.hire(t.find("CFO"), "Butts", "Mark");
    t.hire(t.find("CFO"), "Bootymaster", "Miley");
    t.hire(root, "Scrubmaster General", "John");
    t.hire(t.find("Scrubmaster General"), "Scrubmaster Lieutenant", "Daniel");
    t.hire(t.find("Scrubmaster General"), "Scrubmaster Assistant", "Jared");
    t.hire(t.find("Bootymaster"), "Twerking Intern", "Azzy");

    t.printAll();
    t.printTree();

    t.fire("CFO");
	t.addRoot("Super CEO", "Jesus");

    t.printAll();
	t.printTree();

	
}