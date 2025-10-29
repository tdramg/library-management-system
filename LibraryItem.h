#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H

#include <string>
#include <sstream>

class LibraryItem {
protected:
    std::string title;
    std::string author;
    int id;
    bool isBorrowed;

public:
    LibraryItem() : title(), author(), id(0), isBorrowed(false) {}
    LibraryItem(const std::string &title, const std::string &author, int id)
        : title(title), author(author), id(id), isBorrowed(false) {}
    virtual ~LibraryItem() = default;

    int getId() const { return id; }
    const std::string &getTitle() const { return title; }
    const std::string &getAuthor() const { return author; }
    bool borrowed() const { return isBorrowed; }

    void borrow() { isBorrowed = true; }
    void ret() { isBorrowed = false; }

    virtual std::string getType() const = 0;
    virtual std::string displayInfo() const = 0;

    // Serialization to a single-line record (type|id|title|author|borrowed|extra)
    virtual std::string serialize() const {
        std::ostringstream oss;
        oss << getType() << '|' << id << '|' << escape(title) << '|' << escape(author) << '|' << (isBorrowed ? 1 : 0);
        return oss.str();
    }

    static std::string escape(const std::string &s) {
        std::string out;
        for (char c : s) {
            if (c == '|' ) out += "\\|";
            else if (c == '\\') out += "\\\\";
            else out += c;
        }
        return out;
    }

    static std::string unescape(const std::string &s) {
        std::string out;
        for (size_t i=0;i<s.size();++i){
            if (s[i]=='\\' && i+1<s.size()){
                out += s[i+1];
                ++i;
            } else out += s[i];
        }
        return out;
    }
};

#endif
