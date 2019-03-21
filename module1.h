#pragma once

#include<iostream>
#include<fstream>
#include<cstring>
#include<vector>
#include<sstream>
#include<algorithm>
#include<set>
#include <iterator> 
#include <map>

class module1{
public:
	std::string get_Csv_File_Name();
	int store_File_Get_Total_Rows(std::string);
	int get_Total_Cols(std::string);
	void display_File();
	int set_Target_Col();
	int get_Col_Remove_Index(std::set<int>&,int);
	void store_To_Vector(std::string , std::set < int > & ,  std::vector < std::string > * ,  int ,  int ,  int ,  int * );
	void store_Vector_To_File(std::vector < std::string > * ,  int ,  int ,  int ,  int * );
};