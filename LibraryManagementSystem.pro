QT -= gui

CONFIG += console c++17
TARGET = LibraryManagementSystem
TEMPLATE = app

SOURCES += \
    Book.cpp \
    Magazine.cpp \
    LibraryItem.cpp \
    main.cpp \
    LibraryUtils.cpp

HEADERS += \
    Book.h \
    Magazine.h \
    LibraryItem.h \
    Storage.h \
    LibraryUtils.h
