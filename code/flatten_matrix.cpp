#include <vector>
#include <iostream>

std::vector<double> flatten_matrix(std::vector<std::vector<double>> matrix, int matrix_size){
    std::vector<double> flattened = std::vector<double>(matrix_size, 0);
    for (int fila = 0; fila < matrix_size; fila++){
        int index = 0;
        for (index; index < matrix_size; index++){
            flattened.push_back(matrix[fila][index]);
        }
    }
    for (int j = 0; j < matrix_size; j++){
        flattened.push_back(0);
    }
    return flattened;
}

template<typename T>
void print_vector(const std::vector<T>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

int main(){
    std::vector<std::vector<double>> matrix = {{10.6,5.3,4.3,5.5,3.2,3.9,7.1,5.8,5.8,2.9},
                                                {1.2,6.1,7.1,5.9,8.1,10.4,4.2,5.6,5.5,9.5},
                                                {2.9,2.8,4.6,2.9,4.9,7.2,2.8,2.6,2.3,6.2},
                                                {7.5,2.1,3.9,2.3,3.7,2.2,4.0,2.6,2.7,1.3},
                                                {9.0,3.6,3.3,3.8,3.1,1.2,5.5,4.1,4.2,0.3},
                                                {4.4,9.8,10.8,9.6,11.8,14.1,7.9,9.3,9.2,13.2},
                                                {2.1,3.2,4.2,3.0,5.3,7.6,1.4,2.7,2.7,6.6},
                                                {2.3,3.1,4.0,2.9,5.1,7.4,1.2,2.6,2.9,6.4},
                                                {3.9,2.3,2.4,1.3,3.5,5.8,1.4,1.5,3.8,4.8},
                                                {3.7,4.8,5.8,4.6,6.9,9.2,3.5,4.3,4.2,8.2}};
    std::vector<double> flattened = flatten_matrix(matrix, 10);
    print_vector(flattened);
}