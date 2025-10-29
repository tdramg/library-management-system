#ifndef BOOK_H
#define BOOK_H

#include "LibraryItem.h"
#include <string>

class Book : public LibraryItem {
    int pages;
    std::string publisher;
public:
    Book() : LibraryItem(), pages(0), publisher() {}
    Book(const std::string &title, const std::string &author, int id, int pages, const std::string &publisher)
        : LibraryItem(title, author, id), pages(pages), publisher(publisher) {}

    int getPages() const { return pages; }
    const std::string &getPublisher() const { return publisher; }

    std::string getType() const override { return "BOOK"; }

    std::string displayInfo() const override {
        std::ostringstream oss;
        oss << "Book [ID="<<id<<"] Title: "<<title<<", Author: "<<author<<", Pages: "<<pages<<", Publisher: "<<publisher<<", Borrowed: "<<(isBorrowed? "Yes":"No");
        return oss.str();
    }

    std::string serialize() const override {
        std::ostringstream oss;
        oss << LibraryItem::serialize() << '|' << pages << '|' << LibraryItem::escape(publisher);
        return oss.str();
    }

    static Book deserializeFromParts(int id, const std::string &title, const std::string &author, int borrowed, const std::string &extra1, const std::string &extra2) {
        Book b;
        b.id = id;
        b.title = title;
        b.author = author;
        b.isBorrowed = borrowed!=0;
        b.pages = std::stoi(extra1);
        b.publisher = extra2;
        return b;
    }
};

#endif
