#include <iostream>
#include <cstdlib>
#include <stdexcept>

using namespace std;

struct node {
	int data;
	node *next;
};

struct list
{
	int nb;
	node *head;
};

list *new_list();
void show_list(list *l);
void add_head(list *l, int val);
void add_end(list *l, int val);
void delete_val(list *l, int val);
int search_max(list *l);
void free_list(list *l);
void tri_insertion(list *l);