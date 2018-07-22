// http://acm.timus.ru/problem.aspx?space=1&num=1878

#include <iostream>
#include <string>
#include <array>
#include <numeric>
#include <algorithm>

int sub_mod(int a, int b, int mod)
{
    int sub{a - b};
    return sub < 0 ? (sub + mod) : sub;
}

int main()
{
  std::array<int, 4> elements;
  std::array<std::array<int, 4>, 4> distances{0};
  std::array<int, 4> distance_sums{0};
  int tmp;

  std::ios::sync_with_stdio(false);
  
  std::cin >> elements[0] >> elements[1] >> tmp >> tmp;
  std::cin >> elements[2] >> elements[3] >> tmp >> tmp;
  std::cin >> tmp >> tmp >> tmp >> tmp;
  std::cin >> tmp >> tmp >> tmp >> tmp;
  
  for(auto i{0}; i < 4; ++i)
  {
    for(auto j{i+1}; j < 4; ++j)
    {
      distances[i][j] = distances[j][i] = std::min<int>(sub_mod(elements[i], elements[j], 4),
                                                        sub_mod(elements[j], elements[i], 4));
    }
  }
  
  for(auto i{0}; i < 4; ++i)
  {
    distance_sums[i] = std::accumulate(std::cbegin(distances[i]), std::cend(distances[i]), 0);
  }
  std::cout << *std::min_element(std::cbegin(distance_sums), std::cend(distance_sums));
  return 0;
}