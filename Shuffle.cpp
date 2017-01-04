// File holding function that shuffles the Tiles for testing
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

vector<std::string> shuffleTiles();

vector<std::string> shuffleTiles()
{
  vector<int> numTiles;
  vector<std::string> tileOrder;

  //Fill vector with number of each type of tile
  //associated with tileID by index in vector
  numTiles.push_back(1);
  numTiles.push_back(4);
  numTiles.push_back(2);
  numTiles.push_back(1);
  numTiles.push_back(8);
  numTiles.push_back(9);
  numTiles.push_back(4);
  numTiles.push_back(1);
  numTiles.push_back(4);
  numTiles.push_back(5);
  numTiles.push_back(3);
  numTiles.push_back(3);
  numTiles.push_back(5);
  numTiles.push_back(2);
  numTiles.push_back(1);
  numTiles.push_back(2);
  numTiles.push_back(1);
  numTiles.push_back(2);
  numTiles.push_back(3);
  numTiles.push_back(2);
  numTiles.push_back(1);
  numTiles.push_back(1);
  numTiles.push_back(2);
  numTiles.push_back(3);
  numTiles.push_back(2);
  numTiles.push_back(1);
  numTiles.push_back(2);
  numTiles.push_back(2);

  int numTilesRemaining = 77;

  //Tile 19 is always first tile (19-1=18)
  tileOrder.push_back("TLTJ-");
  numTiles[18] = numTiles[18] - 1;
  numTilesRemaining--;

  //Generate random numbers from 0 to 27 (28 tile types)
  //Add the random index to the tileOrder vector
  //Decrement count for that tile type
  int randomNum = 0;
  srand(time(0));
  while(numTilesRemaining > 0)
  {
    randomNum = ( rand() % 28 );
    if(numTiles[randomNum] > 0)
    {
      if(randomNum == 0)
      {
        tileOrder.push_back("JJJJ-");
      }
      if(randomNum == 1)
      {
        tileOrder.push_back("JJJJX");
      }
      if(randomNum == 2)
      {
        tileOrder.push_back("JJTJX");
      }
      if(randomNum == 3)
      {
        tileOrder.push_back("TTTT-");
      }
      if(randomNum == 4)
      {
        tileOrder.push_back("TJTJ-");
      }
      if(randomNum == 5)
      {
        tileOrder.push_back("TJJT-");
      }
      if(randomNum == 6)
      {
        tileOrder.push_back("TJTT-");
      }
      if(randomNum == 7)
      {
        tileOrder.push_back("LLLL-");
      }
      if(randomNum == 8)
      {
        tileOrder.push_back("JLLL-");
      }
      if(randomNum == 9)
      {
        tileOrder.push_back("LLJJ-");
      }
      if(randomNum == 10)
      {
        tileOrder.push_back("JLJL-");
      }
      if(randomNum == 11)
      {
        tileOrder.push_back("LJLJ-");
      }
      if(randomNum == 12)
      {
        tileOrder.push_back("LJJJ-");
      }
      if(randomNum == 13)
      {
        tileOrder.push_back("JLLJ-");
      }
      if(randomNum == 14)
      {
        tileOrder.push_back("TLJT-");
      }
      if(randomNum == 15)
      {
        tileOrder.push_back("TLJTP");
      }
      if(randomNum == 16)
      {
        tileOrder.push_back("JLTT-");
      }
      if(randomNum == 17)
      {
        tileOrder.push_back("JLTTB");
      }
      if(randomNum == 18)
      {
        tileOrder.push_back("TLTJ-");
      }
      if(randomNum == 19)
      {
        tileOrder.push_back("TLTJD");
      }
      if(randomNum == 20)
      {
        tileOrder.push_back("TLLL-");
      }
      if(randomNum == 21)
      {
        tileOrder.push_back("TLTT-");
      }
      if(randomNum == 22)
      {
        tileOrder.push_back("TLTTP");
      }
      if(randomNum == 23)
      {
        tileOrder.push_back("TLLT-");
      }
      if(randomNum == 24)
      {
        tileOrder.push_back("TLLTB");
      }
      if(randomNum == 25)
      {
        tileOrder.push_back("LJTJ-");
      }
      if(randomNum == 26)
      {
        tileOrder.push_back("LJTJD");
      }
      if(randomNum == 27)
      {
        tileOrder.push_back("TLLLC");
      }
      numTiles[randomNum] = numTiles[randomNum] - 1;
      numTilesRemaining--;
    }
  }

  return tileOrder; 
}

/*
int main()
{
  vector<std::string> tiles = shuffleTiles();
  cout << "Size is " << tiles.size() << endl;
  for(int i = 0; i < tiles.size(); i++)
  {
    cout << tiles[i] << endl;
  }
return 0;
}
*/
