///Name: Sai, Motukuri
//NETID: SSM190012

//Include all essential files
#include "Seat.h"
#include "Node.h"
#include "Auditorium.h"

using namespace std;

//Create an Order Structure to hold the details of a single order.
struct Order
{
    Auditorium* Theatre;
    int Row;
    char sSeat;
    int NumAdults;
    int NumChildren;
    int NumSeniors;
    //Vector holds all the seats in this particular order.
    vector<Node<Seat>*>* Seats;
};

//Create an User Structure to hold the details of a single user.
struct User
{
    string Password;
    //Vector holds all the orders for this particular user.
    vector<Order*>* Orders;
};

//Initialize constant variables
unordered_map<string, User*> Users;
const double adult_price = 10.00;
const double child_price = 5.00;
const double senior_price = 7.50;

void readUserData(string);
bool checkAvailability(Auditorium*, int, char, int);
void ReserveSeats(Auditorium*, int, char, int, int, int, string);
Node<Seat>* BestAvailable(Auditorium*, int);
void viewOrders(string);
bool displayOrders(string, int &);
void addToOrder(string, int);
void ReserveNewSeats(Auditorium*, int, char, int, int, int, string, int);
void deleteFromOrder(string, int);
void unReserveSeat(Auditorium*, int, char, string, int);
void cancelOrder(string, int);
void displayReceipt(string);
void printBar();
void printReport(Auditorium, Auditorium, Auditorium);
void writeToFile(Auditorium, string);

int main()
{
    //Read in the auditorium seating charts in their linked list objects.
    Auditorium Theatre1(1,"A1.txt");
    Auditorium Theatre2(2, "A2.txt");
    Auditorium Theatre3(3, "A3.txt");

    //Read in the User data to an unordered class
    readUserData("userdb.dat");

    //Create all essential variables
    string Username, Password;
    int main_Choice, auditorium_Choice, action_Choice, admin_Choice;
    int row, aTickets, cTickets, sTickets, tTickets, altRow;
    char sSeat, altSeat;
    bool isAvailable;
    Auditorium* currTheatre;
    bool PassCheck = false;
    Node<Seat>* alt;
    bool exitFlag = false;

    //Print the login screen while the exit flag is not active.
    do
    {
        printBar();
        PassCheck = false;
        int entryCount = 0;

        //Input the Username
        cout << "LOGIN: " << endl;
        cout << endl;
        cout << "Username: " << endl;
        cin >> Username;


        //Input the Password
        cout << "Password: " << endl;
        cin >> Password;

        //Validate the password, if 3 invalid entries, reset the login page
        while(PassCheck == false && entryCount < 2)
        {
            //Loop through all the users in the unordered map to validate the password
            for(auto x : Users)
            {
                if(Username == x.first && Password == x.second->Password)
                {
                    PassCheck = true;
                    break;
                }
            }
            //If password is invalid, increase the attempt counter by 1 and re-prompt for password
            if(PassCheck == false)
            {
                entryCount++;
                cout << "Invalid password, Retry" << endl;
                cin >> Password;
            }
            else
            {
                break;
            }
        }

        //If the administrator successfully logins ...
        if(Username == "admin" && PassCheck == true)
        {
            do
            {
                printBar();
                //Print the admin menu
                cout << "ADMIN MENU: " << endl;
                cout << endl;
                cout << "1. Print Report" << endl;
                cout << "2. Logout" << endl;
                cout << "3. Exit" << endl;
                cout << endl << "Your choice: " << endl;
                cin >> admin_Choice;

                //Input the menu choice and validate it
                while(admin_Choice < 1 || admin_Choice > 3)
                {
                    //While the menu choice is not valid, re-prompt and input another choice.
                    cout << endl;
                    cout << "ADMIN MENU: " << endl;
                    cout << endl;
                    cout << "1. Print Report" << endl;
                    cout << "2. Logout" << endl;
                    cout << "3. Exit" << endl;
                    cout << endl << "Your choice: " << endl;
                    cin.clear();
                    cin.ignore(123,'\n');
                    cin >> admin_Choice;
                }

                //If admin chooses to print Report...
                if(admin_Choice == 1)
                {
                    //Call the print report function
                    printReport(Theatre1, Theatre2, Theatre3);
                }
                else if (admin_Choice == 2)
                {
                    //If the admin wants to log out, break out of the menu loop and return to the log in screen
                    break;
                }
                else if (admin_Choice == 3)
                {
                    //If the admin wants to exit, call the write to file functions for the three theaters' output files.
                    writeToFile(Theatre1, "A1Final.txt");
                    writeToFile(Theatre2, "A2Final.txt");
                    writeToFile(Theatre3, "A3Final.txt");
                    //And exit the loop.
                    exitFlag = true;
                    break;
                }
            }//Do all of the above while the user chooses not to log out or exit.
            while(admin_Choice != 2 && admin_Choice != 3);

        } //If a user successfully logs in
        else if(PassCheck == true)
        {
            do
            {
                printBar();

                //Print the main menu and prompt for an input choice
                cout << "MAIN MENU: " << endl;
                cout << endl;
                cout << "1. Reserve Seats" << endl;
                cout << "2. View Orders" << endl;
                cout << "3. Update Order" << endl;
                cout << "4. Display Receipt" << endl;
                cout << "5. Log Out" << endl;

                cout << endl << "Your choice: " <<endl;
                cin >> main_Choice;

                //Validate the input choice and re-prompt is invalid.
                while(main_Choice < 1 || main_Choice > 5)
                {

                    cout << endl;
                    cout << "MAIN MENU: " << endl;
                    cout << endl;
                    cout << "1. Reserve Seats" << endl;
                    cout << "2. View Orders" << endl;
                    cout << "3. Update Order" << endl;
                    cout << "4. Display Receipt" << endl;
                    cout << "5. Log Out" << endl;

                    cout << endl << "Your choice: " << endl;
                    cin.clear();
                    cin.ignore(123,'\n');
                    cin >> main_Choice;
                }

                //If the user chooses to reserve seats ...
                if(main_Choice == 1)
                {
                    printBar();
                    //Print the list of auditoriums and let the use choose.
                    cout << "SELECT AUDITORIUM: " << endl;
                    cout << endl;
                    cout << "1. Auditorium 1" << endl;
                    cout << "2. Auditorium 2" << endl;
                    cout << "3. Auditorium 3" << endl;

                    cout << endl << "Your choice: " << endl;
                    cin >> auditorium_Choice;

                    //Input the user's choice and validate the input.
                    while(auditorium_Choice < 1 || auditorium_Choice > 3)
                    {
                        cout << endl;
                        cout << "SELECT AUDITORIUM: " << endl;
                        cout << endl;
                        cout << "1. Auditorium 1" << endl;
                        cout << "2. Auditorium 2" << endl;
                        cout << "3. Auditorium 3" << endl;

                        //While the input is invalid, re-prompt for another choice.
                        cout << endl << "Your choice: " << endl;
                        cin.clear();
                        cin.ignore(123,'\n');
                        cin >> auditorium_Choice;
                        cout << "AUDITORIUM_CHOICE: " << auditorium_Choice << endl;
                    }

                    //Assign the correct auditorium to the curr_Theatre variable which keeps track of the current auditorium.
                    if(auditorium_Choice == 1)
                    {
                        currTheatre = &Theatre1;
                    }
                    else if(auditorium_Choice == 2)
                    {
                        currTheatre = &Theatre2;
                    }
                    else if(auditorium_Choice == 3)
                    {
                        currTheatre = &Theatre3;
                    }

                    printBar();
                    //Print out the reservation menu and a preview of the auditorium seating chart.
                    cout << "RESERVATION: " << endl;
                    currTheatre->displayAuditorium();
                    cout << endl;
                    int rows = currTheatre->getRows();
                    int columns = currTheatre->getColumns();

                    //Prompt the user for all of the information regarding the seats and validate each and every input.
                    //Prompt and validation for row number
                    cout << "Please enter the Row:  " << endl;
                    while(!(cin >> row) || row < 1 || row > rows)
                    {
                        cout << "ERROR: A valid number must be entered: " << endl;
                        cin.clear();
                        cin.ignore(123, '\n');
                    }

                    //Prompt and validation for seat letter
                    cout << "Please enter the Starting Seat Letter: " << endl;
                    while(!(cin >> sSeat) || toupper(sSeat) < 'A' || toupper(sSeat) > currTheatre->getLastSeat())
                    {
                        cout << "ERROR: A valid letter must be entered: " << endl;
                        cin.clear();
                        cin.ignore(123, '\n');
                    }

                    //Prompt and validation for number of adult tickets.
                    cout << "Please enter No. of Adult Tickets: "<< endl;
                    while(!(cin >> aTickets) || aTickets > columns || aTickets < 0)
                    {
                        cout << "ERROR: A valid number must be entered: " << endl;
                        cin.clear();
                        cin.ignore(123, '\n');
                    }

                    //Prompt and validation for number of child tickets.
                    cout << "Please enter No. of Child Tickets: " << endl;
                    while(!(cin>> cTickets) || cTickets > columns || cTickets < 0)
                    {
                        cout << "ERROR: A valid number must be entered: " << endl;
                        cin.clear();
                        cin.ignore(123, '\n');
                    }

                    //Prompt and validation for number of senior tickets.
                    cout << "Please enter No. of Senior Tickets: "<< endl;
                    while(!(cin >> sTickets) || sTickets > columns || sTickets < 0)
                    {
                        cout << "ERROR: A valid number must be entered: " << endl;
                        cin.clear();
                        cin.ignore(123, '\n');
                    }

                    //Calculate the total number of tickets being requested.
                    tTickets = aTickets + cTickets + sTickets;

                    //Get the upper case value of the seat so the other functions process the input properly.
                    sSeat = (char) toupper(sSeat);
                    //Check if the requested seats are available using the checkAvailability function.
                    isAvailable = checkAvailability(currTheatre, row, sSeat, tTickets);

                    //If the seats are available
                    if(isAvailable)
                    {
                        //Reserve the seats and update the seating the chart
                        ReserveSeats(currTheatre, row, sSeat, aTickets, cTickets, sTickets, Username);
                        //Display the new seats to the user.
                        cout << endl;
                        cout << "UPDATED SEATS" << endl;
                        currTheatre->displayAuditorium();
                    }
                    else
                    {
                        //If the seats are not available ...
                        cout << endl;
                        //Find the best available alternative seats in this auditorium
                        alt = BestAvailable(currTheatre, tTickets);
                        if(alt == nullptr) //If there are no alternative seats //
                        {
                            //Inform the user that there are no alternatives and return to the main menu.
                            cout << "no seats available" << endl;
                        }
                        else  //If there are a set of alternative seats ...
                        {

                            //Get the row and seat letter for the starting seat of the selection.
                            altRow = alt->getPayLoad().getRow();
                            altSeat = alt->getPayLoad().getSeat();

                            //Let the user know that we could not find the selected seats and provide them with the alternative set of seats.
                            cout << "We could not reserve the seats you requested but here are our alternatives: ";

                            //Print out the set of alternative seats for the user to see.
                            if(tTickets>1)
                            {
                                cout << altRow << altSeat << " - " << altRow << (char)(altSeat+tTickets-1) << endl;
                            }
                            else
                            {
                                cout << altRow << altSeat << endl;
                            }

                            cout << endl;

                            //Prompt the user to choose to accept these seats or not.
                            cout << "Please enter 'Y' to book the alternative seats, or 'N' to the end the program: " << endl;
                            char temp;
                            cin >> temp;
                            //Validate the user input for the prompt above.


                            while(!(temp == 'Y' || temp =='N' || temp == 'y' || temp == 'n'))
                            {
                                cout << "ERROR: A valid letter must be entered: " << endl;
                                //cin.clear();
                                //cin.ignore(123, '\n');
                                cin >> temp;
                                cout << "TEMP: " << temp << endl;
                            }



                            //if the user chooses to accept the alternatives, reserve the alternatives and display the theater with the new reserves seats ...
                            if (toupper(temp) == 'Y')
                            {
                                ReserveSeats(currTheatre, altRow, altSeat, aTickets, cTickets, sTickets, Username);
                                cout << endl ;
                                cout << "UPDATED SEATS: " << endl;
                                currTheatre->displayAuditorium();
                            }
                            //Else, just return to the main menu.
                        }
                    }
                }
                else if(main_Choice == 2)
                {
                    //If the user chooses to view his or her orders ...
                    printBar();
                    //Call the viewOrders function.
                    viewOrders(Username);
                }
                else if(main_Choice == 3)
                {
                    //If the user chooses to update his or her orders ...
                    printBar();
                    int orderIndex;
                    //Check if the user has any orders, and display them.
                    bool orderCheck = displayOrders(Username, orderIndex);
                    //Display orders function also get the right order number form the user.

                    //If the user has at least one order ...
                    if(orderCheck)
                    {
                        //Print the update orders menu ...
                        printBar();
                        cout << "UPDATE ORDER MENU: " << endl;
                        cout << endl;
                        cout << "1. Add tickets to order" << endl;
                        cout << "2. Delete tickets from order" << endl;
                        cout << "3. Cancel Order" << endl;

                        cout << endl << "Your Choice: ";
                        cin >> action_Choice;

                        //Get the user's input choice for this menu and validate it.
                        while(action_Choice < 1 || action_Choice > 3)
                        {

                            cout << endl;
                            cout << "UPDATE ORDER MENU: " << endl;
                            cout << endl;
                            cout << "1. Add tickets to order" << endl;
                            cout << "2. Delete tickets from order" << endl;
                            cout << "3. Cancel Order" << endl;

                            //If the input is invalid, re-prompt and input a new choice.
                            cout << endl << "Your Choice: ";
                            cin.clear();
                            cin.ignore(123,'\n');
                            cin >> action_Choice;
                        }

                        if(action_Choice == 1)
                        {

                            //If the user chooses to add new tickets to the order...
                            printBar();
                            //Call the addToOrder function.
                            addToOrder(Username, orderIndex);

                        }
                        else if (action_Choice == 2)
                        {

                            //If the user chooses to delete a ticket from the order...
                            printBar();
                            //Call the deleteFromOrder function.
                            deleteFromOrder(Username, orderIndex);

                        }
                        else if (action_Choice == 3)
                        {
                            //If the user chooses to cancel the order...
                            printBar();
                            //Call the cancelOrder function.
                            cancelOrder(Username, orderIndex);
                        }
                    }
                    else
                    {
                        //If the user does not have any orders..
                        //Print out the appropriate message.
                        cout <<"No orders" << endl;
                    }

                }
                else if(main_Choice == 4)
                {
                    //If the user chooses to view the receipt for his or her orders ...
                    printBar();
                    //Call the displayReceipt function for this user.
                    displayReceipt(Username);
                }
                else if(main_Choice == 5)
                {
                    //If the user chooses to log off...
                    //Break out of this loop to return to the login page.
                    break;
                }
            }//Do all of the above while the user chooses not to log off.
            while(main_Choice != 5);
        }
    }//Do all of the above while the exit Flag is not active.
    while(!exitFlag);
    printBar();
    return 0;
}

void readUserData(string filename)
{
    //Create an input file stream with the given filename.
    ifstream inFile;
    inFile.open(filename);

    string Username, Password;

    //While you don't reach the end of the file.
    while(!inFile.eof())
    {
        //Get one user name and one password from the file and input them into the right variable.
        getline(inFile, Username, ' ');
        getline(inFile, Password);
        //Create a temporary user object with the given user name and password.
        User* temp = new User;
        temp->Password = Password;
        //Create a temporary vector of orders for this user, initially empty.
        vector<Order*>* orders = new vector<Order*>(0);
        temp->Orders = orders;
        //Enter the user into the unordered map.
        Users[Username] = temp;
    }
    //Close the input file stream.
    inFile.close();
}

bool checkAvailability(Auditorium* Theatre, int row, char sSeat, int tTickets)
{
    Node<Seat>* curr;
    //Assign the first seat to 'curr' so you can start processing the list from the start.
    curr = Theatre->getFirst();

    //While a seat exists at the node.
    while(curr != nullptr)
    {
        //Access the row and seat letter of the current node being processed.
        int curr_row = curr->getPayLoad().getRow();
        char curr_seat = curr->getPayLoad().getSeat();
        //If the row and seat letter match the starting seat of the selection we are searching for ...
        if(row == curr_row && sSeat == curr_seat)
        {
            //Initialize a counter that starts at 0.
            int i = 0;
            //From 0 to the total number of seats requested.
            while(i < tTickets)
            {
                //Access row and seat letter of the current node being processed.
                curr_row = curr->getPayLoad().getRow();
                curr_seat = curr->getPayLoad().getSeat();
                //Status is the type of seat existing at the current node.
                char status = curr->getPayLoad().getType();
                //If the seat is not empty ...
                if(status != '.')
                {
                    //Return false immediately.
                    return false;
                }
                else     //If the seat is empty ...
                {
                    //Move to the next node and continue the loop.
                    curr = curr->getRight();
                    //Increase the counter by 1 as you are moving to the next node.
                    i++;
                }
            }
            //If you reach the end of the loop, that means the selected seat range is empty and available.
            //So return true.
            return true;
        }
        //Move to the next node after processing this seat.
        curr = curr->getRight();
    }
    //If you cant finish the loop, return false.
    return false;
}

void ReserveSeats(Auditorium* Theatre, int row, char sSeat, int aTicket, int cTicket, int sTicket, string User)
{
    //Create a node pointer to keep track of the current node being processed.
    Node<Seat>* curr;
    //Assign the first seat to 'curr' so you can start processing the list from the start.
    curr = Theatre->getFirst();
    int curr_row;
    char curr_seat;

    vector<Node<Seat>*>* seats = new vector<Node<Seat>*>();
    //While a seat exists in the current node ...
    while(curr != nullptr)
    {
        //Access the row and seat letter of the current node being processed.
        curr_row = curr->getPayLoad().getRow();
        curr_seat = curr->getPayLoad().getSeat();

        //When you find the start of the seat selection in the theater.
        if(row == curr_row && sSeat == curr_seat)
        {
            for(int i = 0; i < aTicket; i++)
            {
                //Reserve the adult tickets first.
                Seat temp(curr->getPayLoad().getRow(), curr->getPayLoad().getSeat(), 'A');
                curr->setPayLoad(temp);
                seats->push_back(curr);
                curr = curr->getRight();
            }
            for(int i = 0; i < cTicket; i++)
            {
                //Reserve the child tickets after.
                Seat temp(curr->getPayLoad().getRow(), curr->getPayLoad().getSeat(), 'C');
                curr->setPayLoad(temp);
                seats->push_back(curr);
                curr = curr->getRight();
            }
            for(int i = 0; i < sTicket; i++)
            {
                //Reserve the senior tickets last.
                Seat temp(curr->getPayLoad().getRow(), curr->getPayLoad().getSeat(), 'S');
                curr->setPayLoad(temp);
                seats->push_back(curr);
                curr = curr->getRight();
            }
        }
        else     //If the current seat is not the starting seat of the selection ...
        {
            //Then move on to the next node.
            curr = curr->getRight();
        }
    }
    //Loop through all of the users in the unordered map.
    for( auto x : Users)
    {
        //when you find the user that is currently logged in.
        if(User == x.first)
        {
            //Create an order object with all the details of the current order being reserved.
            Order* tempOrder = new Order;
            tempOrder->Theatre = Theatre;
            tempOrder->Row = row;
            tempOrder->sSeat = sSeat;
            tempOrder->NumAdults = aTicket;
            tempOrder->NumChildren = cTicket;
            tempOrder->NumSeniors = sTicket;
            tempOrder->Seats = seats;
            //Insert the order into the orders vector of this user.
            x.second->Orders->push_back(tempOrder);
        }
    }
}

Node<Seat>* BestAvailable(Auditorium* theatre, int tTicket)
{
    //Initialize the alternate node pointer and pick the highest possible distance you could possibly have between two seats in the theater.
    Node<Seat>* alt = nullptr;
    double distance = 100.000000;

    //Access the total number of columns and rows in the theater.
    int numCols = theatre->getColumns();
    int numRows = theatre->getRows();

    //Create a boolean variable to keep track of the availability of the current seat selection
    bool isAvailable = false;

    //Access the first node of the theater.
    Node<Seat>* head = theatre->getFirst();
    //Create a node pointer to keep track of the current node.
    Node<Seat>* curr;

    //Find the middle row and middle column.
    double midRow = (numRows+1)/2.0;
    double midCol = (numCols+1)/2.0;

    //Loop from the first to last row.
    for(int i = 0; i < numRows; i++)
    {
        //Start from the head node.
        curr = head;
        //Loop from the head node to the last possible start point for the seat selection in a row.
        for(int j = 0; j < (numCols-tTicket+1); j++)
        {
            //Get the row and column of the current node.
            int row = curr->getPayLoad().getRow();
            char col = curr->getPayLoad().getSeat();

            //Check if the current seat selection is available to be reserved.
            isAvailable = checkAvailability(theatre, row, col, tTicket);

            //If the seats are available ...
            if(isAvailable)
            {
                //Find the middle of the seat selection.
                double middle = (double)(j+1+j+tTicket)/2.0;

                //Find the vertical distance from the current row to the middle row.
                double vertDist = abs(row-midRow);
                //Find the horizontal distance from the middle of the selection to the middle column.
                double horDist = abs(middle- midCol);

                //Find the diagonal distance from the middle of the selected seats to the middle of the theater.
                double tempDist = sqrt((vertDist*vertDist)+(horDist*horDist));

                //If the current selection's distance is lower than the previous available distance ...
                if(tempDist < distance)
                {
                    //Change the alternate seat to the start of the current seat selection.
                    alt = curr;
                    //Change the distance to the current distance.
                    distance = tempDist;
                }
                else if (tempDist == distance)    //If the current distance equals the previous distance ...
                {
                    //Calculate which of the selections is closer to the middle row and assign that seat to the alternative.
                    int altRow = alt->getPayLoad().getRow();
                    double altVertDist = abs(altRow-midRow);

                    if(vertDist < altVertDist)
                    {
                        alt = curr;
                        distance = tempDist;
                    }
                    else if (vertDist == altVertDist)    //If both selections have the same distance from the middle row, pick the one with the smaller number.
                    {
                        if(row < altRow)
                        {
                            alt = curr;
                            distance = tempDist;
                        }
                    }
                }
            }
            //Move to the next node.
            curr = curr->getRight();
        }
        //Assign the head to the start of the next row, so the inner loop starts at the beginning of the next row later.
        head = head->getDown();
    }
    //Return the best available alternative starting seat, NULL if none are available.
    return alt;
}

void viewOrders(string User)
{
    int seatCount;
    Node<Seat>* currNode;
    //Loop through all of the users in the unordered map.
    for( auto x : Users)
    {
        //When you find the user that is currently logged in.
        if(x.first == User)
        {
            //If the user has no ordered...
            if((x.second->Orders->size()) < 1)
            {
                //Print out the appropriate message.
                cout << "No orders" << endl;
            }
            else //If the user has at least one order
            {
                //Calculate the number of orders.
                size_t orders = x.second->Orders->size();
                //Loop through all of the user's orders
                for(unsigned int i = 0; i < orders; i++)
                {
                    //Print out eh auditorium number for this order
                    cout << "Auditorium " << x.second->Orders->at(i)->Theatre->getTheatreNum() << ", ";

                    //Loop from the beginning of the theater to the end
                    currNode = x.second->Orders->at(i)->Theatre->getFirst();
                    seatCount = 0;
                    while(currNode != nullptr)
                    {
                        //Find out which of seats in this order comes first based on the row and seat.
                        int row = currNode->getPayLoad().getRow();
                        char seat = currNode->getPayLoad().getSeat();

                        size_t numSeats = x.second->Orders->at(i)->Seats->size();
                        for(unsigned int j = 0; j < numSeats; j++)
                        {
                            if(row == x.second->Orders->at(i)->Seats->at(j)->getPayLoad().getRow())
                            {
                                if(seat == x.second->Orders->at(i)->Seats->at(j)->getPayLoad().getSeat())
                                {
                                    //Print out all of the seats in this order in ascending order.
                                    cout <<  x.second->Orders->at(i)->Seats->at(j)->getPayLoad().getRow();
                                    cout <<  x.second->Orders->at(i)->Seats->at(j)->getPayLoad().getSeat();

                                    //Keep track of how many seats you have processed so you don't print out a seat multiple times.
                                    if(seatCount < (int)numSeats-1)
                                    {
                                        cout << ", ";
                                    }
                                    //Increase the seat count when you output a seat value.
                                    seatCount++;
                                }
                            }

                        }
                        //Move to the next node
                        currNode = currNode->getRight();
                    }
                    cout << endl;
                    //Print out the number of adult, child, and senior seats in this order.
                    cout << x.second->Orders->at(i)->NumAdults << " adult, ";
                    cout << x.second->Orders->at(i)->NumChildren << " child, ";
                    cout << x.second->Orders->at(i)->NumSeniors << " senior" << endl;
                }
            }
        }
    }
}

bool displayOrders(string User, int &number)
{
    size_t orders;
    //Loop through all of the users
    for( auto x : Users)
    {
        //Find the current user
        if(x.first == User)
        {
            //If the user has no orders...
            if((x.second->Orders->size()) < 1)
            {
                //Return false and leave the function.
                return false;
            }

            //If the user has at least one order...
            orders = x.second->Orders->size();
            //Loop through all of the orders
            for(unsigned int i = 0; i < orders; i++)
            {

                //Print out the appropriate details.
                cout << "Order " << i+1 << ": ";
                cout << "Auditorium " << x.second->Orders->at(i)->Theatre->getTheatreNum() << ", ";
                cout << "Starting Row: " << x.second->Orders->at(i)->Row << ", ";
                cout << "Starting Seat: " << x.second->Orders->at(i)->sSeat << ", ";

                //Calculate the totals of the ticket types.
                int tTicket = x.second->Orders->at(i)->NumAdults;
                tTicket += x.second->Orders->at(i)->NumChildren;
                tTicket += x.second->Orders->at(i)->NumSeniors;
                cout << tTicket << " tickets" << endl;
            }

            cout << endl;
            //Get the order choice from the user
            cout << "Your Choice: ";
            cin >> number;
            //Input and validate the order choice from the user.
            while(number < 1 || number > (int)orders)
            {
                //While the input is invalid, re-prompt and input a new choice.
                orders = x.second->Orders->size();
                for(unsigned int i = 0; i < orders; i++)
                {

                    cout << endl;
                    cout << "Order " << i+1 << ": ";
                    cout << "Auditorium " << x.second->Orders->at(i)->Theatre->getTheatreNum() << ", ";
                    cout << "Starting Row: " << x.second->Orders->at(i)->Row << ", ";
                    cout << "Starting Seat: " << x.second->Orders->at(i)->sSeat << ", ";


                    int tTicket = x.second->Orders->at(i)->NumAdults;
                    tTicket += x.second->Orders->at(i)->NumChildren;
                    tTicket += x.second->Orders->at(i)->NumSeniors;
                    cout << tTicket << " tickets" << endl;
                }
                cout << endl;
                cout << "Your Choice: ";
                cin.clear();
                cin.ignore(123,'\n');
                cin >> number;

            }
        }
    }
    number--;
    return true;
}

void addToOrder(string Username, int orderIndex)
{
    int row, aTickets, cTickets, sTickets;
    char sSeat;
    bool isAvailable;

    //Loop through all of the users
    for(auto x : Users)
    {
        //Find the current user
        if(Username == x.first)
        {
            //Loop through all of the orders
            size_t orders = x.second->Orders->size();
            for(unsigned int i = 0; i < orders; i++)
            {
                //Find the current order
                if((int)i == orderIndex)
                {
                    int rows = x.second->Orders->at(i)->Theatre->getRows();
                    int columns = x.second->Orders->at(i)->Theatre->getColumns();

                    //Prompt and input details of the seats being added.
                    //Validate each input, re-prompt if invalid.
                    cout << "ADDING TO ORDER: " << endl;
                    x.second->Orders->at(i)->Theatre->displayAuditorium();
                    cout << endl;

                    cout << "Please enter the Row:  ";
                    while(!(cin >> row) || row < 1 || row > rows)
                    {
                        cout << "ERROR: A valid number must be entered: ";
                        cin.clear();
                        cin.ignore(123, '\n');
                    }

                    cout << "Please enter the Starting Seat Letter: ";
                    while(!(cin >> sSeat) || toupper(sSeat) < 'A' || toupper(sSeat) > x.second->Orders->at(i)->Theatre->getLastSeat())
                    {
                        cout << "ERROR: A valid letter must be entered: ";
                        cin.clear();
                        cin.ignore(123, '\n');
                    }

                    cout << "Please enter No. of Adult Tickets: ";
                    while(!(cin >> aTickets) || aTickets > columns || aTickets < 0)
                    {
                        cout << "ERROR: A valid number must be entered: ";
                        cin.clear();
                        cin.ignore(123, '\n');
                    }

                    cout << "Please enter No. of Child Tickets: ";
                    while(!(cin>> cTickets) || cTickets > columns || cTickets < 0)
                    {
                        cout << "ERROR: A valid number must be entered: ";
                        cin.clear();
                        cin.ignore(123, '\n');
                    }

                    cout << "Please enter No. of Senior Tickets: ";
                    while(!(cin >> sTickets) || sTickets > columns || sTickets < 0)
                    {
                        cout << "ERROR: A valid number must be entered: ";
                        cin.clear();
                        cin.ignore(123, '\n');
                    }

                    int tTickets = aTickets + cTickets + sTickets;

                    sSeat = (char) toupper(sSeat);
                    isAvailable = checkAvailability(x.second->Orders->at(i)->Theatre, row, sSeat, tTickets);

                    //If the seats are available, reserve them
                    if(isAvailable)
                    {
                        ReserveNewSeats(x.second->Orders->at(i)->Theatre, row, sSeat, aTickets, cTickets, sTickets, Username, orderIndex);
                        cout << endl << "UPDATED SEATS" << endl;
                        x.second->Orders->at(i)->Theatre->displayAuditorium();
                    }
                    else
                    {
                        //If they are not available, print out the appropriate message.
                        cout << endl;
                        cout << "no seats available" << endl;
                        break;
                    }
                }
            }
        }
    }
}

void ReserveNewSeats(Auditorium* Theatre, int row, char sSeat, int aTicket, int cTicket, int sTicket, string Username, int OrderIndex)
{
    //Create a node pointer to keep track of the current node being processed.
    Node<Seat>* curr;
    //Assign the first seat to 'curr' so you can start processing the list from the start.
    curr = Theatre->getFirst();
    int curr_row;
    char curr_seat;

    vector<Node<Seat>*>* seats = new vector<Node<Seat>*>();
    //While a seat exists in the current node ...
    while(curr != nullptr)
    {
        //Access the row and seat letter of the current node being processed.
        curr_row = curr->getPayLoad().getRow();
        curr_seat = curr->getPayLoad().getSeat();

        //When you find the start of the seat selection in the theater.
        if(row == curr_row && sSeat == curr_seat)
        {
            for(int i = 0; i < aTicket; i++)
            {
                //Reserve the adult tickets first.
                Seat temp(curr->getPayLoad().getRow(), curr->getPayLoad().getSeat(), 'A');
                curr->setPayLoad(temp);
                seats->push_back(curr);
                curr = curr->getRight();
            }
            for(int i = 0; i < cTicket; i++)
            {
                //Reserve the child tickets after.
                Seat temp(curr->getPayLoad().getRow(), curr->getPayLoad().getSeat(), 'C');
                curr->setPayLoad(temp);
                seats->push_back(curr);
                curr = curr->getRight();
            }
            for(int i = 0; i < sTicket; i++)
            {
                //Reserve the senior tickets last.
                Seat temp(curr->getPayLoad().getRow(), curr->getPayLoad().getSeat(), 'S');
                curr->setPayLoad(temp);
                seats->push_back(curr);
                curr = curr->getRight();
            }
        }
        else     //If the current seat is not the starting seat of the selection ...
        {
            //Then move on to the next node.
            curr = curr->getRight();
        }
    }
    //Loop through all the users
    for(auto x : Users)
    {
        //Find the current User
        if(x.first == Username)
        {
            //Loop through all of this User's orders
            size_t orders = x.second->Orders->size();
            for(unsigned int i = 0; i < orders; i++)
            {
                //Find the current order
                if((int) i == OrderIndex)
                {
                    //Add the seats to the orders and increase the ticket types by the appropriate amount.
                    x.second->Orders->at(i)->NumAdults += aTicket;
                    x.second->Orders->at(i)->NumChildren += cTicket;
                    x.second->Orders->at(i)->NumSeniors += sTicket;
                    for(unsigned int j = 0; j < seats->size(); j++)
                    {
                        x.second->Orders->at(i)->Seats->push_back(seats->at(j));
                    }
                }
            }
        }
    }
}

void deleteFromOrder(string Username, int orderIndex)
{
    int row;
    char sSeat;
    bool belongsToUser = false;
    //Loop through all of the useras
    for(auto x : Users)
    {
        //Find the right user
        if(x.first == Username)
        {
            //Loop through all of the orders
            size_t orders = x.second->Orders->size();
            for(unsigned int i = 0; i < orders; i++)
            {
                //Find the current order
                if((int) i == orderIndex)
                {
                    //Prompt and input the seat that is being deleted.
                    int rows = x.second->Orders->at(i)->Theatre->getRows();

                    cout << "Please enter the Row:  " << endl;
                    while(!(cin >> row) || row < 1 || row > rows)
                    {
                        cout << "ERROR: A valid number must be entered: ";
                        cin.clear();
                        cin.ignore(123, '\n');
                    }

                    cout << "Please enter the Starting Seat Letter: " << endl;
                    while(!(cin >> sSeat) || toupper(sSeat) < 'A' || toupper(sSeat) > x.second->Orders->at(i)->Theatre->getLastSeat())
                    {
                        cout << "ERROR: A valid letter must be entered: ";
                        cin.clear();
                        cin.ignore(123, '\n');
                    }
                    sSeat = (char)toupper(sSeat);
                    size_t numSeats = x.second->Orders->at(i)->Seats->size();
                    //Loop through all the seats in this order
                    for(unsigned int j = 0; j < numSeats; j++)
                    {
                        //Find the seat that is being deleted.
                        if(x.second->Orders->at(i)->Seats->at(j)->getPayLoad().getRow() == row)
                        {
                            if(x.second->Orders->at(i)->Seats->at(j)->getPayLoad().getSeat() == sSeat)
                            {
                                //The seat belongs to the user
                                belongsToUser = true;
                                //Decrease the appropriate ticket type by one
                                char status = x.second->Orders->at(i)->Seats->at(j)->getPayLoad().getType();
                                if(status == 'A')
                                {
                                    x.second->Orders->at(i)->NumAdults--;
                                }
                                else if (status == 'C')
                                {
                                    x.second->Orders->at(i)->NumChildren--;
                                }
                                else if (status == 'S')
                                {
                                    x.second->Orders->at(i)->NumSeniors--;
                                }
                            }
                        }
                    }

                    //If the ticket belongs to the user
                    if(belongsToUser)
                    {
                        //De allocate the seat from the order and the auditorium
                        unReserveSeat(x.second->Orders->at(i)->Theatre, row, sSeat, Username, orderIndex);
                    }
                    else
                    {
                        //Else, print out the appropriate message
                        cout << endl << "This seat does not belong to you" << endl;
                    }
                    numSeats = x.second->Orders->at(i)->Seats->size();
                    if(numSeats<1)
                    {
                        //If there are no more seats left in the order, cancel the order.
                        cancelOrder(Username, orderIndex);
                    }
                    else
                    {
                        //Else, make the next seat in the order the starting seat
                        x.second->Orders->at(i)->Row = x.second->Orders->at(i)->Seats->at(0)->getPayLoad().getRow();
                        x.second->Orders->at(i)->sSeat = x.second->Orders->at(i)->Seats->at(0)->getPayLoad().getSeat();
                    }
                }
            }
        }
    }
}

void unReserveSeat(Auditorium* Theatre, int row, char sSeat, string Username, int orderIndex)
{
    //Loop through all of the seats in this auditorium
    Node<Seat>* currNode = Theatre->getFirst();
    while(currNode)
    {
        //Find the seat you are trying to unreserve
        int currRow = currNode->getPayLoad().getRow();
        char currSeat = currNode->getPayLoad().getSeat();
        if(currRow == row && currSeat == sSeat)
        {
            //Replace the seat status with a '.'.
            Seat temp(currRow, currSeat, '.');
            currNode->setPayLoad(temp);
            break;
        }
        else
        {
            //Move to the next seat.
            currNode = currNode->getRight();
        }
    }
    //Loop through all of the users
    for(auto x : Users)
    {
        //Find the current user
        if(x.first == Username)
        {
            //Loop through all of this user's orders
            size_t orders = x.second->Orders->size();
            for(unsigned int i = 0; i < orders; i++)
            {
                //Find the current order
                if((int)i == orderIndex)
                {
                    //Loop through all of the seats in this order
                    size_t numSeats = x.second->Orders->at(i)->Seats->size();
                    for(unsigned int j = 0; j < numSeats; j++)
                    {
                        //Find the seat that is being deallocated.
                        if(x.second->Orders->at(i)->Seats->at(j)->getPayLoad().getRow() == row)
                        {
                            if(x.second->Orders->at(i)->Seats->at(j)->getPayLoad().getSeat() == sSeat)
                            {
                                //remove the seat from the list of this seats in this order on the unordered map.
                                x.second->Orders->at(i)->Seats->erase(x.second->Orders->at(i)->Seats->begin() + j);
                                numSeats--;
                            }
                        }
                    }
                }
            }
        }
    }
}

void cancelOrder(string Username, int orderIndex)
{
    //Loop through all of the users
    for(auto x : Users)
    {
        //Find the current user
        if(x.first == Username)
        {
            //Loop through all of this user's orders
            size_t orders = x.second->Orders->size();
            for(unsigned int i = 0; i < orders; i++)
            {
                //Find the current order
                if((int) i == orderIndex)
                {
                    //Find the number of seats
                    size_t numSeats = x.second->Orders->at(i)->Seats->size();
                    //If this order still has at least one seat.
                    if(numSeats > 0)
                    {
                        //Loop through all the seats
                        for(unsigned int j = 0; j < numSeats; j++)
                        {
                            //Un-Reserve each seat from the auditorium linked lisr.
                            int row = x.second->Orders->at(i)->Seats->at(j)->getPayLoad().getRow();
                            char sSeat = x.second->Orders->at(i)->Seats->at(j)->getPayLoad().getSeat();

                            unReserveSeat(x.second->Orders->at(i)->Theatre, row, sSeat, Username, orderIndex);
                            j--;
                            numSeats--;
                        }
                    }
                    //Erase the order from this user's list of orders.
                    x.second->Orders->erase(x.second->Orders->begin() + i);
                    cout << "Order " << orderIndex+1 << " canceled." << endl;
                }
            }
        }
    }
}

//This is basically a repeat of the function from project 2, so no comments.
void displayReceipt(string Username)
{
    double totalPrice = 0.0;
    int aTickets, cTickets, sTickets;
    double currPrice = 0.0;
    int seatCount = 0;
    if(seatCount) {}
    Node<Seat>* currNode;
    if(currNode) {}
    for(auto x : Users)
    {
        if(x.first == Username)
        {
            size_t numOrders = x.second->Orders->size();
            for(unsigned int i = 0; i < numOrders; i++)
            {
                aTickets = 0;
                cTickets = 0;
                sTickets = 0;
                cout << "Auditorium " << x.second->Orders->at(i)->Theatre->getTheatreNum() << ", ";
                currNode = x.second->Orders->at(i)->Theatre->getFirst();
                seatCount = 0;

                size_t numSeats = x.second->Orders->at(i)->Seats->size();
                for(unsigned int j = 0; j < numSeats; j++)
                {
                    cout <<  x.second->Orders->at(i)->Seats->at(j)->getPayLoad().getRow();
                    cout <<  x.second->Orders->at(i)->Seats->at(j)->getPayLoad().getSeat();
                    if(j < numSeats-1)
                    {
                        cout << ",";
                    }
                    char status;
                    status = x.second->Orders->at(i)->Seats->at(j)->getPayLoad().getType();
                    if(status == 'A')
                    {
                        aTickets++;
                    }
                    else if(status == 'C')
                    {
                        cTickets++;
                    }
                    else if(status == 'S')
                    {
                        sTickets++;
                    }
                }
                cout << endl;
                cout << aTickets << " adult, " << cTickets << " child, " << sTickets << " senior" << endl;
                currPrice = ((double)aTickets*adult_price)+((double)cTickets*child_price)+((double)sTickets*senior_price);
                cout << "Order Total: $" << fixed << setprecision(2) << currPrice << endl;
                cout << endl;
                totalPrice += currPrice;
            }
            cout << "Customer Total: $" << fixed << setprecision(2) << totalPrice << endl;
        }
    }
}


void printReport(Auditorium Theatre1, Auditorium Theatre2, Auditorium Theatre3)
{
    //Print out the details of each order for the user.
    printBar();
    int currOpen = 0, currRes = 0, currAdult = 0, currChild = 0, currSenior = 0;
    double currPrice = 0.0;
    int totalOpen = 0, totalRes = 0, totalAdult = 0, totalChild = 0, totalSenior = 0;
    double totalPrice = 0.0;
    char status;

    cout << "ADMIN REPORT: " << endl;
    //Auditorium 1 Report
    //This function is a huge repetition for each auditorium, not a lot of logic involved, so no comments.
    Node<Seat>* curr = Theatre1.getFirst();
    while(curr != nullptr)
    {
        status = curr->getPayLoad().getType();
        if(status == 'A')
        {
            currAdult++;
            currRes++;
        }
        else if(status == 'C')
        {
            currChild++;
            currRes++;
        }
        else if(status == 'S')
        {
            currSenior++;
            currRes++;
        }
        else
        {
            currOpen++;
        }
        curr = curr->getRight();
    }
    currPrice = ((double)currAdult*adult_price)+((double)currChild*child_price)+((double)currSenior*senior_price);
    cout << "Auditorium 1" << '\t';
    cout << currOpen << '\t';
    cout << currRes << '\t';
    cout << currAdult << '\t';
    cout << currChild << '\t';
    cout << currSenior << '\t';
    cout << "$" << fixed << setprecision(2) << currPrice << endl;
    totalOpen += currOpen;
    currOpen = 0;
    totalRes += currRes;
    currRes = 0;
    totalAdult += currAdult;
    currAdult = 0;
    totalChild += currChild;
    currChild = 0;
    totalSenior += currSenior;
    currSenior = 0;
    totalPrice += currPrice;
    currPrice = 0;

    //Auditorium 2 Report
    curr = Theatre2.getFirst();
    while(curr != nullptr)
    {
        status = curr->getPayLoad().getType();
        if(status == 'A')
        {
            currAdult++;
            currRes++;
        }
        else if(status == 'C')
        {
            currChild++;
            currRes++;
        }
        else if(status == 'S')
        {
            currSenior++;
            currRes++;
        }
        else
        {
            currOpen++;
        }
        curr = curr->getRight();
    }

    currPrice = ((double)currAdult*adult_price)+((double)currChild*child_price)+((double)currSenior*senior_price);
    cout << "Auditorium 2" << '\t';
    cout << currOpen << '\t';
    cout << currRes << '\t';
    cout << currAdult << '\t';
    cout << currChild << '\t';
    cout << currSenior << '\t';
    cout << "$" << fixed << setprecision(2) << currPrice << '\t';
    totalOpen += currOpen;
    currOpen = 0;
    totalRes += currRes;
    currRes = 0;
    totalAdult += currAdult;
    currAdult = 0;
    totalChild += currChild;
    currChild = 0;
    totalSenior += currSenior;
    currSenior = 0;
    totalPrice += currPrice;
    currPrice = 0;
    cout << endl;

    //Auditorium 3 Report
    curr = Theatre3.getFirst();
    while(curr != nullptr)
    {
        status = curr->getPayLoad().getType();
        if(status == 'A')
        {
            currAdult++;
            currRes++;
        }
        else if(status == 'C')
        {
            currChild++;
            currRes++;
        }
        else if(status == 'S')
        {
            currSenior++;
            currRes++;
        }
        else
        {
            currOpen++;
        }
        curr = curr->getRight();
    }
    currPrice = ((double)currAdult*adult_price)+((double)currChild*child_price)+((double)currSenior*senior_price);
    cout << "Auditorium 3" << '\t';
    cout << currOpen << '\t';
    cout << currRes << '\t';
    cout << currAdult << '\t';
    cout << currChild << '\t';
    cout << currSenior << '\t';
    cout << "$" << fixed << setprecision(2) << currPrice << '\t';
    totalOpen += currOpen;
    currOpen = 0;
    totalRes += currRes;
    currRes = 0;
    totalAdult += currAdult;
    currAdult = 0;
    totalChild += currChild;
    currChild = 0;
    totalSenior += currSenior;
    currSenior = 0;
    totalPrice += currPrice;
    currPrice = 0;
    cout << endl;

    //Total Report
    cout << endl;
    cout << "Total" << '\t' << '\t';
    cout << totalOpen << '\t';
    cout << totalRes << '\t';
    cout << totalAdult << '\t';
    cout << totalChild << '\t';
    cout << totalSenior << '\t';
    cout << "$" << fixed << setprecision(2) << totalPrice << endl;
}

void writeToFile(Auditorium theatre, string filename)
{
    //Initialize an output file stream.
    ofstream outFile(filename);

    //Access the total number of rows and columns in the theater.
    int ROWS = theatre.getRows();
    int COLUMNS = theatre.getColumns();
    //Create a node pointer to keep track of the current node being processed.
    Node<Seat>* curr;
    //Assign the first seat to 'curr' so you can start processing the list from the start.
    curr = theatre.getFirst();
    //Char variable to read the status of every seat.
    char status;

    //Loop from the first to last row.
    for (int i = 0; i < ROWS; i++)
    {
        //Loop from the first to last column of each row.
        for (int j = 0; j < COLUMNS; j++)
        {
            //Status is the type of seat existing at the current node.
            status = curr->getPayLoad().getType();
            //Stream the status of the seat into the output file.
            outFile << status;
            //Move on to the next seat after the seat is processed.
            curr = curr->getRight();
        }
        //Skip to the next line on the output file when you reach the end of a row.
        outFile << endl;
    }
    //Close the output file once you finish writing the matrix into the file.
    outFile.close();
}

void printBar()
{
    //Function to print a bar of hyphens to separate the different sections of the console output
    for(int i = 0; i < 90; i++)
    {
        cout << "-";
    }
    cout << endl;
}
