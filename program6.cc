//Michelle Godwin
//CS3377.502
//Project #6
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "cdk.h"
#include <stdint.h>
#include <stdio.h>
#include <iomanip>

const int MATRIX_WIDTH = 3;
const int MATRIX_HEIGHT = 5;
const int BOX_WIDTH = 25;
const int MAX_REC_LEN = 25;

#define MATRIX_NAME_STRING "cs3377.bin"

using namespace std;

class BinaryRecord
{
  public:
  uint8_t strLen;
  char strBuf[MAX_REC_LEN];
};

class BinaryHeader
{
  public: 
  uint32_t magicNum;
  uint32_t version;
  uint64_t numRecs;
};

int main()
{
  //A 2D Array to hold the contents of each cell
  string cells[MATRIX_WIDTH][MATRIX_HEIGHT];
    for(int i = 0; i < MATRIX_WIDTH; i++)
      for(int j = 0; j < MATRIX_HEIGHT; j++)
	cells[i][j] = "";

  //Read the header of the file
  BinaryHeader *head = new BinaryHeader();
  ifstream in(MATRIX_NAME_STRING, ios::in | ios::binary);
  in.read((char *) head, sizeof(BinaryHeader));
  
  //Convert the results to strings
  long magicNumLong = (long)head->magicNum;
  int versionInt = (int)head->version;
  int numRecsInt = (int)head->numRecs;

  //MagicNum's string should be in hex
  stringstream convertToHex;
  string magicNumStr;
  convertToHex << setbase(16) << magicNumLong;
  convertToHex >> magicNumStr;
  
  std::string versionStr = std::to_string(versionInt);
  std::string numRecsStr = std::to_string(numRecsInt);
 
  //Set their cells in the matrix
  cells[0][0] = "Magic: 0x" + magicNumStr;
  cells[1][0] = "Version: " + versionStr;
  cells[2][0] = "NumRecords: " + numRecsStr;

  //For the first four records
  for(int i = 0; i < numRecsInt && i < 4; i++)
    {
      //Read the record
      BinaryRecord *rec = new BinaryRecord();
      in.read((char *) rec, sizeof(BinaryRecord));
      
      //Set the record to the array
      cells[1][i + 1] = rec->strBuf;
      
      //Find and set the length to the array
      int length = 0;
      for( ; cells[1][i + 1][length] != '\0'; length++);
      std::string lenStr = std::to_string(length);
      cells[0][i + 1] = "strlen: " + lenStr;
    }

  //Set matrix and its parameters
  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;

  const char *rowTitles[] = {"potato", "a", "b", "c", "d", "e"};
  const char *columnTitles[] = {"tomato", "a", "b", "c"};
  int boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  window = initscr();
  cdkscreen = initCDKScreen(window);

  initCDKColor();

  //Create the matrix and ensure that it was created
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths, boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix == NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  //Display the matric
  drawCDKMatrix(myMatrix, true);

  //Display each cell's information
  for(int i = 0; i < MATRIX_WIDTH; i++)
    for(int j = 0; j < MATRIX_HEIGHT; j++)
      setCDKMatrixCell(myMatrix, j + 1, i + 1, cells[i][j].c_str());

  drawCDKMatrix(myMatrix, true);

  //Pause until a key is pressed
  unsigned char x;
  cin >> x;

  //End the program
  endCDK();
  return 0;
}
