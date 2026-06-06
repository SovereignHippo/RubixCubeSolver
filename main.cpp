#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"      // Red text
#define GREEN   "\033[32m"      // Green text
#define YELLOW  "\033[33m"      // Yellow text
#define BLUE    "\033[34m"      // Blue text
#define BOLD    "\033[1m"       // Bold text

void printcube();
void rotateSide(int side, int times);
void topLeft();
void middleLeft();
void bottomLeft();
void topRight();
void middleRight();
void bottomRight();
void leftUp();
void middleUp();
void rightUp();
void leftDown();
void middleDown();
void rightDown();
void frontLeft();
void centerLeft();
void backLeft();
void frontRight();
void centerRight();
void backRight();
void MakeAMove(int i);
bool checkIfSolved();
void recordMove(string info);
void recordCube();
void resetCube();


//MY CUBE
//int cube[6][3][3] = {
//	{
//	{1, 1, 1},
//	{1, 1, 1},
//	{1, 1, 1}
//	}, //1 White
//	{
//	{2, 2, 2},
//	{6, 2, 2},
//	{4, 2, 2}
//	}, //2 Green
//	{
//	{4, 4, 6},
//	{5, 3, 3},
//	{2, 5, 6}
//	}, //3 Yellow
//	{
//	{4, 4, 5},
//	{4, 4, 4},
//	{4, 2, 5}
//	}, //4 Blue
//	{
//	{3, 6, 3},
//	{5, 5, 3},
//	{5, 5, 5}
//	}, //5 Orange
//	{
//	{6, 6, 6},
//	{6, 6, 3},
//	{3, 3, 3}
//	} //6 Red
//};

//FULLY SOLVED CUBE
//int cube[6][3][3] = {
//	{
//	{1, 1, 1},
//	{1, 1, 1},
//	{1, 1, 1}
//	}, //1 White
//	{
//	{2, 2, 2},
//	{2, 2, 2},
//	{2, 2, 2}
//	}, //2 Green
//	{
//	{3, 3, 3},
//	{3, 3, 3},
//	{3, 3, 3}
//	}, //3 Yellow
//	{
//	{4, 4, 4},
//	{4, 4, 4},
//	{4, 4, 4}
//	}, //4 Blue
//	{
//	{5, 5, 5},
//	{5, 5, 5},
//	{5, 5, 5}
//	}, //5 Orange
//	{
//	{6, 6, 6},
//	{6, 6, 6},
//	{6, 6, 6}
//	} //6 Red
//};

//ALMOST SOLVED CUBE 3-STEPS
int cube[6][3][3] = {
	{
	{5, 4, 4},
	{5, 1, 6},
	{1, 1, 6}
	}, //1 White
	{
	{2, 2, 1},
	{2, 2, 1},
	{2, 2, 6}
	}, //2 Green
	{
	{2, 2, 6},
	{5, 3, 6},
	{5, 3, 6}
	}, //3 Yellow
	{
	{5, 3, 3},
	{4, 4, 4},
	{4, 4, 4}
	}, //4 Blue
	{
	{3, 5, 5},
	{3, 5, 5},
	{2, 1, 1}
	}, //5 Orange
	{
	{4, 6, 3},
	{1, 6, 3},
	{1, 6, 3}
	} //6 Red
};



int cube2[6][3][3];
int TURNLIMIT = 20;
string record;

int inverseMoveLog = -1;

//[0][0][1] is secound sqaure
//[0][1][0] is first sqare secound row

//My attempt to reduce memory
int i;
int j;
int h;

int a;
int b;
int c;

int temp;
int temp2;

int main() {

	int seed;

	do {

		
		
		cout << "Enter seed: ";
		cin >> seed;
		
		
		if (seed == 0) {
			cout << RED << "Error: Not a valid number!" << RESET << endl;
			//cin.clear();
			//cin.ignore(numeric_limits<streamsize>::max(), '\n');
			
		}

	} while (seed == 0);
	
	
	srand(seed);
	

	int count = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++){
			for (int h = 0; h < 3; h++) {
				count += cube[i][j][h];
			}
		}
	}
	if (count != 189) {
		cout << " Incorect Cube Input";
		return 1; // to check if the cube was correctly inputed
	}
	recordCube();
	//printcube();
	int turns = 0;
	int countAgain = 0;
	int counter = 0;

	cout << GREEN << "Begining Simulation" << RESET << endl;

	do {
		if (checkIfSolved()) {
			break;
		}
		turns = 0;
		record = "";
		resetCube();

		if (countAgain < 1000000) {
			cout << "\rAttempt #" << countAgain;
		}

		//cout << "AGAIN!! - "  << countAgain << endl;
		if (countAgain % 1000000 == 0) {
			cout << "\rAttempt #" << countAgain;
		}
		

		countAgain++;
		
		
		do {
			
			MakeAMove(rand() % 18);
			turns++;
			if (checkIfSolved()) {
				
				break;
			}

		} while (turns < TURNLIMIT);

		
		
	} while (!checkIfSolved());

	

	cout << endl << GREEN <<"Congratulations! Solved in " << turns << " steps" << RESET << endl << record << endl;

	string outputFileName = "RubixCubeSolution";

	string OUTPUTFILE = outputFileName + "-" + to_string(seed) + ".txt";

	cout << "Solution Saved to " << BLUE << OUTPUTFILE << RESET << endl;

	ofstream MyFile(OUTPUTFILE);

	MyFile << "Solved in " << turns << " steps, after " << countAgain << " iterations" << endl << record;

	MyFile.close();

	//All moves are from the perspective of White head on and Green to the left

	return 0;
}
void recordCube() {
	
	for ( i = 0; i < 6; i++) {
		for ( j = 0; j < 3; j++) {
			for ( h = 0; h < 3; h++) {
				cube2[i][j][h] = cube[i][j][h];
			}
		}
	}
}
void resetCube() {
	for ( i = 0; i < 6; i++) {
		for ( j = 0; j < 3; j++) {
			for ( h = 0; h < 3; h++) {
				cube[i][j][h] = cube2[i][j][h];
			}
		}
	}
}

void MakeAMove(int i) {
	if (inverseMoveLog == i) {
		MakeAMove(rand() % 18);
		return;
	}
	switch (i)
	{
	case (0):
		topLeft();
		recordMove("Top Left ");
		inverseMoveLog = 3;
		break;
	case (1):
		middleLeft();
		recordMove("Middle Left ");
		inverseMoveLog = 4;
		break;
	case (2):
		bottomLeft();
		recordMove("Bottom Left ");
		inverseMoveLog = 5;
		break;
	case (3):
		topRight();
		recordMove("Top Right ");
		inverseMoveLog = 0;
		break;
	case (4):
		middleRight();
		recordMove("Middle Right ");
		inverseMoveLog = 1;
		break;
	case (5):
		bottomRight();
		recordMove("Bottom Right ");
		inverseMoveLog = 2;
		break;
	case(6):
		leftUp();
		recordMove("Left UP ");
		inverseMoveLog = 9;
		break;
	case (7):
		middleUp();
		recordMove("Middle UP ");
		inverseMoveLog = 10;
		break;
	case (8):
		rightUp();
		recordMove("Right UP ");
		inverseMoveLog = 11;
		break;
	case (9):
		leftDown();
		recordMove("left Down ");
		inverseMoveLog = 6;
		break;
	case(10):
		middleDown();
		recordMove("Middle Down ");
		inverseMoveLog = 7;
		break;
	case(11):
		rightDown();
		recordMove("Right Down ");
		inverseMoveLog = 8;
		break;
	case(12):
		frontLeft();
		recordMove("Front Left ");
		inverseMoveLog = 15;
		break;
	case(13):
		centerLeft();
		recordMove("Center Left ");
		inverseMoveLog = 16;
		break;
	case(14):
		backLeft();
		recordMove("Back Left ");
		inverseMoveLog = 17;
		break;
	case(15):
		frontRight();
		recordMove("Front Right ");
		inverseMoveLog = 12;
		break;
	case(16):
		centerRight();
		recordMove("Center Right ");
		inverseMoveLog = 13;
		break;
	case(17):
		backRight();
		recordMove("Back Right ");
		inverseMoveLog = 14;
	default:
		break;
	}
}

bool checkIfSolved() {
	 temp2 = cube[0][0][0];
	for ( i = 0; i < 6; i++) {
		for ( j = 0; j < 3; j++) {
			for ( h = 0; h < 3; h++) {
				//cout << i << ", " << j << ", " << h << endl;
				if (cube[i][j][h] != temp2) {
					return false;
				}
			}
		}
		if (i < 6) {
			temp2 = cube[i + 1][0][0];
		}
	}
	return true;
}

void recordMove(string info) {
	record += info;
	record += "\n";
	//cout << info << endl;
}

void printcube() {
	cout << "printing cube" << endl;
	for ( i = 0; i < 6; i++) {
		for ( j = 0; j < 3; j++) {
			for ( h = 0; h < 3; h++) {
				cout << cube[i][j][h] << ", ";
			}
			cout << endl;
		}
		cout << endl;
	}
}

void rotateSide(int side, int times) {
	//rotate counterclockwise do times = 1
	//rotate clockwise do times = 3
	for ( h = 0; h < times; h++) {

		for ( i = 0; i < 3 / 2; i++) {
			for ( j = i; j < 3 - i - 1; j++) {
				 temp = cube[side][i][j];
				cube[side][i][j] = cube[side][j][3 - 1 - i];
				cube[side][j][3 - 1 - i] = cube[side][3 - 1 - i][3 - 1 - j];
				cube[side][3 - 1 - i][3 - 1 - j] = cube[side][3 - 1 - j][i];
				cube[side][3 - 1 - j][i] = temp;
			}
		}


	}
}
//left and right
void topLeft() {
	//int a, b, c;
	//save side 0
	a = cube[0][0][0];
	b = cube[0][0][1];
	c = cube[0][0][2];
	//side 3 to side 0
	cube[0][0][0] = cube[3][0][0];
	cube[0][0][1] = cube[3][0][1];
	cube[0][0][2] = cube[3][0][2];
	//side 2 to side 3
	cube[3][0][0] = cube[2][0][0];
	cube[3][0][1] = cube[2][0][1];
	cube[3][0][2] = cube[2][0][2];
	//side 1 to side 2
	cube[2][0][0] = cube[1][0][0];
	cube[2][0][1] = cube[1][0][1];
	cube[2][0][2] = cube[1][0][2];
	//a,b,c to side 1
	cube[1][0][0] = a;
	cube[1][0][1] = b;
	cube[1][0][2] = c;
	//Roate top clockwise
	rotateSide(4, 3);
}
void middleLeft() {
	//int a, b, c;
	//save side 0
	a = cube[0][1][0];
	b = cube[0][1][1];
	c = cube[0][1][2];
	//side 3 to side 0
	cube[0][1][0] = cube[3][1][0];
	cube[0][1][1] = cube[3][1][1];
	cube[0][1][2] = cube[3][1][2];
	//side 2 to side 3
	cube[3][1][0] = cube[2][1][0];
	cube[3][1][1] = cube[2][1][1];
	cube[3][1][2] = cube[2][1][2];
	//side 1 to side 2
	cube[2][1][0] = cube[1][1][0];
	cube[2][1][1] = cube[1][1][1];
	cube[2][1][2] = cube[1][1][2];
	//a,b,c to side 1
	cube[1][1][0] = a;
	cube[1][1][1] = b;
	cube[1][1][2] = c;
	//Roate top couterclockwise
	
}
void bottomLeft() {
	//int a, b, c;
	//save side 0
	a = cube[0][2][0];
	b = cube[0][2][1];
	c = cube[0][2][2];
	//side 3 to side 0
	cube[0][2][0] = cube[3][2][0];
	cube[0][2][1] = cube[3][2][1];
	cube[0][2][2] = cube[3][2][2];
	//side 2 to side 3
	cube[3][2][0] = cube[2][2][0];
	cube[3][2][1] = cube[2][2][1];
	cube[3][2][2] = cube[2][2][2];
	//side 1 to side 2
	cube[2][2][0] = cube[1][2][0];
	cube[2][2][1] = cube[1][2][1];
	cube[2][2][2] = cube[1][2][2];
	//a,b,c to side 1
	cube[1][2][0] = a;
	cube[1][2][1] = b;
	cube[1][2][2] = c;
	//Roate bottom couterclockwise
	rotateSide(5, 1);
}
void topRight() {
	//int a, b, c;
	//save side 0
	a = cube[0][0][0];
	b = cube[0][0][1];
	c = cube[0][0][2];
	//side 1 to side 0
	cube[0][0][0] = cube[1][0][0];
	cube[0][0][1] = cube[1][0][1];
	cube[0][0][2] = cube[1][0][2];
	//side 2 to side 1
	cube[1][0][0] = cube[2][0][0];
	cube[1][0][1] = cube[2][0][1];
	cube[1][0][2] = cube[2][0][2];
	//side 3 to side 2
	cube[2][0][0] = cube[3][0][0];
	cube[2][0][1] = cube[3][0][1];
	cube[2][0][2] = cube[3][0][2];
	//a,b,c to side 3
	cube[3][0][0] = a;
	cube[3][0][1] = b;
	cube[3][0][2] = c;
	//Roate bottom couterclockwise
	rotateSide(4, 1);
}
void middleRight() {
	//int a, b, c;
	//save side 0
	a = cube[0][1][0];
	b = cube[0][1][1];
	c = cube[0][1][2];
	//side 1 to side 0
	cube[0][1][0] = cube[1][1][0];
	cube[0][1][1] = cube[1][1][1];
	cube[0][1][2] = cube[1][1][2];
	//side 2 to side 1
	cube[1][1][0] = cube[2][1][0];
	cube[1][1][1] = cube[2][1][1];
	cube[1][1][2] = cube[2][1][2];
	//side 3 to side 2
	cube[2][1][0] = cube[3][1][0];
	cube[2][1][1] = cube[3][1][1];
	cube[2][1][2] = cube[3][1][2];
	//a,b,c to side 3
	cube[3][1][0] = a;
	cube[3][1][1] = b;
	cube[3][1][2] = c;
	
}
void bottomRight() {
	//int a, b, c;
	//save side 0
	a = cube[0][2][0];
	b = cube[0][2][1];
	c = cube[0][2][2];
	//side 1 to side 0
	cube[0][2][0] = cube[1][2][0];
	cube[0][2][1] = cube[1][2][1];
	cube[0][2][2] = cube[1][2][2];
	//side 2 to side 1
	cube[1][2][0] = cube[2][2][0];
	cube[1][2][1] = cube[2][2][1];
	cube[1][2][2] = cube[2][2][2];
	//side 3 to side 2
	cube[2][2][0] = cube[3][2][0];
	cube[2][2][1] = cube[3][2][1];
	cube[2][2][2] = cube[3][2][2];
	//a,b,c to side 3
	cube[3][2][0] = a;
	cube[3][2][1] = b;
	cube[3][2][2] = c;
	//Roate bottom clockwise
	rotateSide(5, 3);
}

// up and down
void leftUp() {
	//int a, b, c;
	//save side 0
	a = cube[0][0][0];
	b = cube[0][1][0];
	c = cube[0][2][0];
	//side 5 to side 0
	cube[0][0][0] = cube[5][0][0];
	cube[0][1][0] = cube[5][1][0];
	cube[0][2][0] = cube[5][2][0];
	//side 2 to side 5
	cube[5][0][0] = cube[2][2][2];
	cube[5][1][0] = cube[2][1][2];
	cube[5][2][0] = cube[2][0][2];
	//side 4 to side 2
	cube[2][0][2] = cube[4][2][0];
	cube[2][1][2] = cube[4][1][0];
	cube[2][2][2] = cube[4][0][0];
	//a,b,c to side 4
	cube[4][0][0] = a;
	cube[4][1][0] = b;
	cube[4][2][0] = c;
	//Roate 1 counterclockwise
	rotateSide(1, 1);
}
void middleUp() {
	//int a, b, c;
	//save side 0
	a = cube[0][0][1];
	b = cube[0][1][1];
	c = cube[0][2][1];
	//side 5 to side 0
	cube[0][0][1] = cube[5][0][1];
	cube[0][1][1] = cube[5][1][1];
	cube[0][2][1] = cube[5][2][1];
	//side 2 to side 5
	cube[5][0][1] = cube[2][2][1];
	cube[5][1][1] = cube[2][1][1];
	cube[5][2][1] = cube[2][0][1];
	//side 4 to side 2
	cube[2][0][1] = cube[4][2][1];
	cube[2][1][1] = cube[4][1][1];
	cube[2][2][1] = cube[4][0][1];
	//a,b,c to side 4
	cube[4][0][1] = a;
	cube[4][1][1] = b;
	cube[4][2][1] = c;
	
}
void rightUp() {
	//int a, b, c;
	//save side 0
	a = cube[0][0][2];
	b = cube[0][1][2];
	c = cube[0][2][2];
	//side 5 to side 0
	cube[0][0][2] = cube[5][0][2];
	cube[0][1][2] = cube[5][1][2];
	cube[0][2][2] = cube[5][2][2];
	//side 2 to side 5
	cube[5][0][2] = cube[2][2][0];
	cube[5][1][2] = cube[2][1][0];
	cube[5][2][2] = cube[2][0][0];
	//side 4 to side 2
	cube[2][0][0] = cube[4][2][2];
	cube[2][1][0] = cube[4][1][2];
	cube[2][2][0] = cube[4][0][2];
	//a,b,c to side 4
	cube[4][0][2] = a;
	cube[4][1][2] = b;
	cube[4][2][2] = c;
	//Roate 3 clockwise
	rotateSide(3, 3);
}
void leftDown() {
	//int a, b, c;
	//save side 0
	a = cube[0][0][0];
	b = cube[0][1][0];
	c = cube[0][2][0];
	//side 4 to side 0
	cube[0][0][0] = cube[4][0][0];
	cube[0][1][0] = cube[4][1][0];
	cube[0][2][0] = cube[4][2][0];
	//side 2 to side 4
	cube[4][0][0] = cube[2][2][2];
	cube[4][1][0] = cube[2][1][2];
	cube[4][2][0] = cube[2][0][2];
	//side 5 to side 2
	cube[2][0][2] = cube[5][2][0];
	cube[2][1][2] = cube[5][1][0];
	cube[2][2][2] = cube[5][0][0];
	//a,b,c to side 5
	cube[5][0][0] = a;
	cube[5][1][0] = b;
	cube[5][2][0] = c;
	//Roate 1 clockwise
	rotateSide(1, 3);
}
void middleDown() {
	//int a, b, c;
	//save side 0
	a = cube[0][0][1];
	b = cube[0][1][1];
	c = cube[0][2][1];
	//side 4 to side 0
	cube[0][0][1] = cube[4][0][1];
	cube[0][1][1] = cube[4][1][1];
	cube[0][2][1] = cube[4][2][1];
	//side 2 to side 4
	cube[4][0][1] = cube[2][2][1];
	cube[4][1][1] = cube[2][1][1];
	cube[4][2][1] = cube[2][0][1];
	//side 5 to side 2
	cube[2][0][1] = cube[5][2][1];
	cube[2][1][1] = cube[5][1][1];
	cube[2][2][1] = cube[5][0][1];
	//a,b,c to side 5
	cube[5][0][1] = a;
	cube[5][1][1] = b;
	cube[5][2][1] = c;

}
void rightDown() {
	//int a, b, c;
	//save side 0
	a = cube[0][0][2];
	b = cube[0][1][2];
	c = cube[0][2][2];
	//side 4 to side 0
	cube[0][0][2] = cube[4][0][2];
	cube[0][1][2] = cube[4][1][2];
	cube[0][2][2] = cube[4][2][2];
	//side 2 to side 4
	cube[4][0][2] = cube[2][2][0];
	cube[4][1][2] = cube[2][1][0];
	cube[4][2][2] = cube[2][0][0];
	//side 5 to side 2
	cube[2][0][0] = cube[5][2][2];
	cube[2][1][0] = cube[5][1][2];
	cube[2][2][0] = cube[5][0][2];
	//a,b,c to side 4
	cube[5][0][2] = a;
	cube[5][1][2] = b;
	cube[5][2][2] = c;
	//Roate 3 counterclockwise
	rotateSide(3, 1);
}

//depth turns
void frontLeft() {
	//int a, b, c;
	//save side 3
	a = cube[3][0][0];
	b = cube[3][1][0];
	c = cube[3][2][0];
	//side 5 to side 3
	cube[3][0][0] = cube[5][0][2];
	cube[3][1][0] = cube[5][0][1];
	cube[3][2][0] = cube[5][0][0];
	//side 1 to side 5
	cube[5][0][0] = cube[1][0][2];
	cube[5][0][1] = cube[1][1][2];
	cube[5][0][2] = cube[1][2][2];
	//side 4 to side 1
	cube[1][0][2] = cube[4][2][2];
	cube[1][1][2] = cube[4][2][1];
	cube[1][2][2] = cube[4][2][0];
	//a,b,c to side 4
	cube[4][2][0] = a;
	cube[4][2][1] = b;
	cube[4][2][2] = c;
	//Roate 0 counterclockwise
	rotateSide(0, 1);
}
void centerLeft() {
	//int a, b, c;
	//save side 3
	a = cube[3][0][1];
	b = cube[3][1][1];
	c = cube[3][2][1];
	//side 5 to side 3
	cube[3][0][1] = cube[5][1][2];
	cube[3][1][1] = cube[5][1][1];
	cube[3][2][1] = cube[5][1][0];
	//side 1 to side 5
	cube[5][1][0] = cube[1][0][1];
	cube[5][1][1] = cube[1][1][1];
	cube[5][1][2] = cube[1][2][1];
	//side 4 to side 1
	cube[1][0][1] = cube[4][1][2];
	cube[1][1][1] = cube[4][1][1];
	cube[1][2][1] = cube[4][1][0];
	//a,b,c to side 4
	cube[4][1][0] = a;
	cube[4][1][1] = b;
	cube[4][1][2] = c;
	
}
void backLeft() {
	//int a, b, c;
	//save side 3
	a = cube[3][0][2];
	b = cube[3][1][2];
	c = cube[3][2][2];
	//side 5 to side 3
	cube[3][0][2] = cube[5][2][2];
	cube[3][1][2] = cube[5][2][1];
	cube[3][2][2] = cube[5][2][0];
	//side 1 to side 5
	cube[5][2][0] = cube[1][0][0];
	cube[5][2][1] = cube[1][1][0];
	cube[5][2][2] = cube[1][2][0];
	//side 4 to side 1
	cube[1][0][0] = cube[4][0][2];
	cube[1][1][0] = cube[4][0][1];
	cube[1][2][0] = cube[4][0][0];
	//a,b,c to side 4
	cube[4][0][0] = a;
	cube[4][0][1] = b;
	cube[4][0][2] = c;
	//Roate 2 clockwise
	rotateSide(2, 3);
}
void frontRight() {
	//int a, b, c;
	//save side 3
	a = cube[3][0][0];
	b = cube[3][1][0];
	c = cube[3][2][0];
	//side 4 to side 3
	cube[3][0][0] = cube[4][2][0];
	cube[3][1][0] = cube[4][2][1];
	cube[3][2][0] = cube[4][2][2];
	//side 1 to side 4
	cube[4][2][2] = cube[1][0][2];
	cube[4][2][1] = cube[1][1][2];
	cube[4][2][0] = cube[1][2][2];
	//side 5 to side 1
	cube[1][0][2] = cube[5][0][0];
	cube[1][1][2] = cube[5][0][1];
	cube[1][2][2] = cube[5][0][2];
	//a,b,c to side 5
	cube[5][0][0] = a;
	cube[5][0][1] = b;
	cube[5][0][2] = c;
	//Roate 0 clockwise
	rotateSide(0, 3);
}
void centerRight() {
	//int a, b, c;
	//save side 3
	a = cube[3][0][1];
	b = cube[3][1][1];
	c = cube[3][2][1];
	//side 4 to side 3
	cube[3][0][1] = cube[4][1][0];
	cube[3][1][1] = cube[4][1][1];
	cube[3][2][1] = cube[4][1][2];
	//side 1 to side 4
	cube[4][1][2] = cube[1][0][1];
	cube[4][1][1] = cube[1][1][1];
	cube[4][1][0] = cube[1][2][1];
	//side 5 to side 1
	cube[1][0][1] = cube[5][1][0];
	cube[1][1][1] = cube[5][1][1];
	cube[1][2][1] = cube[5][1][2];
	//a,b,c to side 5
	cube[5][1][2] = a;
	cube[5][1][1] = b;
	cube[5][1][0] = c;
}
void backRight() {
	//int a, b, c;
	//save side 3
	a = cube[3][0][2];
	b = cube[3][1][2];
	c = cube[3][2][2];
	//side 4 to side 3
	cube[3][0][2] = cube[4][0][0];
	cube[3][1][2] = cube[4][0][1];
	cube[3][2][2] = cube[4][0][2];
	//side 1 to side 4
	cube[4][0][2] = cube[1][0][0];
	cube[4][0][1] = cube[1][1][0];
	cube[4][0][0] = cube[1][2][0];
	//side 5 to side 1
	cube[1][0][0] = cube[5][2][0];
	cube[1][1][0] = cube[5][2][1];
	cube[1][2][0] = cube[5][2][2];
	//a,b,c to side 5
	cube[5][2][2] = a;
	cube[5][2][1] = b;
	cube[5][2][0] = c;
	//Roate 2 counterclockwise
	rotateSide(2, 1);
}