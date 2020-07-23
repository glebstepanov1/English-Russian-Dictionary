#include <iostream>
#include <windows.h>
#include "english_russian_dictionary.hpp"

int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  EnglishRussianDictionary ERD;

  try
  {
    //добавление новых слов с проверкой на алфавитный порядок переводов
    ERD.insertWord("call", "называть");
    ERD.insertWord("fuss", "суетиться");
    ERD.insertWord("fuss", "волноваться");
    ERD.insertWord("wrap up", "кутаться");
    ERD.insertWord("ahead", "вперёд");
    ERD.insertWord("ahead", "впереди");
    ERD.insertWord("alone", "одинокий");
    ERD.insertWord("chilly", "прохладный");
    ERD.insertWord("chilly", "зябко");
    ERD.insertWord("alone", "один");
    ERD.insertWord("break", "ломать");
    ERD.insertWord("actually", "фактически");
    ERD.insertWord("actually", "на самом деле");
    ERD.insertWord("break", "разбивать");
    ERD.insertWord("wonderful", "замечательный");
    ERD.insertWord("breakfast", "завтрак");
    ERD.insertWord("brother", "брат");
    ERD.insertWord("call", "звать");
    ERD.insertWord("call", "навещать");
    ERD.insertWord("zebra", "зебра");
    ERD.insertWord("calm", "спокойный");
    ERD.insertWord("chilly", "холодно");
    ERD.insertWord("fortnight", "две недели");
    ERD.insertWord("furious", "взбешённый");

    //проверка на повторы
    ERD.insertWord("call", "звать");
    ERD.insertWord("call", "называть");
    ERD.insertWord("call", "навещать");
    ERD.insertWord("calm", "спокойный");
    ERD.insertWord("chilly", "прохладный");
    ERD.insertWord("chilly", "зябко");
    ERD.insertWord("chilly", "холодно");
    ERD.insertWord("fortnight", "две недели");
    ERD.insertWord("furious", "взбешённый");
    ERD.insertWord("fuss", "суетиться");
    ERD.insertWord("fuss", "волноваться");
  }
  catch (const std::invalid_argument& ia)
  {
    std::cerr << ia.what();
    return -1;
  }
  
  char option;

  while (true)
  {
    std::cout << "\t\tEnglish-Russian Dictionary\n\n\n1. Show the dictioanary\n2. Find word\n3. Add word/translation\n4. Delete word\n5. Delete translation\n\n0. Close program\n\n\nChoose the option: ";
    std::cin >> option;

    system("cls");

    switch (option)
    {
    case '1':
    {
      ERD.print();
      system("pause >> void");
      system("cls");
      break;
    }
    case '2':
    {
      std::string search_word;
      std::cout << "Enter a search word: ";
      std::cin >> search_word;

      std::cout << "\n\nResult: ";

      try
      {
        ERD.printWord(search_word);
      }
      catch (const std::invalid_argument& ia1)
      {
        std::cerr << '\n' << ia1.what();
        system("pause >> void");
        system("cls");
        break;
      }

      system("pause >> void");
      system("cls");
      break;
    }
    case '3':
    {
      std::string word_to_add;
      std::cout << "Enter a word to add: ";
      std::cin >> word_to_add;

      std::string translation;
      std::cout << "\n\nEnter the translation: ";
      std::cin >> translation;

      try
      {
        ERD.insertWord(word_to_add, translation);
      }
      catch (const std::invalid_argument& ia2)
      {
        std::cerr << '\n' << ia2.what();
        system("pause >> void");
        system("cls");
        break;
      }

      std::cout << "\n\nWord and translation added!";
      system("pause >> void");
      system("cls");
      break;
    }
    case '4':
    {
      std::string word_to_delete;
      std::cout << "Enter a word to delete: ";
      std::cin >> word_to_delete;

      try
      {
        ERD.deleteWord(word_to_delete);
      }
      catch (const std::invalid_argument& ia3)
      {
        std::cerr << '\n' << ia3.what();
        system("pause >> void");
        system("cls");
        break;
      }

      std::cout << "\n\nWord deleted!";
      system("pause >> void");
      system("cls");
      break;
    }
    case '5':
    {
      std::string word;
      std::cout << "Enter a word: ";
      std::cin >> word;

      std::string translation_to_delete;
      std::cout << "\n\nEnter the translation to delete: ";
      std::cin >> translation_to_delete;

      try
      {
        ERD.deleteTranslation(word, translation_to_delete);
      }
      catch (const std::invalid_argument& ia4)
      {
        std::cerr << '\n' << ia4.what();
        system("pause >> void");
        system("cls");
        break;
      }

      std::cout << "\n\nTranslation deleted!";
      system("pause >> void");
      system("cls");
      break;
    }
    case '0':
    {
      return 0;
    }
    default:
    {
      break;
    }
    }
  }

  return 0;
}
