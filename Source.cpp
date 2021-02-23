#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;
void Print_list(vector<int> list)
{
	for (int i = 0; i < list.size(); i++)
	{
		cout << list[i] << "\t";
	}
	cout << endl;
}
void Rand_vec(vector<int>& list)
{
	for (int i = 0; i < list.size(); i++)
	{
		list[i] = rand() % 1000;
	}
}
int GetSize()
{
	int size;
	cout << "Введите размер массива:\t";
	while (!(cin >> size) || size < 1)
	{
		cin.clear();
		while (cin.get() != '\n')
		{
			cin.ignore();
		}
		cout << "Введите корректное число:\t";
	}
	return size;
}


//balanced merge
vector<int> Merge(vector<int> list1, vector<int> list2)
{
	int l1 = 0;
	int l2 = 0;
	vector<int>tmp;
	while (l1 < list1.size() && l2 < list2.size()) 
	{
		if (list1[l1] <= list2[l2]) 
		{
			tmp.push_back(list1[l1]);
			l1++;
		}
		else 
		{
			tmp.push_back(list2[l2]);
			l2++;
		}
	}
	while (l1 < list1.size()) 
	{
		tmp.push_back(list1[l1]);
		l1++;
	}
	while (l2 < list2.size())
	{
		tmp.push_back(list2[l2]);
		l2++;
	}
	Print_list(tmp);//вывод серий минимум по 2 элемента
	cout << "-------------------------------------------" << endl;
	return tmp;
}
void Merge_sort(vector<int> &list) 
{
	if (list.size() < 2) 
	{
		return;
	}
	/*else if (list.size() == 2) 
	{
		if (list[0] > list[1]) swap(list[0], list[1]);
		return;
	}*/
	vector<int> left;
	vector<int> right;
	int mid = list.size() / 2;
	for (int i = 0; i < mid; i++) 
	{
		left.push_back(list[i]);
	}
	for (int i = mid; i < list.size(); i++)
	{
		right.push_back(list[i]);
	}
	Merge_sort(left);
	Merge_sort(right);
	list = Merge(left, right);
}

//natural merge
void Print_series(vector<vector<int>> list_of_series)
{
	for (int i = 0; i < list_of_series.size(); i++)
	{
		cout << i + 1 << "-я серия:" << endl;
		cout << "| ";
		for (int j = 0; j < list_of_series[i].size(); j++)
		{
			cout << list_of_series[i][j] << " ";
		}
		cout << "|" << endl;
	}
	cout << endl;
}
void Split_series(vector<vector<int>> &list_of_series, vector<int> list) 
{
	int i = 0;
	while (i < list.size())
	{
		vector<int> line;
		line.push_back(list[i]);
		i++;

		while (i < list.size() && list[i - 1] < list[i])
		{
			line.push_back(list[i]);
			i++;
		}

		list_of_series.push_back(line);
	}
}
vector<int> Merge_series(vector<int> list1, vector<int> list2) // Используется в естественном и многофазном слиянии
{
	int l1 = 0, l2 = 0;
	vector <int> tmp;
	while (l1 < list1.size() && l2 < list2.size())
	{
		if (list1[l1] <= list2[l2])
		{
			tmp.push_back(list1[l1]);
			l1++;
		}
		else
		{
			tmp.push_back(list2[l2]);
			l2++;
		}
	}
	while (l1 < list1.size())
	{
		tmp.push_back(list1[l1]);
		l1++;
	}
	while (l2 < list2.size())
	{
		tmp.push_back(list2[l2]);
		l2++;
	}
	return tmp;
}
vector<int> Natural_merge(vector<int> list)
{
	vector<vector<int>> list_of_series;
	Split_series(list_of_series, list); //разделение массива на серии по возрастанию
	Print_series(list_of_series); //вывод серий

	while (list_of_series.size() >= 2) 
	{
		vector<int> Merged = Merge_series(list_of_series[0], list_of_series[1]);//слияние первой и второй серии
		list_of_series.push_back(Merged); //добавление первой и второй серии после слияния в конец массива серий
		list_of_series.erase(list_of_series.begin());//удаление первой серии
		list_of_series.erase(list_of_series.begin());//удаление второй серии
	}
	return list_of_series[0];
}


//Phase_merge
void Print_Files(vector<vector<int>> File1, vector<vector<int>> File2, vector<vector<int>> File3)
{
	cout << "F1:" << endl;
	Print_series(File1);
	cout << "=============================================" << endl;
	cout << "F2:" << endl;
	Print_series(File2);
	cout << "=============================================" << endl;
	cout << "F3:" << endl;
	Print_series(File3);
	cout << "=============================================" << endl;
}

void Fibb(int count_of_series, int &size1, int &size2) 
{
	size1 = 0, size2 = 1;
	while (size1 + size2 < count_of_series) 
	{
		int tmp = size2;
		size2 += size1;
		size1 = tmp;
	}
}

vector<vector<int>> Split_to_series(vector<int> list) 
{
	vector<vector<int>> result;
	int count;
	if (list.size() < 8) {
		count = 1;
	}
	else
	{
		count = list.size() / 8;
		while (list.size() % count != 0)
			count--; // нахождение максимального количества элементов в серии (для скорости размер массива делится на 4)
	}
	int i = 0;
	for (int i = 0; i < list.size() / count; i++)
	{
		vector<int> tmp;
		for (int j = 0; j < count; j++)
		{
			tmp.push_back(list[i * count + j]);
		}
		result.push_back(tmp);
	}
	return result;
}

vector<vector<int>> Files_Merge(vector<vector<int>> &F1, vector<vector<int>> &F2)
{
	vector<vector<int>> result; //"входной файл"
	int min;
	if (F1.size() < F2.size()) //выбор наименьшего количества серий в файле
		min = F1.size();
	else
		min = F2.size();
	
	for (int i = 0; i < min; i++)
	{
		result.push_back(Merge_series(F1[i], F2[i])); // слияние 2 серий и добавление
																	// во входной файл
	}

	F1.erase(F1.begin(), F1.begin() + min); // Удаление серий,которые 
	F2.erase(F2.begin(), F2.begin() + min); 			   // попали во входной файл

	return result;
}

void Delete_emptySerie(vector<int> &list) 
{
	while (list[0] == -100) 
	{
		list.erase(list.begin());
	}
}

vector<int> Phase_merge(vector<int> list) 
{
	vector<vector<int>> series = Split_to_series(list);
	int size1, size2; // size1 - количество серий во 2 файле(векторе) size2 - количество серий во втором файле(векторе)

	vector<vector<int>> File1, File2, File3; //файлы
	Fibb(series.size(), size1, size2); // получение количества серий в 1 и 2 файле

	//___________________Заполнение файлов________________________//
	for (int i = 0; i < size1; i++) 
	{
		File1.push_back(series[i]);
	}
	if (size1 + size2 == series.size()) 
	{
		for (int i = size1; i < series.size(); i++) 
		{
			File2.push_back(series[i]);
		}
	}
	else 
	{
		int tmp = size1;
		for (tmp; tmp < series.size(); tmp++)
		{
			File2.push_back(series[tmp]);
		}

		for (tmp; tmp < size1 + size2; tmp++) 
		{
			vector<int> empty_serie;
			for (int j = 0; j < File2[0].size(); j++)
			{
				empty_serie.push_back(-100);
			}
			File2.push_back(empty_serie);
		}
	}
	//_________________________________________________________________//
	
	Print_Files(File1, File2, File3); //вывод файлов

	//_______________________Сортировка файлов________________________//
	for (int i = 0; i < File1.size(); i++) 
	{
		sort(File1[i].begin(), File1[i].end());
	}
	for (int i = 0; i < File2.size(); i++)
	{
		sort(File2[i].begin(), File2[i].end());
	}
	//_________________________________________________________________//

	cout << "Файлы после сортировки:" << endl;
	Print_Files(File1, File2, File3); //вывод файлов

	//________________________Слияние_________________________________//
	int count_of_emptyfiles = 1; //изначально File3
	while (count_of_emptyfiles != 2) 
	{
		int empty_index = 3; // изначально 3;
		if (File1.empty()) empty_index = 1;
		if (File2.empty()) empty_index = 2;
		switch (empty_index) 
		{
			case 1: 
			{
				File1 = Files_Merge(File2, File3);
				break;
			}
			case 2: 
			{
				File2 = Files_Merge(File1, File3);
				break;
			}
			case 3: 
			{
				File3 = Files_Merge(File1, File2);
				break;
			}
		}
		count_of_emptyfiles = 0;
		if (File1.empty()) count_of_emptyfiles++;
		if (File2.empty()) count_of_emptyfiles++;
		if (File3.empty()) count_of_emptyfiles++;
		Print_Files(File1, File2, File3);
	}

	if (!File1.empty())
	{
		Delete_emptySerie(File1[0]);
		return File1[0];
	}
	if (!File2.empty())
	{
		Delete_emptySerie(File2[0]);
		return File2[0];
	}
	if (!File3.empty())
	{
		Delete_emptySerie(File3[0]);
		return File3[0];
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(0));
	int size = GetSize();
	vector <int> list(size);
	Rand_vec(list);
	cout << "Исходный массив:" << endl;
	Print_list(list);
	cout << "======================================================================================================================" << endl << endl;
	cout << "Массив, отсортированный сбалансированным слиянием:" << endl;
	cout << "Серии и конечный массив" << endl << endl;
	Merge_sort(list);
	cout << "======================================================================================================================" << endl << endl;
	cout << "Исходный массив:" << endl;
	Rand_vec(list);
	Print_list(list);
	cout << "======================================================================================================================" << endl << endl;
	cout << "Массив, отсортированный натуральным слиянием:" << endl;
	list = Natural_merge(list);
	Print_list(list);
	cout << "======================================================================================================================" << endl << endl;
	cout << "Исходный массив:" << endl;
	Rand_vec(list);
	Print_list(list);
	cout << "======================================================================================================================" << endl << endl;
	cout << "Массив, отсортированный многофазныйм слиянием:" << endl;
	list = Phase_merge(list);
	cout << "Отсортированный массив:" << endl;
	Print_list(list);
	cout << "======================================================================================================================" << endl;
}