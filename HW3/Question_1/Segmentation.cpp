// This sample code reads in image data from a RAW image file and // writes it into another file// NOTE:	The code assumes that the image is of size 256 x 256 and is in the//			RAW format. You will need to make corresponding changes to//			accommodate images of different sizes and/or types#include <stdio.h>#include <iostream>#include <stdlib.h>#include <math.h>#include <fstream>using namespace std;int **kernel1(int x, int y);int** DynamicMem(int height, int width){	int **Image = new int *[height];	for (int i = 0; i < height; i++) {		Image[i] = new int[width];		for (int j = 0; j < width; j++) {			Image[i][j] = 0;		}	}	return Image;}double** DynamicMem_double(int height, int width){		double **Image = new double *[height];	for (int i = 0; i < height; i++) {		Image[i] = new double[width];		for (int j = 0; j < width; j++) {			Image[i][j] = 0;		}	}	return Image;}double*** Dynamic_3d(int height, int width,int length){		double ***Image = new double **[height];	for (int i = 0; i < height; i++) {		*Image[i] = new double [width];		for (int j = 0; j < width; j++) {			Image[i][j] = new double [length];			for (int k = 0; k < length; k++) {				Image[i][j][k] = 0;			}		}	}	return Image;}double* d_array(int length) {	double *arr = new double[length];	for (int i = 0; i < length; i++) {		arr[i] = 0;	}	return arr;}double Energy[350][590][25];double Energy1[350][590][25];int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Height,Width;		// Check for proper syntax	if (argc < 3) {		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel] [Height] [Width]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4) {		BytesPerPixel = 1; // default is grey image	}	else {		BytesPerPixel = atoi(argv[3]);		// Check if size is specified		if (argc >= 5) {			Height = atoi(argv[4]);			Width = atoi(argv[5]);		}	}	// Allocate image data array	unsigned char Image[Height][Width][BytesPerPixel];	unsigned char GImage[Height][Width];	// Read image (filename specified by first argument) into image data matrix	if (!(file = fopen(argv[1], "rb"))) {		cout << "Cannot open file: " << argv[1] << endl;		exit(1);	}	fread(Image, sizeof(unsigned char), Height*Width*BytesPerPixel, file);	fclose(file);	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////	// Grey Scale Conversion	double sum;	for (int i = 0; i < Height; i++) {		for (int j = 0; j < Width; j++) {			sum = 0.2989*(double)Image[i][j][0] + 0.5870*(double)Image[i][j][1] + 0.1140*(double)Image[i][j][2];			GImage[i][j] = sum;		}	}		double **Texture = new double *[Height];	for (int i = 0; i < Height; i++) {		Texture[i] = new double[Width];	}	double Text[Height][Width];	//double ImageExtend[Height+4][Width+4];	//double ImageExtend13[Height + 12][Width + 12];*/	//double **Text = new double *[Height];	//for (int i = 0; i < Height; i++) {	//	Text[i] = new double[Width];	//}	//double **Text = DynamicMem_double(Height, Width);	//double **ImageExtend = new double *[Height + 4];	//for (int i = 0; i < (Height + 4); i++) {	//	ImageExtend[i] = new double[Width + 4];	//}	double **ImageExtend= DynamicMem_double((Height+4), (Width+4));	//double **ImageExtend13 = new double *[Height + 12];	//for (int i = 0; i < (Height + 12); i++) {	//	ImageExtend13[i] = new double[Width + 12];	//}	double **ImageExtend13 = DynamicMem_double((Height + 12), (Width + 12));	double **ImageExtend15 = DynamicMem_double((Height + 14), (Width + 14));	double **ImageExtend9 = DynamicMem_double((Height + 8), (Width + 8));	//double ***Energy = Dynamic_3d(Height, Width, 25);			for (int i = 0; i < Height; i++) {		for (int j = 0; j < Width; j++) {			Texture[i][j] = (double)GImage[i][j];		}	}	double global_mean = 0;	for (int i = 0; i < Height; i++) {		for (int j = 0; j < Width; j++) {			global_mean += Texture[i][j];		}	}	global_mean /= (Height*Width);	for (int i = 0; i < Height; i++) {		for (int j = 0; j < Width; j++) {			Text[i][j] = Texture[i][j] - global_mean;		}	}	for (int i = 0; i < Height; i++) {		for (int j = 0; j < Width; j++) {			ImageExtend[i + 2][j + 2] = Text[i][j];		}	}	for (int j = 0; j < Width; j++) {		ImageExtend[0][j + 2] = Text[0][j];		ImageExtend[1][j + 2] = Text[0][j];		ImageExtend[Height + 2][j + 2] = Text[Height - 1][j];		ImageExtend[Height + 3][j + 2] = Text[Height - 1][j];	}	for (int i = 0; i < (Height + 4); i++) {		ImageExtend[i][0] = ImageExtend[i][2];		ImageExtend[i][1] = ImageExtend[i][2];		ImageExtend[i][Width + 2] = ImageExtend[i][Width + 1];		ImageExtend[i][Width + 3] = ImageExtend[i][Width + 1];	}	double conv = 0;	int counter = 0;	for (int p = 0; p < 5; p++) {		for (int q = 0; q < 5; q++) {						int **filter = kernel1(p, q);						for (int i = 2; i <= (Height + 1); i++) {				for (int j = 2; j <= (Width + 1); j++) {					for (int m = 0; m < 5; m++) {						for (int n = 0; n < 5; n++) {							conv += filter[m][n] * ImageExtend[i - 2 + m][j - 2 + n];						}					}					Text[i - 2][j - 2] = conv;					conv = 0;				}			}						// Image Extension for 13X13 Window			for (int i = 0; i < Height; i++) {				for (int j = 0; j < Width; j++) {					ImageExtend13[i + 6][j + 6] = Text[i][j];				}			}						for (int j = 0; j < Width; j++) {				for (int k = 0; k < 6; k++) {					ImageExtend13[k][j + 6] = Text[0][j];					ImageExtend13[Height + 6 + k][j + 6] = Text[Height - 1][j];				}			}			for (int i = 0; i < (Height + 8); i++) {				for (int k = 0; k < 6; k++) {					ImageExtend13[i][k] = ImageExtend13[i][6];					ImageExtend13[i][Width + 6 + k] = ImageExtend13[i][Width + 5];				}			}									double engy=0;						for (int i = 0; i < Height; i++) {								for (int j = 0; j < Width; j++) {										for (int k = 0; k < 12; k++) {												for (int l = 0; l < 12; l++) {														engy += pow(ImageExtend13[i + k][j + l], 2);													}					}					engy /= (double)(13*13*1.0);					Energy[i][j][counter] = (double)engy;				}			}						counter++;		}			}	for (int i = 0; i < Height; i++) {		for (int j = 0; j < Width; j++) {			for (int k = 24; k >= 0; k--) {				Energy1[i][j][k] = Energy[i][j][k]/Energy[i][j][0];			}		}	}	/*for (int i = 0; i < 10; i++) {		for (int j = 0; j < 10; j++) {			cout << Energy[i][j][1] << "  ";		}		cout << endl;	}*/	double **codebook = DynamicMem_double(5, 25);	double **cbdummy = DynamicMem_double(5, 25);	double **pca_cb = DynamicMem_double(5, 3);	double **pca_cb1 = DynamicMem_double(5, 3);		for (int i = 0; i < 25; i++) {		codebook[0][i] = Energy1[64][31][i];		codebook[1][i] = Energy1[87][282][i];		codebook[2][i] = Energy1[100][395][i];		codebook[3][i] = Energy1[152][228][i];		codebook[4][i] = Energy1[265][383][i];	}		double **map = DynamicMem_double(Height, Width);	int cou = 0;	while (cou < 10) {		cout << "Iteration " << (cou + 1) << endl;		double **a = DynamicMem_double(Height, Width);		double **b = DynamicMem_double(Height, Width);		double **c = DynamicMem_double(Height, Width);		double **d = DynamicMem_double(Height, Width);		double **e = DynamicMem_double(Height, Width);		double n0 = 0;		double n1 = 0;		double n2 = 0;		double n3 = 0;		double n4 = 0;		for (int i = 0; i < Height; i++) {			for (int j = 0; j < Width; j++) {				for (int k = 0; k < 25; k++) {					a[i][j] += pow((codebook[0][k] - Energy1[i][j][k]), 2);					b[i][j] += pow((codebook[1][k] - Energy1[i][j][k]), 2);					c[i][j] += pow((codebook[2][k] - Energy1[i][j][k]), 2);					d[i][j] += pow((codebook[3][k] - Energy1[i][j][k]), 2);					e[i][j] += pow((codebook[4][k] - Energy1[i][j][k]), 2);				}				a[i][j] = sqrt(a[i][j]);				b[i][j] = sqrt(b[i][j]);				c[i][j] = sqrt(c[i][j]);				d[i][j] = sqrt(d[i][j]);				e[i][j] = sqrt(e[i][j]);				if (a[i][j] < b[i][j] && a[i][j] < c[i][j] && a[i][j] < d[i][j] && a[i][j] < e[i][j]) {					map[i][j] = 0;				}				else if (b[i][j] < a[i][j] && b[i][j] < c[i][j] && b[i][j] < d[i][j] && b[i][j] < e[i][j]) {					map[i][j] = 1;				}				else if (c[i][j] < b[i][j] && c[i][j] < a[i][j] && c[i][j] < d[i][j] && c[i][j] < e[i][j]) {					map[i][j] = 2;				}				else if (d[i][j] < b[i][j] && d[i][j] < c[i][j] && d[i][j] < a[i][j] && d[i][j] < e[i][j]) {					map[i][j] = 3;				}				else if (e[i][j] < b[i][j] && e[i][j] < c[i][j] && e[i][j] < d[i][j] && e[i][j] < a[i][j]) {					map[i][j] = 4;				}			}		}		for (int i = 0; i < Height; i++) {			for (int j = 0; j < Width; j++) {				if (map[i][j] == 0) {					n0++;				}				else if (map[i][j] == 1) {					n1++;				}				else if (map[i][j] == 2) {					n2++;				}				else if (map[i][j] == 3) {					n3++;				}				else if (map[i][j] == 4) {					n4++;				}			}		}				double *cb0 = d_array(25);		double *cb1 = d_array(25);		double *cb2 = d_array(25);		double *cb3 = d_array(25);		double *cb4 = d_array(25);		for (int i = 0; i < Height; i++) {			for (int j = 0; j < Width; j++) {				if (map[i][j] == 0) {					for (int k = 0; k < 25; k++) {						cb0[k] += Energy1[i][j][k];					}				}				else if (map[i][j] == 1) {					for (int k = 0; k < 25; k++) {						cb1[k] += Energy1[i][j][k];					}				}				else if (map[i][j] == 2) {					for (int k = 0; k < 25; k++) {						cb2[k] += Energy1[i][j][k];					}				}				else if (map[i][j] == 3) {					for (int k = 0; k < 25; k++) {						cb3[k] += Energy1[i][j][k];					}				}				else if (map[i][j] == 4) {					for (int k = 0; k < 25; k++) {						cb4[k] += Energy1[i][j][k];					}				}			}		}		for (int j = 0; j < 25; j++) {			cbdummy[0][j] = cb0[j] / n0;			cbdummy[1][j] = cb1[j] / n1;			cbdummy[2][j] = cb2[j] / n2;			cbdummy[3][j] = cb3[j] / n3;			cbdummy[4][j] = cb4[j] / n4;		}				if (cbdummy[0][0] == codebook[0][0]) {			break;		}		else {			for (int i = 0; i < 5; i++) {				for (int j = 0; j < 25; j++) {					codebook[i][j] = cbdummy[i][j];				}			}		}		cou++;	}	for (int i = 0; i < 5; i++) {		for (int j = 0; j < 25; j++) {			cout << cbdummy[i][j] << "  ";		}		cout << endl;	}		ofstream file1;	file1.open("energy.txt");	for (int i = 0; i < Height; i++)	{		for (int j = 0; j < Width; j++)		{			for (int k = 0; k < 25; k++)			{				file1 << Energy1[i][j][k] << "\t";			}			file1 << endl;			file1 << endl;		}	}	file1.close();	double **pca_o = DynamicMem_double(Height*Width, 3);	ifstream file2;	file2.open("D:/HW3/k3.txt");	for (int i = 0; i < Height*Width; i++)	{		for (int j = 0; j < 3; j++)		{			file2 >> pca_o[i][j] ;					}		}	file2.close();	for (int i = 0; i < 3; i++) {		pca_cb[0][i] = pca_o[64 * Width + 31][i];		pca_cb[1][i] = pca_o[87 * Width + 282][i];		pca_cb[2][i] = pca_o[100 * Width + 395][i];		pca_cb[3][i] = pca_o[152 * Width + 228][i];		pca_cb[4][i] = pca_o[265 * Width + 383][i];	}	int cou1 = 0;	while (cou1 < 10) {		//cout << "Iteration " << (cou + 1) << endl;		double **a = DynamicMem_double(Height, Width);		double **b = DynamicMem_double(Height, Width);		double **c = DynamicMem_double(Height, Width);		double **d = DynamicMem_double(Height, Width);		double **e = DynamicMem_double(Height, Width);		int n0 = 0;		int n1 = 0;		int n2 = 0;		int n3 = 0;		int n4 = 0;		for (int i = 0; i < Height; i++) {			for (int j = 0; j < Width; j++) {				for (int k = 0; k < 3; k++) {					a[i][j] += pow((pca_cb[0][k] - pca_o[i*Width + j][k]), 2);					b[i][j] += pow((pca_cb[1][k] - pca_o[i*Width + j][k]), 2);					c[i][j] += pow((pca_cb[2][k] - pca_o[i*Width + j][k]), 2);					d[i][j] += pow((pca_cb[3][k] - pca_o[i*Width + j][k]), 2);					e[i][j] += pow((pca_cb[4][k] - pca_o[i*Width + j][k]), 2);				}				a[i][j] = sqrt(a[i][j]);				b[i][j] = sqrt(b[i][j]);				c[i][j] = sqrt(c[i][j]);				d[i][j] = sqrt(d[i][j]);				e[i][j] = sqrt(e[i][j]);				if (a[i][j] < b[i][j] && a[i][j] < c[i][j] && a[i][j] < d[i][j] && a[i][j] < e[i][j]) {					map[i][j] = 0;				}				else if (b[i][j] < a[i][j] && b[i][j] < c[i][j] && b[i][j] < d[i][j] && b[i][j] < e[i][j]) {					map[i][j] = 1;				}				else if (c[i][j] < b[i][j] && c[i][j] < a[i][j] && c[i][j] < d[i][j] && c[i][j] < e[i][j]) {					map[i][j] = 2;				}				else if (d[i][j] < b[i][j] && d[i][j] < c[i][j] && d[i][j] < a[i][j] && d[i][j] < e[i][j]) {					map[i][j] = 3;				}				else if (e[i][j] < b[i][j] && e[i][j] < c[i][j] && e[i][j] < d[i][j] && e[i][j] < a[i][j]) {					map[i][j] = 4;				}			}		}		for (int i = 0; i < Height; i++) {			for (int j = 0; j < Width; j++) {				if (map[i][j] == 0) {					n0++;				}				else if (map[i][j] == 1) {					n1++;				}				else if (map[i][j] == 2) {					n2++;				}				else if (map[i][j] == 3) {					n3++;				}				else if (map[i][j] == 4) {					n4++;				}			}		}		double *cb00 = d_array(3);		double *cb11 = d_array(3);		double *cb22 = d_array(3);		double *cb33 = d_array(3);		double *cb44 = d_array(3);		for (int i = 0; i < Height; i++) {			for (int j = 0; j < Width; j++) {				if (map[i][j] == 0) {					for (int k = 0; k < 3; k++) {						cb00[k] += pca_o[i*Width + j][k];					}				}				else if (map[i][j] == 1) {					for (int k = 0; k < 3; k++) {						cb11[k] += pca_o[i*Width + j][k];					}				}				else if (map[i][j] == 2) {					for (int k = 0; k < 3; k++) {						cb22[k] += pca_o[i*Width + j][k];					}				}				else if (map[i][j] == 3) {					for (int k = 0; k < 3; k++) {						cb33[k] += pca_o[i*Width + j][k];					}				}				else if (map[i][j] == 4) {					for (int k = 0; k < 3; k++) {						cb44[k] += pca_o[i*Width + j][k];					}				}			}		}		for (int j = 0; j < 3; j++) {			pca_cb1[0][j] = cb00[j] / n0;			pca_cb1[1][j] = cb11[j] / n1;			pca_cb1[2][j] = cb22[j] / n2;			pca_cb1[3][j] = cb33[j] / n3;			pca_cb1[4][j] = cb44[j] / n4;		}		if (pca_cb1[0][0] == pca_cb[0][0]) {			break;		}		else {			for (int i = 0; i < 5; i++) {				for (int j = 0; j < 25; j++) {					pca_cb[i][j] = pca_cb1[i][j];				}			}		}		cou1++;	}	for (int i = 0; i < Height; i++) {		for (int j = 0; j < Width; j++) {			if (map[i][j] == 0) {				Image[i][j][0] = 255;				Image[i][j][1] = 105;				Image[i][j][2] = 180;			}			else if (map[i][j] == 1) {				Image[i][j][0] = 123;				Image[i][j][1] = 104;				Image[i][j][2] = 238;			}			else if (map[i][j] == 2) {				Image[i][j][0] = 0;				Image[i][j][1] = 238;				Image[i][j][2] = 118;			}			else if (map[i][j] == 3) {				Image[i][j][0] = 238;				Image[i][j][1] = 238;				Image[i][j][2] = 0;			}			else if (map[i][j] == 4) {				Image[i][j][0] = 255;				Image[i][j][1] = 140;				Image[i][j][2] = 0;			}		}	}	//for (int i = 0; i < 10; i++) {	//	for (int j = 0; j < 10; j++) {	//		cout << Energy[i][j][1] << "  ";	//	}	//	cout << endl;	//}	// Write image data (filename specified by second argument) from image data matrix	if (!(file = fopen(argv[2], "wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}	fwrite(Image, sizeof(unsigned char), (Height)*(Width)*BytesPerPixel, file);	fclose(file);	return 0;}int **kernel1(int x, int y) {	int k1[5][1];	int k2[5];	int L5[5] = { 1, 4, 6, 4, 1 };	int E5[5] = { -1,-2,0,2,1 };	int S5[5] = { -1,0,2,0,-1 };	int W5[5] = { -1,2,0,-2,1 };	int R5[5] = { 1,-4,6,-4,1 };	int **kernel = DynamicMem(5, 5);	if (x == 0) {		for (int i = 0; i < 5; i++) {			k1[i][0] = L5[i];		}	}	else if (x == 1) {		for (int i = 0; i < 5; i++) {			k1[i][0] = E5[i];		}	}	else if (x == 2) {		for (int i = 0; i < 5; i++) {			k1[i][0] = S5[i];		}	}	else if (x == 3) {		for (int i = 0; i < 5; i++) {			k1[i][0] = W5[i];		}	}	else if (x == 4) {		for (int i = 0; i < 5; i++) {			k1[i][0] = R5[i];		}	}	if (y == 0) {		for (int i = 0; i < 5; i++) {			k2[i] = L5[i];		}	}	else if (y == 1) {		for (int i = 0; i < 5; i++) {			k2[i] = E5[i];		}	}	else if (y == 2) {		for (int i = 0; i < 5; i++) {			k2[i] = S5[i];		}	}	else if (y == 3) {		for (int i = 0; i < 5; i++) {			k2[i] = W5[i];		}	}	else if (y == 4) {		for (int i = 0; i < 5; i++) {			k2[i] = R5[i];		}	}	for (int i = 0; i < 5; i++) {		for (int j = 0; j < 5; j++) {			kernel[i][j] = k1[i][0] * k2[j];			//cout << kernel[i][j] << "  ";		}		//cout << endl;	}	return kernel;}