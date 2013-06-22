#include "Ternary.h"

Tptr head = NULL;

int main(int argc, char** argv)
{
	TreeData_t d[5] = {0};
	d[0].len = 9;
	d[1].len = 9;
	d[2].len = 9;
	d[3].len = 9;
	d[4].len = 9;
	strcpy(d[0].prefix, "986");
	strcpy(d[1].prefix, "62");
	strcpy(d[2].prefix, "98");
	strcpy(d[3].prefix, "24");
	strcpy(d[4].prefix, "3");
	
	insert(head, d[0].prefix, (void*)&d[0]);
	insert(head, d[1].prefix, (void*)&d[1]);
	insert(head, d[2].prefix, (void*)&d[2]);
	insert(head, d[3].prefix, (void*)&d[3]);
	insert(head, d[4].prefix, (void*)&d[4]);

	Tptr nodes[5] = {NULL};
	int ret = getPrefix("986", (Tptr*)&nodes[0], 5);
	for (int ci = 0; ci<ret; ci++)
		cout<<"Matching prefix: "<<(char*)((TreeData_t*)nodes[ci]->data)->prefix<<endl;


	char findP[20] = "62";
	Tptr s = NULL;
	s = getExactPrefix(findP);
	if (!s)
		cout<<"Prefix: "<<findP<<" not present!."<<endl;

	char delPre[20] = "62";
	deletePrefix(delPre);
	
	display(head);

	cout<<"Nodes:-->"<<endl;
	displayNode(head);

	clean(head);
	return 0;
}

