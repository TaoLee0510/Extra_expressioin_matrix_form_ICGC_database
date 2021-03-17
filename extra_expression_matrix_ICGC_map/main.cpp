//
//  main.cpp
//  extra_expression_matrix_ICGC_map
//
//  Created by Tao Lee on 11/2/19.
//  Copyright © 2019 Tao Lee. All rights reserved.
//

//
//  main.cpp
//  extra_expression_matrix_ICGC
//
//  Created by Taolee on 11/2/19.
//  Copyright © 2019 Taolee. All rights reserved.
//


#include<iostream>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<ctime>
#include<fstream>
#include<string>
#include<sstream>
#include<cassert>
#include<cstring>
#include<string.h>
#include<map>
#include"mapiter.hpp"
using namespace std;
double str2num(const string str)
{
    stringstream ss(str);
    double num;
    ss >> num;
    return num;
}
struct Point
{
    string x;
    string y;
};
struct Point1
{
    string x;
};
vector<Point> read(string file)
{
    ifstream fin(file.c_str(), ios::in);
    char     line[500];
    string   x, y;
    vector<Point> num;
    while (fin.getline(line, sizeof(line)))
    {
        stringstream words(line);
        words >> x;
        words >> y;
        Point point;
        point.x = x.c_str();
        point.y = y.c_str();
        num.push_back(point);
    }
    return num;
}
vector<Point1> read1(string file)
{
    ifstream fin(file.c_str(), ios::in);
    char     line[500];
    string   x;
    vector<Point1> num1;
    while (fin.getline(line, sizeof(line)))
    {
        stringstream words(line);
        words >> x;
        Point1 point1;
        point1.x = x.c_str();
        num1.push_back(point1);
    }
    return num1;
}
int main()
{
    float start1 = clock();
    vector<Point> data  = read("/Volumes/Tao_EXT/Projects/active/201910_PAAD_EV/raw/ICGC/AU/ICGC_PAAD_AU_expression.txt");
    cout << "read time ： " << clock() - start1 << endl;
    vector<Point1> gene  = read1("/Volumes/Tao_EXT/Projects/active/201910_PAAD_EV/raw/ICGC/AU/gene.txt");
    vector<Point1> sample  = read1("/Volumes/Tao_EXT/Projects/active/201910_PAAD_EV/raw/ICGC/AU/sample.txt");
    
    int aa=int(data.size());
    map<string, string> map_mat;
//    for (int ii=0; ii<aa; ii++)
//    {
//        map_mat.insert(map<string, string>::value_type(data[ii].y,data[ii].x));
//    }
//
    for (int ii=0; ii<aa; ii++)
    {
        map_mat[data[ii].x]=data[ii].y;
    }
    
    
    int row=56207;
    int column=93;

    vector<vector<string> >mat(56207,vector<string>(93));
    cout << mat.size() <<endl;
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<column; j++)
        {
            if(i==0)
            {
                if (j==0)
                {
                    mat[i][j]="Tags";
                }
                else
                {
                    mat[i][j]=sample[j-1].x;
                }
            }
            else
            {
                if (j==0)
                {
                    mat[i][j]=gene[i-1].x;
                }
                else
                {
                    mat[i][j]="0";
                }
            }
        }
    }
    
    for (int q=1; q< row; q++ )
    {
        float start1 = clock();
        for (int p=1;p< column; p++)
      {
          string ID = mat[0][p]+mat[q][0];
          string value= mapiter(map_mat,ID);
          mat[q][p]=value;
      }
     cout << "row = " << q <<  "  time ： " << clock() - start1 << endl;
    }
    
    float start = clock();
    ofstream out("/Volumes/Tao_EXT/Projects/active/201910_PAAD_EV/raw/ICGC/AU/ICGC_PAAD_AU_expression_matrix.txt");
    for(int i = 0; i < row; i ++)
    {
        for(int j = 0; j < column; j ++)
        {
            out<<mat[i][j]<<"\t";
        }
        out << endl;
    }
    cout << "time cost for write file ： " << clock() - start << endl;
}

