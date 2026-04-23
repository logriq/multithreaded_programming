#include <iostream>
#include <string>
#include <future>
#include <chrono>
#include <thread>

// Функція перевірки
std::string check_assignment(std::string student_name, int score_to_get) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return "Student " + student_name + " received " + std::to_string(score_to_get) + " points.";
}

int main() {
    // Асинхронний запуск
    auto result1 = std::async(std::launch::async, check_assignment, "Alice", 95);
    auto result2 = std::async(std::launch::async, check_assignment, "Bob", 88);

    std::cout << "Main thread: Working on other things..." << std::endl;

    // Отримання результатів
    std::cout << result1.get() << std::endl;
    std::cout << result2.get() << std::endl;

    return 0;
}