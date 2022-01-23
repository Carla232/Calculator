#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <iomanip>
using namespace std;
char a[100];
char fz[100];
long long int sz[100];
long long int shead = 0;
long long int fhead = 0;

class Expresie
{
private:
    char* a1;
    char* fz1;
    float* sz1;
    int shead1;
    int fhead1;
public:
    Expresie()
    {
        a1 = nullptr;
        fz1 = nullptr;
        sz1 = nullptr;
        shead1 = 0;
        fhead1 = 0;
    }
    Expresie(char* a1, char* fz1, float* sz1, int shead1, int fhead1)
    {
        this->fhead1 = fhead1;
        this->a1 = new char[strlen(a1) + 1];
        strcpy_s(this->a1, strlen(a1) + 1, a1);
        this->fz1 = new char[strlen(fz1) + 1];
        strcpy_s(this->fz1, strlen(fz1) + 1, fz1);
        //producator = this->producator;
        if (this->sz1 != nullptr && this->shead1 > 0)
        {
            this->shead1 = shead1;
            sz1 = new float[this->shead1];
            for (int i = 0; i < shead1; i++)
            {
                sz1[i] = this->sz1[i];
            }
        }
        else
        {
            sz1 = nullptr;
            shead1 = 0;
        }
    }
    Expresie& operator=(const Expresie& t)
    {
        if (this != &t)
        {
            if (sz1 != nullptr)
            {
                delete[] sz1;
            }
            if (a1 != nullptr)
            {
                delete[] a1;
            }
            if (fz1 != nullptr)
            {
                delete[] fz1;
            }
            fhead1 = t.fhead1;
            if (t.a1 != nullptr)
            {
                this->a1 = new char[strlen(t.a1) + 1];
                strcpy_s(this->a1, strlen(t.a1) + 1, t.a1);
            }
            if (t.fz1 != nullptr)
            {
                this->fz1 = new char[strlen(t.fz1) + 1];
                strcpy_s(this->fz1, strlen(t.fz1) + 1, t.fz1);
            }
            if (t.sz1 != nullptr && t.shead1 > 0)
            {
                shead1 = t.shead1;
                sz1 = new float[shead1];
                for (int i = 0; i < shead1; i++)
                {
                    sz1[i] = t.sz1[i];
                }
            }
            else
            {
                sz1 = nullptr;
                shead1 = 0;
            }
        }
        return *this;
    }
    char* getA()
    {
        return this->a1;
    }
    char* getfz1()
    {
        return this->fz1;
    }
    float* getsz1()
    {
        return this->sz1;
    }
    int getshead1()
    {
        this->shead1;
    }
    int getfhead1()
    {
        this->fhead1;
    }
    void setA()
    {
        this->a1 = new char[strlen(a1) + 1];
        strcpy_s(this->a1, strlen(a1) + 1, a1);
    }
    void setsz1(float* sz1, int shead1)
    {
        this->shead1 = shead1;
        if (sz1 != nullptr)
        {
            delete[] sz1;
        }
        this->sz1 = new float[shead1];
        for (int i = 0; i < shead1; i++)
        {
            this->sz1[i] = sz1[i];
        }
    }
    void setfz1()
    {
        this->fz1 = new char[strlen(fz1) + 1];
        strcpy_s(this->fz1, strlen(fz1) + 1, fz1);
    }
    void setfhead1()
    {
        this->fhead1 = fhead1;
    }
    void myFunction() {
        cout << "I just got executed!";
    }


    void mathi(char f) 
    {
        switch (f)
        {
        case '+': sz[--shead] += sz[shead + 1]; break;
        case '-': sz[--shead] -= sz[shead + 1]; break;
        case '*': sz[--shead] *= sz[shead + 1]; break;
        case '/':
            sz[--shead] /= sz[shead + 1];
            break;
        case '^':
            sz[--shead] = pow(sz[shead], sz[shead + 1]);
            break;
        case '#':  sz[--shead] = pow(sz[shead], 1 / sz[shead + 1]); break;
        }
        --fhead;
        sz[shead + 1] = 0;
    }

    void expresie()
    {
        cin.getline(a, sizeof a);
        int len = strlen(a) - 1;
        for (int i = 0; i <= len; ++i)
        {
            if (a[i] == '[') {
                fz[++fhead] = a[i];
                continue;
            }
            if (a[i] == '(') {
                fz[++fhead] = a[i];
                continue;
            }
            if (a[i] == ')') {
                while (fz[fhead] != '(')
                    mathi(fz[fhead]);
                --fhead;
                continue;
            }
            if (a[i] == ']') {
                while (fz[fhead] != '[')
                    mathi(fz[fhead]);
                --fhead;
                continue;
            }
            if (a[i] >= '0' && a[i] <= '9') {
                ++shead;
                while (a[i] >= '0' && a[i] <= '9')
                    sz[shead] = sz[shead] * 10 + a[i] - '0', i++;
                i--;
                continue;
            }
            else {
                if (a[i] == '/' || a[i] == '*') {
                    fz[++fhead] = a[i];
                    continue;
                }
                else
                    while (fz[fhead] == '*' || fz[fhead] == '/' || fz[fhead] == a[i]) {
                        mathi(fz[fhead]);
                    }
                fz[++fhead] = a[i];
            }
        }
        while (fhead != 0) {
            mathi(fz[fhead]);
        }
        cout << sz[shead];
    }
};
class Ecuatie {
private:
    long double x, y, result;
    char choice, a;
public:
    void add(long double i, long double a);
    void subtract(long double i, long double a);
    void mult(long double i, long double a);
    void divide(long double i, long double a);
    void pw(long double i, long double a);
    void rad(long double i, long double a);
    void driver();
    void driver2();
    Ecuatie()
    {
        x = 0;
        y = 0;
        result = 0;
    };
    Ecuatie(long double x, long double y, long double result, char choice, char a)
    {
        this->x = x;
        this->y = y;
        this->result = result;
        this->a = a;
        this->choice = choice;
    }
    long double getx()
    {
        return this->x;
    }
    long double gety()
    {
        return this->y;
    }
    long double getresult()
    {
        return this->result;
    }
    char getchoice()
    {
        return this->choice;
    }
    char geta()
    {
        return this->a;
    }
    void setx()
    {
        this->x = x;
    }
    void sety()
    {
        this->y = y;
    }
    void setresult()
    {
        this->result = result;
    }
    void setchoice()
    {
        this->choice = choice;
    }
    void seta()
    {
        this->a = a;
    }
    Ecuatie operator++(int i)
    {
        Ecuatie copie = *this;
        this->x++;
        return copie;
    }
    explicit operator int()
    {
        return y;
    }
    friend ostream& operator<<(ostream&, Ecuatie);
    friend istream& operator>>(istream&, Ecuatie&);
};
ostream& operator<<(ostream& out, Ecuatie s)
{
    out << "numar 1: " << s.x << endl;
    out << "numar 2: " << s.y << endl;
    out << "resultat: " << s.result << endl;
    out << "alegere: " << s.choice << endl;
    out << "operator" << s.a << endl;
    return out;
}
istream& operator>>(istream& in, Ecuatie& s)
{
    cout << "numar 1 = ";
    in >> s.x;
    cout << "numar 2 = ";
    in >> s.y;
    cout << "resultat = ";
    in >> s.result;
    cout << "alegere = ";
    in >> s.choice;
    cout << "operator = ";
    in >> s.a;
    return in;
}
void Ecuatie::add(long double i, long double a) {
    result = i + a;
    cout << "Result:" << fixed << setprecision(4) << result << endl;
}

void Ecuatie::subtract(long double i, long double a) {
    result = i - a;
    cout << "Result:" << fixed << setprecision(4) << result << endl;
}

void Ecuatie::mult(long double i, long double a) {
    result = i * a;
    cout << "Result:" << fixed << result << setprecision(4) << endl;
}

void Ecuatie::divide(long double i, long double a) {
    if (a == 0)
        cout << "Nu se poate" << endl;
    else {
        result = i / a;
        cout << "Result:" << fixed << setprecision(4) << result << endl;
    }
}
void Ecuatie::pw(long double i, long double a) {
    result = pow(i, a);
    cout << "Result:" << fixed << setprecision(4) << result << endl;
}
void Ecuatie::rad(long double i, long double a) {
    result = pow(i, 1 / a);
    cout << "Result:" << fixed << setprecision(4) << result << endl;
}
void Ecuatie::driver() {
    cin >> x >> a >> y;
    switch (a) {
    case '+':add(x, y); break;
    case '-': subtract(x, y); break;
    case '*': mult(x, y); break;
    case '/': divide(x, y); break;
    case '^': pw(x, y); break;
    case '#': rad(x, y); break;
    default: cout << "Nu este valid! Mai incearca" << endl;
    }

}

void Ecuatie::driver2() {
    do {
        driver();

        cout << "Do you want to continue? Y/N" << endl;
        cin >> choice;
    } while (choice == 'Y' || choice == 'y');

};
class Eroare_si_Afisare
{
private:
    const int phi;
    static string Afisare;
    double h;
    double u;
    char o;
public:
    Eroare_si_Afisare() :phi(3)
    {
        h = 0;
        u = 0;
    }
    Eroare_si_Afisare(int h, int u, char o) : phi(phi)
    {
        this->h = h;
        this->u = u;
    }
    double geth()
    {
        return this->h;
    }
    double getu()
    {
        return this->u;
    }
    void seth()
    {
        this->h = h;
    }
    static string getAfisare()
    {
        return Afisare;
    }
    Eroare_si_Afisare operator+(int valoare)
    {
        Eroare_si_Afisare copie = *this;
        copie.u += valoare;
        return copie;
    }
    bool operator!()
    {
        return h > 0 && u >0;
    }
    static void setAfisare(string Afisare)
    {
        Eroare_si_Afisare::Afisare = Afisare;
    }
    void eroare1()
    {
        cin >> h >> o >> u;
        if (o == '/')
            if (u == 0)
                cout << "Eroare";
            else if (o != '+' || o != '-' || o != '*' || o != '^' || o != '#')
                cout << "Eroare";
    }
    friend ostream& operator<<(ostream&, Eroare_si_Afisare);
    friend istream& operator>>(istream&, Eroare_si_Afisare&);
};
string Eroare_si_Afisare::Afisare = "Afiseaza ecuatia: ";
ostream& operator<<(ostream& out, Eroare_si_Afisare e)
{
    out << "numar 1: " << e.h << endl;
    out << "operator: " << e.o << endl;
    out << "numar 2: " << e.u << endl;
    out << "valoare aprox phi: " << e.phi << endl;
    return out;
}
istream& operator>>(istream& in, Eroare_si_Afisare& e)
{
    cout << "numar 1 = ";
    in >> e.h;
    cout << "operator = ";
    in >> e.o;
    cout << "numar 2 = ";
    in >> e.u;
    return in;
}
int main()
{
    Eroare_si_Afisare e;
    Eroare_si_Afisare::setAfisare("Scrie ecuatia: ");
    cout << e.getAfisare() << endl;
    Expresie t;
    t.expresie();
    //aceasta clasa de mai jos este folosita pentru 2 numere, in special am folosit-o pentru numere de tip float(cu virgula)
    /*Ecuatie imba;
    imba.driver();
    imba.driver2();*/
    return 0;
}