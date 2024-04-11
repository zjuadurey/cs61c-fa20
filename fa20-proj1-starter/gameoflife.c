/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
	
	//build the map_table
    int mask = 1;

    int map_table[19] = {0};

    for (int i = 0; i < 18; i ++) {
        map_table[i] = (rule & mask) != 0 ? 1 : 0;
        mask *= 2;
    }

	//use directions to determine the color
	Color *output = (Color *) malloc(sizeof(Color));

	int max_row_index = image->rows - 1, max_col_index = image->cols - 1; //limit the range
	int directions[8][2] = {
        {-1, 0}, {-1, 1}, {0, 1}, {1, 1},
        {1, 0}, {1, -1}, {0, -1}, {-1, -1}
    };

	//count the vaild neighbors
	int count[3]; // count for R, G, B
	int offset[3]; // differ the dead & alive state
	for (int i = 0; i < 3; i ++) {
		count[i] = 0;
		offset[i] = 0;
	}

	if (image->image[row][col].R == 255) {
		offset[0] = 9;
	}

	if (image->image[row][col].G == 255) {
		offset[1] = 9;
	}

	if (image->image[row][col].B == 255) {
		offset[2] = 9;
	}

	for (int i = 0; i < 8; i ++) {
		int row_index = row + directions[i][0];
		int col_index = col + directions[i][1];
		//boundary checks & changes
		if (row_index == max_row_index + 1) row_index = 0;
		if (col_index == max_col_index + 1) col_index = 0;

		if (row_index == -1) row_index = max_row_index;
		if (col_index == -1) col_index = max_col_index;

		if (image->image[row_index][col_index].R == 255) count[0] ++;
		if (image->image[row_index][col_index].G == 255) count[1] ++;
		if (image->image[row_index][col_index].B == 255) count[2] ++;
	}

	//process the color according to the count array & the map_table
	//printf("count[0], offset[0] : %d %d\n", count[0], offset[0]);
	//printf("map_table[count[0] + offset[0]]: %d\n", map_table[count[0] + offset[0]]);
	output->R = map_table[count[0] + offset[0]] == 1 ? 255 : 0;
	output->G = map_table[count[1] + offset[1]] == 1 ? 255 : 0;
	output->B = map_table[count[2] + offset[2]] == 1 ? 255 : 0;
	return output;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	Image *output = (Image *) malloc(sizeof(Image));
	Color **output_image = (Color **) malloc(sizeof(Color *) * image->rows);

	for (int i = 0; i < image->rows; i ++ ) {
		output_image[i] = (Color *) malloc(sizeof(Color) * image->cols);
		for (int j = 0; j < image->cols; j ++) {
			Color *tmp = evaluateOneCell(image, i, j, rule);
			output_image[i][j] = *tmp;
			free(tmp);
		}
	}

	output->cols = image->cols;
	output->rows = image->rows;
	output->image = output_image;

	return output;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if (argc != 3) {
		printf("usage: %s filename rule\n",argv[0]);
		printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
		printf("rule is a hex number beginning with 0x; Life is 0x1808.\n");
		exit(-1);
	}

	//read the input file
	Image *img = readData(argv[1]);

	//process the input file
	char *ptr;
	Image *new_image = life(img, strtoul(argv[2], &ptr, 0));

	writeData(new_image);

	freeImage(img);
	freeImage(new_image);
	return 0;
}
