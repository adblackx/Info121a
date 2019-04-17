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

int searchMin(tree *t) {
	branch *b = t -> root;
	while (b -> left != NULL) {
		b = b -> left;
	}
	return b -> data;
}

void ajouterVal(tree *a, int val) {
	branch *n = newBranch(val);
	if(a->root==NULL){
		a->root=n;
	}
	
	else{
		//branch *e = newBranch(val);
		branch *e = a->root;
		while(e!=NULL){
			cout<<"t nul"<<endl;
			if(val < e->data){
				if(e->left==NULL){
					e->left=n;
					break;
				}else{
					e=e->left;
				}
			}
				else{
				if(e->right==NULL){
					e->right=n;
					break;
				}else{
					e=e->right;
				}
			}
			
		}
	}
			
}



int main() {
	tree *t = (tree*) malloc (sizeof(tree));
	t -> root = newBranch(5);
	t -> root -> left = newBranch(4);
	t -> root -> right = newBranch(6);
	t -> root -> left -> left = newBranch(3);
	
	ajouterVal(t,9);
	
	//t -> root -> left -> left-> left = newBranch(1);
	showTree(t);
	cout<<"La profondeur est "<<deepness(t)<<endl;
	cout<<"Le minimum est "<<searchMin(t)<<endl;

	return 0;
}
