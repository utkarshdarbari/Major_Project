#include"module6.h"

void module6::store_Outlier_Rows(int current_Col,
  int total_Rows,
  double lower_Bound1,
  double upper_Bound1,
  std::vector < std::string > * data,
  std::set < int > & outlier_Row_Idx) {
  //std::cout<<"entered\n";
  double val;
  for (int i = 0; i < total_Rows; i++) {
    val = stod(data[current_Col][i]);
    //std::cout<<val<<" ";
    if (val > upper_Bound1 || val < lower_Bound1) {
      outlier_Row_Idx.insert(i);
    }
  }

}

void module6::outlier_Detection(std::vector < std::string > * data,
  int current_Col,
  int total_Rows,
  double * upper_Bound,
  double * lower_Bound,
  std::set < int > & outlier_Row_Idx) {
  int median1, median2;
  std::vector < double > sort_Data;
  sort_Data.clear();
  for (int i = 0; i < total_Rows; i++) {
    sort_Data.push_back(stod(data[current_Col][i]));
  }
  sort(sort_Data.begin(), sort_Data.end());
  for (int i = 0; i < sort_Data.size(); i++)
    median1 = total_Rows / 4;
  median2 = (total_Rows * 3) / 4;
  double q1 = sort_Data[median1];
  double q3 = sort_Data[median2];
  double iqr = q3 - q1;
  lower_Bound[current_Col] = q1 - (1.5 * iqr);
  upper_Bound[current_Col] = q3 + (1.5 * iqr);
  //std::cout<<lower_Bound[current_Col]<<" "<<upper_Bound[current_Col]<<"\n";
  store_Outlier_Rows(current_Col, total_Rows, lower_Bound[current_Col], upper_Bound[current_Col], data, outlier_Row_Idx);
}

void module6::check_Outlier(std::vector < std::string > * data,
  bool * sparse_Idx,
  int remaining_Cols,
  int total_Rows,
  double * upper_Bound,
  double * lower_Bound,
  std::set < int > & outlier_Row_Idx) {
  for (int i = 0; i < remaining_Cols; i++) {
    if (sparse_Idx[i] != 1)
      outlier_Detection(data, i, total_Rows, upper_Bound, lower_Bound, outlier_Row_Idx);
  }
}