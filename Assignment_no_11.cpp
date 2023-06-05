// ==============================================================
// Assignment No : 11
// Name : Sarthak Nirgude
// Roll No. : 21156
// Batch : G1
// ==============================================================


#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

class Student
{
    char name[20];
    int roll;
    friend class Database;

public:
    void input()
    {
        cout << "Enter the Name : " << endl;
        cin >> name;
        cout << "Enter Roll NO. :  " << endl;
        cin >> roll;
    }
    void show()
    {
        cout << "\t" << name << "\t" << roll << endl;
    }
    void modification()
    {
        cout << "Enter the new Name : " << endl;
        cin >> name;
    }
};
class Database
{
    char fname[20];

public:
    Database(char f[])
    {
        strcpy(fname, f);
    }
    void add(int n)
    {
        ofstream fout;
        fout.open(fname, ios::app);
        Student s;
        for (int i = 0; i < n; i++)
        {
            s.input();
            fout.write((char *)&s, sizeof(s));
        }
        fout.close();
    }
    void display()
    {
        ifstream fin;
        fin.open(fname, ios::in);
        Student s;
        while (fin.read((char *)&s, sizeof(s)))
        {
            s.show();
            cout << endl;
        }
        fin.close();
    }
    void del(int rn)
    {

        int flag = 0;
        ifstream file1;
        ofstream file2;
        file1.open(fname, ios::in);
        file2.open("temp.txt", ios::out);

        Student s;
        while (file1.read((char *)&s, sizeof(s)))
        {
            if (s.roll != rn)
            {
                file2.write((char *)&s, sizeof(s));
            }
            else if (s.roll == rn)
            {
                flag = 1;
            }
        }

        if (flag == 0)
        {
            cout << "Record is not present in the data base " << endl;
        }
        file1.close();
        file2.close();
        remove(fname);
        rename("temp.txt", fname);
    }
    void update(int rn)
    {
        int flag = 0;
        ifstream file1;
        ofstream file2;
        file1.open(fname, ios::in);
        file2.open("temp.txt", ios::out);

        Student s;
        while (file1.read((char *)&s, sizeof(s)))
        {
            if (s.roll == rn)
            {
                s.modification();
                flag = 1;
            }
            file2.write((char *)&s, sizeof(s));
        }

        if (flag == 0)
        {
            cout << "Record is not present in the data base " << endl;
        }
        file1.close();
        file2.close();
        remove(fname);
        rename("temp.txt", fname);
    }
    void Search(int rn)
    {
        int flag = 0;
        ifstream file;
        file.open(fname, ios::in);
        Student s;

        while (file.read((char *)&s, sizeof(s)))
        {
            if (s.roll == rn)
            {
                flag = 1;
                break;
            }
        }
        if (flag)
        {
            cout << "Record is Found " << endl;
            s.show();
        }
        else
        {
            cout << "Record is not Found " << endl;
        }
    }
};
int main()
{
    char name[20];
    cout << "Enter the fiel name : ";
    cin >> name;
    cout << "\n";
    Database d(name);
    int n;
    while (1)
    {
        cout << "1.Add record " << endl;
        cout << "2.Display record" << endl;
        cout << "3.Search record" << endl;
        cout << "4.Delete record" << endl;
        cout << "5.Update record" << endl;
        cout << "6.Exit" << endl;
        int c;
        cout << "Enter your choice : " << endl;
        cin >> c;
        if (c == 1)
        {
            cout << "Enter the total no. of students  " << endl;
            cin >> n;
            d.add(n);
        }
        else if (c == 2)
        {
            d.display();
        }
        else if (c == 3)
        {
            cout << "Enter the Roll No. " << endl;
            cin >> n;
            d.Search(n);
        }
        else if (c == 4)
        {
            cout << "Enter the Roll No " << endl;
            cin >> n;
            d.del(n);
        }
        else if (c == 5)
        {
            cout << "Enter the Roll No " << endl;
            cin >> n;
            d.update(n);
        }
        else
        {
            cout << "Thank you !" << endl;
            break;
        }
    }
    return 0;
}