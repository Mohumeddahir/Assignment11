/*
 *This program is used to test the concept of backtracking 
 *algorithm using recursion to solve maze problem and
 *build it in a stack.
*/

#include<iostream>
#include"Maze.hpp"
using namespace std;

//constructor which creates a list of strings containing 
//only asterisks or blank spaces.
Maze :: Maze(string *textmaze, int num_strings, Cell start, Cell finish){
	m_start = start;
	m_finish = finish;
	m_rows = num_strings;//
	m_cols = textmaze[0].length();
	m_grid = new char* [m_rows];
	for(int i = 0; i < m_rows; i++){
		m_grid[i] = new char[m_cols];
	}
	for(int r = 0; r < m_rows; r++){
		for(int c = 0; c < m_cols; c++){
			m_grid[r][c] = textmaze[r][c];
		}
	}
}	
//destructor which removes any allocated memeory associated with the maze.
Maze :: ~Maze(){
	for(int i = 0; i < m_rows; i++){
		delete [] m_grid[i];
	}
	delete [] m_grid;
}
//this is a string representation of the maze as a grid of characters.
//A path can be represented by any character that is not space or an asterisk.
string Maze :: to_string(){
	string to_return = "";
	for(int r = 0; r < m_rows; r++){
		for(int c = 0; c < m_cols; c++){
			to_return = to_return + m_grid[r][c];
		}
		to_return = to_return + "\n";
	}
	return to_return;

}
bool Maze :: find_path(Cell src, Cell dest){
	int row = src.row; // the row of the cell src.
	int col = src.col;// the col of the cell src.
	char text = 'Z';
	//base cases
	
	if(row > m_rows-1 || row < 0){//if the row of src is greater than m_rows or the row < 0,
									//it is out of pounds, and we return false.
		return false;
	}
	if(col>m_cols-1 || col < 0){//if the col of src is greater than m_cols or the col < 0,
									//it is out of pounds, and we return false.
		return false;
	}
	if(m_grid[row][col] == '*'){//if there is a wall, we return false;
		return false;
	}
	if(m_grid[row][col] == text){//if there is already a path character on the cell, we return false
		return false;
	}	
	if (src == dest){//if we src is the same as dest, we isert the path character and return true.
		m_grid[row][col] = text;
		path.push(src);
		return true;
	}
	//if it is past base cases, we insert the path character.
	m_grid[row][col] = text;
	path.push(src);
	Cell up(row-1, col);//moving north
	Cell down(row+1, col);//moving south
	Cell left(row, col-1);//moving west
	Cell right(row, col+1);//moving east
	
	//recursive cases 
	if(find_path(up, dest)){
		return true;
	}
	if(find_path(down, dest)){
		return true;
	}
		
	if(find_path(right, dest)){
		return true;
	}
	if(find_path(left, dest)){
		return true;
	}
	
	// if it does go past all the above cases, it removes it from the stack 
	// and the space in the src is empted and does backtracking when it returns false.
	m_grid[row][col] = ' ';
	path.pop();
	return false;
	
}
//this solves the maze by finding a path and storing as a deque of cells.
//If there is no path, then the queue is empty.
Deque<Cell>& Maze ::  solve(){
	find_path(m_start, m_finish);
	return path;
}
