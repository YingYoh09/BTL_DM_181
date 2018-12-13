#include <iostream>
#include <string>
#include<stdio.h>
using namespace std;

void main()
{
	/*
	Vàng, du lịch, nhập, nữ			= 0
	Đỏ, thể thao, trong nước, nam	= 1
	tạo bảng theo thứ tự Màu xe - dòng xe - xuất xứ - người mua với nhãn là người mua
	*/
	int arr[10][4] = {
		{ 1, 1, 1, 1 },
		{ 1, 1, 1, 0 },
		{ 1, 1, 1, 1 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 0, 1 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 1 },
		{ 0, 0, 1, 0 },
		{ 1, 0, 0, 0 },
		{ 1, 1, 0, 1 } };

	int m = 10; //số đối tượng
	const int labelrange = 2;	//số lượng các giá trị khác nhau của nhãn
	const int datarange = 2;	//số lượng các giá trị khác nhau của đặc điểm
	const int n = 3; //số lượng đặc điểm
	string label[labelrange] = { "nu","nam" };
	const int m1 = n; // kích thước mẫu
	const float p1 = (1 / float(datarange)); // ước lượng tiền định
	//test data: Đỏ, du lịch, trong nước tương ứng 1 0 1
	int qu[3] = { 1, 0, 1 };
	

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
	float p[datarange][labelrange][n];
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
	float v[labelrange];
	for (int i = 0; i < labelrange; i++) {
		v[i] = lab[i] / float(lab[labelrange]);
	}
	//tính v
	for (int i = 0; i < labelrange; i++) {
		for (int j = 0; j < n; j++) {
			v[i] *= p[qu[j]][i][j];// p[qu[i]][i][j] tương ứng p[giá trị][nhãn][đặc điểm]
		}
	}
	//in ra kết quả
	cout << "Predicting class of qu: " << label[ans];
	for (int i = ans + 1; i < 2; i++) {
		if (v[i] == v[ans]) {
			cout << " or " << label[i];
		}
	}
	getchar();
}
