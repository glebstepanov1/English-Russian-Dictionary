#include "english_russian_dictionary.hpp"
#include <stdexcept>
#include "double_direction_list.hpp"

EnglishRussianDictionary::EnglishRussianDictionary() :
	root_(nullptr),
	size_(0)
{
}

EnglishRussianDictionary::~EnglishRussianDictionary()
{
	deleteDictionary(root_);
}

void EnglishRussianDictionary::insertWord(const std::string key, const std::string translation)
{
	if ((checkWord(key, "English") && checkWord(translation, "Russian")) == false)
	{
		throw std::invalid_argument("All words must be correct!\n(void EnglishRussianDictionary::insertWord(const std::string key, const std::string translation))");
	}

	if (root_ == nullptr)
	{
		root_ = new Word();
		root_->key_ = key;
		root_->translation_ += translation;
	}
	else
	{
		Word* current_word = root_;

		while (true)
		{
			if (key < current_word->key_)
			{
				if (current_word->left_)
				{
					current_word = current_word->left_;
				}
				else
				{
					Word* new_word = new Word();
					new_word->key_ = key;
					new_word->translation_ += translation;
					current_word->left_ = new_word;
					new_word->p_ = current_word;

					break;
				}
			}
			else if (key > current_word->key_)
			{
				if (current_word->right_)
				{
					current_word = current_word->right_;
				}
				else
				{
					Word* new_word = new Word();
					new_word->key_ = key;
					new_word->translation_ += translation;
					current_word->right_ = new_word;
					new_word->p_ = current_word;

					break;
				}
			}
			else if (key == current_word->key_)
			{
				current_word->translation_ += translation;

				return;
			}
		}
	}
}

void EnglishRussianDictionary::printWord(const std::string key) const
{
	if (checkWord(key, "English") == false)
	{
		throw std::invalid_argument("Word must be correct!\n(void EnglishRussianDictionary::printWord(const std::string key) const)");
	}

	Word* current_word = searchWordAndReturn(key);

	if (current_word)
	{
		std::cout << current_word->key_ << " - " << current_word->translation_ << '\n';
	}
	else
	{
		std::cout << "The word is not found :( / —лово не найдено :(";
	}
}

void EnglishRussianDictionary::deleteWord(const std::string key)
{
	if (checkWord(key, "English") == false)
	{
		throw std::invalid_argument("Word must be correct!\n(void EnglishRussianDictionary::deleteWord(const std::string key))");
	}

	Word* current_word = searchWordAndReturn(key);

	if (current_word == nullptr)
	{
		throw std::invalid_argument("Word not found!\n(void English_Russian_Dictionary::delete_word(const std::string word))");
	}

	//удаление листа
	if ((current_word->left_ == nullptr) && (current_word->right_ == nullptr))
	{
		if (current_word == root_)
		{
			delete root_;
			root_ = nullptr; //дает возможность работать с пустым деревом
		}
		else
		{
			if (current_word == current_word->p_->left_)
			{
				current_word->p_->left_ = nullptr;
			}

			if (current_word == current_word->p_->right_)
			{
				current_word->p_->right_ = nullptr;
			}

			delete current_word;
		}
	}
	//удаление узла с двум€ потомками
	else if (current_word->left_ && current_word->right_)
	{
		Word* successor = searchSuccessorAndReturn(key);

		//разрыв св€зи преемника со своим старым родителем
		if (successor == successor->p_->left_)
		{
			//передача детей преемника его родителю
			if (successor->right_)
			{
				successor->right_->p_ = successor->p_;
				successor->p_->left_ = successor->right_;
			}
			else if (successor->left_)
			{
				successor->left_->p_ = successor->p_;
				successor->p_->left_ = successor->left_;
			}
			else
			{
				successor->p_->left_ = nullptr;
			}
		}

		if (successor == successor->p_->right_)
		{
			//передача детей преемника его родителю
			if (successor->right_)
			{
				successor->right_->p_ = successor->p_;
				successor->p_->right_ = successor->right_;
			}
			else if (successor->left_)
			{
				successor->left_->p_ = successor->p_;
				successor->p_->right_ = successor->left_;
			}
			else
			{
				successor->p_->right_ = nullptr;
			}
		}

		//новый родитель
		successor->p_ = current_word->p_;

		//новые дети будут дальше

		//определение положени€ toDelete
		if (current_word == root_)
		{
			root_ = successor;
		}
		else
		{
			if (current_word == current_word->p_->left_)
			{
				current_word->p_->left_ = successor;
			}

			if (current_word == current_word->p_->right_)
			{
				current_word->p_->right_ = successor;
			}
		}

		//перенос потомков от toDelete к преемнику
		if (current_word->left_)
		{
			successor->left_ = current_word->left_;
			current_word->left_->p_ = successor;
		}

		if (current_word->right_)
		{
			successor->right_ = current_word->right_;
			current_word->right_->p_ = successor;
		}

		delete current_word;
	}
	//удаление узла с одним потомком
	else if (current_word->left_)
	{
		if (current_word == root_)
		{
			root_ = current_word->left_;
			root_->p_ = nullptr;
		}
		else
		{
			if (current_word == current_word->p_->left_)
			{
				current_word->p_->left_ = current_word->left_;
				current_word->left_->p_ = current_word->p_;
			}

			if (current_word == current_word->p_->right_)
			{
				current_word->p_->right_ = current_word->left_;
				current_word->left_->p_ = current_word->p_;
			}
		}

		delete current_word;
	}
	else if (current_word->right_)
	{
		if (current_word == root_)
		{
			root_ = current_word->right_;
			root_->p_ = nullptr;
		}
		else
		{
			if (current_word == current_word->p_->left_)
			{
				current_word->p_->left_ = current_word->right_;
				current_word->right_->p_ = current_word->p_;
			}

			if (current_word == current_word->p_->right_)
			{
				current_word->p_->right_ = current_word->right_;
				current_word->right_->p_ = current_word->p_;
			}
		}

		delete current_word;
	}
}

void EnglishRussianDictionary::deleteTranslation(const std::string key, const std::string translation)
{
	if ((checkWord(key, "English") && checkWord(translation, "Russian")) == false)
	{
		throw std::invalid_argument("All words must be correct!\n(void EnglishRussianDictionary::deleteTranslation(const std::string key, const std::string translation))");
	}

	Word* current_word = searchWordAndReturn(key);

	if (current_word == nullptr)
	{
		throw std::invalid_argument("Word not found!\n(void EnglishRussianDictionary::deleteTranslation(const std::string key, const std::string translation))");
	}

	if (current_word->translation_.getSize() == 1)
	{
		throw std::invalid_argument("This word has one translation!\n(void English_Russian_Dictionary::delete_translation(const std::string word, const std::string translation))");
	}

	try
	{
		current_word->translation_.deleteNode(translation);
	}
	catch (...)
	{
		throw std::invalid_argument("Translation not found!\n(void English_Russian_Dictionary::delete_translation(const std::string word, const std::string translation))");
	}
}

void EnglishRussianDictionary::print() const
{
	printWordsStartingWith(root_);
}

bool EnglishRussianDictionary::checkWord(const std::string word, const std::string language) const
{
	if (word.empty())
	{
		return false;
	}

	bool no_symbols = word.find_first_of("!@#є$;%:^&?*()-+=[]{}|/'.,") == std::string::npos;
	bool no_numbers = word.find_first_of("1234567890") == std::string::npos;

	if (language == "English")
	{
		bool ok_eng = (word.find_first_of("абвгдеЄжзийклмнопрстуфхцчшщъыьэю€јЅ¬√ƒ≈®∆«»… ЋћЌќѕ–—“”‘’÷„ЎўЏџ№Ёёя") == std::string::npos);
		return no_symbols && no_numbers && ok_eng;
	}
	else if (language == "Russian")
	{
		bool ok_rus = (word.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos);
		return no_symbols && no_numbers && ok_rus;
	}
	else
	{
		throw std::invalid_argument("I don't know that language :(\n(bool EnglishRussianDictionary::checkWord(const std::string word, const std::string language) const)");
	}
}

EnglishRussianDictionary::Word* EnglishRussianDictionary::searchWordAndReturn(const std::string key) const
{
	Word* current_word = root_;

	if (current_word == nullptr)
	{
		return nullptr;
	}

	while (key != current_word->key_)
	{
		if (key < current_word->key_)
		{
			if (current_word->left_)
			{
				current_word = current_word->left_;
			}
			else
			{
				return nullptr;
			}
		}
		else if (key > current_word->key_)
		{
			if (current_word->right_)
			{
				current_word = current_word->right_;
			}
			else
			{
				return nullptr;
			}
		}
	}

	return current_word;
}

EnglishRussianDictionary::Word* EnglishRussianDictionary::searchSuccessorAndReturn(const std::string key) const
{
	Word* current_word = searchWordAndReturn(key);

	if (current_word == nullptr)
	{
		return nullptr;
	}

	if (current_word->right_)
	{
		current_word = current_word->right_;

		while (current_word->left_)
		{
			current_word = current_word->left_;
		}

		return current_word;
	}

	while (current_word->p_)
	{
		if (current_word == current_word->p_->left_)
		{
			return current_word->p_;
		}
		else
		{
			current_word = current_word->p_;
		}
	}

	return nullptr;
}

void EnglishRussianDictionary::deleteDictionary(Word* word)
{
	if (word)
	{
		if (word->right_)
		{
			deleteDictionary(word->right_);
		}

		if (word->left_)
		{
			deleteDictionary(word->left_);
		}
	}

	delete word;
}

void EnglishRussianDictionary::printWordsStartingWith(Word* word) const
{
	if (word)
	{
		std::cout << word->key_ << " - " << word->translation_ << '\n';

		printWordsStartingWith(word->left_);
		printWordsStartingWith(word->right_);
	}
}
