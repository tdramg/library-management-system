
#include "Book.h"
#include "Magazine.h"
#include "LibraryUtils.h"
#include "Storage.h"
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <limits>

const std::string DATA_FILE = "library_data.txt";

std::vector<std::shared_ptr<LibraryItem>> libraryItems;
int currentId = 1;

void load() {
    int maxId=0;
    libraryItems = LibraryUtils::loadFromFile(DATA_FILE, maxId);
    if (maxId > 0) currentId = maxId + 1;
}

void save() {
    if (!LibraryUtils::saveToFile(DATA_FILE, libraryItems)) {
        std::cerr << "Warning: failed to save data to " << DATA_FILE << std::endl;
    }
}

int readInt(const std::string &prompt) {
    while (true) {
        std::cout << prompt;
        int v;
        if (std::cin >> v) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return v;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid integer, try again.\n";
    }
}

std::string readLine(const std::string &prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

void addItem() {
    std::cout << "Add Book (1) or Magazine (2)? ";
    int t = readInt("");
    if (t==1) {
        std::string title = readLine("Title: ");
        std::string author = readLine("Author: ");
        int pages = readInt("Pages: ");
        std::string publisher = readLine("Publisher: ");
        auto b = std::make_shared<Book>(title,author,currentId++,pages,publisher);
        libraryItems.push_back(b);
        std::cout << "Added Book ID="<<b->getId()<<"\n";
    } else {
        std::string title = readLine("Title: ");
        std::string author = readLine("Author: ");
        int issue = readInt("Issue Number: ");
        std::string freq = readLine("Frequency: ");
        auto m = std::make_shared<Magazine>(title,author,currentId++,issue,freq);
        libraryItems.push_back(m);
        std::cout << "Added Magazine ID="<<m->getId()<<"\n";
    }
    save();
}

void displayAll() {
    if (libraryItems.empty()) { std::cout << "Library empty.\n"; return; }
    for (auto &it : libraryItems) {
        std::cout << it->displayInfo() << "\n";
    }
}

std::shared_ptr<LibraryItem> findById(int id) {
    for (auto &it : libraryItems) if (it->getId() == id) return it;
    return nullptr;
}

void borrowItem() {
    int id = readInt("Enter ID to borrow: ");
    auto it = findById(id);
    if (!it) { std::cout << "Item not found.\n"; return; }
    if (it->borrowed()) { std::cout << "Item already borrowed.\n"; return; }
    it->borrow();
    std::cout << "Borrowed.\n";
    save();
}

void returnItem() {
    int id = readInt("Enter ID to return: ");
    auto it = findById(id);
    if (!it) { std::cout << "Item not found.\n"; return; }
    if (!it->borrowed()) { std::cout << "Item is not borrowed.\n"; return; }
    it->ret();
    std::cout << "Returned.\n";
    save();
}

void searchByTitle() {
    std::string q = readLine("Search title substring: ");
    for (auto &it : libraryItems) {
        if (it->getTitle().find(q) != std::string::npos) {
            std::cout << it->displayInfo() << "\n";
        }
    }
}

int main() {
    load();
    int choice=0;
    do {
        std::cout << "\n--- Library Menu ---\n";
        std::cout << "1. Add Item\n2. Display All\n3. Borrow Item\n4. Return Item\n5. Search by Title\n6. Exit\nChoose: ";
        choice = readInt("");
        switch (choice) {
            case 1: addItem(); break;
            case 2: displayAll(); break;
            case 3: borrowItem(); break;
            case 4: returnItem(); break;
            case 5: searchByTitle(); break;
            case 6: std::cout<<"Exiting.\n"; break;
            default: std::cout<<"Invalid choice.\n"; break;
        }
    } while (choice != 6);
    return 0;
}
