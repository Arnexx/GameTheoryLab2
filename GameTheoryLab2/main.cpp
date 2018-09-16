#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

void generateRandomMatrix(vector<vector<int>> & matrix)
{
	for(int i = 0; i < matrix.size(); i++)
		for (int j = 0; j < matrix.size(); j++)
		{
			matrix[i].push_back(rand() % 90 + 10);
		}
}
int findMaxIndex(vector<int> array)
{
	int maxValue = array[0], maxIndex = 0;
	for (int i = 1; i < array.size(); i++)
	{
		if (array[i] > maxValue)
		{
			maxValue = array[i];
			maxIndex = i;
		}
	}
	return maxIndex;
}
vector<int> getColumn(vector<vector<int>> matrix, int columnNum)
{
	vector<int> result;
	result.resize(matrix[0].size());
	for(int i = 0; i < matrix.size(); i++)
	{
		result[i] = matrix[i][columnNum];
	}
	return result;
}

vector<vector<int>> intersection(vector <vector<int>> arrayA, vector <vector<int>> arrayB)
{
	vector<vector<int>> result;
	for (int i = 0; i < arrayA.size(); i++)
	{
		for (int j = 0; j < arrayB.size(); j++)
		{
			if ((arrayA[i][0] == arrayB[j][0]) && (arrayA[i][1] == arrayB[j][1]))
			{
				result.push_back(arrayA[i]);
				break;
			}
		}
	}
	return result;
}
vector<vector<int>> nash(vector<vector<int>> matrixA, vector<vector<int>> matrixB)
{
	vector<vector<int>> maxA, maxB;
	maxA.resize(matrixA.size());
	maxB.resize(matrixB.size());

	for (int j = 0; j < matrixA[0].size(); j++)
	{
		maxA[j].push_back(findMaxIndex(getColumn(matrixA, j)));
		maxA[j].push_back(j);
	}

	for (int i = 0; i < matrixB.size(); i++)
	{
		maxB[i].push_back(i);
		maxB[i].push_back(findMaxIndex(matrixB[i]));
	}

	return intersection(maxA, maxB);
}

bool moreEffective(int i1, int j1, int i2, int j2, vector<vector<int>> matrixA, vector<vector<int>> matrixB)
{
	return ((i1 != i2) || (j1 != j2)) && (matrixA[i1][j1] >= matrixA[i2][j2]) && (matrixB[i1][j1] >= matrixB[i2][j2]);
}

vector<vector<int>> pareto(vector<vector<int>> matrixA, vector<vector<int>> matrixB)
{
	int n = matrixA.size();
	bool isPareto;
	vector<int> vals;
	vals.resize(2);
	vector<vector<int>> paretoArray;
	for(int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			isPareto = true;
			for (int k = 0; k < n; k++)
			{
				for (int l = 0; l < n; l++)
				{
					if (moreEffective(k, l, i, j, matrixA, matrixB))
						isPareto = false;
				}
			}
			if (isPareto)
			{
				vals[0] = i;
				vals[1] = j;
				paretoArray.push_back(vals);
			}				
		}
	return paretoArray;
}

void printGameMatrix(vector<vector<int>> matrixA, vector<vector<int>> matrixB)
{
	cout << "Matrix game "<< matrixA.size() << " x " << matrixA.size() << endl;
	for (int i = 0; i < matrixA.size(); i++)
	{
		for (int j = 0; j < matrixA.size(); j++)
		{
			cout << "(" << matrixA[i][j] << ", " << matrixB[i][j] << ") ";
		}
		cout << endl;
	}
}

void printGame(const char* gameName, vector<vector<int>> matrixA, vector<vector<int>> matrixB)
{
	vector<vector<int>> nashArray, paretoArray, intersectionArray;
	cout << gameName << endl;
	printGameMatrix(matrixA, matrixB);
	nashArray = nash(matrixA, matrixB);
	paretoArray = pareto(matrixA, matrixB);
	intersectionArray = intersection(nashArray, paretoArray);

	cout << endl << "pareto: (";
	for (int i = 0; i < paretoArray.size(); i++)
	{
		cout << "{" << paretoArray[i][0] << ", " << paretoArray[i][1] << "} ";
	}
	cout << ")" << endl;

	cout << "nash: (";
	for (int i = 0; i < nashArray.size(); i++)
	{
		cout << "{" << nashArray[i][0] << ", " << nashArray[i][1] << "} ";
	}
	cout << ")" << endl;

	cout << "intersection: (";
	for (int i = 0; i < intersectionArray.size(); i++)
	{
		cout << "{" << intersectionArray[i][0] << ", " << intersectionArray[i][1] << "} ";
	}
	cout << ")" << endl << endl;
}

int main()
{
	vector<vector<int>> matrixA, matrixB;
	int size = 10;
	matrixA.resize(size);
	matrixB.resize(size);
	srand(400);
	generateRandomMatrix(matrixA);
	generateRandomMatrix(matrixB);
	printGame("Random matrix", matrixA, matrixB);
	
	vector<vector<int>> prisoner1 = { { -1, -10}, { 0, -5 } };
	vector<vector<int>> prisoner2 = { { -1, 0 }, { -10, -5 } };
	printGame("Game of prisoners", prisoner1, prisoner2);

	vector<vector<int>> family1 = { { 4, 0 }, { 0, 1 } };
	vector<vector<int>> family2 = { { 1, 0 }, { 0, 4 } };
	printGame("Family dispute", family1, family2);

	vector<vector<int>> crossroad1 = { { -1, 0 },{ 5, -10 } };
	vector<vector<int>> crossroad2 = { { -1, 5 },{ 0, -10 } };
	printGame("Crossroad", crossroad1, crossroad2);

	system("pause");
	return 0;
}