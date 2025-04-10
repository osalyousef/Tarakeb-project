#include <iostream>
#include <stdexcept>

template<typename K, typename V>
class MySimpleMap {
private:
    struct Entry {
        K key;
        V value;
    };

    Entry* entries;
    int capacity;
    int currentSize;

    void resize() {
        capacity *= 2;
        Entry* newEntries = new Entry[capacity];
        for (int i = 0; i < currentSize; ++i)
            newEntries[i] = entries[i];
        delete[] entries;
        entries = newEntries;
    }

    void sortEntries() {
        for (int i = 0; i < currentSize - 1; ++i) {
            for (int j = i + 1; j < currentSize; ++j) {
                if (entries[i].key > entries[j].key)
                    std::swap(entries[i], entries[j]);
            }
        }
    }

public:
    MySimpleMap(int initialCapacity = 10)
        : capacity(initialCapacity), currentSize(0) {
        entries = new Entry[capacity];
    }

    ~MySimpleMap() {
        delete[] entries;
    }

    void insert(const K& key, const V& value) {
        for (int i = 0; i < currentSize; ++i) {
            if (entries[i].key == key) {
                entries[i].value = value; // update if exists
                return;
            }
        }
        if (currentSize == capacity)
            resize();

        entries[currentSize++] = {key, value};
        sortEntries();  // optional: keep keys ordered
    }

    V get(const K& key) const {
        for (int i = 0; i < currentSize; ++i) {
            if (entries[i].key == key)
                return entries[i].value;
        }
        throw std::out_of_range("Key not found");
    }

    bool exists(const K& key) const {
        for (int i = 0; i < currentSize; ++i)
            if (entries[i].key == key)
                return true;
        return false;
    }

    void remove(const K& key) {
        for (int i = 0; i < currentSize; ++i) {
            if (entries[i].key == key) {
                for (int j = i; j < currentSize - 1; ++j)
                    entries[j] = entries[j + 1];
                --currentSize;
                return;
            }
        }
    }

    void print() const {
        for (int i = 0; i < currentSize; ++i) {
            std::cout << entries[i].key << " => " << entries[i].value << std::endl;
        }
    }

    int size() const {
        return currentSize;
    }
};
