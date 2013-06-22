/*
Use this freely.
Kunal Ekawde kunalekawde2002 at yahoo com
*/

#include "Ternary.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
typedef struct tnode* Tptr; 
typedef struct tnode*& TAptr; 


Tptr insert(TAptr p, char *s, void* data)
{
	if (p == 0) 
	{ 
		p = new Tnode; 
		p->alpha = *s; 
		p->left = p->equal = p->right = p->revEqual= 0;
	}
	
	if (*s < p->alpha) 
		p->left = insert(p->left, s, data); 
	else if (*s == p->alpha) 
	{ 
		if (*++s != 0)
		{
			p->equal = insert(p->equal, s, data);
			p->equal->revEqual = p;
		}
		else
		{
			p->isWord = true;
			p->data = data;
		}
	} 
	else 
		p->right = insert(p->right, s, data); 
	
	return p; 
} 


/* Get all matching prefixes */
int getPrefix(char *f, Tptr* retarr, int max)
{
	if ( max < 1 )
		return 0;

	int ret = 0;
	Tptr p = head;

	if (*f == 0)
		return ret;

	while (*f && p)
	{
		if (ret >= max)
			return max;

		if (*f > p->alpha)
			p = p->right;
		else if (*f < p->alpha)
			p = p->left;
		else
		{
			if (*f++ == p->alpha)
			{
				if (p->isWord == true)
				{
					if (ret<max)
						retarr[ret++] = p;
				}
				p = p->equal;
			}
		}
	}
	return ret;
}

/*Get the exact prefix/key*/
Tptr getExactPrefix(char *f)
{
	Tptr p = head;

	if (*f == 0)
		return NULL;

	while (*f && p)
	{
		if (*f > p->alpha)
			p = p->right;
		else if (*f < p->alpha)
			p = p->left;
		else
		{
			if (*f++ == p->alpha)
			{
				if (p->isWord == true && *f == 0)
				{
					cout<<"Prefix: "<<(char*)((TreeData_t*)p->data)->prefix<<" present!."<<endl;
					return p;
				}
				p = p->equal;
			}
		}
	}
	return NULL;
}


/*Delete a key from the tree*/
void deletePrefix(char *d)
{
	Tptr current = head;
	Tptr currParent = NULL;

	while(*d && current)
	{
		if (*d > current->alpha)
		{
			currParent = current;
			current = current->right;
		}
		else if (*d < current->alpha)
		{
			currParent = current;
			current = current->left;
		}
		else
		{
			if ((current->alpha == *(d++)) && (*d == 0) )
			{
				if (current->isWord == true)
				{
					if ( current->equal )
					{
						current->isWord = false;
					}
					else if ( current->right && !current->left )
					{
						if(currParent)
						{
							if (currParent->equal == current)
							{
								currParent->equal = current->right;
								currParent->equal->revEqual = currParent;
							}
							else if (currParent->right == current)
								currParent->right = current->right;
							else
								currParent->left = current->right;
						}
						else
							head = current->right;
						
						delete current;
						current = NULL;
					}
					else if ( current->left && !current->right )
					{
						if(currParent)
						{
							if (currParent->equal == current)
							{
								currParent->equal = current->left;
								currParent->equal->revEqual = currParent;
							}
							else if (currParent->right == current)
								currParent->right = current->left;
							else
								currParent->left = current->left;
						}
						else
							head = current->left;

						delete current;
						current = NULL;
					}
					else if (  current->right && current->left ) 
					{
						if ( current->left->right )
						{
							adjustLefthRightNode(current);
							if (currParent)
							{
								currParent->equal = current->left;
								currParent->equal->right = current->right;
							}
							else
							{
								head = current->left;
								head->right = current->right;
							}

							delete current;
							current = NULL;
						}
						/*else if ( current->right->left )
						{
							//TODO:its either of above
						}*/
						else
						{
							if (currParent && currParent->equal)
							{
								currParent->equal = current->left;
								currParent->equal->right = current->right;
							}
							else if (currParent && (currParent->left == current))
							{
								currParent->left = current->left;
								currParent->left->right = current->right;
							}
							else if (currParent && (currParent->right == current))
							{
								currParent->right = current->left;
								currParent->right->right = current->right;
							}
							else
							{
								head = current->left;
								head->right = current->right;
							}
							delete current;
							current = NULL;
						}
					}
					else //was only word
					{
						if (currParent && (currParent->left == current))
						{
							currParent->left = NULL;
						}
						else if (currParent && (currParent->right == current))
						{
							currParent->right = NULL;
						}
						else
						{
							if (currParent)
							{
								Tptr cp = cleanBack(current);
								if ( cp && cp->isWord == false)
								{
									if (cp->left)
									{
										if (  cp->left->right && cp->right )
											adjustLefthRightNode(cp);

										Tptr cpLeft = cp->left;

										cp->isWord = cp->left->isWord;
										cp->alpha = cp->left->alpha;
										cp->data = cp->left->data;
										if (cp->left->equal)
										{
											cp->equal = cp->left->equal;
											cp->equal->revEqual = cp;
										}
										if (cp->left->revEqual)
											cp->revEqual = cp->left->revEqual;

										if (cp->left->right)
											cp->right = cp->left->right;

										if (cp->left->left)
											cp->left = cp->left->left;
										else
											cp->left = NULL;

										delete cpLeft;
										cpLeft = NULL;
									}
								}
							}
						}
						delete current;
						if (current == head)
							head = NULL;
						current = NULL;
					}
				}
			}
			else
			{
				currParent = current;
				current = current->equal;
			}
		}
	}
}

void adjustLefthRightNode(Tptr& current)
{
	Tptr clr = current->left->right; //one to be moved
	Tptr cr = current->right;
	Tptr pcr = NULL; 
	while(cr)
	{
		pcr = cr;
		cr = cr->left;
	}
	pcr->left = clr;
	current->left->right = NULL;
}


Tptr  cleanBack(Tptr c)
{
	Tptr cp = c->revEqual;
	Tptr cpp = NULL;

	while(cp)
	{
		if (cp->right == NULL && cp->left == NULL && cp->isWord == false)
		{
			cp->equal = NULL;
			cpp = cp->revEqual;
			if (cp == head)
				head = NULL;
			delete cp;
			cp = cpp;
		}
		else
		{
			cp->equal = NULL;
			break;
		}
	}
	return cp;
}

void display(Tptr n)
{
	if (n == 0)
		return;
	display(n->left);
	if (n && n->isWord)
			cout<<" "<<(char*)((TreeData_t*)n->data)->prefix<<endl;
	display(n->equal);
	display(n->right);
}

void displayNode(Tptr n)
{
	if (n == 0)
		return;
	displayNode(n->left);
	if (n)
		cout<<" "<<n->alpha<<endl;
	displayNode(n->equal);
	displayNode(n->right);
}

void clean(Tptr n)
{
	if (n == NULL)
		return;
	clean(n->left);
	if (n && n->isWord)
	{
		delete n;
		n = NULL;
	}
	if (n != NULL)
		clean(n->equal);
	if (n != NULL)
		clean(n->right);
}
