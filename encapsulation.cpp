// -------------------------------------------------------------------------------
// Name:        Encapsulation
//
// Author:      Julian Gherghel
// -------------------------------------------------------------------------------
//
// Demonstrate understanding of OOP, particularly encapsulation

// Purpose
// A program to demonstrate the dividing of messages into a number of packets and 
// simulating their transmission. In this simulation, the messages are entered by 
// the user at the keyboard and packet transmission is simulated by sending
// them to the screen. 

// Background
// A packet-based communication channel requires that the messages transmitted or
// received are broken into a number of separate packets each of which may take
// a different path when transmitted between source and destination. Although the
// packets can be transmitted in any order, each packet must be indentified with
// its order in the sequence so that the message can be reassembled 
// at the destination.

// Limitation
// For the purposes of the simulation, all the characters in the messages are 
// 'printable' and do not contain white space.

#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

// For the purposes of the simulation, it is assumed that there is a limit to the 
// number of packets making up the message. A limit on the number of characters
// in each packet is normal.
#define MAX_NUMBER_OF_PACKETS 10
#define MAX_SIZE_PACKET 5

// function return values
enum {OK, NO_NEW_MESSAGE, MESSAGE_TOO_LONG};  
enum {NO_VALID_MESSAGE=1, MESSAGE_NOT_SENT}; 

// The 'Packets' object is that for a single packets to be sent. 
// Each of the 'Packets has the following member functions
//  Show - to display a packet
//  SetPacket - update the PacketNum and TotalNum
//  GetTotalNum - the number of packets for the message
//  UpDate - modify the message
// Each of the 'Packets has the following members
//  Header - the destination of the message - 1, 2 and 3 is available 
//  Data - the part of the message held in this packet (up to MAX_SIZE_PACKET)
//  PacketNum - the number of the packet in the range 1 to TotalNum
//  TotalNum - total number of packets
class Packets {
 public:
  void Show() const;
  void SetPacket(uint32_t, uint32_t);
  uint32_t GetTotalNum() const;
  void UpDate(const char *);
 private:
  char Header;  // holds destination details
  char Data[MAX_SIZE_PACKET];  // the part of the message held in this packet
  uint32_t PacketNum;  // the number of the packet in the range 1 to TotalNum
  uint32_t TotalNum;  // total number of packets
};

// The 'Transmissions' object holds the packets to be sent. 
// A 'Transmissions' object has the following member functions
//  Transmissions - a constructor function to run the menu
//  New - allow entry of a new message
//  Transmit - transmit a message to the screen
// A 'Transmissions' object has the following members
//  Packet - the packets to be sent for this message
//  ValidMessgae - flag to indicate whether the packets hold valid data 
//  MessageSent = flag to indicate whether the message has been sent
class Transmissions {
 public:
  Transmissions();
  uint8_t New();
  uint8_t Transmit();
 private:
  Packets Packet[MAX_NUMBER_OF_PACKETS];   // all of the packets
  bool ValidMessage;  // true if a message has been entered into the packets
  bool MessageSent;  // true if the message in the packets has been transmitted
};

// Display a packet
// Arguments: none
// Returns: nothing 
void Packets::Show() const
{
  cout << PacketNum << "               ";
  for (uint32_t CountChar = 0; CountChar<MAX_SIZE_PACKET; CountChar++) {
    cout << Data[CountChar];
  }
}

// Initialize a packet
// Arguments: 
//   (1) the packet number
//   (2) the total number of packets
// Returns: nothing 
void Packets::SetPacket(uint32_t _PacketNum, uint32_t _TotalNum)
{
  PacketNum = _PacketNum;
  TotalNum = _TotalNum;
}

// Return the total number of packets
// Arguments: none
// Returns: the total number of packets
uint32_t Packets::GetTotalNum() const
{
  return TotalNum;
}

// Modify the data in a packet
// Arguments: 
//   (1) the new data for the packet
// Returns: nothing 
void Packets::UpDate(const char* _Data)
{
  strncpy(Data, _Data, MAX_SIZE_PACKET);
}

// Provides a menu to allow the user to control the entering and transmission 
// of packets
// Arguments: None
// Returns: Nothing
Transmissions::Transmissions()
{
  ValidMessage = false;
  MessageSent = true;
  char UserInput;

  // loop until the user wishes to exit
  while (1) {

    // show the menu of options
    cout << endl;
    cout << "Packet Simulation Menu" << endl;
    cout << "----------------------" << endl;
    cout << "1. Enter a new message for transmission" << endl;
    cout << "2. Transmit the message" << endl;
    cout << "3. Exit from the program" << endl << endl;

    // get the user's choice
    cout << "Enter your option: ";
    cin >> UserInput;
    cout << endl;

    // act on the user's input
    switch(UserInput) {
      case '1':
        switch (New()) {
          case NO_NEW_MESSAGE:
            cout << endl << "No new message entered" << endl;
            break;
          case MESSAGE_TOO_LONG:
            cout << endl << "Message too long for packets available" << endl;
            break;
        }
        break;

      case '2':
        switch (Transmit()) {
          case NO_VALID_MESSAGE:
            cout << endl << "No valid message to transmit" << endl;
            break;
          case MESSAGE_NOT_SENT:
            cout << endl << "Message not sent" << endl;
            break;
        }
        break;

      case '3':
        return;

      default:
        cout << "Invalid entry" << endl << endl;
        break;
    }
  }
}


// Allow the user to enter a new message and so create the relevant packets. Asks
// for confirmation before allowing the user to overwrite a message not yet transmitted.
// Detects and returns with an error if the user enters an invalid header (destination)
// or if the user enters a message which is too long.
// Arguments: none
// Returns: NO_NEW_MESSAGE   message not modified
//          DESTINATION_NOT_AVAILABLE   header contains invalid destination
//          MESSAGE_TOO_LONG   message exceeds capacity of packets
//    
uint8_t Transmissions::New()
{
  // declare a string for the message
  char Message[10*MAX_NUMBER_OF_PACKETS*MAX_SIZE_PACKET];

  // warn if previous message has not been sent - confirm overwrite
  char Confirm = 'Y';
  if (!MessageSent) {
    cout << "Previous message not yet sent, enter Y to continue: ";
    cin >> Confirm;
  }

  // return with error if user does not wish to overwrite previous message
  if (! (Confirm=='Y' || Confirm=='y')) {
    return NO_NEW_MESSAGE;
  }

  // get the message from the user
  cout << endl;
  cout << "Enter new message" << endl;
  cout << "-----------------" << endl;
  cout << "Enter message: ";
  cin >> Message;

  // return with an error if the message is too long
  if (strlen(Message)>MAX_NUMBER_OF_PACKETS*MAX_SIZE_PACKET) {
	  return MESSAGE_TOO_LONG;
  }

  // find number of packets needed
  uint32_t TotalNum 
    = (uint32_t) ceil((double)strlen(Message)/(double)MAX_SIZE_PACKET);

  // for each packet initialize TotalNum and PacketNum
  for (uint32_t CountPacket = 0; CountPacket < TotalNum; CountPacket++) {
    Packet[CountPacket].SetPacket(CountPacket, TotalNum);
  }

  // split into packets
  for(uint32_t CountPacket=0;CountPacket<TotalNum;CountPacket++) {
    Packet[CountPacket].UpDate(&Message[CountPacket*MAX_SIZE_PACKET]);
  }

  // Record that the message is valid
  ValidMessage = true;

  // Record that the message has not been sent
  MessageSent = false;

  return OK;
}

// Simulate transmission by displaying the contents of the packets on the screen.
// Prevents the user sending an invalid message and asks for confirmation before
// sending again a message already transmitted.
// Arguments: None
// Returns: OK   transmission operated as intended
//          NO_VALID_MESSAGE   there is no valid message to send
//          MESSAGE_NOT_SENT   message already sent
uint8_t Transmissions::Transmit()
{
  // return with a error if the current message is not valid
  if (!ValidMessage) {
    return NO_VALID_MESSAGE;
  }

  // warn if message has already been sent - ask for confirmation
  char Confirm = 'Y';
  if (MessageSent) {
    cout << "Previous message has already been sent, enter Y to send again: ";
    cin >> Confirm;
  }

  // return with error if user does not wish to overwrite previous message
  if (! (Confirm=='Y' || Confirm=='y')) {
    return MESSAGE_NOT_SENT;
  }

  // display a title
  cout << endl;
  cout << "Packet Number   Data" << endl;

  // display message
  for (uint32_t CountPacket = 0; CountPacket < Packet[0].GetTotalNum(); 
       CountPacket++) {
    Packet[CountPacket].Show();
    cout << endl;
  }

  // Record that the message has been sent
  MessageSent = true;

  return OK;
}

// Starting point for the program
// Arguments: None
// Returns: 0 on completion
int main()
{
  Transmissions Transmission;

  return 0;
}