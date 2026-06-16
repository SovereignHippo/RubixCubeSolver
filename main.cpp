#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <thread>

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"      // Red text
#define GREEN   "\033[32m"      // Green text
#define YELLOW  "\033[33m"      // Yellow text
#define BLUE    "\033[34m"      // Blue text
#define BOLD    "\033[1m"       // Bold text

void printcube(int cube[6][3][3]);
void rotateSide(int side, int times, int cube[6][3][3]);
void topLeft(int cube[6][3][3]);
void middleLeft(int cube[6][3][3]);
void bottomLeft(int cube[6][3][3]);
void topRight(int cube[6][3][3]);
void middleRight(int cube[6][3][3]);
void bottomRight(int cube[6][3][3]);
void leftUp(int cube[6][3][3]);
void middleUp(int cube[6][3][3]);
void rightUp(int cube[6][3][3]);
void leftDown(int cube[6][3][3]);
void middleDown(int cube[6][3][3]);
void rightDown(int cube[6][3][3]);
void frontLeft(int cube[6][3][3]);
void centerLeft(int cube[6][3][3]);
void backLeft(int cube[6][3][3]);
void frontRight(int cube[6][3][3]);
void centerRight(int cube[6][3][3]);
void backRight(int cube[6][3][3]);
void MakeAMove(int i, int cube[6][3][3]);
bool checkIfSolved(int cube[6][3][3]);
void recordMove(int turnNumber, string& record);
void recordCube();
void resetCube();
void UnMakeAMove(int i, int cube[6][3][3]);
bool TryToSolve(int turnNumber, int cube[6][3][3], string& record);
bool TryToSolve(int turnNumber, int cube[6][3][3], string& record, int startingIndex);
void CopyCube(int newCube[6][3][3], int oldCube[6][3][3]);
void PrintResults(string record, int startingIndex);
void StartThread(int startingIndex, int cube[6][3][3],string& record);


//MY CUBE
int baseCube[6][3][3] = {
	{
	{1, 1, 1},
	{1, 1, 1},
	{1, 1, 1}
	}, //1 White
	{
	{3, 6, 2},
	{3, 2, 2},
	{6, 4, 2}
	}, //2 Green
	{
	{3, 3, 5},
	{3, 3, 4},
	{5, 5, 3}
	}, //3 Yellow
	{
	{4, 2, 2},
	{4, 4, 2},
	{4, 5, 4}
	}, //4 Blue
	{
	{2, 6, 6},
	{4, 5, 6},
	{5, 5, 5}
	}, //5 Orange
	{
	{6, 6, 6},
	{5, 6, 2},
	{4, 3, 3}
	} //6 Red
};

//FULLY SOLVED CUBE
//int baseCube[6][3][3] = {
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
//int baseCube[6][3][3] = {
//	{
//	{1, 1, 5},
//	{6, 1, 5},
//	{6, 4, 4}
//	}, //1 White
//	{
//	{2, 2, 5},
//	{2, 2, 1},
//	{2, 2, 1}
//	}, //2 Green
//	{
//	{6, 3, 5},
//	{6, 3, 5},
//	{2, 2, 5}
//	}, //3 Yellow
//	{
//	{4, 4, 4},
//	{4, 4, 4},
//	{6, 3, 3}
//	}, //4 Blue
//	{
//	{1, 5, 3},
//	{1, 5, 3},
//	{4, 5, 3}
//	}, //5 Orange
//	{
//	{2, 1, 1},
//	{3, 6, 6},
//	{3, 6, 6}
//	} //6 Red
//};



int cube2[6][3][3];
int cubeCopy1[6][3][3];
int cubeCopy2[6][3][3];
int cubeCopy3[6][3][3];
int cubeCopy4[6][3][3];
int TURNLIMIT = 15;
string record1;
string record2;
string record3;
string record4;

int inverseMoveLog = -1;

//[0][0][1] is secound sqaure
//[0][1][0] is first sqare secound row

////My attempt to reduce memory //Bad for multi-threading
//int i;
//int j;
//int h;
//
//int a;
//int b;
//int c;
//
//int temp;
//int temp2;

//unsigned long long totalMovesTried = 0;
int turns = 0;

int main(int argc, char* argv[]) {

	if (argc > 2) {
		cerr << RED << "Error: Too many arguments, only argument is seed" << RESET << endl;
	}
	

	int count = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++){
			for (int h = 0; h < 3; h++) {
				count += baseCube[i][j][h];
			}
		}
	}
	if (count != 189) {
		cout << " Incorect Cube Input";
		return 1; // to check if the cube was correctly inputed
	}
	recordCube();
	//printcube();
	
	
	int counter = 0;

	cout << GREEN << "Begining Simulation" << RESET << endl;

	record1 = "";
	record2 = "";
	record3 = "";
	record4 = "";


	CopyCube(cubeCopy1, baseCube);
	CopyCube(cubeCopy2, baseCube);
	CopyCube(cubeCopy3, baseCube);
	CopyCube(cubeCopy4, baseCube);

	thread t(StartThread, 1, cubeCopy1, ref(record1));
	thread t2(StartThread, 3, cubeCopy2, ref(record2));
	thread t3(StartThread, 5, cubeCopy3, ref(record3));
	thread t4(StartThread, 7, cubeCopy4, ref(record4));

	t.join();
	t2.detach();
	t3.detach();
	t4.detach();
	
	

	//do {
	//	if (checkIfSolved()) {
	//		break;
	//	}
	//	turns = 0;
	//	record = "";
	//	resetCube();

	//	if (countAgain < 1000000) {
	//		cout << "\rAttempt #" << countAgain;
	//	}

	//	//cout << "AGAIN!! - "  << countAgain << endl;
	//	if (countAgain % 100000 == 0) {
	//		cout << "\rAttempt #" << countAgain;
	//	}
	//	

	//	countAgain++;
	//	
	//	


	//	/*do {
	//		
	//		MakeAMove(rand() % 18);
	//		turns++;
	//		if (checkIfSolved()) {
	//			
	//			break;
	//		}

	//	} while (turns < TURNLIMIT);*/

		
		
	/*} while (!checkIfSolved());*/

	
	cerr << "Main has finished" << endl;
	

	return 0;
}

void StartThread(int startingIndex, int cube[6][3][3],string& record) {
	if (TryToSolve(1, cube, record, startingIndex)) {
		cerr << "Winner: " << startingIndex << endl;
		PrintResults(record, startingIndex);
		printcube(cube);
	}
	
}

bool TryToSolve(int turnNumber, int cube[6][3][3],string& record) {
	return TryToSolve(turnNumber, cube, record, 0);
}

bool TryToSolve(int turnNumber, int cube[6][3][3], string& record, int startingIndex) {
	if (turnNumber > TURNLIMIT) return false;

	if (turnNumber == 1 && startingIndex !=0) {
		cerr << "progress-" << startingIndex << ": " << 0 << "%" <<endl;
	}

	for (int i = startingIndex; i < 18; i++) {

		MakeAMove(i, cube);
		//totalMovesTried++;
		
		if (checkIfSolved(cube)) {
			recordMove(i, record);
			cerr << endl << "SOLVED IT! at " << i << endl;
			return true;
		}
		if (TryToSolve((turnNumber + 1), cube, record)) {
			recordMove(i, record);
			cerr << "They Solved it at my " << i << endl;
			return true;
		}
		UnMakeAMove(i, cube);

		if (turnNumber == 1 && startingIndex != 0) {
			cerr << "progress-"<< startingIndex <<": " << ((i + 1) / 18) * 100 << " % "<<endl;
		}
		
	}
	
	
	
	
	return false;
}

void CopyCube(int newCube[6][3][3], int oldCube[6][3][3]) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int h = 0; h < 3; h++) {
				newCube[i][j][h] = oldCube[i][j][h];
			}
		}
	}
}

void PrintResults(string record, int startingIndex) {
	cerr << endl << GREEN << "Congratulations! Solved!" << RESET << endl << record << endl;

	string outputFileName = "RubixCubeSolution";

	string OUTPUTFILE = outputFileName + "-" + to_string(startingIndex) + ".txt";

	cerr << "Solution Saved to " << BLUE << OUTPUTFILE << RESET << endl;

	ofstream MyFile(OUTPUTFILE);

	MyFile << "Solved in " << turns << " steps" << endl << record;

	MyFile.close();

	//All moves are from the perspective of White head on and Green to the left
}



void recordCube() {
	
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int h = 0; h < 3; h++) {
				cube2[i][j][h] = baseCube[i][j][h];
			}
		}
	}
}
void resetCube() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int h = 0; h < 3; h++) {
				baseCube[i][j][h] = cube2[i][j][h];
			}
		}
	}
}

void MakeAMove(int i, int cube[6][3][3]) {
	//if (inverseMoveLog == i) {
	//	//MakeAMove(rand() % 18);
	//	return;
	//}
	switch (i)
	{
	case (0):
		topLeft(cube);
		//recordMove("Top Left ");
		inverseMoveLog = 3;
		break;
	case (1):
		//middleLeft(cube);
		//recordMove("Middle Left ");
		//inverseMoveLog = 4;
		break;
	case (2):
		bottomLeft(cube);
		//recordMove("Bottom Left ");
		inverseMoveLog = 5;
		break;
	case (3):
		topRight(cube);
		//recordMove("Top Right ");
		inverseMoveLog = 0;
		break;
	case (4):
		//middleRight(cube);
		//recordMove("Middle Right ");
		//inverseMoveLog = 1;
		break;
	case (5):
		bottomRight(cube);
		//recordMove("Bottom Right ");
		inverseMoveLog = 2;
		break;
	case(6):
		leftUp(cube);
		//recordMove("Left UP ");
		inverseMoveLog = 9;
		break;
	case (7):
		//middleUp(cube);
		//recordMove("Middle UP ");
		//inverseMoveLog = 10;
		break;
	case (8):
		rightUp(cube);
		//recordMove("Right UP ");
		inverseMoveLog = 11;
		break;
	case (9):
		leftDown(cube);
		//recordMove("left Down ");
		inverseMoveLog = 6;
		break;
	case(10):
		//middleDown(cube);
		//recordMove("Middle Down ");
		//inverseMoveLog = 7;
		break;
	case(11):
		rightDown(cube);
		//recordMove("Right Down ");
		inverseMoveLog = 8;
		break;
	case(12):
		//frontLeft(cube);
		//recordMove("Front Left ");
		//inverseMoveLog = 15;
		break;
	case(13):
		centerLeft(cube);
		//recordMove("Center Left ");
		inverseMoveLog = 16;
		break;
	case(14):
		backLeft(cube);
		//recordMove("Back Left ");
		inverseMoveLog = 17;
		break;
	case(15):
		//frontRight(cube);
		//recordMove("Front Right ");
		//inverseMoveLog = 12;
		break;
	case(16):
		centerRight(cube);
		//recordMove("Center Right ");
		inverseMoveLog = 13;
		break;
	case(17):
		backRight(cube);
		//recordMove("Back Right ");
		inverseMoveLog = 14;
		break;
	default:
		break;
	}
}

void UnMakeAMove(int i, int cube[6][3][3]) {
	
	
	switch (i)
	{
	case (3):
		topLeft(cube);
		
		break;
	case (4):
		//middleLeft(cube);
		
		break;
	case (5):
		bottomLeft(cube);
		
		break;
	case (0):
		topRight(cube);
		
		break;
	case (1):
		//middleRight(cube);
		
		break;
	case (2):
		bottomRight(cube);
		
		break;
	case(9):
		leftUp(cube);
		
		break;
	case (10):
		//middleUp(cube);
		
		break;
	case (11):
		rightUp(cube);
		
		break;
	case (6):
		leftDown(cube);
		
		break;
	case(7):
		//middleDown(cube);
		
		break;
	case(8):
		rightDown(cube);
		
		break;
	case(15):
		//frontLeft(cube);
		
		break;
	case(16):
		centerLeft(cube);
		
		break;
	case(17):
		backLeft(cube);
		
		break;
	case(12):
		//frontRight(cube);
		
		break;
	case(13):
		centerRight(cube);
		
		
		break;
	case(14):
		backRight(cube);
		
		break;
	default:
		break;
	}
}

bool checkIfSolved(int cube[6][3][3]) {
	int temp2 = cube[0][0][0];
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int h = 0; h < 3; h++) {
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

void recordMove(int moveNumber,string& record) {
	switch (moveNumber)
	{
	case (0):
		
		record = "Top Left \n" + record;
		
		break;
	case (1):
		//record = "Middle Left \n" + record;
		
		break;
	case (2):
		record = "Bottom Left \n" + record;
		
		break;
	case (3):
		record = "Top Right \n" + record;
		//recordMove("Top Right ");
		
		break;
	case (4):
		//record = "Middle Right \n" + record;
		//recordMove("Middle Right ");
		
		break;
	case (5):
		record = "Bottom Right \n" + record;
		//recordMove("Bottom Right ");
		
		break;
	case(6):
		record = "Left Up \n" + record;
		//recordMove("Left UP ");
		
		break;
	case (7):
		//record = "Middle Up \n" + record;
		//recordMove("Middle UP ");
		
		break;
	case (8):
		record = "Right Up \n" + record;
		//recordMove("Right UP ");
		
		break;
	case (9):
		record = "Left Down \n" + record;
		//recordMove("left Down ");
		
		break;
	case(10):
		//record = "Middle Down \n" + record;
		//recordMove("Middle Down ");
		
		break;
	case(11):
		record = "Right Down \n" + record;
		//recordMove("Right Down ");
		
		break;
	case(12):
		//record = "Front Left \n" + record;
		//recordMove("Front Left ");
		
		break;
	case(13):
		record = "Center Left \n" + record;
		//recordMove("Center Left ");
		
		break;
	case(14):
		record = "Back Left \n" + record;
		//recordMove("Back Left ");
		
		break;
	case(15):
		//record = "Front Right \n" + record;
		//recordMove("Front Right ");
		
		break;
	case(16):
		record = "Center Right \n" + record;
		//recordMove("Center Right ");
		
		break;
	case(17):
		record = "Back Right \n" + record;
		//recordMove("Back Right ");
		
	default:
		break;
	}

	turns++;
	
	//cout << info << endl;
}

void printcube(int cube[6][3][3]) {
	cout << "printing cube" << endl;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int h = 0; h < 3; h++) {
				cout << cube[i][j][h] << ", ";
			}
			cout << endl;
		}
		cout << endl;
	}
}

void rotateSide(int side, int times, int cube[6][3][3]) {
	//rotate counterclockwise do times = 1
	for (int h = 0; h < times; h++) {

		for (int i = 0; i < 3 / 2; i++) {
			for (int j = i; j < 3 - i - 1; j++) {
				int temp = cube[side][i][j];
				cube[side][i][j] = cube[side][j][3 - 1 - i];
				cube[side][j][3 - 1 - i] = cube[side][3 - 1 - i][3 - 1 - j];
				cube[side][3 - 1 - i][3 - 1 - j] = cube[side][3 - 1 - j][i];
				cube[side][3 - 1 - j][i] = temp;
			}
		}


	}
}
//left and right
void topLeft(int cube[6][3][3]) {
	//int a, b, c;
	//save side 0
	int a = cube[0][0][0];
	int b = cube[0][0][1];
	int c = cube[0][0][2];
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
	rotateSide(4, 3, cube);
}
void middleLeft(int cube[6][3][3]) {
	//int a, b, c;
	//save side 0
	int a = cube[0][1][0];
	int b = cube[0][1][1];
	int c = cube[0][1][2];
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
void bottomLeft(int cube[6][3][3]) {
	//int a, b, c;
	//save side 0
	int a = cube[0][2][0];
	int b = cube[0][2][1];
	int c = cube[0][2][2];
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
	rotateSide(5, 1, cube);
}
void topRight(int cube[6][3][3]) {
	//int a, b, c;
	//save side 0
	int a = cube[0][0][0];
	int b = cube[0][0][1];
	int c = cube[0][0][2];
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
	rotateSide(4, 1, cube);
}
void middleRight(int cube[6][3][3]) {
	//int a, b, c;
	//save side 0
	int a = cube[0][1][0];
	int b = cube[0][1][1];
	int c = cube[0][1][2];
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
void bottomRight(int cube[6][3][3]) {
	//int a, b, c;
	//save side 0
	int a = cube[0][2][0];
	int b = cube[0][2][1];
	int c = cube[0][2][2];
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
	rotateSide(5, 3, cube);
}

// up and down
void leftUp(int cube[6][3][3]) {
	//int a, b, c;
	//save side 0
	int a = cube[0][0][0];
	int b = cube[0][1][0];
	int c = cube[0][2][0];
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
	rotateSide(1, 1, cube);
}
void middleUp(int cube[6][3][3]) {
	//int a, b, c;
	//save side 0
	int a = cube[0][0][1];
	int b = cube[0][1][1];
	int c = cube[0][2][1];
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
void rightUp(int cube[6][3][3]) {
	//int a, b, c;
	//save side 0
	int a = cube[0][0][2];
	int b = cube[0][1][2];
	int c = cube[0][2][2];
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
	rotateSide(3, 3, cube);
}
void leftDown(int cube[6][3][3]) {
	//int a, b, c;
	//save side 0
	int a = cube[0][0][0];
	int b = cube[0][1][0];
	int c = cube[0][2][0];
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
	rotateSide(1, 3, cube);
}
void middleDown(int cube[6][3][3]) {
	//int a, b, c;
	//save side 0
	int a = cube[0][0][1];
	int b = cube[0][1][1];
	int c = cube[0][2][1];
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
void rightDown(int cube[6][3][3]) {
	//int a, b, c;
	//save side 0
	int a = cube[0][0][2];
	int b = cube[0][1][2];
	int c = cube[0][2][2];
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
	rotateSide(3, 1, cube);
}

//depth turns
void frontLeft(int cube[6][3][3]) {
	//int a, b, c;
	//save side 3
	int a = cube[3][0][0];
	int b = cube[3][1][0];
	int c = cube[3][2][0];
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
	rotateSide(0, 1, cube);
}
void centerLeft(int cube[6][3][3]) {
	//int a, b, c;
	//save side 3
	int a = cube[3][0][1];
	int b = cube[3][1][1];
	int c = cube[3][2][1];
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
void backLeft(int cube[6][3][3]) {
	//int a, b, c;
	//save side 3
	int a = cube[3][0][2];
	int b = cube[3][1][2];
	int c = cube[3][2][2];
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
	rotateSide(2, 3, cube);
}
void frontRight(int cube[6][3][3]) {
	//int a, b, c;
	//save side 3
	int a = cube[3][0][0];
	int b = cube[3][1][0];
	int c = cube[3][2][0];
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
	rotateSide(0, 3, cube);
}
void centerRight(int cube[6][3][3]) {
	//int a, b, c;
	//save side 3
	int a = cube[3][0][1];
	int b = cube[3][1][1];
	int c = cube[3][2][1];
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
void backRight(int cube[6][3][3]) {
	//int a, b, c;
	//save side 3
	int a = cube[3][0][2];
	int b = cube[3][1][2];
	int c = cube[3][2][2];
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
	rotateSide(2, 1, cube);
}