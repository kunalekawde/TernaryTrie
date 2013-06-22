/*
Use this freely.
Kunal Ekawde kunalekawde2002 at yahoo com
*/

#ifndef _TERNARY_H_
#define _TERNARY_H_


typedef struct tnode* Tptr; 
typedef struct tnode*& TAptr; 

/* The Key could be integer string of alpha, basically alphanumeric*/


/* The data part, to be stored in tree, modify this to any type*/
typedef struct
{
	char prefix[20];
	int len;
}TreeData_t;


typedef struct tnode
{ 
	char alpha; 
	bool isWord; 
	Tptr left, equal, right, revEqual;
	void* data;
}Tnode; 


Tptr insert(TAptr p, char *s, void* data);
int getPrefix(char *f, Tptr* retarr, int max);
Tptr getExactPrefix(char *f);
void deletePrefix(char *d);
Tptr cleanBack(Tptr c);
void adjustLefthRightNode(Tptr& current);
void display(Tptr n);
void displayNode(Tptr n);
void clean(Tptr n);

#endif
