#include "double_direction_list.hpp"
#include <stdexcept>

List::List() :
	head_(nullptr),
	size_(0)
{
}

List::~List()
{
	while (size_)
	{
		Node* old_head = head_;
		head_ = head_->next_;
		size_--;
		delete old_head;
	}
}

std::size_t List::getSize() const
{
	return size_;
}

List& List::deleteNode(const std::string data)
{
	Node* current = searchNodeAndReturn(data);

	if (current == nullptr)
	{
		throw std::invalid_argument("Node not found!\n(List& List::delete_node(const std::string data))");
	}

	//один узел
	if ((current == head_) && (current->next_ == nullptr))
	{
		delete current;
		head_ = nullptr;
		return *this;
	}
	//голова
	else if (current == head_)
	{
		head_ = head_->next_;
		head_->prev_ = nullptr;
	}
	//хвост
	else if (current->next_ == nullptr)
	{
		current->prev_->next_ = nullptr;
	}
	//середина
	else
	{
		current->prev_->next_ = current->next_;
		current->next_->prev_ = current->prev_;
	}

	size_--;
	delete current;
	return *this;
}

List& List::operator+=(const std::string data)
{
	if (head_ == nullptr)
	{
		head_ = new Node;
		head_->data_ = data;
	}
	else
	{
		Node* current = head_;

		while (data >= current->data_)
		{
			if (data == current->data_)
				return *this;
			
			if (current->next_)
				current = current->next_;
			else
				break;
		}

		if (current == head_ && data < current->data_)
		{
			Node* old_head = head_;
			head_ = new Node;
			head_->data_ = data;
			head_->next_ = old_head;
			old_head->prev_ = head_;
		}
		else if (current->next_ == nullptr && data > current->data_)
		{
			Node* new_node = new Node;
			new_node->data_ = data;
			new_node->prev_ = current;
			current->next_ = new_node;
		}
		else
		{
			Node* new_node = new Node;
			new_node->data_ = data;
			current->prev_->next_ = new_node;
			new_node->prev_ = current->prev_;
			current->prev_ = new_node;
			new_node->next_ = current;
		}
	}

	size_++;
	return *this;
}

List::Node* List::searchNodeAndReturn(const std::string data) const
{
	List::Node* current = head_;

	while (current)
	{
		if (data == current->data_)
		{
			return current;
		}

		current = current->next_;
	}

	return nullptr;
}

std::ostream& operator<<(std::ostream& out, const List& List)
{
	if (List.head_)
	{
		List::Node* current = List.head_;

		while (current->next_)
		{
			out << current->data_ << ", ";
			current = current->next_;
		}

		out << current->data_;
	}

	return out;
}
