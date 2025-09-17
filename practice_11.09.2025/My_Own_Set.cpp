#include "My_Own_Set.h"

My_Own_Set::My_Own_Set(uint16_t s) : size(s)
{
	segments_count = (size + 31) >> 5;
	segments = new uint32_t[segments_count]();
}
My_Own_Set::~My_Own_Set() { delete[] segments; }

My_Own_Set::My_Own_Set(const My_Own_Set& copied_one)
{
	size = copied_one.size;
	segments_count = copied_one.segments_count;
	segments = new uint32_t[segments_count]();
	for (size_t i = 0; i < segments_count; i++)
		segments[i] = copied_one.segments[i];
}
My_Own_Set& My_Own_Set::operator=(const My_Own_Set& copied_one)
{
	if (this == &copied_one) return *this;
	delete[] segments;
	size = copied_one.size;
	segments_count = copied_one.segments_count;
	segments = new uint32_t[segments_count]();
	for (size_t i = 0; i < segments_count; i++)
		segments[i] = copied_one.segments[i];
}

uint16_t My_Own_Set::get_size() const { return size; }
void My_Own_Set::set_size(uint16_t ns)
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

void My_Own_Set::add(uint16_t i) { if (i < size) segments[i >> 5] |= (1 << (i & 31)); }
void My_Own_Set::del(uint16_t i) { if (i < size) segments[i >> 5] &= ~(1 << (i & 31)); }

My_Own_Set& My_Own_Set::operator+(uint16_t i)
{
	if (i < size) segments[i >> 5] |= (1 << (i & 31));
	return *this;
}
My_Own_Set& My_Own_Set::operator-(uint16_t i)
{
	if (i < size) segments[i >> 5] &= ~(1 << (i & 31));
	return *this;
}

bool My_Own_Set::is_there(uint16_t i) const
{
	if (i >= size) return false;
	return segments[i >> 5] & (1 << (i & 31));
}

My_Own_Set& My_Own_Set::associateWith(const My_Own_Set& what_associate_with)
{
	uint16_t min;
	if (segments_count < what_associate_with.segments_count)
		min = segments_count;
	else min = what_associate_with.segments_count;
	for (size_t i = 0; i < min; i++)
		segments[i] |= what_associate_with.segments[i];
	return *this;
}
My_Own_Set& My_Own_Set::intersectWith(const My_Own_Set& what_intersect_with)
{
	uint16_t min;
	if (segments_count < what_intersect_with.segments_count)
		min = segments_count;
	else min = what_intersect_with.segments_count;
	for (size_t i = 0; i < min; i++)
		segments[i] &= what_intersect_with.segments[i];
	return *this;
}
My_Own_Set& My_Own_Set::negate()
{
	for (size_t i = 0; i < segments_count; i++)
		segments[i] = ~(segments[i]);
	return *this;
}

My_Own_Set& My_Own_Set::operator|(const My_Own_Set& what_associate_with) 
{ 
	this->associateWith(what_associate_with); 
	return *this;
}
My_Own_Set& My_Own_Set::operator&(const My_Own_Set& what_intersect_with) 
{ 
	this->intersectWith(what_intersect_with); 
	return *this;
}
My_Own_Set& My_Own_Set::operator~() 
{ 
	this->negate(); 
	return *this;
}

My_Own_Set My_Own_Set::association(const My_Own_Set& first, const My_Own_Set& second)
{
	if (first.size >= second.size)
		return My_Own_Set(first).associateWith(second);
	return My_Own_Set(second).associateWith(first);
}
My_Own_Set My_Own_Set::intersection(const My_Own_Set& first, const My_Own_Set& second)
{
	if (first.size >= second.size)
		return My_Own_Set(first).intersectWith(second);
	return My_Own_Set(second).intersectWith(first);
}
My_Own_Set My_Own_Set::negation(const My_Own_Set& what_to_negate)
{
	return My_Own_Set(what_to_negate).negate();
}

void My_Own_Set::print_all()
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

ostream& operator<<(ostream& out, const My_Own_Set& set)
{
	uint16_t s = set.get_size() - 1; out << "{";
	bool flag = false;
	for (size_t i = 0; i < s; i++)
		if (set.is_there(i))
		{
			if (flag) out << ", ";
			out << i; flag = true;
		}
	if (set.is_there(s)) { out << ", " << s; }
	out << "}" << endl;
	return out;
}