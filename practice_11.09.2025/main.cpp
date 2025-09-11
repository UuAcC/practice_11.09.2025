#include <iostream>
#include <stdint.h>
using namespace std;


// ������� ��� �����������:
// ��������� 1 �� ������� i � ������� ����� A: A |= (1 << i) 
// (�������� �� ������� i + 1, �� ���� ���� i = 2, �� �������� 1 � ������ ��� => ����� ����� 4)
// ��������� 0 �� ������� i � ������� ����� A: A &= ~(1 << i)
// ������� �� ������� �� 32: i & ((1 << 5) - 1)
// ������� �� ������� �� 32: a >> 5

class My_Own_Set
{
	// � ��� ������� ������ ���� �� ������� �������, ����� uint16
	// ����� ��� ��� ������ ��������� uint32 �����, ������ ��� ������� 
	// ������� ��� ����� �� ���������� � ���
	uint16_t size;
	uint32_t* segments;
public:
	My_Own_Set(uint16_t s) : size(s) { segments = new uint32_t[size >> 5]; }
	~My_Own_Set() { delete[] segments; }

	My_Own_Set(const My_Own_Set& copied_one)
	{
		size = copied_one.size;
		segments = new uint32_t[size >> 5];
		for (size_t i = 0; i < size; i++)
			segments[i] = copied_one.segments[i];
	}
	My_Own_Set& operator=(const My_Own_Set& copied_one)
	{
		if (this == &copied_one) return *this;
		delete[] segments;
		size = copied_one.size;
		segments = new uint32_t[size >> 5];
		for (size_t i = 0; i < size; i++)
			segments[i] = copied_one.segments[i];
	}

	uint16_t get_size() const { return size; }
	void set_size(uint16_t ns)
	{
		uint32_t* new_segments = new uint32_t[ns >> 5];
		for (size_t i = 0; i < size; i++)
			new_segments[i] = segments[i];
		delete[] segments;
		size = ns;
		segments = new_segments;
	}

	void add(uint16_t i) { segments[i >> 5] |= (1 << (i & ((1 << 5) - 1))); }
	void del(uint16_t i) { segments[i >> 5] &= ~(1 << (i & ((1 << 5) - 1))); }
	bool is_there(uint16_t i) { return segments[i >> 5] & (1 << i); }

	My_Own_Set& association(const My_Own_Set& what_associate_with)
	{
		for (size_t i = 0; i < size; i++)
			segments[i] |= what_associate_with.segments[i];
		return *this;
	}
	My_Own_Set& intersection(const My_Own_Set& what_intersect_with)
	{
		for (size_t i = 0; i < size; i++)
			segments[i] &= what_intersect_with.segments[i];
		return *this;
	}
	My_Own_Set& negation()
	{
		for (size_t i = 0; i < size; i++)
			segments[i] = ~(segments[i]);
		return *this;
	}

	void print_all()
	{
		for (size_t i = 0; i < size; i++)
			if (this->is_there(i)) { cout << i; }
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

	cout << "Enter how many elems you want to delete: "; cin >> cd; cout << endl;
	cout << "Enter elems to delete: " << endl;
	for (size_t i = 0; i < cd; i++) { cin >> d; mos.del(d); }
	
	return 0;
}

/*print_bit(uint16_t(~65536));*/