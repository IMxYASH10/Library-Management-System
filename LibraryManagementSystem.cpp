#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// ================== Book Class ==================
class Book {
public:
    int id;
    string title, author;
    bool isIssued;

    Book(int id, string title, string author, bool isIssued = false) {
        this->id = id;
        this->title = title;
        this->author = author;
        this->isIssued = isIssued;
    }

    void display() {
        cout << "ID: " << id << " | Title: " << title 
             << " | Author: " << author 
             << " | Status: " << (isIssued ? "Issued" : "Available") << endl;
    }
};

// ================== Library Class ==================
class Library {
    vector<Book> books;

public:
    // Load books from file
    void loadFromFile() {
        ifstream fin("library.txt");
        if (!fin) return;

        books.clear();
        int id, status;
        string title, author;

        while (fin >> id) {
            fin.ignore();
            getline(fin, title);
            getline(fin, author);
            fin >> status;
            books.push_back(Book(id, title, author, status));
        }
        fin.close();
    }

    // Save books to file
    void saveToFile() {
        ofstream fout("library.txt");
        for (auto &b : books) {
            fout << b.id << endl;
            fout << b.title << endl;
            fout << b.author << endl;
            fout << b.isIssued << endl;
        }
        fout.close();
    }

    // Add a new book
    void addBook() {
        int id;
        string title, author;

        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        books.push_back(Book(id, title, author));
        cout << "Book added successfully!\n";
    }

    // Display all books
    void displayBooks() {
        if (books.empty()) {
            cout << "No books in library.\n";
            return;
        }
        for (auto &b : books) b.display();
    }

    // Issue a book
    void issueBook() {
        int id;
        cout << "Enter Book ID to issue: ";
        cin >> id;

        for (auto &b : books) {
            if (b.id == id) {
                if (!b.isIssued) {
                    b.isIssued = true;
                    cout << "Book issued successfully!\n";
                } else {
                    cout << "Book is already issued.\n";
                }
                return;
            }
        }
        cout << "Book not found!\n";
    }

    // Return a book
    void returnBook() {
        int id;
        cout << "Enter Book ID to return: ";
        cin >> id;

        for (auto &b : books) {
            if (b.id == id) {
                if (b.isIssued) {
                    b.isIssued = false;
                    cout << "Book returned successfully!\n";
                } else {
                    cout << "Book was not issued.\n";
                }
                return;
            }
        }
        cout << "Book not found!\n";
    }
};

// ================== Main Function ==================
int main() {
    Library lib;
    lib.loadFromFile();

    int choice;
    do {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n2. Display Books\n3. Issue Book\n4. Return Book\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: lib.addBook(); break;
        case 2: lib.displayBooks(); break;
        case 3: lib.issueBook(); break;
        case 4: lib.returnBook(); break;
        case 5: lib.saveToFile(); cout << "Exiting... Data saved!\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
