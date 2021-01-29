#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

enum directions {North = 1, West, South, East};


class WORLD {
	private: 
		int street;
		int avenue;
		int beeperworld;
		int direction;
		int wallNorth[10][10];
		int wallWest[10][10];
		int wallSouth[10][10];
		int wallEast[10][10];
		int wallON[10][10];			
		int numBeeper[10][10];
	public:
		void clearBeeper (int avenue, int street);
		void placeBeeper (int avenue, int street, int beeper);
		void increBeeper (int avenue, int street);
		void getBeepersCount (int avenue, int street);
		void wallNorthSouth (int avenue, int street);
		void wallWestEast (int avenue, int street);
		void clearAllWall (int avenue, int street);
		void initialWorld();
		WORLD () {
		}
		~WORLD() {
		}
		friend class ur_Robot;
};



void WORLD::clearBeeper(int avenue, int street) {				
	numBeeper[avenue][street] = 0;														
}

void WORLD::placeBeeper (int avenue, int street, int beeperworld) {				
	numBeeper[avenue][street] = beeperworld;														 
}

void WORLD::increBeeper(int avenue, int street) {	
	numBeeper[avenue][street]++;					
}

void WORLD::getBeepersCount (int avenue, int street) {
}

void WORLD::wallNorthSouth(int avenue, int street) {
	wallEast[avenue][street] = 4;					
	wallWest[avenue + 1][street] = 2;				 	
	wallON[avenue][street] = 1;
	wallON[avenue + 1][street] = 1;
}

void WORLD::wallWestEast(int avenue, int street) {
	wallNorth[avenue][street] = 1;					 
	wallSouth[avenue][street + 1] = 3;						
	wallON[avenue][street] = 1;
	wallON[avenue][street+1] = 1;
}

void WORLD::clearAllWall(int avenue, int street) {	
	wallON[avenue][street] = 0;
}

void WORLD::initialWorld() {						// World sample with 4 beepers at intersection 2,1 and a horizontal wall at 1,3		
	placeBeeper(2,1,4);
	wallWestEast(1,3);			
}

WORLD sample;

class ur_Robot 
	{
	private:
		int x_pos;
		int y_pos;
		int dir;
		int beeperrobot;
		int off;
	public:
		ur_Robot (int x_Pos, int y_Pos, directions Dir , int beeperCount);
		void move();
		void turnLeft();
		void pickBeeper();
		void turnOff();
		void putBeeper();
		static void printWorld();
		void printAllRobot();	
		ur_Robot(){}
		~ur_Robot(){
		}
		friend class WORLD;	
	};
	


void ur_Robot::move() 
{	
	if (off == 1) 
	{
		return;
	}
	else if ((sample.wallON[x_pos][y_pos] == 1) && (dir == sample.wallNorth[x_pos][y_pos] || dir == sample.wallWest[x_pos][y_pos] 
	|| dir == sample.wallSouth[x_pos][y_pos] || dir == sample.wallWest[x_pos][y_pos]))
	{
		cout << "Error: Front is not clear. Robot can't move further. Turning off." << endl;
		turnOff();
	}
	else if (x_pos <= 0 || y_pos <= 0)
	{
		cout << "Error: Robot can't move out of bounds. Turning off" << endl;
		turnOff();
	}
	else if (dir == 1) 
	{
		y_pos++;
	}
	else if (dir == 2) 
	{
		if (x_pos - 1 < 1) 
		{
			cout << "Error: Robot can't move out of bounds. Turning off" << endl;
			turnOff();
		}
		else {
			x_pos--;
		}
	}
	else if (dir == 3) 
	{
		if (y_pos - 1 < 1) 
		{
			cout <<	"Error: Robot can't move out of bounds. Turning off." << endl;
			turnOff();
		}
		else {
			y_pos--;
		}
	}
	else 
	{
		x_pos++;
	}
}

void ur_Robot::turnLeft()
{
	if (off == 1) 
	{
		return;
	}
	else {
		if (dir + 1 == 5)
		{
		dir = 1;
		}
		else dir++;
	}
}

void ur_Robot::turnOff()
{
	off = 1;
}

void ur_Robot::putBeeper()
{
	if (off == 1) 
	{
		return;
	}
	else {
		beeperrobot--;
		sample.numBeeper[x_pos][y_pos] ++;
	}
}
	
void ur_Robot::pickBeeper()
{
	if (off == 1) 
	{
		return;
	}
	else {
		beeperrobot++;
		sample.numBeeper[x_pos][y_pos]--;
	}
}
	
void ur_Robot::printAllRobot() {
	cout << endl << "Robot's status: " << endl;
	cout << "Karel is at " << x_pos << " street, " << y_pos << " avenue and facing ";
	if (dir == 1) 
	{
		cout << "North ";
	}		else if (dir == 2) 
	{
		cout << "West ";
	}
	else if (dir == 3) 
	{
		cout << "South ";
	}
	else 
	{
		cout << "East ";
	}
	cout << "with " << beeperrobot << " beepers" << endl;	
}


void ur_Robot::printWorld() {
	int i, j;
	int emptywall = 0;
	int emptybeeper = 0;
	cout << endl << "World's status: " << endl;
	for (i = 1; i <= 10; i++) {
		for(j = 1; j <= 10; j++) {
			if (sample.numBeeper[i][j] >= 1) {
				cout << "There is/are " << sample.numBeeper[i][j] << " beeper(s) at " << i << " avenue "  << j << " street " << endl;
				emptybeeper = 1;
			}
			if (sample.wallON[i][j] == 1) {
				if (sample.wallNorth[i][j] == 1) {
					cout << "There is a horizontal wall between " << i << " avenue " << j << " street and " <<  i << " avenue " << j + 1 << " street" << endl;
				}
				if (sample.wallEast[i][j] == 4) {
						cout << "There is a vertical wall between " << i << " avenue " << j << " street and " << i + 1 << " avenue " << j  << " street" << endl;
				}
				emptywall = 1;
			}
		}
	}
	if (emptybeeper == 0) {
		cout << "There isn't any beeper in this world" << endl;
	}
	if (emptywall == 0) {
		cout << "There isn't any wall in this world" << endl;
	}
	cout << endl;
}

ur_Robot::ur_Robot(int x_Pos, int y_Pos, directions Dir, int beeperCount )
{
	x_pos = x_Pos;
	y_pos = y_Pos;
	dir = Dir;
	beeperrobot = beeperCount;
}


int main() {
	sample.initialWorld();
	ur_Robot karel(1,1,East,10);
	ur_Robot karel2(1,1,East,0);
	ur_Robot karel3(1,1, North, 0);
	
	karel.printAllRobot();  
	karel2.printAllRobot(); 
	karel3.printAllRobot();
	ur_Robot::printWorld();
	
	karel.move( );
	karel.putBeeper( );
	karel.move( );
	karel.putBeeper( );
	karel.putBeeper( );
	karel.move( );
	karel.putBeeper( );
	karel.turnLeft( );
	karel.move( );
	karel.move( );
	karel.turnOff( );
	
	cout << endl << "First robot: ";
	karel.printAllRobot();  
	ur_Robot::printWorld();
	
	karel2.move( );
	karel2.pickBeeper( );
	karel2.move( );
	karel2.pickBeeper( );
	karel2.move( );
	karel2.pickBeeper( );
	karel2.turnLeft( );
	karel2.turnLeft( );
	karel2.turnLeft( );
	karel2.move( );
	karel2.move( );
	
	cout << endl << "Second robot: ";
	karel2.printAllRobot();  
	ur_Robot::printWorld();
	
	karel2.turnOff( );		  
	karel2.turnLeft( );
	karel2.turnLeft( );
	karel2.move( );
	karel2.move( );
	
	karel3.move();
	karel3.move();
	karel3.move();
	
	cout << endl << "Third robot: ";
	karel3.printAllRobot();
	
	ur_Robot::printWorld();
		
	return 0;
}

/*Name: Nguyen Truong
Assignment 6
Date: 3/25
*/
