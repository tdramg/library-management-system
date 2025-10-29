#ifndef LIBRARYUTILS_H
#define LIBRARYUTILS_H

#include <vector>
#include <memory>
#include <string>
#include "LibraryItem.h"
#include "Book.h"
#include "Magazine.h"

class LibraryUtils {
public:
    // Load items from a simple line-oriented file. Returns items and sets maxIdOut to highest id found.
    static std::vector<std::shared_ptr<LibraryItem>> loadFromFile(const std::string &filename, int &maxIdOut);
    static bool saveToFile(const std::string &filename, const std::vector<std::shared_ptr<LibraryItem>> &items);
};

#endif
