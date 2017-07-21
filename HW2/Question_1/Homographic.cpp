// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Size1,Size2,Size3,Size4;

	// Check for proper syntax
	if (argc < 3) {
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image1.raw input_image2.raw output_image.raw [BytesPerPixel] [Size1] [Size2] [Size3] [Size4]" << endl;
		return 0;
	}

	// Check if image is grayscale or color
	if (argc < 4) {
		BytesPerPixel = 1; // default is grey image
	}
	else {
		BytesPerPixel = atoi(argv[4]);
		// Check if size is specified
		if (argc >= 5) {
			Size1 = atoi(argv[5]);
			Size2 = atoi(argv[6]);
			Size3 = atoi(argv[7]);
			Size4 = atoi(argv[8]);
		}
	}

	// Allocate image data array
	unsigned char Imagefield[Size1][Size2][BytesPerPixel];
	unsigned char Imagefield1[Size1][Size2][BytesPerPixel];
	unsigned char Imagetrojan[Size3][Size4][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(argv[1], "rb"))) {
		cout << "Cannot open file: " << argv[1] << endl;
		exit(1);
	}
	fread(Imagefield, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
	fclose(file);

	if (!(file = fopen(argv[2], "rb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fread(Imagetrojan, sizeof(unsigned char), Size3*Size4*BytesPerPixel, file);
	fclose(file);
	
	double H[3][3] = { { 0.0657,0.8522,-63.6415},{ -0.7932,0.5405,401.0036 },{ 0.0001,-0.0026,1.0 } };


	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	for (int i = 0; i < Size1; i++) {
		for (int j = 0; j < Size2; j++) {
			for (int k = 0; k < 3; k++) {
				Imagefield1[i][j][k] = Imagefield[i][j][k];
			}
		}
	}
	
	for (int i = 0; i < Size1; i++)
	{
		for (int j = 0; j < Size2; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				double x = j + 0.5;
				double y = 648 - i - 0.5;
				if ((0.765*x)>=(y+194.928) && y<=(235.162-(0.027*x)) && (1.464*x)<=(y+739.224) && y>=(75.153-(0.0769*x)))
				{
					double x1 = ((H[0][0] *x) + (H[0][1] *y) + H[0][2]);
					double y1 = ((H[1][0] *x) + (H[1][1] *y) + H[1][2]);
					double w1 = ((H[2][0] *x) + (H[2][1] *y) + H[2][2]);
					double x2 = x1 / w1;
					double y2 = y1 / w1;
					double Tcol = x2 - 0.5;
					double Trow = 197 - y2 - 0.5;
					int p = Trow;  
					int q = Tcol; 
					double delx = Trow - floor(Trow);
					double dely = Tcol - floor(Tcol);
					Imagefield[i][j][k] = (1 - delx)*(1 - dely)*Imagetrojan[p][q][k] + (delx)*(1 - dely)*Imagetrojan[p][q+1][k] + (1 - delx)*(dely)*Imagetrojan[p+1][q][k] + (delx)*(dely)*Imagetrojan[p+1][q+1][k];
					 
				}
			}
		}
	}
			
	// Removing White background	
	
	for (int i = 0; i < 648; i++) {
		for (int j = 0; j < 972; j++) {
				if (Imagefield[i][j][0] >= 240 && Imagefield[i][j][1] >= 240 && Imagefield[i][j][2] >= 240) {
					for (int k = 0; k < 3; k++) {
						Imagefield[i][j][k] = Imagefield1[i][j][k];	
				}
			}
		}
	}

	
	// Write image data (filename specified by second argument) from image data matrix

	if (!(file = fopen(argv[3], "wb"))) {
		cout << "Cannot open file: " << argv[3] << endl;
		exit(1);
	}
	fwrite(Imagefield, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
	fclose(file);

	return 0;
}
