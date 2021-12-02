//Name: Sai, Motukuri
//NETID: SSM190012

#ifndef NODE_H
#define NODE_H

#include "Seat.h"

template <typename T>
class Node
{
   public:
      Node() {
         Up = nullptr;
         Down = nullptr;
         Left = nullptr;
         Right = nullptr;
      }
      Node(T temp) {
         Up = nullptr;
         Down = nullptr;
         Left = nullptr;
         Right = nullptr;
         Payload = temp;
      }
      Node* getUp(){
         return Up;
      }
      Node* getDown(){
         return Down;
      }
      Node* getLeft(){
         return Left;
      }
      Node* getRight(){
         return Right;
      }
      T getPayLoad(){
         return Payload;
      }
      void setUp(Node* temp){
         Up = temp;
      }
      void setDown(Node* temp){
         Down = temp;
      }
      void setLeft(Node* temp){
         Left = temp;
      }
      void setRight(Node* temp){
         Right = temp;
      }
      void setPayLoad(T temp){
         Payload = temp;
      }

   private:
      Node* Up;
      Node* Down;
      Node* Left;
      Node* Right;
      T Payload;
};

#endif // NODE_H
