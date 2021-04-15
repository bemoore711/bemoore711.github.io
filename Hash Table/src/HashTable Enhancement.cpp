#include <algorithm>

#include <climits>

#include <iostream>

#include <string> // atoi

#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================

// Global definitions visible to all methods and classes

//============================================================================

//Declare DEFAULT_SIZE as const unsigned int and

//assign 179

const unsigned int DEFAULT_SIZE = 179;

// forward declarations

double strToDouble(string str, char ch);

// define a structure to hold bid information

struct Bid {

        string bidId; // unique identifier

        string title;

        string fund;

        double amount;

        //Implementation of Bid()

        Bid()

        {

        amount = 0.0;

        }

};

void displayBid(Bid bid);

//============================================================================

// Hash Table class definition

//============================================================================

/**

* Define a class containing data members and methods to

* implement a hash table with chaining.

*/

class HashTable {

private:

        // FIXME (1): Define structures to hold bids

        //Implementation of HashNode

        struct HashNode

        {

        //Declare bid as type of Bid

        Bid bidObject;

        //Declare key as type of unsigned

        unsigned key;

        //Declare nextPtr as type of HashNode*

        HashNode* nextPtr;

        // Implementation of default constructor

        HashNode()

        {

                        //assign UINT_MAX to key

                        key = UINT_MAX;

                        //assign nullptr to nextPtr

                        nextPtr = nullptr;

        }

        // Implementation of HashNode with parameter

        HashNode(Bid myBidObject) : HashNode()

        {

                        //assign myBidObject to bidObject

                        bidObject = myBidObject;

        }

        // Implementation of HashNode with parameters

        HashNode(Bid myBidObject, unsigned requiredKey) : HashNode(myBidObject)

        {

                        //assign requiredKey to key

                        key = requiredKey;

        }

        };

        //Declaration of nodeObject as type of

        //vector<HashNode>

        vector<HashNode> nodeObject;

        //Declared setSizeofNode as type fo unsigned

        unsigned setSizeofNode = DEFAULT_SIZE;

        //Declare hash as type of intger function

        //with parameter key

        unsigned int hash(int key);

public:

        //Declaration of Default constructor

        HashTable();

        //Declaration of destructor

        virtual ~HashTable();

        //Declaration of Insert function

        void Insert(Bid bid);

        //Declaration of PrintAll function

        void PrintAll();

        //Declaration of Remove function

        void Remove(string bidId);

        //Declaration of Search function

        Bid Search(string bidId);

};

/**

* Default constructor

*/

HashTable::HashTable()

{

        // FIXME (2): Initialize the structures used to hold bids

        //call the resize fuinction with appropriate parameter

        //setSizeofNode

        nodeObject.resize(setSizeofNode);

}

/**

* Destructor

*/

//Implementation of Destructor

HashTable::~HashTable() {

        // FIXME (3): Implement logic to free storage when class is destroyed

        //call the erase fuinction with appropriate parameter

        //nodeObject.begin()

        nodeObject.erase(nodeObject.begin());

}

/**

* Calculate the hash value of a given key.

* Note that key is specifically defined as

* unsigned int to prevent undefined results

* of a negative list index.

*

* @param key The key to hash

* @return The calculated hash

*/

unsigned int HashTable::hash(int key) {

        // FIXME (4): Implement logic to calculate a hash value

        //return the resultant value of key % setSizeofNode

        return key % setSizeofNode;

}

/**

* Insert a bid

*

* @param bid The bid to insert

*/

//Implementation of Insert function

void HashTable::Insert(Bid bid)

{

        // FIXME (5): Implement logic to insert a bid

        unsigned key = hash(atoi(bid.bidId.c_str()));

        //get the particular node for search

        HashNode* previous = &(nodeObject.at(key));

        //check previous is nullptr then

        if (previous == nullptr)

        {

        //Create an object for HashNode class

        HashNode* next = new HashNode(bid, key);

        //call insert function through nodeObject

        nodeObject.insert(nodeObject.begin() + key, (*next));

        }

        //check previous is not equal to nullptr then

        else if(previous!=nullptr)

        {

        // check previous->key is equal to

        // UINT_MAX

        if (previous->key == UINT_MAX)

        {

                        //assign key to previous->key

                        previous->key = key;

                        //assign bid to previous->bidObject

                        previous->bidObject = bid;

                        //assign nullptr to previous->nextPtr

                        previous->nextPtr = nullptr;

        }

        // check previous->key is NOT equal to

        // UINT_MAX

        else if (previous->key!= UINT_MAX)

        {

                        //Iterate the loop

                        while (previous->nextPtr != nullptr)

                        {

                                        //assign previous->nextPtr to previous

                                        previous = previous->nextPtr;

                        }

        }

        }

}

/**

* Print all bids

*/

//Implementation of printAll function

void HashTable::PrintAll() {

        // FIXME (6): Implement logic to print all bids

        unsigned int k = 0;

        //Iterate the loop

        while (k < nodeObject.size())

        {

        //call displayBid function

        displayBid(nodeObject[k].bidObject);

        //increment k by 1

        ++k;

        }

}

/**

* Remove a bid

*

* @param bidId The bid id to search for

*/

//Implementation of Remove function

void HashTable::Remove(string bidId) {

        // FIXME (7): Implement logic to remove a bid

        //Declare keytoRemove as type of unsigned

        unsigned keytoRemove = hash(atoi(bidId.c_str()));

        //call erase function with nodeObject

        nodeObject.erase(nodeObject.begin() + keytoRemove);

}

/**

* Search for the specified bidId

*

* @param bidId The bid id to search for

*/

//Implementation of Search function

Bid HashTable::Search(string bidId)

{

        //Declare bid as type of Bid

        Bid bid;

        // FIXME (8): Implement logic to search for and return a bid

        unsigned key = hash(atoi(bidId.c_str()));

        //Declare hasObject as type of HashNode*

        HashNode* hasObject = &(nodeObject.at(key));

        //check hasObject->bidObject.bidId.compare(bidId) is equal to 0

        //and hasObject->key != UINT_MAX and hasObject != nullptr

        if ( hasObject->key != UINT_MAX && hasObject != nullptr

        && hasObject->bidObject.bidId.compare(bidId) == 0)

        {

        //return hasObject->bidObject

        return hasObject->bidObject;

        }

        //check hasObject is equal to nullptr or hasObject->key

        //is equal to UINT_MAX

        if ( hasObject->key == UINT_MAX || hasObject == nullptr)

        {

        //return bidObject

        return bid;

        }

        //Iterate the loop

        while (hasObject != nullptr)

        {

        //check hasObject->bidObject.bidId.compare(bidId) is equal to 0 and

        //hasObject->key is not equal to UINT_MAX

        if ( hasObject->bidObject.bidId.compare(bidId) == 0 && hasObject->key != UINT_MAX)

        {

                        return hasObject->bidObject;

        }

        //assign hasObject->nextPtr to hasObject

        hasObject = hasObject->nextPtr;

        }

        //return bidObject

        return bid;

}

//============================================================================

// Static methods used for testing

//============================================================================

/**

* Display the bid information to the console (std::out)

*

* @param bid struct containing the bid info

*/

//Implementation of displayBid function

void displayBid(Bid bid)

{

        //Display statement

        cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "

        << bid.fund << endl;

        return;

}

/**

* Load a CSV file containing bids into a container

*

* @param csvPath the path to the CSV file to load

* @return a container holding all the bids read

*/

//Implementation of loadBids function with appropriate parameters

//csvPath and hashTable

void loadBids(string csvPath, HashTable* hashTable)

{

        //Display statement

        cout << "Loading CSV file " << csvPath << endl;

        // initialize the CSV Parser using the given path

        csv::Parser file = csv::Parser(csvPath);

        // read and display header row - optional

        vector<string> header = file.getHeader();

        //Iterate the loop

        for (auto const& c : header)

        {

        //Display statement

        cout << c << " | ";

        }

        cout << "" << endl;

        try {

        //Iterate the loop

        // loop to read rows of a CSV file

        for (unsigned int i = 0; i < file.rowCount(); i++) {

                        // Create a data structure and add to the collection of bids

                        Bid bid;

                        bid.bidId = file[i][1];

                        bid.title = file[i][0];

                        bid.fund = file[i][8];

                        bid.amount = strToDouble(file[i][4], '$');

                        //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

                        // push this bid to the end

                        hashTable->Insert(bid);

        }

        }

        //catch the exception

        catch (csv::Error &e) {

        //Display statement

        std::cerr << e.what() << std::endl;

        }

}

/**

* Simple C function to convert a string to a double

* after stripping out unwanted char

*

*

*

* @param ch The character to strip out

*/

//Implementation of strToDouble function

double strToDouble(string str, char ch) {

        str.erase(remove(str.begin(), str.end(), ch), str.end());

        return atof(str.c_str());

}

/**

* The one and only main() method

*/

//Implementation of main function

int main(int argc, char* argv[]) {

        // process command line arguments

        //csvPath,searchVal as type of string

        string csvPath, searchVal;

        switch (argc)

        {

        //check the condition is 2

        //then execute

        case 2:

                        csvPath = argv[1];

                        searchVal = "98109";

                        break;

        //check the condition is 3

        //then execute

        case 3:

                        csvPath = argv[1];

                        searchVal = argv[2];

                        break;

        //default it execute

        default:

                        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";

                        searchVal = "98109";

        }

        // Define a timer variable

        clock_t ticks;

        // Define a hash table to hold all the bids

        HashTable* bidTable;

        Bid bid;

        int choice = 0;

        //Iterate the loop

        while (choice != 9) {

        //Display statements

        cout << "Menu:" << endl;

        cout << " 1. Load Bids" << endl;

        cout << " 2. Display All Bids" << endl;

        cout << " 3. Find Bid" << endl;

        cout << " 4. Remove Bid" << endl;

        cout << " 9. Exit" << endl;

        cout << "Enter choice: ";

        cin >> choice;

        //check the condition

        switch (choice) {

        //check the condition is 1

        //then execute

        case 1:

                        bidTable = new HashTable();

                        // Initialize a timer variable before loading bids

                        ticks = clock();

                        // Complete the method call to load the bids

                        loadBids(csvPath, bidTable);

                        // Calculate elapsed time and display result

                        ticks = clock() - ticks; // current clock ticks minus starting clock ticks

                        //Display statement for ticks

                        cout << "time: " << ticks << " clock ticks" << endl;

                        //Display statement for time

                        cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

                        break;

        //check the condition is 2

        //then execute

        case 2:

                        //call bidTable->PrintAll function

                        bidTable->PrintAll();

                        break;

        //check the condition is 3

        //then execute

        case 3:

                        ticks = clock();

                        //get the resultant value of bidTable->Search(searchVal)

                        //and store in bid

                        bid = bidTable->Search(searchVal);

                        ticks = clock() - ticks; // current clock ticks minus starting clock ticks

                        //check bid.bidId.empty() or not

                        if (!bid.bidId.empty())

                        {

                                        //call displayBid function

                                        displayBid(bid);

                        }

                        else

                        {

                                        //Display statement

                                        cout << "Bid Id " << searchVal << " not found." << endl;

                        }

                        //Display statement

                        cout << "time: " << ticks << " clock ticks" << endl;

                        //Display statement

                        cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

                        break;

        //check the condition is 4

        //then execute

        case 4:

                        //call Remove function

                        bidTable->Remove(searchVal);

                        break;
	   
	  case 9:

        //Display statement

        cout << "Good bye." << endl;

        return 0;

}
