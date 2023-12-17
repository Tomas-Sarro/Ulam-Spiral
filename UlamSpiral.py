import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
from timeit import default_timer as timer
from PIL import Image
start = timer()


NumRow = 501
summation = 0

CenterRow = int((NumRow/2)//1)
H = 1
primeCount = 0

MatrixInitialize = timer()
Matrix = np.full(shape=(NumRow,NumRow), fill_value=0)
Matrix[CenterRow,CenterRow] = 1


def IsPrime(n,x,y):
    global primeCount
    if (n <= 3):
        primeCount += 1
        Matrix[x][y] = 1
        return(1)
    
    if ((n % 2 == 0) or (n % 3 == 0)):
        return(1)

    for m in range(5, int(n**0.5)+1,6):
        if ((n % m == 0) or (n % (m+2)) == 0):
            return(1)

    primeCount += 1
    Matrix[x][y] = 1

for i in range(0, NumRow*2 - 1):

    x = CenterRow + (-1)**(int((i/2)//1)) * int((i/4 + 1/2)//1)
    y = CenterRow + int(((-1)**(int((i/2 - 1/2)//1)) * int((i/4 + 3/4)//1))//1)
    n = int((i/2 + 1)//1)

    k = (2*((i+1)**2) -1 + (-1)**(i+1))/8 + 2

    if(i == (NumRow*2 - 2)):
        n = int((k-2)**0.5)//1
        
        for i in range(1,n+1):
                Matrix[x][y+i] = 0
                IsPrime((k+i-1),x,y+i)
        break


    b = [0,-1,0,1]

    for z in range(1, n+1):
        Matrix[x + (z*b[i%4])][y + (z*b[3-(i%4)])] = 0
        IsPrime((k + z - 1),(x + (z*b[i%4])), (y + (z*b[3-(i%4)])))


Matrix[CenterRow,CenterRow] = 0
Matrix[CenterRow,CenterRow+1] = 1

print("Total time to generate = ", timer()-start)
print("primecount : ", primeCount)
    
fig, ax = plt.subplots()
im = ax.imshow(Matrix)

plt.show()

rescaled = (255.0 / Matrix.max() * (Matrix - Matrix.min())).astype(np.uint8)

im = Image.fromarray(rescaled)
im.save("UlamOutput.jpeg")


