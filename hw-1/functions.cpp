#include <stdexcept>
#include <vector>

// Длина входа, если вход:
// - число n - log2(n) = log n
// - одномерный массив - длина массива
// - двумерный массив - произведение размеров массива

// Вычисление чисел Фибоначчи. Последовательность Фибоначчи определяется как:
// a_0 = 0, a_1 = 1, a_k = a_k-1 + a_k-2, при 𝑘 ≥ 2. Дано: n, вычислить: a_n

// Длина входа log n
// Сложность по времени O(2^log n)
// Сложность по памяти O(1)
uint64_t fibonacci(unsigned int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    uint64_t left   = 0;
    uint64_t middle = 1;
    for (int i = 0; i <= n; ++i) {
        unsigned long long cache = middle;
        middle                   = left + middle;
        left                     = cache;
    }
    return middle;
}

// Дан невозрастающий массив из N элементов. Найти количество различных чисел
// среди элементов этого массива:
//  a. Для любых элементов
//  b. Если известно, что все элементы массива – числа от 1 до k

// a
// Длина входа N
// Сложность по времени O(N)
// Сложность по памяти O(1)
double diffNumsAmount(std::vector<double>& v) {
    if (v.empty()) throw std::invalid_argument("Array cannot be empty");

    double count = 0;
    double prev  = v[0];
    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] < prev) ++count;
        prev = v[i];
    }
    return count;
}

// b
// Длина входа N + log k
// Сложность по времени O(N)
// Сложность по памяти O(1)
double diffNumsAmount(std::vector<double>& v, int k) {
    // return k; // если есть условие, что обязательно должны быть все числа
    // из диапазона [1, k] Тогда сложность и по времени и по памяти - O(1) В
    // противном случае нет смысла менять алгоритм
    if (v.empty()) throw std::invalid_argument("Array cannot be empty");

    double count = 0;
    double prev  = v[0];
    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] < prev) ++count;
        prev = v[i];
    }
    return count;
}

// Вычислить сумму 1 / (1!) + 1 / (2!) + ... + 1 / (n!), n - натуральное

// Длина входа log n
// Сложность по времени O(2^log n)
// Сложность по памяти O(1)
double RowSum(uint8_t n) {
    if (n == 0)
        throw std::invalid_argument(
            "Can not calculate factorial of negative number");
    if (n == 1) return 1;
    double sum = 1;
    for (uint8_t i = 2; i < n; ++i) {
        sum += sum / i;
    }
    return sum;
}

// В массиве a[1], ... , a[n] встречаются по одному разу все числа от 0 до 𝑛,
// кроме одного. Найти пропущенное число (с константной доп. памятью).

// Длина входа n
// Сложность по времени O(n)
// Сложность по памяти O(1)
uint32_t whichNumIsMissing(std::vector<uint32_t>& v, uint32_t n) {
    uint64_t sum = 0;
    for (size_t i = 0; i < v.size(); ++i) {
        sum += v[i];
    }
    // (a_1 + a_n) / 2 * n - сумма арифметической прогрессии
    return n * n / 2 - sum;
}

// Дан двумерный массив x: array[n x n], такой, что: x[i][j] <= x[i][j + 1],
// x[i][j] <= x[i + 1][j], и число a. Требуется выяснить, встречается ли a в
// данном массиве.

// Длина входа n^2
// Сложность по времени O(n^2)
// Сложность по памяти O(1)
bool isContaining(std::vector<std::vector<double>>& v, double a) {
    if (v.empty()) return false;

    size_t lastCol = v[0].size();
    size_t lastStr = v.size();
    for (size_t i = 0; i < lastStr; ++i) {
        if (v[i][0] > a) {
            lastStr = i;
        }
        for (size_t j = 0; j < lastCol; ++j) {
            if (v[i][j] == a) return true;
            if (v[i][j] > a) {
                lastCol = j;
            }
        }
    }
    return false;
}

// Разработать программу, которая проверяет корректность заполнения судоку
// (размер N^2 x N^2)

// Длина входа N^4
// Сложность по времени O(N^4)
// Сложность по памяти O(1)
bool sudokuFilledCorrected(std::vector<std::vector<uint32_t>>& v) {
    // (a_1 + a_n) / 2 * n - сумма арифметической прогрессии
    const uint64_t sumThatShouldBe = (1 + v.size()) * v.size() / 2;
    for (size_t i = 0; i < v.size(); ++i) {
        uint64_t strSum = 0;
        for (size_t j = 0; j < v.size(); ++j) {
            if (v[i][j] == 0) return false;
            strSum += v[i][j];
            if (strSum > sumThatShouldBe) return false;
        }
        if (strSum != sumThatShouldBe) return false;
    }

    // Можно было бы исключить цикл ниже, но для этого потребовался бы массив
    // vector<uint64_t> размера N^2, хранивший бы суммы столбцов, что изменило
    // бы сложность по памяти до O(sqrt(N^4)), а сложность по времени до
    // O(sqrt(N^4))
    for (size_t j = 0; j < v.size(); ++j) {
        uint64_t colSum = 0;
        for (size_t i = 0; i < v.size(); ++i) {
            if (v[j][i] == 0) return false;
            colSum += v[j][i];
            if (colSum > sumThatShouldBe) return false;
        }
        if (colSum != sumThatShouldBe) return false;
    }

    return true;
}

// Дан массив целых чисел nums. Необходимо вернуть массив answer, где answer[i]
// равно произведению всех элементов массива, кроме nums[i]. Запрещается
// использование операции деления

// Длина входа n
// Сложность по времени O(n^2)
// Сложность по памяти O(n)
std::vector<uint64_t> compositionExceptSelf(std::vector<uint16_t>& nums) {
    std::vector<uint64_t> answer(nums.size(), 1);

    for (size_t i = 0; i < nums.size(); ++i) {
        for (size_t j = 0; j < answer.size(); ++j) {
            if (j == i) continue;
            answer[j] *= nums[i];
        }
    }

    return answer;
}
