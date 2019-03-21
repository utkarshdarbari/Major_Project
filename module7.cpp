#include"module7.h"

int module7::find_number_of_Sparse(bool * sparse_Idx, int remaining_Cols) {
  int count = 0;
  for (int i = 0; i < remaining_Cols; i++) {
    if (sparse_Idx[i] == 1)
      count++;
  }
  return count;
}

int module7::convert_Sparse_Cols(std::vector < std::string > * data,
  int remaining_Cols, int total_Rows,
  bool * sparse_Idx,
  std::vector < int > * sparse_Matrix_Guide) 
{
  int count = 0;
  int sparse_Editing_Idx = 0;
  std::multimap < std::string, int > mapper;
  for (int j = 0; j < remaining_Cols; j++) {
    int idx = 0;
    if (sparse_Idx[j] == 1) {
      mapper.clear();
      //sparse_Matrix_Guide.clear();
      std::string line;
      for (int i = 0; i < total_Rows; i++) {
        line = data[j][i];
        if (mapper.find(line) == mapper.end()) {
          int val = idx + sparse_Editing_Idx;
          mapper.insert(std::make_pair(line, val));
          idx++;
        }
        sparse_Matrix_Guide[count].push_back(mapper.find(line) -> second);
      }
      sparse_Editing_Idx = sparse_Editing_Idx + idx;
      count++;
    }
  }
  return sparse_Editing_Idx;
}