#include <stdio.h>#include <iostream>#include <stdlib.h>#include <math.h>using namespace std;int **kernel1(int x, int y);int** DynamicMem(int height,int width){	int **Image = new int *[height];	for (int i = 0; i < height;i++) {		Image[i] = new int[width];		for (int j = 0; j < width; j++) {			Image[i][j] = 0;		}	}	return Image;}double** DynamicMem_double(int height, int width){	double **Image = new double *[height];	for (int i = 0; i < height; i++) {		Image[i] = new double[width];		for (int j = 0; j < width; j++) {			Image[i][j] = 0;		}	}	return Image;}double* d_array(int length) {	double *arr = new double[length];	for (int i = 0; i < length; i++) {		arr[i] = 0;	}	return arr; }int main(int argc, char *argv[]){	// Define file pointer and variables	double **Energy = DynamicMem_double(18, 25);	double **EnergyTest = DynamicMem_double(6, 25);	double **cbdummy = DynamicMem_double(4, 25);	FILE *file;	int BytesPerPixel;	int Height, Width;	// Check for proper syntax	if (argc < 3) {		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name texture1.raw texture2.raw texture3.raw texture4.raw texture5.raw texture6.raw texture7.raw texture8.raw texture9.raw texture10.raw texture11.raw texture12.raw TextureA.raw TextureB.raw TextureC.raw TextureD.raw TextureE.raw TextureF.raw [BytesPerPixel] [Height] [Width]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4) {		BytesPerPixel = 1; // default is grey image	}	else {		BytesPerPixel = atoi(argv[19]);		// Check if size is specified		if (argc >= 5) {			Height = atoi(argv[20]);			Width = atoi(argv[21]);		}	}		double **Texture = new double *[Height];	for (int i = 0; i < Height; i++) {		Texture[i] = new double [Width];	}		// Allocate image data array	unsigned char Imagedata[Height][Width];	double ImageExtend[Height+4][Width+4];	double Text[Height][Width];	double mean[25];	double std_dev[25];	// Read image (filename specified by first argument) into image data matrix	for (int z = 1; z < 19; z++) {		if (!(file = fopen(argv[z], "rb"))) {			cout << "Cannot open file: " << argv[z] << endl;			exit(1);		}		fread(Imagedata, sizeof(unsigned char), Height*Width, file);		fclose(file);				for (int i = 0; i < Height; i++) {			for (int j = 0; j < Width; j++){				Texture[i][j] = (double)Imagedata[i][j];			}		}				double global_mean = 0;		for (int i = 0; i < Height; i++) {			for (int j = 0; j < Width; j++) {				global_mean += Texture[i][j];			}		}		global_mean /= (Height*Width);				for (int i = 0; i < Height; i++) {			for (int j = 0; j < Width; j++) {				Text[i][j] = Texture[i][j] - global_mean;							}					}		// Image Extension		for (int i = 0; i < Height; i++) {			for (int j = 0; j < Width; j++) {				ImageExtend[i + 2][j + 2] = Text[i][j];			}		}		for (int j = 0; j < Width; j++) {			ImageExtend[0][j + 2] = Text[0][j];			ImageExtend[1][j + 2] = Text[0][j];			ImageExtend[Height + 2][j + 2] = Text[Height - 1][j];			ImageExtend[Height + 3][j + 2] = Text[Height - 1][j];		}		for (int i = 0; i < (Height + 4); i++) {			ImageExtend[i][0] = ImageExtend[i][2];			ImageExtend[i][1] = ImageExtend[i][2];			ImageExtend[i][Width + 2] = ImageExtend[i][Width + 1];			ImageExtend[i][Width + 3] = ImageExtend[i][Width + 1];		}				int b = 0;		double conv=0;				for (int p = 0; p < 5; p++) {					for (int q = 0; q < 5; q++) {						int **filter = kernel1(p, q);						for (int i = 2; i <= (Height + 1); i++) {							for (int j = 2; j <= (Width + 1); j++) {																for (int m = 0; m < 5; m++) {									for (int n = 0; n < 5; n++) {										conv += filter[m][n] * ImageExtend[i - 2 + m][j - 2 + n];									}								}								Text[i - 2][j - 2] = conv;								conv = 0;							}						}						double engy;						for (int k = 0; k < Height; k++) {							for(int l = 0; l < Width; l++) {								engy += pow(Text[k][l], 2);							}						}						engy /= (Height*Width);						Energy[z - 1][b] = engy;												b++;											}									}	}	/*for (int i = 0; i < 18; i++) {		for (int j = 0; j < 25; j++) {			cout << Energy[i][j] << "  ";		}		cout << endl;	}*/	//cout << "Mean" << endl;	for (int i = 12; i < 18; i++) {		for (int j = 0; j < 25; j++) {			EnergyTest[i - 12][j] = Energy[i][j];		}	}	// Normalising	for (int j = 0; j < 25; j++) {		double sum = 0;		for (int i = 0; i < 12; i++) {			sum += Energy[i][j];		}		mean[j] = sum / 12;	}	for (int j = 0; j < 25; j++) {		double sum = 0;		for (int i = 0; i < 12; i++) {			sum += pow((Energy[i][j] - mean[j]), 2);		}		std_dev[j] = sqrt(sum / 12.0);			}	for (int j = 0; j < 25; j++) {		for (int i = 0; i < 12; i++) {			Energy[i][j] = (Energy[i][j] - mean[j]) / std_dev[j];		}	}	// Normalizing Test Energy	for (int j = 0; j < 25; j++) {		double sum = 0;		for (int i = 0; i < 6; i++) {			sum += EnergyTest[i][j];		}		mean[j] = sum / 6;	}	for (int j = 0; j < 25; j++) {		double sum = 0;		for (int i = 0; i < 6; i++) {			sum += pow((EnergyTest[i][j] - mean[j]), 2);		}		std_dev[j] = sqrt(sum / 6.0);	}	for (int j = 0; j < 25; j++) {		for (int i = 0; i < 6; i++) {			EnergyTest[i][j] = (EnergyTest[i][j] - mean[j]) / std_dev[j];		}	}	/*for (int i = 0; i < 12; i++) {		for (int j = 0; j < 25; j++) {			cout << Energy[i][j] << "  ";		}		cout << endl;	}*/	double codebook[4][25];	int k = 0;	for (int i = 0; i < 4; i++) {		for (int j = 0; j < 25; j++) {			codebook[i][j] = Energy[k][j];					}		k += 3;	}	// Euclidean Distance	int cou = 0;	cout << "******************** UnSupervised Learning*********************" << endl;	cout << "*************Texture1 to Texture12****************" << endl;	while (cou < 10) {		cout << "Iteration:" << (cou + 1) << endl;		double a[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };		double b[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };		double c[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };		double d[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };		for (int i = 0; i < 12; i++) {			for (int j = 0; j < 25; j++) {				a[i] += pow((codebook[0][j] - Energy[i][j]), 2);				b[i] += pow((codebook[1][j] - Energy[i][j]), 2);				c[i] += pow((codebook[2][j] - Energy[i][j]), 2);				d[i] += pow((codebook[3][j] - Energy[i][j]), 2);			}			a[i] = sqrt(a[i]);			b[i] = sqrt(b[i]);			c[i] = sqrt(c[i]);			d[i] = sqrt(d[i]);			//cout << "a[i]    " << a[i] << "    b[i]    " << b[i] << "    c[i]    " << c[i] << "    d[i]    " << d[i] << endl;		}		double map[12];		for (int i = 0; i < 12; i++) {			if (a[i] < b[i] && a[i] < c[i] && a[i] < d[i]) {				map[i] = 0;			}			else if (b[i] < a[i] && b[i] < c[i] && b[i] < d[i]) {				map[i] = 1;			}			else if (c[i] < b[i] && c[i] < a[i] && c[i] < d[i]) {				map[i] = 2;			}			else if (d[i] < b[i] && d[i] < c[i] && d[i] < a[i]) {				map[i] = 3;			}			//cout << map[i] << endl;		}		double n0 = 0;		double n1 = 0;		double n2 = 0;		double n3 = 0;		for (int i = 0; i < 12; i++) {			if (map[i] == 0) {				cout << "Texture" << (i + 1) << " is Bark" << endl;				n0++;			}			else if (map[i] == 1) {				n1++;				cout << "Texture" << (i + 1) << " is Grass" << endl;			}			else if (map[i] == 2) {				n2++;				cout << "Texture" << (i + 1) << " is Straw" << endl;			}			else if (map[i] == 3) {				n3++;				cout << "Texture" << (i + 1) << " is Sand" << endl;			}		}		double *cb0 = d_array(25);		double *cb1 = d_array(25);		double *cb2 = d_array(25);		double *cb3 = d_array(25);		int v = 0;		while (v < 12) {			if (map[v] == 0) {				for (int j = 0; j < 25; j++) {					cb0[j] += Energy[v][j];				}			}			else if (map[v] == 1) {				for (int j = 0; j < 25; j++) {					cb1[j] += Energy[v][j];				}			}			else if (map[v] == 2) {				for (int j = 0; j < 25; j++) {					cb2[j] += Energy[v][j];				}			}			else if (map[v] == 3) {				for (int j = 0; j < 25; j++) {					cb3[j] += Energy[v][j];				}			}			v++;		}		for (int j = 0; j < 25; j++) {			cbdummy[0][j] = cb0[j] / n0;			cbdummy[1][j] = cb1[j] / n1;			cbdummy[2][j] = cb2[j] / n2;			cbdummy[3][j] = cb3[j] / n3;		}		if (cbdummy[0][0] == codebook[0][0]) {			break;		}		else {			for (int i = 0; i < 4; i++) {				for (int j = 0; j < 25; j++) {					codebook[i][j] = cbdummy[i][j];				}			}		}		cou++;	}	// For Test Images	double *at = d_array(6);	double *bt = d_array(6);	double *ct = d_array(6);	double *dt = d_array(6);	for (int i = 0; i < 6; i++) {		for (int j = 0; j < 25; j++) {			at[i] += pow((codebook[0][j] - EnergyTest[i][j]), 2);			bt[i] += pow((codebook[1][j] - EnergyTest[i][j]), 2);			ct[i] += pow((codebook[2][j] - EnergyTest[i][j]), 2);			dt[i] += pow((codebook[3][j] - EnergyTest[i][j]), 2);		}		at[i] = sqrt(at[i]);		bt[i] = sqrt(bt[i]);		ct[i] = sqrt(ct[i]);		dt[i] = sqrt(dt[i]);		//cout << "a[i]    " << a[i] << "    b[i]    " << b[i] << "    c[i]    " << c[i] << "    d[i]    " << d[i] << endl;	}	double mapt[6];	for (int i = 0; i < 6; i++) {		if (at[i] < bt[i] && at[i] < ct[i] && at[i] < dt[i]) {			mapt[i] = 0;		}		else if (bt[i] < at[i] && bt[i] < ct[i] && bt[i] < dt[i]) {			mapt[i] = 1;		}		else if (ct[i] < bt[i] && ct[i] < at[i] && ct[i] < dt[i]) {			mapt[i] = 2;		}		else if (dt[i] < bt[i] && dt[i] < ct[i] && dt[i] < at[i]) {			mapt[i] = 3;		}		//cout << mapt[i] << endl;	}	string ch;	string ty;	cout << "*************TextureA to TextureF****************" << endl;	for (int i = 0; i < 6; i++) {		if (i == 0) {			ch = "A";		}		else if (i == 1) {			ch = "B";		}		else if (i == 2) {			ch = "C";		}		else if (i == 3) {			ch = "D";		}		else if (i == 4) {			ch = "E";		}		else if (i == 5) {			ch = "F";		}		if (mapt[i] == 0) {			ty = "Bark";		}		else if (mapt[i] == 1) {			ty = "Grass";		}		else if (mapt[i] == 2) {			ty = "Straw";		}		else if (mapt[i] == 3) {			ty = "Sand";		}		cout << "Texture" << ch << " is " << ty << endl;	}	cout << "********************Supervised Learning*************************" << endl;	double codebooks[4][25];	for (int j = 0; j < 25; j++) {		codebooks[0][j] = (Energy[0][j] + Energy[1][j] + Energy[2][j]) / 3;		codebooks[1][j] = (Energy[3][j] + Energy[4][j] + Energy[5][j]) / 3;		codebooks[2][j] = (Energy[6][j] + Energy[7][j] + Energy[8][j]) / 3;		codebooks[3][j] = (Energy[9][j] + Energy[10][j] + Energy[11][j]) / 3;	}	// For Test Images	double *at1 = d_array(6);	double *bt1 = d_array(6);	double *ct1 = d_array(6);	double *dt1 = d_array(6);	for (int i = 0; i < 6; i++) {		for (int j = 0; j < 25; j++) {			at1[i] += pow((codebooks[0][j] - EnergyTest[i][j]), 2);			bt1[i] += pow((codebooks[1][j] - EnergyTest[i][j]), 2);			ct1[i] += pow((codebooks[2][j] - EnergyTest[i][j]), 2);			dt1[i] += pow((codebooks[3][j] - EnergyTest[i][j]), 2);		}		at1[i] = sqrt(at1[i]);		bt1[i] = sqrt(bt1[i]);		ct1[i] = sqrt(ct1[i]);		dt1[i] = sqrt(dt1[i]);		//cout << "a[i]    " << a[i] << "    b[i]    " << b[i] << "    c[i]    " << c[i] << "    d[i]    " << d[i] << endl;	}	double mapt1[6];	for (int i = 0; i < 6; i++) {		if (at1[i] < bt1[i] && at1[i] < ct1[i] && at1[i] < dt1[i]) {			mapt1[i] = 0;		}		else if (bt1[i] < at1[i] && bt1[i] < ct1[i] && bt1[i] < dt1[i]) {			mapt1[i] = 1;		}		else if (ct1[i] < bt1[i] && ct1[i] < at1[i] && ct1[i] < dt1[i]) {			mapt1[i] = 2;		}		else if (dt1[i] < bt1[i] && dt1[i] < ct1[i] && dt1[i] < at1[i]) {			mapt1[i] = 3;		}		//cout << mapt[i] << endl;	}		cout << "*************TextureA to TextureF****************" << endl;	for (int i = 0; i < 6; i++) {		if (i == 0) {			ch = "A";		}		else if (i == 1) {			ch = "B";		}		else if (i == 2) {			ch = "C";		}		else if (i == 3) {			ch = "D";		}		else if (i == 4) {			ch = "E";		}		else if (i == 5) {			ch = "F";		}		if (mapt1[i] == 0) {			ty = "Bark";		}		else if (mapt1[i] == 1) {			ty = "Grass";		}		else if (mapt1[i] == 2) {			ty = "Straw";		}		else if (mapt1[i] == 3) {			ty = "Sand";		}		cout << "Texture" << ch << " is " << ty << endl;	}}int **kernel1(int x, int y) {	int k1[5][1];	int k2[5];	int L5[5] = { 1, 4, 6, 4, 1 };	int E5[5] = { -1,-2,0,2,1 };	int S5[5] = { -1,0,2,0,-1 };	int W5[5] = { -1,2,0,-2,1 };	int R5[5] = { 1,-4,6,-4,1 };	int **kernel = DynamicMem(5, 5);	if (x == 0){		for (int i = 0; i < 5; i++) {			k1[i][0] = L5[i];		}	}	else if (x == 1){		for (int i = 0; i < 5; i++) {			k1[i][0] = E5[i];		}	}	else if (x == 2){		for (int i = 0; i < 5; i++) {			k1[i][0] = S5[i];		}	}	else if (x == 3){		for (int i = 0; i < 5; i++) {			k1[i][0] = W5[i];		}	}	else if (x == 4){		for (int i = 0; i < 5; i++) {			k1[i][0] = R5[i];		}	}	if (y == 0) {		for (int i = 0; i < 5; i++) {			k2[i] = L5[i];		}	}	else if (y == 1) {		for (int i = 0; i < 5; i++) {			k2[i] = E5[i];		}	}	else if (y == 2) {		for (int i = 0; i < 5; i++) {			k2[i] = S5[i];		}	}	else if (y == 3) {		for (int i = 0; i < 5; i++) {			k2[i] = W5[i];		}	}	else if (y == 4) {		for (int i = 0; i < 5; i++) {			k2[i] = R5[i];		}	}	for (int i = 0; i < 5; i++) {		for (int j = 0; j < 5; j++) {			kernel[i][j] = k1[i][0]*k2[j];			//cout << kernel[i][j] << "  ";					}		//cout << endl;	}		return kernel;}