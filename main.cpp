#include "Deque.hpp"
#include "Maze.hpp"
#include<iostream>
#include<fstream>
	using std::cout;
	using std::ifstream;
	using std::ofstream;
	using std::cout;
	using std::cerr;
	using std::endl;
	using std::ios;
	using std::string;

/******* functions that help trim whitespace from the beginning and end of strings ********/
// From StackOverflow user = Galik
const char* ws = " \t\n\r\f\v";
/**
 * Trims the trailing whitespace at the end of a string.
 * Whitespace to the left or between words is left alone.
 * @param s The string.
 * @return The trimmed string.
 */
string& rtrim(string & s) {
	s.erase(s.find_last_not_of(ws) + 1);
	return s;
}

/**
 * Trims the whitespace at the beginning of a string.
 * Whitespace to the right or between words is left alone.
 * @param s The string.
 * @return The trimmed string.
 */
string& ltrim(string & s) {
	s.erase(0, s.find_first_not_of(ws));
	return s;
}

/**
 * Trims the whitespace at the beginning and end of a string.
 * Whitespace in the middle of the string is left alone.
 * @param s The string.
 * @return The trimmed string.
 */
string& trim(string & s) {
	return ltrim(rtrim(s));
}
/***********************************************************************************/

/**
 * Tester to solve maze problem.
 * @param arc The number of strings (delimited by whitespace) that follow
 *		the run command for this program.
 * @param argv An array of arrays of characters.
 *		(The array of words that follow the run command, deimited by whitespace).
 * @return An integer (usually 0) indicating success or failure of the function
 *		to run to completion.
 */
int main(int argc, char ** argv) {

	// expecting the name of the maze file.
	if (argc < 2) {
		cerr << "usage: <run command> <mazefilename>\n";
		exit(1);
	}

	string filename(argv[1]);
	int rows, cols, start_row, start_col, finish_row, finish_col;

	// read in the info from the maze file.
	ifstream reader(filename);
	reader >> rows;
	reader >> cols;
	reader >> start_row;
	reader >> start_col;
	reader >> finish_row;
	reader >> finish_col;
	string junk;
	getline(reader, junk); // to clear the newline character after the last int.

	string * maze_data = new string[rows];
	string line;
	for (int row = 0; row < rows; row++) {
		getline(reader,line);
		maze_data[row] = trim(line);
	}
	reader.close();

	// establishing the start and finish cell
	// as well as the Maze itself
	Cell start(start_row, start_col);
	Cell finish(finish_row, finish_col);
	Maze maze(maze_data, rows, start, finish);

	Deque<Cell> soln = maze.solve();

	if (soln.is_empty()) {
		cout << "No path!\n";
	} else {
		cout << "Solution found\n";
		soln.print_queue();
		cout << "\n";
		cout << maze.to_string() << endl;
	}

	cout << "All done!\n";
	return 0;
}
