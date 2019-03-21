#include"module5.h"

void module5::min_Max_Normalization(std::string * min,
  std::string * max,
  std::vector < std::string > * data,
  int * col_Data_Type,
  int remaining_Cols,
  int total_Rows) {
  double max1, min1, val, ans;
  for (int i = 0; i < remaining_Cols; i++) {
    max1 = stod(max[i]);
    min1 = stod(min[i]);
    if (col_Data_Type[i] == 1) {
      for (int j = 0; j < total_Rows; j++) {
        val = stod(data[i][j]);
        ans = (val - min1) / (max1 - min1);
        data[i][j] = std::to_string(ans);
      }
    }
  }
}
