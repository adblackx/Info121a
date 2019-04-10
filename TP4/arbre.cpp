#include <cstdlib>
#include <iostream>

using namespace std;

struct branch {
	int data;
	branch *left;
	branch *right;
};

struct tree {
	branch *root;
};

branch *newBranch(int val) {
	branch *b = (branch*) malloc (sizeof(branch));
	b -> data = val;
	b -> left = NULL;
	b -> right = NULL;
	return b;
}

void showRec(branch *b, int space) {
	for (int i = 0; i < space; i++) {
		if (i < space - 1)
			cout << "| ";
		else
			cout << "\u21B3 ";
	}
	cout << b -> data << endl;
	if (b -> left != NULL) {
		showRec(b -> left, space+1);
	}
	if (b -> right != NULL) {
		showRec(b -> right, space+1);
	}
}

void showTree(tree *t) {
	branch *b = t -> root;
	showRec(b, 0);
}

void addValIter(tree *t, int val) {
	branch *b = t -> root;
	while(b -> left != NULL || b -> right != NULL) {
		if (val >= b -> data) {
			b = b -> right;
		} else {
			b = b -> left;
		}
	}
	if (val >= b -> data) {
		b -> right = newBranch(val);
	} else {
		b -> left = newBranch(val);
	}
}

void recAddVal(branch *b, int val) {
	if (b ->left != NULL && val < b -> data)
		recAddVal(b -> left, val);
	else if (b ->right != NULL && val >= b -> data)
		recAddVal(b -> right, val);
	if (b ->left == NULL && b ->right == NULL) {
		if (val >= b -> data) {
			b -> right = newBranch(val);
		} else {
			b -> left = newBranch(val);
		}
	}
}

void addValRec(tree *t, int val) {
	recAddVal(t -> root, val);
}

int searchMin(tree *t) {
	branch *b = t -> root;
	while (b -> left == NULL) {
		b = b -> left;
	}
	return b -> data;
}

int recDeepness(branch *b) {
	if (b -> left != NULL && b -> right != NULL) {
		return 1 + max(recDeepness(b -> left), recDeepness(b -> right));
	} else if (b -> right != NULL) {
		return 1 + recDeepness(b ->right);
	} else if (b -> left != NULL) {
		return 1 + recDeepness(b -> left);
	} else {
		return 1;
	}
}

int deepness(tree *t) {
	return recDeepness(t -> root);
}

int main() {
	tree *t = (tree*) malloc (sizeof(tree));
	t -> root = newBranch(5);
	t -> root -> left = newBranch(4);
	t -> root -> right = newBranch(6);
	t -> root -> left -> left = newBranch(3);
	addValRec(t, 7);
	cout << "Profondeur: " << deepness(t) << endl;;
	showTree(t);
	return 0;
}