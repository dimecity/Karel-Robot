#include <iostream>
using namespace std;

enum directions {North = 1, West, South, East};

class ur_Robot 
	{
	private:
		int x_pos;
		int y_pos;
		int dir;
		int beepercount;
		int off;
	public:
		ur_Robot (int x_Pos, int y_Pos, directions Dir , int beeperCount);
		void move();
		void turnLeft();
		void pickBeeper();
		void turnOff();
		void putBeeper();
		void print();
		ur_Robot(){
		}
		~ur_Robot(){
		}
	};
	
	void ur_Robot::move() 
	{
		if (off == 1) 
		{
			return;
		}
		else if (x_pos <= 0 || y_pos <= 0) 
		{
			cout << "Karel can't move further" << endl;
			turnOff();
		}
		else if (dir == 1) 
		{
			cout << "Moving North 1 unit" << endl;
			y_pos++;
		}
		else if (dir == 2) 
		{
			if (x_pos - 1 < 1) 
			{
				cout << "Karel can't move further" << endl;
				turnOff();
			}
			else {
				cout << "Moving West 1 unit" << endl;
				x_pos--;
			}
		}
		else if (dir == 3) 
		{
			if (y_pos - 1 < 1) 
			{
				cout <<	"Karel can't move further" << endl;
				turnOff();
			}
			else {
				cout << "Moving South 1 unit" << endl;
				y_pos--;
			}
		}
		else 
		{
			cout << "Moving East 1 unit" << endl;
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
			cout << "Turning left" << endl;
			if (dir + 1 == 5)
			{
				dir = 1;
			}
			else dir++;
		}
	}

	void ur_Robot::turnOff()
	{
		cout << "Turning off" << endl;
		off = 1;
	}
		
	void ur_Robot::putBeeper()
	{
		if (off == 1) 
		{
			return;
		}
		else {
			cout << "Put 1 beeper down" << endl;
			beepercount--;
		}
	}
	
	void ur_Robot::pickBeeper()
	{
		if (off == 1) 
		{
			return;
		}
		else {
			cout << "Pick 1 beeper up" << endl;
			beepercount++;
		}
	}
	
	void ur_Robot::print() {
		cout << "Karel is at " << x_pos << " street, " << y_pos << " avenue and facing ";
		if (dir == 1) 
		{
			cout << "North ";
		}
		else if (dir == 2) 
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
		cout << "with " << beepercount << " beepers" << endl;
	}
	
	ur_Robot::ur_Robot(int x_Pos, int y_Pos, directions Dir, int beeperCount )
	{
		x_pos = x_Pos;
		y_pos = y_Pos;
		dir = Dir;
		beepercount = beeperCount;
	}
	

int main()
{
  ur_Robot karel(1,1,East,10);
  
  karel.print( );
  
  karel.move( );
  karel.pickBeeper( );
  karel.move( );
  karel.print( );
  
  karel.turnLeft( );
  karel.move( );
  karel.putBeeper( );
  karel.putBeeper( );
  karel.turnOff( );
  
  karel.print( );

  return 0;
}

//Name: Nguyen Truong
//Date: 2/20
//Assignment 4
