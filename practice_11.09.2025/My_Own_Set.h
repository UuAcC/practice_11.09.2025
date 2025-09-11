#pragma once

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
	uint16_t segments_count;
	uint32_t* segments;
public:
	My_Own_Set(uint16_t s);
	~My_Own_Set();

	My_Own_Set(const My_Own_Set& copied_one);

	My_Own_Set& operator=(const My_Own_Set& copied_one);

	uint16_t get_size() const;
	void set_size(uint16_t ns);

	void add(uint16_t i);
	void del(uint16_t i);
	bool is_there(uint16_t i) const;

	My_Own_Set& associateWith(const My_Own_Set& what_associate_with);
	My_Own_Set& intersectWith(const My_Own_Set& what_intersect_with);
	My_Own_Set& negate();

	static My_Own_Set association(const My_Own_Set& first, const My_Own_Set& second);
	static My_Own_Set intersection(const My_Own_Set& first, const My_Own_Set& second);
	static My_Own_Set negation(const My_Own_Set& what_to_negate);

	void print_all();
};

/*print_bit(uint16_t(~65536));*/