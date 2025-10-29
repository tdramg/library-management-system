#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "LibraryItem.h"
#include <string>

class Magazine : public LibraryItem {
    int issueNumber;
    std::string frequency;
public:
    Magazine() : LibraryItem(), issueNumber(0), frequency() {}
    Magazine(const std::string &title, const std::string &author, int id, int issueNumber, const std::string &frequency)
        : LibraryItem(title, author, id), issueNumber(issueNumber), frequency(frequency) {}

    int getIssueNumber() const { return issueNumber; }
    const std::string &getFrequency() const { return frequency; }

    std::string getType() const override { return "MAGAZINE"; }

    std::string displayInfo() const override {
        std::ostringstream oss;
        oss << "Magazine [ID="<<id<<"] Title: "<<title<<", Author: "<<author<<", Issue: "<<issueNumber<<", Freq: "<<frequency<<", Borrowed: "<<(isBorrowed? "Yes":"No");
        return oss.str();
    }

    std::string serialize() const override {
        std::ostringstream oss;
        oss << LibraryItem::serialize() << '|' << issueNumber << '|' << LibraryItem::escape(frequency);
        return oss.str();
    }

    static Magazine deserializeFromParts(int id, const std::string &title, const std::string &author, int borrowed, const std::string &extra1, const std::string &extra2) {
        Magazine m;
        m.id = id;
        m.title = title;
        m.author = author;
        m.isBorrowed = borrowed!=0;
        m.issueNumber = std::stoi(extra1);
        m.frequency = extra2;
        return m;
    }
};

#endif
