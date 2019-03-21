#include"module8.h"
int module8::store_To_Final_File(std::vector < std::string > * data,
  int remaining_Cols, int total_Rows,
  std::set < int > & outlier_Row_Index,
  std::vector < int > * sparse_Matrix_Guide,
  int no_Of_Sparse,
  bool * sparse_Idx,
  int total_New_Columns) {
  int remaining_Rows = 0;
  std::ofstream writer;
  writer.open("Module1.csv");
  std::set < int > ::iterator itr = outlier_Row_Index.begin();
  for (int i = 0, idx = 0; i < total_Rows; i++) {
    bool fill_started = 0;
    if ( * itr != i) {
      for (int j = 0; j < remaining_Cols - 1; j++) {
        if (sparse_Idx[j] != 1) {
          if (fill_started)
            writer << "," << data[j][i];
          else {
            writer << data[j][i];
            fill_started = 1;
          }
        }
      }
      for (int j = 0, idx = 0; j < total_New_Columns; j++) {
        if (sparse_Matrix_Guide[idx][i] == j) {
          writer << ",1";
          idx++;
          if (idx > no_Of_Sparse)
            idx = no_Of_Sparse - 1;
        } else
          writer << ",0";
      }
      if (sparse_Idx[remaining_Cols - 1] != 1) {
        writer << "," << data[remaining_Cols - 1][i] << "\n";
      } else {
        writer << "\n";
      }
      remaining_Rows++;
    } else
      itr++;
  }
  writer.close();
  system("./showCSVfileModule1.sh");
  return remaining_Rows;
}

void module8::create_Test_Train_Split(int remaining_Rows) {
  int count = 0;
  std::ifstream reader;
  std::ofstream writer1;
  std::ofstream writer;
  reader.open("Module1.csv");
  writer1.open("Train.csv");
  writer.open("Test.csv");
  std::string line = "";
  int limit = (remaining_Rows * 75) / 100;
  for (int i = 0; i < limit; i++) {
    getline(reader, line, '\n');
    writer1 << line;
    writer1 << "\n";
  }
  for (int i = limit; i < remaining_Rows; i++) {
    getline(reader, line, '\n');
    writer << line;
    writer << "\n";
  }
  reader.close();
  writer1.close();
  writer.close();
  system("./showCSVfileTrain.sh");
  system("./showCSVfileTest.sh");
}