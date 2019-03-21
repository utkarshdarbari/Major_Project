#pragma once

#include"module1.h"

class module6{
public:
  void store_Outlier_Rows(int ,  int ,  double ,  double ,  std::vector < std::string > * , std::set < int > & );
  void outlier_Detection(std::vector < std::string > * ,  int ,int ,  double * ,  double * ,  std::set < int > & );
  void check_Outlier(std::vector < std::string > * ,  bool * ,  int ,  int ,  double * ,  double * ,  std::set < int > & );
};