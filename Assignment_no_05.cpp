// ==============================================================
// Assignment No : 5
// Name : Sarthak Nirgude
// Roll No. : 21156
// Batch : G1
// ==============================================================


// Problem Statement :
// Implement all the functions of a dictionary (ADT) using hashing and handle
// collisions using chaining with / without replacement.
// Data: Set of (key, value) pairs, Keys are mapped to values, Keys must be
// comparable, Keys must be unique. Standard Operations: Insert(key, value),
// Find(key), Delete(key)


#include <bits/stdc++.h>
using namespace std;


class Node
{
public:
   string key;
   string value;
   Node *next;
   Node() : key(" "), value(" "), next(NULL) {}
   Node(string key, string value)
   {
       this->key = key;
       this->value = value;
       this->next = NULL;
   }
   friend class Links;
   friend class HashTable;
};


class Links
{
   Node *head;
   Node *tail;
   friend class HashTable;
public:
   // void insert();
   // void display();
   // bool find();
   // void del();
   Links() : head(NULL), tail(NULL) {}
   void insertInLink(string key, string value)
   {
       Node *newNode = new Node(key, value);
       if (head == NULL)
       {
           head = newNode;
           tail = newNode;
       }
       else
       {
           tail->next = newNode;
           tail = tail->next;
       }
   }
   void display(Node *temp)
   {
       if (temp == NULL)
       {
           cout << " - ";
       }
       else
       {
           while (temp != NULL)
           {
               cout << temp->key << " : " << temp->value << " ->";
               temp = temp->next;
           }
       }
   }
   bool Search(string key, Node *head, Node *tail)
   {
       Node *temp = head;
       if (tail->key == key)
       {
           return true;
       }
       while (temp->key != key && temp != tail)
       {
           temp = temp->next;
       }
       if (temp == tail)
       {
           return false;
       }
       else
       {
           return true;
       }
   }
   void del(string key)
   {
       Node *ptr = head;
       if (ptr->key == key)
       {
           if (head == tail)
           {
               head = tail = nullptr;
               delete ptr;
               return;
           }
           head = head->next;
           delete ptr;
           return;
       }
       Node *follow = ptr;
       while (ptr->key != key || ptr == nullptr)
       {
           follow = ptr;
           ptr = ptr->next;
       }
       follow->next = ptr->next;
       if (ptr == tail)
       {
           tail = follow;
       }
       delete ptr;
       return;
   }


   bool isempty(Node *any)
   {
       return (any == NULL) ? (true) : (false);
   }
};


class HashTable
{
   Links *hash;
   int size;
public:
   HashTable(int s)
   {
       this->size = s;
       hash = new Links[size];
       for (int i = 0; i < size; i++)
       {
           hash[i].head = NULL;
           hash[i].tail = NULL;
       }
   }
   int Hashfunc(string key)
   {
       int t = 0;
       for (auto i : key)
       {
           t += int(i);
       }
       return (t) % (this->size);
   }


   void insert(string key, string value)
   {
       int index = Hashfunc(key);
       // bool isPresent = hash[index].Search(key, hash[index].head, hash[index].tail);
       // if (isPresent)
       // {
       //     cout << "Duplicate word is not allowed !" << endl;
       //     return;
       // }
       if (hash[index].head == NULL || hash[index].tail == NULL)
       {
           hash[index].insertInLink(key, value);
       }
       else
       {


           hash[index].insertInLink(key, value);
       }
   }


   void display()
   {
       cout << "\n\t====== | Dictionary | =======\t\n";
       for (int i = 0; i < size; i++)
       {
           if (i == 9)
           {
               cout << "Index : " << i + 1 << "|| ";
           }
           else
           {
               cout << "Index : " << i + 1 << " || ";
           }


           hash[i].display(hash[i].head);
           cout << endl;
       }
       cout << endl;
   }
   void find(string key)
   {


       int index = Hashfunc(key);
       bool isPresent = hash[index].Search(key, hash[index].head, hash[index].tail);
       if (isPresent)
       {
           cout << "Key is found in the Dictionary at " << index + 1 << endl;
       }
       else
       {
           cout << "Key is not found ! " << endl;
       }
   }
   void deleteInHashTable(string key)
   {
       int index = Hashfunc(key);
       bool isPresent = hash[index].Search(key, hash[index].head, hash[index].tail);
       if (!isPresent)
       {
           cout << "key is not Present in the HashTable\n";
           return;
       }
       hash[index].del(key);
   }
};


int main()
{


   HashTable h(10);
   h.insert("abc", "cd");
   h.insert("get", "yes");
   h.insert("cda", "no");
   h.insert("get", "yes");
   h.insert("apt", "no");
   h.insert("set", "get");
   h.insert("NO", "yes");
   h.insert("no", "yes");
   // h.insert("NO", "YES");
   // h.display();
   // h.find("abc");
   // h.find("unknown");
   while (1)
   {
       cout << "_____________: Menu Bar :_____________\n";
       cout << "1.Insert in Dictionary\n";
       cout << "2.Display\n";
       cout << "3.Find the word in Dictionary\n";
       cout << "4:Delete the word from the Dictionary\n";
       cout << "5:Exit\n";
       cout << "__________________________________________\n";
       cout << "Enter your choice : ";
       int c;
       cin >> c;
       cout << endl;
       if (c == 1)
       {
           cin.ignore(1);
           cin.clear();
           string word, meaning;
           cout << "Enter the word  : ";
           // cin >> word;
           getline(cin, word);
           cout << endl;
           cout << "Enter the meaning : ";
           // cin >> meaning;
           getline(cin, meaning);
           cout << endl;
           h.insert(word, meaning);
       }
       else if (c == 2)
       {
           h.display();
       }
       else if (c == 3)
       {
           cin.ignore(1);
           cin.clear();
           string word;
           cout << "Enter the word : ";
           // cin >> word;
           getline(cin, word);
           cout << endl;
           h.find(word);
       }
       else if (c == 4)
       {
           string word;
           cin.ignore(1);
           cin.clear();
           cout << "Enter the word : ";
           getline(cin, word);
           cout << endl;
           h.deleteInHashTable(word);
       }
       else if (c == 5)
       {
           cout << "\tThank You..!!\n";
           break;
       }
   }
   return 0;
}


