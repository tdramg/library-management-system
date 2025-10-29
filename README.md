

Files added/modified:
- LibraryItem.h        : abstract base class, serialization helpers
- LibraryItem.cpp      : minimal file to satisfy build
- Book.h               : Book subclass with pages & publisher
- Book.cpp             : minimal file
- Magazine.h           : Magazine subclass with issue & frequency
- Magazine.cpp         : minimal file
- Storage.h            : template storage utility
- LibraryUtils.h/cpp   : file persistence (load/save) and parsing
- main.cpp             : console UI implementing add/display/borrow/return/search
- LibraryManagementSystem.pro : updated to include new headers and sources

How to build:
1. Open LibraryManagementSystem.pro in Qt Creator configured for Qt 6.9.0 MinGW 64-bit.
2. Build the project (Release or Debug).
3. Run the executable. The program reads/writes `library_data.txt` in the working directory.

Behavior implemented:
- Add Book or Magazine with incremental unique ID.
- Display all items with full info.
- Borrow and Return by ID, with state persisted.
- Search by title substring.
- Persistence: simple line-oriented text file 'library_data.txt' with escape support for '|' characters.
- Template Storage<T> provided for potential internal use (not strictly necessary for console UI but implemented per assignment).