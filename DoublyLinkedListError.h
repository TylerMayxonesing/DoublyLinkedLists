//
// Created by mfbut on 11/24/2019.
//

#ifndef TESTDOUBLELINKEDLIST_DOUBLYLINKEDLISTERROR_H
#define TESTDOUBLELINKEDLIST_DOUBLYLINKEDLISTERROR_H
#include <string>
#include <exception>
#include "DoublyLinkedList.h"
#include "DoublyLinkedNode.h"
//#include "DoublyLinkedListEmptyError.h"
#include "ConstDoublyLinkedListIterator.h"
#include "DoublyLinkedListIterator.h"
#include "ConstReverseDoublyLinkedIterator.h"
#include "ReverseDoublyLinkedListIterator.h"

 class DoublyLinkedListError : public std::exception{

 public:
  virtual  const char* what() const noexcept override;

  protected:
  std::string errorString;
};

#endif //TESTDOUBLELINKEDLIST_DOUBLYLINKEDLISTERROR_H
