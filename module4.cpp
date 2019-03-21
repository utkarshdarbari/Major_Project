#include"module4.h"

void module4::rank_Ordinal(std::vector < std::string > * data,
  int total_Rows, int index) {
  std::multimap < std::string, std::string > mapper;
  mapper.clear();
  std::string line, line2;
  for (int i = 0; i < total_Rows; i++) {
    line = data[index][i];
    if (mapper.find(line) == mapper.end()) {
      std::cout << "Enter rank for " << line << "\n";
      std::cin >> line2;
      mapper.insert(std::make_pair(line, line2));
    }
    data[index][i] = mapper.find(line) -> second;
  }
}

void module4::check_Nominal_Ordinal(std::vector < std::string > * data,
  int * col_Data_Type, int total_Rows,
  int remaining_Cols, bool * sparse_Idx) {
  int idx = 0;
  bool order_exists = 0;
  for (int i = 0; i < remaining_Cols; i++) {
    if (col_Data_Type[i] != 1) {
      std::cout << "\nDoes the Column " << i + 1 << " have an order \nSample of Column " << i + 1 << "\n";
      for (int j = 0; j < 5 && j < total_Rows; j++)
        std::cout << data[i][j] << "\n";
      std::cout << "\nPress 1 if order/rank exist, Press 0 otherwise\n";
      std::cin >> order_exists;
      if (order_exists) {
        sparse_Idx[i] = 0;
        rank_Ordinal(data, total_Rows, i);
      } else {
        sparse_Idx[i] = 1;
      }
    }
  }
}
