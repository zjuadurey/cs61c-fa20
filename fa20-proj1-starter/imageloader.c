/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	Image *img = (Image*) malloc(sizeof(Image));
		if (img == NULL) {
		printf("a malloc fails\n.\n");
		exit(-1);
	}
	char Type[10];
	int color_stage;
	FILE *fp = fopen(filename, "r");
	fscanf(fp, "%s %u %u %d", Type, &img->cols, &img->rows, &color_stage);
	if (fp == NULL) {
		printf("fp fopen fails\n.\n");
		exit(-1);
	}
	Color **image = (Color **) malloc(sizeof(Color*) * img->rows);
	if (image == NULL) {
		printf("image malloc fails\n.\n");
		exit(-1);
	}
	for (int i = 0; i < img->rows; i ++) {
		image[i] = (Color *)malloc(img->cols * sizeof(Color));
		for (int j = 0; j < img->cols; j ++) {
			fscanf(fp, "%hhu %hhu %hhu", &image[i][j].R, &image[i][j].G, &image[i][j].B);
		}
	}

	img->image = image;

	fclose(fp);

	return img;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	uint32_t cols = image->cols;
	uint32_t rows = image->rows;
	Color **img = image->image;
	printf("P3\n%u %u\n255\n", cols, rows);
	for (uint32_t i = 0; i < rows; i ++)
	{
		for (uint32_t j = 0; j < cols; j ++)
		{
			printf("%3d %3d %3d", img[i][j].R, img[i][j].G, img[i][j].B);
			if (j < cols - 1) printf("   ");
		}
		printf("\n");
	}
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	Color **img = image->image;

	for (int i = 0; i < image->rows; i ++) {
		free(img[i]);
	}
	free(img);
	free(image);
}