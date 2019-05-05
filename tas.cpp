#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <random>


using namespace std;

int nombredefois(0);

int parent(int i){
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

void espace(int n){
	for(int i=0; i <n; i++){
		cout<<" ";
	}
}

void show_tas(int tab[], int n){ 
	// est appele que pour n <= parent(TAILLE) ou TAILLE est la taille max du tab
	// c a dire pour afficher le dernier tas
	// affiche aussi le parent pour mieux se situer dans les branches l. 42 a l.44
	int vide=0;
	if(n!=0){
		cout << tab[parent(n)]<<endl;
	}

	cout<<"P|__"<< tab[n]<<endl;
	int gauche=left(n);
	int droite=right(n);
	vide+=4;
	if(gauche>n){
		espace(vide);
		cout <<"G|__"<< tab[left(n)]<<endl;
	}
	if (droite>n){
		espace(vide);
		cout <<"D|__"<< tab[right(n)]<<endl;

	}

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

void tamiser(int tab[], int deb, int racine){
	nombredefois++;
	if(left(racine)>=deb and right(racine)>=deb){
		return ;
	}

	if(left(racine)==deb-1){ // ajout de ce cas
		if(tab[left(racine)]>=tab[racine]){
			echange(tab, racine, left(racine));
		}
		return ;
	}
	
	int x = max(tab[right(racine)], max(tab[left(racine)], tab[racine]));
	if(x==tab[racine]){
		return;
	}
	else if(x==tab[left(racine)] ){
		echange(tab, racine, left(racine));
		tamiser(tab, deb, left(racine));
	}

	else if( x==tab[right(racine)]){
		echange(tab, racine, right(racine));
		tamiser(tab, deb, right(racine));
	}
}

void new_tas(int tab[], int n){
	int deb= parent(n-1);   
	while(deb>=0){
		tamiser(tab,n, deb);
		deb--;
	}
}

void tri_par_tas(int tab[], int n){
	for(int i=n; i>0; i--){
		new_tas(tab, i);
		echange(tab, 0, i-1);	
	}
}

void new_tab_alea(int tab[] , int taille){
	int alea;
	for(int i=0; i<taille; i++){
		alea=rand()%(1000);
		tab[i]=alea;
	}
}


int main() {
	srand(time(NULL));
	int alea = rand()%(1000);
	int tab[alea];
	new_tab_alea(tab, alea);
	const int taille(21), taille1(23);
	int tab1[taille]={			 5,
								1,2,
					 5,4,            		 9,1,
			 	9,8,	21,20, 			90,4,	1,2,
			 3,4, 5,6, 100,200
		};

	int tab2[taille1]={3,1,2,5,4,9,1,11,8,12,15,23,14,97,12,15,26,59,417,1,523,12,14};	

	tri_par_tas(tab, alea);
	show_tab(tab, alea);

	cout<<endl;	
	//tri_par_tas(tab1, taille);
	//show_tab(tab1, taille);
	cout<<endl;	
	show_tas(tab1,0);
	cout<<endl;	
	show_tas(tab1,2);
	cout<<endl;	

	cout<<"Nombre de recursives: "<< nombredefois <<endl;

	return 0;
}
