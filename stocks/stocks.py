import pandas as pd
import numpy as np




df = pd.read_csv("WunderFund_data.csv")
prices = df['price']
print(prices)
"prices = [1,1,1,2]"
N  = len(prices)
matrix = np.zeros((N,N),dtype ='int64')
matrix[0,0] = 0
matrix[0,1] = -prices[0]
for j in  range(2,N):
    matrix[0,j] = (np.iinfo('int64').min)/2
for  i in range(1,N):
    for j in range(0,N):
        if (j > 0):
            if j == (N -1 ):
                matrix[i,j] = max([ matrix[i-1,j], matrix[i-1,j-1] - prices[i] ] )
            else:
                matrix[i,j] = max([ matrix[i-1,j], matrix[i-1,j-1] - prices[i], matrix[i-1,j+1] + prices[i]  ] )
        else: 
            matrix[i,j] = max([ matrix[i-1,j], matrix[i-1,j+1] + prices[i]  ] )

np.savetxt("foo.csv",matrix,"%d", delimiter=",")
list_results = []
for i in range (0,N):
    list_results.append(matrix[N-1,i]+i*prices[N-1])
print(max(list_results))
