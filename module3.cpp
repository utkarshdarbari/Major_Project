#include"module3.h"

void module3::find_Mode(std::vector < std::string > * data,
  std::string * mode, int total_Rows,
  int remaining_Cols) {
  int val;
  std::string line, most_used_line;
  std::multimap < std::string, int > mode_Finder;
  for (int i = 0; i < remaining_Cols; i++) {
    mode_Finder.clear();
    int max = 0;
    most_used_line = data[i][0];
    for (int j = 0; j < total_Rows; j++) {
      line = data[i][j];
      if (line == "")
      ;
      else if (mode_Finder.find(line) == mode_Finder.end()) {
        mode_Finder.insert(std::make_pair(line, 1));
        //std::cout << "  Insert\n";
      } else {
        mode_Finder.find(line) -> second++;
        val = mode_Finder.find(line) -> second;
        //std::cout<<"  Add count\n";
        if (val > max) {
          max = val;
          most_used_line = line;
        }
      }
    }
    mode[i] = most_used_line;
  }
}

void module3::find_Mean(std::vector < std::string > * data,
  int * col_Data_Type,
  double * mean,
  int total_Rows,
  int remaining_Cols,
  std::string * max,
  std::string * min) {
  for (int i = 0; i < remaining_Cols; i++) {
    if (col_Data_Type[i] != 1) {
      mean[i] = 0;
      max[i] = "0";
      min[i] = "0";
    } else {
      double val1, max1, min1;
      max1 = stod(data[i][0]);
      min1 = max1;
      double sum = 0;
      int counter = 0;
      for (int j = 0; j < total_Rows; j++) {
        if (data[i][j] != "") {
          val1 = stod(data[i][j]);
          sum = sum + val1;
          counter++;
          if (val1 > max1)
            max1 = val1;
          if (val1 < min1)
            min1 = val1;
        }

      }
      mean[i] = sum / counter;
      max[i] = std::to_string(max1);
      min[i] = std::to_string(min1);
    }
  }

}


void module3::fill_Missing_Values(double * mean, std::string * mode, std::vector < std::string > * data, int remaining_Cols, int total_Rows, int * col_Data_Type) {
  for (int i = 0; i < remaining_Cols; i++) {
    for (int j = 0; j < total_Rows; j++) {
      if (data[i][j] == "" && col_Data_Type[i] == 1)
        data[i][j] = std::to_string(mean[i]); //fill mean
      else {
        if (data[i][j] == "")
          data[i][j] = mode[i];
      }
    }
  }
}