#include "utils.hpp"

void get_func_type(TYPE& func_type_id) {
    switch(func_type_id) {
        case 0:
            std::cout << "Function type: Void" << std::endl;
            break;
        case 1:
            std::cout << "Function type: Int32" << std::endl;
            break;
        case 2:
            std::cout << "Function type: Float32" << std::endl;
            break;
        default:
            std::cout << "Unknown function type ID: " << func_type_id << std::endl;
    }
}