//
// Created by Michal on 27/11/2017.
//
#ifndef WET2_HASHCHAINS_H
#define WET2_HASHCHAINS_H

#include <iostream>
#include <functional>
#include <new>
#include "List.h"

#define nullptr 0
#define HASH_INIT_SIZE 2
#define MIN_LOAD_FACTOR 0.5
#define MAX_LOAD_FACTOR 1
#define LOAD_FACTOR 0.67


namespace HashExceptions{
    class ElementNotFound{
    public:
        ElementNotFound() {};
    };
    class ElementAlreadyExists{
    public:
        ElementAlreadyExists() {};
    };
}

template <class T, class GetKey>
class HashChains {
    friend class Colosseum;
//--------------HASH CHAIN FIELDS-----------------------------
    int hash_size;
    List<T>* hash_table; //List is not already pointer?
    int num_of_elements;
    GetKey getKey;

    /**
     * The function calculates the the hash for a given element
     * @param element_key - the key of an element
     * @return the list that fits for the element
     */
    List<T>& hash(int element_key){
        return this->hash_table[element_key % hash_size];
    }

    /**
     * The function resizes the hash_table in order to save the load factor
     * between the MIN_LOAD_FACTOR and the MAX_LOAD_FACTOR. If needed, the
     * hash_table will be resized according to the LOAD_FACTOR.
     * (num_of_Elements/LOAD_FACTOR)
     */
    template<typename HelpFunc>
    void dynamicHash(const HelpFunc& helpFunc){
        if(((double)num_of_elements/hash_size > ((double)MAX_LOAD_FACTOR)) ||
        ((double)num_of_elements/hash_size < (double)MIN_LOAD_FACTOR)){
            List<T>* old_hash_table = hash_table;
            int old_hash_size = hash_size;
            hash_size = (int)(num_of_elements/LOAD_FACTOR);
            try{
                hash_table = new List<T>[hash_size];
            } catch(std::bad_alloc& e){
                hash_table = old_hash_table;
                hash_size = old_hash_size;
                throw e;
            }
            for(int i=0; i<old_hash_size; ++i){
                List<T>& ListToDestroy = old_hash_table[i];
                typename List<T>::Iterator iterator = ListToDestroy.begin();
                try {
                    while (iterator != ListToDestroy.end()) {
                        List<T>& list = hash(getKey(*iterator));
                        list.insert(*iterator);
                        helpFunc(*iterator);
                        ListToDestroy.remove(iterator);
                        iterator = ListToDestroy.begin();
                    }
                } catch (LExceptions::ElementNotFound& e) {
                    throw HashExceptions::ElementNotFound();
                }
            }
            delete[] old_hash_table;
        }
    }

public:
    /**
     * default constructor
     * @param getKey - function that gets the key of a T type element
     */
    HashChains<T, GetKey>(const GetKey& getKey): hash_size(HASH_INIT_SIZE),
             hash_table(new List<T>[HASH_INIT_SIZE]),
             num_of_elements(0), getKey(getKey){}

    /**
     * Constructor
     * @param table - the new data to insert to the hash table
     * @param num  - the number of elements to insert to the hash table
     */
    HashChains<T,GetKey>(T* table, const int num, const GetKey& getKey):
            hash_size(int(num/LOAD_FACTOR)), num_of_elements(num),
            getKey(getKey){
        this->hash_table = new List<T>[hash_size];
        for(int i=0; i < num; ++i){
            List<T>& list = hash(getKey(table[i]));
            list.insert(table[i]);
        }
    }

    /**
     * destructor
     */
    ~HashChains<T, GetKey>(){
        delete[] hash_table;              //makes a bug
    }

public:

    /**
     * The function find an element according to a given element_key
     * @param element_key - the key of the element to find
     * @return pointer to the found element or null if doesn't exist
     */
    T* find(const int element_key){
        List<T>& list = hash(element_key);
        try{
            typename List<T>::Iterator iterator = list.find(getKey, element_key);
            if(iterator == list.end())
                throw HashExceptions::ElementNotFound();
            return &((*iterator));
        } catch (LExceptions::ElementNotFound& e){
            throw HashExceptions::ElementNotFound();
        }
    }


    /**
     * The function inserts a given element to the matching list according
     * to the hash function. If the element already exists the function throws
     * exception
     * @param element - the element to insert
     */
    template<typename HelpFunc>
    void insert(const T& element, const HelpFunc& helpFunc)
    {
        try{
            if(find(getKey(element)))
                throw HashExceptions::ElementAlreadyExists();
        } catch (HashExceptions::ElementNotFound& e){}
        num_of_elements++;
        this->dynamicHash(helpFunc);
        List<T>& list = hash(getKey(element));
        list.insert(element);
       // printHash();
    }

    /**
     * the function removes the element with the given key from the hash_table
     * @param key - the key of the element to remove
     */
    template<typename HelpFunc>
    void remove(int key, const HelpFunc& helpFunc) {
        List<T> &list = hash(key);
        if (find(key) == nullptr)
            throw HashExceptions::ElementNotFound();
        list.remove(list.find(getKey, key));
        num_of_elements--;
        this->dynamicHash(helpFunc);
    }


    void printHash(){
        int j = 1;
        std::cout << "Hash Size: " << hash_size << std::endl;
        std::cout << "Num of elements: " << num_of_elements << std::endl;
        //std::cout << "Keys: " << std::endl;
        for(int i=0; i<this->hash_size ;++i){
            typename List<T>::Iterator iterator = this->hash_table[i].begin();
            std::cout << "List num " << i << " -> ";
            for (; iterator != this->hash_table[i].end(); iterator++) {
                std::cout << " " << getKey(*iterator);
                j++;
            }
            std::cout << std::endl;
        }
    }
};

#endif //WET2_HASHCHAINS_H
