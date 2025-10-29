#include "LibraryUtils.h"
#include <fstream>
#include <iostream>

std::vector<std::shared_ptr<LibraryItem>> LibraryUtils::loadFromFile(const std::string &filename, int &maxIdOut) {
    std::vector<std::shared_ptr<LibraryItem>> out;
    std::ifstream in(filename);
    maxIdOut = 0;
    if (!in) return out;
    std::string line;
    while (std::getline(in,line)) {
        if (line.empty()) continue;
        // split by '|' but handle escaped pipes
        std::vector<std::string> parts;
        std::string cur;
        bool esc=false;
        for (size_t i=0;i<line.size();++i){
            char c=line[i];
            if (!esc && c=='|') { parts.push_back(cur); cur.clear(); }
            else {
                if (!esc && c=='\\') { esc=true; continue; }
                cur.push_back(c);
                esc=false;
            }
        }
        parts.push_back(cur);
        if (parts.size() < 5) continue;
        std::string type = parts[0];
        int id = std::stoi(parts[1]);
        std::string title = LibraryItem::unescape(parts[2]);
        std::string author = LibraryItem::unescape(parts[3]);
        int borrowed = std::stoi(parts[4]);
        if (type=="BOOK") {
            if (parts.size() < 7) continue;
            std::string extra1 = parts[5];
            std::string extra2 = LibraryItem::unescape(parts[6]);
            Book b = Book::deserializeFromParts(id,title,author,borrowed,extra1,extra2);
            out.push_back(std::make_shared<Book>(b));
        } else if (type=="MAGAZINE") {
            if (parts.size() < 7) continue;
            std::string extra1 = parts[5];
            std::string extra2 = LibraryItem::unescape(parts[6]);
            Magazine m = Magazine::deserializeFromParts(id,title,author,borrowed,extra1,extra2);
            out.push_back(std::make_shared<Magazine>(m));
        }
        if (id > maxIdOut) maxIdOut = id;
    }
    return out;
}

bool LibraryUtils::saveToFile(const std::string &filename, const std::vector<std::shared_ptr<LibraryItem>> &items) {
    std::ofstream out(filename);
    if (!out) return false;
    for (auto &it : items) {
        out << it->serialize() << '\n';
    }
    return true;
}
