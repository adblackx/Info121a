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
	int nb_element;
};

branch *newBranch(int val) {
	branch *b = (branch*) malloc (sizeof(branch));
	b -> data = val;
	b -> visited = 0;
	b -> left = NULL;
	b -> right = NULL;
	return b;
}

//sous fonction pour affiche l'arbre
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

// affihce un arbre
void showTree(tree *t) {
	branch *b = t -> root;
	showRec(b, 0);
}

void ajouterVal(tree *a, int val) {
	a->nb_element++;
	branch *n = newBranch(val);
	if(a->root==NULL){
		a->root=n;
	}
	else{
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
				}
				else{
					e=e->right;
				}
			}
			
		}
	}
			
}


// plusieurs tentative d'ajout de val dans un arbre
/*
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
}*/

int searchMin(tree *t) {

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
// fonction pour la profondeur
int deepnessRec(tree *t) {
	return recDeepness(t -> root);
}

//fonction pour la profondeur de facon itérative
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

//sous fonction de contains
int recContains(branch *b, int val){
	if(b->data!=val){
			if (val < b -> data && b->left !=NULL){
				return recContains(b->left, val);
			}

			else if (val > b -> data && b->right !=NULL){
					return recContains(b->right, val);
			}
			else
			return 0;
	} else
	return 1;

}

// retour 1 si l'arbre contient l'element val
int contains(tree *b, int val){
	 recContains(b -> root, val);
}

// cherche la branche minimale
branch *findMin(branch *b) {
	while (b -> left != NULL) {
		b = b -> left;
	}
	return b;
}

branch* recDel(branch *b, int val) {
	if (b == NULL)
		return NULL;

	if (val < b -> data) {  // le data est a gauche
		b->left = recDel(b->left, val);
	} else if ( val > b->data) { // le data est a droite
		b->right = recDel(b->right, val);
	} else {
		// cas 1: pas d'enfant à la root
		if (b->left == NULL && b->right == NULL) {
			delete(b); //on efface la memoire
			b = NULL;
		}
		// cas 2: un enfant à droite
		else if (b->left == NULL) {
			branch *temp = b; // on enregistre le noeud
			b = b->right;
			delete temp;
		}
		// cas 3: un enfant a gauche
		else if (b->right == NULL) {
			branch *temp = b; // on enregistre le noeud
			b = b->left;
			delete temp;
		}
		// case 4: avec deux enfants
		else {
			branch *temp = findMin(b -> right); // on cherche le minimal dans la branche a droite
			b->data = temp->data; // on duplique le noeuf
			b->right = recDel(b->right, temp->data); // on supprime le noeud duplique
		}
	}
	return b;
}

// surpprimer la valeur t dans l'arbre
void del(tree *t, int val) {
	t->nb_element--;
	if(t -> root -> left == NULL ){  // si tout ce qui a gauche est vide ( ou a deja ete supprime)
		if(t -> root -> right == NULL){// si tout ce qui a droite aussi est vide ( ou a deja ete supprime) il ne reste que le root
			t->root=NULL;
		}
		else{ // transfere la branche de droite a gauche, puis on supprime
			branch *temp = findMin(t->root -> right); // on cherche le minimal dans la branche a droite
			t->root->data = temp->data; // on duplique le noeuf
			t->root->right = recDel(t->root->right, temp->data); // on supprime le noeud duplique
		}

	}
	else{
	recDel(t->root, val);
	}
}

// tri un tableau à l'aide d'un arbre
void tri(int tab[], int n){
	cout<<endl;
	tree *t = (tree*) malloc (sizeof(tree));
	for(int i =0; i<n; i++){
		ajouterVal(t,tab[i]);
	}

	showTree(t);
	for(int i=0; i<n;i++){
		int minimum=searchMin(t);
		cout<<minimum<<" ";
		del(t, minimum);
	}
	
	cout << endl;
}


int taille_sub(branch *e){
	if (e==NULL)
		return 0;
	return 1 + taille_sub(e->left) + taille_sub(e->right);
}

int mediane_sub(branch *e, int n){
	if (e==NULL)
		return -1;
	
	int g= taille_sub(e->left);
	if (g==n)
		return e->data;
	
	if(g>n)
		return mediane_sub(e->left, n);
	
	return mediane_sub(e->right, n-g-1);		
	
}

// retourne la valeur mediane d'un arbre
int mediane_rec(tree *t){
	if(t->root ==0)
		return -1;
	int taille= t->nb_element/2;
	return mediane_sub(t->root, taille);
}



int main() {


	int taille=10;
	int TAILLE=15;

	int tab1[taille]={3,1,2,5,4,9,1,9,8,4};
	int tab2[taille]={3,1,2,5,4,10,7,7,10,4};
	int tab3[TAILLE]={12,15,3,1,2,5,4,9,14,19,7,13,14,4,16};

	cout<<endl;
	tree *t = (tree*) malloc (sizeof(tree));
	for(int i =0; i<TAILLE; i++){
		ajouterVal(t,tab3[i]);
	}

	// contient letest de ajoute val, newtree et newBranch et afficher arbre
	// ainsi que chercher minimum
	tri(tab3,15);
	cout<<"nombre elements: "<< t->nb_element<<endl; 
	cout<<mediane_rec(t)<<endl;
	//cout<<mediane_rec(t)<<endl;
	
	for(int i =0; i<TAILLE; i++){
		cout<<tab3[i]<<" ";
	}	
	
	cout<<endl;
	
	cout<<"L'arbre contient t il : " << tab3[0] <<" : " <<contains(t, tab3[0])<<endl;
	cout<<"L'arbre contient t il : " << tab3[TAILLE-1] <<" : " <<contains(t, tab3[TAILLE-1])<<endl;
	cout<<"L'arbre contient t il : " << tab3[5] <<" : " <<contains(t, tab3[5])<<endl;

	cout<<"Le minimum de l'arbre est : " <<searchMin(t)<<endl;


	cout<<"L'arbre contient t il : " << 10000 <<" : " <<contains(t, 10000)<<endl;
	cout<<"La profondeur est (iterative)  : "<<deepnessIter(t)<<endl;
	cout<<"La profondeur est (recusrive) : "<<deepnessRec(t)<<endl;


	//showTree(t);

	return 0;
}
