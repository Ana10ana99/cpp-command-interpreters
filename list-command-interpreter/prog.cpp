/*
  This is a small program to demonstrate gcov. It
  can take no arguments or 1 argument. It prints
  a message if more than one is given. If the argument's
  value is odd it prints out odd, otherwise even.
  The goal is to show you need multiple test cases
  to cover all of the code.

  -richard.m.veras@ou.edu
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
  // STUDENT_TODO

  if (argc != 3)
  {
    cout << "I need an input and output file!\n";
    return 1;
  }

  ifstream inputFile(argv[1]);
  ofstream outputFile(argv[2]);

  vector<char> list;

  string command;
  int maxSize;

  // Read the spec line
  inputFile >> command >> maxSize;

  // The list starts empty
  outputFile << "0: 0 |" << endl;

  int lineNumber = 1;

  // Read each command from the input file
  while (inputFile >> command)
  {
    bool fullInsert = false;
    bool emptyRemove = false;
    bool insertAtFront = false;
    bool insertAtBack = false;
    char attemptedValue = '\0';

    if (command == "insert-front")
    {
      char value;
      inputFile >> value;

      if (maxSize < 0 || static_cast<int>(list.size()) < maxSize)
      {
        list.insert(list.begin(), value);
      }
      else
      {
        fullInsert = true;
        insertAtFront = true;
        attemptedValue = value;
      }
    }

    else if (command == "insert-back")
    {
      char value;
      inputFile >> value;

      if (maxSize < 0 || static_cast<int>(list.size()) < maxSize)
      {
        list.push_back(value);
      }
      else
      {
        fullInsert = true;
        insertAtBack = true;
        attemptedValue = value;
      }
    }

    else if (command == "remove-front" || command == "remove-back")
    {
      if (list.empty())
      {
        emptyRemove = true;
      }
      else if (command == "remove-front")
      {
        list.erase(list.begin());
      }
      else
      {
        list.pop_back();
      }
    }

    // Print line number and current list size
    outputFile << lineNumber << ": " << list.size() << " |";

    // Tried to remove from an empty list
    if (emptyRemove)
    {
      outputFile << " ()^";
    }

    // Tried to insert at the front of a full list
    else if (fullInsert && insertAtFront)
    {
      outputFile << " " << attemptedValue << "^";

      for (char value : list)
      {
        outputFile << " " << value;
      }
    }

    // Tried to insert at the back of a full list
    else if (fullInsert && insertAtBack)
    {
      for (char value : list)
      {
        outputFile << " " << value;
      }

      outputFile << " " << attemptedValue << "^";
    }

    // Normal output
    else
    {
      for (char value : list)
      {
        outputFile << " " << value;
      }
    }

    outputFile << endl;

    lineNumber++;
  }

  return 0;
}