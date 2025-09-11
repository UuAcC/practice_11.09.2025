#include <iostream>
#include <stdint.h>
using namespace std;

// краткое для копирования:
// поставить 1 на позицию i в битовом числе A: A |= (1 << i) 
// (поставит на позицию i + 1, то есть если i = 2, то поставит 1 в третий бит => число будет 4)
// поставить 0 на позицию i в битовом числе A: A &= ~(1 << i)
// остаток от деления на 32: i & ((1 << 5) - 1)
// частное от деления на 32: a >> 5

class My_Own_Set
{
	// у нас разброс должен быть не слишком большой, тогда uint16
	// тогда нам нет смысла добавлять uint32 числа, потому что слишком 
	// большие все равно не запихнутся в сет
	uint16_t size;
	uint16_t segments_count;
	uint32_t* segments;
public:
	My_Own_Set(uint16_t s) : size(s) 
	{ 
		segments_count = (size + 31) >> 5;
		segments = new uint32_t[segments_count](); 
	}
	~My_Own_Set() { delete[] segments; }

	My_Own_Set(const My_Own_Set& copied_one)
	{
		size = copied_one.size;
		segments_count = copied_one.segments_count;
		segments = new uint32_t[segments_count]();
		for (size_t i = 0; i < segments_count; i++)
			segments[i] = copied_one.segments[i];
	}
	My_Own_Set& operator=(const My_Own_Set& copied_one)
	{
		if (this == &copied_one) return *this;
		delete[] segments;
		size = copied_one.size;
		segments_count = copied_one.segments_count;
		segments = new uint32_t[segments_count]();
		for (size_t i = 0; i < segments_count; i++)
			segments[i] = copied_one.segments[i];
	}

	uint16_t get_size() const { return size; }
	void set_size(uint16_t ns)
	{
		uint16_t nsc = (ns + 31) >> 5;
		uint32_t* new_segments = new uint32_t[nsc]();
		uint16_t min = (segments_count < nsc) ? segments_count : nsc;
		for (size_t i = 0; i < min; i++)
			new_segments[i] = segments[i];
		delete[] segments;
		size = ns;
		segments_count = nsc;
		segments = new_segments;
	}

	void add(uint16_t i) { if (i < size) segments[i >> 5] |= (1 << (i & 31)); }
	void del(uint16_t i) { if (i < size) segments[i >> 5] &= ~(1 << (i & 31)); }
	bool is_there(uint16_t i) const
	{
		if (i >= size) return false;
		return segments[i >> 5] & (1 << (i & 31));
	}

	My_Own_Set& associateWith(const My_Own_Set& what_associate_with)
	{
		uint16_t min;
		if (segments_count < what_associate_with.segments_count)
			min = segments_count;
		else min = what_associate_with.segments_count;
		for (size_t i = 0; i < min; i++)
			segments[i] |= what_associate_with.segments[i];
		return *this;
	}
	My_Own_Set& intersectWith(const My_Own_Set& what_intersect_with)
	{
		uint16_t min;
		if (segments_count < what_intersect_with.segments_count)
			min = segments_count;
		else min = what_intersect_with.segments_count;
		for (size_t i = 0; i < min; i++)
			segments[i] &= what_intersect_with.segments[i];
		return *this;
	}
	My_Own_Set& negate()
	{
		for (size_t i = 0; i < segments_count; i++)
			segments[i] = ~(segments[i]);
		return *this;
	}

	static My_Own_Set association(const My_Own_Set& first, const My_Own_Set& second)
	{
		if (first.size >= second.size)
			return My_Own_Set(first).associateWith(second);
		return My_Own_Set(second).associateWith(first);
	}
	static My_Own_Set intersection(const My_Own_Set& first, const My_Own_Set& second)
	{
		if (first.size >= second.size)
			return My_Own_Set(first).intersectWith(second);
		return My_Own_Set(second).intersectWith(first);
	}
	static My_Own_Set negation(const My_Own_Set& what_to_negate)
	{
		return My_Own_Set(what_to_negate).negate();
	}

	void print_all()
	{
		uint16_t s = size - 1; cout << "{";
		bool flag = false;
		for (size_t i = 0; i < s; i++)
			if (this->is_there(i)) 
			{ 
				if (flag) cout << ", ";
				cout << i; flag = true;
			}
		if (this->is_there(s)) { cout << ", " << s; }
		cout << "}" << endl;
	}
};

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

/*print_bit(uint16_t(~65536));*/