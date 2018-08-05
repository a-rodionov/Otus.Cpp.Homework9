//http://acm.timus.ru/problem.aspx?space=1&num=1723

#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

// Так как любая подстрока является заклинанием, то проще всего искать кол-во 
// повторяющихся букв. Сначала сортируем строку, далее подсчитываем кол-во 
// подряд идущих одинаковых символов.

int main()
{
  std::list<char> spell;
  std::pair<size_t, char> result{0, 'a'};

  std::ios::sync_with_stdio(false);

  std::copy(std::istream_iterator<char>(std::cin),
            std::istream_iterator<char>(),
            std::back_inserter(spell));
  spell.sort();

  auto begin = spell.cbegin();
  auto end = spell.cend();
  while(begin != end) {
    auto pos = std::upper_bound(begin, end, *begin);
    auto count = std::distance(begin, pos);
    if(count > result.first)
      result = std::make_pair(count, *begin);
      begin = pos;
  }
  std::cout << result.second;
}