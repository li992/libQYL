#include<string>
using namespace std;
class treeNodes {
private:
	string value;
	treeNodes* left;	// pointing to leftchild
	treeNodes* right;	// pointing to rightchild
	treeNodes* parent;	// pointing to its parent

public:
	treeNodes();
	~treeNodes();
	void saveValue(string);
	string getValue();

	// pointer setting or abstracting
	void setLeft(treeNodes*);
	void setRight(treeNodes*);
	void setParent(treeNodes*);
	treeNodes* getLeft() { return left; };
	treeNodes* getRight() { return right; };
	treeNodes* getParent() { return parent; };

};