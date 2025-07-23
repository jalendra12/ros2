#include <chrono>
#include <thread>
#include <iostream>

int main() {
    auto start_wall = std::chrono::steady_clock::now();
    clock_t start_cpu = clock();

    std::this_thread::sleep_for(std::chrono::seconds(2)); // Sleep

    auto end_wall = std::chrono::steady_clock::now();
    clock_t end_cpu = clock();

    auto wall_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_wall - start_wall).count();
    double cpu_duration = 1000.0 * (end_cpu - start_cpu) / CLOCKS_PER_SEC;

    std::cout << "Wall time: " << wall_duration << "ms\n";
    std::cout << "CPU time: " << cpu_duration << "ms\n";
}