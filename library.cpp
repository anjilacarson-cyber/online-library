#include <iostream>
#include <vector>
using namespace std;

// Book class
class Book {
private:
    int id;
    string title;
    string author;
    bool available;

public:
    Book(int i, string t, string a) {
        id = i;
        title = t;
        author = a;
        available = true;
    }

    int getId() { return id; }
    string getTitle() { return title; }
    string getAuthor() { return author; }
    bool isAvailable() { return available; }

    void borrow() { available = false; }
    void giveBack() { available = true; }

    void display() {
        cout << id << " | " << title << " | " << author
             << " | " << (available ? "Available" : "Borrowed") << endl;
    }
};

// User class
class User {
private:
    int userId;
    string name;
    vector<int> borrowedBookIds;

public:
    User(int id, string n) {
        userId = id;
        name = n;
    }

    int getId() { return userId; }

    void borrowBook(int bookId) {
        borrowedBookIds.push_back(bookId);
    }

    void returnBook(int bookId) {
        for (size_t i = 0; i < borrowedBookIds.size(); i++) {
            if (borrowedBookIds[i] == bookId) {
                borrowedBookIds.erase(borrowedBookIds.begin() + i);
                break;
            }
        }
    }
};

// Library class
class Library {
private:
    vector<Book> books;
    vector<User> users;

public:
    void addBook(Book b) { books.push_back(b); }
    void registerUser(User u) { users.push_back(u); }

    Book* findBook(int id) {
        for (auto &b : books)
            if (b.getId() == id) return &b;
        return nullptr;
    }

    User* findUser(int id) {
        for (auto &u : users)
            if (u.getId() == id) return &u;
        return nullptr;
    }

    void borrowBook(int userId, int bookId) {
        Book* b = findBook(bookId);
        User* u = findUser(userId);

        if (!b || !u) {
            cout << "User or Book not found." << endl;
            return;
        }

        if (!b->isAvailable()) {
            cout << "Book is already borrowed." << endl;
            return;
        }

        b->borrow();
        u->borrowBook(bookId);
        cout << "Book borrowed successfully." << endl;
    }

    void returnBook(int userId, int bookId) {
        Book* b = findBook(bookId);
        User* u = findUser(userId);

        if (!b || !u) {
            cout << "User or Book not found." << endl;
            return;
        }

        b->giveBack();
        u->returnBook(bookId);
        cout << "Book returned successfully." << endl;
    }

    void displayBooks() {
        cout << "ID | Title | Author | Status" << endl;
        cout << "-------------------------------" << endl;
        for (auto &b : books)
            b.display();
    }
};

// Main function
int main() {
    Library lib;

    // Sample data
    lib.addBook(Book(1, "C++ Basics", "Bjarne"));
    lib.addBook(Book(2, "OOP Design", "Gamma"));
    lib.addBook(Book(3, "Data Structures", "Weiss"));

    lib.registerUser(User(101, "Alice"));
    lib.registerUser(User(102, "Bob"));

    cout << "Initial Book List:" << endl;
    lib.displayBooks();

    cout << "\nBorrowing Book ID 1 by User 101..." << endl;
    lib.borrowBook(101, 1);

    cout << "\nBook List After Borrow:" << endl;
    lib.displayBooks();

    cout << "\nReturning Book ID 1 by User 101..." << endl;
    lib.returnBook(101, 1);

    cout << "\nFinal Book List:" << endl;
    lib.displayBooks();

    // Pause before closing (Windows-friendly)
    cout << "\nPress Enter to exit...";
    cin.get();

    return 0;
}
