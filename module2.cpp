#include"module2.h"


int module2::get_Total_Cols(std::string file_Name) {
  std::ifstream reader;
  int count = 0;
  reader.open(file_Name);
  std::string line = "";
  getline(reader, line, '\n');
  for (int i = 0; i < line.length(); i++) {
    if (line[i] == ',')
      count++;
  }
  reader.close();
  return count + 1;
}

void module2::check_Data_Type(int i, std::string line, int * col_Data_Type) {
  bool is_Integer = 1;
  int count_Decimal = 0;
  for (int j = 0; j < line.length(); j++) {
    if (line[j] <= '9' && line[j] >= '0') {
      is_Integer = 1;
    } else if (line[j] == '.')
      count_Decimal++;
    else {
      is_Integer = 0;
      break;
    }
  }
  if (is_Integer == 0)
    col_Data_Type[i] = 0;
  else if (is_Integer == 1 && count_Decimal < 2)
    col_Data_Type[i] = 1;
  else if (is_Integer == 1 && count_Decimal > 2)
    col_Data_Type[i] = 0;
  else
    col_Data_Type[i] = 2;
}

int module2::find_Data_Type(std::string file_Name, int * col_Data_Type) {
  int remaining_Cols = get_Total_Cols(file_Name);
  std::ifstream reader;
  reader.open(file_Name);
  std::string line = "";
  int count_Decimal, i;
  bool is_Integer;
  for (i = 0; i < remaining_Cols - 1; i++) {
    getline(reader, line, ',');
    check_Data_Type(i, line, col_Data_Type);
  }
  getline(reader, line, '\n');
  check_Data_Type(i, line, col_Data_Type);
  reader.close();
  return remaining_Cols;
}