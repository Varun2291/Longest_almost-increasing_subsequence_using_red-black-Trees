//----------------------------------------------------//
// Author: Varun Rajavelu                             //
// G Number: G00937282                                // 
//----------------------------------------------------//
#include <iostream>
//#include <conio.h>
#include <stdlib.h>
#include <fstream>

//#include "Main.h"
#include "RedBlackTrees.h"

using namespace std;

static NODEPTR tail_node;

NODEPTR predecessor_new(NODEPTR *treeroot, int val) 
{
	NODEPTR Z = (NODEPTR) malloc(sizeof(struct node));
	Z->key = val;
	NODEPTR y = NILPTR;
	NODEPTR x = *treeroot;
	NODEPTR pred;

	while (x != NILPTR) {
		MainCounter++;
		y = x;
		if (Z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	Z->p = y;
	if (Z->key < y->key)
		y->left = Z;
	else
		y->right = Z;
	Z->left = NILPTR;
	Z->right = NILPTR;
	Z->color = RED;

	pred = predecessor(*treeroot, Z->key);

	Z->p = NILPTR;
	if (Z->key < y->key)
		y->left = NILPTR;
	else
		y->right = NILPTR;

	free(Z);
	return pred;
}

NODEPTR GetTailIndex(NODEPTR x)
{
	MainCounter++;
	if (x != NILPTR) {
		GetTailIndex(x->left);
		tail_node = x;
		GetTailIndex(x->right);
	
	}
	return tail_node;
}

int Call_LaIS(int max, bool printflag)
{
	int *x = new (nothrow) int[max];
	int *p = new (nothrow) int[max];
	int *out_ptr = new (nothrow) int[max];
	int c = 2;
	int n = max - 1;
	int output_index = 0;

	// Get the Inputs
	for(int i = 0; i < max; i++)
	{
		MainCounter++;
		x[i] = rand() % max + 1;

	}

	if(printflag)
	{
		for(int i = 0; i < max; i++)
			cout<<" "<<x[i];
	}

	NIL.left = NIL.right = NIL.p = NILPTR;
	NIL.color = BLACK;
	NODEPTR tree = NILPTR;

	lnode *v; 
	NODEPTR pred, s, temp;

	for(int i = 0; i < max; i++)
	{
		MainCounter++;
		v = new lnode();
		v->index = i;
		v->value = x[i];

		rbinsert(&tree, v);

		pred = predecessor(tree, x[i]);
		
		if(pred != NILPTR)
			p[i] = pred->ind;
		else
			p[i] = i;
		
		temp = predecessor_new(&tree, (x[i] + c));
		s = successor(temp, temp->key);
		
		if(s != NILPTR)
			rbdelete(&tree, s->key);
		delete v;
	}
	
	int t;
	NODEPTR tail;
	tail = GetTailIndex(tree);
	int m = tail->ind;

	for(int i = n; i >= (m+1); i--)
	{
		MainCounter++;
		if(((x[m]-c) < x[i]) && (x[i] <= x[m]))
		{
		//	cout<<" "<<x[i];
			out_ptr[output_index++] = x[i];
		}
	}
	//cout<<" "<<x[m];
	out_ptr[output_index++] = x[m];
	t = m;
	
	while(p[t] != t)
	{
		MainCounter++;
		for(int i = (t-1); i >= (p[t] + 1); i--)
		{
			MainCounter++;
			if(((x[p[t]]-c) < x[i]) && (x[i] <= x[p[i]]))
			{
			//	cout<<" "<<x[i];		
				out_ptr[output_index++] = x[i];
			}
		}
		//cout<<" "<<x[p[t]];
		out_ptr[output_index++] = x[p[t]];
		t = p[t];
	}
	
	if(printflag)
	{
		cout<<endl<<"The table 2-a Values: ";
		for(int i = 0; i <= output_index-1; i++)
			cout<<" "<<out_ptr[i];
		cout<<endl<<"The table 2-b Values: ";
		for(int i = 0; i <max; i++)
			cout<<" "<<p[i];
		cout<<endl<<"Output in the reverse order: ";
		for(int i = output_index-1; i >= 0; i--)
			cout<<" "<<out_ptr[i];
	}
	delete[] x;
	delete[] p;
	delete[] out_ptr;

	return output_index;
}

int main()
{
	int max = 0;
	int cnst = 1;
	double avg = 0.0;
	int sub_length;

//	ofstream myfile;
//	myfile.open ("Report.txt");
	max = 1000;
	sub_length = 0;
	for(int i = 0; i < 1000; i++)
	{
		sub_length = Call_LaIS(max, false);
		avg = MainCounter/cnst;
		cout<<endl<<"Iteration: "<<i+1<<endl;
		cout<<endl<<"Average: "<<avg<<endl;
		cout<<"Sub_Sequence Length: "<<sub_length<<endl;
		//myfile <<avg<<"\t"<<sub_length<<"\n";
		MainCounter = 0;
	}  
//	myfile.close();

	max = 20;
	for(int j = 0; j < 2; j++)
	{
		cout<<"Input sequence ";
		cout<<j+1<<": ";
		sub_length = Call_LaIS(max, true);
		cout<<endl<<endl;
	}
//	getch();

}