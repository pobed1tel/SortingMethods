// SortingMethods.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdlib>
#include <Windows.h>
using namespace std;

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;

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
            cout << "Введите корректное число." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    cout << "Массив со случайными неупорядоченными числами: " << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    int sortingType;
    while (true) 
    {
        cout << "Введите номер типа сортировки(1-6): ";
        if (cin >> sortingType && sortingType > 0 && sortingType < 7) {
            switch (sortingType)
            {
            case 1:
                quickSort(arr, 0, n - 1);
                break;

            default:
                break;
            }
            for (int i = 0; i < n; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
        else {
            cout << "Введите корректное число." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
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
