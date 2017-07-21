// This sample code reads in image data from a RAW image file and
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <math.h>

using namespace std;
int Median(int array[], int Size);
//unsigned char Imageextend[514][514][3];
//unsigned char Imagedata[512][512][3];
int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel;
    int Size1;
    int Size2;
	int mf[3][3] = { {1,1,1},{1,1,1},{1,1,1} };
	int gf[3][3] = { {1,2,1},{2,4,2},{1,2,1} };
    
    // Check for proper syntax
    if (argc < 3){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw output_image.raw [BytesPerPixel] [Size1] [Size2] noisefreeimage.raw" << endl;
        return 0;
    }
    
    // Check if image is grayscale or color
    if (argc < 4){
        BytesPerPixel = 1; // default is grey image
    }
    else {
        BytesPerPixel = atoi(argv[3]);
        // Check if size is specified
        if (argc >= 5){
            Size1 = atoi(argv[4]);
            Size2 = atoi(argv[5]);
        }
    }
    
    // Allocate image data array
	unsigned char Imageextend[Size1+2][Size2+2][BytesPerPixel];
	unsigned char Imagedata[Size1][Size2][BytesPerPixel];
	unsigned char OImage[Size1][Size2][BytesPerPixel];
    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
    fclose(file);

	if (!(file = fopen(argv[6], "rb"))) {
		cout << "Cannot open file: " << argv[6] << endl;
		exit(1);
	}
	fread(OImage, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
	fclose(file);
    
    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    
    for(int i=1;i<=Size1;i++){
        for(int j=1;j<=Size2;j++){
            for (int k=0;k<3;k++){
                Imageextend[i][j][k]=Imagedata[i-1][j-1][k];
                
            }
        }
    }
    for(int j=1;j<=Size2;j++){
        for(int k=0;k<3;k++){
            Imageextend[0][j][k]=Imageextend[1][j][k];
            
        }
    }
    for(int j=1;j<=Size2;j++){
        for(int k=0;k<3;k++){
            Imageextend[Size1+1][j][k]=Imageextend[Size1][j][k];
            
        }
    }
    for (int i =0;i<(Size1+2);i++){
        for (int k=0;k<3;k++){
            Imageextend[i][0][k]=Imageextend[i][1][k];
        }
    }
    for (int i =0;i<(Size1+2);i++){
        for (int k=0;k<3;k++){
            Imageextend[i][Size2+1][k]=Imageextend[i][Size2][k];
        }
    }

	//Gaussian Filter for Red Channel

	for (int i = 0; i < Size1; i++) {
		for (int j = 0; j < Size2; j++) {
			
				Imagedata[i][j][0] = (Imageextend[i][j][0] * gf[0][0] + Imageextend[i][j + 1][0] * gf[0][1] +
					Imageextend[i][j + 2][0] * gf[0][2] + Imageextend[i + 1][j][0] *gf[1][0] +
					Imageextend[i + 1][j + 1][0] * gf[1][1] + Imageextend[i + 1][j + 2][0] * gf[1][2] +
					Imageextend[i + 2][j][0] * gf[2][0] + Imageextend[i + 2][j + 1][0] * gf[2][1] +
					Imageextend[i + 2][j + 2][0] * gf[2][2]) / 16;
			
		}
	}

	//Mean Filter for Green Channel

	/*for (int i = 0; i < Size1; i++) {
		for (int j = 0; j < Size2; j++) {
			
				Imagedata[i][j][1] = (Imageextend[i][j][1] * mf[0][0] + Imageextend[i][j + 1][1] * mf[0][1] +
					Imageextend[i][j + 2][1] * mf[0][2] + Imageextend[i + 1][j][1] * mf[1][0] +
					Imageextend[i + 1][j + 1][1] * mf[1][1] + Imageextend[i + 1][j + 2][1] * mf[1][2] +
					Imageextend[i + 2][j][1] * mf[2][0] + Imageextend[i + 2][j + 1][1] * mf[2][1] +
					Imageextend[i + 2][j + 2][1] * mf[2][2]) / 9;
			
		}
	}*/


	int Med1[9];
	for (int i = 0; i < Size1; i++) {
		for (int j = 0; j < Size2; j++) {

			Med1[0] = Imageextend[i][j][1];
			Med1[1] = Imageextend[i][j + 1][1];
			Med1[2] = Imageextend[i][j + 2][1];
			Med1[3] = Imageextend[i + 1][j][1];
			Med1[4] = Imageextend[i + 1][j + 1][1];
			Med1[5] = Imageextend[i + 1][j + 2][1];
			Med1[6] = Imageextend[i + 2][j][1];
			Med1[7] = Imageextend[i + 2][j + 1][1];
			Med1[8] = Imageextend[i + 2][j + 2][1];
			Imagedata[i][j][1] = Median(Med1, 9);

		}
	}

	/*for (int i = 0; i < Size1; i++) {
		for (int j = 0; j < Size2; j++) {

			Imagedata[i][j][1] = (Imageextend[i][j][1] * gf[0][0] + Imageextend[i][j + 1][1] * gf[0][1] +
				Imageextend[i][j + 2][1] * gf[0][2] + Imageextend[i + 1][j][1] * gf[1][0] +
				Imageextend[i + 1][j + 1][1] * gf[1][1] + Imageextend[i + 1][j + 2][1] * gf[1][2] +
				Imageextend[i + 2][j][1] * gf[2][0] + Imageextend[i + 2][j + 1][1] * gf[2][1] +
				Imageextend[i + 2][j + 2][1] * gf[2][2]) / 16;

		}
	}*/

	//Meadian Filter for Blue Channel

	int Med[9];
	for (int i = 0; i < Size1; i++) {
		for (int j = 0; j < Size2; j++) {
			
				Med[0] = Imageextend[i][j][2];
				Med[1] = Imageextend[i][j+1][2];
				Med[2] = Imageextend[i][j+2][2];
				Med[3] = Imageextend[i+1][j][2];
				Med[4] = Imageextend[i+1][j+1][2];
				Med[5] = Imageextend[i+1][j+2][2];
				Med[6] = Imageextend[i+2][j][2];
				Med[7] = Imageextend[i+2][j+1][2];
				Med[8] = Imageextend[i+2][j+2][2];
				Imagedata[i][j][2] = Median(Med, 9);
			
		}
	}

	//PSNR
	double tempr = 0;
	double temp1r = 0;
	double MSEr;
	double PSNRr;
	double tempb = 0;
	double temp1b = 0;
	double MSEb;
	double PSNRb;
	double tempg = 0;
	double temp1g = 0;
	double MSEg;
	double PSNRg;
	for (int i = 0; i <= Size1; i++) {
		for (int j = 0; j <= Size2; j++) {
			tempr = pow((OImage[i][j][0] - Imagedata[i][j][0]), 2);
			temp1r += tempr;

			tempg = pow((OImage[i][j][1] - Imagedata[i][j][1]), 2);
			temp1g += tempg;

			tempb = pow((OImage[i][j][2] - Imagedata[i][j][2]), 2);
			temp1b += tempb;
			
		}
	}
	//cout << temp1 << endl;
	MSEr = (1 / ((double)Size1*(double)Size2))*temp1r;
	MSEg = (1 / ((double)Size1*(double)Size2))*temp1g;
	MSEb = (1 / ((double)Size1*(double)Size2))*temp1b;

	//cout << MSE << endl;
	PSNRr = 10 * log10(pow(255, 2) / MSEr);
	PSNRg = 10 * log10(pow(255, 2) / MSEg);
	PSNRb = 10 * log10(pow(255, 2) / MSEb);
	cout << PSNRr <<"   "<<PSNRg<<"   "<<PSNRb<< endl;
    // Write image data (filename specified by second argument) from image data matrix
    
    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(Imagedata, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
    fclose(file);
    
    return 0;
}


int Median(int array[], int Size) {
	
	int* Sort = new int[Size];
	for (int i = 0; i < Size; i++) {
		Sort[i] = array[i];
	}
	for (int i = Size - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (Sort[j] > Sort[j + 1]) {
				int Temp = Sort[j];
				Sort[j] = Sort[j + 1];
				Sort[j + 1] = Temp;
			}
		}
	}

	
	int Median = 0;
	if ((Size % 2) == 0) {
		Median = (Sort[Size / 2] + Sort[(Size / 2) - 1]) / 2.0;
	}
	else {
		Median = Sort[Size / 2];
	}
	delete[] Sort;
	return Median;
}
