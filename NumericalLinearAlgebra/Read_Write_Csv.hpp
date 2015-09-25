// This file was created to read data from
// csv file. Return a matrix.
//
// Zhenfeng Liang
//
// 08/17/2014 In Elmhurst, New York

// PLEASE REMEMBER TO ADD A DELIMITER AFTER THE LAST COLOUM OF THE DATA!!!!!!!
// 
// 请记得在csv数据最后一列后加上分隔符！！！！！！！！

// 8/30/2014 Changed all the m_data way access member to () reading and writing elements.

#ifndef READ_WRITE_CSV
#define READ_WRITE_CSV

#include <fstream>
#include <sstream>
#include <iomanip>
#include "Matrix.hpp"

using namespace std;

// row and col are the dimensions of the matrix you get
// start_row, start_col are the row and col from which you start to read data
// step is the step_length between two data read, e.g weekly, 5/7, monthly and etc

Matrix ReadMatrix(int row, int col, int start_row, int start_col, int step, string filename);

void WriteMatrix(Matrix m, string filename);



#endif