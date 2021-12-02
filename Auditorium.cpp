//Name: Sai, Motukuri
//NETID: SSM190012

#include "Auditorium.h"

//The default constructor for the theater.
Auditorium::Auditorium(){}

//The overloaded constructor for the theater.
Auditorium::Auditorium(int num, string filename)
{
   //Initialize the first node.
   theatre_num = num;
   First = nullptr;
   string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

   int row = 0;
   int col = 0;

   //Create an input file stream.
   //Open the text file.
   ifstream inFile;
   inFile.open(filename);
   string line;
   //Create nodes to track current node, previous node, and the node above.
   Node<Seat>* prevNode = nullptr, *currNode = nullptr;
   Node<Seat>* aboveNode = nullptr;

   //Loop from start to the end of the  file.
   while(!inFile.eof()){
      //Loop from the first row to the last.

      while(getline(inFile,line)){

         //Calculate the size of the row, assign to the number of columns.
         size_t length = line.size();
         col = static_cast<int>(length);

         //Loop through each column of the current row.
         for(int i = 0; i<col;i++){
            //Create seat with the current column and row, along with the seat status from the text file.
            Seat s(row+1, letters.at(i), line.at(i));
            //Create a node with the seat you made.
            currNode = new Node<Seat>(s);
            //If the seat is the first of the list ...
            if (First == nullptr){
               //Assign the seat to the head pointer.
               First = currNode;
               //Move to the next node.
               prevNode = currNode;
            } else if (row > 0){ //If the node is after the first row ...
               //Connect the node to the previous node and vice versa.
               addAfter(prevNode, currNode);

               //Find the node above.
               aboveNode = getAbove(currNode);

               //Connect the node to the node above, and vice versa.
               aboveNode->setDown(currNode);
               currNode->setUp(aboveNode);

               //Move to the next node.
               prevNode = currNode;
            } else { //If the node is just another node in the first row ...
               //Connect the node to the previous node and vice versa.
               addAfter(prevNode, currNode);
               //Move to the next node.
               prevNode = currNode;
            }
         }
         //Move to the next row.
         row++;
      }
   }

   //Assign the calculated number of rows and columns to the member variables that keep track of them.
   ROWS = row;
   COLUMNS = col;

   //Close the input file.
   inFile.close();
}

//Function to get the first node of the linked list.
Node<Seat>* Auditorium::getFirst()
{
   return First;
}

//Function to set the first node of the linked list.
void Auditorium::setFirst(Node<Seat>* temp)
{
   First = temp;
}

//Function to link the a node on the left to the node on the right, and vice versa.
void Auditorium::addAfter(Node<Seat>* left, Node<Seat>* right){
   left->setRight(right);
   right->setLeft(left);
}

//Function to get the node right about the parameter node.
Node<Seat>* Auditorium::getAbove(Node<Seat>* curr)
{
   //Start at the first node in the list
   Node<Seat>* temp;
   temp = First;

   //Access the row about the current and the column of the current node.
   int row = curr->getPayLoad().getRow()-1;
   char seat = curr->getPayLoad().getSeat();

   //Find numerical values of the column with the current node.
   string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   size_t loc = letters.find(seat);
   loc++;

   //Loop from the first node to the end of the list.
   while(temp != nullptr){
      //Find the row and seat of the current node being processed.
      int temp_row = temp->getPayLoad().getRow();
      char temp_seat = temp->getPayLoad().getSeat();

      //Find the numerical value of the current column.
      size_t tempLoc = letters.find(temp_seat);
      tempLoc++;

      //If the row matched the row above parameter node and and columns matched the parameter column ...
      if(row == temp_row && loc == tempLoc){
         //return the current node, because it is the node above the parameter node.
         return temp;
      }
      //Move to the next node.
      temp = temp->getRight();
   }
   //If you cant find, the node above, return null pointer.
   return nullptr;
}

//Function to display the auditorium in the console.
void Auditorium::displayAuditorium()
{
   //Start at the first node.
   Node<Seat>* currNode;
   currNode = First;
   char status;
   string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

   //Print out the seat letters at the top of the matrix.
   cout << endl << "  ";
   for (int i = 0; i < COLUMNS; i++){
      cout << letters.at(i);
      lastSeat = letters.at(i);
   }
   cout << endl;

   //Variables to resemble free and reserved seat statuses.
   char free = '.';
   char reserved = '#';

   //Loop from the first to last row.
   for (int i = 0; i < ROWS; i++){
      //Print out the row number to the left of the all the seats.
      cout << (i+1) << " ";
      for (int j = 0; j < COLUMNS; j++){
         status = currNode->getPayLoad().getType();
         //If the seat is not free, print out '#'.
         if(status != free){
            cout << reserved;
         } else { //If it is free, then print out '.'.
            cout << free;
         }
         //Move to the next node.
         currNode = currNode->getRight();
      }
      //Move to the next line once you finish printing a row.
      cout << endl;
   }
}

//Function to get the total number of rows.
int Auditorium::getRows()
{
   return ROWS;
}

//Function to get the total number of columns.
int Auditorium::getColumns()
{
   return COLUMNS;
}

//Function to get the last seat letter in the theater.
char Auditorium::getLastSeat()
{
   return lastSeat;
}

int Auditorium::getTheatreNum()
{
   return theatre_num;
}
