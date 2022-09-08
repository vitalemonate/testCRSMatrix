#include <iostream>
#include <ceres/ceres.h>
#include <vector>
#include <fstream>

Eigen::MatrixXd CRSMatrix2EigenMatrix(ceres::CRSMatrix *jacobian_crs_matrix)
{
    Eigen::MatrixXd J(jacobian_crs_matrix->num_rows, jacobian_crs_matrix->num_cols);
    J.setZero();

    std::vector<int> jacobian_crs_matrix_rows, jacobian_crs_matrix_cols;
    std::vector<double> jacobian_crs_matrix_values;
    jacobian_crs_matrix_rows = jacobian_crs_matrix->rows;
    jacobian_crs_matrix_cols = jacobian_crs_matrix->cols;
    jacobian_crs_matrix_values = jacobian_crs_matrix->values;

    int cur_index_in_cols_and_values = 0;
    // rows is a num_rows + 1 sized array
    int row_size = static_cast<int>(jacobian_crs_matrix_rows.size()) - 1;
    // outer loop traverse rows, inner loop traverse cols and values
    for (int row_index = 0; row_index < row_size; ++row_index)
    {
        while (cur_index_in_cols_and_values < jacobian_crs_matrix_rows[row_index + 1])
        {
            J(row_index, jacobian_crs_matrix_cols[cur_index_in_cols_and_values]) = jacobian_crs_matrix_values[cur_index_in_cols_and_values];
            cur_index_in_cols_and_values++;
        }
    }
    return J;
}

void testCRSMatrix2EigenMatrix()
{
    // A compressed row matrix stores its contents in three arrays,
    // rows, cols and values.
    //
    // rows is a num_rows + 1 sized array that points into the cols and
    // values array. For each row i:
    //
    // cols[rows[i]] ... cols[rows[i + 1] - 1] are the indices of the
    // non-zero columns of row i.
    //
    // values[rows[i]] .. values[rows[i + 1] - 1] are the values of the
    // corresponding entries.
    //
    // cols and values contain as many entries as there are non-zeros in
    // the matrix.
    //
    // e.g, consider the 3x4 sparse matrix
    //
    //  [ 0 10  0  4 ]
    //  [ 0  2 -3  2 ]
    //  [ 1  2  0  0 ]
    //
    // The three arrays will be:
    //
    //
    //            -row0-  ---row1---  -row2-
    //  rows   = [ 0,      2,          5,     7]
    //  cols   = [ 1,  3,  1,  2,  3,  0,  1]
    //  values = [10,  4,  2, -3,  2,  1,  2]

    ceres::CRSMatrix crs_matrix;
    std::vector<int> rows{0, 2, 5, 7};
    std::vector<int> cols{1, 3, 1, 2, 3, 0, 1};
    std::vector<double> values{10, 4, 2, -3, 2, 1, 2};

    crs_matrix.rows = rows;
    crs_matrix.cols = cols;
    crs_matrix.values = values;
    crs_matrix.num_rows = 3;
    crs_matrix.num_cols = 4;
    Eigen::MatrixXd eigen_matrix = CRSMatrix2EigenMatrix(&crs_matrix);
    std::cout << "eigen_matrix is \n"
              << eigen_matrix << std::endl;

    static std::ofstream eigen_matrix_file("../eigen_matrix.txt");
    eigen_matrix_file << std::fixed;
    eigen_matrix_file.precision(9);

    for(int i = 0; i < crs_matrix.num_rows; ++i){
        for(int j = 0;j < crs_matrix.num_cols; ++j){
            eigen_matrix_file << eigen_matrix(i, j);
            if(j == crs_matrix.num_cols - 1){
                eigen_matrix_file << std::endl;
            }
            else{
                eigen_matrix_file << " ";
            }
        }
    }
}

int main(int, char **)
{
    std::cout << "testCRSMatrix2EigenMatrix start !\n";
    testCRSMatrix2EigenMatrix();
    std::cout << "testCRSMatrix2EigenMatrix end !\n";
}
