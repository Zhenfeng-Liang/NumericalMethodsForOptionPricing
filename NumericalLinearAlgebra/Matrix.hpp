// This is designed for the NLA class.
// This file includes matrix basic function
//
// Zhenfeng Liang
//
// 11:29 PM, 8/26/2014, Elmhurst, NY
// 8/30/2014 Change the + - and * scalar functions to be friend global functions so as to 
// make the basic operation available, such as 1+m and m+1.
// Let m_data be a private member rather than public member, Add () operator const and non-const versions to read and write the matrix
// Note: 用STL vector代替m[n][1]可使程序简化，但运行速度未知，需要进一步对比！

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <sstream>

using namespace std;

class Matrix
{
private:
	int m_row_num;
	int m_col_num;
	double** m_data;
public:
	Matrix();
	Matrix(int row_num, int col_num);
	Matrix(int row_num, int col_num, double** new_array);
	Matrix(const Matrix& source);
	~Matrix();

	int Size1() const;
	int Size2() const;
	
	// Find the largest abs value's index from element a to b in k coloum
	int max_abs_entry_row_index(int a, int b, int k);

	// Matrix Operation
	// Swap row i and j from element k1 to k2.
	void row_pivot(int i, int j, int k1, int k2);

	Matrix Trans() const;
	Matrix inverse() const;

	void identity_matrix();

	void turn_upside_down();

	double norm();

	Matrix& operator = (const Matrix& source);
	
	// Member operator overloading
	Matrix operator + (const Matrix& m) const;
	Matrix operator - (const Matrix& m) const;
	Matrix operator * (const Matrix& m) const;

	// Scalar function
	Matrix operator / (double factor) const;

	// Read and Write the elements in the matrix, const and non-const versions
	double& operator () (int j, int k);
	const double& operator () (int j, int k) const;



	Matrix& operator <<= (string data);

	// friend functions
	friend Matrix operator + (const Matrix& m, double factor);
	friend Matrix operator + (double factor, const Matrix& m);
	friend Matrix operator - (double factor, const Matrix& m);
	friend Matrix operator - (const Matrix& m, double factor);
	friend Matrix operator * (const Matrix& m, double factor);
	friend Matrix operator * (double factor, const Matrix& m);
	friend std::ostream& operator << (std::ostream& os, const Matrix& m);
	friend std::istream& operator >>(std::istream &input, Matrix &mat);
};

#endif