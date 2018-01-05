#include "HashChains.h"
#include <assert.h>


void printInt(const int& x);

class getKey {
public:
    int operator()(int y) const {
        return y;
    }
};

void printInt(const int& x) {
    std::cout << x << " ";
}

int main() {
    int arr[7] = {1,15,3,8,32,6,4};
    HashChains<int,getKey> hashTable(arr, 7, getKey());
    assert(*hashTable.find(15) == 15);
    assert(*hashTable.find(1) == 1);
    assert(*hashTable.find(3) == 3);
    assert(*hashTable.find(8) == 8);
    assert(*hashTable.find(32) == 32);
    assert(*hashTable.find(6) == 6);
    assert(*hashTable.find(4) == 4);

    try {
        hashTable.find(2);
    } catch (HashExceptions::ElementNotFound& e) {
        std::cout << "1 - caught exception [V]" << std::endl;
    }
    try {
        hashTable.insert(8);
    } catch (HashExceptions::ElementAlreadyExists& e) {
        std::cout << "2 - caught exception [V]" << std::endl;
    }
    hashTable.remove(8);
    try {
        hashTable.find(8);
    } catch (HashExceptions::ElementNotFound& e) {
        std::cout << "3 - caught exception [V]" << std::endl;
    }
    hashTable.printHash();
    hashTable.insert(8);
    hashTable.insert(57);
    hashTable.insert(4516);
    hashTable.insert(6543);
    hashTable.insert(99);
    hashTable.insert(1222);
    hashTable.insert(137);
    hashTable.insert(385);
    hashTable.printHash();

    // Check table size here
    hashTable.remove(8);
    hashTable.remove(57);
    hashTable.remove(4516);
    hashTable.remove(6543);
    hashTable.remove(99);
    hashTable.remove(1222);
    hashTable.remove(137);
    hashTable.remove(385);
    hashTable.printHash();

    // Check table size here
}