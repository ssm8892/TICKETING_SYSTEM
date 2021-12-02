//Name: Sai, Motukuri
//NETID: SSM190012

#ifndef AUDITORIUM_H
#define AUDITORIUM_H

#include "Node.h"

class Auditorium
{
   public:
      Auditorium();
      Auditorium(int, string);
      Node<Seat>* getFirst();
      void setFirst(Node<Seat>*);
      void addAfter(Node<Seat>*, Node<Seat>*);
      Node<Seat>* getAbove(Node<Seat>*);
      void displayAuditorium();
      int getRows();
      int getColumns();
      char getLastSeat();
      int getTheatreNum();

   private:
      Node<Seat>* First;
      int ROWS;
      int COLUMNS;
      char lastSeat;
      int theatre_num;
};

#endif // AUDITORIUM_H
