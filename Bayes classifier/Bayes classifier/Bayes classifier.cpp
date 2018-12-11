#include <iostream>
#include <string>
using namespace std;

void main()
{
	const int m1 = 3; // kích thước mẫu
	const float p1 = 0.5; // ước lượng tiền định
	int m = 10; //số giá trị
	int n = 4; //số lượng đặc điểm + số lượng nhãn
	string label[2] = { "Nu","Nam" };
	/* 
		Đỏ, thể thao, trong nước, nam	= 1
		Vàng, du lịch, nhập, nữ			= 0
		tạo bảng theo thứ tự Màu xe - dòng xe - xuất xứ - người mua với nhãn là người mua
	*/
	int arr[10][4] = {
		{1, 1, 1, 1},
		{1, 1, 1, 0},
		{1, 1, 1, 1},
		{0, 1, 1, 0},
		{0, 1, 0, 1},
		{0, 0, 0, 0},
		{0, 0, 0, 1},
		{0, 0, 1, 0},
		{1, 0, 0, 0},
		{1, 1, 0, 1} };

	//mảng đếm, với 3 là số lượng giá trị của nhãn + 1, 4 = n
	int F[2][3][4]; // mảng đếm số lượng có giá trị 1
	memset(F, 0, sizeof(F[0][0][0]) *2 * 3 * 4);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] == 1) {
				F[1][arr[i][n - 1]][j] += 1;
			}
			else
			{
				F[0][arr[i][n - 1]][j] += 1;
			}
		}
	}
	F[1][0][n - 1] = F[0][0][n - 1]; F[0][1][n - 1] = F[1][1][n - 1];
	for (int j = 0; j < n; j++) {
		F[1][2][j] = F[1][0][j] + F[1][1][j];
		F[0][2][j] = F[0][0][j] + F[0][1][j];
	}
	//test data: Đỏ, du lịch, trong nước tương ứng 1 0 1
	int qu[3] = { 1, 0, 1 };

	//tìm p(đặc điểm | nhãn) cần tính
	float p[2][2][4];
	memset(p, 0, sizeof(p[0][0][0]) * 2 * 2 * 4);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < n; j++) {
			p[0][i][j] = (F[0][i][j] + m1*p1) / (F[0][2][j] + m1);
			p[1][i][j] = (F[1][i][j] + m1*p1) / (F[1][2][j] + m1);
		}
	}
	
	//tính v, 2 là số giá trị của nhãn
	float v[2] = { 1, 1 };
	float sumv = 0;// v (nam) + v (nữ)
	//v[1] v nam
	v[1] *= p[0][1][3]; // p(Nam)
	v[0] *= p[0][0][3]; // p(Nữ)
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < n - 1; i++) {
			v[j] *= p[qu[i]][j][i]; // p[qu[i]][1][i] tương ứng p[đặc điểm][giới tính][cột]
		}
		sumv += v[j];
	}
	//p(d | nam/ nữ) và tìm p(d|) max
	float pd[2];
	int ans = 0;
	for (int i = 0; i < 2; i++) {
		pd[i] = v[i] / sumv;
		if (pd[i] > pd[ans]) ans = i;
	}
	//in ra kết quả
	cout << "Predicting class of qu: " << label[ans];
	getchar();
}

