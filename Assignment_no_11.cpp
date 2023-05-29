// ==============================================================
// Assignment No : 11
// Name : Sarthak Nirgude
// Roll No. : 21156
// Batch : G1
// ==============================================================

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

using namespace std;

class Student
{
    int rollNumber;
    string name;
    string division;
    string address;

    public:
        void addStudentRecord() 
    {
        ofstream file("student_data.txt", ios::app); // Open the file in append mode

        if (!file) {
            cout << "Error opening file!" << endl;
            return;
        }

        Student student;
        cout << "Enter Roll Number: ";
        cin >> student.rollNumber;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, student.name);
        cout << "Enter Division: ";
        getline(cin, student.division);
        cout << "Enter Address: ";
        getline(cin, student.address);

        // Write the student record to the file
        file << student.rollNumber << "," << student.name << "," << student.division << "," << student.address << endl;

        file.close();
        cout << "Student record added successfully!" << endl;
    }

    void deleteStudentRecord() 
    {
        ifstream inFile("student_data.txt"); // Open the file for reading
        ofstream outFile("temp.txt"); // Open a temporary file for writing

        if (!inFile) {
            cout << "Error opening file!" << endl;
            return;
        }

        int rollNumber;
        cout << "Enter the Roll Number of the student to delete: ";
        cin >> rollNumber;

        bool found = false;
        string line;

        // Read each line from the file
        while (getline(inFile, line)) 
        {
            // Split the line into fields
            size_t pos = line.find(',');
            int fileRollNumber = stoi(line.substr(0, pos));

            if (fileRollNumber == rollNumber) {
                found = true;
                continue; // Skip writing this line to the temporary file
            }

            outFile << line << endl;
        }

        inFile.close();
        outFile.close();

        if (found) 
        {
            remove("student_data.txt");              // Delete the original file
            rename("temp.txt", "student_data.txt");  // Rename the temporary file to the original file
            cout << "Student record deleted successfully!" << endl;
        } else {
            remove("temp.txt"); // Delete the temporary file
            cout << "Student record not found!" << endl;
        }
    }

// Function to display information of a particular student
        void displayStudentRecord() 
        {
            ifstream file("student_data.txt");

            if (!file) 
            {
                cout << "Error opening file!" << endl;
                return;
            }

            int rollNumber;
            cout << "Enter the Roll Number of the student to display: ";
            cin >> rollNumber;

            bool found = false;
            string line;

            // Read each line from the file
            while (getline(file, line)) 
            {
                // Split the line into fields
                size_t pos = line.find(',');
                int fileRollNumber = stoi(line.substr(0, pos));

                if (fileRollNumber == rollNumber) {
                    found = true;

                    // Extract the student details from the line
                    Student student;
                    student.rollNumber = fileRollNumber;
                    student.name = line.substr(pos + 1, line.find(',', pos + 1) - pos - 1);
                    pos = line.find(',', pos + 1);
                    student.division = line.substr(pos + 1, line.find(',', pos + 1) - pos - 1);
                    pos = line.find(',', pos + 1);
                    student.address = line.substr(pos + 1);

                    // Display the student details
                    cout << "Roll Number: " << student.rollNumber << endl;
                    cout << "Name: " << student.name << endl;
                    cout << "Division: " << student.division << endl;
                    cout << "Address: " << student.address << endl;

                    break;
                }
            }

            file.close();

            if (!found) 
            {
                cout << "Student record not found!" << endl;
            }
        }
};



int main() {
    int choice;
    Student s1;

    do {
        cout << "========== Student Information System ==========" << endl<<endl;;
        cout << "1. Add Student Record" << endl;
        cout << "2. Delete Student Record" << endl;
        cout << "3. Display Student Record" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                s1.addStudentRecord();
                break;
            case 2:
                s1.deleteStudentRecord();
                break;
            case 3:
                s1.displayStudentRecord();
                break;
            case 4:
                cout << "Exiting the program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    } while (choice != 4);

    return 0;
}