#include <iostream>

// Function to solve the Tower of Hanoi puzzle
void hanoi(int num, char source, char destination, char auxiliary) {
    if (num == 1) {
        std::cout << "Move disk 1 from " << source << " to " << destination << std::endl;
        return;
    }
    hanoi(num - 1, source, auxiliary, destination);
    std::cout << "Move disk " << num << " from " << source << " to " << destination << std::endl;
    hanoi(num - 1, auxiliary, destination, source);
}

int main() {
    int num;

    std::cout << "Enter the number of disks: ";
    std::cin >> num;

    std::cout << "The sequence of moves involved in the Tower of Hanoi are:" << std::endl;
    hanoi(num, 'A', 'C', 'B'); // 'A' is the source, 'C' is the destination, and 'B' is the auxiliary peg

    return 0;
}
