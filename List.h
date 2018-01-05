//
// Created by edri6 on 05/01/2018.
//

#ifndef WET2_FINAL_LIST_H
#define WET2_FINAL_LIST_H

#include <functional>
#include <iostream>

#define nullptr 0

namespace LExceptions{
    class ElementNotFound{
    public:
        ElementNotFound() {};
    };
}

template <class T>
class List {
    template <class P>
    class Node {
        friend class List<T>;
        friend class Iterator;
        P data;
        Node<P>* next;
        Node<P>* previous;
        /**
         * The function constructs a new node with the given data.
         * next and previous fields are initialized to NULL.
         * @param data - the data for the new node
         */
        Node<P>(const P& data): data(data),next(), previous(){}

        /**
         * Constructor
         */
        Node<P>(): data(),next(), previous(){}

        /**
         * The function constructs a new node by copying the data field from the
         * given copy_node. next and previous fields are initialized to NULL.
         * @param copy_node - the node to copy from
         */
        Node<P>(const Node<P>& copy_node): data(copy_node.data), next(),
                                           previous(){}

        /**
         * Assignment operator
         * @param assign_node - the node to assign
         */
        Node<P>& operator=(const Node<P>& assign_node);

        /**
         * Destructor for node
         */
        ~Node<P>() {
            this->next = nullptr;
            this->previous = nullptr;
        }

    };
    Node<T>* head;
    Node<T>* tail;
    int length;
public:
    class Iterator {
        Node<T> *current;
        const List<T> *list;

        /**
         * Constructor
         * @param list - the list the iterator will point to
         */
        Iterator(const List<T>& list): current(list.head), list(&list){}
        Iterator():current(), list(){};
    public:
        friend class List<T>;

        /**
         * The function moves the iterator to the next node in the list and
         * returns the updated iterator.
         * @return The updated iterator
         */
        Iterator& operator++(){
            if(this->current == nullptr)
                return *this;
            this->current = this->current->next;
            return *this;
        }

        /**
         * The function moves the iterator to the next node in the list and
         * returns new copy of the iterator before the change.
         * @return new iterator before the change
         */
        Iterator operator++(int){
            if(this->current == nullptr)
                return *this;
            Iterator iterator = *this;
            this->current = this->current->next;
            return iterator;
        }

        /**
         * The function moves the iterator to the previous node in the list and
         * returns the updated iterator.
         * @return The updated iterator
         */
        Iterator& operator--(){
            if(this->current == nullptr) {
                this->current = this->list->tail;
                return *this;
            }
            this->current = this->current->previous;
            return *this;
        }

        /**
         * The function moves the iterator to the previous node in the list and
         * returns new copy of the iterator before the change.
         * @return new iterator before the change
         */
        Iterator operator--(int){
            Iterator iterator = *this;
            if(this->current == nullptr){
                this->current = this->list->tail;
                return iterator;
            }
            this->current = this->current->previous;
            return iterator;
        }

        /**
         *  The function returns the data that the iterator points to.
         *  if the iterator points to the end of the list, the function throws
         *  ElementNotFound exception.
         * @return - The data of the node that the iterator points to.
         */
        T& operator*() const{
            if(this -> current == nullptr) {
                throw LExceptions::ElementNotFound();
            }
            return this->current->data;
        }

        /**
         * the function compares between two iterators
         * @param iterator - the iterator to compare to
         * @return true - if the iterators are equal
         *          flase - if not.
         */
        bool operator==(const Iterator& iterator) const{
            return (this->current == iterator.current &&
                    this->list == iterator.list);
        }

        /**
         * the function compares between two iterators
         * @param iterator - the iterator to compare to
         * @return true - if the iterators are not equal
         *          flase - if equal.
         */
        bool operator!=(const Iterator& iterator) const{
            return !(*this == iterator);
        }
    };

    /**
    * Constructs a new List.
    */
    List<T>(): head(),tail(), length(0){}

    /**
     * Copy constructor
     * @param list - the list to copy
     */
    List<T>(const List<T>& list): head(),tail(), length(0) {
        for (Iterator iterator = list.begin(); iterator != list.end();
             ++iterator) {
            this->insert(iterator);
        }
        this->length = list.length;
    }

    /**
     * Distructor
     */
    ~List<T>(){
        Iterator iterator = this->begin();
        while(iterator != this->end()){
            this->remove(iterator);
            iterator = this->begin();
        }
    }

    /**
     * Assignment operator
     * @param assign_list
     * @return
     */
    List<T>& operator=(const List<T>& assign_list){
        if(*this == assign_list) return *this;
        Iterator iterator = this->begin();
        while(iterator != this->end()){
            this->remove(iterator);
            iterator = this->begin();
        }
        iterator = assign_list.begin();
        for ( ; iterator != assign_list.end(); ++iterator) {
            this->insert(iterator);
        }
        return *this;
    }

    /**
     * The function compares two lists
     * @param list - the list to compare to
     * @return true - if the lists are equal
     *          false- if not
     */
    bool operator==(const List<T>& list) const{
        if(this->length != list.length) return false;
        Iterator list_iterator = list.begin();
        for (Iterator iterator = this->begin() ; iterator != this->end();
             iterator++) {
            if(iterator != list_iterator) return false;
            list_iterator++;
        }
        return true;
    }

    /**
     * The function compares two lists
     * @param list - the list to compare to
     * @return true - if the lists are not equal
     *          false- if they are
     */
    bool operator!=(const List<T>& list) const{
        return !(*this == list);
    }

    /**
     * The function returns iterator pointing to the first node in the list.
     * If the list is empty, the function returns iterator pointing to the end
     * of the list.
     *
     * @return Iterator pointing to the beginning of the list
     */
    Iterator begin() const {
        Iterator iterator(*this);
        return iterator;
    }

    /**
     * The function returns iterator pointing to the end of the list.
     * points to null.
     *
     * @return Iterator pointing to the end of the list = null.
     */
    Iterator end() const{
        Iterator iterator(*this);
        iterator.current = nullptr;
        return iterator;
    }

    /**
     * The function will add a new node with the given data to the list, before
     * the node which the iterator points to.
     * If the iterator points to another list, the function throws the
     * exception: ElementNotFound
     * @param data - the data of the new node to create
     * @param iterator - the iterator that points to a node in the list.
     */
    void insert(const T& data, Iterator iterator){
        if(iterator.list != this){
            throw LExceptions::ElementNotFound();
        }
        if(iterator.current == nullptr){
            this->insert(data);
            return;
        }
        Node<T>* new_node = new Node<T>(data);
        new_node->next = iterator.current;

        if(iterator.current != nullptr){
            new_node->previous = iterator.current->previous;
            iterator.current->previous = new_node;
        }
        if(iterator.current == this->head){
            this->head = new_node;
        } else {
            iterator--;
            iterator--;
            iterator.current->next = new_node;
        }
        this->length++;
    }

    /**
     * The function will add a new node with the given data to the end of the
     * list.
     * @param data - the data of the new node to create.
     */
    void insert(const T& data){
        try {
            Node<T> *new_node = new Node<T>(data);
            new_node->previous = this->tail;
            if (this->length == 0) {
                this->tail = new_node;
                this->head = new_node;
            } else {
                this->tail->next = new_node;
                this->tail = this->tail->next;
            }
            this->length++;
        } catch(const std::bad_alloc&){

        }
    }

    /**
     * The function will remove the node that iterator points from the list.
     * If the iterator points to another list or if the list is empty the
     * function throws the exception: ElementNotFound
     * @param iterator - the iterator that points to a node in the list.
     */
    void remove(Iterator iterator){
        if(*iterator.list != *this || this->length == 0 ||
           iterator.current == nullptr){
            throw LExceptions::ElementNotFound();
        }
        if(this->length == 1){
            this->head = nullptr;
            this->tail = nullptr;
        }
        else if(iterator.current == this->head){
            this->head->next->previous = nullptr;
            this->head = this->head->next;
        }
        else if(iterator.current == this->tail){
            this->tail->previous->next = nullptr;
            this->tail = this->tail->previous;
        }
        else {
            iterator.current->previous->next = iterator.current->next;
            iterator.current->next->previous = iterator.current->previous;
        }
        delete iterator.current;
        iterator.current = nullptr;
        this->length--;
    }

    /**
     * The function returns iterator that points to the first node in the list
     * that fullfils the predicate. If no one found, the iterator will point to
     * the end of the list - null.
     * @param predicate - a function that checks a condition and returns true
     *                      if a node fullfils the condition.
     * @return - iterator that points to a node according to the rules above.
     */
    template <typename Predicate>
    Iterator find(const Predicate& predicate){
        try {
            Iterator iterator=this->begin();
            for( ; iterator != this->end() ; iterator++){
                if(predicate(iterator.current->data)) return iterator;
            }
            return iterator;
        } catch (LExceptions::ElementNotFound& e){
            throw LExceptions::ElementNotFound();
        }

    }

    /**
     * The function returns iterator that points to the first node in the list
     * that his key is equal to the given key. If no one found, the iterator
     * will point to the end of the list - null.
     * @param getKey -  Function Object to get the Node's key
     * @param key - a key to compare to
     * @return - iteartor that points to a node according to the comparison
     */
    template <typename GetKey>
    Iterator find(const GetKey& getKey, int key){
        Iterator iterator=this->begin();
        for( ; iterator != this->end() ; iterator++){
            if(getKey(iterator.current->data) == key) return iterator;
        }
        return iterator;

    }

    /**
     * The function sorts a list according to the given compare function.
     * @param compare - a function that compares between two nodes and returns
     *                      true if one in lower than the second.
     */
    template <typename Compare>
    void sort(const Compare& compare){
        Iterator iterator = this->begin();
        List<T> sorted_list;
        sorted_list.insert(iterator.current->data);
        iterator++;
        Iterator sorted_iterator = sorted_list.begin();
        while(iterator != this->end()){
            while(sorted_iterator != sorted_list.end() &&
                  !compare(iterator,sorted_iterator)){
                sorted_iterator++;
            }
            sorted_list.insert(iterator,sorted_iterator);
            sorted_iterator = sorted_list.begin();
            iterator++;
        }
        *this = sorted_list;
    }

    /**
     * The function returns the number of nodes in the list.
     * @return - number of nodes in the list.
     */
    int getSize(){
        return this->length;
    }

};


#endif //WET2_FINAL_LIST_H
