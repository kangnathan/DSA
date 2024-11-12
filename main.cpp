#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

struct NODE {
    string code, title, lec, lab, sem;
    int year;
    NODE* nextNode;
} *head, *tail;

void insertTail() {
    NODE* newNode = new NODE;
    cout << "Data Entry\n";
    cout << "Enter code: "; cin >> newNode->code;
    cout << "Enter title: "; cin >> newNode->title;
    cout << "Enter lecture: "; cin >> newNode->lec;
    cout << "Enter laboratory: "; cin >> newNode->lab;
    cout << "Enter semester: "; cin >> newNode->sem;
    cout << "Enter year: "; cin >> newNode->year;
    newNode->nextNode = NULL;

    if (head == NULL) {
        head = tail = newNode;
    } else {
        tail->nextNode = newNode;
        tail = newNode;
    }
}

void display() {
    if (head == NULL) {
        cout << "No courses available." << endl;
        return;
    }

    cout << "Course Checklist\nCode\tTitle\tLec\tLab\tSem\tYear\n";
    NODE* readNode = head;
    while (readNode != NULL) {
        cout << readNode->code << "\t"
             << readNode->title << "\t"
             << readNode->lec << "\t"
             << readNode->lab << "\t"
             << readNode->sem << "\t"
             << readNode->year << endl;
        readNode = readNode->nextNode;
    }
}

void saveToFile() {
    ofstream saveData("course_management.txt");
    if (!saveData) {
        cout << "Failed to open file for saving." << endl;
        return;
    }

    NODE* readNode = head;
    while (readNode != NULL) {
        saveData << readNode->code << ","
                 << readNode->title << ","
                 << readNode->lec << ","
                 << readNode->lab << ","
                 << readNode->sem << ","
                 << readNode->year << endl;
        readNode = readNode->nextNode;
    }
    saveData.close();
    cout << "Save successful." << endl;
}

void loadData() {
    ifstream readData("course_management.txt");
    if (!readData) {
        cout << "File not found." << endl;
        return;
    }

    string code, title, lec, lab, sem;
    int year;
    while (getline(readData, code, ',') && 
           getline(readData, title, ',') && 
           getline(readData, lec, ',') && 
           getline(readData, lab, ',') && 
           getline(readData, sem, ',') &&
           readData >> year) {
        // Clear the rest of the line (if there's extra data after the year)
        readData.ignore();

        NODE* newNode = new NODE;
        newNode->code = code;
        newNode->title = title;
        newNode->lec = lec;
        newNode->lab = lab;
        newNode->sem = sem;
        newNode->year = year;
        newNode->nextNode = NULL;

        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->nextNode = newNode;
            tail = newNode;
        }
    }
    readData.close();
    cout << "Data loaded successfully." << endl;
}

void deleteList() {
    NODE* current = head;
    while (current != NULL) {
        NODE* next = current->nextNode;
        delete current;
        current = next;
    }
    head = tail = NULL;
}

int main() {
    head = tail = NULL;

    int choice;
    while (true) {
        cout << "\nCourse Management\n";
        cout << "1 - Data Entry\n";
        cout << "2 - Display Courses\n";
        cout << "3 - Save to File\n";
        cout << "4 - Load Data\n";
        cout << "5 - Exit\n";
        cout << "Choice: ";
        cin >> choice;

        // Clear error flags and ignore invalid input
        if (cin.fail()) {
            cin.clear();  // clear error flag
            cin.ignore(10000, '\n');  // discard invalid input
            cout << "Invalid input, please enter a number." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                insertTail();
                break;
            case 2:
                display();
                break;
            case 3:
                saveToFile();
                break;
            case 4:
                loadData();
                break;
            case 5:
                deleteList();
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
        }
    }
}

