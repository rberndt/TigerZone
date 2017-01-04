
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <sstream>
#include <cstdlib>
#include <algorithm>
//#include "GameEngine.cpp"
#include "TileClass.cpp"

typedef struct {

	bool top;
	bool bottom;
	bool left;
	bool right;

	int x, y;
} emptySpace;

typedef struct {
	int ClusterId;
	int ParentId;
	int IncompleteSides;
	int TileCount; //Includes tilecount + Shield value
    //Lake = 1, Jungle = 2, Trail = 3
	int MeepleCountMe;
	int MeepleCountYou;
	int type;
	bool Boar;
	bool Deer;
	bool Ox;
	int CrocCount;
} ComponentTracker;

using namespace std;

class Player{

public:
	//GameEngine * myGameEngine;
	int MeepleCountMe;
 	int MeepleCountYou;
	int ScoreMe;
	int ScoreYou;
	int TilesRemaining;
	int * myMovePtr;
	int myMove[5];
	string tileStack;
	
	vector<Tile*> randomTileStack;
	static const int BESTVALUE = 1000000;
	 Tile * _TileGrid[153][153];
    bool _TilePresent[153][153];
	 int tigerCount;
	 int crocodileCount;
	 int curScore;
	 //Tile curTile;
	 vector<emptySpace> emptyTiles;
    ComponentTracker MainList[100];
    Tile *tileStructure(int);
    Tile *parseTile(string);
	
	//myMovePtr = myMove;

	//int tempNextState;

	Player();
	~Player();

	//void startNewGame();
	//void runGame();
	void addFirstTile_p(string, int, int , int);
	vector<string> giveMyMove_p(int, string);
	void placeMove_p(string, int[], int);
	void getTileStack(vector<string>);
	void cleanUpGame();

        void updateBoard(Tile*[153][153], int, int, Tile*, int);
        //Tile* getTile(char const*);
        Tile* MiniMaxDecision(Tile*[153][153], int,  Tile*, vector<Tile*>, vector<Tile*>);
        vector<Tile*> generateMoves(Tile*[153][153], Tile*);
        int *MinMoveDecision(Tile*[153][153], int, int, int, int, vector<Tile>, Tile);
        int *MaxMoveDecision(Tile*[153][153], int, int, int, int, vector<Tile>, Tile);
        int *evaluatePosition(Tile*[153][153], int, int, int, int, Tile*);
        int tigerLocation(Tile*[153][153], int, int, int, int, Tile*);
        void tigerCheck(int[], Tile*[153][153], int, int, Tile* );
        void updateTigerCount(int);

        //void initiateTileGrid();
        void InheritValue(ComponentTracker, ComponentTracker);
        int ScoreUpdate(ComponentTracker);
        void SingleUpdate(Tile*[153][153], Tile*, Tile*, int, int, int, int *);
        //void DenUpdate(Tile[153][153], int , int , int * );
        //void DenCheck(Tile[153][153], int , int, int , int, int *);
        int DenScoreUpdate(ComponentTracker );
        int MeepleUpdateMe(ComponentTracker );
        int MeepleUpdateYou(ComponentTracker );
        void updateComponents(Tile*[153][153], int, int);
        //void gameOver();

        //void placeOPPOMove_p(string, string[], int);


        
        

};

Player::Player(){
       tigerCount = 7;
       crocodileCount =2; 
}

Player::~Player(){

}


//void Player::startNewGame();
//{
//    
//}

Tile *Player::parseTile(string tileLetters)
{
    int i = 0;
    string check = "";
    
    for(i = 0; i < 28; i++)
    {
        
        check = "";
        for(int j = 0; j < 5; j++)
        {
            check += tileStructure(i)->des.at(j);
        }
        if(tileLetters.compare(check) == 0)
        {
            //cout<<check<<endl;
            break;
        }
        
    }
    //cout<<"Tile given: "<<check<<endl;
    return tileStructure(i);
}

//Tile* Player::getTile(char const* temp2){
//	//printf("In getTile\n");
//	char a = temp2[0];
//	char b = temp2[1];
//	char c = temp2[2];
//	char d = temp2[3];
//	char e = temp2[4];
//        //printf("In getTile passed chars\n");
//	for(int i = 0; i < 28; i++){
//		//tile structure holds all the hard coded values for each tile
//		//printf("%d\n", i);
//		Tile *temp = tileStructure(i);
//		//printf("In getTile in For passed tileStructure\n");
//                Tile * ptr = &temp;
//		//vector<char> temp1 = ptr->des;
//		//printf("%d\n", i);
//		//printf("%c %c %c %c %c \n", a, b, c, d, e);
//		//printf("%c %c %c %c %c \n", temp.des.at(0), temp.des.at(1), temp.des.at(2), temp.des.at(3), temp.des.at(4));
//	        //printf("%c %c %c %c %c \n", ptr->des.at(0), ptr->des.at(1), ptr->des.at(2), ptr->des.at(3), ptr->des.at(4));
//		if(a == temp.des[0] && b == temp.des[1] && c == temp.des[2] && d == temp.des[3] && e == temp.des[4])
//		{
//		        //printf("%d\n", i);
//			return ptr;
//                }
//	}
//	printf("DID NOT FIND TILE!\n");
//}


void Player::addFirstTile_p(string tile, int x, int y, int orientation){
	//myGameEngine->addFirstTile_g(tile, x, y, orientation);
	//cout << "addFirstTile_p function sucessfully called";
    
    x = x + 77;
    y = y + 77;
    
    updateBoard(_TileGrid, x, y, parseTile(tile.c_str()), orientation);
	//printf("EmptyTiles size: %d\n", emptyTiles.size());

}

int Player::ScoreUpdate(ComponentTracker Region){
	//score calc
	int score;
	int game;
	game = 0;
	score = Region.TileCount;
	if ( Region.Boar > 0){
		if (Region.type == 1)
			game += 1;
		else
			game += Region.Boar;
	}
	if ( Region.Deer > 0)
	{
		if (Region.type == 1)
		{
			game += 1;
		}
		else
		{
			game += Region.Deer;
		}
	}
	if ( Region.Ox > 0)
	{
		if (Region.type == 1)
		{
			game += 1;
		}
		else
		{
			game += Region.Ox;
		}
	}
	game -= Region.CrocCount;
	if ( game > 0 )
	{
		score += game;
	}
	if ( Region.IncompleteSides == 0 )
	{
		score = score * 2;
	}
	return score;
}

int Player::DenScoreUpdate(ComponentTracker Region){
	int score;
	score = 8 - Region.IncompleteSides;
	return score;
}

int Player::MeepleUpdateMe(ComponentTracker Region){
	/*player.MeepleCountMe += Region.MeepleCountMe;
	player.MeepleCountYou += Region.MeepleCountYou;
	Region.MeepleCountMe = 0;
	Region.MeepleCountYou = 0;*/
	return Region.MeepleCountMe;
}

int Player::MeepleUpdateYou(ComponentTracker Region){
	/*player.MeepleCountMe += Region.MeepleCountMe;
	player.MeepleCountYou += Region.MeepleCountYou;
	Region.MeepleCountMe = 0;
	Region.MeepleCountYou = 0;*/
	return Region.MeepleCountYou;
}

// void Player::DenCheck(Tile _TileGrid[153][153], int X, int Y, int NewX, int NewY, int * values){
// 	if(_TileGrid[NewX][NewY].orientation != NULL)
// 	{
// 		if(_TileGrid[X][Y]->Den == true)
// 		{
// 			MainList[_TileGrid[X][Y]->CenterClusterid].IncompleteSides -= 1;
// 			if (MainList[_TileGrid[X][Y]->CenterClusterid].IncompleteSides == 0)
// 			{
// 				if (MainList[_TileGrid[X][Y]->CenterClusterid].MeepleCountMe == 1)
// 				{
// 					values[3] += DenScoreUpdate(MainList[_TileGrid[X][Y]->CenterClusterid]);
// 				}
// 				if (MainList[_TileGrid[X][Y]->CenterClusterid].MeepleCountYou == 1)
// 				{
// 					values[4] += DenScoreUpdate(MainList[_TileGrid[X][Y]->CenterClusterid]);
// 				}
// 				values[1] += MeepleUpdateMe(MainList[_TileGrid[X][Y]->CenterClusterid]);
// 				values[2] += MeepleUpdateYou(MainList[_TileGrid[X][Y]->CenterClusterid]);
// 			}
// 		}
// 		if(_TileGrid[NewX][NewY]->Den == true)
// 		{
// 			MainList[_TileGrid[NewX][NewY]->CenterClusterid].IncompleteSides -= 1;
// 			if (MainList[_TileGrid[NewX][NewY]->CenterClusterid].IncompleteSides == 0)
// 			{
// 				if (MainList[_TileGrid[NewX][NewY]->CenterClusterid].MeepleCountMe == 1)
// 				{
// 					values[3] += DenScoreUpdate(MainList[_TileGrid[NewX][NewY]->CenterClusterid]);
// 				}
// 				if (MainList[_TileGrid[NewX][NewY]->CenterClusterid].MeepleCountYou == 1)
// 				{
// 					values[4] += DenScoreUpdate(MainList[_TileGrid[NewX][NewY]->CenterClusterid]);
// 				}
// 				values[1] += MeepleUpdateMe(MainList[_TileGrid[NewX][NewY]->CenterClusterid]);
// 				values[2] += MeepleUpdateYou(MainList[_TileGrid[NewX][NewY]->CenterClusterid]);
// 			}
// 		}
// 	}
// }

// void Player::DenUpdate(Tile _TileGrid[153][153], int X, int Y, int * values){
// 	if (_TileGrid[X][Y]->Den == true){
// 		DenCheck(_TileGrid, X, Y, X+1, Y, values);
// 		DenCheck(_TileGrid, X, Y, X+1, Y+1, values);
// 		DenCheck(_TileGrid, X, Y, X+1, Y-1, values);
// 		DenCheck(_TileGrid, X, Y, X-1, Y, values);
// 		DenCheck(_TileGrid, X, Y, X-1, Y+1, values);
// 		DenCheck(_TileGrid, X, Y, X-1, Y-1, values);
// 		DenCheck(_TileGrid, X, Y, X, Y+1, values);
// 		DenCheck(_TileGrid, X, Y, X, Y-1, values);
// 	}
// }

 void Player::SingleUpdate(Tile * _TileGrid[153][153], Tile * CurrentTile, Tile * OldTile, int newS, int oldS, int Side, int * values){
 	int x;
 	int y;
 	bool DontAdd;
 	DontAdd = false;
 	//Catch for nonexistent tile
 	if (OldTile->orientation != NULL && CurrentTile->type.at(newS) != 4){
 		if (CurrentTile->type.at(newS) == OldTile->type.at(oldS)){
 			//Special Check for corner Jungle . Jungle
 			if ((newS % 2 == 0) && (CurrentTile->type.at(newS) == 2)){
 				switch(Side){
       			  	case 1: 
       			  		if (OldTile->type.at(5) == 1)
       			  			DontAdd = true;
       			  	break;
  					case 2:
  						if (OldTile->type.at(7) == 1)
       			  			DontAdd = true;
  					break;
         			case 3:
         				if (OldTile->type.at(1) == 1)
       			  			DontAdd = true;
         			break;
         			case 4:
         				if (OldTile->type.at(3) == 1)
       			  			DontAdd = true;
         			break;
         		}
 			}
 			x = CurrentTile->clusterid.at(newS);
 			y = OldTile->clusterid.at(oldS);
 			while (x != MainList[x].ParentId)
 			{
 			 	x = MainList[x].ParentId;		
 			 	if (x == y)
 			 	{// REQUIRE CATCH FOR scenario in which y already absorbed into x.parent
 			 		DontAdd = true;
 			 	}	 	
 			}	
 			if (DontAdd == false)
 			{
 				while (y != MainList[y].ParentId)
 			 		y = MainList[y].ParentId;			 	
 				//InheritValue(ComponentTracker Child, ComponentTracker Parent)
 				InheritValue(MainList[x], MainList[y]);
 			}
 			if ((newS % 2 == 1) && (CurrentTile->type.at(newS) != 2)) 
 			{
 				MainList[y].IncompleteSides -= 2;
 				if ( MainList[y].IncompleteSides == 0 )
 				{
 					if (MainList[y].MeepleCountMe >= MainList[y].MeepleCountYou)
 					{
 						values[3] += ScoreUpdate(MainList[y]);	
 					}
 					if (MainList[y].MeepleCountMe <= MainList[y].MeepleCountYou)
 					{
 						values[4] += ScoreUpdate(MainList[y]);
 					}
 					values[1] += MeepleUpdateMe(MainList[y]);
 					values[2] += MeepleUpdateMe(MainList[y]);
 				}
 			}
 		}
 	}
 }

//update the components
 void Player::updateComponents(Tile * _TileGrid[153][153], int X, int Y){
 	int * values;
 	values[1] = 0;
 	values[2] = 0;
 	values[3] = 0;
 	values[4] = 0;
 	Tile * CurrentTile;
 	Tile * LeftTile;
 	Tile * RightTile;
 	Tile * UpTile;
 	Tile * DownTile;

 	CurrentTile = _TileGrid[X][Y];
 /*
 	LeftTile = _TileGrid[X-1][Y];
 	RightTile = _TileGrid[X+1][Y];
 	UpTile = _TileGrid[X][Y+1];
 	DownTile = _TileGrid[X][Y-1];
 	*/
 	LeftTile = _TileGrid[X][Y-1];
 	RightTile = _TileGrid[X][Y+1];
 	UpTile = _TileGrid[X+1][Y];
 	DownTile = _TileGrid[X-1][Y];
 	//SingleUpdate(Map _TileGrid, Tile CurrentTile, Tile OldTile, int newS, int oldS);
 	SingleUpdate(_TileGrid, CurrentTile, UpTile, 0, 6, 1, values);
 	SingleUpdate(_TileGrid, CurrentTile, UpTile, 1, 5, 1, values);
 	SingleUpdate(_TileGrid, CurrentTile, UpTile, 2, 4, 1, values);

 	SingleUpdate(_TileGrid, CurrentTile, RightTile, 2, 0, 2, values);
 	SingleUpdate(_TileGrid, CurrentTile, RightTile, 3, 7, 2, values);
 	SingleUpdate(_TileGrid, CurrentTile, RightTile, 4, 6, 2, values);

 	SingleUpdate(_TileGrid, CurrentTile, DownTile, 4, 2, 3, values);
 	SingleUpdate(_TileGrid, CurrentTile, DownTile, 5, 1, 3, values);
 	SingleUpdate(_TileGrid, CurrentTile, DownTile, 6, 0, 3, values);

 	SingleUpdate(_TileGrid, CurrentTile, LeftTile, 6, 4, 4, values);
 	SingleUpdate(_TileGrid, CurrentTile, LeftTile, 7, 3, 4, values);
 	SingleUpdate(_TileGrid, CurrentTile, LeftTile, 0, 2, 4, values);

 	//DenUpdate(_TileGrid, X, Y, values);
 	//return values;
 }

/*
void Player::cleanUpGame(){
	delete myGameEngine;
}
*/
void Player::InheritValue(ComponentTracker Child, ComponentTracker Parent) 
{
	Parent.Ox += Child.Ox;
	Parent.Deer += Child.Deer;
	Parent.Boar += Child.Boar;
	Parent.CrocCount = Parent.CrocCount + Child.CrocCount;
	Parent.MeepleCountYou += Child.MeepleCountYou;
	Parent.MeepleCountMe += Child.MeepleCountMe;
	Parent.IncompleteSides += Child.IncompleteSides;
	Parent.TileCount += Child.TileCount;
	Child.ParentId = Parent.ParentId;
	//Delete Child from 'To-Check' List ```````````````WITHIN MAPCLASS``````````````````
	//Only Check parents for scoring and updates
}

vector<string> Player::giveMyMove_p(int moveNum, string tile){

        //printf("In giveMyMove\n");
        int bvalue = -BESTVALUE;
        int index = 0;
        //Tile * ptr = getTile(tile.c_str());
        Tile * myTile = new Tile;
        myTile = parseTile(tile);
        Tile * tileResult = new Tile;
	//printf("In giveMyMove ready for minimaxDecision\n");
    

    
        vector<Tile*> movelist;

        vector<string> bestmoves;
        movelist = generateMoves(_TileGrid, myTile);
    
    
        //printf("In giveMyMove made it passed init\n");
        if(movelist.size() == 0)
        {
		//we are going to do nothing

            //cout<<"Why so empty"<<endl;

		return bestmoves;
		//but we do need to know how to repond to both of these things if our opponent does this to us
        }
        //We were going to have MiniMax Decision choose an index of movelist that was best move but we couldnt even get correct tile placement
        //tileResult = MiniMaxDecision(_TileGrid, moveNum, myTile, randomTileStack, movelist);

		//but we do need to know how to repond to both of these things if our opponent does this to us
    //cout<<"number of possible moves: "<<movelist.size()<<endl;
		
        int x = movelist.at(0)->x;
        //cout << x << " is x" << endl;
    
    
        int y = movelist.at(0)->y;
        //cout << y << " is y" << endl;
    
    
        int z = movelist.at(0)->orientation;
        //cout << z << " is z" << endl;
        
//        int *value = evaluatePosition(_TileGrid, x, y, z, moveNum, myTile);
//	 	if(value[0] > bvalue) {
//	 		bvalue = value[0];
//	 		bestmoves[index] = x;
//	 		bestmoves[index+1] = y;
//	 		bestmoves[index+2] = z;
//	 		//m represents 0 for not placing anything, 1 for tiger on a feild, 2 for tiger on water, 3 for tiger on a path, and 4 for placing a croc
//	 		bestmoves[index+3] = value[1];
//	 		index = 0;
//	 	}

    
    updateBoard(_TileGrid, x, y, myTile, z);
    
    x = x - 77;
    
    y = 77 - y;

    
    //0 = not placing tiger
    bestmoves.push_back("0");
    
    ostringstream xC;
    xC << x;
    string xCoord = xC.str();
    bestmoves.push_back(xCoord);
         
    ostringstream yC;
    yC << y;
    string yCoord = yC.str();
    bestmoves.push_back(yCoord);
         
    ostringstream oC;
    oC << z;
    string oCoord = oC.str();
    bestmoves.push_back(oCoord);
    
    
    
    
    

			
			//m represents 0 for not placing anything, 1 for tiger on a feild, 2 for tiger on water, 3 for tiger on a path, and 4 for placing a croc
			
	//int* bestmovesPtr = &bestmoves[0];
	return bestmoves;
}



void Player::placeMove_p(string tile, int move[3], int i){

    Tile * temp = parseTile(tile.c_str());
    int x = move[0];
    int y = move[1];
    int z = move[2];
    
//     int m = z;
// 	if(m > 0 && m < 5)
// 		updateTigerCount(0);
// 	if(m == 5)
// 		updateCrocodileCount();
	updateBoard(_TileGrid, x, y, temp, z);
    
	//updateComponents(_TileGrid, x, y);
 

}

// void Player::placeOPPOMove_p(string tile, int * move, int i){

// //decode move string array to int* 
//     Tile * temp = getTile(tile.c_str());
//     int x = *(move);
//     int x = *(move+1);
//     int z = *(move+2);

    
// //     int m = z;
// // 	if(m > 0 && m < 5)
// // 		updateTigerCount(0);
// // 	if(m == 5)
// // 		updateCrocodileCount();
// 	updateBoard(_TileGrid, x, y, temp, z);
// 	//updateComponents(_TileGrid, x, y);
   

// }

void Player::getTileStack(vector<string> tileString){
//        printf("In getTileStack\n");
	for(int i = 0; i < tileString.size(); i++)
	{
		//take that specific string named temp
		// temp2[0] = temp1[i];
		// temp2[1] = temp1[i+1];
		// temp2[2] = temp1[i+2];
		// temp2[3] = temp1[i+3];
		// temp2[4] = temp1[i+4];
		//printf("In getTileStack in For\n");
		Tile * tempTile = parseTile(tileString.at(i));
		//printf("In getTileStack in For passed tempTile\n");
                //Tile myTile = *tempTile;
		//printf("In getTileStack in For passed myTile\n");
		randomTileStack.push_back(tempTile);//myTile);
        }
	//printf("added tile stack to randomTileStack");
	//parse tileString to tileStack
}

void Player::updateBoard(Tile * _TileGrid[153][153], int x, int y, Tile * t, int orien) {
//        printf("In updateBoard\n");
	emptySpace temp;
	//temp.top = false;
	//temp.bottom = false;
	//temp.right = false;
	//temp.left = false;
	//t->orientation = orien;
    
    
    if(orien == 90)
    {
        rotate(t->type.begin(), t->type.begin() + 2, t->type.end());
    }else if(orien == 180)
    {
        rotate(t->type.begin(), t->type.begin() + 2, t->type.end());
        rotate(t->type.begin(), t->type.begin() + 2, t->type.end());
    }else if(orien == 270)
    {
        rotate(t->type.begin(), t->type.begin() + 2, t->type.end());
        rotate(t->type.begin(), t->type.begin() + 4, t->type.end());
    }
    
    cout<<endl;
    for(int i = 0; i < t->type.size(); i++)
    {
        cout<<t->type.at(i)<<endl;
    }
	_TileGrid[x][y] = t;
	_TilePresent[x][y] = true;
	//if a newly placed value is in our emptyTiles we need to erase it
//    cout<<"Updating board"<<endl;
    
    
	if(!emptyTiles.empty())
    {
		int s = emptyTiles.size();
		for(int i = 0; i<s; i++)
        {
            
			if(emptyTiles.at(i).x == x && emptyTiles.at(i).y == y)
            {
                //cout<<"Erased element at "<<x<< ", "<<y<<endl;
				emptyTiles.erase(emptyTiles.begin() + i);
                s -= 1;
			}
		}
	}
    
    temp.top = true;
    temp.right = true;
    temp.bottom = true;
    temp.left = true;
    
    bool firstTime = emptyTiles.empty();
    if(!_TilePresent[x][y-1])
    {
        //cout<<"No top tile"<<endl;
		//if(!_TilePresent[x][y-2] && !_TilePresent[x-1][y-1] && !_TilePresent[x+1][y-1])
		//{
        temp.x = x;
        temp.y = y - 1;
		for(int j = 0; j < emptyTiles.size(); j++)
		{
			if(emptyTiles.at(j).x == temp.x && emptyTiles.at(j).y == temp.y)
			{
              emptyTiles.erase(emptyTiles.begin() + j);
			}
		}
        if(!_TilePresent[x][y-2])
        {
            temp.top = false;
        }
        if(!_TilePresent[x+1][y-1])
        {
            temp.right = false;
        }
        if(!_TilePresent[x-1][y-1])
        {
			cout << "LEFT TILE NOT PRESENT" << endl;
            temp.left = false;
        }
        emptyTiles.push_back(temp);
		//}
    }
    
    temp.top = true;
    temp.right = true;
    temp.bottom = true;
    temp.left = true;

    if(!_TilePresent[x+1][y])
    {
        //cout<<"No right tile"<<endl;
		//if(!_TilePresent[x+1][y-1] && !_TilePresent[x+1][y+1] && !_TilePresent[x+2][y])
		//{
        temp.x = x + 1;
        temp.y = y;
		for(int j = 0; j < emptyTiles.size(); j++)
		{
			if(emptyTiles.at(j).x == temp.x && emptyTiles.at(j).y == temp.y)
			{
              emptyTiles.erase(emptyTiles.begin() + j);
			}
		}
        if(!_TilePresent[x+2][y])
        {
            temp.right = false;
        }
        if(!_TilePresent[x+1][y-1])
        {
            temp.top = false;
        }
        if(!_TilePresent[x+1][y+1])
        {
            temp.bottom = false;
        }
        
        emptyTiles.push_back(temp);
		//}
    }
    temp.top = true;
    temp.right = true;
    temp.bottom = true;
    temp.left = true;

    
    if(!_TilePresent[x][y+1])
    {
        //cout<<"No bottom tile"<<endl;
		//if(!_TilePresent[x][y+2] && !_TilePresent[x-1][y+1] && !_TilePresent[x+1][y+1])
		//{
        temp.x = x;
        temp.y = y + 1;
		for(int j = 0; j < emptyTiles.size(); j++)
		{
			if(emptyTiles.at(j).x == temp.x && emptyTiles.at(j).y == temp.y)
			{
              emptyTiles.erase(emptyTiles.begin() + j);
			}
		}
        if(!_TilePresent[x][y+2])
        {
            temp.bottom = false;
        }
        if(!_TilePresent[x+1][y+1])
        {
            temp.right = false;
        }
        if(!_TilePresent[x-1][y+1])
        {
            temp.left = false;
        }
        
        emptyTiles.push_back(temp);
		//}
    }
    
    temp.top = true;
    temp.right = true;
    temp.bottom = true;
    temp.left = true;

    if(!_TilePresent[x-1][y])
    {
        //cout<<"No left tile"<<endl;
		//if(!_TilePresent[x-2][y] && !_TilePresent[x-1][y-1] && !_TilePresent[x-1][y+1])
		//{
        temp.x = x - 1;
        temp.y = y;
		for(int j = 0; j < emptyTiles.size(); j++)
		{
			if(emptyTiles.at(j).x == temp.x && emptyTiles.at(j).y == temp.y)
			{
              emptyTiles.erase(emptyTiles.begin() + j);
			}
		}
        if(!_TilePresent[x-2][y])
        {
            temp.left = false;
        }
        if(!_TilePresent[x-1][y-1])
        {
            temp.top = false;
        }
        if(!_TilePresent[x-1][y+1])
        {
            temp.bottom = false;
        }
        
        emptyTiles.push_back(temp);
		//}
    }
    
    
    
    
}

//start of minimax algorithm 
Tile *Player::MiniMaxDecision(Tile * _TileGrid[153][153], int moveNum, Tile *t, vector<Tile*> temp, vector<Tile*> movelist)
{
    Tile * tile = t;
    int bvalue = -BESTVALUE;
    int index = 0;
    int x, y, z;
    Tile *bestTile = new Tile;
	int bestmoves[4];

	//this next part evaluates the possible move and compares it with future moves
		x = movelist.at(0)->x;
		y = movelist.at(0)->y;
		z = movelist.at(0)->orientation;
		
		t->orientation = z;
		_TileGrid[x][y] = t;
		//this next move is the opponent playing with the board we created after placing a valid tile
		//int value = MinMoveDecision(_TileGrid, x, y, z, moveNum+1, temp, t);
		//usually this next part wouldnt be here, because we would be going into the min move decision...
		//but for now we will just evaluate the current valid positions here

		int *value = evaluatePosition(_TileGrid, x, y, z, moveNum, t);
//        cout<<"evaluate position is working"<<endl;
		if(value[0] > bvalue)
        {
			bvalue = value[0];
			bestmoves[index] = x;
			bestmoves[index+1] = y;
			bestmoves[index+2] = z;
			//m represents 0 for not placing anything, 1 for tiger on a feild, 2 for tiger on water, 3 for tiger on a path, and 4 for placing a croc
			bestmoves[index+3] = value[1];
			index = 0;
		}
		//since we havent chosen this location yet, I want to to go back to nothing
		//_TileGrid[x][y] = NULL;
    
//    cout<<"evaluate position is working"<<endl;
	int m = bestmoves[3];
	if(m > 0 && m < 5)
		updateTigerCount(0);
	if(m == 5)
		//updateCrocodileCount();
	updateBoard(_TileGrid, x, y, tile, z);
	updateComponents(_TileGrid, x, y);
	//update components?
	//update meeplecount?
	return bestTile;
}

//generate possible valid moves, thinking of having it stacked as x, y, z, x, y, z, ... z being the orientation

vector<Tile*> Player::generateMoves(Tile * _TileGrid[153][153], Tile *curTile)
{
//    vector<Tile> possibleConnections;
//    vector<Tile> legalMovesFinal;
//    Tile *tempTile = new Tile;
//    emptySpace *tempSpot = new emptySpace;
    
    	vector<emptySpace> temp = emptyTiles;
    
//        cout<<"the size of empty tiles in generate is " <<temp.size()<<endl;
    	emptySpace curr;
    
        Tile * tempTileHold = new Tile;
    tempTileHold = curTile;
        Tile * tempTile2 = new Tile;
    
        int x = 0;
        int y = 0;
        //int z = 0;
        bool top;
        bool bottom;
        bool left;
        bool right;
        vector<Tile*> movelist;
        //tempTile1 = curTile;
    	while(!temp.empty())
        {
//            cout<<"Generating moves"<<endl;
         
//            for(int i = 0; i < 5; i++)
//            {
//                cout<<curTile->des.at(i);
//            }
            
            
    		curr = temp.back();
    		x = curr.x;
    		y = curr.y;
    		//top = curr.top;
    		//bottom = curr.bottom;
    		//left = curr.left;
    		//right = curr.right;
			top = _TilePresent[x][y-1];
			bottom = _TilePresent[x][y+1];
			left = _TilePresent[x-1][y];
			right = _TilePresent[x+1][y];
            
            //cout<<"x of empty space is " << x<<endl;
            //cout<<"y of empty space is " << y<<endl;
            //cout<<"top is " << top<<endl;
            //cout<<"bottom is " << bottom<<endl;
            //cout<<"left is " << left<<endl;
            //cout<<"right is " << right<<endl;
    		temp.pop_back();
            //tempTile1 = curTile;
    		//tempTile1 = _TileGrid[x][y];
            
    		for(int m = 0; m<4; m++)
            {

                
                int a, b, c, d, e, f, g, h, z;
    			if(m == 0)
                {
                    
                    a = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6, h = 7;
                    z = 0;
                }
    			else if(m == 1)
                {
                    a = 2, b = 3, c = 4, d = 5, e = 6, f = 7, g = 0, h = 1;
                    z = 90;
                }
    			else if(m == 2)
                {
                    a = 4, b = 5, c = 6, d = 7, e = 0, f = 1, g = 2, h = 3;
                    z = 180;
                }
    			else if(m == 3)
                {
    				a = 6, b = 7, c = 0, d = 1, e = 2, f = 3, g = 4, h = 5;
                    z = 270;
                }
                Tile * tempTile1 = new Tile;
                tempTile1 = tempTileHold;
                if(top)
                {
                    if(right)
                    {
                        if(bottom)
                        {
                            if(left)
                            {
                                //all sides
                                tempTile2 = _TileGrid[x][y-1];
                                if(tempTile2->type.at(4) == tempTile1->type.at(c) && tempTile2->type.at(5) == tempTile1->type.at(b) && tempTile2->type.at(6) == tempTile1->type.at(a))
                                {
                                    tempTile2 = _TileGrid[x+1][y];
                                    if(tempTile2->type.at(6) == tempTile1->type.at(e) && tempTile2->type.at(7) == tempTile1->type.at(d) && tempTile2->type.at(0) == tempTile1->type.at(c))
                                    {
                                        tempTile2 = _TileGrid[x][y+1];
                                        if(tempTile2->type.at(2) == tempTile1->type.at(e) && tempTile2->type.at(1) == tempTile1->type.at(f) && tempTile2->type.at(0) == tempTile1->type.at(g))
                                        {
                                            tempTile2 = _TileGrid[x-1][y];
                                            if(tempTile2->type.at(4) == tempTile1->type.at(g) && tempTile2->type.at(3) == tempTile1->type.at(h) && tempTile2->type.at(2) == tempTile1->type.at(a))
                                            {
//                                                cout<<"bottom and right and left and top"<<endl;
//                                                cout<<"orientation is "<<z<<endl;
                                                tempTile1->x = x;
                                                tempTile1->y = y;
                                                tempTile1->orientation = z;
                                                movelist.push_back(tempTile1);
                                                
                                            }
                                        }
                                    }

                                }
                            }else
                            {
                                //no left
                                tempTile2 = _TileGrid[x][y-1];
                                if(tempTile2->type.at(4) == tempTile1->type.at(c) && tempTile2->type.at(5) == tempTile1->type.at(b) && tempTile2->type.at(6) == tempTile1->type.at(a))
                                {
                                    tempTile2 = _TileGrid[x+1][y];
                                    if(tempTile2->type.at(6) == tempTile1->type.at(e) && tempTile2->type.at(7) == tempTile1->type.at(d) && tempTile2->type.at(0) == tempTile1->type.at(c))
                                    {
                                        tempTile2 = _TileGrid[x][y+1];
                                        if(tempTile2->type.at(2) == tempTile1->type.at(e) && tempTile2->type.at(1) == tempTile1->type.at(f) && tempTile2->type.at(0) == tempTile1->type.at(g))
                                        {
//                                            cout<<"bottom and right and top"<<endl;
//                                            cout<<"orientation is "<<z<<endl;
                                            tempTile1->x = x;
                                            tempTile1->y = y;
                                            tempTile1->orientation = z;
                                            movelist.push_back(tempTile1);
                                            
                                        }
                                    }
                                }
                            }
                        }else if(left)
                        {
                            //no bottom
                            tempTile2 = _TileGrid[x][y-1];
                            if(tempTile2->type.at(4) == tempTile1->type.at(c) && tempTile2->type.at(5) == tempTile1->type.at(b) && tempTile2->type.at(6) == tempTile1->type.at(a))
                            {
                                tempTile2 = _TileGrid[x+1][y];
                                if(tempTile2->type.at(6) == tempTile1->type.at(e) && tempTile2->type.at(7) == tempTile1->type.at(d) && tempTile2->type.at(0) == tempTile1->type.at(c))
                                {
                                    tempTile2 = _TileGrid[x-1][y];
                                    if(tempTile2->type.at(4) == tempTile1->type.at(g) && tempTile2->type.at(3) == tempTile1->type.at(h) && tempTile2->type.at(2) == tempTile1->type.at(a))
                                    {
//                                        cout<<"top and right and left"<<endl;
//                                        cout<<"orientation is "<<z<<endl;
                                        tempTile1->x = x;
                                        tempTile1->y = y;
                                        tempTile1->orientation = z;
                                        movelist.push_back(tempTile1);
                                        
                                    }
                                }
                            }
                        }else
                        {
                            //right and top
                            tempTile2 = _TileGrid[x][y-1];
                            if(tempTile2->type.at(4) == tempTile1->type.at(c) && tempTile2->type.at(5) == tempTile1->type.at(b) && tempTile2->type.at(6) == tempTile1->type.at(a))
                            {
                                tempTile2 = _TileGrid[x+1][y];
                                if(tempTile2->type.at(6) == tempTile1->type.at(e) && tempTile2->type.at(7) == tempTile1->type.at(d) && tempTile2->type.at(0) == tempTile1->type.at(c))
                                {
//                                    cout<<"top and right"<<endl;
//                                    cout<<"orientation is "<<z<<endl;
                                    tempTile1->x = x;
                                    tempTile1->y = y;
                                    tempTile1->orientation = z;
                                    movelist.push_back(tempTile1);
                                    
                                }

                            }
                        }
                    }else if(bottom && left)
                    {
                        //no right
                        //FIXED
                        tempTile2 = _TileGrid[x][y-1];
                        if(tempTile2->type.at(4) == tempTile1->type.at(c) && tempTile2->type.at(5) == tempTile1->type.at(b) && tempTile2->type.at(6) == tempTile1->type.at(a))
                        {
                            tempTile2 = _TileGrid[x][y+1];
                            if(tempTile2->type.at(2) == tempTile1->type.at(e) && tempTile2->type.at(1) == tempTile1->type.at(f) && tempTile2->type.at(0) == tempTile1->type.at(g))
                            {
                                tempTile2 = _TileGrid[x-1][y];
                                if(tempTile2->type.at(4) == tempTile1->type.at(g) && tempTile2->type.at(3) == tempTile1->type.at(h) && tempTile2->type.at(2) == tempTile1->type.at(a))
                                {
//                                    cout<<"bottom and right and left"<<endl;
//                                    cout<<"orientation is "<<z<<endl;
                                    tempTile1->x = x;
                                    tempTile1->y = y;
                                    tempTile1->orientation = z;
                                    movelist.push_back(tempTile1);
                                    
                                }
                            }

                        }
                    }else if(bottom)
                    {
                        //Top and bottom
                        tempTile2 = _TileGrid[x][y-1];
                        if(tempTile2->type.at(4) == tempTile1->type.at(c) && tempTile2->type.at(5) == tempTile1->type.at(b) && tempTile2->type.at(6) == tempTile1->type.at(a))
                        {
                            tempTile2 = _TileGrid[x][y+1];
                            if(tempTile2->type.at(2) == tempTile1->type.at(e) && tempTile2->type.at(1) == tempTile1->type.at(f) && tempTile2->type.at(0) == tempTile1->type.at(g))
                            {
//                                cout<<"bottom and top"<<endl;
//                                cout<<"orientation is "<<z<<endl;
                                tempTile1->x = x;
                                tempTile1->y = y;
                                tempTile1->orientation = z;
                                movelist.push_back(tempTile1);

                            }
                        }
                    }else if(left)
                    {
						tempTile2 = _TileGrid[x][y-1];
                        if(tempTile2->type.at(4) == tempTile1->type.at(c) && tempTile2->type.at(5) == tempTile1->type.at(b) && tempTile2->type.at(6) == tempTile1->type.at(a))
                        {
                        tempTile2 = _TileGrid[x-1][y];
                        if(tempTile2->type.at(4) == tempTile1->type.at(g) && tempTile2->type.at(3) == tempTile1->type.at(h) && tempTile2->type.at(2) == tempTile1->type.at(a))
                        {
                            //                                    cout<<"bottom and right and left"<<endl;
                            //                                    cout<<"orientation is "<<z<<endl;
                            tempTile1->x = x;
                            tempTile1->y = y;
                            tempTile1->orientation = z;
                            movelist.push_back(tempTile1);
                            
                        }
						}
                    }
                    else
                    {
                        //just top
                        tempTile2 = _TileGrid[x][y-1];
                        if(tempTile2->type.at(4) == tempTile1->type.at(c) && tempTile2->type.at(5) == tempTile1->type.at(b) && tempTile2->type.at(6) == tempTile1->type.at(a))
                        {
//                            cout<<"top"<<endl;
//                            cout<<"orientation is "<<z<<endl;
                            tempTile1->x = x;
                            tempTile1->y = y;
                            tempTile1->orientation = z;
                            movelist.push_back(tempTile1);
                            
                        }
                    }
                }else if(bottom && left && right)
                {
                    //no top
//                    cout<<" only no top"<<endl;
                    tempTile2 = _TileGrid[x+1][y];
                    if(tempTile2->type.at(6) == tempTile1->type.at(e) && tempTile2->type.at(7) == tempTile1->type.at(d) && tempTile2->type.at(0) == tempTile1->type.at(c))
                    {
                        tempTile2 = _TileGrid[x][y+1];
                        if(tempTile2->type.at(2) == tempTile1->type.at(e) && tempTile2->type.at(1) == tempTile1->type.at(f) && tempTile2->type.at(0) == tempTile1->type.at(g))
                        {
                            tempTile2 = _TileGrid[x-1][y];
                            if(tempTile2->type.at(4) == tempTile1->type.at(g) && tempTile2->type.at(3) == tempTile1->type.at(h) && tempTile2->type.at(2) == tempTile1->type.at(a))
                            {
//                                cout<<"bottom and right and left"<<endl;
//                                cout<<"orientation is "<<z<<endl;
                                tempTile1->x = x;
                                tempTile1->y = y;
                                tempTile1->orientation = z;
                                movelist.push_back(tempTile1);
                                
                            }
                        }
                    }
                }else if(bottom && left)
                {
                    //bottom and left
//                    cout<<"were in 1, 1"<<endl;
                    tempTile2 = _TileGrid[x][y+1];
                    
                    if((tempTile2->type.at(2) == tempTile1->type.at(e)) && (tempTile2->type.at(1) == tempTile1->type.at(f)) && (tempTile2->type.at(0) == tempTile1->type.at(g)))
                    {
                        tempTile2 = _TileGrid[x-1][y];
                        
                        if((tempTile2->type.at(4) == tempTile1->type.at(g)) && (tempTile2->type.at(3) == tempTile1->type.at(h)) && (tempTile2->type.at(2) == tempTile1->type.at(a)))
                        {
//                          cout<<"bottom and left"<<endl;
//                            cout<<"orientation is "<<z<<endl;
                            tempTile1->x = x;
                            tempTile1->y = y;
                            tempTile1->orientation = z;
                            movelist.push_back(tempTile1);
                            
                        }
                    }
                }else if(left && right)
                {
                    //left and right
                    tempTile2 = _TileGrid[x+1][y];
                    if(tempTile2->type.at(6) == tempTile1->type.at(e) && tempTile2->type.at(7) == tempTile1->type.at(d) && tempTile2->type.at(0) == tempTile1->type.at(c))
                    {
                        tempTile2 = _TileGrid[x-1][y];
                        if(tempTile2->type.at(4) == tempTile1->type.at(g) && tempTile2->type.at(3) == tempTile1->type.at(h) && tempTile2->type.at(2) == tempTile1->type.at(a))
                        {
//                            cout<<"left and right"<<endl;
//                            cout<<"orientation is "<<z<<endl;
                            tempTile1->x = x;
                            tempTile1->y = y;
                            tempTile1->orientation = z;
                            movelist.push_back(tempTile1);
                            
                        }
                    }
                }else if(bottom && right)
                {
                    //bottom and right
                   
                    tempTile2 = _TileGrid[x][y+1];
                    
                    if((tempTile2->type.at(2) == tempTile1->type.at(e)) && (tempTile2->type.at(1) == tempTile1->type.at(f)) && (tempTile2->type.at(0) == tempTile1->type.at(g)))
                    {
                        tempTile2 = _TileGrid[x+1][y];
                        
                        
                        if((tempTile2->type.at(6) == tempTile1->type.at(e)) && (tempTile2->type.at(7) == tempTile1->type.at(d)) && (tempTile2->type.at(0) == tempTile1->type.at(c)))
                        {
//                            cout<<"bottom and right"<<endl;
//                            cout<<"orientation is "<<z<<endl;
                            tempTile1->x = x;
                            tempTile1->y = y;
                            tempTile1->orientation = z;
                            movelist.push_back(tempTile1);
                            
                        }
                    }
                }else if(left)
                {
                    tempTile2 = _TileGrid[x-1][y];
                    if(tempTile2->type.at(4) == tempTile1->type.at(g) && tempTile2->type.at(3) == tempTile1->type.at(h) && tempTile2->type.at(2) == tempTile1->type.at(a))
                    {
//                        cout<<"left"<<endl;
//                        cout<<"orientation is "<<z<<endl;
                        tempTile1->x = x;
                        tempTile1->y = y;
                        tempTile1->orientation = z;
                        movelist.push_back(tempTile1);
                        
                    }
                }else if(right)
                {
                    tempTile2 = _TileGrid[x+1][y];
                    
//                    for(int i = 0; i < 8; i++)
//                    {
//                        cout<<_TileGrid[x+1][y]->type.at(i);
//                    }
                    
                    if(tempTile2->type.at(6) == tempTile1->type.at(e) && tempTile2->type.at(7) == tempTile1->type.at(d) && tempTile2->type.at(0) == tempTile1->type.at(c))
                    {
//                        cout<<"right"<<endl;
//                        cout<<"orientation is "<<z<<endl;
                        tempTile1->x = x;
                        tempTile1->y = y;
                        tempTile1->orientation = z;
                        movelist.push_back(tempTile1);
                        
                    }
                }else if(bottom)
                {
                    tempTile2 = _TileGrid[x][y+1];
                    if(tempTile2->type.at(2) == tempTile1->type.at(e) && tempTile2->type.at(1) == tempTile1->type.at(f) && tempTile2->type.at(0) == tempTile1->type.at(g))
                    {
//                        cout<<"bottom"<<endl;
//                        cout<<"orientation is "<<z<<endl;
                        tempTile1->x = x;
                        tempTile1->y = y;
                        tempTile1->orientation = z;
                        movelist.push_back(tempTile1);
                        
                    }
                }else
                {
//                    cout<<"Nothing"<<endl;
                    tempTile1->x = x;
                    tempTile1->y = y;
                    tempTile1->orientation = z;
                    movelist.push_back(tempTile1);
                    
                }
                
            }
        
        }
//    cout<<"Gets to end of generate"<<endl;
    return movelist;

}



//This is the opponents future move
// int *Player::MinMoveDecision(Tile _TileGrid[153][153], int x, int y, int z, int moveNum, vector<Tile> temp, Tile t) {
// 	int *pvalue = evaluatePosition(_TileGrid, x, y, z, moveNum, t);
// 	if(pvalue[0] == -1)
// 		return pvalue;
// 	int bvalue[2] = {+BESTVALUE, 0};
// 	list<int> movelist;
// 	//current tile searches the temp list, which holds the order of the tiles, for the tile we need
// 	curTile = temp[moveNum-1];
// 	generateMoves(_TileGrid, movelist, curTile);
// 	while(!movelist.empty()) {
// 		int x = movelist.front();
// 		movelist.pop_front();
// 		int y = movelist.front();
// 		movelist.pop_front();
// 		int z = movelist.front();
// 		movelist.pop_front();
// 		curTile.orientation = z;
// 		_TileGrid[x][y] = curTile;
// 		//this would be after we placed a valid move and then the opponent placed a valid move, it would come back to us
// 		//int value = MaxMoveDecision(_TileGrid, x, y, z, moveNum+1, temp, t);
// 		//if we dont do use max move then we need an evaluatePosition method to get value
// 		int *value = evaluatePosition(_TileGrid, x, y, z, moveNum, t);
// 		if(value[0] > bvalue[0]){
// 			bvalue[0] = value[0];
// 			bvalue[1] = value[1];
// 		}
// 	}
// 	return bvalue;
// }

// //this is our future move
// int *Player::MaxMoveDecision(Tile _TileGrid[153][153], int x, int y, int z, int moveNum, vector<tile> temp, Tile t) {
// 	int *pvalue = evaluatePosition(_TileGrid, x, y, z, moveNum, t);
// 	if(pvalue[0] == -1)
// 		return pvalue;
// 	int bvalue[2] = {+BESTVALUE, 0};
// 	list<int> movelist;
// 	//current tile searches the temp list, which holds the order of the tiles, for the tile we need
// 	curTile = temp[moveNum];
// 	generateMoves(_TileGrid, movelist, curTile);
// 	while(!movelist.empty()) {
// 		int x = movelist.front();
// 		movelist.pop_front();
// 		int y = movelist.front();
// 		movelist.pop_front();
// 		int z = movelist.front();
// 		movelist.pop_front();
// 		curTile.orientation = z;
// 		_TileGrid[x][y] = curTile;
// 		//just like the last one but the opposite, this will keep going until the last move
// 		//int value = MinMoveDecision(_TileGrid, x, y, z, moveNum+1, temp, t);
// 		//if we dont do use min move then we need an evaluatePosition method to get value
// 		int *value = evaluatePosition(_TileGrid, x, y, z, moveNum, t);
// 		if(value[0] > bvalue[0]){
// 			bvalue[0] = value[0];
// 			bvalue[1] = value[1];
// 		}
// 	}
// 	return bvalue;
// }

//returns the value of the tile at that location also any prunning needed
//also any logic here can be changed or added, this is just a starting point for checking and such
int *Player::evaluatePosition(Tile * _TileGrid[153][153], int x, int y, int z, int num, Tile *t) {
	int value[0];
	int mLocation = tigerLocation(_TileGrid, x, y, z, num, t);
    //cout<<"the tiger location function works"<<endl;
	//should first check to see if we are helping the other player out with this move and return '-'1, if we have time
	if(mLocation  > 0){
		//return a value of 10 for feilds
		if(mLocation == 4){
			value[0] = 20;
			value[1] = 4;
			return value;
		}
		else if(mLocation == 1){
			value[0] = 10;
			value[1] = 1;
			return value;
		}
		//return a value of 5 for water
		else if(mLocation == 2){
			value[0] = 5;
			value[1] = 2;
			return value;
		}
		//return a value of 3 for paths
		else if(mLocation == 3){
			value[0] = 3;
			value[1] = 3;
			return value;
		}
		//return a value of 2 for crocs
		else{
			value[0] = 2;
			value[1] = 5;
			return value;
		}
	}
	else{
		value[0] = 0;
		value[1] = 0;
		return value;
	}
}

//picks tiger or croc location on tile
//also any logic here can be changed or added, this is just a starting point for checking and such
int Player::tigerLocation(Tile * _TileGrid[153][153], int x, int y, int z, int moveNum, Tile *t){
    int options[9];
	tigerCheck(options, _TileGrid, x, y, t);
    //cout<<"the tiger check function works"<<endl;
	//moveNum is, for example, move number 2 or 3 so to get number of tiles left we subtract it from 76
	int num = 76 - moveNum;
	//options[0] = the feild, options[1] = the water, options[2] = the path, options[3] = places a crocodile, options[4] = den
	if(num >= 50){
		//in this if statement, given these conditions, the presedence would be field over water over path 
		if(options[3] == 1 && tigerCount != 0)
			return 4;
		else if(options[0] == 1 && tigerCount != 0)
			return 1;
		else if(options[1] == 1 && tigerCount != 0)
			return 2;
		else if(options[2] == 1 && tigerCount != 0)
			return 3;
		else 
			return 0;
	}
	else if(num >= 30){
		//in this if statement, given these conditions, the presedence would be water over feild over path
		if(options[3] == 1 && tigerCount != 0)
			return 4;
		else if(options[1] == 1 && tigerCount != 0)
			return 2;
		else if(options[0] == 1 && tigerCount >= 3)
			return 1;
		else if(options[2] == 1 && tigerCount != 0)
			return 3;
		else 
			return 0;
	}
	else if(num >= 10){
		//in this if statement, given these conditions, the presedence would be water over path over placing a croc
		if(options[3] == 1 && tigerCount != 0)
			return 4;
		else if(options[1] == 1 && tigerCount != 0)
			return 2;
		else if(options[2] == 1 && tigerCount != 0)
			return 3;
		else if(options[3] == 1 && crocodileCount != 0)
			return 4;
		else 
			return 0;
	}
	else if (num >= 3){
		//in this if statement, given these conditions, the presedence would be water over path over placing a croc
		if(options[3] == 1 && tigerCount != 0)
			return 4;
		else if(options[1] == 1 && tigerCount != 0)
			return 2;
		else if(options[2] == 1 && tigerCount != 0)
			return 3;
		else if(options[3] == 1 && crocodileCount != 0)
			return 4;
		else 
			return 0;
	}
}

//checks the components to see where we can legally place tigers on this tile
void Player::tigerCheck(int options[9], Tile * _TileGrid[153][153], int x, int y, Tile * t){
    if(tigerCount == 0){
        options[0] = 0;
		options[1] = 0;
		options[2] = 0;
		options[3] = 0;
        options[4] = 0;
        options[5] = 0;
        options[6] = 0;
        options[7] = 0;
        options[8] = 0;
        //cout<<"out of tigers"<<endl;
    }
	else{
		options[0] = 0;
		options[1] = 0;
		options[2] = 0;
		options[3] = 0;
		//options[4] = 0;
        //cout<<"hmmmm"<<endl;
        int q;
        if(_TilePresent[x][y+1])
        {
            q = _TileGrid[x][y]->clusterid.at(5);
            //cout<<"q was set"<<endl;
            while (q != MainList[q].ParentId)
            {
                //cout<<"q could be compared to Mainlist"<<endl;
                q = MainList[q].ParentId;
            }
            if ((_TileGrid[x][y+1]->type.at(5) == 1 || _TileGrid[x][y+1]->type.at(5) == 3) && MainList[q].MeepleCountMe == 0 && MainList[q].MeepleCountYou == 0)
            {
                options[0] = 1;
            }
        }
        
        if(_TilePresent[x-1][y])
        {
            q = _TileGrid[x-1][y]->clusterid.at(1);
            while (q != MainList[q].ParentId)
            {
                q = MainList[q].ParentId;
            }
            if ((_TileGrid[x-1][y]->type.at(1) == 1 || _TileGrid[x-1][y]->type.at(1) == 3) && MainList[q].MeepleCountMe == 0 && MainList[q].MeepleCountYou == 0)
            {
                options[1] = 1;
            }
        }
        
		if(_TilePresent[x+1][y])
        {
            q = _TileGrid[x+1][y]->clusterid.at(7);
            while (q != MainList[q].ParentId)
            {
                q = MainList[q].ParentId;
            }
            if ((_TileGrid[x+1][y]->type.at(7) == 1 || _TileGrid[x+1][y]->type.at(7) == 3) && MainList[q].MeepleCountMe == 0 && MainList[q].MeepleCountYou == 0)
            {
                options[2] = 1;
            }
            
        }
        
        if(_TilePresent[x+1][y])
        {
            q = _TileGrid[x][y-1]->clusterid.at(3);
            while (q != MainList[q].ParentId)
            {
                q = MainList[q].ParentId;
            }
            if ((_TileGrid[x][y-1]->type.at(3) == 1 || _TileGrid[x][y-1]->type.at(3) == 3) && MainList[q].MeepleCountMe == 0 && MainList[q].MeepleCountYou == 0)
            {
                options[3] = 1;
            }
            if (t->Den == true)
            {
                options[4] = 1;
            }
        }
        
	}
}
//this updates our tigerCount. If the value is zero then we used a tiger, if the number is something else then we are receiving our tiger(s)
void Player::updateTigerCount(int value){
	if (value == 0)
		tigerCount--;
	else
		tigerCount = tigerCount + value;
}


Tile *Player::tileStructure(int i)
{
                //printf("In tileStructure\n");
		if(i == 0)
		{
		//printf("In tileStructure in 0\n");
            Tile *Tile_1 = new Tile();
            //printf("In tileStructure made it to return\n");
		/*Tile_1.des = {'J', 'J', 'J', 'J', '-'};
		Tile_1.type = {2,2,2,2,2,2,2,2};
		Tile_1.clusterid = {1,1,1,1,1,1,1,1};
		Tile_1.tiger = {false,false,false,false,false,false,false,false};
	
		return Tile_1;*/
       // Tile_1.
	Tile_1->des.push_back('J');//) = 'J';
	Tile_1->des.push_back('J');
        Tile_1->des.push_back('J');
	Tile_1->des.push_back('J');
	Tile_1->des.push_back('-');

        //printf("In tileStructure after des\n");
	
        Tile_1->type.push_back(2);
        Tile_1->type.push_back(2);
        Tile_1->type.push_back(2);
        Tile_1->type.push_back(2);
        Tile_1->type.push_back(2);
        Tile_1->type.push_back(2);
        Tile_1->type.push_back(2);
        Tile_1->type.push_back(2);
        Tile_1->clusterid.push_back(1);
        Tile_1->clusterid.push_back(1);
        Tile_1->clusterid.push_back(1);
        Tile_1->clusterid.push_back(1);
        Tile_1->clusterid.push_back(1);
        Tile_1->clusterid.push_back(1);
        Tile_1->clusterid.push_back(1);
        Tile_1->clusterid.push_back(1);
            Tile_1->tiger.push_back(false);
            Tile_1->tiger.push_back(false);
            Tile_1->tiger.push_back(false);
            Tile_1->tiger.push_back(false);
            Tile_1->tiger.push_back(false);
            Tile_1->tiger.push_back(false);
            Tile_1->tiger.push_back(false);
            Tile_1->tiger.push_back(false);
        Tile_1->croc_count = 0;
        Tile_1->Ox = false;
        Tile_1->Boar = false;
        Tile_1->Deer = false;
        Tile_1->Den = false;
        Tile_1->CenterClusterid = 0;
        Tile_1->x = 0;
        Tile_1->y = 0;
       // Tile_1.completion[4] = {false};
         

	//printf("In tileStructure made it to return\n");
        return Tile_1;
    }
	else if(i == 1){
        Tile *Tile_2 = new Tile();
	Tile_2->des.push_back('J');
	Tile_2->des.push_back('J');
        Tile_2->des.push_back('J');
	Tile_2->des.push_back('J');
	Tile_2->des.push_back('X');

        Tile_2->type.push_back(2);
        Tile_2->type.push_back(2);
        Tile_2->type.push_back(2);
        Tile_2->type.push_back(2);
        Tile_2->type.push_back(2);
        Tile_2->type.push_back(2);
        Tile_2->type.push_back(2);
        Tile_2->type.push_back(2);
        Tile_2->clusterid.push_back(1);
        Tile_2->clusterid.push_back(1);
        Tile_2->clusterid.push_back(1);
        Tile_2->clusterid.push_back(1);
        Tile_2->clusterid.push_back(1);
        Tile_2->clusterid.push_back(1);
        Tile_2->clusterid.push_back(1);
        Tile_2->clusterid.push_back(1);
        Tile_2->tiger.push_back(false);
        Tile_2->tiger.push_back(false);
        Tile_2->tiger.push_back(false);
        Tile_2->tiger.push_back(false);
        Tile_2->tiger.push_back(false);
        Tile_2->tiger.push_back(false);
        Tile_2->tiger.push_back(false);
        Tile_2->tiger.push_back(false);
		Tile_2->croc_count = 0;
		Tile_2->Ox = false;
		Tile_2->Boar = false;
		Tile_2->Deer = false;
		Tile_2->Den = true;
		Tile_2->CenterClusterid = 0;
		Tile_2->x = 0;
		Tile_2->y = 0;
		//Tile_2.completion[4] = {false};
		return Tile_2;
	}
	else if(i == 2){
        Tile *Tile_3 = new Tile();
	Tile_3->des.push_back('J');
	Tile_3->des.push_back('J');
        Tile_3->des.push_back('T');
	Tile_3->des.push_back('J');
	Tile_3->des.push_back('X');
	
        Tile_3->type.push_back(2);
        Tile_3->type.push_back(2);
        Tile_3->type.push_back(2);
        Tile_3->type.push_back(2);
        Tile_3->type.push_back(2);
        Tile_3->type.push_back(3);
        Tile_3->type.push_back(2);
        Tile_3->type.push_back(2);
        Tile_3->clusterid.push_back(1);
        Tile_3->clusterid.push_back(1);
        Tile_3->clusterid.push_back(1);
        Tile_3->clusterid.push_back(1);
        Tile_3->clusterid.push_back(1);
        Tile_3->clusterid.push_back(2);
        Tile_3->clusterid.push_back(1);
        Tile_3->clusterid.push_back(1);
        Tile_3->tiger.push_back(false);
        Tile_3->tiger.push_back(false);
        Tile_3->tiger.push_back(false);
        Tile_3->tiger.push_back(false);
        Tile_3->tiger.push_back(false);
        Tile_3->tiger.push_back(false);
        Tile_3->tiger.push_back(false);
        Tile_3->tiger.push_back(false);
		Tile_3->croc_count = 0;
		Tile_3->Ox = false;
		Tile_3->Boar = false;
		Tile_3->Deer = false;
		Tile_3->Den = true;
		Tile_3->CenterClusterid = 0;
		Tile_3->x = 0;
		Tile_3->y = 0;
		//Tile_3.completion[4] = {false};
		return Tile_3;
	}
	else if(i == 3){
		//
        Tile *Tile_4 = new Tile();
	Tile_4->des.push_back('T');
	Tile_4->des.push_back('T');
        Tile_4->des.push_back('T');
	Tile_4->des.push_back('T');
	Tile_4->des.push_back('-');
	
        Tile_4->type.push_back(2);
        Tile_4->type.push_back(3);
        Tile_4->type.push_back(2);
        Tile_4->type.push_back(3);
        Tile_4->type.push_back(2);
        Tile_4->type.push_back(3);
        Tile_4->type.push_back(2);
        Tile_4->type.push_back(3);
        Tile_4->clusterid.push_back(1);
        Tile_4->clusterid.push_back(2);
        Tile_4->clusterid.push_back(3);
        Tile_4->clusterid.push_back(4);
        Tile_4->clusterid.push_back(5);
        Tile_4->clusterid.push_back(6);
        Tile_4->clusterid.push_back(7);
        Tile_4->clusterid.push_back(8);
        Tile_4->tiger.push_back(false);
        Tile_4->tiger.push_back(false);
        Tile_4->tiger.push_back(false);
        Tile_4->tiger.push_back(false);
        Tile_4->tiger.push_back(false);
        Tile_4->tiger.push_back(false);
        Tile_4->tiger.push_back(false);
        Tile_4->tiger.push_back(false);
	Tile_4->croc_count = 0;
	Tile_4->Ox = false;
	Tile_4->Boar = false;
	Tile_4->Deer = false;
	Tile_4->Den = false;
	Tile_4->CenterClusterid = 0;
	Tile_4->x = 0;
	Tile_4->y = 0;
	//Tile_4.completion[4] = {false};
	return Tile_4;
	}
	else if(i == 4){
        Tile *Tile_5 = new Tile();
	Tile_5->des.push_back('T');
	Tile_5->des.push_back('J');
        Tile_5->des.push_back('T');
	Tile_5->des.push_back('J');
	Tile_5->des.push_back('-');

        Tile_5->type.push_back(2);
        Tile_5->type.push_back(3);
        Tile_5->type.push_back(2);
        Tile_5->type.push_back(2);
        Tile_5->type.push_back(2);
        Tile_5->type.push_back(3);
        Tile_5->type.push_back(2);
        Tile_5->type.push_back(2);
        Tile_5->clusterid.push_back(1);
        Tile_5->clusterid.push_back(2);
        Tile_5->clusterid.push_back(3);
        Tile_5->clusterid.push_back(3);
        Tile_5->clusterid.push_back(3);
        Tile_5->clusterid.push_back(2);
        Tile_5->clusterid.push_back(1);
        Tile_5->clusterid.push_back(1);
        Tile_5->tiger.push_back(false);
        Tile_5->tiger.push_back(false);
        Tile_5->tiger.push_back(false);
        Tile_5->tiger.push_back(false);
        Tile_5->tiger.push_back(false);
        Tile_5->tiger.push_back(false);
        Tile_5->tiger.push_back(false);
        Tile_5->tiger.push_back(false);
		Tile_5->croc_count = 0;
		Tile_5->Ox = false;
		Tile_5->Boar = false;
		Tile_5->Deer = false;
		Tile_5->Den = false;
		Tile_5->CenterClusterid = 0;
		Tile_5->x = 0;
		Tile_5->y = 0;
		//Tile_5.completion[4] = {false};
		return Tile_5;
	}
	else if(i == 5){
        Tile *Tile_6 = new Tile();
	Tile_6->des.push_back('T');
	Tile_6->des.push_back('J');
        Tile_6->des.push_back('J');
	Tile_6->des.push_back('T');
	Tile_6->des.push_back('-');
	
        Tile_6->type.push_back(2);
        Tile_6->type.push_back(3);
        Tile_6->type.push_back(2);
        Tile_6->type.push_back(2);
        Tile_6->type.push_back(2);
        Tile_6->type.push_back(2);
        Tile_6->type.push_back(2);
        Tile_6->type.push_back(3);
        Tile_6->clusterid.push_back(1);
        Tile_6->clusterid.push_back(2);
        Tile_6->clusterid.push_back(3);
        Tile_6->clusterid.push_back(3);
        Tile_6->clusterid.push_back(3);
        Tile_6->clusterid.push_back(3);
        Tile_6->clusterid.push_back(3);
        Tile_6->clusterid.push_back(2);
        Tile_6->tiger.push_back(false);
        Tile_6->tiger.push_back(false);
        Tile_6->tiger.push_back(false);
        Tile_6->tiger.push_back(false);
        Tile_6->tiger.push_back(false);
        Tile_6->tiger.push_back(false);
        Tile_6->tiger.push_back(false);
        Tile_6->tiger.push_back(false);
		Tile_6->croc_count = 0;
		Tile_6->Ox = false;
		Tile_6->Boar = false;
		Tile_6->Deer = false;
		Tile_6->Den = false;
		Tile_6->CenterClusterid = 0;
		Tile_6->x = 0;
		Tile_6->y = 0;
		//Tile_6.completion[4] = {false};
		return Tile_6;
	}
	else if(i == 6){
        Tile *Tile_7 = new Tile();
        Tile_7->des.push_back('T');
	Tile_7->des.push_back('J');
        Tile_7->des.push_back('T');
	Tile_7->des.push_back('T');
	Tile_7->des.push_back('-');
        Tile_7->type.push_back(2);
        Tile_7->type.push_back(3);
        Tile_7->type.push_back(2);
        Tile_7->type.push_back(2);
        Tile_7->type.push_back(2);
        Tile_7->type.push_back(3);
        Tile_7->type.push_back(2);
        Tile_7->type.push_back(3);
        Tile_7->clusterid.push_back(1);
        Tile_7->clusterid.push_back(2);
        Tile_7->clusterid.push_back(3);
        Tile_7->clusterid.push_back(3);
        Tile_7->clusterid.push_back(3);
        Tile_7->clusterid.push_back(4);
        Tile_7->clusterid.push_back(5);
        Tile_7->clusterid.push_back(6);
        Tile_7->tiger.push_back(false);
        Tile_7->tiger.push_back(false);
        Tile_7->tiger.push_back(false);
        Tile_7->tiger.push_back(false);
        Tile_7->tiger.push_back(false);
        Tile_7->tiger.push_back(false);
        Tile_7->tiger.push_back(false);
        Tile_7->tiger.push_back(false);
		Tile_7->croc_count = 0;
		Tile_7->Ox = false;
		Tile_7->Boar = false;
		Tile_7->Deer = false;
		Tile_7->Den = false;
		Tile_7->CenterClusterid = 0;
		Tile_7->x = 0;
		Tile_7->y = 0;
		//Tile_7.completion[4] = {false};
		return Tile_7;
	}
	else if(i == 7){
        Tile *Tile_8 = new Tile();
	Tile_8->des.push_back('L');
	Tile_8->des.push_back('L');
        Tile_8->des.push_back('L');
	Tile_8->des.push_back('L');
	Tile_8->des.push_back('-');
	
        Tile_8->type.push_back(1);
        Tile_8->type.push_back(1);
        Tile_8->type.push_back(1);
        Tile_8->type.push_back(1);
        Tile_8->type.push_back(1);
        Tile_8->type.push_back(1);
        Tile_8->type.push_back(1);
        Tile_8->type.push_back(1);
        Tile_8->clusterid.push_back(1);
        Tile_8->clusterid.push_back(1);
        Tile_8->clusterid.push_back(1);
        Tile_8->clusterid.push_back(1);
        Tile_8->clusterid.push_back(1);
        Tile_8->clusterid.push_back(1);
        Tile_8->clusterid.push_back(1);
        Tile_8->clusterid.push_back(1);
        Tile_8->tiger.push_back(false);
        Tile_8->tiger.push_back(false);
        Tile_8->tiger.push_back(false);
        Tile_8->tiger.push_back(false);
        Tile_8->tiger.push_back(false);
        Tile_8->tiger.push_back(false);
        Tile_8->tiger.push_back(false);
        Tile_8->tiger.push_back(false);
		Tile_8->croc_count = 0;
		Tile_8->Ox = false;
		Tile_8->Boar = false;
		Tile_8->Deer = false;
		Tile_8->Den = false;
		Tile_8->CenterClusterid = 0;
		Tile_8->x = 0;
		Tile_8->y = 0;
		//Tile_8.completion[4] = {false};
		return Tile_8;
	}
	else if(i == 8){
		Tile *Tile_9 = new Tile();
	       Tile_9->des.push_back('J');
	       Tile_9->des.push_back('L');
               Tile_9->des.push_back('L');
	       Tile_9->des.push_back('L');
	       Tile_9->des.push_back('-');
	    
		//Tile_9.des = {'J', 'L', 'L', 'L', '-'};
		Tile_9->type.push_back(2);
		Tile_9->type.push_back(2);
		Tile_9->type.push_back(2);
		Tile_9->type.push_back(1);
		Tile_9->type.push_back(1);
		Tile_9->type.push_back(1);
		Tile_9->type.push_back(1);
		Tile_9->type.push_back(1);
		Tile_9->clusterid.push_back(1);
		Tile_9->clusterid.push_back(1);
		Tile_9->clusterid.push_back(1);
		Tile_9->clusterid.push_back(2);
		Tile_9->clusterid.push_back(2);
		Tile_9->clusterid.push_back(2);
		Tile_9->clusterid.push_back(2);
		Tile_9->clusterid.push_back(2);
		Tile_9->tiger.push_back(false);
		Tile_9->tiger.push_back(false);
		Tile_9->tiger.push_back(false);
		Tile_9->tiger.push_back(false);
		Tile_9->tiger.push_back(false);
		Tile_9->tiger.push_back(false);
		Tile_9->tiger.push_back(false);
		Tile_9->tiger.push_back(false);
		//Tile_9.type = {2,2,2,1,1,1,1,1};
		//Tile_9.clusterid = {1,1,1,2,2,2,2,2};
		//Tile_9.tiger = {false,false,false,false,false,false,false,false};
		Tile_9->croc_count = 0;
		Tile_9->Ox = false;
		Tile_9->Boar = false;
		Tile_9->Deer = false;
		Tile_9->Den = false;
		Tile_9->CenterClusterid = 0;
		Tile_9->x = 0;
		Tile_9->y = 0;
		//Tile_9.completion[4] = {false};
		return Tile_9;
	}
	else if(i == 9){
		Tile *Tile_10 = new Tile();
		Tile_10->des.push_back('L');
		Tile_10->des.push_back('L');
       		Tile_10->des.push_back('J');
		Tile_10->des.push_back('J');
		Tile_10->des.push_back('-');
		
		//Tile_10.des = {'L', 'L', 'J', 'J', '-'};
		Tile_10->type.push_back(2);
		Tile_10->type.push_back(1);
		Tile_10->type.push_back(1);
		Tile_10->type.push_back(1);
		Tile_10->type.push_back(2);
		Tile_10->type.push_back(2);
		Tile_10->type.push_back(2);
		Tile_10->type.push_back(2);
		Tile_10->clusterid.push_back(1);
		Tile_10->clusterid.push_back(2);
		Tile_10->clusterid.push_back(2);
		Tile_10->clusterid.push_back(2);
		Tile_10->clusterid.push_back(1);
		Tile_10->clusterid.push_back(1);
		Tile_10->clusterid.push_back(1);
		Tile_10->clusterid.push_back(1);
		Tile_10->tiger.push_back(false);
		Tile_10->tiger.push_back(false);
		Tile_10->tiger.push_back(false);
		Tile_10->tiger.push_back(false);
		Tile_10->tiger.push_back(false);
		Tile_10->tiger.push_back(false);
		Tile_10->tiger.push_back(false);
		Tile_10->tiger.push_back(false);
		//Tile_10.type = {2,1,1,1,2,2,2,2};
		//Tile_10.clusterid = {1,2,2,2,1,1,1,1};
		//Tile_10.tiger = {false,false,false,false,false,false,false,false};
		Tile_10->croc_count = 0;
		Tile_10->Ox = false;
		Tile_10->Boar = false;
		Tile_10->Deer = false;
		Tile_10->Den = false;
		Tile_10->CenterClusterid = 0;
		Tile_10->x = 0;
		Tile_10->y = 0;
		//Tile_10.completion[4] = {false};
		return Tile_10;
	}
	else if(i == 10){
		Tile *Tile_11 = new Tile();
	//	Tile_11.des = {'J', 'L', 'J', 'L', '-'};
		Tile_11->des.push_back('J');
		Tile_11->des.push_back('L');
       		Tile_11->des.push_back('J');
		Tile_11->des.push_back('L');
		Tile_11->des.push_back('-');
		
		Tile_11->type.push_back(2);
		Tile_11->type.push_back(2);
		Tile_11->type.push_back(2);
		Tile_11->type.push_back(1);
		Tile_11->type.push_back(2);
		Tile_11->type.push_back(2);
		Tile_11->type.push_back(2);
		Tile_11->type.push_back(1);
		Tile_11->clusterid.push_back(1);
		Tile_11->clusterid.push_back(1);
		Tile_11->clusterid.push_back(1);
		Tile_11->clusterid.push_back(2);
		Tile_11->clusterid.push_back(3);
		Tile_11->clusterid.push_back(3);
		Tile_11->clusterid.push_back(3);
		Tile_11->clusterid.push_back(2);
		Tile_11->tiger.push_back(false);
		Tile_11->tiger.push_back(false);
		Tile_11->tiger.push_back(false);
		Tile_11->tiger.push_back(false);
		Tile_11->tiger.push_back(false);
		Tile_11->tiger.push_back(false);
		Tile_11->tiger.push_back(false);
		Tile_11->tiger.push_back(false);
		//Tile_11.type = {2,2,2,1,2,2,2,1};/////
		//Tile_11.clusterid = {1,1,1,2,3,3,3,2};
		//Tile_11.tiger = {false,false,false,false,false,false,false,false};
		Tile_11->croc_count = 0;
		Tile_11->Ox = false;
		Tile_11->Boar = false;
		Tile_11->Deer = false;
		Tile_11->Den = false;
		Tile_11->CenterClusterid = 0;
		Tile_11->x = 0;
		Tile_11->y = 0;
		//Tile_11.completion[4] = {false};
		return Tile_11;
	}
	else if(i == 11){
        Tile *Tile_12 = new Tile();
	//	Tile_12.des = {'L', 'J', 'L', 'J', '-'};
		Tile_12->des.push_back('L');
		Tile_12->des.push_back('J');
       		Tile_12->des.push_back('L');
		Tile_12->des.push_back('J');
		Tile_12->des.push_back('-');
		Tile_12->type.push_back(2);
		Tile_12->type.push_back(1);
		Tile_12->type.push_back(2);
		Tile_12->type.push_back(2);
		Tile_12->type.push_back(2);
		Tile_12->type.push_back(1);
		Tile_12->type.push_back(2);
		Tile_12->type.push_back(2);
		Tile_12->clusterid.push_back(1);
		Tile_12->clusterid.push_back(2);
		Tile_12->clusterid.push_back(1);
		Tile_12->clusterid.push_back(1);
		Tile_12->clusterid.push_back(1);
		Tile_12->clusterid.push_back(3);
		Tile_12->clusterid.push_back(1);
		Tile_12->clusterid.push_back(1);
		Tile_12->tiger.push_back(false);
		Tile_12->tiger.push_back(false);
		Tile_12->tiger.push_back(false);
		Tile_12->tiger.push_back(false);
		Tile_12->tiger.push_back(false);
		Tile_12->tiger.push_back(false);
		Tile_12->tiger.push_back(false);
		Tile_12->tiger.push_back(false);
		//Tile_12.type = {2,1,2,2,2,1,2,2};////
		//Tile_12.clusterid = {1,2,1,1,1,3,1,1};
		//Tile_12.tiger = {false,false,false,false,false,false,false,false};
		Tile_12->croc_count = 0;
		Tile_12->Ox = false;
		Tile_12->Boar = false;
		Tile_12->Deer = false;
		Tile_12->Den = false;
		Tile_12->CenterClusterid = 0;
		Tile_12->x = 0;
		Tile_12->y = 0;
		//Tile_12.completion[4] = {false};
		return Tile_12;
	}
	else if(i == 12){
		Tile *Tile_13 = new Tile();
	//	Tile_13.des = {'L', 'J', 'J', 'J', '-'};
		Tile_13->des.push_back('L');
		Tile_13->des.push_back('J');
       		Tile_13->des.push_back('J');
		Tile_13->des.push_back('J');
		Tile_13->des.push_back('-');
		Tile_13->type.push_back(2);
		Tile_13->type.push_back(1);
		Tile_13->type.push_back(2);
		Tile_13->type.push_back(2);
		Tile_13->type.push_back(2);
		Tile_13->type.push_back(2);
		Tile_13->type.push_back(2);
		Tile_13->type.push_back(2);
		Tile_13->clusterid.push_back(1);
		Tile_13->clusterid.push_back(2);
		Tile_13->clusterid.push_back(1);
		Tile_13->clusterid.push_back(1);
		Tile_13->clusterid.push_back(1);
		Tile_13->clusterid.push_back(1);
		Tile_13->clusterid.push_back(1);
        Tile_13->clusterid.push_back(1);
		Tile_13->tiger.push_back(false);
		Tile_13->tiger.push_back(false);
		Tile_13->tiger.push_back(false);
		Tile_13->tiger.push_back(false);
		Tile_13->tiger.push_back(false);
		Tile_13->tiger.push_back(false);
		Tile_13->tiger.push_back(false);
		Tile_13->tiger.push_back(false);
		//Tile_13.type = {2,1,2,2,2,2,2,2};
		//Tile_13.clusterid = {1,2,1,1,1,1,1,1}; 
		//Tile_13.tiger = {false,false,false,false,false,false,false,false};
		Tile_13->croc_count = 0;
		Tile_13->Ox = false;
		Tile_13->Boar = false;
		Tile_13->Deer = false;
		Tile_13->Den = false;
		Tile_13->CenterClusterid = 0;
		Tile_13->x = 0;
		Tile_13->y = 0;
		//Tile_13.completion[4] = {false};
		return Tile_13;
	}
	else if(i == 13){
		Tile  *Tile_14 = new Tile();
		//Tile_14.des = {'J', 'L', 'L', 'J', '-'};
		Tile_14->des.push_back('J');
		Tile_14->des.push_back('L');
       		Tile_14->des.push_back('L');
		Tile_14->des.push_back('J');
		Tile_14->des.push_back('-');
		Tile_14->type.push_back(2);
		Tile_14->type.push_back(2);
		Tile_14->type.push_back(2);
		Tile_14->type.push_back(1);
		Tile_14->type.push_back(4);
		Tile_14->type.push_back(1);
		Tile_14->type.push_back(2);
		Tile_14->type.push_back(2);
		Tile_14->clusterid.push_back(1);
		Tile_14->clusterid.push_back(1);
		Tile_14->clusterid.push_back(1);
		Tile_14->clusterid.push_back(2);
		Tile_14->clusterid.push_back(0);
		Tile_14->clusterid.push_back(3);
		Tile_14->clusterid.push_back(1);
		Tile_14->clusterid.push_back(1);
		Tile_14->tiger.push_back(false);
		Tile_14->tiger.push_back(false);
		Tile_14->tiger.push_back(false);
		Tile_14->tiger.push_back(false);
		Tile_14->tiger.push_back(false);
		Tile_14->tiger.push_back(false);
		Tile_14->tiger.push_back(false);
		Tile_14->tiger.push_back(false);
		//Tile_14.type = {2,2,2,1,4,1,2,2};
		//Tile_14.clusterid = {1,1,1,2,0,3,1,1};
		//Tile_14.tiger = {false,false,false,false,false,false,false,false};
		Tile_14->croc_count = 0;
		Tile_14->Ox = false;
		Tile_14->Boar = false;
		Tile_14->Deer = false;
		Tile_14->Den = false;
		Tile_14->CenterClusterid = 0;
		Tile_14->x = 0;
		Tile_14->y = 0;
		//Tile_14.completion[4] = {false};
		return Tile_14;
	}
	else if(i == 14){
		Tile *Tile_15 = new Tile();
		//Tile_15.des = {'T', 'L', 'J', 'T', '-'};
		Tile_15->des.push_back('T');
		Tile_15->des.push_back('L');
       		Tile_15->des.push_back('J');
		Tile_15->des.push_back('T');
		Tile_15->des.push_back('-');
		Tile_15->type.push_back(2);
		Tile_15->type.push_back(3);
		Tile_15->type.push_back(2);
		Tile_15->type.push_back(1);
		Tile_15->type.push_back(2);
		Tile_15->type.push_back(2);
		Tile_15->type.push_back(2);
		Tile_15->type.push_back(3);
		Tile_15->clusterid.push_back(1);
		Tile_15->clusterid.push_back(2);
		Tile_15->clusterid.push_back(3);
		Tile_15->clusterid.push_back(4);
		Tile_15->clusterid.push_back(3);
		Tile_15->clusterid.push_back(3);
		Tile_15->clusterid.push_back(3);
		Tile_15->clusterid.push_back(2);
		Tile_15->tiger.push_back(false);
		Tile_15->tiger.push_back(false);
		Tile_15->tiger.push_back(false);
		Tile_15->tiger.push_back(false);
		Tile_15->tiger.push_back(false);
		Tile_15->tiger.push_back(false);
		Tile_15->tiger.push_back(false);
		Tile_15->tiger.push_back(false);
		//Tile_15.type = {2,3,2,1,2,2,2,3};
		//Tile_15.clusterid = {1,2,1,3,1,1,1,2};
		//Tile_15.tiger = {false,false,false,false,false,false,false,false};
		Tile_15->croc_count = 0;
		Tile_15->Ox = false;
		Tile_15->Boar = false;
		Tile_15->Deer = false;
		Tile_15->Den = false;
		Tile_15->CenterClusterid = 0;
		Tile_15->x = 0;
		Tile_15->y = 0;
		//Tile_15.completion[4] = {false};
		return Tile_15;
	}
	else if(i == 15){
		Tile *Tile_16 = new Tile();
		//Tile_16.des = {'T', 'L', 'J', 'T', 'P'};
		Tile_16->des.push_back('T');
		Tile_16->des.push_back('L');
       		Tile_16->des.push_back('J');
		Tile_16->des.push_back('T');
		Tile_16->des.push_back('P');
		Tile_16->type.push_back(2);
		Tile_16->type.push_back(3);
		Tile_16->type.push_back(2);
		Tile_16->type.push_back(1);
		Tile_16->type.push_back(2);
		Tile_16->type.push_back(2);
		Tile_16->type.push_back(2);
		Tile_16->type.push_back(3);
		Tile_16->clusterid.push_back(1);
		Tile_16->clusterid.push_back(2);
		Tile_16->clusterid.push_back(3);
		Tile_16->clusterid.push_back(4);
		Tile_16->clusterid.push_back(3);
		Tile_16->clusterid.push_back(3);
		Tile_16->clusterid.push_back(3);
		Tile_16->clusterid.push_back(2);
		Tile_16->tiger.push_back(false);
		Tile_16->tiger.push_back(false);
		Tile_16->tiger.push_back(false);
		Tile_16->tiger.push_back(false);
		Tile_16->tiger.push_back(false);
		Tile_16->tiger.push_back(false);
		Tile_16->tiger.push_back(false);
		Tile_16->tiger.push_back(false);
		//Tile_16.type = {2,3,2,1,2,2,2,3}; // has boar
		//Tile_16.clusterid = {1,2,1,3,1,1,1,2};
		//Tile_16.tiger = {false,false,false,false,false,false,false,false};
		Tile_16->croc_count = 0;
		Tile_16->Ox = false;
		Tile_16->Boar = true;
		Tile_16->Deer = false;
		Tile_16->Den = false;
		Tile_16->CenterClusterid = 0;
		Tile_16->x = 0;
		Tile_16->y = 0;
		//Tile_16.completion[4] = {false};
		return Tile_16;
	}
	else if(i == 16){
		Tile *Tile_17 = new Tile();
	//	Tile_17.des = {'J', 'L', 'T', 'T', '-'};
		Tile_17->des.push_back('J');
		Tile_17->des.push_back('L');
       		Tile_17->des.push_back('T');
		Tile_17->des.push_back('T');
		Tile_17->des.push_back('-');
		Tile_17->type.push_back(2);
		Tile_17->type.push_back(2);
		Tile_17->type.push_back(2);
		Tile_17->type.push_back(1);
		Tile_17->type.push_back(2);
		Tile_17->type.push_back(3);
		Tile_17->type.push_back(2);
		Tile_17->type.push_back(3);
		Tile_17->clusterid.push_back(1);
		Tile_17->clusterid.push_back(1);
		Tile_17->clusterid.push_back(1);
		Tile_17->clusterid.push_back(2);
		Tile_17->clusterid.push_back(1);
		Tile_17->clusterid.push_back(3);
		Tile_17->clusterid.push_back(4);
		Tile_17->clusterid.push_back(3);
		Tile_17->tiger.push_back(false);
		Tile_17->tiger.push_back(false);
		Tile_17->tiger.push_back(false);
		Tile_17->tiger.push_back(false);
		Tile_17->tiger.push_back(false);
        Tile_17->tiger.push_back(false);
		Tile_17->tiger.push_back(false);
        Tile_17->tiger.push_back(false);
		//Tile_17.type = {2,2,2,1,2,3,2,3};
		//Tile_17.clusterid = {1,1,1,2,1,3,4,3};
		//Tile_17.tiger = {false,false,false,false,false,false,false,false};
		Tile_17->croc_count = 0;
		Tile_17->Ox = false;
		Tile_17->Boar = false;
		Tile_17->Deer = false;
		Tile_17->Den = false;
		Tile_17->CenterClusterid = 0;
		Tile_17->x = 0;
		Tile_17->y = 0;
		//Tile_17.completion[4] = {false};
		return Tile_17;
	}
	else if(i == 17){
		Tile *Tile_18 = new Tile();
	//	Tile_18.des = {'J', 'L', 'T', 'T', 'B'};
		Tile_18->des.push_back('J');
		Tile_18->des.push_back('L');
       		Tile_18->des.push_back('T');
		Tile_18->des.push_back('T');
		Tile_18->des.push_back('B');
		Tile_18->type.push_back(2);
		Tile_18->type.push_back(2);
		Tile_18->type.push_back(2);
		Tile_18->type.push_back(1);
		Tile_18->type.push_back(2);
		Tile_18->type.push_back(3);
		Tile_18->type.push_back(2);
        Tile_18->type.push_back(3);
		Tile_18->clusterid.push_back(1);
		Tile_18->clusterid.push_back(1);
		Tile_18->clusterid.push_back(1);
		Tile_18->clusterid.push_back(2);
		Tile_18->clusterid.push_back(1);
		Tile_18->clusterid.push_back(3);
		Tile_18->clusterid.push_back(4);
		Tile_18->clusterid.push_back(3);
		Tile_18->tiger.push_back(false);
		Tile_18->tiger.push_back(false);
		Tile_18->tiger.push_back(false);
		Tile_18->tiger.push_back(false);
		Tile_18->tiger.push_back(false);
		Tile_18->tiger.push_back(false);
		Tile_18->tiger.push_back(false);
		Tile_18->tiger.push_back(false);
		//Tile_18.type = {2,2,2,1,2,3,2,3}; // has ox
		//Tile_18.clusterid = {1,1,1,2,1,3,4,3};
		//Tile_18.tiger = {false,false,false,false,false,false,false,false};
		Tile_18->croc_count = 0;
		Tile_18->Ox = true;
		Tile_18->Boar = false;
		Tile_18->Deer = false;
		Tile_18->Den = false;
		Tile_18->CenterClusterid = 0;
		Tile_18->x = 0;
		Tile_18->y = 0;
		//Tile_18.completion[4] = {false};
		return Tile_18;
	}
	else if(i == 18){
		Tile *Tile_19 = new Tile();
	//	Tile_19.des = {'T', 'L', 'T', 'J', '-'};
		Tile_19->des.push_back('T');
		Tile_19->des.push_back('L');
       		Tile_19->des.push_back('T');
		Tile_19->des.push_back('J');
		Tile_19->des.push_back('-');
		Tile_19->type.push_back(2);
		Tile_19->type.push_back(3);
		Tile_19->type.push_back(2);
		Tile_19->type.push_back(1);
		Tile_19->type.push_back(2);
		Tile_19->type.push_back(3);
		Tile_19->type.push_back(2);
		Tile_19->type.push_back(2);
		Tile_19->clusterid.push_back(1);
		Tile_19->clusterid.push_back(2);
		Tile_19->clusterid.push_back(3);
		Tile_19->clusterid.push_back(4);
		Tile_19->clusterid.push_back(3);
		Tile_19->clusterid.push_back(2);
		Tile_19->clusterid.push_back(1);
		Tile_19->clusterid.push_back(1);
		Tile_19->tiger.push_back(false);
		Tile_19->tiger.push_back(false);
		Tile_19->tiger.push_back(false);
		Tile_19->tiger.push_back(false);
		Tile_19->tiger.push_back(false);
		Tile_19->tiger.push_back(false);
		Tile_19->tiger.push_back(false);
		Tile_19->tiger.push_back(false);
		//Tile_19.type = {2,3,2,1,2,3,2,3};
		//Tile_19.clusterid = {1,2,3,4,3,2,1,1};
		//Tile_19.tiger = {false,false,false,false,false,false,false,false};
		Tile_19->croc_count = 0;
		Tile_19->Ox = false;
		Tile_19->Boar = false;
		Tile_19->Deer = false;
		Tile_19->Den = false;
		Tile_19->CenterClusterid = 0;
		Tile_19->x = 0;
		Tile_19->y = 0;
		//Tile_19.completion[4] = {false};
		return Tile_19;
	}
	else if(i == 19){
		Tile *Tile_20 = new Tile();
	//	Tile_20.des = {'T', 'L', 'T', 'J', 'D'};
		Tile_20->des.push_back('T');
		Tile_20->des.push_back('L');
       		Tile_20->des.push_back('T');
		Tile_20->des.push_back('J');
		Tile_20->des.push_back('D');
		Tile_20->type.push_back(2);
		Tile_20->type.push_back(3);
		Tile_20->type.push_back(2);
		Tile_20->type.push_back(1);
		Tile_20->type.push_back(2);
		Tile_20->type.push_back(3);
		Tile_20->type.push_back(2);
		Tile_20->type.push_back(2);
		Tile_20->clusterid.push_back(1);
		Tile_20->clusterid.push_back(2);
		Tile_20->clusterid.push_back(3);
		Tile_20->clusterid.push_back(4);
		Tile_20->clusterid.push_back(3);
		Tile_20->clusterid.push_back(2);
		Tile_20->clusterid.push_back(1);
		Tile_20->clusterid.push_back(1);
		Tile_20->tiger.push_back(false);
		Tile_20->tiger.push_back(false);
		Tile_20->tiger.push_back(false);
		Tile_20->tiger.push_back(false);
		Tile_20->tiger.push_back(false);
		Tile_20->tiger.push_back(false);
		Tile_20->tiger.push_back(false);
		Tile_20->tiger.push_back(false);
		//Tile_20.type = {2,3,2,1,2,3,2,3}; // has deer	
		//Tile_20.clusterid = {1,2,3,4,3,2,1,1};
		//Tile_20.tiger = {false,false,false,false,false,false,false,false};
		Tile_20->croc_count = 0;
		Tile_20->Ox = false;
		Tile_20->Boar = false;
		Tile_20->Deer = true;
		Tile_20->Den = false;
		Tile_20->CenterClusterid = 0;
		Tile_20->x = 0;
		Tile_20->y = 0;
		//Tile_20.completion[4] = {false};
		return Tile_20;
	}
	else if(i == 20){
		Tile *Tile_21 = new Tile();
	//	Tile_21.des = {'T', 'L', 'L', 'L', '-'};
		Tile_21->des.push_back('T');
		Tile_21->des.push_back('L');
       		Tile_21->des.push_back('L');
		Tile_21->des.push_back('L');
		Tile_21->des.push_back('-');
		Tile_21->type.push_back(2);
		Tile_21->type.push_back(3);
		Tile_21->type.push_back(2);
		Tile_21->type.push_back(1);
		Tile_21->type.push_back(1);
		Tile_21->type.push_back(1);
		Tile_21->type.push_back(1);
		Tile_21->type.push_back(1);
		Tile_21->clusterid.push_back(1);
		Tile_21->clusterid.push_back(2);
		Tile_21->clusterid.push_back(3);
		Tile_21->clusterid.push_back(4);
		Tile_21->clusterid.push_back(4);
		Tile_21->clusterid.push_back(4);
		Tile_21->clusterid.push_back(4);
		Tile_21->clusterid.push_back(4);
		Tile_21->tiger.push_back(false);
		Tile_21->tiger.push_back(false);
		Tile_21->tiger.push_back(false);
		Tile_21->tiger.push_back(false);
		Tile_21->tiger.push_back(false);
		Tile_21->tiger.push_back(false);
		Tile_21->tiger.push_back(false);
		Tile_21->tiger.push_back(false);
		//Tile_21.type = {2,3,2,1,1,1,1,1};
		//Tile_21.clusterid = {1,2,3,4,4,4,4,4};
		//Tile_21.tiger = {false,false,false,false,false,false,false,false};
		Tile_21->croc_count = 0;
		Tile_21->Ox = false;
		Tile_21->Boar = false;
		Tile_21->Deer = false;
		Tile_21->Den = false;
		Tile_21->CenterClusterid = 0;
		Tile_21->x = 0;
		Tile_21->y = 0;
		//Tile_*21.completion[4] = {false};
		return Tile_21;
	}
	else if(i == 21){
		Tile *Tile_22 = new Tile();
	//	Tile_22.des = {'T', 'L', 'T', 'T', '-'};
		Tile_22->des.push_back('T');
		Tile_22->des.push_back('L');
       		Tile_22->des.push_back('T');
		Tile_22->des.push_back('T');
		Tile_22->des.push_back('-');
		Tile_22->type.push_back(2);
		Tile_22->type.push_back(3);
		Tile_22->type.push_back(2);
		Tile_22->type.push_back(1);
		Tile_22->type.push_back(2);
		Tile_22->type.push_back(3);
		Tile_22->type.push_back(2);
		Tile_22->type.push_back(3);
		Tile_22->clusterid.push_back(1);
		Tile_22->clusterid.push_back(2);
		Tile_22->clusterid.push_back(3);
		Tile_22->clusterid.push_back(4);
		Tile_22->clusterid.push_back(3);
		Tile_22->clusterid.push_back(2);
		Tile_22->clusterid.push_back(5);
		Tile_22->clusterid.push_back(2);
		Tile_22->tiger.push_back(false);
		Tile_22->tiger.push_back(false);
		Tile_22->tiger.push_back(false);
		Tile_22->tiger.push_back(false);
		Tile_22->tiger.push_back(false);
		Tile_22->tiger.push_back(false);
		Tile_22->tiger.push_back(false);
		Tile_22->tiger.push_back(false);
		//Tile_22.type = {2,3,2,1,2,2,2,3};
		//Tile_22.clusterid = {1,2,3,4,3,2,5,2};
		//Tile_22.tiger = {false,false,false,false,false,false,false,false};
		Tile_22->croc_count = 0;
		Tile_22->Ox = false;
		Tile_22->Boar = false;
		Tile_22->Deer = false;
		Tile_22->Den = false;	
		Tile_22->CenterClusterid = 0;
		Tile_22->x = 0;
		Tile_22->y = 0;
		//Tile_22.completion[4] = {false};
		return Tile_22;
	}
	else if(i == 22){
		Tile *Tile_23 = new Tile();
	//	Tile_23.des = {'T', 'L', 'T', 'T', 'P'};
		Tile_23->des.push_back('T');
		Tile_23->des.push_back('L');
       		Tile_23->des.push_back('T');
		Tile_23->des.push_back('T');
		Tile_23->des.push_back('P');
		Tile_23->type.push_back(2);
		Tile_23->type.push_back(3);
		Tile_23->type.push_back(2);
		Tile_23->type.push_back(1);
		Tile_23->type.push_back(2);
		Tile_23->type.push_back(3);
		Tile_23->type.push_back(2);
		Tile_23->type.push_back(3);
		Tile_23->clusterid.push_back(1);
		Tile_23->clusterid.push_back(2);
		Tile_23->clusterid.push_back(3);
		Tile_23->clusterid.push_back(4);
		Tile_23->clusterid.push_back(3);
		Tile_23->clusterid.push_back(2);
		Tile_23->clusterid.push_back(5);
		Tile_23->clusterid.push_back(2);
		Tile_23->tiger.push_back(false);
		Tile_23->tiger.push_back(false);
		Tile_23->tiger.push_back(false);
		Tile_23->tiger.push_back(false);
		Tile_23->tiger.push_back(false);
		Tile_23->tiger.push_back(false);
		Tile_23->tiger.push_back(false);
		Tile_23->tiger.push_back(false);
		//Tile_23.type = {2,3,2,1,2,2,2,3}; // has boar	
		//Tile_23.clusterid = {1,2,3,4,3,2,5,2};
		//Tile_23.tiger = {false,false,false,false,false,false,false,false};
		Tile_23->croc_count = 0;
		Tile_23->Ox = false;
		Tile_23->Boar = true;
		Tile_23->Deer = false;
		Tile_23->Den = false;
		Tile_23->CenterClusterid = 0;
		Tile_23->x = 0;
		Tile_23->y = 0;
		//Tile_23.completion[4] = {false};
		return Tile_23;
	}	
	else if(i == 23){
		Tile *Tile_24 = new Tile();
	//	Tile_24.des = {'T', 'L', 'L', 'T', '-'};
		Tile_24->des.push_back('T');
		Tile_24->des.push_back('L');
       		Tile_24->des.push_back('L');
		Tile_24->des.push_back('T');
		Tile_24->des.push_back('-');
		Tile_24->type.push_back(2);
		Tile_24->type.push_back(3);
		Tile_24->type.push_back(2);
		Tile_24->type.push_back(1);
        Tile_24->type.push_back(1);
		Tile_24->type.push_back(1);
		Tile_24->type.push_back(2);
		Tile_24->type.push_back(3);
		Tile_24->clusterid.push_back(1);
		Tile_24->clusterid.push_back(2);
		Tile_24->clusterid.push_back(3);
		Tile_24->clusterid.push_back(4);
		Tile_24->clusterid.push_back(4);
		Tile_24->clusterid.push_back(4);
		Tile_24->clusterid.push_back(3);
		Tile_24->clusterid.push_back(2);
		Tile_24->tiger.push_back(false);
		Tile_24->tiger.push_back(false);
		Tile_24->tiger.push_back(false);
		Tile_24->tiger.push_back(false);
		Tile_24->tiger.push_back(false);
		Tile_24->tiger.push_back(false);
		Tile_24->tiger.push_back(false);
		Tile_24->tiger.push_back(false);
		//Tile_24.type = {2,3,2,1,1,1,2,3};
		//Tile_24.clusterid = {1,2,3,4,4,4,3,2};
		//Tile_24.tiger = {false,false,false,false,false,false,false,false};
		Tile_24->croc_count = 0;
		Tile_24->Ox = false;
		Tile_24->Boar = false;
		Tile_24->Deer = false;
		Tile_24->Den = false;
		Tile_24->CenterClusterid = 0;
		Tile_24->x = 0;
		Tile_24->y = 0;
		//Tile_24.completion[4] = {false};
		return Tile_24;
	}
	else if(i == 24){
		Tile *Tile_25 = new Tile();
	//	Tile_25.des = {'T', 'L', 'L', 'T', 'B'};
		Tile_25->des.push_back('T');
		Tile_25->des.push_back('L');
       		Tile_25->des.push_back('L');
		Tile_25->des.push_back('T');
		Tile_25->des.push_back('B');
		Tile_25->type.push_back(2);
		Tile_25->type.push_back(3);
		Tile_25->type.push_back(2);
		Tile_25->type.push_back(1);
		Tile_25->type.push_back(1);
		Tile_25->type.push_back(1);
		Tile_25->type.push_back(2);
		Tile_25->type.push_back(3);
		Tile_25->clusterid.push_back(1);
		Tile_25->clusterid.push_back(2);
		Tile_25->clusterid.push_back(3);
		Tile_25->clusterid.push_back(4);
		Tile_25->clusterid.push_back(4);
		Tile_25->clusterid.push_back(3);
		Tile_25->clusterid.push_back(2);
		Tile_25->tiger.push_back(false);
		Tile_25->tiger.push_back(false);
		Tile_25->tiger.push_back(false);
		Tile_25->tiger.push_back(false);
		Tile_25->tiger.push_back(false);
		Tile_25->tiger.push_back(false);
		Tile_25->tiger.push_back(false);
		Tile_25->tiger.push_back(false);
		//Tile_25.type = {2,3,2,1,1,1,2,3}; // has ox
		//Tile_25.clusterid = {1,2,3,4,4,4,3,2};
		//Tile_25.tiger = {false,false,false,false,false,false,false,false};
		Tile_25->croc_count = 0;
		Tile_25->Ox = true;
		Tile_25->Boar = false;
		Tile_25->Deer = false;
		Tile_25->Den = false;
		Tile_25->CenterClusterid = 0;
		Tile_25->x = 0;
		Tile_25->y = 0;
		//Tile_25.completion[4] = {false};
		return Tile_25;
	}
	else if(i == 25){
		Tile *Tile_26 = new Tile();
	//	Tile_26.des = {'L', 'J', 'T', 'J', '-'};
		Tile_26->des.push_back('L');
		Tile_26->des.push_back('J');
       		Tile_26->des.push_back('T');
		Tile_26->des.push_back('J');
		Tile_26->des.push_back('-');
		Tile_26->type.push_back(2);
		Tile_26->type.push_back(1);
		Tile_26->type.push_back(2);
		Tile_26->type.push_back(2);
		Tile_26->type.push_back(2);
		Tile_26->type.push_back(3);
		Tile_26->type.push_back(2);
		Tile_26->type.push_back(2);
		Tile_26->clusterid.push_back(1);
		Tile_26->clusterid.push_back(2);
		Tile_26->clusterid.push_back(3);
		Tile_26->clusterid.push_back(3);
		Tile_26->clusterid.push_back(3);
		Tile_26->clusterid.push_back(4);
		Tile_26->clusterid.push_back(1);
		Tile_26->clusterid.push_back(1);
		Tile_26->tiger.push_back(false);
		Tile_26->tiger.push_back(false);
		Tile_26->tiger.push_back(false);
		Tile_26->tiger.push_back(false);
		Tile_26->tiger.push_back(false);
		Tile_26->tiger.push_back(false);
		Tile_26->tiger.push_back(false);
		Tile_26->tiger.push_back(false);
		//Tile_26.type = {2,1,2,2,2,3,2,2};
		//Tile_26.clusterid = {1,2,3,3,3,4,1,1};
		//Tile_26.tiger = {false,false,false,false,false,false,false,false};
		Tile_26->croc_count = 0;
		Tile_26->Ox = false;
		Tile_26->Boar = false;
		Tile_26->Deer = false;
		Tile_26->Den = false;
		Tile_26->CenterClusterid = 0;
		Tile_26->x = 0;
		Tile_26->y = 0;
		//Tile_26.completion[4] = {false};
		return Tile_26;
	}
	else if(i == 26){
		Tile *Tile_27 = new Tile();
	//	Tile_27.des = {'L', 'J', 'T', 'J', 'D'};
		Tile_27->des.push_back('L');
		Tile_27->des.push_back('J');
       		Tile_27->des.push_back('T');
		Tile_27->des.push_back('J');
		Tile_27->des.push_back('D');
		Tile_27->type.push_back(2);
		Tile_27->type.push_back(1);
		Tile_27->type.push_back(2);
		Tile_27->type.push_back(2);
		Tile_27->type.push_back(2);
		Tile_27->type.push_back(3);
		Tile_27->type.push_back(2);
		Tile_27->type.push_back(2);
		Tile_27->clusterid.push_back(1);
		Tile_27->clusterid.push_back(2);
		Tile_27->clusterid.push_back(3);
		Tile_27->clusterid.push_back(3);
		Tile_27->clusterid.push_back(3);
		Tile_27->clusterid.push_back(4);
		Tile_27->clusterid.push_back(1);
		Tile_27->clusterid.push_back(1);
		Tile_27->tiger.push_back(false);
		Tile_27->tiger.push_back(false);
		Tile_27->tiger.push_back(false);
		Tile_27->tiger.push_back(false);
		Tile_27->tiger.push_back(false);
		Tile_27->tiger.push_back(false);
		Tile_27->tiger.push_back(false);
        Tile_27->tiger.push_back(false);
		//Tile_27.type = {2,1,2,2,2,3,2,2}; // has deer
		//Tile_27.clusterid = {1,2,3,3,3,4,1,1};
		//Tile_27.tiger = {false,false,false,false,false,false,false,false};
		Tile_27->croc_count = 0;
		Tile_27->Ox = false;
		Tile_27->Boar = false;
		Tile_27->Deer = true;
		Tile_27->Den = false;
		Tile_27->CenterClusterid = 0;
		Tile_27->x = 0;
		Tile_27->y = 0;
		//Tile_27.completion[4] = {false};
		return Tile_27;
	}
	else if(i == 27){
		/*tile Tile_28;
		Tile_28.des = {'T', 'L', 'L', 'L', 'C'};
		Tile_28.type = {2,3,2,1,1,1,1,1};
		Tile_28.clusterid = {1,2,3,4,4,4,4,4};
		Tile_28.tiger = {false,false,false,false,false,false,false,false};
		Tile_28->croc_count = 1;
		Tile_28->Ox = false;
		Tile_28->Boar = false;
		Tile_28->Deer = false;
		Tile_28->Den = false;
		Tile_28.x = 0;
		Tile_28->y = 0;
		Tile_28.completion[4] = {false};
		return Tile_28;*/
		Tile *Tile_28 = new Tile();
		//Tile_28.des = {'T', 'L', 'L', 'L', 'C'};
		Tile_28->des.push_back('T');
		Tile_28->des.push_back('L');
       		Tile_28->des.push_back('L');
		Tile_28->des.push_back('L');
		Tile_28->des.push_back('C');
		Tile_28->type.push_back(2);
		Tile_28->type.push_back(3);
		Tile_28->type.push_back(2);
		Tile_28->type.push_back(1);
		Tile_28->type.push_back(1);
		Tile_28->type.push_back(1);
		Tile_28->type.push_back(1);
		Tile_28->type.push_back(1);
		Tile_28->clusterid.push_back(1);
		Tile_28->clusterid.push_back(2);
		Tile_28->clusterid.push_back(3);
		Tile_28->clusterid.push_back(4);
		Tile_28->clusterid.push_back(4);
		Tile_28->clusterid.push_back(4);
		Tile_28->clusterid.push_back(4);
		Tile_28->clusterid.push_back(4);
		Tile_28->tiger.push_back(false);
		Tile_28->tiger.push_back(false);
		Tile_28->tiger.push_back(false);
		Tile_28->tiger.push_back(false);
		Tile_28->tiger.push_back(false);
		Tile_28->tiger.push_back(false);
		Tile_28->tiger.push_back(false);
		Tile_28->tiger.push_back(false);
		//Tile_28.clusterid = {1,2,3,4,4,4,4,4};
		//Tile_28.tiger = {false,false,false,false,false,false,false,false};
		Tile_28->croc_count = 1;
		Tile_28->Ox = false;
		Tile_28->Boar = false;
		Tile_28->Deer = false;
		Tile_28->Den = false;
		Tile_28->CenterClusterid = 0;
		Tile_28->x = 0;
		Tile_28->y = 0;
		//Tile_28.completion[4];
		//Tile_28.completion[0] = false;
		//Tile_28.completion[1] = false;
		//Tile_28.completion[2] = false;
		//Tile_28.completion[3] = false;
		return Tile_28;
        
        //cout<<"we made it"<<endl;
    }else{
        //cout<<"couldnt find tile"<<endl;
    }
    
    
}






