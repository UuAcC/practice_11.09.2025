#include "My_Own_Set.h"

template <class T>
void print_bit(T v)
{
	int size = sizeof(v) * 8;
	for (size_t i = 0; i < size; i++)
	{
		if (v & (1 << i)) cout << "1";
		else cout << "0";
	}
	cout << endl;
}

int main()
{
	uint16_t s, ca, cd, a, d;

	cout << "Enter size: "; cin >> s; cout << endl;
	My_Own_Set mos = My_Own_Set(s);

	cout << "Enter how many elems you want to add: "; cin >> ca; cout << endl;
	cout << "Enter elems to add: " << endl;
	for (size_t i = 0; i < ca; i++) { cin >> a; mos.add(a); }
	mos.print_all();

	cout << "Enter how many elems you want to delete: "; cin >> cd; cout << endl;
	cout << "Enter elems to delete: " << endl;
	for (size_t i = 0; i < cd; i++) { cin >> d; mos.del(d); }
	mos.print_all();
	cout << endl;
	My_Own_Set mos2 = My_Own_Set::negation(mos);
	mos2.print_all();
	cout << endl;
	My_Own_Set mos3 = My_Own_Set::association(mos, mos2).intersectWith(mos);
	mos3.print_all();
	cout << endl;
	
	return 0;
}
