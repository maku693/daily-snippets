#include <iostream>

int main()
{
    int arr1[3] = { 1, 2, 3 };
    int arr2[3] = { 0, 0, 0 };

    for (int i = 0; i < 3; i++) {
        arr2[i] = std::move(arr1[i]);
    }

    std::cout << arr1[0] << arr1[1] << arr1[2] << "\n";
    std::cout << arr2[0] << arr2[1] << arr2[2] << "\n";
}
