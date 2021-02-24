// -------------------------------------------------------------------------------
// Name:        Polymorphism
//
// Author:      Julian Gherghel
// -------------------------------------------------------------------------------
// Overload operators to implement classes for
//  (1) coordinate pairs
//  (2) arrays of co-ordinate pairs
// It is assumed exception handling is disabled (compile using -fno-exceptions or equivalent)

#include <iostream>
#include <fstream>
using namespace std;

class CoordArray;

// coordinate class
class Coord
{
  public:
    Coord(double=0.0, double = 0.0);
    Coord(const Coord&);
    Coord operator+(double) const;    // Coord + double
    Coord operator+(const Coord&) const;    // Coord + Coord
    CoordArray operator+(const CoordArray&) const;  // = Coord + CoordArray 
    friend Coord operator+(double, const Coord&);  // double + Coord
    Coord operator-(const Coord&) const;    // Coord - Coord
    Coord operator-() const;    // - Coord
    friend ostream& operator<<(ostream&, const Coord&);  // output to stream
    friend istream& operator>>(istream&, Coord&);   // input from stream
  private:
    double X;
    double Y;
};

// coordinate array class
class CoordArray
{
  public:
    CoordArray(uint32_t = 0);  // allocate memory and set Array elements to zero
    CoordArray(const CoordArray&);
    CoordArray(const Coord&);
    CoordArray operator+(const CoordArray&) const;    // Array + Array
    CoordArray operator+(double) const;    // Array + double
    friend CoordArray operator+(double, const CoordArray&);  // double + Array
    CoordArray operator-(const CoordArray&) const;    // Array - Array
    CoordArray operator-() const;
    CoordArray& operator=(const CoordArray&);    // Array = Array
    Coord& operator[](uint32_t) const;    // Array[] 
    friend ostream& operator<<(ostream&, const CoordArray&);  // output to stream
    friend istream& operator>>(istream&, CoordArray&);   // input from stream
    ~CoordArray();
  private:
    Coord* Co;  // the address of the first element in the Array
    uint32_t Length;  // the number of elements in the Array
};


// Coordinate default constructor
// Arguments: (1) x coordinate
//            (2) y coordinate
Coord::Coord(double SetX, double SetY)
{
  X = SetX;
  Y = SetY;
}

// Construct a coordinate using a coordinate 
// Arguments: (1) the coordinate to copy
Coord::Coord(const Coord& CoordExisting)
{
  X = CoordExisting.X;
  Y = CoordExisting.Y;
}

// Add two coordinates
// (x1,y1) + (x2,y2) => (x1+x2,y1+y2)
// Arguments: (1) right-hand side of addition (coordinate)
// Returns: the result of the addition (coordinate array)
Coord Coord::operator+(const Coord& CoordAdd) const
{
  Coord CoordReturn(*this);
  CoordReturn.X = CoordReturn.X + CoordAdd.X;
  CoordReturn.Y = CoordReturn.Y + CoordAdd.Y;
  return CoordReturn; 
}

// Add a coordinate and a coordinate array
// (x1,y1) + [(xa,ya),(xb,yb),...] => [(x1+xa,y1+yb),(xb,yb),...]
// Arguments: (1) right-hand side of addition (coordinate array)
// Returns: the result of the addition (coordinate array)
CoordArray Coord::operator+(const CoordArray& ArrayAdd) const
{
  CoordArray LeftCoordArray(*this);
  return LeftCoordArray + ArrayAdd; 
}

// Add a coordinate and a double 
// (x1,y1) + D => (x1+D,y1)
// Arguments: (1) right-hand side of addition (double)
// Returns: the result of the addition
Coord Coord::operator+(double DoubleAdd) const
{
  return Coord(X + DoubleAdd, Y);
}

// Add a double and a coordinate 
// D + (x1,y1) => (x1+D,y1)
// Arguments: (1) left-hand side of addition (double)
//            (2) right-hand side of addition (coordinate)
// Returns: the result of the addition
Coord operator+(double DoubleAdd, const Coord& CoordAdd)
{
  return Coord(DoubleAdd + CoordAdd.X, CoordAdd.Y);
}

// Subtract one coordinate from another
// (x1,y1) - (x2,y2) => (x1-x2,y1-y2)
// Arguments: (1) right-hand side of subtraction 
// Returns: the result of the subtraction
Coord Coord::operator-(const Coord& CoordSub) const
{
  return Coord(X - CoordSub.X, Y - CoordSub.Y);
}

// Negate one coordinate
// -(x1,y1) => (-x1,-y1)
// Arguments: none
// Returns: the result of the negation
Coord Coord::operator-() const
{
  return Coord(-X, -Y);
}

// Send a coordinate to the output stream
// Arguments: (1) output stream
//            (2) coordinate to send to the stream
// Returns: the output stream
ostream& operator<<(ostream& Output, const Coord& CoordOut)
{ 
  Output << "(" << CoordOut.X << "," << CoordOut.Y << ")";
  return Output;
}

// Read a coordinate from the input stream
// Arguments: (1) input stream
//            (2) coordinate read from the stream
// Returns: the input stream
istream& operator>>(istream& Input, Coord& CoordIn)
{ 
  Input >> CoordIn.X;
  Input >> CoordIn.Y;
  return Input;
}

// Coordinate array default constructor
// Arguments: (1) the number of elements in the array
CoordArray::CoordArray(uint32_t NewLength)
{
  Length = NewLength;
  Co = 0;
  if (Length) {
    Co = new Coord[Length];
    if (Co == 0) {
      cerr << "Unable to allocate memory\n";
    }
  }
}

// Coordinate array copy constructor
// Arguments: (1) the coordinate array to copy
CoordArray::CoordArray(const CoordArray& ArrayExisting)
{
  Length = ArrayExisting.Length;
  Co = 0;
  if (Length) {
    Co = new Coord[Length];
    if (Co == 0) {
      cerr << "Unable to allocate memory\n";
    }
  }
  for (uint32_t CountNumber = 0; CountNumber < Length; CountNumber++) {
    Co[CountNumber] = ArrayExisting[CountNumber];
  }
}

// Create a coordinate array having a single element copied from a coordinate
// Arguments: (1) the coordinate to copy
CoordArray::CoordArray(const Coord& CoordExisting)
{
  Length = 1;
  Co = new Coord[Length];
  if (Co == 0) {
    cerr << "Unable to allocate memory\n";
  }
  for (uint32_t CountNumber = 0; CountNumber < Length; CountNumber++) {
    Co[CountNumber] = CoordExisting;
  }
}
  
// Add two coordinate arrays - this concatenates the arrays
// Arguments: (1) right-hand side of addition 
// Returns: the result of the addition (concatenated coordinate array)
CoordArray CoordArray::operator+(const CoordArray& ArrayAdd) const
{
  CoordArray NewCoordArray(Length + ArrayAdd.Length);
  NewCoordArray.Length = Length + ArrayAdd.Length;

  for(uint32_t i=0; i<Length; i++) {
    NewCoordArray[i] = (*this)[i];
  }

  for(uint32_t i=0; i<ArrayAdd.Length ; i++) {
    NewCoordArray[i+Length] = ArrayAdd[i];
  }

  return NewCoordArray;
}

// Add a coordinate array and a double
// [(x1,y1),(x2,y2),...] + D => [(x1+D,y1),(x2+D,y2),...]
// Arguments: (1) right-hand side of addition (double)
// Returns: the result of the addition (coordinate array)
CoordArray CoordArray::operator+(double DoubleAdd) const
{
  CoordArray ArrayNew(*this);
  for (uint32_t CountNumber = 0; CountNumber < Length; CountNumber++) {
    ArrayNew[CountNumber] = ArrayNew[CountNumber] + DoubleAdd;
  }
  return ArrayNew;
}

// Add a double and a coordinate array
// D + [(x1,y1),(x2,y2),...] => [(x1+D,y1),(x2+D,y2),...]
// Arguments: (1) left-hand side of the addition (double)
//            (2) right-hand side of addition (coordinate array)
// Returns: the result of the addition (coordinate array)
CoordArray operator+(double DoubleAdd, const CoordArray& ArrayAdd)
{
  CoordArray ArrayNew(ArrayAdd);
  for (uint32_t CountNumber = 0; CountNumber < ArrayAdd.Length; CountNumber++) {
    ArrayNew[CountNumber] = ArrayNew[CountNumber] + DoubleAdd;
  }
  return ArrayNew;
}
  
// Subtract one coordinate array from another
// [(x1,y1),(x2,y2),...] - [(xa,ya),(xb,yb),...] 
//  => [(x1-xa,y1-ya),(x2-xb,y2-yb),...]
// Arguments: (1) the right-hand side of the subraction
// Returns: the result of the subtraction (coordinate array) 
CoordArray CoordArray::operator-(const CoordArray& ArraySub) const
{
  if (Length >= ArraySub.Length) {
    CoordArray ArrayNew(*this);
    for (uint32_t CountNumber = 0; CountNumber < ArraySub.Length; CountNumber++) {
      ArrayNew[CountNumber] = ArrayNew[CountNumber] - ArraySub[CountNumber];
    }
    return ArrayNew;
  }
  else {
    CoordArray ArrayNew(ArraySub);
    for (uint32_t CountNumber = 0; CountNumber < Length; CountNumber++) {
      ArrayNew[CountNumber] = Co[CountNumber] - ArrayNew[CountNumber]; 
    }
    return ArrayNew;
  }
}

// Negate a coordinate array
// - [(x1,y1),(x2,y2),...] => [(-x1,-y1),(-x2,-y2),...]
// Arguments: (1) the right-hand side of the negation
// Returns: the result of the subtraction (coordinate array) 
CoordArray CoordArray::operator-() const
{
  CoordArray MinusArray(*this);
  for (uint32_t CountNumber = 0; CountNumber < Length; CountNumber++) {
    MinusArray[CountNumber] = -MinusArray[CountNumber];
  }
  return MinusArray;
}

// Assign one coordinate array to another
// [(x1,y1),(x2,y2),...] = [(x1,y1),(x2,y2),...]
// Arguments: (1) the right-hand side of the assignment
// Returns: the result of the assignment (coordinate array) 
CoordArray& CoordArray::operator=(const CoordArray& ArrayAssign) 
{
  if (this != &ArrayAssign) {
    delete [] Co;

    Length = ArrayAssign.Length;
    Co = 0;
    if (Length) {
      Co = new Coord[Length];
      if (Co == 0) {
        cerr << "Unable to allocate memory\n";
      }
    }
    for (uint32_t CountNumber = 0; CountNumber < Length; CountNumber++) {
      Co[CountNumber] = ArrayAssign[CountNumber];
    }
  }
  return *this;
}

// Overload [] operator to return an element in the coordinate array
// [(x1,y1),(x2,y2),...][z] => (xz,yz)
// Arguments: (1) the right-hand side of the assignment
// Returns: the result of the array operation (coordinate) 
Coord& CoordArray::operator[](uint32_t Index) const
{
	return Co[Index];
}

// Send a coordinate array to the output stream
// Arguments: (1) output stream
//            (2) coordinate to send to the stream
// Returns: the output stream
ostream& operator<<(ostream& Output, const CoordArray& ArrayOutput)
{ 
  Output << "[";
  for (uint32_t CountNumber = 0; CountNumber < ArrayOutput.Length; CountNumber++) {
    Output << ArrayOutput[CountNumber];
  } 
  Output << "]";  
  return Output;
}

// Read a coordinate array from the input stream
// Arguments: (1) input stream
//            (2) coordinate read from the stream
// Returns: the input stream
istream& operator>>(istream& Input, CoordArray& ArrayInput)
{ 
  for (uint32_t CountNumber = 0; CountNumber < ArrayInput.Length; CountNumber++) {
    Input >> ArrayInput[CountNumber];
  } 
  return Input;
}

// Coordinate array destructor
// Release memory allocated to the array
CoordArray::~CoordArray()
{
  delete [] Co;		
}

// Perform operations on co-ordinate objects and co-ordintae array objects
int main()
{
  // create coordinates with default values of (0,0)
  Coord C3, C4, C5, C6, C7;

  // create coordinates with initial values
  Coord C1(1.0,2.0);
  Coord C2(4.5,6.7);

  // display a coordinate
  cout << "C1 is " << C1 << endl;

  // allow user to enter a coordinate
  cout << "Enter a value pair for a coordinate: ";
  cin >> C3;

  // manipulate some coordinates
  C4 = C1 + C2;    // (x1,y1) + (x2,y2) => (x1+x2,y1+y2)
  C5 = C3 - C2;    // (x1,y1) - (x2,y2) => (x1-x2,y1-y2)
  C6 = -C4 + 10.4;  // add a value to the x-coordinate
  C7 = 20.3 + C5;   // add a value to the x-coordinate

  // create coordinate arrays
  CoordArray A4, A5, A6, A7;  // create coordinate arrays with default length of 0
  CoordArray A1(3);  // 3 coordinates in the array
  CoordArray A2(C1);  // initialise first coordinate in an array of one coordinate
  CoordArray A3(A1);  // copy construct a new array

  // give a coordinate array coordinate values (no bounds check needed)
  A1[0] = C1;
  A1[1] = C2;
  A1[2] = C3;

  // display all the coordinates in an array
  cout << "A1 is " << A1 << endl;

  // allow the user to enter a coordinate array
  cout << "Enter the value of three coordinates: ";
  cin >> A3;

  // add arrays and doubles
  A6 = -A4 + 10.4;  // add a value to each of the x-coordinates in the array
  A7 = 20.3 + A5;  // add a value to each of the x-coordinates in the array 

  // concatenate coordinate arrays
  A4 = A1 + A2;  // A4 will contain the coordinates of A1 and A2

  // concatenate arrays and coordinates
  A2 = A4 + C5;  // add a coordinate to end of array 
  A3 = C2 + A4;  // add a coordinate to start of array

  cout << A4 << " + " << C5 << " is " << A2 << endl;
  cout << C2 << " + " << A4 << " is " << A3 << endl;

  A1 = A2 - A3;
  cout << A2 << " - " << A3 << " is " << A1 << endl;

  return 0;
}