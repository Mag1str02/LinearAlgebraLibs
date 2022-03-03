#include <iostream>
#include <numeric>

#include "../Matrix/matrix.h"

int main() {
    Matrix m;
    std::string command_type;

    size_t i, j;
    Fraction y;

    while (std::cin >> command_type) {
        if (command_type == "help") {
            std::cout << "Welcome to Matrix Calculator" << std::endl
                      << "Available commands:" << std::endl
                      << "    help: Views command list." << std::endl
                      << "        No arguments required" << std::endl
                      << "    1: Performs first elementary operation with matrix (adds line i multiplied by y to line j)" << std::endl
                      << "        Arguments list: i j y" << std::endl
                      << "    2: Performs second elementary operation with matrix (swaps lines i and j)" << std::endl
                      << "        Arguments list: i j" << std::endl
                      << "    3: Performs third elementary operation with matrix (multiplies line i by y)" << std::endl
                      << "        Arguments list: i y" << std::endl
                      << "    4: Runs Matrix input process" << std::endl
                      << "        No arguments required" << std::endl
                      << "    exit: Closes program" << std::endl
                      << "        No arguments required" << std::endl
                      << "Good luck!" << std::endl;
        }
        if (command_type == "exit") {
            break;
        }
        if (command_type == "4") {
            m.InputMatrix();
            std::cout << std::endl << m << std::endl;
        }
        if (command_type == "4_") {
            m.InputMatrix();
            m.SimetrickGauss();
            std::cout << std::endl << m << std::endl;
        }
        if (command_type == "1") {
            std::cin >> i >> j >> y;
            --i;
            --j;
            m.Op1(i, j, y);
            std::cout << std::endl << m << std::endl;
        }

        if (command_type == "2") {
            std::cin >> i >> j;
            --i;
            --j;
            m.Op2(i, j);
            std::cout << std::endl << m << std::endl;
        }
        if (command_type == "3") {
            std::cin >> i >> y;
            --i;
            m.Op3(i, y);
            std::cout << std::endl << m << std::endl;
        }
        if (command_type == "1_") {
            std::cin >> i >> j >> y;
            --i;
            --j;
            m.Op1_s(i, j, y);
            std::cout << std::endl << m << std::endl;
        }
        if (command_type == "2_") {
            std::cin >> i >> j;
            --i;
            --j;
            m.Op2_s(i, j);
            std::cout << std::endl << m << std::endl;
        }
        if (command_type == "3_") {
            std::cin >> i >> y;
            --i;
            m.Op3_s(i, y);
            std::cout << std::endl << m << std::endl;
        }
    }
    return 0;
}