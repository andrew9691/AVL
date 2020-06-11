#include <iostream>
#include <ctime>
#include <set>
#include "AVL-Tree.h"

using namespace std;

int main()
{
	AVL<int> t(20);
	t.add(10);
	t.add(9);
	t.add(8);
	t.add(7);
	t.add(6);
	t.add(5);
	t.add(4);
	t.add(3);
	t.print();
	cout << endl << endl;
	t.erase(20);
	t.erase(9);
	t.print();
	cout << endl << "Rotations: " << t.get_rotations() << endl;

	AVLSet<int> aset;
	cout << "--------------------insert-----------------------" << endl << endl;
	time_t start = clock();

	for (int i = 1; i <= 100000; i++)
	{
		int x = rand() % 100000 + 1;
		if (!aset.is_in_tree(x))
			aset.avl_set_add(x);
	}
	cout << "AVL set insert : " << double(clock() - start) / CLOCKS_PER_SEC << " seconds" << endl;

	set<int> s;
	start = clock();
	for (int i = 1; i <= 100000; i++)
	{
		int x = rand() % 100000 + 1;
		s.insert(x);
	}
	cout << "Set insert: " << double(clock() - start) / CLOCKS_PER_SEC << " seconds" << endl << endl;


	cout << "--------------------remove-----------------------" << endl << endl;

	start = clock();
	for (int i = 1; i <= 80000; i++)
		aset.avl_set_del(i);

	cout << "AVL set remove: " << double(clock() - start) / CLOCKS_PER_SEC << " seconds" << endl;

	start = clock();
	for (int i = 1; i <= 80000; i++)
		s.erase(i);
	cout << "Set remove: " << double(clock() - start) / CLOCKS_PER_SEC << " seconds" << endl << endl;
}
