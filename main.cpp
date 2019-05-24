#include <iostream>

class SortInterface{
public:
    virtual int* doSort(int*, int) = 0;
};

class InsertionSort : public SortInterface{
public:
    int* doSort(int* arr, int size){
        int* temp = new int[size];
        for(int i = 0; i < size; i++){
            temp[i] = arr[i];
        }

        for(int i = 1; i < size; i++){
            int j = i;
            while(j > 0 && temp[j-1] > temp[j]){
                std::swap(temp[j-1], temp[j]);
                j--;
            }
        }
        return temp;
    };
};

int main() {
    int n;
    std::cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++)
        std::cin >> arr[i];

    SortInterface* solver = new InsertionSort;
    int* solve = solver->doSort(arr, n);
    delete solver;

    for(int i = 0; i < n; i++)
        std::cout << solve[i] << " ";
    delete[] solve;
    return 0;
}
