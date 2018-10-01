#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <string>
#include <string>
#include <stdio.h>
#include <algorithm>


using namespace cv;
using namespace std;
template <typename T>
string NumberToString ( T Number )
{
	stringstream ss;
	ss << Number;
	return ss.str();
}

Point2f point1 = Point2f(0, 0), point2 = Point2f(0, 0);

//scan the four sides to see where the corner intersects the side - a corner will pass through only two sides
void findBoundingPoints(Mat img, Mat c) {
	point1 = Point2f(0, 0), point2 = Point2f(0, 0);
	Point p1 = Point2f(0, 0), p2 = Point2f(0, 0);

	bool p1Found = false;
	for (int i = 0; i < img.cols-1; i++) {
		int a = img.at<uchar>(0, i);
		int b = img.at<uchar>(0, i + 1);
		if (a == 0 && b == 255 && !p1Found) { p1 = Point(i, 0); p1Found = true; }
		if (a == 255 && b == 0 && !p1Found) { p1 = Point(i, 0); p1Found = true; }
		if (a == 0 && b == 255 && p1Found) { p2 = Point(i, 0); p1Found = true; }
		if (a == 255 && b == 0 && p1Found) { p2= Point(i, 0); p1Found = true; }
	}

	//p1Found = false;
	for (int i = 0; i < img.cols-1; i++) {
		int a = img.at<uchar>(img.rows - 1, i);
		int b = img.at<uchar>(img.rows - 1, i + 1);
		if (a == 0 && b == 255 && !p1Found) { p1 = Point(i, img.rows - 1); p1Found = true; }
		if (a == 255 && b == 0 && !p1Found) { p1 = Point(i, img.rows - 1); p1Found = true; }
		if (a == 0 && b == 255 && p1Found) { p2 = Point(i, img.rows - 1); p1Found = true; }
		if (a == 255 && b == 0 && p1Found) { p2 = Point(i, img.rows - 1); p1Found = true; }
	}

	//p1Found = false;
	for (int i = 0; i < img.rows-1; i++) {
		int a = img.at<uchar>(i, 0);
		int b = img.at<uchar>(i + 1, 0);
		if (a == 0 && b == 255 && !p1Found) { p1 = Point(0, i); p1Found = true; }
		if (a == 255 && b == 0 && !p1Found) { p1 = Point(0, i); p1Found = true; }
		if (a == 0 && b == 255 && p1Found) { p2 = Point(0, i); p1Found = true; }
		if (a == 255 && b == 0 && p1Found) { p2 = Point(0, i); p1Found = true; }
	}

	//p1Found = false;
	for (int i = 0; i < img.rows-1; i++) {
		int a = img.at<uchar>(i, img.cols - 1);
		int b = img.at<uchar>(i + 1, img.cols - 1);
		if (a == 0 && b == 255 && !p1Found) { p1 = Point(img.cols - 1, i); p1Found = true; }
		if (a == 255 && b == 0 && !p1Found) { p1 = Point(img.cols - 1, i); p1Found = true; }
		if (a == 0 && b == 255 && p1Found) { p2 = Point(img.cols - 1, i); p1Found = true; }
		if (a == 255 && b == 0 && p1Found) { p2 = Point(img.cols - 1, i); p1Found = true; }
	}

	circle(c, p1, 1, Scalar(0, 255, 0));
	circle(c, p2, 1, Scalar(0, 255, 0));

	point1 = p1;
	point2 = p2;
}

//BINARY_IMAGE contour_points - now redundant. The function above replaced this
Point findPointsX(Mat img, Mat c) {
	vector<Point> p;
	Point p1 = Point(0, 0);
	for (int i = 0; i < img.cols; i++) {
		int a = img.at<uchar>(0, i);
		int b = img.at<uchar>(0, i + 1);
		int c = img.at<uchar>(img.rows - 1, i);
		int d = img.at<uchar>(img.rows - 1, i + 1);

		if (a == 0 && b == 255) { p1 = Point(i,0); break;	}
		if (a == 255 && b == 0) { p1 = Point(i,0); break; }
		if (c == 0 && d == 255) { p1 = Point(i, img.rows - 1); break; }
		if (c == 255 && d == 0) { p1 = Point(i, img.rows - 1); break; }
	}
	circle(c, p1, 1, Scalar(0, 255, 0));
	return p1;
}
Point findPointsY(Mat img, Mat c) {
	Point p2 = Point(0, 0);

	for (int i = 0; i < img.rows; i++) {
		int a = img.at<uchar>(i, 0);
		int b = img.at<uchar>(i + 1, 0);
		int c = img.at<uchar>(i, img.cols - 1);
		int d = img.at<uchar>(i + 1, img.cols - 1);

		if (a == 0 && b == 255) { p2 = Point(0, i); break; }
		if (a == 255 && b == 0) { p2 = Point(0, i); break; }
		if (c == 0 && d == 255) { p2 = Point(img.cols - 1, i); break; }
		if (c == 255 && d == 0) { p2 = Point(img.cols - 1, i); break; }
	}
	circle(c, p2, 1, Scalar(0, 255, 0));
	return p2;
}

//find the line between the extreme points - then find the furthest contour point to the line
Point findExtremePoint(Mat img, vector<Point2f> c, Point2f p1, Point2f p2, Mat imgO) {

	float m = 1;
	if(p1.x != p2.x) m = (p1.y - p2.y) / (p1.x - p2.x);
	double cc = p2.y - m*p2.x;
	double cc1 = p1.y - m*p1.x;
	double mDist = 0;
	Point pp;

	for (int i = 0; i < c.size(); i++) {
		double X = c[i].x, Y = c[i].y;
		if (X != 0 && X != img.cols - 1 && Y != 0 && Y != img.rows - 1) {
			double temp1 = -1 * m*X + Y - cc;
			double temp2 = sqrt(1 + pow(-1 * m, 2));
			double temp3 = abs(temp1 / temp2);
			if (temp3 > mDist) {
				mDist = temp3;
				pp = c[i];
			}
		}
	}
	circle(imgO, pp, 1, Scalar(0, 0, 255));
	return pp;
}


int findLargestContour(vector<vector<Point> > c, Mat im){
	double largest_area = 0;
	int largest_idx = 0;
	for (int i = 0; i < c.size(); i++) {
		double a = contourArea(c[i]);
		if (a > largest_area && a < im.cols*im.rows) {
			largest_area = a;
			largest_idx = i;
		}
	}
	return largest_idx;
}

// bool dirExists(const std::string& dirName_in){
// 	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
// 	if (ftyp == INVALID_FILE_ATTRIBUTES)		return false;
// 	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)		return true;
// 	return false;
// }



int main(int argc, char* argv[]) {

	//stuff for original image matching
	Mat original_img;
	Point finalp;
	String path = argv[1];
	ofstream pointsFile;
	cout << "[+]Reading Path:"<<path<<endl;
	double xa[10];
	double ya[10];
	int crops = 0;
	int headerread = 0;
	original_img = imread(path + "outputs/original.jpg", 1);
	ifstream in((path + "outputs/areas.txt").c_str());
	if(!in) {
	  cout << "Cannot open input file.\n";
	  return 1;
	}
	char str[255];

	while(in) {
	  in.getline(str, 255);  // delim defaults to '\n'
	  // if(in) cout << str << endl;
		if(atoi(str) == 0 && headerread == 0){
			cout << "Panty found" << endl;
			crops = 6;
		}else if(atoi(str) == 1 && headerread == 0){
			crops = 8;
		}

		if(!(headerread == 0)){
			if(headerread % 2 == 1){
				xa[headerread/2] = atof(str);
				cout << "x["<<headerread/2<<"]:"<<xa[headerread/2] << endl;
			}else{
				ya[headerread/2-1] = atof(str);
				cout << "y["<<headerread/2-1<<"]:"<<ya[headerread/2-1] << endl;
			}

		}

		headerread++;

	}
	in.close();
	pointsFile.open ("core/outputs/points.txt");



	for (int a = 0; a < crops; a++) {
		Mat img, gray, thresh;

   string idx= NumberToString ( a );

		 //std::string idx = std::to_string(a);
	 //string idx = (a);

		img = imread(path + "outputs/cropped_" + idx + ".jpg", 1);
		//img = imread(argv[1], 1);

		//img.copyTo(gray);
		cvtColor(img, gray, COLOR_BGR2GRAY);
		Mat th;
		threshold(gray, th, 120, 255, CV_THRESH_BINARY_INV);

		vector<vector<Point> > cont;
		findContours(th, cont, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
		Mat dd = Mat::zeros(gray.size(), gray.type());

		drawContours(dd, cont, findLargestContour(cont, gray), Scalar(255, 255, 255), -1);

		int d0 = findLargestContour(cont, dd);


		Mat D0 = Mat::zeros(gray.size(), CV_8UC3);
		drawContours(D0, cont, d0, Scalar(255, 255, 255));

		vector<Point2f> cc0;
		for (int i = 0; i < cont[d0].size(); i++) cc0.push_back(cont[d0][i]);


		findBoundingPoints(dd, D0);
		Point ppp0 = findExtremePoint(dd, cc0, point1, point2, D0);
		line(D0, point1, point2, Scalar(0, 255, 0));


		circle(img, ppp0, 5, Scalar(0, 255, 0), 1);	circle(img, ppp0, 2, Scalar(0, 0, 255), -1);
		finalp.x = xa[a] + ppp0.x;
		finalp.y = ya[a] + ppp0.y;
		pointsFile <<finalp.x<<"\n"<<finalp.y<<"\n";

		circle(original_img, finalp, 5, Scalar(0, 255, 0), 1);	circle(original_img, finalp, 2, Scalar(0, 0, 255), -1);
		cout << "Point at:"<<finalp.x<<endl;

		imwrite(path + "outputs/im" + idx + ".jpg", img);
		imwrite(path + "outputs/pt" + idx + ".jpg", D0);
	}


  pointsFile.close();

	imwrite(path + "outputs/original_convert.jpg", original_img);


	return 0;

}
