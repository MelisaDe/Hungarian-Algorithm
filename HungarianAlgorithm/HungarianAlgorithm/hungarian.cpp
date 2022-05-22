#include<iostream>
#include<stdlib.h>
#include<time.h>

#define S 10
using namespace std;

void printMatrix(int[][S], int);
void yatayCikarma(int, int, int);
void dikeyCikarma(int, int, int);
void ilkcoz(int);
int kalanlar(int);
void ilkad(int, int);
void olusturma(int);

int Y[S][S], LD[S], LY[S], eslesmeDY[S], eslesmeYD[S], UstD[S], minYD[S], minDegerD[S];
bool SaY[S];


void main() {

	int A[S][S];
	int cs, min, size;
	int i, j;
	int optimal = 0;
	srand(time(NULL));

	cout << "Enter the size of matrix: ";
	cin >> size;
	cout << endl << endl;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			A[i][j] = rand() % 100;
		}
	}

	cout << "A matrix" << endl << "------------------------------" << endl;
	printMatrix(A, size);


	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			Y[i][j] = A[i][j];
		}
	}


	for (i = 0; i < size; i++)
	{
		min = Y[i][0];
		for (j = 0; j < size; j++)
		{
			min = Y[i][j] < min ? Y[i][j] : min;
		}
		yatayCikarma(size, min, i);
	}


	for (i = 0; i < size; i++)
	{
		min = Y[0][i];
		for (j = 0; j < size; j++)
		{
			min = Y[j][i] < min ? Y[j][i] : min;
		}
		dikeyCikarma(size, min, i);
	}


	for (i = 0; i < size; i++)
	{
		eslesmeDY[i] = -1;
		eslesmeYD[i] = -1;
	}

	ilkcoz(size);
	cs = kalanlar(size);
	while (cs < size)
	{
		ilkad(cs, size);
		olusturma(size);
		cs = kalanlar(size);
	}


	for (cs = 0; cs < size; cs++)
	{
		if (eslesmeDY[cs] >= size)
		{
			eslesmeDY[cs] = -1;
		}
	}

	for (i = 0; i < size; i++)
	{
		optimal += A[i][eslesmeDY[i]];
	}

	cout << endl << endl;
	cout << "optimal assignment: " << optimal;

	cout << endl << endl;
	system("pause");
}
void printMatrix(int A[][S], int size) {
	int i, j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			cout << A[i][j] << "\t";
		}
		cout << endl;
	}

}
void yatayCikarma(int size, int min, int i) {
	int j;
	for (j = 0; j < size; j++)
	{
		Y[i][j] = Y[i][j] - min;
	}

}
void dikeyCikarma(int size, int min, int i) {
	int j;

	for (j = 0; j < size; j++)
	{
		Y[j][i] = Y[j][i] - min;
	}

}
void ilkcoz(int size)
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		LD[i] = 100;
	}

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			LD[j] = Y[i][j] < LD[j] ? Y[i][j] : LD[j];
		}
	}

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (eslesmeDY[i] == -1 && eslesmeYD[j] == -1)
			{
				if (Y[i][j] - LY[i] - LD[j] == 0)
				{
					eslesmeDY[i] = j;
					eslesmeYD[j] = i;
				}
			}
		}
	}
}
int kalanlar(int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		if (eslesmeDY[i] == -1)
		{
			break;
		}
	}
	return i;
}
void ilkad(int cs, int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		SaY[i] = i == cs ? true : false;
		UstD[i] = -1;
	}

	for (i = 0; i < size; i++)
	{
		minDegerD[i] = Y[cs][i] - LY[cs] - LD[i];
		minYD[i] = cs;
	}
}
void olusturma(int size)
{
	int minSY, minSD, minDeger;
	int yatay, SaD, UstY, temp, sl;
	int i;
	while (true)
	{
		minSY = -1;
		minSD = -1;
		minDeger = 100;

		for (i = 0; i < size; i++)
		{
			if (UstD[i] == -1 && minDegerD[i] < minDeger)
			{
				minDeger = minDegerD[i];
				minSY = minYD[i];
				minSD = i;

			}
		}

		if (minDeger > 0)
		{
			for (i = 0; i < size; i++)
			{
				if (SaY[i] == true)
				{
					LY[i] += minDeger;
				}
			}
			for (i = 0; i < size; i++)
			{
				if (UstD[i] != -1)
				{
					LD[i] -= minDeger;
				}
				else
				{
					minDegerD[i] -= minDeger;
				}
			}
		}
		UstD[minSD] = minSY;

		if (eslesmeYD[minSD] == -1)
		{
			SaD = minSD;
			UstY = UstD[SaD];
			while (true)
			{
				temp = eslesmeDY[UstY];
				eslesmeDY[UstY] = SaD;
				eslesmeYD[SaD] = UstY;

				SaD = temp;

				if (SaD == -1)
				{
					break;
				}

				UstY = UstD[SaD];
			}
			return;
		}
		else
		{
			yatay = eslesmeYD[minSD];
			SaY[yatay] = true;

			for (i = 0; i < size; i++)
			{
				if (UstD[i] == -1)
				{
					sl = Y[yatay][i] - LY[yatay] - LD[i];

					if (minDegerD[i] > sl)
					{
						minDegerD[i] = sl;
						minYD[i] = yatay;
					}
				}
			}
		}
	}
}