// ReadMat.cpp : 定义控制台应用程序的入口点。
//  test
//  test1
////  test20181001
//  test3
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include <opencv2\opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/ml.hpp>
#include<time.h>

using namespace std;
using namespace cv;
using namespace cv::ml;



void salt(Mat &image, int num) {
	if (!image.data) return;//防止传入空图
	int i, j;
	srand(time(NULL));
	for (int x = 0; x < num; ++x) {
		i = rand() % image.rows;
		j = rand() % image.cols;
		image.at<Vec3b>(i, j)[0] = 255;
		image.at<Vec3b>(i, j)[1] = 255;
		image.at<Vec3b>(i, j)[2] = 255;
	}
}

//ptr和[]操作符
void ReadMat0(Mat &image)
{
	int Rows=image.rows;
	int ColsCha=image.cols*image.channels();
	for(int i=1;i<Rows;i++)
	{
		uchar *data=image.ptr<uchar>(i);
		for(int j=1;j<ColsCha;j++)
		{
			data[j]=data[j]-125;

		}
	}
}

//ptr和指针操作
void ReadMat1(Mat &image)
{
	int Rows=image.rows;
	int ColsCha=image.cols*image.channels();
	for(int i=1;i<Rows;i++)
	{
		uchar *data=image.ptr<uchar>(i);
		for(int j=1;j<ColsCha;j++)
		{
			*data++=*data-125;

		}
	}
}

//
void ReadMat2(Mat &image)
{
	int Rows=image.rows;
	int Cols=image.cols;
	for(int i=1;i<Rows;i++)
	{
		for(int j=1;j<Cols;j++)
		{
			image.at<Vec3b>(i,j)[0]=image.at<Vec3b>(i,j)[0]-125;
			image.at<Vec3b>(i,j)[1]=image.at<Vec3b>(i,j)[1]-125;
			image.at<Vec3b>(i,j)[2]=image.at<Vec3b>(i,j)[2]-125;
			//image.at<Vec3b>(i,j)=Vec3b(image.at<Vec3b>(i,j)[0]-125,image.at<Vec3b>(i,j)[1]-125,image.at<Vec3b>(i,j)[2]-125);

		}
	}
}

void salt1(Mat &ima,int n)
{
	int Rows=ima.rows;
	int Cols=ima.cols;
	int i;
	int j;
	for (int num=0;num<n;num++)
	{
		i=rand()%Rows;
		j=rand()%Cols;
		if(ima.type() ==CV_8UC1)
			ima.at<uchar>(i,j)=255;
		else if(ima.type() ==CV_8UC3)
		{
			ima.at<Vec3b>(i,j)[0]=255;
			ima.at<Vec3b>(i,j)[1]=255;
			ima.at<Vec3b>(i,j)[2]=255;
		}

	
	}

}
void Colorreduce(Mat image, int div=64)
{
	int iRows=image.rows;
	int iColscha=image.cols*image.channels();
	for (int iI=0;iI<iRows;iI++)
	{
		uchar *ucData =image.ptr<uchar>(iI); 
		for(int iJ=0;iJ<iColscha;iJ++)
		{
			*ucData++ = *ucData/div+div/2;
		
		}
	}

	 namedWindow("image.jpg");
	 imshow("image.jpg", image);
}

void Imagecut(Mat &img)
{
	Rect rectangle1(73,0,230,219);  //("people.jpg");
	Mat cutresult,bgModel,fgModel;

	 grabCut(img,
			 cutresult,
			 rectangle1,
			 bgModel,fgModel,
			 3,
			 GC_INIT_WITH_RECT);
	 
	 compare(cutresult,GC_PR_FGD, cutresult,CMP_EQ); 
	 namedWindow("cutresult.jpg");
	 imshow("cutresult.jpg", cutresult);
	 
	 //分割通道
	 Mat cutresult1;
	 vector<Mat> planes;
	 split(img,planes);
	 bitwise_and(planes[0],cutresult,planes[0]);
	 bitwise_and(planes[1],cutresult,planes[1]);
	 bitwise_and(planes[2],cutresult,planes[2]);
	 merge(planes,cutresult1);
	 namedWindow("cutresult1.jpg");
	 imshow("cutresult1.jpg", cutresult1);
}
void Filter(Mat &image)
	
{
	Mat image1,image2,image3,sobelX,sobelY,sobel,sobelimage,sobelThresholded;
	double sobMin,sobMax;
	salt1(image,3000);
	blur(image,image1,Size(5,5));
	imshow("image.jpg", image);
	imshow("imageblur.jpg", image1);
	GaussianBlur(image,image2,Size(5,5),1.5);
	imshow("imagegaussblur.jpg", image2);
	medianBlur(image,image3,5);
	imshow("imagemedianblur.jpg", image3);
	Sobel(image3,sobelX,CV_16S,1,0);
	Sobel(image3,sobelY,CV_16S,0,1);
	sobel=abs(sobelX)+abs(sobelY);
	minMaxLoc(sobel,&sobMin,&sobMax);
	sobel.convertTo(sobelimage,CV_8U,-255./sobMax,255);
	imshow("sobel.jpg", sobel);
	imshow("sobelimage.jpg", sobelimage);
	threshold(sobelimage,sobelThresholded,200,255,THRESH_BINARY);
	imshow("sobelThresholded.jpg", sobelThresholded);





}
int _tmain(int argc, _TCHAR* argv[])
{
	int rowNumber;
	int colNumber;
	int num_c;
	Mat img = imread("people.jpg");
	//Mat_<Vec3b> img2(img);
	//img2(50,100)=(0,255,0);
	Mat img1;
    cout<<img.size();
    if (img.empty())
    {
        cout << "error";    
        return -1;
    }
	//cllorreduce
	/*
	 img1=img.clone();
	 Colorreduce(img1,2);
	 */
	// rectangle(img,cvPoint(83,0),cvPoint(293,219),Scalar(0,0,255),1,1,0);
	//imagecut 
	/*
	namedWindow("img.jpg");
	imshow("img.jpg", img);
	Imagecut(img);
	*/
	//Filter
	Filter(img);
	waitKey(0);
	
	return 0;
}
    
