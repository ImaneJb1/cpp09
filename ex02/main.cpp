#include "PmergeMe.hpp"

template <typename Container>
void printVec(const Container& v)
{
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    std::vector<int> vector_arr;
    std::deque<int> deque_arr;

    if (!PmergeMe<std::vector<int> >::parser(argc, argv, vector_arr) ||
        !PmergeMe<std::deque<int> >::parser(argc, argv, deque_arr))
    {
        std::cout << "Error: invalid input\n";
        return 1;
    }

    std::cout << "Before: ";
    printVec(vector_arr);

    // ---------------- Vector ----------------

    std::vector<int> vec_tmp = vector_arr;

    clock_t start_vec = clock();
    // for(int i = 0; i < 1000; i++)
    PmergeMe<std::vector<int> >::mergeInstertVector(vec_tmp);

    clock_t end_vec = clock();

    // ---------------- Deque ----------------

    std::deque<int> deq_tmp = deque_arr;

    clock_t start_deq = clock();
    // for(int i = 0; i < 1000; i++)
    PmergeMe<std::deque<int> >::mergeInstertVector(deq_tmp);

    clock_t end_deq = clock();

    std::cout << "After:  ";
    printVec(vec_tmp);

    double vec_time =
        static_cast<double>(end_vec - start_vec) * 1000000.0 / CLOCKS_PER_SEC;

    double deq_time =
        static_cast<double>(end_deq - start_deq) * 1000000.0 / CLOCKS_PER_SEC;

    std::cout << std::fixed << std::setprecision(5);

    std::cout << "Time to process a range of "
              << vector_arr.size()
              << " elements with std::vector : "
              << vec_time << " us\n";

    std::cout << "Time to process a range of "
              << deque_arr.size()
              << " elements with std::deque : "
              << deq_time << " us\n";

    return 0;
}