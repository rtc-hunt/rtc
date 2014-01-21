/**
 * This program searches a wordsearch for words in a dictionary, and returns
 * the words matched and their locations. Make with "make wordsearch", assuming
 * a standard POSIX environment with GCC.
 *
 * The one limit is that the program cannot find the same word originating from
 * the same letter in multiple directions.
 *
 * It would be fairly little work to search for "bent" words. Just create a data
 * structure and modify search_for_word() to use the same kind of "look around"
 * logic that start_search_for_word() contains.
 *
 * Outputs in the form
 * (row, column) DIRECTION WORD
 *
 * Where DIRECTION is NW, N, NE, W, etc
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Reads in the wordsearch matrix from a file.
 * Assumes the matrix is a rectangle, so the number of characters in the
 * first line is the number of characters in every line.
 *
 * Files should look like:
CAA
BAB
CCT
 * (A 3x3 wordsearch with "CAT" going from the top left to the bottom right)
 *
 * Returns a 2D matrix of the characters. The *rows and *cols arguments
 * will be filled with the number of rows and columns in the wordsearch.
 */
char **
get_matrix (char *filename, int *rows, int *cols)
{
	FILE *f;
	char **matrix;
	char c;
	int row, col;

	f = fopen (filename, "r");
	if (f == NULL) {
		fprintf (stderr, "Error opening %s\n", filename);
		exit (1);
	}

	*cols = 0;
	while ((c = getc(f)) != '\n') {
		(*cols)++;
	}

	*rows = 1;
	while ((c = getc(f)) != EOF) {
		if (c == '\n') {
			(*rows)++;
		}
	}

	fseek (f, 0, SEEK_SET);

	matrix = calloc (*rows, sizeof *matrix);
	for (row = 0; row < *rows; row++) {
		matrix[row] = calloc (*cols, sizeof *matrix[row]);
		for (col = 0; col < *cols; col++) {
			matrix[row][col] = getc(f);
		}
		if (getc(f) != '\n') {
			fprintf (stderr, "Character at row %d, col %d not "
				 "newline", row, col);
			exit (1);
		}
	}
	fclose (f);

	return matrix;
}

/**
 * Reads in the wordlist from the file.
 * Each word should be on one line.
 *
 * Returns an array of NULL-terminated strings. The *words argument
 * will be filled with the number of words found.
 */
char **
get_wordlist (char *filename, int *words)
{
	FILE *f;
	char **wordlist;
	int word, length;
	char c;

	f = fopen (filename, "r");
	if (f == NULL) {
		fprintf (stderr, "Error opening %s\n", filename);
		exit (1);
	}

	*words = 0;
	while ((c = getc(f)) != EOF) {
		if (c == '\n') {
			(*words)++;
		}
	}

	fseek (f, 0, SEEK_SET);

	wordlist = calloc (*words, sizeof *wordlist);
	word = 0;
	length = 0;
	while ((c = getc(f)) != EOF) {
		length++;
		if (c == '\n') {
			wordlist[word] = calloc (length,
						 sizeof *wordlist[word]);
			fseek (f, -length, SEEK_CUR);
			fgets (wordlist[word], length, f);
			getc(f);
			word++;
			length = 0;
		}
	}
	fclose (f);
	return wordlist;
}

/**
 * Unless position is out of range, return if the letter at the position
 * is the letter being examined.
 */
int
look_for_letter (char **matrix, int rows, int cols, int row, int col,
		 char letter)
{
	if (row < 0 || row >= rows || col < 0 || col >= cols) {
		return 0;
	}

	return (matrix[row][col] == letter);
}

/**
 * Continues to look for a word in a given direction, after being
 * called by start_search_for_word()
 *
 * Returns 1 if the word was found, and 0 if an inconsistency was
 * found.
 */
int
search_for_word (char **matrix, int rows, int cols, int row, int col,
		 char *word, int pos, int row_delta, int col_delta)
{
	if (word[pos + 1] == '\0') {
		return 1;
	}
	if (look_for_letter (matrix, rows, cols,
			     row + row_delta, col + col_delta,
			     word[pos + 1])) {
		return search_for_word (matrix, rows, cols,
					row + row_delta,
					col + col_delta,
					word, pos + 1,
					row_delta, col_delta);
	}
	return 0;
}

/**
 * Takes a word search matrix, with the size rows and cols, and a position
 * identified by row and column. *word is the current word being examined.
 *
 * When a direction is found which could potentially contain the word, it
 * will start to follow in that direction and see if the entire word matches.
 *
 * Returns 0 if the word does not exist at the location, and 1 if it does.
 * If it does exist, *row_delta and *col_delta are set to the direction
 * the word lies in.
 */
int
start_search_for_word (char **matrix, int rows, int cols, int row, int col,
		       char *word, int *row_delta, int *col_delta)
{
	for ((*row_delta) = -1; (*row_delta) < 2; (*row_delta)++) {
		for ((*col_delta) = -1; (*col_delta) < 2; (*col_delta)++) {
			if ((*row_delta) == 0 && (*col_delta) == 0) {
				continue;
			}
			if (look_for_letter (matrix, rows, cols,
					     row + (*row_delta),
					     col + (*col_delta),
					     word[1])) {
				return search_for_word (matrix,
							rows, cols,
							row + (*row_delta),
							col + (*col_delta),
							word, 1,
							*row_delta,
							*col_delta);
			}
		}
	}
	return 0;
}

#define NW "NW"
#define N " N"
#define NE "NE"
#define W " W"
#define NO_DIR "##"
#define E " E"
#define SW "SW"
#define S " S"
#define SE "SE"

/**
 * Return the direction indicated by row_delta and col_delta
 * (both of which should be between -1 and 1, inclusive).
 * If both are 0, return NO_DIR.
 */
char *
direction (int row_delta, int col_delta)
{
	switch (row_delta) {
	case -1:
		switch (col_delta) {
		case -1:
			return NW;
		case 0:
			return N;
		case 1:
			return NE;
		}
		break; // Never reached
	case 0:
		switch (col_delta) {
		case -1:
			return W;
		case 0:
			return NO_DIR; // Should not occur
		case 1:
			return E;
		}
	case 1:
		switch (col_delta) {
		case -1:
			return SW;
		case 0:
			return S;
		case 1:
			return SE;
		}
	}
	return NO_DIR; // Never reached
}

int
main (int argc, char **argv)
{
	int rows, cols;
	char **matrix;
	int words, word;
	char **wordlist;
	int row, col;
	int row_delta, col_delta;

	if (argc < 3) {
		fprintf (stderr, "Usage: %s <word search> <word list>\n",
			 argv[0]);
		exit (0);
	}

	matrix = get_matrix (argv[1], &rows, &cols);
	wordlist = get_wordlist (argv[2], &words);

	for (row = 0; row < rows; row++) {
		for (col = 0; col < cols; col++) {
			for (word = 0; word < words; word++) {
				if (matrix[row][col] == wordlist[word][0]) {
					row_delta = 0;
					col_delta = 0;
					if (start_search_for_word (matrix,
								   rows, cols,
								   row, col,
								   wordlist[word],
								   &row_delta,
								   &col_delta)) {
						printf ("(%d, %d) %s %s\n",
							row, col,
							direction (row_delta,
								   col_delta),
							wordlist[word]);
					}
				}
			}
		}
	}

	return 0;
}
