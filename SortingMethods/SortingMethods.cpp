// SortingMethods.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <Windows.h>
using namespace std;

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;

}

int getMax(const vector<int>& arr) {
    int mx = arr[0];
    for (int num : arr)
        if (num > mx)
            mx = num;
    return mx;
}

void quickSort(int* arr, int left, int right) {
    if (left >= right) return;

    int pivot = arr[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;

        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (left < j) quickSort(arr, left, j);
    if (i < right) quickSort(arr, i, right);
}

void heapify(int* arr, int n, int i) {
    int parent = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if (leftChild < n && arr[leftChild] > arr[parent])
        parent = leftChild;

    if (rightChild < n && arr[rightChild] > arr[parent])
        parent = rightChild;

    if (parent != i) {
        swap(arr[i], arr[parent]);

        heapify(arr, n, parent);
    }
}

void heapSort(int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}

void bucketSort(int* arr, int n) {
    if (n <= 0) return;

    int maxValue = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > maxValue)
            maxValue = arr[i];
    }

    int bucketCount = n;
    vector<vector<int>> buckets(bucketCount);

    for (int i = 0; i < n; ++i) {
        int index = (arr[i] * bucketCount) / (maxValue + 1);
        buckets[index].push_back(arr[i]);
    }

    int index = 0;
    for (int i = 0; i < bucketCount; ++i) {
        sort(buckets[i].begin(), buckets[i].end());
        for (int j = 0; j < buckets[i].size(); ++j) {
            arr[index++] = buckets[i][j];
        }
    }
}

void countingSort(vector<int>& arr, int exp) {
    int n = arr.size();
    int* output = new int[n];
    int count[10] = { 0 };

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    delete[] output;
}

void countingSort2(int* arr, int n) {
    int maxVal = arr[0];
    int minVal = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
        if (arr[i] < minVal) minVal = arr[i];
    }

    int range = maxVal - minVal + 1;

    int* count = new int[range] {0};

    for (int i = 0; i < n; i++)
        count[arr[i] - minVal]++;

    for (int i = 1; i < range; i++)
        count[i] += count[i - 1];

    int* output = new int[n];
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    delete[] count;
    delete[] output;
}

void merge(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])  
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void radixSort(vector<int>& arr) {
    int max = getMax(arr);

    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(arr, exp);
    }
}

void radixSortWithNegatives(int* arr, int n) {
    vector<int> positives;
    vector<int> negatives;

    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0)
            positives.push_back(arr[i]);
        else
            negatives.push_back(-arr[i]);
    }

    if (!negatives.empty()) radixSort(negatives);
    if (!positives.empty()) radixSort(positives);

    // Восстанавливаем порядок: отрицательные в обратном порядке и снова минус
    int idx = 0;
    for (int i = negatives.size() - 1; i >= 0; i--)
        arr[idx++] = -negatives[i];
    for (int x : positives)
        arr[idx++] = x;
}


void invalidInput() {
    cout << "Введите корректное число." << endl;
    cin.clear();
    cin.ignore(10000, '\n');
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n;
    
    while (true)
    {
        cout << "Введите количество чисел в массиве: " ;
        if (cin >> n) {
            break;
        }
        else {
            invalidInput();
        }
    }
    int* arr = new int[n];

    int sortingType;
    while (true) 
    {
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 10;
        }

        cout << "Массив со случайными неупорядоченными числами: " << endl << " ";
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;

        cout << "Введите номер типа сортировки(1-6): ";
        if (cin >> sortingType) {
           
            switch (sortingType)
            {
            case 1:
                quickSort(arr, 0, n - 1);
                break;
            case 2:
                heapSort(arr, n);
                break;
            case 3:
                bucketSort(arr, n);
                break;
            case 4:
                radixSortWithNegatives(arr, n);
                break;
            case 5:
                countingSort2(arr, n);
                break;
            case 6:
                mergeSort(arr, 0, n - 1);
                break;

            default:
                invalidInput();
                break;
            }

            cout << ' ';
            for (int i = 0; i < n; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
            cout << endl;
        }
        else {
            invalidInput();
        }
    }

    delete[] arr;
    return 0;
}






// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
