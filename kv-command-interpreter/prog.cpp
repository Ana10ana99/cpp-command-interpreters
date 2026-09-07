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
#include <map>
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

  map<char, vector<char>> datastore;

  string command;

  while (inputFile >> command)
  {
    char key;

    if (command == "create")
    {
      inputFile >> key;

      if (datastore.find(key) == datastore.end())
      {
        datastore[key] = {};
      }

      outputFile << "datastore[" << key << "] = {";

      for (size_t i = 0; i < datastore[key].size(); i++)
      {
        outputFile << datastore[key][i];

        if (i != datastore[key].size() - 1)
        {
          outputFile << ", ";
        }
      }

      outputFile << "}" << endl;
    }

    else if (command == "read")
    {
      inputFile >> key;

      if (datastore.find(key) == datastore.end())
      {
        outputFile << "no-key " << key << endl;
      }
      else
      {
        outputFile << "datastore[" << key << "] = {";

        for (size_t i = 0; i < datastore[key].size(); i++)
        {
          outputFile << datastore[key][i];

          if (i != datastore[key].size() - 1)
          {
            outputFile << ", ";
          }
        }

        outputFile << "}" << endl;
      }
    }

    else if (command == "insert")
    {
      char value;
      inputFile >> key >> value;

      if (datastore.find(key) == datastore.end())
      {
        outputFile << "no-key " << key << endl;
      }
      else
      {
        bool alreadyExists = false;

        for (char existingValue : datastore[key])
        {
          if (existingValue == value)
          {
            alreadyExists = true;
          }
        }

        if (!alreadyExists)
        {
          datastore[key].push_back(value);
        }

        outputFile << "datastore[" << key << "] = {";

        for (size_t i = 0; i < datastore[key].size(); i++)
        {
          outputFile << datastore[key][i];

          if (i != datastore[key].size() - 1)
          {
            outputFile << ", ";
          }
        }

        outputFile << "}" << endl;
      }
    }

    else if (command == "delete")
    {
      inputFile >> key;

      if (datastore.find(key) == datastore.end())
      {
        outputFile << "no-key " << key << endl;
      }
      else
      {
        datastore.erase(key);
        outputFile << "no-key " << key << endl;
      }
    }
  }

  return 0;
}