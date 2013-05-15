#include <iostream>
#include <ctime>
#include <stack>
#include <windows.h>
using namespace std;

const int MAX = 12;

void fillArray(char maze[12][12], int row, int col){
  for(int i = 0; i < row; i++)
		for(int j = 0; j < col; j++)
			maze[i][j] =  '#';
}

void printMaze(char maze[12][12], int row, int col){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			cout << maze[i][j] << " ";
		}
		cout << endl;
	}

}

/* check the chosen point's surrounding points */
bool checkNextMove(char maze[MAX][MAX], int r, int c){
	int row = r;
	int col = c;
	bool canMove = true;
	int cantMove = 0;

	//if the col is at the last column just move there
	if(col == (MAX - 1))
		return true;

	//checking for boundaries and '.'
	if((col + 1) > (MAX - 1) || maze[row][(col + 1)] == '.')
		cantMove++;

	if((col - 1) < 0 || maze[row][(col - 1)] == '.')
		cantMove++;

	if((row + 1) > (MAX - 1) || maze[row + 1][(col)] == '.')
		cantMove++;

	if((row - 1) < 0 || maze[row - 1][(col)] == '.')
		cantMove++;

	//if you have more than one spot you can move it's not a valid spot
	if(cantMove > 1)
		canMove = false;

	return canMove;
}

/* check the chosen point's surrounding points */
bool checkToSolveNextMove(char maze[MAX][MAX], int r, int c){
	int row = r;
	int col = c;

	//checking for boundaries and '.'
	if(maze[row][col] == '.')
		return true;

	return false;
}


void createMaze(char maze[12][12], int start){
	int row = start;
	int col = 0;
	int rowTemp = 0;
	int colTemp = 0;
	int noRow = 0;
	int noCol = 0;
	bool noColumns = false;
	bool noRows = false;
	bool stuck = true;
	bool done = false;
	int RoworColA = 0;
	int RoworCol = 0;
	char RoworColArray[2] = {'r','c'};
	int rowArray[4] = {};
	int colArray[4] = {};

	stack<int> sRow;
	stack<int> sCol;

	// put in starting point
	maze[row][col] = '.';

	srand ((unsigned int) time(NULL) );

	while(!done)
	{
		//clear screen
		system("cls");

		//push the row and col for later
		sRow.push(row);
		sCol.push(col);

		//check surroundings for moves
		if(checkNextMove(maze, row, col + 1)){ 
			RoworCol++;
			colTemp = col + 1;
			rowArray[RoworCol] = row;
			colArray[RoworCol] = colTemp;			
		}
		else
			noCol++;
		
		if(checkNextMove(maze, row, col - 1)){
			RoworCol++;
			colTemp = col - 1;
			rowArray[RoworCol] = row;
			colArray[RoworCol] = colTemp;	
		}
		else
			noCol++;

		if(noCol > 1)
			noColumns = true;

		if(checkNextMove(maze, row + 1, col)){ 
			RoworCol++;
			rowTemp = row + 1;
			rowArray[RoworCol] = rowTemp;
			colArray[RoworCol] = col;
		}
		else
			noRow++;

		if(checkNextMove(maze, row - 1, col)){ 
			RoworCol++;
			rowTemp = row - 1;
			rowArray[RoworCol] = rowTemp;
			colArray[RoworCol] = col;
		}
		else
			noRow++;

		if(noRow > 1)
			noRows = true;


		//if we have a move make the move and set the row and col
		if(!noRows || !noColumns){

			RoworColA = (rand() % (RoworCol)) + 1;

			row = rowArray[RoworColA];

			col = colArray[RoworColA];

			maze[row][col] = '.';
		}

		/* we are stuck if this if is true re-trace back */
		if(noRows && noColumns){
			//pop off the row and col (they didn't work)
			sRow.pop();
			sCol.pop();

			row = sRow.top();
			col = sCol.top();

			//if we are still stuck continue searching for new coordinates
			while(stuck){
				RoworCol = 0;
				noRow = 0;
				noCol = 0;
				if(checkNextMove(maze, row, col + 1)){ 
					RoworCol++;
					colTemp = col + 1;
					rowArray[RoworCol] = row;
					colArray[RoworCol] = colTemp;			
				}
				else
					noCol++;
				
				if(checkNextMove(maze, row, col - 1)){
					RoworCol++;
					colTemp = col - 1;
					rowArray[RoworCol] = row;
					colArray[RoworCol] = colTemp;	
				}
				else
					noCol++;

				if(checkNextMove(maze, row + 1, col)){ 
					RoworCol++;
					rowTemp = row + 1;
					rowArray[RoworCol] = rowTemp;
					colArray[RoworCol] = col;
				}
				else
					noRow++;

				if(checkNextMove(maze, row - 1, col)){ 
					RoworCol++;
					rowTemp = row - 1;
					rowArray[RoworCol] = rowTemp;
					colArray[RoworCol] = col;
				}
				else
					noRow++;

				if(noRow > 1 && noCol > 1)
					stuck = true;
				else
					stuck = false;

				//if still stuck pop those coordinates off
				if(stuck){
					sRow.pop();
					sCol.pop();

					row = sRow.top();
					col = sCol.top();
				}
				else{
					//else check the new coordinates again
					RoworColA = (rand() % (RoworCol)) + 1;

					row = rowArray[RoworColA];

					col = colArray[RoworColA];

					RoworCol = 0;

					noRow = 0;
					noCol = 0;
					if(checkNextMove(maze, row, col + 1)){ 
						RoworCol++;
						colTemp = col + 1;
						rowArray[RoworCol] = row;
						colArray[RoworCol] = colTemp;			
					}
					else
						noCol++;
				
					if(checkNextMove(maze, row, col - 1)){
						RoworCol++;
						colTemp = col - 1;
						rowArray[RoworCol] = row;
						colArray[RoworCol] = colTemp;	
					}
					else
						noCol++;

					if(checkNextMove(maze, row + 1, col)){ 
						RoworCol++;
						rowTemp = row + 1;
						rowArray[RoworCol] = rowTemp;
						colArray[RoworCol] = col;
					}
					else
						noRow++;

					if(checkNextMove(maze, row - 1, col)){ 
						RoworCol++;
						rowTemp = row - 1;
						rowArray[RoworCol] = rowTemp;
						colArray[RoworCol] = col;
					}
					else
						noRow++;

					//if nothing was found we are still stuck
					if(noRow > 1 && noCol > 1){
						sRow.pop();
						sCol.pop();

						row = sRow.top();
						col = sCol.top();

						stuck = true;
					}
					else{
						//else we are not stuck anymore
						sRow.pop();
						sCol.pop();

						row = sRow.top();
						col = sCol.top();

						stuck = false;
					}
				}
				noRow = 0;
				noCol = 0;
			}		
		}
		//print maze
		printMaze(maze,MAX,MAX);

		//reset variables
		noRow = 0;
		noCol = 0;
		RoworCol = 0;
		noRows = false;
		noColumns = false;
		stuck = true;
		//Sleep(1000);
		//if we reach the last column we are done
		if(col == (MAX - 1))
			done = true;
	}

	cout << "DONE!" << endl;

}

//solve the maze that was generated
void solveMaze(char maze[MAX][MAX], int start){
	int row = start;
	int col = 0;
	int rowTemp = 0;
	int colTemp = 0;
	int noRow = 0;
	int noCol = 0;
	int RoworCol = 0;
	int RoworColA = 0;
	int rowArray[4] = {};
	int colArray[4] = {};
	bool done = false;
	bool stuck = false;
	bool noRows = false;
	bool noColumns = false;

	stack<int> sRow;
	stack<int> sCol;

	maze[row][col] = 'x';

	srand ((unsigned int) time(NULL) );

	while(!done){

		//clear screen
		system("cls");

		sRow.push(row);
		sCol.push(col);

		cout << "solving maze..." << endl;

		if(checkToSolveNextMove(maze, row, col + 1)){ 
			RoworCol++;
			colTemp = col + 1;
			rowArray[RoworCol] = row;
			colArray[RoworCol] = colTemp;			
		}
		else
			noCol++;
		
		if(checkToSolveNextMove(maze, row, col - 1)){
			RoworCol++;
			colTemp = col - 1;
			rowArray[RoworCol] = row;
			colArray[RoworCol] = colTemp;	
		}
		else
			noCol++;

		if(checkToSolveNextMove(maze, row + 1, col)){ 
			RoworCol++;
			rowTemp = row + 1;
			rowArray[RoworCol] = rowTemp;
			colArray[RoworCol] = col;
		}
		else
			noRow++;

		if(checkToSolveNextMove(maze, row - 1, col)){ 
			RoworCol++;
			rowTemp = row - 1;
			rowArray[RoworCol] = rowTemp;
			colArray[RoworCol] = col;
		}
		else
			noRow++;

		if(noRow > 1)
			noRows = true;
		if(noCol > 1)
			noColumns = true;

		if(!noRows || !noColumns){

			RoworColA = (rand() % (RoworCol)) + 1;

			row = rowArray[RoworColA];

			col = colArray[RoworColA];

			maze[row][col] = 'x';
		}

		if(noRows && noColumns){
			stuck = true;

			if(col == -11){
				stuck = false;
				done = true;
				break;
			}

			sRow.pop();
			sCol.pop();

			row = sRow.top();
			col = sCol.top();

			while(stuck){
				RoworCol = 0;
				noCol = 0;
				noRow = 0;
				if(checkToSolveNextMove(maze, row, col + 1)){ 
					RoworCol++;
					colTemp = col + 1;
					rowArray[RoworCol] = row;
					colArray[RoworCol] = colTemp;			
				}
				else
					noCol++;
				
				if(checkToSolveNextMove(maze, row, col - 1)){
					RoworCol++;
					colTemp = col - 1;
					rowArray[RoworCol] = row;
					colArray[RoworCol] = colTemp;	
				}
				else
					noCol++;

				if(checkToSolveNextMove(maze, row + 1, col)){ 
					RoworCol++;
					rowTemp = row + 1;
					rowArray[RoworCol] = rowTemp;
					colArray[RoworCol] = col;
				}
				else
					noRow++;

				if(checkToSolveNextMove(maze, row - 1, col)){ 
					RoworCol++;
					rowTemp = row - 1;
					rowArray[RoworCol] = rowTemp;
					colArray[RoworCol] = col;
				}
				else
					noRow++;

				if(noRow > 1 && noCol > 1)
					stuck = true;
				else
					stuck = false;

				if(stuck){
					sRow.pop();
					sCol.pop();

					row = sRow.top();
					col = sCol.top();

					stuck = true;
				}
				else{
					RoworColA = (rand() % (RoworCol)) + 1;

					row = rowArray[RoworColA];

					col = colArray[RoworColA];

					maze[row][col] = 'x';

					stuck = false;
				}
			
			}//while
		
		}

		RoworCol = 0;
		noRow = 0;
		noCol = 0;

		noRows = false;
		noColumns = false;

		printMaze(maze,MAX,MAX);

		if(col == (MAX - 1))
			done = true;
	}
	cout << "maze solved!" << endl;
}

int main(){
	int start;

	srand ((unsigned int) time(NULL) );

	//grab a starting point between 1-9
	start = (rand() % 9) + 1;

	char maze[MAX][MAX];
	
	fillArray(maze,MAX,MAX);

	createMaze(maze,start);

	solveMaze(maze,start);

	return 0;
}
