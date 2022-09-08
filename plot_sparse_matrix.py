import matplotlib.pyplot as plt
import numpy as np 
from scipy.sparse import csr_matrix
import pandas as pd 
import sys
import os

file_path = os.path.abspath(sys.argv[1])
dense_matrix = pd.read_table(file_path, header=None, sep=' ')
dense_matrix = np.array(dense_matrix.values.tolist(), dtype='float64')

sparse_matrix = csr_matrix(dense_matrix)
plt.spy(sparse_matrix)
plt.show()