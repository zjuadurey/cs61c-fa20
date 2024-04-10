/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	Color *output = (Color *) malloc(sizeof(Color));
	uint8_t color_val = image->image[row][col].B % 2 == 0 ? 0 : 255;
	output->R = output->G = output->B = color_val;
	return output;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	Image *output = (Image *) malloc(sizeof(Image));
	Color **output_image = (Color **) malloc(sizeof(Color *) * image->rows);

	for (int i = 0; i < image->rows; i ++ ) {
		output_image[i] = (Color *) malloc(sizeof(Color) * image->cols);
		for (int j = 0; j < image->cols; j ++) {
			Color *tmp = evaluateOnePixel(image, i, j);
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
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if (argc != 2) {
		printf("usage: %s filename\n",argv[0]);
		printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
		exit(-1);
	}

	//read the input file
	Image *img = (Image*) malloc(sizeof(Image));
	if (img == NULL) {
		printf("a malloc fails\n.\n");
		exit(-1);
	}
	char Type[10];
	int color_stage;
	FILE *fp = fopen(argv[1], "r");
	fscanf(fp, "%s %u %u %d", Type, &img->cols, &img->rows, &color_stage);

	Color **image = (Color **) malloc(sizeof(Color*) * img->rows);

	for (int i = 0; i < img->rows; i ++) {
		image[i] = (Color *)malloc(img->cols * sizeof(Color));
		for (int j = 0; j < img->cols; j ++) {
			fscanf(fp, "%hhu %hhu %hhu", &image[i][j].R, &image[i][j].G, &image[i][j].B);
		}
	}

	img->image = image;

	fclose(fp);

	//process the input file
	Image *new_image = steganography(img);

	writeData(new_image);

	freeImage(img);
	freeImage(new_image);
	return 0;
}
