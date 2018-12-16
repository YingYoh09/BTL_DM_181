#include <iostream>
#include <string>
#include<stdio.h>
using namespace std;

void main()
{
	/*
	mưa, nhiệt độ thấp, độ ẩm thấp, trời không có gió, mua cà phê			= 0
	âm u, nhiệt độ bình thường, độ ẩm bình thường, trời có gió, mua trà		= 1
	nắng, nhiệt độ cao, độ ẩm cao,nước trái cây					= 2
	tạo bảng "thời tiết - nhiệt độ - độ ẩm - gió - thời tiết hôm trước" với nhãn là sản phẩm đc mua
	*/
	int arr[20][6] = {
		{2, 1, 0, 0, 0, 2},
		{0, 0, 2, 0, 1, 1},
		{0, 1, 0, 1, 1, 0},
		{1, 1, 1, 1, 2, 0},
		{0, 0, 1, 0, 1, 1},
		{0, 1, 0, 0, 1, 1},
		{1, 2, 1, 1, 1, 0},
		{1, 0, 1, 1, 1, 2},
		{1, 1, 0, 1, 1, 0},
		{0, 2, 1, 0, 1, 2},
		{1, 2, 0, 0, 0, 1},
		{1, 2, 1, 0, 0, 1},
		{0, 0, 0, 1, 1, 0},
		{1, 0, 0, 0, 2, 2},
		{0, 2, 2, 0, 1, 2},
		{2, 1, 2, 0, 0, 2},
		{2, 0, 2, 0, 1, 2},
		{0, 1, 0, 0, 2, 1},
		{1, 1, 1, 0, 1, 2},
		{2, 1, 2, 0, 2, 0} };

	int m = 20; //số đối tượng
	const int labelrange = 3;	//số lượng các giá trị khác nhau của nhãn
	const int datarange = 3;	//số lượng các giá trị khác nhau của đặc điểm (max)
	const int n = 5; //số lượng đặc điểm
	string label[labelrange] = { "Ca phe","tra","nuoc trai cay"};
	const int m1 = n; // kích thước mẫu
	const double p1 = (1 / double(datarange)); // ước lượng tiền định
	//test data: nắng, nhiệt độ bình thường, độ ẩm cao, không gió, âm u tương ứng 2 1 2 0 1
	int qu[5] = { 2, 1, 2, 0, 1 };
	

	// mảng đếm số lượng các đặc điểm,  n ở đây là số đặc điểm
	int F[datarange][labelrange + 1][n]; 
	memset(F, 0, sizeof(F[0][0][0]) * datarange * (labelrange + 1) * n);
	//đếm số lượng các đặc điểm
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			F[arr[i][j]][arr[i][n]][j]++;//đếm từng đặc điểm
			F[arr[i][j]][labelrange][j]++;//sum
		}
	}
	//đếm số lượng các nhãn có giá trị ....
	int lab[labelrange + 1];
	memset(lab, 0, sizeof(lab[0]) * (labelrange + 1));
	for (int i = 0; i < m; i++) {
		lab[arr[i][n]]++;
		lab[labelrange]++;
	}
	//tìm p(đặc điểm | nhãn)
	double p[datarange][labelrange][n];
	memset(p, 0, sizeof(p[0][0][0]) * datarange * labelrange * n);
	for (int i = 0; i < datarange; i++) {
		for (int j = 0; j < labelrange; j++) {
			for (int k = 0; k < n; k++) {
				p[i][j][k] = (F[i][j][k] + m1*p1) / (F[i][labelrange][k] + m1);
			}
		}
	}
	//khai báo v, tính P(label)
	int ans = 0;
	double v[labelrange];
	for (int i = 0; i < labelrange; i++) {
		v[i] = lab[i] / double(lab[labelrange]);
	}
	//tính v
	for (int i = 0; i < labelrange; i++) {
		for (int j = 0; j < n; j++) {
			v[i] *= p[qu[j]][i][j];// p[qu[i]][i][j] tương ứng p[giá trị][nhãn][đặc điểm]
		}
		if (v[i] > v[ans]) ans = i;
	}
	//in ra kết quả
	cout << "Predicting class of qu: " << label[ans];
	for (int i = ans + 1; i < labelrange; i++) {
		if (v[i] == v[ans]) {
			cout << " or " << label[i];
		}
	}
	getchar();
}
