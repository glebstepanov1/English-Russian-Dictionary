#ifndef DOUBLE_DIRECTION_LIST_HPP
#define DOUBLE_DIRECTION_LIST_HPP

#include <iostream>

class List
{
	class Node
	{
	public:
		std::string data_;
		Node* next_;
		Node* prev_;

		Node() :
			data_(""),
			next_(nullptr),
			prev_(nullptr)
		{
		}
	};

	Node* head_;
	std::size_t size_;

public:
	List();
	~List();
	std::size_t getSize() const;
	List& deleteNode(const std::string data);
	List& operator+=(const std::string data);
	friend std::ostream& operator<<(std::ostream& out, const List& List);

private:
	Node* searchNodeAndReturn(const std::string data) const;
};

#endif
