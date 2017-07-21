// This sample code reads in image data from a RAW image file and // writes it into another file// NOTE:	The code assumes that the image is of size 256 x 256 and is in the//			RAW format. You will need to make corresponding changes to//			accommodate images of different sizes and/or types#include <stdio.h>#include <iostream>#include <stdlib.h>#include <math.h>using namespace std;int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size1;	int Size2;	// Check for proper syntax	if (argc < 3) {		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel] [Size1] [Size2] noisefreeimage.raw" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4) {		BytesPerPixel = 1; // default is grey image	}	else {		BytesPerPixel = atoi(argv[3]);		// Check if size is specified		if (argc >= 5) {			Size1 = atoi(argv[4]);			Size2 = atoi(argv[5]);		}	}	double gf[3][3] = { {1/16.0,2/16.0,1/16.0},{2/16.0,4/16.0,2/16.0},{1/16.0,2/16.0,1/16.0} };	double h = 100;	// Allocate image data array	unsigned char Imagedata[Size1][Size2][BytesPerPixel];	unsigned char Imageextend[Size1 + 20][Size2 + 20][BytesPerPixel];	unsigned char OImage[Size1][Size2][BytesPerPixel];	//unsigned char Image[Size1 + 20][Size2 + 20][BytesPerPixel];	// Read image (filename specified by first argument) into image data matrix	if (!(file = fopen(argv[1], "rb"))) {		cout << "Cannot open file: " << argv[1] << endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);	fclose(file);	if (!(file = fopen(argv[6], "rb"))) {
		cout << "Cannot open file: " << argv[6] << endl;
		exit(1);
	}
	fread(OImage, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
	fclose(file);	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	for (int i = 10; i <= Size1+10; i++) {
		for (int j = 10; j <= Size2+10; j++) {
			for (int k = 0; k<3; k++) {
				Imageextend[i][j][k] = Imagedata[i - 10][j - 10][k];

			}
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 10; j <= Size2 + 10; j++) {
			for (int k = 0; k < 3; k++) {
				Imageextend[i][j][k] = Imageextend[10][j][k];
			}
		}
	}

	for (int i = Size1+10; i < Size1+20; i++) {
		for (int j = 10; j <= Size2 + 10; j++) {
			for (int k = 0; k < 3; k++) {
				Imageextend[i][j][k] = Imageextend[Size1+9][j][k];
			}
		}
	}

	for (int i = 0; i <= Size1 + 20; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 3; k++) {
				Imageextend[i][j][k] = Imageextend[i][10][k];
			}
		}
	}

	for (int i = 0; i <= Size1 + 20; i++) {
		for (int j = Size2+10; j < Size2+20; j++) {
			for (int k = 0; k < 3; k++) {
				Imageextend[i][j][k] = Imageextend[i][Size2+9][k];
			}
		}
	}
	unsigned char Imagered[Size1 + 20][Size2 + 20];	unsigned char Imagegreen[Size1 + 20][Size2 + 20];	unsigned char Imageblue[Size1 + 20][Size2 + 20];	int patchsize = 3;	int winsize = 21;	int exp1 = (winsize - 1) / 2;	int expansionpatch = (patchsize - 1) / 2;	double wp_red[19][19];	double wp_green[19][19];	double wp_blue[19][19];	for (int i = 0; i <= Size1 + 20; i++) {		for (int j = 0; j <= Size2+20; j++) {			Imagered[i][j] = Imageextend[i][j][0];			Imageblue[i][j] = Imageextend[i][j][2];			Imagegreen[i][j] = Imageextend[i][j][1];		}	}	unsigned char cp_red[patchsize][patchsize];	unsigned char np_red[patchsize][patchsize];	unsigned char cp_green[patchsize][patchsize];	unsigned char np_green[patchsize][patchsize];	unsigned char cp_blue[patchsize][patchsize];	unsigned char np_blue[patchsize][patchsize];	double redtemp,greentemp,bluetemp,rsum,gsum,bsum,rpixel,gpixel,bpixel;	for (int i = 0; i <= (Size1 + 2 * exp1 - winsize); i++) {		for (int j = 0; j <= (Size1 + 2 * exp1 - winsize); j++) {			for (int k = 0; k <= (winsize - patchsize); k++) {				for (int l = 0; l <= (winsize - patchsize); l++) {					for (int m = 0; m < patchsize; m++) {						for (int n = 0; n < patchsize; n++) {							cp_red[m][n] = Imagered[i + exp1 - expansionpatch + m][j + exp1 - expansionpatch + n];							np_red[m][n] = Imagered[i + k + m][j + l + n];							redtemp += gf[m][n] * pow((cp_red[m][n] - np_red[m][n]), 2);							cp_green[m][n] = Imagegreen[i + exp1 - expansionpatch + m][j + exp1 - expansionpatch + n];							np_green[m][n] = Imagegreen[i + k + m][j + l + n];							greentemp += gf[m][n] * pow((cp_green[m][n] - np_green[m][n]), 2);							cp_blue[m][n] = Imageblue[i + exp1 - expansionpatch + m][j + exp1 - expansionpatch + n];							np_blue[m][n] = Imageblue[i + k + m][j + l + n];							bluetemp += gf[m][n] * pow((cp_blue[m][n] - np_blue[m][n]), 2);						}					}					wp_red[k][l] = redtemp;					rsum += exp(-wp_red[k][l] / pow(h, 2));					wp_green[k][l] = greentemp;					gsum += exp(-wp_green[k][l] / pow(h, 2));					wp_blue[k][l] = bluetemp;					bsum += exp(-wp_blue[k][l] / pow(h, 2));				}			}			for (int p = 0; p < winsize - patchsize; p++) {				for (int q = 0; q < winsize - patchsize; q++) {					rpixel += ((exp(-wp_red[p][q] / pow(h, 2))) / rsum)*Imagered[p + expansionpatch + i][q + expansionpatch + j];					gpixel += ((exp(-wp_green[p][q] / pow(h, 2))) / gsum)*Imagegreen[p + expansionpatch + i][q + expansionpatch + j];					bpixel += ((exp(-wp_blue[p][q] / pow(h, 2))) / bsum)*Imageblue[p + expansionpatch + i][q + expansionpatch + j];				}			}			Imagered[i][j] = rpixel;			rpixel = 0;			redtemp = 0;			rsum = 0;			Imagegreen[i][j] = gpixel;			gpixel = 0;			greentemp = 0;			gsum = 0;			Imageblue[i][j] = bpixel;			bpixel = 0;			bluetemp = 0;			bsum = 0;		}	}			for (int i = 0; i <= Size1 + 20; i++) {		for (int j = 0; j <= Size2 + 20; j++) {			Imageextend[i][j][0] = Imagered[i][j];			Imageextend[i][j][1] = Imagegreen[i][j];			Imageextend[i][j][2] = Imageblue[i][j];		}	}	for (int i = 0; i < Size1; i++) {		for (int j = 0; j < Size2; j++) {			for (int k = 0; k < 3; k++) {				Imagedata[i][j][k] = Imageextend[i + 10][j + 10][k];			}		}	}	//PSNR
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
	cout << PSNRr << "   " << PSNRg << "   " << PSNRb << endl;	// Write image data (filename specified by second argument) from image data matrix	if (!(file = fopen(argv[2], "wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}	fwrite(Imagedata, sizeof(unsigned char), (Size1)*(Size2)*BytesPerPixel, file);	fclose(file);	return 0;}