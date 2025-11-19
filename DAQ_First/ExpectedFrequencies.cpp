
#include <iostream>
#include <cmath>
#include <numbers>
#include <vector>

//g++ -o Calculate ExpectedFrequencies.cpp

double calculate_falias(const long int &fs, const long int &f)
{
    double ws = 2 * M_PI * fs;
    double w = 2 * M_PI * f;
    double k = std::floor(w / ws);
    if (k == 0)
    {
        k = 1;
    }

    if (ws >= 2 * w)
    {
        return f;
    }
    return std::abs((w - k * ws) / 2 / M_PI);
}

int main()
{
    char comm{'i'};
    long int Fs{0}; // sampling freq
    long int F{0};  // signal freq

    std::vector<long int> freq{100, 200, 400, 600, 900, 1100, 1500, 1900, 2050, 4990};

    std::cout << "'q' to quit, 's' to run on the vector, any letter to reiterate\n";
    std::cout << "allahGrande$ ";
    std::cin >> comm;

    while (comm != 'q')
    {
        if (comm == 's')
        {
            std::cout << "sampling freq: ";
            std::cin >> Fs;
            for (auto &e : freq)
            {
                if (Fs > 2 * e)
                {
                    std::cout << "NO ALIAS ";
                }
                else{
                    std::cout << "Alias ";
                }
                std::cout  << "Freq: " << calculate_falias(Fs, e) << "  F_in: " << e << std::endl;
            }
            break;
        }

        std::cout << "frequencies (Fs, F): ";
        std::cin >> Fs >> F;

        if (Fs > 2 * F)
        {
            std::cout << "NO ALIAS ";
        }
        else{
            std::cout << "Alias ";
        }
        std::cout << "Freq: " << calculate_falias(Fs, F) << std::endl;
        std::cout << "allahGrande$ ";
        std::cin >> comm;
    }

    return 0;
}