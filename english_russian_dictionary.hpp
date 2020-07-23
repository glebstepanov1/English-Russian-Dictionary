#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>
#include "double_direction_list.hpp"

class EnglishRussianDictionary
{
	class Word
	{
	public:
		std::string key_;
		List translation_;
		Word* left_;
		Word* right_;
		Word* p_;

		Word() :
			key_(""),
			translation_(List()),
			left_(nullptr),
			right_(nullptr),
			p_(nullptr)
		{
		}
	};

	Word* root_;
	std::size_t size_;

public:
	EnglishRussianDictionary();
	~EnglishRussianDictionary();
	void insertWord(const std::string key, const std::string translation);
	void printWord(const std::string key) const;
	void deleteWord(const std::string key);
	void deleteTranslation(const std::string key, const std::string translation);
	void print() const;
	bool checkWord(const std::string word, const std::string language) const;

private:
	Word* searchWordAndReturn(const std::string key) const;
	Word* searchSuccessorAndReturn(const std::string key) const;
	void deleteDictionary(Word* word);
	void printWordsStartingWith(Word* word) const;
};

#endif
