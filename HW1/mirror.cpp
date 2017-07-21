// This sample code reads in image data from a RAW image file and // writes it into another file// NOTE:	The code assumes that the image is of size 256 x 256 and is in the//			RAW format. You will need to make corresponding changes to//			accommodate images of different sizes and/or types#include <stdio.h>#include <iostream>#include <stdlib.h>using namespace std;int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size1;	int	Size2;		// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel] [Size1] [Size2]" << endl;		return 0;	}		// Check if image is grayscale or color	if (argc < 4){		BytesPerPixel = 1; // default is grey image	} 	else {		BytesPerPixel = atoi(argv[3]);		// Check if size is specified		if (argc >= 5){			Size1 = atoi(argv[4]);			Size2 = atoi(argv[5]);		}	}	cout << BytesPerPixel << endl;	cout << Size1 <<"  "<<Size2<< endl;	// Allocate image data array	unsigned char Imagedata[Size1][Size2][BytesPerPixel];	// Read image (filename specified by first argument) into image data matrix	if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);	fclose(file);	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////	unsigned char ImageMirror[Size1][Size2][BytesPerPixel];	for (int i = 0; i < 300; i++) {		for (int j = 0; j < 300; j++) {			for(int k = 0; k < 3; k++) {				ImageMirror[i][j][k] = Imagedata[i][299 - j][k];			}		}	}	// Write image data (filename specified by second argument) from image data matrix	if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}	fwrite(ImageMirror, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);	fclose(file);	cout << (int)Imagedata[0][0][2] << endl;	return 0;}