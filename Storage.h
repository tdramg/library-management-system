#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include <algorithm>
#include <functional>

template <typename T>
class Storage {
    std::vector<T> items;
public:
    void add(const T &t) { items.push_back(t); }
    bool removeIf(std::function<bool(const T&)> pred) {
        auto it = std::remove_if(items.begin(), items.end(), pred);
        if (it != items.end()) {
            items.erase(it, items.end());
            return true;
        }
        return false;
    }
    std::vector<T> findAll(std::function<bool(const T&)> pred) const {
        std::vector<T> out;
        for (const auto &i : items) if (pred(i)) out.push_back(i);
        return out;
    }
    T* findFirst(std::function<bool(const T&)> pred) {
        for (auto &i : items) if (pred(i)) return &i;
        return nullptr;
    }
    size_t size() const { return items.size(); }
    const std::vector<T>& all() const { return items; }
    void clear() { items.clear(); }
};

#endif
