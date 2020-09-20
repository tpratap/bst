import numpy as np 
from fractions import Fraction as f 

def min_test(table,ind):
    r=0
    jnd=0
    i=0
    min=99999
    l=list(table[:,ind])
    while i < M:
        if l[i] != 0.0:
            val=table[i,4+M]/l[i]
            if val >= 0:
                if min > val:
                    min= val
                    jnd=i
                    r=1
        i=i+1
    return jnd,r

# Input and Table formation 
M = int(input("Enter the number of  equations:"))
print("Enter the maximizing equation coefficient separated by space:(Ax + By): ")
Xj=list(map(float,input().split()))
print(Xj)
for i in range(M):
    Xj.append(float(0))
print(Xj)    
B=list()
matrix=list()
cb=list()   
right=[]
print("Enter the equations coefficient separated by space:(Ax + By >= C): ")
for i in range(M):
    print("A B C ")
    entries=list(map(float,input().split()))
    right.append(entries.pop(-1))
    matrix.append(entries)
A =np.array(matrix)      
for i in range(M):
    cb.append(0)
    B.append(i+2)
cb= np.array(cb)
cb=np.transpose([cb])
c= np.array(Xj)
c=np.transpose([c])  
B = np.array(B)
B=np.transpose([B]) 
table = np.hstack((B, cb))
table = np.hstack((table, A))
slack=np.identity(M)
table=np.append(table,slack,axis=1)
right=np.transpose([right])
table = np.hstack((table, right))
table = np.array(table, dtype ='float')

# Table display and Iteration
v=""
itr=0
for i in range(2,M):
    v=v+("\tx" +str(i+3))
while True:
    itr=itr+1
    print("Table iteration: " + str(itr)) 
    print("B \tCB \tx1 \tx2 \tx3 \tx4 "+v+" \tRHS")
    i=0
    for row in table:
        for el in row:
            if i%(M+5)== 0:
                print('x'+str(int(el)+1), end ='\t')
            else:
                print(f(str(el)).limit_denominator(100), end ='\t')
            i=i+1
        print() 
    print()
    i=0
    Cj_Zj=[]
    theta=[]
    while i<len(Xj):
        Cj_Zj.append(Xj[i] - np.sum(table[:, 1]*table[:, 2 + i]))
        i = i + 1 
    print("Cj_Zj",end='\t\t')
    for el in Cj_Zj: 
            print(f(str(el)).limit_denominator(100), end ='\t')  
    if max(Cj_Zj)<=0:
        break
    ind=Cj_Zj.index(max(Cj_Zj))+2
    jnd,r=min_test(table,ind)
    if r==0:
        print("Unboundedness occured")
        break;
    pivot=table[jnd,ind]
    table[jnd, 2:M+5] = table[jnd, 2:M+5] / pivot
    i=0
    while i<M:
        if i != jnd:
            table[i, 2:M+5] = table[i,2:M+5] - table[i][ind]*table[jnd][2:M+5]
        i=i+1
     # Assign the new basic variable 
    table[jnd][0] = ind-2 
    table[jnd][1] = Xj[ind-2]
    print() 
    print()
# Alternate Solution
if not np.any(table[:,0]== 0):
    ind=2
elif not np.any(table[:,0]== 1):
    ind=3
else:
    ind=-1
if (ind == 2 or ind == 3):
    jnd,r=min_test(table,ind)
    pivot=table[jnd,ind]
    table[jnd, 2:M+5] = table[jnd, 2:M+5] / pivot
    i=0
    while i<M:
        if i != jnd:
            table[i, 2:M+5] = table[i,2:M+5] - table[i][ind]*table[jnd][2:M+5]
        i=i+1
    # Assign the new basic variable 
    table[jnd][0] = ind-2 
    table[jnd][1] = Xj[ind-2]
    print("\n \t\t Alternate Solution")
    itr=itr+1
    print("Table iteration: " + str(itr)) 
    print("B \tCB \tx1 \tx2 \tx3 \tx4 "+v+" \tRHS")
    i=0
    for row in table:
        for el in row:
            if i%(M+5)== 0:
                print('x'+str(int(el)+1), end ='\t')
            else:
                print(f(str(el)).limit_denominator(100), end ='\t')
            i=i+1
        print() 
    print()
    print() 
    print()
# Maximum  Possible Value 
Z= np.sum(table[:, 1]*table[:,M+4])
print("Maximum Z= ",Z)

    
    
