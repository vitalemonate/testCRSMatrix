# 
A project which contains test code to convert ceres [CRSMatrix](http://ceres-solver.org/nnls_solving.html?highlight=crsmatrix#_CPPv4N5ceres9CRSMatrixE) to eigen style matrix.

# Usage
1. convert CRSMatrix to eigen style matrix
```
mkdir build
cd build
cmake ..
make testCRSMatrix
./testCRSMatrix
cd ../
```

2. visualize sparse matrix
```
python plot_sparse_matrix.py eigen_matrix.txt
```
