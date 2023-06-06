// ==============================================================
// Assignment No : 4
// Name : Sarthak Nirgude
// Roll No. : 21156
// Batch : G1
// ==============================================================


// Problem Statement : 
// Consider telephone book database of N clients. Make use of a hash table 
// implementation to quickly look up client‘s telephone number. Make use of
// two collision handling techniques and compare them using number of comparisons
// required to find a set of telephone numbers (Note: Use linear probing with 
// replacement and without replacement)


#include <iostream>
using namespace std;

class client
{
public:
    int id;
    long long tele;
    string name;
    bool flag; // true if default data is present i.e. bucket is empty
    client()
    {
        id = -1;
        tele = -1;
        name = "";
        flag = true;
    }
    client(int i, long long t, string n)
    {
        id = i;
        tele = t;
        name = n;
        flag = false;
    }
    friend class HashTable;
};

class HashTable
{
public:
    client *ht;
    int size;
    int comparsion;
    HashTable(int sz)
    {
        this->size = sz;
        ht = new client[size];
        comparsion = 0;
    }

    void insert(int i, long long t, string n)
    {  //inserting without replacement
        client newClient(i, t, n);
        int it = (newClient.tele) % (this->size);
        if (ht[it].flag == true)
        {
            ht[it] = newClient;
        }
        else
        {
            int preit = it;
            it = (it + 1) % (this->size);
            while (ht[it].flag == false && preit != it)
            {
                it = (it + 1) % (this->size);
            }
            if (preit == it)
            { //if no empty space is found i.e. hash table is overflow
                cout << "Space is full\n";
            }
            else
            {
                ht[it] = newClient;
            }
        }
    }
    void insert_with_replace(int i, long long t, string n)
    { //inserting with replacement
        client newClient(i, t, n);

        int hashindex = (newClient.tele) % (this->size); //calculating the location of the ele.
        int hashcopy = hashindex; 
        do
        {
            if (ht[hashindex].flag == true)
            {
                ht[hashindex] = newClient;

                break;
            }
            else
            {
                int hashindexCollision = (ht[hashindex].tele) % (this->size); //checking for the ele. which already present in the hshtable
                if (hashindex != hashindexCollision && hashcopy == hashindex) //if given ele. in the hashtable is not present at it's appropriate position
                {
                    long long teleofCollision = ht[hashindex].tele;
                    int idofCollision = ht[hashindex].id;
                    string nameofCollision = ht[hashindex].name;
                    ht[hashindex] = newClient;

                    insert_with_replace(idofCollision, teleofCollision, nameofCollision); //sending the ele. which not in there proper position to insert it in the right place in the hshtable
                    break;
                }
                else
                {
                    hashindex = (hashindex + 1) % (this->size); //if ele. which is present in the hashtable having the proper position then find the next empty space for new ele. 
                }
            }
        } while (hashcopy != hashindex);
    }
    void search(long long t)
    {
        comparsion = 0;
        int it = (t) % (this->size);
        if (ht[it].tele == t)
        {
            comparsion++;
            cout << "==================================\n";
            cout << "telephone no. is  found \n";
            cout << "\tDetails : \n";
            cout << "\tId : " << ht[it].id << endl;
            cout << "\tName : " << ht[it].name << endl;
            cout << "\ttelephone No. : " << ht[it].tele << endl;
            cout << "\tcomparsion : " << comparsion << endl;
            cout << "==================================\n";
            return;
        }
        else
        {
            int preit = it;
            it = (it + 1) % (this->size);
            while (ht[it].tele != t && preit != it)
            {
                comparsion++;
                it = (it + 1) % (this->size);
            }
            if (preit != it)
            {
                comparsion++;
                cout << "==================================\n";
                cout << "telephone no. is  found \n";
                cout << "\tDetails : \n";
                cout << "\tId : " << ht[it].id << endl;
                cout << "\tName : " << ht[it].name << endl;
                cout << "\ttelephone No. : " << ht[it].tele << endl;
                cout << "\tcomparsion : " << comparsion << endl;
                cout << "==================================\n";

                return;
            }
            else
            {
                cout << "telephone no. is not found\n";
                comparsion++;
                return;
            }
        }
    }
    void del(long long t)
    {
        int it = (t) % (this->size);
        if (ht[it].tele == t)
        {
            ht[it].tele = -1;
            ht[it].flag = true;
            ht[it].id = -1;
            ht[it].name = "";
            cout << "\n\tSuccessfully deleted\n";
            return;
        }
        else
        {
            int preit = it;
            it = (it + 1) % (this->size);
            while (ht[it].tele != t && preit != it)
            {
                it = (it + 1) % (this->size);
            }
            if (preit == it)
            {
                cout << "telephone no. is not found\n";
                return;
            }
            else
            {
                ht[it].tele = -1;
                ht[it].flag = true;
                ht[it].id = -1;
                ht[it].name = "";
                cout << "\n\tSuccessfully deleted\n";
                return;
            }
        }
    }

    void display()
    {
        cout << "================================================" << endl;
        cout << "id\tName\t\t\tTele \n";
        for (int i = 0; i < this->size; i++)
        {
            if (!ht[i].flag)
            {

                cout << ht[i].id << "\t" << ht[i].name << "\t\t\t" << ht[i].tele << " \n";
            }
        }
        cout << "================================================" << endl;
    }
};

int main()
{
    HashTable h(10);
    HashTable h1(10);
    while (1)
    {
        cout << "\n1.Insert\n2.Display\n3.Search\n4.delete\n5.Exit\n";
        cout << "Enter your choice: ";
        int c;
        cin >> c;
        cout << endl;
        if (c == 1)
        {
            string name;
            int id;
            long long t;
            cout << "Enter Name : " << endl;
            cin >> name;
            cout << "Enter id : " << endl;
            cin >> id;
            cout << "Enter telephone Number : " << endl;
            cin >> t;
            h.insert(id, t, name);
            h1.insert_with_replace(id, t, name);
        }
        else if (c == 2)
        {
            cout << "Without Replacement : \n";
            h.display();
            cout << "With Replacement : " << endl;
            h1.display();
        }
        else if (c == 3)
        {
            cout << "Enter the telephone no. : " << endl;
            long long t;
            cin >> t;
            cout << "For without Replacement : " << endl;
            h.search(t);
            cout << "For with Replacement : " << endl;
            h1.search(t);
        }
        else if (c == 4)
        {
            long long t;
            cout << "Enter the telephone no. : " << endl;
            cin >> t;
            h.del(t);
            h1.del(t);
        }
        else if (c == 5)
        {
            cout << "Thank you!!\n";
            break;
        }
    }

    return 0;
}