// ====================================================
//    Name : Sarthak Nirgude
//    Batch : G1
//    Roll No. : 21156
//    Assignment No. - 10
// ====================================================


// Problem Statement :
// Implement the Heap sort algorithm using heap data structure
// with modularity of programming language.


#include <iostream>
using namespace std;
const int MAX = 100;


class Heap
{
   int arr[MAX];
   int size;
   int n;

public:
   Heap()
   {
       arr[0] = -1;
       size = 0;
   }
   void create()
   {
       cout << "Enter the no. of elements  : ";
       cin >> this->n;
       for (int i = 0; i < n; i++)
       {
           cout << "Enter value : ";
           int val;
           cin >> val;
           insert(val);
       }
   }
   void insert(int val)
   {
       size = size + 1;
       int index = size;
       arr[index] = val;
       while (index > 1)
       {
           int parent = index / 2;
           if (arr[parent] < arr[index]) // for max-heap
           {
               swap(arr[parent], arr[index]);
               parent = index;
           }
           else
           {
               return;
           }
       }
   }
   void deleteInHeap()
   {


       arr[1] = arr[size];
       
       size--;

       int i = 1;
       while (i < size)
       {
           int left = 2 * i;
           int right = 2 * i + 1;
           if (left < size && arr[i] < arr[left])
           {
               swap(arr[i], arr[left]);
               i = left;
           }
           else if (right < size && arr[i] < arr[right])
           {
               swap(arr[i], arr[right]);
               i = right;
           }
           else
           {
               return;
           }
       }
   }
   void heapify(int arr[], int n, int i)
   {
       if (n == 0)
       {
           return;
       }
       int largest = i;
       int left = 2 * i;
       int right = 2 * i + 1;


       if (left <= n && arr[left] > arr[largest])
       {
           largest = left;
       }
       if (right <= n && arr[right] > arr[largest])
       {
           largest = right;
       }


       if (largest != i)
       {
           swap(arr[largest], arr[i]);
           heapify(arr, n, largest);
       }
   }


   void heapSort()
   {
       int size_ = this->size;


       while (size_ > 1)
       {
           swap(arr[1], arr[size_]);


           size_--;


           heapify(arr, size_, 1);
       }
   }


   void print()
   {
       cout << "Display : ";
       for (int i = 1; i < size + 1; i++)
       {
           cout << arr[i] << " ";
       }
       cout << endl;
   }
};


int main()
{
   Heap h;


   cout << endl;
   cout << "\tCreate Heap\n";
   h.create();
   // cout << "Before Heap Sort : ";
   // h.print();
   // cout << "After Heap Sort : ";
   // h.heapSort();
   // h.print();


   do
   {
       cout << "=========== : Heap : ===============\n";
       int c;
       cout << "1.Heap Sort \n2.Print\n3.Exit\n";
       cin >> c;
       if (c == 1)
       {
           h.heapSort();
       }
       else if (c == 2)
       {
           h.print();
       }
       else
       {
           break;
       }
   } while (1);
   return 0;
}



