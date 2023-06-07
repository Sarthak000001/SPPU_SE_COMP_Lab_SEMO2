#include <iostream>
#include <fstream>
#include <cstring>
#define SIZE 10

using namespace std;

class Student
{
public:
    int roll;
    int loc;

    Student(int r = 0, int l = 0)
    {
        roll = r;
        loc = l;
    }

    friend class Hash;
};

class Hash
{
    Student *arr;

public:
    Hash()
    {
        arr = new Student[SIZE];
        for (int i = 0; i < SIZE; i++)
        {
            arr[i].roll = -1; // Initialize roll as -1 to represent an empty slot
            arr[i].loc = -1;  // Initialize loc as -1 to represent an empty slot
        }
    }

    int hashFunction(int key)
    {
        return key % SIZE;
    }

    void show()
    {
        cout << "\nHashTable" << endl;
        for (int i = 0; i < SIZE; i++)
        {
            if (arr[i].roll != -1)
                cout << i << " - " << arr[i].roll << " : " << arr[i].loc << endl;
        }
        cout << endl;
    }

    void insert(int roll, int loc)
    {
        int hashIndex = hashFunction(roll);
        int hashCopy = hashIndex;
        do
        {
            if (arr[hashIndex].roll == -1) // If the slot is empty
            {
                arr[hashIndex].roll = roll;
                arr[hashIndex].loc = loc;
                break;
            }
            else
            {
                hashIndex = (hashIndex + 1) % SIZE; // Linear probing to find the next empty slot
            }
        } while (hashIndex != hashCopy);
    }

    int search(int rn)
    {
        int hashIndex = hashFunction(rn);
        int hashCopy = hashIndex;
        do
        {
            if (arr[hashIndex].roll == rn) // If the roll matches
            {
                return arr[hashIndex].loc;
            }
            else
            {
                hashIndex = (hashIndex + 1) % SIZE; // Linear probing to find the next slot
            }
        } while (hashIndex != hashCopy);
        return -1; // Roll not found
    }

    void remove(int rn)
    {
        int hashIndex = hashFunction(rn);
        int hashCopy = hashIndex;
        do
        {
            if (arr[hashIndex].roll == rn) // If the roll matches
            {
                arr[hashIndex].roll = -1; // Mark the slot as empty
                arr[hashIndex].loc = -1;
                break;
            }
            else
            {
                hashIndex = (hashIndex + 1) % SIZE; // Linear probing to find the next slot
            }
        } while (hashIndex != hashCopy);
    }
};

class File
{
    char fname[20];
    char buffer[100];
    Hash h;
    int roll;
    string name;

public:
    File(char f[])
    {
        strcpy(fname, f);
    }

    void write()
    {
        ofstream fout;
        fout.open(fname, ios::out);

        if (!fout)
            cout << "\nError in opening file" << endl;
        else
        {
            cout << "\nHow many records do you want to add? ";
            int count;
            cin >> count;
            for (int i = 0; i < count; i++)
            {
                cout << "___________________\n";
                cout << "\nEnter Roll: ";
                cin >> roll;
                cout << "Enter Name: ";
                cin >> name;
                h.insert(roll, fout.tellp());
                fout << roll << " : " << name << endl;
            }
        }
        fout.close();
    }

    void read()
    {
        ifstream fin;
        fin.open(fname, ios::in);

        if (!fin)
            cout << "\nError in opening file" << endl;
        else
        {
            int i = 0;
            cout << "--------------Database----------------------" << endl;
            while (!fin.eof())
            {
                fin.getline(buffer, 100);
                cout << "Record: " << i + 1 << " " << buffer << endl;
                i++;
            }
        }
        fin.close();
        h.show();
    }

    void search(int rn)
    {
        ifstream fin;
        fin.open(fname, ios::in);

        if (!fin)
            cout << "\nError in opening file" << endl;
        else
        {
            int loc = h.search(rn);
            if (loc == -1)
            {
                cout << "\nRecord not found " << endl;
                return;
            }
            fin.seekg(loc, ios::beg);
            fin.getline(buffer, 40);
            cout << "\nRecord found" << endl;
            cout << buffer << endl;
        }
        fin.close();
    }

    void removeF(int rn)
    {
        ifstream fin;
        fin.open(fname, ios::in);

        if (!fin)
            cout << "\nError in opening file" << endl;
        else
        {
            int loc = h.search(rn);
            if (loc == -1)
            {
                cout << "\nRecord not found " << endl;
                return;
            }
            fin.seekg(loc, ios::beg);
            fin.getline(buffer, 40);
            cout << "\nRecord to be deleted" << endl;
            cout << buffer << endl;
        }
        fin.close();

        ofstream fout;
        fin.open(fname, ios::in);
        fout.open("temp.txt", ios::out);
        Student s;
        if (!fin || !fout)
            cout << "\nError in opening file" << endl;
        else
        {
            while (!fin.eof())
            {
                fin.getline(buffer, 100);
                int r;
                sscanf(buffer, "%d", &r);
                if (r != rn)
                    fout << buffer << endl;
            }
        }
        fin.close();
        fout.close();

        remove(fname);
        rename("temp.txt", fname);
        h.remove(rn);
    }
};

int main()
{
    char str[20];
    cout << "Enter the file Name : ";
    cin >> str;
    cout << endl;
    File f(str);

    while (1)
    {
        cout << "\n------------------" << endl;
        cout << "1.Create record " << endl;
        cout << "2.Display record" << endl;
        cout << "3.Search record" << endl;
        cout << "4.Delete record" << endl;
        cout << "5.Exit" << endl;
        int c;
        cout << "Enter your choice : " << endl;
        cin >> c;
        if (c == 1)
        {
            f.write();
        }
        else if (c == 2)
        {
            f.read();
        }
        else if (c == 3)
        {
            cout << "Enter the roll : " << endl;
            int r;
            cin >> r;
            f.search(r);
        }
        else if (c == 4)
        {
            cout << "Enter the roll : " << endl;
            int r;
            cin >> r;
            f.removeF(r);
        }
        else
        {
            cout << "Thank you !" << endl;
            break;
        }
    }
    return 0;
}
