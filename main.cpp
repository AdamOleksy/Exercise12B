#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <math.h>

std::vector<int> generateNumbers(int max, int quan);
std::vector<int> generatePrimes(int max);
std::vector<int> prepareDividendVector(std::vector<int> vec, int divider);

int main()
{
    int max, quantity;
    std::cout << "Do jakiej wartości liczby chcesz generować?: ";
    std::cin >> max;
    std::cout << "Ile liczb chcesz generować?: ";
    std::cin >> quantity;

    std::vector<int> vec = generateNumbers(max, quantity);
    std::vector<int> primes = generatePrimes(quantity);

    std::map<int, std::vector<int>> map;

    std::transform(primes.begin(), primes.end(),
                   std::inserter(map, map.begin()),
                   [&vec](int a){
                        return std::make_pair(a, prepareDividendVector(vec, a));}
    );


    for(auto a : map){
        std::cout << a.first << ": ";
            for(auto b : a.second)
                std::cout << b << " ";
        std::cout << std::endl;
    }


}

std::vector<int> generateNumbers(int max, int quan){
    std::vector<int> vec_;
    std::srand(std::time(nullptr));
    std::generate_n(std::back_inserter(vec_),quan,
                    [max](){return std::rand() % max;});
    return vec_;
}

std::vector<int> generatePrimes(int quantity){
    std::vector<int> vec(quantity,0);
    std::generate(vec.begin(), vec.end(),
                    [] {static int i = 2;
                        return i++;});

    std::vector<int> primeVec;
    std::copy(vec.begin(), vec.end(), std::back_inserter(primeVec));

    std::remove_if(vec.begin(), vec.end(),
                   [&primeVec](int number){
                    primeVec.erase(std::remove_if(primeVec.begin(), primeVec.end(),
                                              [number](int a){
                                                return ((a!=number) && (a % number==0));}), primeVec.end());
                    return false;
    });

    return primeVec;
}

std::vector<int> prepareDividendVector(std::vector<int> vec, int divider){

    std::vector<int> dVec;

    std::transform(vec.begin(), vec.end(),
                   std::back_inserter(dVec),[&divider](int a){
                                                if(a % divider == 0)
                                                    return a;}
    );

    dVec.erase(std::remove_if(dVec.begin(), dVec.end(),
                              [&divider](int a){
                                return a<divider;}), dVec.end());

    return dVec;
}
