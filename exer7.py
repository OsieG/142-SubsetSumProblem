import numpy as np

def initialValues():
    x = int(input("Target sum: "))
    size = int(input("Size of the set: "))
    print("")

    arr = []
    i = 1
    copySize = size
    while size != 0:
        num = int(input(("{} : Number == ").format(i)))
        if num >= x:                                    #every value is lower than the target
            print(("{} : should be lower than the target: {}").format(num,x))
            continue
        if num in arr:                                  #prohibits double values; asks for a new one
            print(("{} already in the set").format(num))
            continue
        arr.append(num)
        size-=1
        i+=1

    print("\n")
    return(copySize,arr,x)

def sortSet(arr):                                       #Sorting uses bubble sort method
    n = len(arr)
    swapped = True

    while swapped:
        swapped = False
        for i in range(n-1):
            if arr[i] > arr[i+1]:
                temp = arr[i]
                arr[i] = arr[i+1]
                arr[i+1] = temp
                swapped = True
        n-=1
    return arr

def cellMax(mat2D,n,i,limit):
    start = 0
    while n != limit:
        if mat2D[i-1,start] == 1:
            mat2D[i,n] = 1
        start+=1
        n+=1
    return mat2D

def backtracking(mat2D,setNum,x):
    n = len(setNum)
    solution = []
    lim = -1*x
    skipCounter = 0
    for i in range(-1,lim,-1):
        if skipCounter != 0:
            skipCounter-=1
            continue
        arr = mat2D[:,i]
        for j in range(n):
            if arr[j] == 1:
                solution.append(setNum[j])
                skipCounter = setNum[j]-1
                break
    return solution
#-----------------------------------------------------------------------------------------------------------------------------------------------------

sizeOfSet, setOfNum, targetSum = initialValues()
setOfNum = sortSet(setOfNum)
matrix2D = np.zeros((sizeOfSet,targetSum+1))
matrix2D[:,0] = 1                                       #initializes 1 for the 0th column

for i in range(sizeOfSet):
    if i==0:
        matrix2D[i,setOfNum[0]] = 1
        continue
    matrix2D[i] = matrix2D[(i-1)]
    matrix2D = cellMax(matrix2D,setOfNum[i],i,targetSum+1)

if matrix2D[sizeOfSet-1,targetSum] != 1:                #checker if there's a solution
    print("There's no subset for the target value...\nProgram will now exit...")
    raise SystemExit

ans = backtracking(matrix2D,setOfNum,targetSum+1)
print(ans)