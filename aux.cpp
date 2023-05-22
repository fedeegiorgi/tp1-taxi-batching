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

std::vector<int64_t> set_supplies(int n){
    std::vector<int64_t> supplies = std::vector<int64_t>((2*n+2), -1);
    supplies[0] = n;
    for (int64_t i = 1; i <= n; i++){
        supplies[i] = 1;
    }
    supplies[2*n+1] = -n;
    return supplies;
}

std::vector<int64_t> set_end_nodes(int n) {
    std::vector<int64_t> ret;

    for(int i = 1; i < n+1; i++){
        ret.push_back(i);
    }

    for(int i = n+1; i < 2*n+1; i++){
        for(int j = 0; j < n; j++)
            ret.push_back(n+1+j);


    for(int i = 0; i < n; i++){
        ret.push_back(21);
    }

    return ret;

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
    std::vector<int64_t> supplies = set_supplies(10);
    print_vector(flattened);
    print_vector(supplies);
}