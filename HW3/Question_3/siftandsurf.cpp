#include <stdio.h>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include "stdafx.h"
#include <math.h>

using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;

void readme();
double *histo(Mat des1, Mat dictionary);
double* d_array(int length) {	double *arr = new double[length];	for (int i = 0; i < length; i++) {		arr[i] = 0;	}	return arr;}

/** @function main */
int main(int argc, char** argv)
{
	if (argc != 5)
	{
		readme(); return -1;
	}

	Mat img_1 = imread(argv[1], IMREAD_GRAYSCALE);
	Mat img_2 = imread(argv[2], IMREAD_GRAYSCALE);
	Mat img_3 = imread(argv[3], IMREAD_GRAYSCALE);
	Mat img_4 = imread(argv[4], IMREAD_GRAYSCALE);

	if (!img_1.data || !img_2.data || !img_3.data || !img_4.data)
	{
		std::cout << " --(!) Error reading images " << std::endl; return -1;
	}

	//-- Step 1: Detect the keypoints using SURF Detector
	int minHessian = 3000;
	//int minHessian1 = 9000;
	Ptr<SIFT> detector = SIFT::create(minHessian);
	Ptr<SURF> detector1 = SURF::create(minHessian);
	
	std::vector<KeyPoint> keypoints_sift1, keypoints_sift2, keypoints_surf1, keypoints_surf2, kp_siftc1, kp_siftc2, kp_surfc1, kp_surfc2;
	Mat des1; Mat des_c1;
	Mat des2; Mat des_c2;
	Mat des3; Mat des_c11;
	Mat des4; Mat des_c22;

	detector->detect(img_1, keypoints_sift1);
	detector->detect(img_2, keypoints_sift2);
	detector1->detect(img_1, keypoints_surf1);
	detector1->detect(img_2, keypoints_surf2);
	detector->detect(img_3, kp_siftc1);
	detector->detect(img_4, kp_siftc2);
	detector1->detect(img_3, kp_surfc1);
	detector1->detect(img_4, kp_surfc2);

	detector->compute(img_1, keypoints_sift1,des1);
	detector->compute(img_2, keypoints_sift2,des2);
	detector1->compute(img_1, keypoints_surf1,des3);
	detector1->compute(img_2, keypoints_surf2,des4);
	detector->compute(img_3, kp_siftc1, des_c1);
	detector->compute(img_4, kp_siftc2, des_c2);
	detector1->compute(img_3, kp_surfc1, des_c11);
	detector1->compute(img_4, kp_surfc2, des_c22);

	//-- Draw keypoints
	Mat img_keypoints_sift1; Mat img_keypoints_sift2;
	Mat img_keypoints_surf1; Mat img_keypoints_surf2;
	Mat img_keypoints_siftc1; Mat img_keypoints_siftc2;
	Mat img_keypoints_surfc1; Mat img_keypoints_surfc2;
	
	drawKeypoints(img_1, keypoints_sift1, img_keypoints_sift1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(img_2, keypoints_sift2, img_keypoints_sift2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(img_1, keypoints_surf1, img_keypoints_surf1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(img_2, keypoints_surf2, img_keypoints_surf2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(img_3, kp_siftc1, img_keypoints_siftc1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(img_4, kp_siftc2, img_keypoints_siftc2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(img_3, kp_siftc1, img_keypoints_surfc1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(img_4, kp_siftc2, img_keypoints_surfc2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

	//-- Show detected (drawn) keypoints
	imshow("Keypoints SIFT suv", img_keypoints_sift1);
	imshow("Keypoints SIFT truck", img_keypoints_sift2);
	imshow("Keypoints SURF suv", img_keypoints_surf1);
	imshow("Keypoints SURF truck", img_keypoints_surf2);
	imshow("Keypoints SIFT Convertible_1", img_keypoints_siftc1);
	imshow("Keypoints SIFT Convertible_2", img_keypoints_siftc2);
	imshow("Keypoints SURF Convertible_1", img_keypoints_surfc1);
	imshow("Keypoints SURF Convertible_2", img_keypoints_surfc2);

	BFMatcher sift_con(NORM_L2);
	std::vector<DMatch>siftmatch_con;
	sift_con.match(des_c1, des_c2, siftmatch_con);
	Mat sift_match_con;
	drawMatches(img_3, kp_siftc1, img_4, kp_siftc2, siftmatch_con, sift_match_con);
	imshow("SIFT match Convertibles", sift_match_con);

	BFMatcher surf_con(NORM_L2);
	std::vector<DMatch>surfmatch_con;
	surf_con.match(des_c11, des_c22, surfmatch_con);
	Mat surf_match_con;
	drawMatches(img_3, kp_surfc1, img_4, kp_surfc2, surfmatch_con, surf_match_con);
	imshow("SURF match Convertibles", surf_match_con);

	BFMatcher sift_con1_SUV(NORM_L2);
	std::vector<DMatch>siftmatch_con1_suv;
	sift_con1_SUV.match(des_c1, des1, siftmatch_con1_suv);
	Mat sift_match_con1_suv;
	drawMatches(img_3, kp_siftc1, img_1, keypoints_sift1, siftmatch_con1_suv, sift_match_con1_suv);
	imshow("SIFT match Convertible1 and SUV", sift_match_con1_suv);

	BFMatcher surf_con1_SUV(NORM_L2);
	std::vector<DMatch>surfmatch_con1_suv;
	surf_con1_SUV.match(des_c11, des3, surfmatch_con1_suv);
	Mat surf_match_con1_suv;
	drawMatches(img_3, kp_surfc1, img_1, keypoints_surf1, surfmatch_con1_suv, surf_match_con1_suv);
	imshow("SURF match Convertible1 and SUV", surf_match_con1_suv);

	BFMatcher sift_con2_truck(NORM_L2);
	std::vector<DMatch>siftmatch_con2_truck;
	sift_con2_truck.match(des_c2, des2, siftmatch_con2_truck);
	Mat sift_match_con2_truck;
	drawMatches(img_4, kp_siftc2, img_2, keypoints_sift2, siftmatch_con2_truck, sift_match_con2_truck);
	imshow("SIFT match Convertible2 and Truck", sift_match_con2_truck);

	BFMatcher surf_con2_truck(NORM_L2);
	std::vector<DMatch>surfmatch_con2_truck;
	surf_con2_truck.match(des_c22, des4, surfmatch_con2_truck);
	Mat surf_match_con2_truck;
	drawMatches(img_4, kp_surfc2, img_2, keypoints_surf2, surfmatch_con2_truck, surf_match_con2_truck);
	imshow("SURF match Convertible2 and Truck", surf_match_con2_truck);

	// Bag of Words
	

	BOWKMeansTrainer BagOfWords(8);
	
	BagOfWords.add(des1);
	BagOfWords.add(des2);
	BagOfWords.add(des_c1);
	Mat dictionary = BagOfWords.cluster();
	//cout << dictionary << endl;
	double *bag_suv = d_array(8);
	double *bag_truck = d_array(8);
	double *bag_C1 = d_array(8);
	double *bag_C2 = d_array(8);
	bag_suv = histo(des1, dictionary);
	bag_truck = histo(des2, dictionary);
	bag_C1 = histo(des_c1, dictionary);
	bag_C2 = histo(des_c2, dictionary);
	cout << "bow suv" << endl;
	for (int i = 0; i < 8; i++) {
		cout << bag_suv[i] << endl;
	}
	cout << "bow truck" << endl;
	for (int i = 0; i < 8; i++) {
		cout << bag_truck[i] << endl;
	}
	cout << "bow C1" << endl;
	for (int i = 0; i < 8; i++) {
		cout << bag_C1[i] << endl;
	}
	cout << "bow C2" << endl;
	for (int i = 0; i < 8; i++) {
		cout << bag_C2[i] << endl;
	}

	double suv=0, truck=0, con1=0;
	for (int i = 0; i < 8; i++) {
		suv += abs(bag_suv[i] - bag_C2[i]);
		truck += abs(bag_truck[i] - bag_C2[i]);
		con1 += abs(bag_C1[i] - bag_C2[i]);
	}
	cout << suv/8 << endl;
	cout << truck/8 << endl;
	cout << con1/8 << endl;

	if (suv < truck && suv < con1) {
		cout << "Convertible 2 belongs to SUV" << endl;
	}
	else if (truck < suv && truck < con1) {
		cout << "Convertible 2 belongs to Truck" << endl;
	}
	else if (con1 <= suv && con1 < truck) {
		cout << "Convertible 2 belongs to Convertible 1" << endl;
	}

	waitKey(0);

	return 0;
}

/** @function readme */
void readme()
{
	std::cout << " Usage: ./SURF_detector <img1> <img2>" << std::endl;
}
double *histo(Mat des1, Mat dictionary) {
	double *a = d_array(des1.rows);
	double *b = d_array(des1.rows);
	double *c = d_array(des1.rows);
	double *d = d_array(des1.rows);
	double *e = d_array(des1.rows);
	double *f = d_array(des1.rows);
	double *g = d_array(des1.rows);
	double *h = d_array(des1.rows);
	for (int i = 0; i < des1.rows; i++) {
		for (int j = 0; j < des1.cols; j++) {
			a[i] += pow((dictionary.at<float>(0, j) - des1.at<float>(i, j)), 2);			b[i] += pow((dictionary.at<float>(1, j) - des1.at<float>(i, j)), 2);			c[i] += pow((dictionary.at<float>(2, j) - des1.at<float>(i, j)), 2);			d[i] += pow((dictionary.at<float>(3, j) - des1.at<float>(i, j)), 2);
			e[i] += pow((dictionary.at<float>(4, j) - des1.at<float>(i, j)), 2);			f[i] += pow((dictionary.at<float>(5, j) - des1.at<float>(i, j)), 2);			g[i] += pow((dictionary.at<float>(6, j) - des1.at<float>(i, j)), 2);			h[i] += pow((dictionary.at<float>(7, j) - des1.at<float>(i, j)), 2);
		}
		a[i] = sqrt(a[i]);		b[i] = sqrt(b[i]);		c[i] = sqrt(c[i]);		d[i] = sqrt(d[i]);
		e[i] = sqrt(e[i]);		f[i] = sqrt(f[i]);		g[i] = sqrt(g[i]);		h[i] = sqrt(h[i]);
	}

	double *bag = d_array(8);

	for (int i = 0; i < des1.rows; i++) {
		if (a[i] < b[i] && a[i] < c[i] && a[i] < d[i] && a[i] < e[i] && a[i] < f[i] && a[i] < g[i] && a[i] < h[i]) {
			bag[0] += 1;
		}
		else if (b[i] < a[i] && b[i] < c[i] && b[i] < d[i] && b[i] < e[i] && b[i] < f[i] && b[i] < g[i] && b[i] < h[i]) {
			bag[1] += 1;
		}
		else if (c[i] < b[i] && c[i] < a[i] && c[i] < d[i] && c[i] < e[i] && c[i] < f[i] && c[i] < g[i] && c[i] < h[i]) {
			bag[2] += 1;
		}
		else if (d[i] < b[i] && d[i] < c[i] && d[i] < a[i] && d[i] < e[i] && d[i] < f[i] && d[i] < g[i] && d[i] < h[i]) {
			bag[3] += 1;
		}
		else if (e[i] < b[i] && e[i] < c[i] && e[i] < d[i] && e[i] < a[i] && e[i] < f[i] && e[i] < g[i] && e[i] < h[i]) {
			bag[4] += 1;
		}
		else if (f[i] < b[i] && f[i] < c[i] && f[i] < d[i] && f[i] < e[i] && f[i] < a[i] && f[i] < g[i] && f[i] < h[i]) {
			bag[5] += 1;
		}
		else if (g[i] < b[i] && g[i] < c[i] && g[i] < d[i] && g[i] < e[i] && g[i] < f[i] && g[i] < a[i] && g[i] < h[i]) {
			bag[6] += 1;
		}
		else if (h[i] < b[i] && h[i] < c[i] && h[i] < d[i] && h[i] < e[i] && h[i] < f[i] && h[i] < g[i] && h[i] < a[i]) {
			bag[7] += 1;
		}
	}
	return bag;
}