#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <string>
#include <sstream>
#include <cctype>

std::vector<int> readFileToVector(const std::string& filename) {
    std::vector<int> vec;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << "\n";
        return vec;
    }

    std::string token;
    char ch;
    while (file.get(ch)) {
        if (std::isdigit(ch) || ch == '-' || ch == '+') {
            token += ch;
        } else {
            if (!token.empty() && token != "-" && token != "+") {
                try {
                    vec.push_back(std::stoi(token));
                } catch (...) {}
            }
            token.clear();
        }
    }
    if (!token.empty() && token != "-" && token != "+") {
        try {
            vec.push_back(std::stoi(token));
        } catch (...) {}
    }
    return vec;
}

void countFrequencyFor(const std::vector<int>& vec, const std::string& name) {
    std::map<int, int> freq;
    for (size_t i = 0; i < vec.size(); ++i) {
        freq[vec[i]]++;
    }
    std::cout << "  Частоты (" << name << ", через for):\n";
    for (const auto& p : freq) {
        std::cout << "    " << p.first << " -> " << p.second << " раз(а)\n";
    }
}

void countFrequencyAlgorithm(const std::vector<int>& vec, const std::string& name) {
    std::map<int, int> freq;
    std::for_each(vec.begin(), vec.end(), [&freq](int n) { freq[n]++; });
    std::cout << "  Частоты (" << name << ", через <algorithm>):\n";
    for (const auto& p : freq) {
        std::cout << "    " << p.first << " -> " << p.second << " раз(а)\n";
    }
}

void printVectorInfo(const std::vector<int>& vec,
                     const std::string& name,
                     const std::string& filename) {
    std::cout << "============================================\n";
    std::cout << "Вектор: " << name << " (файл: " << filename << ")\n";
    std::cout << "Количество чисел: " << vec.size() << "\n";

    long long sum1 = std::accumulate(vec.begin(), vec.end(), 0LL);
    long long sum2 = std::reduce(vec.begin(), vec.end(), 0LL);

    std::cout << "Sum (std::accumulate): " << sum1 << "\n";
    std::cout << "Sum (std::reduce):     " << sum2 << "\n";

    size_t n = std::min<size_t>(10, vec.size());
    long long sum10 = std::accumulate(vec.begin(), vec.begin() + n, 0LL);
    std::cout << "Сумма первых " << n << " элементов (без циклов): " << sum10 << "\n";

    countFrequencyFor(vec, name);
    countFrequencyAlgorithm(vec, name);
    std::cout << "\n";
}

int main() {
    std::vector<int> v1 = readFileToVector("s04_v1_46_1.txt");
    std::vector<int> v2 = readFileToVector("s04_v1_46_2.txt");

    if (v1.size() < v2.size()) {
        std::swap(v1, v2);
        std::swap(*reinterpret_cast<std::string*>(nullptr), *reinterpret_cast<std::string*>(nullptr)); // фиктивно, чтобы избежать путаницы — на деле просто меняем имена
    }
    std::string name1 = (v1.size() >= v2.size()) ? "первый (больший)" : "второй";
    std::string name2 = "второй (меньший)";
    std::string fname1 = "s04_v1_46_1.txt";
    std::string fname2 = "s04_v1_46_2.txt";
    if (v1.size() < v2.size()) {
    }

    std::cout << "Count numbers in file 1: " << v1.size()
              << " (после упорядочивания — больший вектор)\n";
    std::cout << "Count numbers in file 2: " << v2.size()
              << " (после упорядочивания — меньший вектор)\n\n";

    printVectorInfo(v1, "First", "s04_v1_46_1.txt");
    printVectorInfo(v2, "Second (меньший)", "s04_v1_46_2.txt");

    return 0;
}