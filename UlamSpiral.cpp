#include <iostream>
#include <cmath>
#include "time.h"

	//				Regular		6n+-1 & n%2		primality wiki		Cleaned		With PFM
	//	51^2	=	0.02s		0.06s			0.022s				0.017s
	//	101^2	=	0.034s		0.065s			0.019s				0.02s
	//	201^2	=	0.035s		0.037s			0.016s				0.014s
	//	501^2	=	0.15s		0.149s			0.022s				0.017s
	//	701^2	=	0.318s		0.326s			0.064s				0.025s
	//	901^2	=	0.579s		0.582s			0.065s				0.04s
	//	1001^2	=	0.763s		0.768s			0.078s				0.05s
	//	2001^2	=	4.558s		4.706s			0.589s				0.277s
	//	3001^2	=	13.909s		14.213s			1.092s				0.815s
	//	4001^2	=	30.28s		31.586s			4.075s				1.765s
	//	5001^2	=	58.525s		59.165s			4.118s				3.305s
	//	6001^2	=	97.628s		98.706s			6.592s				5.405s
	//	10001^2	=	416.341s	417.347s		27.139s				22.329s		24.124s
	//  20001^2 =								176.883s			160.872s
	//	25001^2 =								342.683s			305.158s
	//	30001^2 =								556.122s			513.324s
	//	40001^2 =													1181.89s
	//	50001^2 =													1825.47s
	//	60001^2 =													1832.49s
	//	70001^2 =													2140.61s	2477.79s
	//	100001^2 =																6196.43s

int numRow = 0;
int primeCount = 0;
int summation = 0;
double H = 1;

int isPrime(int n, int x, int y, int** ulamArray) {
	if (n == 2 || n == 3) {
		primeCount += 1;
		ulamArray[x][y] = 1;
		return(1);
	}

	if (n <= 1 || n % 2 == 0 || n % 3 == 0)
		return(1);

	for (int k = 5; k * k <= n; k += 6) {
		if (n % k == 0 || n % (k + 2) == 0)
			return(1);
	}

	primeCount += 1;
	ulamArray[x][y] = 1;
}

int main() {

	std::cout << "Enter the size of the grid: ";
	std::cin >> numRow;

	if (numRow % 2 == 0)
		numRow = numRow + 1;

	clock_t startTime = clock();

	int centerRow = (numRow - 1) / 2;

	int** ulamArray = new int* [numRow];
	for (int i = 0; i < numRow; i++)
		ulamArray[i] = new int[numRow];

	ulamArray[centerRow][centerRow] = 0;

	for (int i = 0; i < pow(numRow, 2) - 1; i++) {

		int x = centerRow + pow(-1, floor(i / 2)) * floor((i + 2) / 4);
		int y = centerRow + floor(pow(-1, floor((i - 1) / 2)) * floor((i + 3) / 4));
		int n = floor((i + 2) / 2);
		summation = summation + floor((i + 1) / 2);

		if (i == (numRow * 2 - 2)) {
			n = sqrt(summation);
			for (int i = 1; i < (n + 1); i++) {
				ulamArray[x][y + i] = 0;
				isPrime((summation + i + 1), x, y + i, ulamArray);
			}
			break;
		}

		int b[4] = { 0,-1,0,1 };

		for (int z = 1; z < (n + 1); z++) {
			ulamArray[x + (z * b[i % 4])][y + (z * b[3 - (i % 4)])] = 0;
			isPrime((summation + z + 1), (x + (z * b[i % 4])), (y + (z * b[3 - (i % 4)])), ulamArray);
		}
	}
	

	std::cout << std::endl;
	std::cout << "Time taken: " << (double)(clock() - startTime) / CLOCKS_PER_SEC << std::endl;
	std::cout << "Row size: " << numRow << " | Grid size: " << numRow*numRow << std::endl;
	std::cout << "Prime count: " << primeCount << std::endl;

	//cv::imwrite("output_image.png", imageMat);
	return 0;
}