//
// Created by mfbut on 2/11/2019.
//

#ifndef LINKEDLIST_DOUBLYLINKEDLIST_H
#define LINKEDLIST_DOUBLYLINKEDLIST_H

#include <vector>
#include <memory>
#include "DoublyLinkedNode.h"
#include "DoublyLinkedListEmptyError.h"
#include "ConstDoublyLinkedListIterator.h"
#include "DoublyLinkedListIterator.h"
#include "ConstReverseDoublyLinkedIterator.h"
#include "ReverseDoublyLinkedListIterator.h"

template<typename T>
class DoublyLinkedList {
public:
    using Node_Ptr = DoublyLinkedNode<T>*;
    using iterator = DoublyLinkedListIterator<T>;//put the type of your iterator here
    using const_iterator = ConstDoublyLinkedListIterator<T>;//put the type of your const iterator here
    using reverse_iterator = ReverseDoublyLinkedListIterator<T>; //put the type of your reverse iterator here
    using const_reverse_iterator = ConstReverseDoublyLinkedListIterator<T>;//put the type of your const reverse iterator here

    //create a Doubly Linked List that has the same values
    //as in the vector and in the same order
    explicit DoublyLinkedList(const std::vector<T>& values);

    //create an empty DoublyLinkedList
    DoublyLinkedList();


    //destructor
    virtual ~DoublyLinkedList();

    //remove all of the elements from your list
    void clear();

    //get a reference to the front element in the list
    const T& front() const;
    T& front();

    //get a reference to the last element in the list
    const T& back() const;
    T& back();

    //add a value to the front of the list
    void push_front(const T& value);

    //add a value to the back of the list
    void push_back(const T& value);

    //is the list empty?
    bool empty() const;

    //return the number of elements in the list
    int size() const;

    //return a constant bidirectional iterator to the front of the list
    const_iterator begin() const;
    const_iterator end() const;

    //return a nonconstant bidirectional iterator to the front of the list
    iterator begin();
    iterator end();

    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    reverse_iterator rbegin();
    reverse_iterator rend();

    //insert the value at the position in the list
    //I promise not to use the iterator again after the insertion is done
    //An example if we had the list 1 <-> 9 <-> 17
    //And the iterator was pointing to the 9 and we wanted to
    //insert 22 the result would be
    //1 <-> 22 <-> 9 <-> 17
    void insert(iterator& position, const T& value);

    //remove the element at the position pointed to
    //by the iterator.
    //I promise not to use the iterator again after the erase is done
    //An example if we had the list 1 <-> 9 <-> 17
    //And when the wanted to erase the iterator was at the 9
    //1 <-> 17
    void erase(iterator& position);

private:
    DoublyLinkedNode<T>* head;
    DoublyLinkedNode<T>* tail;
    int len;


};

//write to the stream each element in the list in order
//with a space in between them
template<typename T>
std::ostream& operator<<(std::ostream& out, const DoublyLinkedList<T>& doublyLinkedList);

//read elements from the stream as long as it is good
// or until a newline (\n) is encountered
//if a newline is encountered it should be consumed
template<typename T>
std::istream& operator>>(std::istream& in, DoublyLinkedList<T>& doublyLinkedList);

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
    len = 0;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const std::vector<T>& values) {
  head = nullptr;
  tail = nullptr;
  len = values.size();
  if(values.empty()){
        DoublyLinkedList();
    }
    else {
        for (unsigned int i = 0; i < values.size(); i++) {
            if (i == 0) {
                auto* newNode = new DoublyLinkedNode<T>(values.at(i), head, tail);
                head = newNode;
                tail = head;
            } else if (i == values.size()) {
                auto* lastNode = new DoublyLinkedNode<T>(values.at(i), tail, nullptr);
                tail = lastNode;
            } else {
                auto* node = new DoublyLinkedNode<T>(values.at(i), tail, nullptr);
                tail->setNext(node);
                tail = node;
            }
        }
    }
    for(iterator itr = this->begin(); itr!= this->end(); itr++){
        std::cout << itr.getNode()->getValue() << std::endl;
    }
    std::cout << "Before Erasing: " << std::endl;
}

template<typename T>
bool DoublyLinkedList<T>::empty() const {
    return (*this).size() == 0;
}

template<typename T>
int DoublyLinkedList<T>::size() const {
    return len;
}

template<typename T>
const T& DoublyLinkedList<T>::front() const {
    return this->head->getValue();
}

template<typename T>
T& DoublyLinkedList<T>::front() {
    return this->head->getValue();
}

template<typename T>
const T& DoublyLinkedList<T>::back() const {
    return this->tail->getValue();
}

template<typename T>
T& DoublyLinkedList<T>::back() {
    return this->tail->getValue();
}

template<typename T>
void DoublyLinkedList<T>::push_front(const T& value) {
    auto* newHeadNode = new DoublyLinkedNode<T>(value, nullptr, head);
    if(!this->empty()){
        head->setPrevious(newHeadNode);
    }
    else{
        tail = newHeadNode;
    }
    head = newHeadNode;
    len++;
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
    auto* newTailNode = new DoublyLinkedNode<T> (value, tail, nullptr);
    if(!this->empty()){
        tail->setNext(newTailNode);
    }
    else{
        head = newTailNode;
    }
    tail = newTailNode;
    len++;
}

template<typename T>
void DoublyLinkedList<T>::clear() {
    DoublyLinkedNode<T>* Node = head;

    while(Node != NULL){
        DoublyLinkedNode<T>* newNode = Node->getNext();
        delete Node;
        Node = newNode;
    }
    head = nullptr;
    tail = nullptr;
    len = 0;

}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template<typename T>
typename DoublyLinkedList<T>::const_iterator DoublyLinkedList<T>::begin() const {
    return const_iterator(head);
}

template<typename T>
typename DoublyLinkedList<T>::const_iterator DoublyLinkedList<T>::end() const {
    return const_iterator(nullptr);
}

template<typename T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::begin() {
    return iterator(head);

}

template<typename T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::end() {
    return iterator(nullptr);
}

template<typename T>
void DoublyLinkedList<T>::insert(iterator& position, const T& value) {
    if(this->empty()){
      auto* newNode = new DoublyLinkedNode<T>(value, nullptr, nullptr);
      head = newNode;
      tail = head;
      len++;
    }
    else if(this->size() == 1) {
      auto* newNode = new DoublyLinkedNode<T>(value, head, nullptr);
      (position).getNode()->setNext(newNode);
      (position.getNode())->getNext()->setPrevious(newNode);
      tail = newNode;
      len++;
    }
    else if (position == this->end()){
      push_back(value);
      len ++;
    }
    else {
      auto* newNode = new DoublyLinkedNode<T>(value, (position).getNode(), (position).getNode()->getNext());
      (position).getNode()->setNext(newNode);
      (position.getNode())->getNext()->setPrevious(newNode);
      len++;
    }
}

template<typename T>
void DoublyLinkedList<T>::erase(iterator& position) {
  if(this->size() > 2) {
    if (position.getNode() == head){
      position.getNode()->getNext()->setPrevious(nullptr);
      head = position.getNode()->getNext();
    }
    else if (position.getNode() == tail){
      position.getNode()->getPrevious()->setNext(nullptr);
      tail = position.getNode()->getPrevious();
    }
    else {
      (position).getNode()->getPrevious()->setNext((position).getNode()->getNext());
      (position).getNode()->getNext()->setPrevious((position).getNode()->getPrevious());
    }
    len--;
  }

  else if(this->size() == 2) {
    if (position.getNode() == head) {
      tail->setPrevious(nullptr);
      head = tail;
    } else if (position.getNode() == tail) {
      head->setNext(nullptr);
      tail = head;
    }
    len --;
  }
  else if(this->size() <= 1){
    (position).getNode()->setNext(nullptr);
    (position).getNode()->setPrevious(nullptr);
    len --;
    head = nullptr;
    tail = head;
//    DoublyLinkedList();
  }

//  for(iterator itr = this->begin(); itr!= this->end(); itr++){
//    std::cout << itr.getNode()->getValue() << std::endl;
//  }





}

template<typename T>
typename DoublyLinkedList<T>::const_reverse_iterator DoublyLinkedList<T>::crbegin() const {
    return const_reverse_iterator (tail);
    //May need revision
}

template<typename T>
typename DoublyLinkedList<T>::const_reverse_iterator DoublyLinkedList<T>::crend() const {
    return const_reverse_iterator (nullptr);
    //May need revision
}

template<typename T>
typename DoublyLinkedList<T>::reverse_iterator DoublyLinkedList<T>::rbegin() {
    return reverse_iterator (tail);
}

template<typename T>
typename DoublyLinkedList<T>::reverse_iterator DoublyLinkedList<T>::rend() {
    return reverse_iterator (nullptr);
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const DoublyLinkedList<T>& doublyLinkedList) {
    for (DoublyLinkedListIterator<T>& itr = doublyLinkedList.begin(); itr != doublyLinkedList.end(); itr++ ) {
        out << (itr.curNode)->getValue();
    }
    return out;
    //May need revision
}

template<typename T>
std::istream& operator>>(std::istream& in, DoublyLinkedList<T>& doublyLinkedList) {
    for (DoublyLinkedListIterator<T> itr = doublyLinkedList.begin(); itr != doublyLinkedList.end(); itr++ ) {
        in >> *itr;
    }
    return in;
    //May need revision
}

#endif //LINKEDLIST_DOUBLYLINKEDLIST_H