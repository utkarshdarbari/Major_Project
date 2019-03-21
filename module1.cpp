#include "module1.h"

std::string module1::get_Csv_File_Name() {
  std::cout << "Enter the Name of the CSV File along with extention\n";
  std::string file_Name;
  std::cin >> file_Name;
  return file_Name;
}

int module1::store_File_Get_Total_Rows(std::string file_Name) {
  std::ifstream reader;
  std::ofstream writer;
  reader.open(file_Name);
  writer.open("Module1.csv"); //save to csv_File.csv
  std::string line = "";
  int count = 0;
  while (reader.good()) {
    count++;
    getline(reader, line, '\n'); //read line
    writer << line << "\n"; //store line
  };
  reader.close();
  writer.close();
  return count - 1; //return No of rows
}

int module1::get_Total_Cols(std::string file_Name) {
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

void module1::display_File() {
  system("./setPermission.sh");
  system("./showCSVfile.sh");
}

int module1::set_Target_Col() {
  int target;
  std::cout << "Enter the target Column\n";
  std::cin >> target;
  return target;
}

int module1::get_Col_Remove_Index(std::set < int > & remove_Col_Idx,
  int target_Col) {
  int idx, remove_Size;
  bool target_Remove = 0;
  std::cout << "Enter No of cols to remove?\n";
  std::cin >> remove_Size;
  for (int i = 0; i < remove_Size; i++) {
    std::cout << "Enter Col Number in digits\n";
    std::cin >> idx;
    if (idx == target_Col) {
      std::cout << "ERROR: You cannot remove the target coloumn\n";
      target_Remove = 1;
    } else
      remove_Col_Idx.insert(idx);
  }
  if (target_Remove == 1)
    return remove_Size - 1;
  else
    return remove_Size;
}

void module1::store_To_Vector(std::string file_Name,
  std::set < int > & remove_Col_Idx,
  std::vector < std::string > * data,
  int total_Cols,
  int target_Col,
  int remaining_Cols,
  int * empty_Values_Per_Col) 
{
  memset(empty_Values_Per_Col,0,sizeof(empty_Values_Per_Col));
  int i, j;
  std::ifstream reader;
  std::string line = "";
  reader.open(file_Name);
  std::set < int > ::iterator itr;
  while (reader.good()) {
    int count = 0;
    itr = remove_Col_Idx.begin();
    for (i = 1, j = 0; i < total_Cols; i++) {
      count++;
      getline(reader, line, ',');
      if ( * itr == i) {
        itr++;
      } else if (i == target_Col) {
        data[remaining_Cols - 1].push_back(line);
        if (line == "")
          empty_Values_Per_Col[remaining_Cols - 1]++;
      } else {
        data[j].push_back(line);
        if (line == "")
          empty_Values_Per_Col[j]++;
        j++;
      }
    }
    getline(reader, line, '\n');
    if (target_Col - 1 == count) {
      data[remaining_Cols - 1].push_back(line);
      if (line == "")
        empty_Values_Per_Col[remaining_Cols - 1]++;
    } else {
      data[j].push_back(line);
      if (line == "")
        empty_Values_Per_Col[j]++;
    }
  }
  remove_Col_Idx.clear();
  reader.close();
}

void module1::store_Vector_To_File(std::vector < std::string > * data,
  int total_Rows,
  int remaining_Cols,
  int limit,
  int * empty_Values_Per_Col) 
{
  std::ofstream writer;
  writer.open("Module1.csv");
  bool target_Above_Limit = 0;
  bool fill_started = 0;
  for (int i = 0; i < total_Rows; i++) {
    fill_started = 0;
    for (int j = 0; j < remaining_Cols; j++) {
      if (empty_Values_Per_Col[j] > limit) {
        if (j == remaining_Cols - 1) {
          writer << "," << data[j][i];
          target_Above_Limit = 1;
        }
      } else {
        if (fill_started == 1)
          writer << "," << data[j][i];
        else {
          writer << data[j][i];
          fill_started = 1;
        }
      }
    }
    writer << "\n";
  }
  for (int j = 0; j < remaining_Cols; j++) {
    data[j].clear();
  }
  writer.close();
  if (target_Above_Limit)
    std::cout << "WARNING: Too many missing values in Target Column\n";
  system("./showCSVfileModule1.sh");
}