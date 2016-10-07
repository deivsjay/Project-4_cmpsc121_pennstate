#include <iostream>
#include <iomanip>
using namespace std;

void dimensions(int&, int&);
void initializePlate(int, int, double[26][30]);
void startingtemp(double, double, double, double, double&, int, int, double[26][30]);
void outputPlate(double[26][30], int, int);
void epsilonThisMoFo(double[26][30], int, int, double);

/*
Divya Jagadeesh
CMPSC 121 - Spring 2015
Sec 004

Purpose:	The purpose of the main function is to initialize variables that will be used in the other functions in this program and to
			call the other functions.
Input:		row (number of rows)
			column (number of columns)
			plate[26][30] (plate array)
			top (top edge of plate)
			bottom (bottom edge of plate)
			left (left edge of plate)
			right (right edge of plate)
			epsilon (epsilon value)
Output:		row *passed by reference*
			column *passed by reference*
			plate[26][30] *passed by reference*
			epsilon *passed by reference*
Processing:
*/

int main() {

	int row = 0, column = 0;
	double plate[26][30];
	double top = 0, bottom = 0, left = 0, right = 0, epsilon = 0;

	dimensions(row, column);			//gets dimensions of plate
	initializePlate(row, column, plate);		//initializes cells in plate to 0
	startingtemp(top, bottom, left, right, epsilon, row, column, plate);		//gets temperatures of edges of plate and epsilon value
	epsilonThisMoFo(plate, row, column, epsilon);			//iterates the plate until the plate is at equilibrium
	outputPlate(plate, row, column);		//outputs the plate
	
	return 0;
}

/*
Divya Jagadeesh
CMPSC 121 - Spring 2015
Sec 004

Purpose:	The purpose of this function is to receive the dimensions of the plate.
Input:		row_dim (width of the plate) *passed by reference*
			column_dim (length of the plate) *passed by reference*
Output:		row_dim
			column_dim
Processing:	The user is asked to enter the length and width of the plate. 
			A while loop is used to confirm that the user inputed a matrix between sizes 2x2 to 26x30.
*/

void dimensions(int& row_dim, int& column_dim) {

	cout << "Enter the length of your plate: ";
	cin >> column_dim;			//user inputed columns

	while (column_dim > 30 || column_dim < 2) {		//confirms user inputed correct length
		cout << "Your plate must be between 2 to 30 units long." << endl;
		cout << "Enter the length of your plate: ";
		cin >> column_dim;
	}

	cout << "Enter the width of your plate: ";
	cin >> row_dim;				//user inputed rows

	while (row_dim > 26 || column_dim < 2) {			//confirms user inputed correct width
		cout << "Your plate must be between 2 to 26 units long." << endl;
		cout << "Enter the width of your plate: ";
		cin >> row_dim;
	}
}

/*
Divya Jagadeesh
CMPSC 121 - Spring 2015
Sec 004

Purpose:	The purpose of this function is to initialize all the elements in the array to zero.
Input:		row_init (number of user inputed rows)
			column_init (number of user inputed columns)
			plate_init[26][30] (plate array)
Output:		plate_init[26][30]
Processing:	A nested for loop is used to initialize all the elements in the rows and columns.
			plate_init[i][j] = 0;
*/

void initializePlate(int row_init, int column_init, double plate_init[26][30]) {

	for (int i = 0; i < row_init; i++) {
		for (int j = 0; j < column_init; j++) {
			plate_init[i][j] = 0;		//initializing all elements in plate to 0
		}
	}

}

/*
Divya Jagadeesh
CMPSC 121 - Spring 2015
Sec 004

Purpose:	The purpose of this function is to assign user inputed temperatures to the outer edges of the plate and receive an epsilon value.
Input:		top_start (temp of top edge of plate)
			left_start (temp of left edge of plate)
			right_start (temp of right edge of plate)
			bottom_start (temp of bottom edge of plate)
			epsilon_start (epsilon value) *passed by reference*
			row_start (number of rows)
			column_start (number of columns)
			plate_start[26][30] (plate array)
Output:		top_start
			left_start
			right_start
			bottom_start
			epsilon_start
			plate_start[26][30]
Processing:	The user is asked to input the temperatures for the edges of the plate.
			A while loop confirms each edge of the plate is between 0-300 degrees.
			cout << "The starting temperature must be between 0 to 300 degrees." << endl;
			cout << "Re-enter the top edge of your plate's starting temp: ";
			cin >> top_start;
			A for loop implements each edge of the plate according to the user inputed temperature.
			plate_start[0][i] = top_start;
			The corners of the plate are calculated after the temperature for the two sides around the corner are received by the user.
			plate_start[0][0] = (plate_start[0][1] + plate_start[1][0]) / 2;
*/

void startingtemp(double top_start, double bottom_start, double left_start, double right_start, double& epsilon_start, int row_start, int column_start, double plate_start[26][30]) {

	cout << "Enter the top edge of your plate's starting temp: ";
	cin >> top_start;		//user inputed top edge

	while (top_start < 0 || top_start > 300) {			//confirms edge is between 0 and 300 degrees
		cout << "The starting temperature must be between 0 to 300 degrees." << endl;
		cout << "Re-enter the top edge of your plate's starting temp: ";
		cin >> top_start;
	}

	for (int i = 1; i < column_start - 1; i++) {	//initializes top edge of plate
		plate_start[0][i] = top_start;
	}

	cout << "Enter the left edge of your plate's starting temp: ";
	cin >> left_start;			//user inputed left edge

	while (left_start < 0 || left_start > 300) {		//confirms edge is between 0 and 300 degrees
		cout << "The starting temperature must be between 0 to 300 degrees." << endl;
		cout << "Re-enter the left edge of your plate's starting temp: ";
		cin >> left_start;
	}

	for (int i = 1; i < row_start - 1; i++) {
		plate_start[i][0] = left_start;			//initializes left edge of plate
	}

	plate_start[0][0] = (plate_start[0][1] + plate_start[1][0]) / 2;	//calculates top left corner of plate

	cout << "Enter the bottom edge of your plate's starting temp: ";
	cin >> bottom_start;		//user inputed bottom edge

	while (bottom_start < 0 || bottom_start > 300) {		//confirms edge is between 0 and 300 degrees
		cout << "The starting temperature must be between 0 to 300 degrees." << endl;
		cout << "Re-enter the bottom edge of your plate's starting temp: ";
		cin >> bottom_start;
	}

	for (int i = 1; i < column_start - 1; i++) {
		plate_start[row_start - 1][i] = bottom_start;		//initializes bottom edge of plate
	}

	plate_start[row_start - 1][0] = (plate_start[row_start - 2][0] + plate_start[row_start - 1][1]) / 2;	//calculates bottom left corner of plate

	cout << "Enter the right edge of your plate's starting temp: ";
	cin >> right_start;			//user inputed right edge

	while (right_start < 0 || right_start > 300) {		//confirms edge is between 0 and 300 degrees
		cout << "The starting temperature must be between 0 to 300 degrees." << endl;
		cout << "Re-enter the right edge of your plate's starting temp: ";
		cin >> right_start;
	}

	for (int i = 1; i < row_start - 1; i++) {
		plate_start[i][column_start - 1] = right_start;		//initializes right edge of plate
	}

	//calculates right corners of plate
	plate_start[row_start - 1][column_start - 1] = (plate_start[row_start - 1][column_start - 2] + plate_start[row_start - 2][column_start - 1]) / 2;
	plate_start[0][column_start - 1] = (plate_start[0][column_start - 2] + plate_start[1][column_start - 1]) / 2;

	cout << "Enter the value of epsilon that will be used to determine when \nthe plate has reached equilibrium: ";
	cin >> epsilon_start;		//user inputed epsilon value

	while (epsilon_start <= 0) {			//confirms the epsilon value is greater than 0
		cout << "Enter a positive epsilon: ";
		cin >> epsilon_start;
	}

}

/*
Divya Jagadeesh
CMPSC 121 - Spring 2015
Sec 004

Purpose:	The purpose of this function is to change the temperatures in the plate until the difference in the last change, in each
			element, is less than epsilon.
Input:		plate_mofo[26][30]
			row_mofo (number of rows)
			column_mofo (number of columns)
			epsilon_mofo (epsilon value)
Output:		plate_mofo[26][30]
Processing:	A nested for loop changes all the values in the plate from 0 to the average of the 4 elements around them.
			plate_mofo[i][j] = (plate_mofo[i - 1][j] + plate_mofo[i + 1][j] + plate_mofo[i][j - 1] + plate_mofo[i][j + 1]) / 4;
			This is nested in a do-while loop that iterates until the difference in the changes of each element from the last iteration
			are less than epsilon.
			The difference in the iterations are checked using if statements.
			comparison = temp - plate_mofo[i][j];
*/

void epsilonThisMoFo(double plate_mofo[26][30], int row_mofo, int column_mofo, double epsilon_mofo) {

	double temp = 0;
	double comparison;
	int count = 0;
	int iterations = 0;
	int i, j;

	//calculates inner cells of plate
	for (i = 1; i <= row_mofo - 2; i++){
		for (j = 1; j <= column_mofo - 2; j++) {
			plate_mofo[i][j] = (plate_mofo[i - 1][j] + plate_mofo[i + 1][j] + plate_mofo[i][j - 1] + plate_mofo[i][j + 1]) / 4;
		}
	}
	iterations++;

	do {
		count = 0;
		for (i = 1; i <= row_mofo - 2; i++){
			for (j = 1; j <= column_mofo - 2; j++) {
				temp = plate_mofo[i][j];
				plate_mofo[i][j] = (plate_mofo[i - 1][j] + plate_mofo[i + 1][j] + plate_mofo[i][j - 1] + plate_mofo[i][j + 1]) / 4;
				comparison = temp - plate_mofo[i][j];		//compares values from last iteration and new iteration
				if (comparison < 0) {		
					comparison *= -1;
				}
				if (comparison <= epsilon_mofo) {
					count++;			//how many differences in values in this iteration are less than epsilon
				}
			}
		}
		iterations++;
	} while (count < (row_mofo - 2)*(column_mofo - 2));		//keeps going until all the values differ less than epsilon

	cout << "The plate reached equilibrium after " << iterations << " iterations." << endl;
}

/*
Divya Jagadeesh
CMPSC 121 - Spring 2015
Sec 004

Purpose:	The purpose of this function is to ouput the plate.
Input:		plate_output[26][30]
			row_output (number of rows)
			column_output (number of columns)
Output:		plate_output[26][30]
Processing:	A nested for loop is used to output each element in the rows and columns.
			cout << setprecision(1) << fixed << showpoint << plate_output[i][j] << "\t";
*/

void outputPlate(double plate_output[26][30], int row_output, int column_output) {

	//outputs the values of the plate
	cout << "The equilibrium temperatures are: " << endl;
	for (int i = 0; i < row_output; i++) {
		for (int j = 0; j < column_output; j++) {
			cout << setprecision(1) << fixed << showpoint << plate_output[i][j] << "\t";
		}
		cout << endl;
	}
}