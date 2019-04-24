#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

	const int taille = 10;


int parent(int i){
	if (i%2==0)
		return i/2;
	else 
		return (i-1)/2;
}

int left(int i){
	return 2*i+1;
}

int right(int i){
	return 2*i +2;
}

void show_tab(int tab[], int n){
	for(int i=0; i<n; i++){
		cout<<tab[i]<<" ";
	}
	cout<<endl;
}

void show_tas(int tab[], int n){

	if(n!=0)
	cout << tab[parent(n)]<<endl;
	cout<<" "<<tab[n]<<endl;
	int gauche=left(n);
	int droite=right(n);

	if(gauche<taille){
		cout <<"  "<< tab[left(n)]<<" ";
	}
	if (droite<taille)
	cout << tab[right(n)]<<endl;

}

void echange(int tab[], int a, int b){
	int temp=tab[a];
	tab[a]=tab[b];
	tab[b]=temp;
}

void tamiser_test(int tab[], int deb, int fin){
	int k = deb;
	int j = 2*k;
	while(j<= fin){
		if(j<fin and tab[j]<tab[j+1])
			j++;
		else if (tab[k]<tab[j]){
			echange(tab, j, k);
			k=j;
			j=2*k;
		}
		else{
			j=fin+1;
		}
	}
}

void tamiser(int tab[], int deb, int fin){
	if(left(fin)>deb and right(deb)>deb){

		return ;
	}

		//nt x = max( tab[fin], max(tab[right(deb),tab[left(deb)] ));
		int y = max(tab[right(deb)],tab[left(deb)])	;	
		int x = max( tab[fin], y );

		if(x==tab[fin]){
			return;
		}
		if(x==tab[left(fin)]){
			echange(tab, fin, left(fin));
			tamiser(tab, deb, left(fin));
		}
}

void cree_tas(int tab[], int n){

}

int main() {

	int tab1[taille]={3,1,2,5,4,9,1,9,8,4};
	show_tab(tab1, taille);
	cout<<endl;
	show_tas(tab1, 0);
	tamiser(tab1, 5, taille);
	show_tas(tab1, 1);
	show_tas(tab1, 2);
	show_tab(tab1, taille);

	return 0;
}
