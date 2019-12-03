//
// Created by mfbut on 2/11/2019.
//

#ifndef LINKEDLIST_DOUBLELINKEDNODE_H
#define LINKEDLIST_DOUBLELINKEDNODE_H
#include <iostream>

template<typename T>
class DoublyLinkedNode {
  explicit DoublyLinkedNode<T> (const T& value, DoublyLinkedNode<T>* previous, DoublyLinkedNode<T>* next);

//  DoublyLinkedNode();

  virtual ~DoublyLinkedNode();

  DoublyLinkedNode<T>* getPrevious()const;
  DoublyLinkedNode<T>* getNext() const;
  T& getValue();

  void setPrevious(DoublyLinkedNode<T>* newPrevious);
  void setNext(DoublyLinkedNode<T>* newNext);
  void setValue (T& newValue);
 private:
  DoublyLinkedNode<T>* previous;
  DoublyLinkedNode<T>* next;
  T& value;


};


template<typename T>
DoublyLinkedNode<T>::DoublyLinkedNode(const T& value, DoublyLinkedNode<T>* previous, DoublyLinkedNode<T>* next):previous(previous),next(next), value(value){
}

//template<typename T>
//DoublyLinkedNode<T>::DoublyLinkedNode():previous(nullptr),next(nullptr), value(){
//}

template<typename T>
DoublyLinkedNode<T>* DoublyLinkedNode<T>::getNext() const{
  return next;
}
template<typename T>
DoublyLinkedNode<T>* DoublyLinkedNode<T>::getPrevious() const{
  return previous;
}

template<typename T>
T& DoublyLinkedNode<T>::getValue(){
  return value;
}

template<typename T>
void DoublyLinkedNode<T>::setNext(DoublyLinkedNode<T>* newNext){
  next = newNext;
}

template<typename T>
void DoublyLinkedNode<T>::setPrevious(DoublyLinkedNode<T>* newPrevious){
  previous = newPrevious;
}

template<typename T>
void DoublyLinkedNode<T>::setValue(T& newValue){
  value = newValue;
}


#endif //LINKEDLIST_DOUBLELINKEDNODE_H
