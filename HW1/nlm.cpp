// This sample code reads in image data from a RAW image file and 
		cout << "Cannot open file: " << argv[6] << endl;
		exit(1);
	}
	fread(OImage, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
	fclose(file);
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
	cout << PSNRr << "   " << PSNRg << "   " << PSNRb << endl;