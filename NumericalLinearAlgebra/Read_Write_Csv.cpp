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

#include <fstream>
#include <sstream>
#include <iomanip>
#include "Matrix.hpp"
#include "Read_Write_Csv.hpp"

using namespace std;

// row and col are the dimensions of the matrix you get
// start_row, start_col are the row and col from which you start to read data
// step is the step_length between two data read, e.g weekly, 5/7, monthly and etc

Matrix ReadMatrix(int row, int col, int start_row, int start_col, int step, string filename)
{ // file name is the file you want to read from
 // 该函数的使用必须得在读取矩阵的最后一行加上分隔符！！！

	Matrix m(row,col);

	double** data = new double*[row];
	
	for(int i = 0; i < row; ++i)
		data[i] = new double[col];

	std::ifstream file(filename.c_str());

	for(int j = 1; j < start_row; j++)
	{// This is to jump over the first several rows whicn you don't want to read

		std::string line;
		std::getline(file, line);
	}

    for(int j = 0; j < row; ++j)
    {
        string line;
        getline(file, line);
        if ( !file.good() )
            break;

        stringstream iss(line);

		for (int k = 1; k < start_col; ++k)
		{ // This is to jump over the first several coloums whicn you don't want to read
            
			string val;
            getline(iss, val, ',');
		}

        for (int k = 0; k < col; ++k)
        {
            string val;
            getline(iss, val, ',');
            if ( !iss.good() )
                break;

            stringstream convertor(val);
            convertor >> data[j][k];
			m(j,k) = data[j][k];
        }

		for(int t = 1; t < step; t++)
		{ // This is to jump over those rows you don't want to read between different rows. 
		  // Most likely, take weekly, monthly or yearly data.

			string line;
	     	getline(file, line);
		}
    }

	for(int i = 0; i < row; i++)
	{
		delete [] data[i];
		data[i] = NULL;
	}
	delete [] data;
	data = NULL;

	return m;
}


void WriteMatrix(Matrix m, string filename)
{	
	ofstream myfile; 
	myfile.open (filename.c_str(), ios::app); 
	myfile << " \n";
	for(int j = 0; j < m.Size1(); ++j) 
	{ 
		for(int k = 0; k < m.Size2(); ++k)
		{
			myfile << setprecision(18) << m(j,k) << ",";
		}
		myfile << endl;
	} 

	myfile.close(); 
}



/*
Matrix ReadMatrix(int row, int col, int useless_row, int useless_col, int flag_col, string filename)
{ // file name is the file you want to read from
  // 这个函数目前还有bug

	Matrix m(row,col);

	double** data = new double*[row];
	
	for(int i = 0; i < row; ++i)
		data[i] = new double[col];

	std::ifstream file(filename.c_str());

	for(int j = 1; j <= useless_row; j++)
	{// This is to jump over the first several rows whicn you don't want to read

		std::string line;
		std::getline(file, line);
	}

    for(int j = 0; j < row; ++j)
    {
		int required_data_row = 0;  // This is to record the data row.

        string line;
        getline(file, line);
        if ( !file.good() )
            break;

        stringstream iss(line);

		int flag;

		for (int k = 1; k <= flag_col; ++k)
		{
			string val;
            getline(iss, val, ',');
			stringstream convertor(val);
			convertor >> flag;
		}

		if(flag == 1)
		{
			for(int k = 1; k <= 3 - flag_col; ++k)
			{ // This is to jump the residual flag variables coloums

				string val;
				getline(iss, val, ',');
			}

			for (int k = 1; k <= useless_col; ++k)
			{ // This is to jump over the first several useless coloums after the flag variables whicn you don't want to read

				string val;
				getline(iss, val, ',');
			}

			for (int k = 0; k < col; ++k)
			{
				string val;
				getline(iss, val, ',');
				if ( !iss.good() )
					break;

				stringstream convertor(val);
				convertor >> data[required_data_row][k];
				m(required_data_row,k) = data[required_data_row][k];
			}

			required_data_row++;

		} //后面的code要整理上来
    }

	for(int i = 0; i < row; i++)
	{
		delete [] data[i];
		data[i] = NULL;
	}

	delete [] data;
	data = NULL;

	return m;
}
*/
