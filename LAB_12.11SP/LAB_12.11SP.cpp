#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

struct Book {
    int udcNumber;
    string author;
    string title;
    int year;
    int quantity;
    Book* next;
};

class BookList {
private:
    Book* head;

public:
    BookList() : head(nullptr) {}

    void addBook(int udcNumber, const string& author, const string& title, int year, int quantity) {
        Book* newBook = new Book;
        newBook->udcNumber = udcNumber;
        newBook->author = author;
        newBook->title = title;
        newBook->year = year;
        newBook->quantity = quantity;
        newBook->next = nullptr;

        if (head == nullptr) {
            head = newBook;
        }
        else {
            Book* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newBook;
        }
    }

    void deleteBook(int year) {
        if (head == nullptr) {
            return;
        }

        if (head->year == year) {
            Book* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Book* current = head;
        while (current->next != nullptr) {
            if (current->next->year == year) {
                Book* temp = current->next;
                current->next = current->next->next;
                delete temp;
                return;
            }
            current = current->next;
        }
    }

    void printBooksByYear() {
        cout << "Books in the library sorted by year of publication:" << endl;
        Book* current = head;
        while (current != nullptr) {
            cout << "Year: " << current->year << ", Title: " << current->title << ", Author: " << current->author << ", Quantity: " << current->quantity << endl;
            current = current->next;
        }
    }

    void loadBooksFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Unable to open file." << endl;
            return;
        }

        int udcNumber, year, quantity;
        string author, title;

        while (file >> udcNumber >> author >> title >> year >> quantity) {
            addBook(udcNumber, author, title, year, quantity);
        }

        file.close();
    }
};

int main() {
    BookList library;
    string filename;

    cout << "Enter the path to the text file containing book records: ";
    getline(cin, filename);

    library.loadBooksFromFile(filename);

    int choice;
    do {
        cout << "\nLibrary Management System Menu:\n"
            << "1. Add a book\n"
            << "2. Remove a book\n"
            << "3. Print books sorted by year\n"
            << "4. Exit\n"
            << "Enter your choice: ";
        cin >> choice;

        // Clearing error flags and input buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            int udcNumber, year, quantity;
            string author, title;
            cout << "Enter UDC number, author, title, year, and quantity of the book: ";
            cin >> udcNumber >> author >> title >> year >> quantity;

            // Clearing error flags and input buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            library.addBook(udcNumber, author, title, year, quantity);
            break;
        }
        case 2: {
            int year;
            cout << "Enter the year of the book to remove: ";
            cin >> year;

            // Clearing error flags and input buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            library.deleteBook(year);
            break;
        }
        case 3:
            library.printBooksByYear();
            break;
        case 4:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
