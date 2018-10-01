#include "opencv2/core/core.hpp"
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/ocl.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/img_hash.hpp"
#include "opencv2/core/core_c.h"
//#include "C:\opencv\sources\samples\gpu\tick_meter.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <opencv2/calib3d.hpp>
#include <math.h>       /* atan */
#include <algorithm>
#define pi 3.14159265
#include <fstream>
using namespace cv;
using namespace std;
double area;
Mat image, img_gray, img_cont;
int cont_index = 0;
int xsort[8] = {};
int ysort[8] = {};

int upperleftmost;
int upperleft;
int bottomleftmost;
int bottomrightmost;
int upperrightmost;
int upperright;
int leftmiddle;
int rightmiddle;
int result;
double len1=0, len2=0, len3=0, len4=0, len5=0, len6=0, len7=0, len8=0;
int id1 = 0;
int id2 = 0;
double midlen = 0;
double midlen2 = 0;
int mid1x = 0;
int mid1y = 0;
int mid2x = 0;
int mid2y = 0;
int xx1;
int yy1;
int xx2;
int yy2;
int set = 0;
int count_pix = 0;
string length;
double pixlen = 0.1675;//0.13487;//0.1319;//0.13;//0.221;

Mat temp1, temp2;
struct measrue {
	int x1;
	int y1;
	int x2;
	int y2;
}measruement1, measruement2, measruement3, measruement4, measruement5, measruement6;

vector<vector<Point> > contours;
vector<Vec4i> hierarchy;
Mat draw1 = Mat::zeros(1944, 2592, CV_8UC3);//Mat::zeros(2050, 3000, CV_8UC3);// Mat::zeros(1700, 2200, CV_8UC3);
Mat draw2 = Mat::zeros(1944, 2592, CV_8UC3);//Mat::zeros(4000, 6000, CV_8UC3);//Mat::zeros(1944, 2592, CV_8UC3);
Mat draw3 = Mat::zeros(1944, 2592, CV_8UC3);//Mat::zeros(2050, 3000, CV_8UC1);

int calculate(int x1,int y1, int x2 ,int y2);
void findids();
// void findmidval();
double calclen();
ofstream measureFile;
int main(int argc, char* argv[])
{
	Mat frame;
	Mat frame2;
	Mat undistortedFrame;
	String path = argv[1];
	int headerread = 0;
	double xa[10];
	double ya[10];


	ifstream in((path + "core/outputs/points.txt").c_str());
	measureFile.open("core/outputs/measurement.txt");
	if(!in) {
	  cout << "Cannot open input file.\n";
	  return 1;
	}
	char str[255];

	printf("Starting kitty");

	while(in) {
	  in.getline(str, 255);  // delim defaults to '\n'
	  // if(in) cout << str << endl;



			if(headerread % 2 == 1){
				ya[headerread/2] = atof(str);
				cout << "y["<<headerread/2-1<<"]:"<<ya[headerread/2-1] << endl;
			}else{
				xa[headerread/2] = atof(str);
				cout << "x["<<headerread/2<<"]:"<<xa[headerread/2] << endl;

			}



		headerread++;

	}
	in.close();


  frame = imread("testcalibnew1.jpg", CV_LOAD_IMAGE_COLOR);
  imwrite("core/outputs/sss.jpg", frame2);

	Mat map1,map2;
	Mat source;
	source = frame; //undistortedFrame;
	imwrite("core/outputs/original2.jpg", source);
	Rect rect(1249, 1145, 3000, 2050);     //100,130,2200,1700

	image = source;// source(rect);
	//
	Mat re1;
	resize(image, re1, cv::Size(640, 480));
	//imshow("original_re", re1);

	imwrite("core/outputs/resize.jpg", image);

	cvtColor(image, img_gray, CV_BGR2GRAY);


	draw2 = image;



	Mat element = getStructuringElement(cv::MORPH_CROSS,
	cv::Size(2 * 3 + 1, 2 * 3 + 1),
	cv::Point(3, 3));
	//imshow("smooth", img_gray);
	threshold(img_gray, img_gray, 150, 255, THRESH_BINARY_INV);   //130   //180
	Canny(img_gray, img_gray, 100, 250, 3);  //100   //80
	imwrite("core/outputs/original_kitty.jpg", img_gray);
	Mat re2;
	resize(img_gray, re2, cv::Size(640, 480));
	//imshow("core/outputs/original1_re", re2);
	img_cont=  Mat::zeros(img_gray.size(), CV_8UC3);
	findContours(img_gray, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, cv::Point(0, 0));
	int erosion_size = 3;
	double largest_area = 0;
	for (int i = 0; i < contours.size(); i++){
		area = contourArea(contours[i], false);
		if (largest_area <area){
			largest_area = area;
			cont_index = i;
		}
	}
	vector<vector<Point> >hull(contours.size());
	cout << "szie" << contours.size() << endl;
	convexHull(Mat(contours[cont_index]), hull[cont_index], false);
	RNG rng;
	Mat drawing = Mat::zeros(img_gray.size(), CV_8UC1);
	Scalar color = Scalar(255,255,255);
  drawContours(drawing, hull, cont_index, color, 1, 8, vector<Vec4i>(), 0, Point());
	Mat convex;
	Mat re3;
	resize(drawing, re3, cv::Size(640, 480));
	//imshow("hull", re3);
	imwrite("core/hull.jpg",drawing);
	cout << hull[0][1] << endl;
	int p = 0;
	cout << area << "index" << cont_index << endl;
	vector<Point2f>corners1[4];
	cout << hull[0].size() << endl;
	for (int i = 0; i < hull.size() - 1; i++){
		cout << hull[i].size() << endl;
	}
	for (int i = 0; i < hull[0].size()-1; i++){
		cout << hull[0][i];
		if ((hull[0][i].y <400)){
			if (abs(hull[0][i].x - hull[0][i + 1].x)>10 && p<4) {
				circle(drawing,Point2f(hull[0][i].x, hull[0][i].y), 8, Scalar(255, 255, 255), 4, 3);
					p = p + 1;
			}
		}
	}
	corners1[0].push_back(Point2f(xa[2], ya[2]));
	corners1[1].push_back(Point2f(xa[3], ya[3]));
	corners1[2].push_back(Point2f(xa[4], ya[4]));
	corners1[3].push_back(Point2f(xa[5], ya[5]));
	drawContours(img_cont, contours, cont_index, Scalar(255, 255, 255), 1, 8, hierarchy, 0, Point());
	Mat re4;
	resize(img_cont, re4, cv::Size(640, 480));
	//imshow("cont", re4);
	Mat dst, dst_norm, dst_norm_scaled,conx;
	dst = Mat::zeros(img_cont.size(), CV_32FC1);
	Mat cont3 = Mat::zeros(img_cont.size(), CV_8UC3);
	cvtColor(img_cont, cont3, CV_BGR2GRAY);
	// Detecting corners
	cornerHarris(cont3, dst, 15,15,0.1, BORDER_DEFAULT);
	Mat re5;
	resize(drawing, re5, cv::Size(640, 480));
	//imshow("convex", re5);
	// Normalizing
	normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(dst_norm, dst_norm_scaled);
	threshold(dst_norm_scaled, dst_norm_scaled, 130, 255, THRESH_BINARY);
	vector<vector<Point> > contours1;
	vector<Vec4i> hierarchy1;
	Mat re6;
	resize(dst_norm_scaled, re6, cv::Size(640, 480));
	//imshow("corners_window", re6);
  findContours(dst_norm_scaled,contours1, hierarchy1, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, cv::Point());
	Mat cont4 = Mat::zeros(img_cont.size(), CV_8UC3);
	for (int g = 0; g < contours1.size(); g++){
		drawContours(cont4, contours1, g, Scalar(255, 255, 255), 1, 8, hierarchy1, 0, Point());
	}
	Mat re7;
	resize(cont4, re7, cv::Size(640, 480));
	//imshow("cont4", re7);
	Mat img_cont2 = Mat::zeros(img_cont.size(), CV_8UC3);
	cout << "contoursize" << contours1.size() << endl;
	vector<Moments> mu(contours1.size());
	for (int i = 0; i < contours1.size(); i++){
		mu[i] = moments(contours1[i], false);
	}
	///  Get the mass centers:
	vector<Point2f> mc(contours1.size());
	vector<Point2f> mcy(contours1.size());
	for (int i = 0; i < contours1.size(); i++){
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
		mcy[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
		cout << "ffff"<< mc[i] << endl;
		circle(draw2, mc[i], 2, Scalar(255, 255, 255), 1, 4, 0);
	}
	int arraysize = contours1.size()-1;
	int id;
	int LminX = image.cols,LmaxY=0,maxX = 0, maxY = 0, minxidX,maxxidX,maxyidY;
	cout  << image.cols<<  endl;
	for (int j = 0; j <contours1.size(); j++){
		circle(img_cont2, mc[j], 2, Scalar(255, 255, 255), 1, 4, 0);
		string order = to_string(j);
	}
	int a; double x, y;
	for (int j = 0; j <contours1.size(); j++){
		for (int i = j + 1; i < contours1.size(); i++){
			if (mc[i].x <= mc[j].x) {
				a = j;
				x = mc[j].x;
				y = mc[j].y;
				mc[j].x = mc[i].x;
				mc[j].y = mc[i].y;
				mc[i].x = x;
				mc[i].y = y;
			}
		}
		cout << endl;
	}
	int b, mx, my;
	for (int j = 0; j <contours1.size(); j++){
		for (int i = j + 1; i < contours1.size(); i++){
			if (mcy[i].y >= mcy[j].y) {
				mx = mcy[j].x;
				my = mcy[j].y;
				mcy[j].x = mcy[i].x;
				mcy[j].y = mcy[i].y;
				mcy[i].x = mx;
				mcy[i].y = my;
			}
		}
		cout << endl;
	}
	vector<Point2f>corners2[4];
	int h=0;
	for (int i = 0; i < mc.size() ; i++){
		if ((mc[i].y >600)&& h<4){
			h = h + 1;
			}
		}
	vector<Point2f>cornerupdate[4];
	corners2[0].push_back(Point(xa[0], ya[0]));
	corners2[1].push_back(Point(xa[1], ya[1]));
	corners2[2].push_back(Point(xa[6], ya[6]));
	corners2[3].push_back(Point(xa[7], ya[7]));
	putText(img_cont2, to_string(1), Point(corners2[0][0].x, corners2[0][0].y), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 4);
	putText(img_cont2, to_string(2), Point(corners2[1][0].x, corners2[1][0].y), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 4);
	putText(img_cont2, to_string(7), Point(corners2[2][0].x, corners2[2][0].y), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 4);
	putText(img_cont2, to_string(8), Point(corners2[3][0].x, corners2[3][0].y), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 4);
	putText(img_cont2, to_string(3), Point(corners1[0][0].x, corners1[0][0].y), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 4);
	putText(img_cont2, to_string(4), Point(corners1[1][0].x, corners1[1][0].y), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 4);
	putText(img_cont2, to_string(5), Point(corners1[2][0].x, corners1[2][0].y), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 4);
	putText(img_cont2, to_string(6), Point(corners1[3][0].x, corners1[3][0].y), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 4);
	for (int i = 0; i < contours1.size(); i++){
		cout << mc[i] << endl;
	}
	cout << endl;
	cout << "ffffffff" << endl;
	for (int i = 0; i < contours1.size(); i++){
		cout << mcy[i] << endl;
	}
	for (int i = 0; i < contours1.size(); i++){
		int z = i + 1;
		string zz = to_string(z);
	}
	measruement1.x1 = corners2[0][0].x;
	measruement1.y1 = corners2[0][0].y;
	measruement1.x2 = corners2[3][0].x;
	measruement1.y2 = corners2[3][0].y;
	findids();
	cout << contours[cont_index][id1] << " vvvvvvvv   " << contours[cont_index][id2] << endl;
	calclen();
	calculate(measruement1.x1, measruement1.y1, measruement1.x2, measruement1.y2);
	cout << "point to point L" << " =" << result*pixlen << endl;
	cout << "result L" << " =" << len1/10 << endl;
	measureFile <<"{\"L\":"<<((result*pixlen) / 10)<<",";
	putText(draw1, to_string((result*pixlen) / 10), Point(((corners2[3][0].x- corners2[0][0].x)/2)+200, corners2[3][0].y-100), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
	midlen = len1 / 2;
	cout << "midlen" << midlen << endl;
	if (set == 0){
	 calclen();
	 cout << "dddddd" << endl;
	}
	set = 1;
	measruement1.x1 = corners2[1][0].x;
	measruement1.y1 = corners2[1][0].y;
	measruement1.x2 = corners2[0][0].x;
	measruement1.y2 = corners2[0][0].y;
	findids();
	calclen();
	calculate(measruement1.x1, measruement1.y1, measruement1.x2, measruement1.y2);
	cout << "point to point" << " =" << result*pixlen << endl;
	cout << "result M" << " =" << len1/10 << endl;
	measureFile <<"\"M\":"<<((result*pixlen) / 10)<<",";
	putText(draw1, to_string((result*pixlen) / 10), Point(corners2[0][0].x,((corners2[0][0].y)-150)), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);

	measruement1.x1 = corners1[0][0].x; //mc[2].x;
		measruement1.y1 = corners1[0][0].y; //mc[2].y;
	measruement1.x2 = corners2[1][0].x;
	measruement1.y2 = corners2[1][0].y;
	circle(draw2, Point(measruement1.x2, measruement1.y2), 8.0, Scalar(140,30, 255), 4, 2);
	circle(draw2, Point(measruement1.x1, measruement1.y1), 8.0, Scalar(180, 90, 255), 4, 2);
	findids();
	calclen();
	cout << "result N" << " =" << len1/10 << endl;
	measureFile <<"\"N\":"<<length<<",";
	putText(draw1, length, Point(corners2[1][0].x+400, ((corners2[1][0].y) - 150)), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
	measruement1.x1 = corners1[1][0].x;//mc[3].x;
	measruement1.y1 = corners1[1][0].y; //mc[3].y;
	measruement1.x2 = corners1[2][0].x;//mc[4].x;
	measruement1.y2 = corners1[2][0].y;//mc[4].y;

	circle(draw2, Point(measruement1.x2, measruement1.y2), 8.0, Scalar(140, 30, 255), 4, 2);
	circle(draw2, Point(measruement1.x1, measruement1.y1), 8.0, Scalar(180, 90, 255), 4, 2);
	circle(draw3, Point(measruement1.x2, measruement1.y2), 8.0, Scalar(140, 30, 255), 4, 2);
	circle(draw3, Point(measruement1.x1, measruement1.y1), 8.0, Scalar(180, 90, 255), 4, 2);
	findids();
	cout << "fff" << endl;
	calclen();
	cout << "fff" << endl;
	// findmidval();
	cout << "result O" << " =" << len1/10 << endl;
	measureFile <<"\"O\":"<<length<<",";
	putText(draw1, length, Point(corners1[1][0].x +120, ((corners1[1][0].y)+180)), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
	measruement1.x1 = corners1[3][0].x;// mc[5].x;
	measruement1.y1 = corners1[3][0].y;//mc[5].y;
	measruement1.x2 = corners2[2][0].x;
	measruement1.y2 = corners2[2][0].y;
	circle(draw2, Point(measruement1.x2, measruement1.y2), 8.0, Scalar(140, 30, 255), 4, 2);
	circle(draw2, Point(measruement1.x1, measruement1.y1), 8.0, Scalar(180, 90, 255), 4, 2);
	findids();
	calclen();

	cout << "result P" << " =" << len1/10 << endl;
	measureFile <<"\"P\":"<<length<<",";
	putText(draw1, length, Point(corners1[3][0].x, ((corners2[2][0].y) - 150)), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);


	measruement1.x1 = corners2[2][0].x;
	measruement1.y1 = corners2[2][0].y;
	measruement1.x2 = corners2[3][0].x;
	measruement1.y2 = corners2[3][0].y;
	findids();
	calclen();
	calculate(measruement1.x1, measruement1.y1, measruement1.x2, measruement1.y2);
	cout << "point to point" << " =" << result*pixlen << endl;
	cout << "result M" << " =" << len1/10 << endl;
	cout << "points M" << " =" << corners2[2][0].x << "  " << (corners2[2][0].y) << "                   " << corners2[3][0] << "  " << (corners2[3][0].y) << endl;
	measureFile <<"\"U\":"<<to_string((result*pixlen)/10)<<",";
	putText(draw1, to_string((result*pixlen)/10), Point(corners2[2][0].x-50, ((corners2[3][0].y) - 150)), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);


	measruement1.x1 = corners2[1][0].x;
	measruement1.y1 = corners2[1][0].y;
	measruement1.x2 = corners2[2][0].x;
	measruement1.y2 = corners2[2][0].y;


	line(draw1, corners2[1][0], corners2[2][0], Scalar(110, 25, 100), 2, 8);
	calculate(measruement1.x1, measruement1.y1, measruement1.x2, measruement1.y2);
	cout << "result K" << " =" << result*(pixlen) / 10 << endl;
	measureFile <<"\"K\":"<<to_string((result*pixlen)/10)<<"}";
	putText(draw1,to_string(result*(pixlen)/10), Point(corners2[1][0].x +1000, ((corners2[2][0].y) - 50)), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
	resize(draw2, temp1, Size(640, 480));
	resize(draw1, temp2, Size(640, 480));
	
	imwrite("core/outputs/draw1.jpg", draw1);
	imwrite("core/outputs/draw2.jpg",draw2);
	imwrite("core/outputs/draw3.jpg", draw3);



	Mat temp3, temp4;
	resize(img_cont2, temp3, Size(640, 360));
	resize(img_cont, temp4, Size(640, 360));
	imwrite("core/outputs/result.jpg", img_cont2);
	measureFile.close();
	

	waitKey(0);
	return 0;
}



int calculate(int x1, int y1 , int x2 , int y2)
{
	int val1;
	int val2;
	int power1;
	int power2;

	if (y2 > y1)
	{
		 val1 = x2 - x1;
		 power1 = pow(val1,2.0);
		 val2 = y2 -y1;
		 power2 = pow(val2, 2.0);

		result = sqrt((power1 + power2));

	}

	else

		val1 = x2 - x1;
	power1 = pow(val1, 2.0);
	val2 = y1 - y2;
	power2 = pow(val2, 2.0);

	result = sqrt((power1 + power2));




	return result*1.414;

}



void findids()
{

	id1 = 0; id2 = 0;
	int d = 0;
	int e = 0;
	for (int i = 1; i < contours[cont_index].size(); i++)
	{

	
		if (contours[cont_index][i].x <= measruement1.x1+4 && contours[cont_index][i].x >= measruement1.x1-4 &&d==0)
		{

			if ((measruement1.y1 - 3) <= contours[cont_index][i].y  && contours[cont_index][i].y <= (measruement1.y1 + 3))
			{

				cout << contours[cont_index][i].x << "ccc1" << contours[cont_index][i].y << endl;
				d = 1;
				id1 = i;

			}
		}


		if (contours[cont_index][i].x <= measruement1.x2 + 4 && contours[cont_index][i].x >= measruement1.x2 - 4&&e==0)
		{
		
			if ((measruement1.y2 - 3) <= contours[cont_index][i].y  && contours[cont_index][i].y <= (measruement1.y2 + 3))
			{

				cout << contours[cont_index][i].x << "dd" << contours[cont_index][i].y << endl;
			
				e = 1;
				id2 = i;
			}



		}


	}

	


}



double calclen()

{
	count_pix = 0;

	len1 = 0;
	if (id1 > id2)
	{
		for (int i = id2; id1>= i; i++)
		{

		
			line(draw1, contours[cont_index][i], contours[cont_index][i + 1], Scalar(110, 220, 0), 2, 8);
			xx1 = contours[cont_index][i].x;
			yy1 = contours[cont_index][i].y;
			xx2 = contours[cont_index][i + 1].x;
			yy2 = contours[cont_index][i + 1].y;
			


			if ((xx1 - xx2) == 0 || (yy1 - yy2) == 0)
			{
				
				len1 = len1 + (0.948*calculate(xx1, yy1, xx2, yy2));

			}


			else if ((xx1 - xx2) != 0 && (yy1 - yy2) != 0)
			{

				
				len1 = len1 + (1.340*calculate(xx1, yy1, xx2, yy2));


			}
		

			draw3.at<uchar>(Point(xx1, yy1)) = 255;
			draw3.at<uchar>(Point(xx2, yy2)) = 255;

		}

	}
	if (id1 < id2)
	{

		for (int i = id1; id2 >= i; i++)
		{
		line(draw1, contours[cont_index][i], contours[cont_index][i + 1], Scalar(110, 220, 0), 2, 8);


			xx1 = contours[cont_index][i].x;
			yy1 = contours[cont_index][i].y;
			xx2 = contours[cont_index][i + 1].x;
			yy2 = contours[cont_index][i + 1].y;
			


			if ((xx1 - xx2) == 0 || (yy1 - yy2) == 0)
			{
				
				len1 = len1 + (0.948*calculate(xx1, yy1, xx2, yy2));
			}


			else if ((xx1 - xx2) != 0 || (yy1 - yy2) != 0)
			{

				
				len1 = len1 + (1.340*calculate(xx1, yy1, xx2, yy2));


			}



		
			if (set == 0 && midlen >= len1*pixlen) {
				mid1x = xx1;
				mid1y = xx2;
			}
			draw3.at<uchar>(Point(xx1, yy1)) = 255;
			draw3.at<uchar>(Point(xx2, yy2)) = 255;
		}
	}
	cout << "length bmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm"  << " " << len1 << endl;
	if (len1 < 3000)
	{
		//count_pix = len1;
		len1 = len1*pixlen;
	}

	if (len1 > 3000){
		cout << "id1 " << id1 << "id2 " << id2<<"size "<< contours[cont_index].size()<<endl;

		double len2 = 0;
		double len3 = 0;
		if (id1 < id2)
		{



			circle(draw1, Point(contours[cont_index][id2].x, contours[cont_index][id2].y), 8.0, Scalar(130, 120, 225), 4, 2);
			circle(draw1, Point(contours[cont_index][contours[cont_index].size()-1].x, contours[cont_index][contours[cont_index].size()-1].y), 8.0, Scalar(230, 120, 250), 4, 2);
			imwrite("O.jpg", draw1);
			
			for (int i = id2; contours[cont_index].size() - 1> i; i++)
			{

				cout << "location      " << i << "   " << contours[cont_index][i] << endl;

				line(draw1, contours[cont_index][i], contours[cont_index][i + 1], Scalar(110, 100, 0), 2, 8);
				line(draw3, contours[cont_index][i], contours[cont_index][i + 1], Scalar(110, 100, 0), 2, 8);
				
				xx1 = contours[cont_index][i].x;
				yy1 = contours[cont_index][i].y;
				xx2 = contours[cont_index][i + 1].x;
				yy2 = contours[cont_index][i + 1].y;
				
				if ((xx1 - xx2) == 0 || (yy1 - yy2) == 0)
				{
					
					len2 = len2 + (0.948*calculate(xx1, yy1, xx2, yy2));
				}


				else if ((xx1 - xx2) != 0 && (yy1 - yy2) != 0)
				{

					
					len2 = len2 + (1.340*calculate(xx1, yy1, xx2, yy2));


				}
				
				draw3.at<uchar>(Point(xx1, yy1)) = 255;
				draw3.at<uchar>(Point(xx2, yy2)) = 255;
			}


			for (int i = id1; 2< i; i--)
			{

				cout << "location2      " << i << "   " << contours[cont_index][i] << endl;

				line(draw1, contours[cont_index][i], contours[cont_index][i + 1], Scalar(110, 100, 0), 2, 8);

				
				xx1 = contours[cont_index][i].x;
				yy1 = contours[cont_index][i].y;
				xx2 = contours[cont_index][i -1].x;
				yy2 = contours[cont_index][i - 1].y;
				
				if ((xx1 - xx2) == 0 || (yy1 - yy2) == 0)
				{
					
					len3 = len3 + (0.948*calculate(xx1, yy1, xx2, yy2));
				}


				else if ((xx1 - xx2) != 0 && (yy1 - yy2) != 0)
				{

					
					len3 = len3 + (1.414*calculate(xx1, yy1, xx2, yy2));


				}
				
			}

			len1 = (len2 + len3)*pixlen;

		}






		cout << "len2 " << len2 << "len3 " << len3*pixlen << "len1 "<< len1 <<endl;



	}



	    length = to_string(len1 /10);


	return len1;



}



