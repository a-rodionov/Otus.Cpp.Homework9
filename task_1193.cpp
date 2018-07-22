// В студенческой группе проходит устный зачёт. В момент начала зачёта каждый
// студент получает от преподавателя вопрос и начинает готовиться к ответу.
// Для подготовки ответа студенту требуется T1 минут, а для самого ответа — T2
//  минут (эти параметры могут быть разными для разных студентов). Также для
// каждого студента известно время T3 (в минутах от запланированного времени
// начала зачёта), не позднее которого он должен освободиться, так как у него
// есть другие важные дела (например, зачёты по другим предметам).
// В процессе зачёта формируется очередь по мере того, как студенты заканчивают
// подготовку. Если в текущий момент никто не отвечает, то подготовившийся
// студент немедленно начинает ответ, иначе встает в конец очереди и начинает
// отвечать сразу после окончания ответа того студента, который стоит в очереди
// перед ним. Может так случиться, что некоторые студенты не успеют по своим
// делам (то есть закончат ответ позднее своего времени T3). Преподаватель готов
// пойти им навстречу и начать принимать зачёт пораньше. Однако приходить в
// университет слишком рано ему тоже не хочется! Напишите программу, которая
// помогла бы преподавателю и студентам: эта программа должна определить 
// минимальное время (в минутах), на которое надо сдвинуть начало зачёта, чтобы
// все студенты успели по своим делам.
//
// Исходные данные
// В первой строке содержится число N — количество студентов (1 ≤ N ≤ 40) Далее
// следуют N строк, содержащих информацию о каждом студенте — три числа T1, T2, T3.
// Эти числа отделены одно от другого пробелом и удовлетворяют неравенствам
// 0 ≤ T1 ≤ T3 ≤ 600, 1 ≤ T2 ≤ 240. Все числа T1 попарно различны.
//
// Результат
// В единственной строке должно быть записано неотрицательное целое число,
// являющееся ответом на вопрос задачи. Если все студенты и так успевают по 
// своим делам, выведите число 0.
//
// Примеры
// исходные данные результат
// 3
// 100 10 120
// 70 40 150
// 99 15 400
// 15

#include <iostream>
#include <vector>
#include <algorithm>

struct timings
{
  timings() = default;
    
  timings(size_t prepare_time, size_t answer_time, size_t leave_time)
    : prepare_time{prepare_time}, answer_time{answer_time}, leave_time{leave_time} {}
    
  size_t prepare_time;
  size_t answer_time;
  size_t leave_time;
};

int main()
{
  size_t count;
  std::vector<timings> students_timings;

  std::ios::sync_with_stdio(false);
  
  // По условию список уже отсортирован и заранее известен его размер,
  // поэтому выбран std::vector и вызван метод reserve.
  std::cin >> count;
  students_timings.reserve(count);

  for(decltype(count) i{0}; i < count; ++i) {
    size_t prepare_time;
    size_t answer_time;
    size_t leave_time;
    std::cin >> prepare_time >> answer_time >> leave_time;
    students_timings.emplace_back(prepare_time, answer_time, leave_time);
  }
  
  std::sort(std::begin(students_timings),
            std::end(students_timings),
            [] (const auto& lhs, const auto& rhs)
            {
              return lhs.prepare_time < rhs.prepare_time;
            });
            
  size_t current_answer_time{0};
  size_t max_delay{0};
  std::for_each(std::begin(students_timings),
                std::end(students_timings),
                [&current_answer_time, &max_delay] (const auto& timing)
                {
                  current_answer_time = current_answer_time < timing.prepare_time
                                        ? timing.prepare_time + timing.answer_time
                                        : current_answer_time + timing.answer_time;
                  max_delay = current_answer_time < timing.leave_time
                              ? max_delay
                              : std::max(max_delay, current_answer_time - timing.leave_time);
                });
  std::cout << max_delay;
  return 0;
}