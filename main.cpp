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
    //���������� ����� ���� � ��������� �� ���������� ������� ���������
    ERD.insertWord("call", "��������");
    ERD.insertWord("fuss", "���������");
    ERD.insertWord("fuss", "�����������");
    ERD.insertWord("wrap up", "��������");
    ERD.insertWord("ahead", "�����");
    ERD.insertWord("ahead", "�������");
    ERD.insertWord("alone", "��������");
    ERD.insertWord("chilly", "����������");
    ERD.insertWord("chilly", "�����");
    ERD.insertWord("alone", "����");
    ERD.insertWord("break", "������");
    ERD.insertWord("actually", "����������");
    ERD.insertWord("actually", "�� ����� ����");
    ERD.insertWord("break", "���������");
    ERD.insertWord("wonderful", "�������������");
    ERD.insertWord("breakfast", "�������");
    ERD.insertWord("brother", "����");
    ERD.insertWord("call", "�����");
    ERD.insertWord("call", "��������");
    ERD.insertWord("zebra", "�����");
    ERD.insertWord("calm", "���������");
    ERD.insertWord("chilly", "�������");
    ERD.insertWord("fortnight", "��� ������");
    ERD.insertWord("furious", "����������");

    //�������� �� �������
    ERD.insertWord("call", "�����");
    ERD.insertWord("call", "��������");
    ERD.insertWord("call", "��������");
    ERD.insertWord("calm", "���������");
    ERD.insertWord("chilly", "����������");
    ERD.insertWord("chilly", "�����");
    ERD.insertWord("chilly", "�������");
    ERD.insertWord("fortnight", "��� ������");
    ERD.insertWord("furious", "����������");
    ERD.insertWord("fuss", "���������");
    ERD.insertWord("fuss", "�����������");
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
