#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
using namespace std;
#define MAX 100000
void Menu(int&);
void expresie(ifstream& myfile, string Infix);
const int SIZE = 20;
class Operanzi {
public:
    virtual int Eval(string temp[])=0;
};
class Schimbare
{
public:
    string Change_me(string my_string)
    {
        for (int i = 0; i < my_string.length(); i++)
        {
            if (my_string[i] == '-')
            {
                if (my_string[i - 1] != 'v' && (my_string[i - 1] != ')'))
                {
                   return my_string.replace(i, 1, "y");
                }
            }
        }
    }
};
class InserareOperatii {
public:
    string Insert_comma(string my_string)
    {
        for (int i = 0; i < my_string.length(); i++)
        {
            if (my_string[i] == 'y')
            {
                return my_string.replace(i, 1, "-");
            }
        }
    }
};
class Afisare
{
public:
    void Menu(int& choice)
    {
        cout << "\n    Atentie! Se va scrie in sample.txt si se va afisa in test.txt!";
        cout << "\n    Pentru profesor(in caz ca nu a vazut): am trimis un fisier text la cealalta faza destul de important";
        cout << "\n    Alege o optiune";
        cout << "\n...................................";
        cout << "\n 1- Afișează primul rezultat al fisierului si scrie in fisiser";
        cout << "\n 2- Afiseaza din consola si scrie in consola";
        cout << "\n 3- Afiseaza din fisier si scrie in consola";
        cout << "\n 4- Scrie si afiseaza in fisier";
        cout << "\n 5- Iesire";
        cout << "\n\n Alege o optiune: ";
        cin >> choice;
    }
};
class Rezultat:public Operanzi, public InserareOperatii, public Schimbare {
public:
    string ch;
    void citirefisier(ifstream& myfile)
    {
        char Reply;
        int idx = 0;
        while (!myfile.eof()) {

            string Postfix, Infix;

            cout << "\n    Scrie expresia fara spatii\n\n";
            myfile >> Infix;

            if (Check_valid(Infix) == true)
            {

                string temp;
                temp = Change_me(Infix);

                Convert(temp, Postfix);

                string hold;
                hold = Insert_comma(Postfix);

                cout << "\n\nRaspunsul este: ";
                Next(hold);
            }
            else
            {
                cout << "***Eroare de sintaxa***\n";
            }
        }
        myfile.close();

    }
    void citiresiafisareconsola()
    {
        char Reply;
        int idx = 0;
        do
        {
            string Postfix, Infix;

            cout << "\n    Scrie expresia fara spatii\n\n";
            cin >> Infix;

            if (Check_valid(Infix) == true)
            {

                string temp;
                temp = Change_me(Infix);

                Convert(temp, Postfix);

                string hold;
                hold = Insert_comma(Postfix);

                cout << "\n\nRaspunsul este: ";
                Next(hold);

                cout << endl << "\nVrei alta? (y/n) ";
                cin >> Reply;
                idx++;
            }
            else
            {
                cout << "***Eroare de sintaxa***\n";
                cout << endl << "Vrei alta? (y/n) ";
                cin >> Reply;
                idx++;
            }

        } while (tolower(Reply) == 'y');
    }
    void afisarefisier(ofstream& yourfile)
    {
        int idx = 0;
        while (!yourfile.eof()) {

            string Postfix, Infix; 

            cout << "\n    Scrie expresia fara spatii\n\n";
            cin >> Infix;

            if (Check_valid(Infix) == true)
            {

                string temp;
                temp = Change_me(Infix);

                Convert(temp, Postfix);


                string hold;
                hold = Insert_comma(Postfix);

                yourfile << "\n\nRaspunsul este: ";
                Next(hold);
                idx++;
            }
            else
            {
                yourfile << "***Eroare de sintaxa***\n";
                idx++;
            }
        }
    }
    void citiresiafisarefisier(ifstream& myfile, ofstream& yourfile)

    {
        int idx = 0;
        while (!yourfile.eof() && !myfile.eof()) {

            string Postfix, Infix; 

            cout << "\n    Scrie expresia fara spatii\n\n";
            myfile >> Infix;

            if (Check_valid(Infix) == true)
            {

                string temp;
                temp = Change_me(Infix);

                Convert(temp, Postfix);

                string hold;
                hold = Insert_comma(Postfix);

                Next(hold);
                idx++;
            }
            else
            {
                yourfile << "***Eroare de sintaxa***\n";
                idx++;
            }
        }
        myfile.close();
    }

    bool IsOperand(char ch)
{
    if (((ch >= 'a') && (ch <= 'z')) ||
        ((ch >= 'A') && (ch <= 'Z')) ||
        ((ch >= '0') && (ch <= '9')))
        return true;
    else
        return false;
}
      bool TakesPrecedence(char OperatorA, char OperatorB)
      {
          if (OperatorA == '(')
              return false;
          else if (OperatorB == '(')
              return false;
          else if (OperatorB == ')')
              return true;
          if (OperatorA == '[')
              return false;
          else if (OperatorB == '[')
              return false;
          else if (OperatorB == ']')
              return true;
          else if ((OperatorA == '^') && (OperatorB == '^'))
              return false;
          else if (OperatorA == '^')
              return true;
          else if (OperatorB == '^')
              return false;
          else if ((OperatorA == '#') && (OperatorB == '#'))
              return false;
          else if (OperatorA == '#')
              return true;
          else if (OperatorB == '#')
              return false;
          else if ((OperatorA == '*') || (OperatorA == '/'))
              return true;
          else if ((OperatorB == '*') || (OperatorB == '/'))
              return false;
          else
              return true;

      }
      void Convert(const string& Infix, string& Postfix)
      {
          stack<char> OperatorStack;
          char TopSymbol, Symbol;
          long int k;

          for (k = 0; k < Infix.size(); k++)
          {
              Symbol = Infix[k];
              if (IsOperand(Symbol))
                  Postfix = Postfix + Symbol;
              else
              {
                  while ((!OperatorStack.empty()) &&
                      (TakesPrecedence(OperatorStack.top(), Symbol)))
                  {
                      TopSymbol = OperatorStack.top();
                      OperatorStack.pop();
                      Postfix = Postfix + TopSymbol;
                  }
                  if ((!OperatorStack.empty()) && ((Symbol == ')') || (Symbol == ']')))
                      OperatorStack.pop(); 
                  else
                      OperatorStack.push(Symbol);
              }
          }

          while (!OperatorStack.empty())
          {
              TopSymbol = OperatorStack.top();
              OperatorStack.pop();
              Postfix = Postfix + TopSymbol;
          }
      }
      string Change_me(string my_string)
      {

          for (int i = 0; i < my_string.length(); i++)
          {
              if (isdigit(my_string[i]) != 0)
              {
                  if (isdigit(my_string[i + 1]) == 0)
                  {
                      my_string.insert(i + 1, "v");
                  }
              }
          }
          for (int i = 0; i < my_string.length(); i++)
          {
              if (my_string[i] == '-')
              {
                  if (my_string[i - 1] != 'v' && (my_string[i - 1] != ')'))
                  {
                      my_string.replace(i, 1, "y");
                  }
              }
          }

          return my_string;
      }
      string Insert_comma(string my_string)
      {
          for (int i = 0; i < my_string.length(); i++)
          {
              if ((my_string[i] == '#') ||
                  (my_string[i] == '^') ||
                  (my_string[i] == '*') ||
                  (my_string[i] == '-') ||
                  (my_string[i] == '/') ||
                  (my_string[i] == '+'))
              {
                  my_string.insert(i + 1, ",");
              }
              else if (my_string[i] == 'v')
              {
                  my_string.replace(i, 1, ",");
              }
          }
          for (int i = 0; i < my_string.length(); i++)
          {
              if (my_string[i] == 'y')
              {
                  my_string.replace(i, 1, "-");
              }
          }
          return my_string;
      }
      bool Check_valid(string my_string)
      {
          for (int i = 0; i < my_string.length(); i++)
          {
              if ((my_string[i] == '+') || (my_string[i] == '-') || (my_string[i] == '.'))
              {
                  if ((my_string[i + 1] == '+') || (my_string[i + 1] == '-') || (my_string[i + 1] == '.'))
                  {
                      return false;
                  }
              }
          }


          string array = "0123456789+-*/()[].^#";

          int count = 0;
          for (int i = 0; i < my_string.length(); i++)
          {
              for (int j = 0; j < array.length(); j++)
              {
                  if (my_string[i] == array[j])
                  {
                      count++;
                  }
              }
          }

          if (count == my_string.length())
          {
              return true;
          }
          else
          {
              return false;
          }

      }
       void Next(string my_string)
      {
          vector <string> array;
          string tempy;

          long int comma_count = 0;
          for (int a = 0; a < my_string.length();a++)
          {
              if (my_string[a] == ',')
              {
                  comma_count++;
              }
          }
          while (my_string.find(",", 0) != string::npos)
          {
              size_t pos = my_string.find(",", 0);
              tempy = my_string.substr(0, pos);
              my_string.erase(0, pos + 1);
              array.push_back(tempy);         
          } 

          stack <string> my_stack;
          string temp[100];
          string ch;

          for (int i = 0; i < comma_count; i++)
          {

              string s;
              s = array[i]; 

              if ((s != "+") &&
                  (s != "*") &&
                  (s != "-") &&
                  (s != "/") &&
                  (s != "^") &&
                  (s != "#"))
              {
                  my_stack.push(s);
              }
              else 
              {
                  my_stack.push(s);
                  temp[0] = my_stack.top();
                  my_stack.pop();

                  temp[1] = my_stack.top();
                  my_stack.pop();

                  temp[2] = my_stack.top();
                  my_stack.pop();


                  long long int z;
                  z = Eval(temp);
                  ostringstream outs;
                  outs << z; 
                  ch = outs.str();

                  my_stack.push(ch);

              }
          }
          cout << ch;
          cin.get();
      }
      int Eval(string temp[])
      {
          string a, b, c;
          a = temp[2]; b = temp[0]; c = temp[1];
          long long int x, y, z;
          istringstream ins, inse;
          ins.str(a);inse.str(c);
          ins >> x;
          inse >> y;

          if (b == "+")
          {
              z = x + y;
              return z;
          }
          else if (b == "-")
          {
              z = x - y;
              return z;
          }
          else if (b == "*")
          {
              z = x * y;
              return z;
          }
          else if (b == "/")
          {
              z = x / y;
              return z;
          }
          else if (b == "^")
          {
              z = pow(x, y);
              return z;
          }
          else if (b == "#")
          {
              z = pow(x, 1 / y);
              return z;
          }
      }
};
void scrieInFisierBinar(string numeFisier, Rezultat j)
{
    ofstream f(numeFisier, ios::out | ios::binary);
    int length = j.ch.length();
    f.write((char*)&length, sizeof(length));
    f.write(j.ch.c_str(), length + 1);
    f.close();
}
int main(int argc, char* argv[])
{
    string filename = "sample.txt";
    int choice;
    ifstream InGradeList;
    InGradeList.open(filename);
    if (InGradeList.fail())
    {
        cerr << filename << "File failed to open" << endl;
        cin.ignore();
        exit(1);
    }
    string filename2 = "test.txt";
    ofstream LittleList;
    LittleList.open(filename2);
    if (LittleList.fail())
    {
        cerr << filename2 << "File failed to open" << endl;
        cin.ignore();
        exit(1);
    }
    Rezultat t;
    Afisare e;
    e.Menu(choice);
    switch (choice)
    {
    case 1: t.citirefisier(InGradeList);
        break;
    case 2: t.citiresiafisareconsola();
        break;
    case 3: t.afisarefisier(LittleList);
        break;
    case 4: t.citiresiafisarefisier(InGradeList, LittleList);
        break;
    default:
        cout << "Invalid input" << endl << endl;
    }
    Rezultat j;
    scrieInFisierBinar("student.bin", j);
}