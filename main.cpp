/*
	Murat Kacmaz
	150140052
*/


#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <cmath>

using namespace std;

int totalDistanceCalculation = 0;
class Ball {
public:
	int x;
	int y;
	int z;
	Ball(int xFile, int yFile, int zFile) { x = xFile; y = yFile; z = zFile; }
	Ball(const Ball &ball_copied) { x = ball_copied.x; y = ball_copied.y; z = ball_copied.z; }
};

 

void heapify(vector<Ball>& data, int n, int i)
{
	int biggest = i;  

	int left = 2 * i + 1; 

	int right = 2 * i + 2; 

					 
	if (left < n && data[left].x > data[biggest].x)
	{
		biggest = left;
	}	

	 
	if (right < n && data[right].x > data[biggest].x)
	{ 
		biggest = right;
	}
	 
	if (biggest != i)
	{
		swap(data[i], data[biggest]);
		heapify(data, n, biggest);
	}
}

void heapsort(vector<Ball>& data, int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heapify(data, n, i);
	}
		

	for (int i = n - 1; i >= 0; i--)
	{
		swap(data[0], data[i]); 
		heapify(data, i, 0);
	}
}


void heapifyY(vector<Ball>& data, int n, int i)
{
	int biggest = i;

	int left = 2 * i + 1;

	int right = 2 * i + 2;


	if (left < n && data[left].y > data[biggest].y)
	{
		biggest = left;
	}


	if (right < n && data[right].y > data[biggest].y)
	{
		biggest = right;
	}

	if (biggest != i)
	{
		swap(data[i], data[biggest]);
		heapifyY(data, n, biggest);
	}
}

void heapsortY(vector<Ball>& data, int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heapifyY(data, n, i);
	}


	for (int i = n - 1; i >= 0; i--)
	{
		swap(data[0], data[i]);
		heapifyY(data, i, 0);
	}
}

float euclid(Ball b1, Ball b2)
{	
	totalDistanceCalculation++;
	return sqrt(pow(b1.x - b2.x, 2)+ pow(b1.y - b2.y, 2)+ pow(b1.z - b2.z, 2));
}

float distanceSmallPairs(vector<Ball>& data, int left, int right)
{
	float minDist = 999999;
	for (int i = left; i < right; i++)
	{	
		for (int j = i + 1; j < right; j++)
		{	
			float euclideanDistance = euclid(data[i], data[j]);
				if (euclideanDistance < minDist)
				{
					minDist = euclideanDistance;
				}
		}
	}
	return minDist;
}


float stripCheckClosest(vector<Ball>& data, float distanceLR)
{
	int n = data.size();
	heapsortY(data, n);
	float minDist = distanceLR;
	float tempMinDist;
	
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if ((data[j].y - data[i].y) < minDist )  // && abs(data[j].z - data[i].z) < minDist
			{
				tempMinDist = distanceSmallPairs(data, i, j);
				if (tempMinDist < minDist)
					minDist = tempMinDist;
			}
		}
	}
	return minDist;
}

float closestPair(vector<Ball>& data, int left, int right)
{
	if (right - left <= 2) {
		return distanceSmallPairs(data, left, right);
	}
	float minLeft, minRight, minLR;
	int middle = (left + (right-1)) / 2;
	minLeft = closestPair(data, left, middle);
	minRight = closestPair(data, middle, right);
	if (minLeft > minRight)
		minLR = minRight;
	else minLR = minLeft;
	
	vector<Ball> stripCheck;
	int j = 0;
	for (int i = left; i < right; i++)
	{
		if (abs(data[i].x - data[middle].x) < minLR)
		{
			Ball newBall = data[i];
			stripCheck.push_back(newBall);
		}
	}

	float closestStripDistance = stripCheckClosest(stripCheck, minLR);

	if (minLR < closestStripDistance)
		return minLR;
	else
		return  closestStripDistance;
	
}


int main(int argc, char* argv[])
{
	vector<Ball> ball_array;

	float closestPairOfArray;
 
 
	string xFile_str, yFile_str, zFile_str;
	int xFile, yFile, zFile;

	ifstream fileRead;
	fileRead.open(argv[1]);

	string lineRead;

	getline(fileRead, lineRead);
	while (getline(fileRead, lineRead))
	{
		istringstream iss(lineRead);
		getline(iss, xFile_str, ' ');
		getline(iss, yFile_str, ' ');
		getline(iss, zFile_str, '\n');

		xFile = atoi(xFile_str.c_str());
		yFile = atoi(yFile_str.c_str());
		zFile = atoi(zFile_str.c_str());

		Ball newBall(xFile, yFile, zFile);

		ball_array.push_back(newBall);
	}

	int n = ball_array.size();
	heapsort(ball_array,n);
//	clock_t begin1 = clock();
	cout << "The distance is " << closestPair(ball_array,0,n-1) << endl ;
	cout << "Number of total distance calculation is " << totalDistanceCalculation << endl;
//	clock_t end1 = clock();
//	double elapsed_secs1 = double(end1 - begin1) / CLOCKS_PER_SEC;
//	cout << endl << "Running Time: " << elapsed_secs1 << " seconds " << endl;
 
	getchar();
	return 0;
}