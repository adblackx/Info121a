#include <cstdlib>
#include <iostream>

using namespace std;

struct branch {
	int data;
	branch *left;
	branch *right;
	int visited;
};

struct tree {
	branch *root;
};

branch *newBranch(int val) {
	branch *b = (branch*) malloc (sizeof(branch));
	b -> data = val;
	b -> visited = 0;
	b -> left = NULL;
	b -> right = NULL;
	return b;
}

void showRec(branch *b, int space) {
	for (int i = 0; i < space; i++) {
		if (i < space - 1)
			cout << "  ";
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
	if (val >= b -> data && b ->right != NULL)
		recAddVal(b -> right, val);
	else if (val < b -> data && b ->left != NULL)
		recAddVal(b -> left, val);
	if (b ->left == NULL || b ->right == NULL) {
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
	/*branch *b = t -> root;
	while (b -> left != NULL) {
		b = b -> left;
	}

	return b -> data;*/

	if (t -> root == NULL) return -1;
    branch *e =  t -> root;
    int min = t -> root -> data;
    while ( e -> left != NULL) {
        e = e -> left;
        min = e -> data;
    }
    return min;
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

int deepnessRec(tree *t) {
	return recDeepness(t -> root);
}

int deepnessIter(tree *t) {
	branch *b = t -> root;
	int max = 0;
	int nb = 0;
	while (b && !b -> visited) {
		if (b -> left && !b -> left->visited) {
			nb++;
			b = b -> left;
		} else if (b -> right && !b -> right->visited) {
			nb++;
			b = b -> right;
		} else {
			nb++;
			if (nb > max)
				max = nb;
			nb = 0;
			b -> visited = 1;
			b = t -> root;
		}
	}
	return max;
}

int recContains(branch *b, int val){
	if(b->data!=val){
			if (val < b -> data && b->left !=NULL){
				return (b->left, val);
			}

			else if (val < b -> data && b->right !=NULL){
					return (b->right, val);
			}
			else
			return 0;
	} else
	return 1;

}

int contains(tree *b, int val){
	 recContains(b -> root, val);
}

// cas 1: noeud est une feuille
// cas 2: noeud entre dans branches avec 1 enfant
// cas3: noeud avec 2 enfants
// replacer 2 data
// version recherche et supression separee
//memoriser le parent

branch *findMin(branch *b) {
	while (b -> left != NULL) {
		b = b -> left;
	}
	return b;
}

branch* recDel(branch *b, int val) {
	if (b == NULL)
		return NULL;
	if (val < b -> data) {  // la data est a left
		b->left = recDel(b->left, val);
	} else if (val > b->data) { // la data est a right
		b->right = recDel(b->right, val);
	} else {
		// case 1: pas d'enfant à la root
		if (b->left == NULL && b->right == NULL) {
			delete(b); // wipe out the memory, in C, use free function
			b = NULL;
		}
		// case 2: un enfant à right
		else if (b->left == NULL) {
			branch *temp = b; // save current node as a backup
			b = b->right;
			delete temp;
		}
		// case 3: un enfant a left
		else if (b->right == NULL) {
			branch *temp = b; // save current node as a backup
			b = b->left;
			delete temp;
		}
		// case 4: avec deux enfants
		else {
			branch *temp = findMin(b -> right); // find minimal value of right sub tree
			b->data = temp->data; // duplicate the node
			b->right = recDel(b->right, temp->data); // delete the duplicate node
		}
	}
	return b;
}

void del(tree *t, int val) {
	recDel(t -> root, val);
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
			//cout<<"t nul"<<endl;
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



void tri(int tab[], int n){
	cout<<endl;
	tree *t = (tree*) malloc (sizeof(tree));
	t -> root = newBranch(tab[0]);
	for(int i =1; i<n; i++){
		ajouterVal(t,tab[i]);
	}

	for (int i =0; i<n; i++){
		cout<<tab[i]<<" ";
	}
	cout << endl;
	showTree(t);
	
	cout << endl;

	for(int i=0; i<7;i++){
		int minimum=searchMin(t);
		cout<<minimum<<" ";
		del(t, minimum);
	}
	cout << endl;
}

int main() {
	tree *t = (tree*) malloc (sizeof(tree));
	t -> root = newBranch(5);
	t -> root -> left = newBranch(4);
	t -> root -> right = newBranch(6);
	t -> root -> left -> left = newBranch(3);
	addValRec(t, 4);
	addValRec(t, 4);
	addValIter(t, 3);
	cout << "Profondeur recursive: " << deepnessRec(t) << endl;
	cout << "Profondeur iterative: " << deepnessIter(t) << endl;
	showTree(t);
	//cout<<contains(t, 6)<<endl;
	cout<<endl;
	addValIter(t, 7);
	//showTree(t);
	cout<<endl;
	del(t, 5);
	//showTree(t);
	del(t, 5);

	cout<<searchMin(t);

	 int taille=10;
	int tab[taille]={3,1,2,5,4,9,7,9,8,4};
	// 9 9 8 7 5 4 4 3 2 1

	tri(tab, taille);




	//showTree(t);

	return 0;
}
