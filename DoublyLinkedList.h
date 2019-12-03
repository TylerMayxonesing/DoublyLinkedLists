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
  const DoublyLinkedNode<T>* head;
  const DoublyLinkedNode<T>* tail;


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

}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const std::vector<T>& values) {
  for(unsigned int i = 0; i < values.size(); i++){
    if (i == 0){
      head = new DoublyLinkedNode<T> (values.at(i), nullptr, tail);
      tail = new DoublyLinkedNode<T> (values.at(i+1), head, nullptr);
    }
    else {
      this->push_back(values.at(i));
    }
  }
}

template<typename T>
bool DoublyLinkedList<T>::empty() const {
  return this->size() == 0;
}

template<typename T>
int DoublyLinkedList<T>::size() const {
  return  this->end() - this->begin();
}

template<typename T>
const T& DoublyLinkedList<T>::front() const {
  return this->at(0);
}

template<typename T>
T& DoublyLinkedList<T>::front() {
  return this->at(0);
}

template<typename T>
const T& DoublyLinkedList<T>::back() const {
  return this->at(this->size());
}

template<typename T>
T& DoublyLinkedList<T>::back() {
  return this->at(this->size());
}

template<typename T>
void DoublyLinkedList<T>::push_front(const T& value) {
  //DoublyLinkedList<T> Node(value, previous, next);
  DoublyLinkedNode<T>* newHeadNode = new DoublyLinkedNode<T>(value, nullptr, head);
  if(!this->empty()){
    head->setPrevious(newHeadNode);
  }
  else{
    tail = newHeadNode;
  }
  head = newHeadNode;
  ++newHeadNode->size();
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
  DoublyLinkedNode<T>* newTailNode = new DoublyLinkedNode<T> (value, nullptr, tail);
  if(!this->empty()){
    tail->setNext(newTailNode);
  }
  else{
    head = newTailNode;
  }
  tail = newTailNode;
  ++newTailNode->size();
}

template<typename T>
void DoublyLinkedList<T>::clear() {

}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {

}

template<typename T>
typename DoublyLinkedList<T>::const_iterator DoublyLinkedList<T>::begin() const {
  return const_iterator(head);
}

template<typename T>
typename DoublyLinkedList<T>::const_iterator DoublyLinkedList<T>::end() const {
  return const_iterator(tail);
}

template<typename T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::begin() {
  return iterator(head);

}

template<typename T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::end() {
  return iterator(tail);
}

template<typename T>
void DoublyLinkedList<T>::insert(iterator& position, const T& value) {
  DoublyLinkedList<T> newNode = new DoublyLinkedList<T>(value, position.curNode, (position.curNode)->getNext());
  position.curNode->setNext(newNode);
  ++newNode.size();
  //May need revision
}

template<typename T>
void DoublyLinkedList<T>::erase(iterator& position) {
  (position.curNode)->getPrevious()->setNext((position.curNode)->getNext());
  (position.curNode)->getNext()->setPrevious((position.curNode)->getPrevious());
  delete(position);
  //May need revision
}

template<typename T>
typename DoublyLinkedList<T>::const_reverse_iterator DoublyLinkedList<T>::crbegin() const {
  return const_reverse_iterator (tail);
  //May need revision
}

template<typename T>
typename DoublyLinkedList<T>::const_reverse_iterator DoublyLinkedList<T>::crend() const {
  return const_reverse_iterator (head);
  //May need revision
}

template<typename T>
typename DoublyLinkedList<T>::reverse_iterator DoublyLinkedList<T>::rbegin() {
  return reverse_iterator (tail);
}

template<typename T>
typename DoublyLinkedList<T>::reverse_iterator DoublyLinkedList<T>::rend() {
  return reverse_iterator (head);
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
  for (DoublyLinkedListIterator<T>& itr = doublyLinkedList.begin(); itr != doublyLinkedList.end(); itr++ ) {
    in >> (itr.curNode)->getValue();
  }
  return in;
  //May need revision
}

#endif //LINKEDLIST_DOUBLYLINKEDLIST_H
