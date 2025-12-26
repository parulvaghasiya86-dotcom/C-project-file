#include <iostream>
using namespace std;

class LibraryItem {
private:
    char title[50];
    char author[50];
    char dueDate[15];

public:
    LibraryItem(const char t[], const char a[], const char d[]) {
        int i = 0;
        while (t[i] != '\0') { title[i] = t[i]; i++; }
        title[i] = '\0';

        i = 0;
        while (a[i] != '\0') { author[i] = a[i]; i++; }
        author[i] = '\0';

        i = 0;
        while (d[i] != '\0') { dueDate[i] = d[i]; i++; }
        dueDate[i] = '\0';
    }

    virtual ~LibraryItem() {}

    const char* getTitle() const { return title; }
    const char* getAuthor() const { return author; }
    const char* getDueDate() const { return dueDate; }

    void setTitle(const char t[]) {
        int i = 0;
        while (t[i] != '\0') { title[i] = t[i]; i++; }
        title[i] = '\0';
    }

    void setAuthor(const char a[]) {
        int i = 0;
        while (a[i] != '\0') { author[i] = a[i]; i++; }
        author[i] = '\0';
    }

    void setDueDate(const char d[]) {
        int i = 0;
        while (d[i] != '\0') { dueDate[i] = d[i]; i++; }
        dueDate[i] = '\0';
    }

    virtual void checkOut() = 0;
    virtual void returnItem() = 0;
    virtual void displayDetails() const = 0;
};

class Book : public LibraryItem {
private:
    char isbn[14];

public:
    Book(const char t[], const char a[], const char d[], const char i[])
        : LibraryItem(t, a, d) {

        int len = 0;
        while (i[len] != '\0') len++;

        if (len != 13)
            throw "Invalid ISBN format!";

        for (int j = 0; j < 14; j++)
            isbn[j] = i[j];
    }

    void checkOut() override {
        cout << "Book checked out successfully.\n";
    }

    void returnItem() override {
        cout << "Book returned successfully.\n";
    }

    void displayDetails() const override {
        cout << "\nType: Book";
        cout << "\nTitle: " << getTitle();
        cout << "\nAuthor: " << getAuthor();
        cout << "\nDue Date: " << getDueDate();
        cout << "\nISBN: " << isbn << "\n";
    }
};

class DVD : public LibraryItem {
private:
    int duration;

public:
    DVD(const char t[], const char a[], const char d[], int dur)
        : LibraryItem(t, a, d), duration(dur) {

        if (duration <= 0)
            throw "Invalid DVD duration!";
    }

    void checkOut() override {
        cout << "DVD checked out successfully.\n";
    }

    void returnItem() override {
        cout << "DVD returned successfully.\n";
    }

    void displayDetails() const override {
        cout << "\nType: DVD";
        cout << "\nTitle: " << getTitle();
        cout << "\nAuthor: " << getAuthor();
        cout << "\nDue Date: " << getDueDate();
        cout << "\nDuration: " << duration << " minutes\n";
    }
};

class Magazine : public LibraryItem {
private:
    int issueNumber;

public:
    Magazine(const char t[], const char a[], const char d[], int issue)
        : LibraryItem(t, a, d), issueNumber(issue) {

        if (issue <= 0)
            throw "Invalid issue number!";
    }

    void checkOut() override {
        cout << "Magazine checked out successfully.\n";
    }

    void returnItem() override {
        cout << "Magazine returned successfully.\n";
    }

    void displayDetails() const override {
        cout << "\nType: Magazine";
        cout << "\nTitle: " << getTitle();
        cout << "\nAuthor: " << getAuthor();
        cout << "\nDue Date: " << getDueDate();
        cout << "\nIssue Number: " << issueNumber << "\n";
    }
};

int main() {
    LibraryItem* items[10];   
    int count = 0;
    int choice;

    try {

        items[count++] = new Book("C++ OOP", "Bjarne", "10-10-2025", "1234567890123");
        items[count++] = new DVD("OOP DVD", "TechGuru", "12-10-2025", 90);
        items[count++] = new Magazine("Tech Today", "Editor", "15-10-2025", 5);
    }
    catch (const char* msg) {
        cout << "Error: " << msg << endl;
    }

    do {
        cout << "\n===== Library Management System =====";
        cout << "\n1. Display Items";
        cout << "\n2. Check Out Item";
        cout << "\n3. Return Item";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            for (int i = 0; i < count; i++) {
                cout << "\nItem No: " << i + 1;
                items[i]->displayDetails();
            }
            break;

        case 2: {
            int num;
            cout << "Enter item number to check out: ";
            cin >> num;

            if (num >= 1 && num <= count)
                items[num - 1]->checkOut();
            else
                cout << "Invalid item number!\n";
            break;
        }

        case 3: {
            int num;
            cout << "Enter item number to return: ";
            cin >> num;

            if (num >= 1 && num <= count)
                items[num - 1]->returnItem();
            else
                cout << "Invalid item number!\n";
            break;
        }

        case 4:
            cout << "Thank you for using Library Management System.\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    for (int i = 0; i < count; i++)
        delete items[i];

    return 0;
}

/*
	Output:
	
	===== Library Management System =====
	1. Display Items
	2. Check Out Item
	3. Return Item
	4. Exit
	Enter your choice: 1
		
	Item No: 1
	Type: Book
	Title: C++ OOP
	Author: Bjarne
	Due Date: 10-10-2025
	ISBN: 1234567890123
	
	Item No: 2
	Type: DVD
	Title: OOP DVD
	Author: TechGuru
	Due Date: 12-10-2025
	Duration: 90 minutes
	
	Item No: 3
	Type: Magazine
	Title: Tech Today
	Author: Editor
	Due Date: 15-10-2025
	Issue Number: 5
	
	===== Library Management System =====
	1. Display Items
	2. Check Out Item
	3. Return Item
	4. Exit
	Enter your choice: 2
	Enter item number to check out: 2
	DVD checked out successfully.
	
	===== Library Management System =====
	1. Display Items
	2. Check Out Item
	3. Return Item
	4. Exit
	Enter your choice: 3
	Enter item number to return: 2
	DVD returned successfully.
	
	===== Library Management System =====
	1. Display Items
	2. Check Out Item
	3. Return Item
	4. Exit
	Enter your choice: 4
	Thank you for using Library Management System.
*/