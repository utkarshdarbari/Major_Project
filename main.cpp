#include "module1.h"
#include "module2.h"
#include "module3.h"
#include "module4.h"
#include "module5.h"
#include "module6.h"
#include "module7.h"
#include "module8.h"
int main() {
  
  module1 obj1;

  std::string file_Name = obj1.get_Csv_File_Name(); //read CSV file Name
  int total_Rows = obj1.store_File_Get_Total_Rows(file_Name); //get Row size and store scv file to Module1.csv
  int total_Cols= obj1.get_Total_Cols(file_Name); //get Number of Cols in CSV file
  obj1.display_File(); //display the CSV file
  int target_Col = obj1.set_Target_Col(); //set the target col
  std::set < int > remove_Col_Idx; //Store column idx to remove
  int removed_Cols = obj1.get_Col_Remove_Index(remove_Col_Idx, target_Col); //find index of cols to remove
  int remaining_Cols = total_Cols - removed_Cols; //remaining cols i.e new file will have remainingCols as No of Cols
  std::vector < std::string > data[remaining_Cols + 1];//stores all data in this field
  int empty_Values_Per_Col[remaining_Cols + 1];//calculates the number of elepty cells
  memset(empty_Values_Per_Col, 0, sizeof(empty_Values_Per_Col)); //initialize array to zero
  obj1.store_To_Vector(file_Name, remove_Col_Idx, data, total_Cols, target_Col, remaining_Cols, empty_Values_Per_Col);//stores values to data vector
  int limit = (total_Rows * 75) / 100;//max limit of each column having empty cells 
  obj1.store_Vector_To_File(data, total_Rows, remaining_Cols, limit, empty_Values_Per_Col);//removing the cols where empty cells are too many

  module2 obj2;

  int col_Data_Type[remaining_Cols + 1];
  memset(col_Data_Type, 0, sizeof(col_Data_Type)); //initialize array to zero
  remaining_Cols = obj2.find_Data_Type("Module1.csv", col_Data_Type); //1 is string, 0 is int, and 2 is null remaining cols are updated
  
  module3 obj3;

  obj1.store_To_Vector("Module1.csv", remove_Col_Idx, data, remaining_Cols, remaining_Cols, remaining_Cols, empty_Values_Per_Col);
  std::string mode[remaining_Cols];
  obj3.find_Mode(data, mode, total_Rows, remaining_Cols);
  double mean[remaining_Cols];
  std::string min[remaining_Cols], max[remaining_Cols];
  obj3.find_Mean(data, col_Data_Type, mean, total_Rows, remaining_Cols, max, min);
  std::cout << "After Filling Missing Values\n";
  obj3.fill_Missing_Values(mean, mode, data, remaining_Cols, total_Rows, col_Data_Type);
  memset(empty_Values_Per_Col, 0, sizeof(empty_Values_Per_Col)); //initialize array to zero
  obj1.store_Vector_To_File(data, total_Rows, remaining_Cols, limit, empty_Values_Per_Col);

  module4 obj4;

  bool sparse_Idx[remaining_Cols];
  memset(sparse_Idx, 0, sizeof(sparse_Idx));
  obj4.check_Nominal_Ordinal(data, col_Data_Type, total_Rows, remaining_Cols, sparse_Idx);
  std::cout << "After Converting Ordinal Strings\n";
  obj1.store_Vector_To_File(data, total_Rows, remaining_Cols, limit, empty_Values_Per_Col);

  module5 obj5;

  obj5.min_Max_Normalization(min, max, data, col_Data_Type, remaining_Cols, total_Rows);
  std::cout << "After normalization\n";
  obj1.store_Vector_To_File(data, total_Rows, remaining_Cols, limit, empty_Values_Per_Col);

  module6 obj6;

  double lower_Bound[remaining_Cols];
  double upper_Bound[remaining_Cols];
  std::set < int > outlier_Row_Idx;
  obj6.check_Outlier(data, sparse_Idx, remaining_Cols, total_Rows, upper_Bound, lower_Bound, outlier_Row_Idx);
  std::cout << "Outlier Removed\n";

  module7 obj7;
  
  int no_Of_Sparse = obj7.find_number_of_Sparse(sparse_Idx, remaining_Cols);
  std::vector < int > sparse_Matrix_Guide[no_Of_Sparse];
  int total_New_Columns = obj7.convert_Sparse_Cols(data, remaining_Cols, total_Rows, sparse_Idx, sparse_Matrix_Guide);
  std::cout << "Convertion of Sparse Matrix done\n";

  module8 obj8;

  int remaining_Rows = obj8.store_To_Final_File(data, remaining_Cols, total_Rows,outlier_Row_Idx, sparse_Matrix_Guide, no_Of_Sparse,  sparse_Idx, total_New_Columns);
  obj8.create_Test_Train_Split(remaining_Rows);
  return 0;
}