//Name: Sai, Motukuri
//NETID: SSM190012

#ifndef SEAT_H
#define SEAT_H

//Include all necessary packages and libraries.
#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <vector>
#include <unordered_map>

using namespace std;

class Seat
{
   public:
      Seat();
      Seat(int , char , char );
      int getRow();
      char getSeat();
      char getType();
      void setRow(int);
      void setSeat(char);
      void setType(char);

   private:
      int Row_Number;
      char Seat_Letter;
      char Ticket_Type;
};

#endif // SEAT_H
