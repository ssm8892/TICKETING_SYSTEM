//Name: Sai, Motukuri
//NETID: SSM190012

#include "Seat.h"

//Default constructor.
Seat::Seat(){}

//The Overloaded constructor.
Seat::Seat(int row, char seat, char type){
   Row_Number = row;
   Seat_Letter = seat;
   Ticket_Type = type;
}

//Function to get the row number.
int Seat::getRow(){
   return Row_Number;
}

//Function to get the seat letter.
char Seat::getSeat(){
   return Seat_Letter;
}

//Function to get the seat status.
char Seat::getType(){
   return Ticket_Type;
}

//Function to set the row number.
void Seat::setRow(int row){
   Row_Number = row;
}

//Function to set the seat letter.
void Seat::setSeat(char seat){
   Seat_Letter = seat;
}

//Function to set the seat status.
void Seat::setType(char type){
   Ticket_Type = type;
}
