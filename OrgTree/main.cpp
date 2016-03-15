#include <iostream>
#include "OrgTree.h"

using namespace std;

int main() {
    OrgTree t;
    t.addRoot("CEO", "George Lucas");
    int root = t.getRoot();
    t.hire(root, "CFO", "George Clooney");
    t.hire(t.find("CFO"), "Butts", "Mark Shuttleworth");
    t.hire(t.find("CFO"), "Bootymaster", "Miley Cyrus");
    t.hire(root, "Scrubmaster General", "John Klaassen");
    t.hire(t.find("Scrubmaster General"), "Scrubmaster Lieutenant", "Daniel Bogan");
    t.hire(t.find("Scrubmaster General"), "Scrubmaster Assistant", "Jared Nees");
    t.hire(t.find("Bootymaster"), "Twerking Intern", "Azzy");

    t.printAll();
    t.printTree();

    t.fire("CFO");

    t.printAll();
	t.printTree();

	
}