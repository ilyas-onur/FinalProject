/* Hand.cpp
 *
 *  Created on: Apr 18, 2014
 *  Author: İlyas Onur ÖZGEN
 */

#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

Mat dst, draw;
uchar isVisited[480][640] = { { 0 } };

int countt;
struct node {
	int x, y;
	node *next;
} *head, *last;

bool value(int, int);

void findNeighbour(int, int);

void addL(int, int);

void delL();

void display();

int hasNeighbour(int, int);

int main() {

	Mat image, image_gray, detected_edges;
	countt = 0;
	image = imread("/home/cse/Desktop/4.jpg");

	cvtColor(image, image_gray, CV_BGR2GRAY);
	blur(image_gray, detected_edges, Size(3, 3));
	Canny(detected_edges, detected_edges, 100, 100 * 3, 3);
	dst = Scalar::all(0);

	image_gray.copyTo(dst, detected_edges);

	draw = image_gray.clone();
	draw = Scalar::all(0);

	namedWindow("Display Image", 0);
	//cvResizeWindow("Display Image", 480, 640);
	threshold(dst, dst, 0, 255, cv::THRESH_BINARY);
	//bitwise_not ( dst, dst );

	int i, j;
	for (i = 0; i < dst.rows; i++) {
		for (j = 0; j < dst.cols; j++) {
			if (255 == (dst.at<uchar>(i, j))) {
				goto brek;
			}
		}
	}

	brek:

	addL(i, j);
	findNeighbour(i, j);

	imwrite("/home/cse/Desktop/dst.jpg", dst);
	imwrite("/home/cse/Desktop/draw.jpg", draw);

	imshow("Display Image", draw);
	imshow("Display Image1", dst);

	waitKey(0);

	return 0;
}

bool value(int x, int y) {

	if ((640 >= x) && (x >= 0) && (480 >= y) && (y >= 0))
		return (255 == (dst.at<uchar>(x, y))) && 0 == isVisited[x][y];
	else
		return 0;

}

void addL(int x, int y) {
	node *temp;
	temp = (struct node *) malloc(sizeof(struct node));
	temp->x = x;
	temp->y = y;
	if (NULL == head) {
		head = temp;
		head->next = NULL;
	} else {
		temp->next = head;
		head = temp;
	}
}

void delL() {

	struct node *temp = head;

	if (NULL == temp)
		printf("List is empty!");
	else {
		head = head->next;
		fprintf(stderr, "deleted:%d-%d\n", temp->x, temp->y);
		free(temp);
	}

}

void display() {

	node *r = head;
	if (NULL == r) {
		return;
	}
	while (r != NULL) {
		draw.at<uchar>(r->x, r->y) = 255;
		printf("%d-%d\n", r->x, r->y);
		r = r->next;
	}
}

void findNeighbour(int x, int y) {

	isVisited[x][y] = 1;

	if (value(x, y - 1))
		addL(x, y - 1);
	else if (value(x, y + 1))
		addL(x, y + 1);
	else if (value(x + 1, y))
		addL(x + 1, y);
	else if (value(x - 1, y))
		addL(x - 1, y);
	else if (value(x, y - 2))
		addL(x, y - 2);
	else if (value(x + 1, y - 1))
		addL(x + 1, y - 1);
	else if (value(x + 2, y))
		addL(x + 2, y);
	else if (value(x + 1, y + 1))
		addL(x + 1, y + 1);
	else if (value(x, y + 2))
		addL(x, y + 2);
	else if (value(x - 1, y + 1))
		addL(x - 1, y + 1);
	else if (value(x - 2, y))
		addL(x - 2, y);
	else if (value(x - 1, y - 1))
		addL(x - 1, y - 1);
	else {
		int c = 0;
		while (!hasNeighbour(head->x, head->y)) {
			delL();
			c++;
			if (c > 5) {
				display();
				return;
			}
		}
	}
	findNeighbour(head->x, head->y);

}

int hasNeighbour(int x, int y) {

	if (value(x, y - 1))
		return 1;
	else if (value(x + 1, y))
		return 1;
	else if (value(x, y + 1))
		return 1;
	else if (value(x - 1, y))
		return 1;
	else if (value(x, y - 2))
		return 1;
	else if (value(x + 1, y - 1))
		return 1;
	else if (value(x + 2, y))
		return 1;
	else if (value(x + 1, y + 1))
		return 1;
	else if (value(x, y + 2))
		return 1;
	else if (value(x - 1, y + 1))
		return 1;
	else if (value(x - 2, y))
		return 1;
	else if (value(x - 1, y - 1))
		return 1;
	else
		return 0;

}

/*{{0.55,0.217,0.008,0.0, 0.0, 0.0, 0.008, 0.217},
 {0.217, 0.55, 0.217, 0.008, 0.0 ,0.0, 0.0, 0.008},
 {0.008, 0.217, 0.55, 0.217, 0.008, 0.0, 0.0, 0.0},
 {0.0, 0.008, 0.217, 0.55, 0.217, 0.008, 0.0, 0.0},
 {0.0 ,0.0 ,0.008, 0.217, 0.55, 0.217, 0.008, 0.0},
 {0.0 ,0.0 ,0.0, 0.008, 0.217, 0.55, 0.217, 0.008},
 {0.008, 0.0, 0.0 ,0.0, 0.008 ,0.217 ,0.55, 0.217},
 {0.217 ,0.008 ,0.0, 0.0, 0.0, 0.008, 0.217, 0.55},}*/
