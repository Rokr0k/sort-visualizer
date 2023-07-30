#ifndef SV_ALGORITHM_HPP
#define SV_ALGORITHM_HPP

#include "container.hpp"

namespace sv
{
  void randomize(Container &c);
  void bubble_sort(Container &c);
  void comb_sort(Container &c);
  void insertion_sort(Container &c);
  void shell_sort(Container &c);
  void selection_sort(Container &c);

  void heap_sort(Container &c);
  void merge_sort(Container &c);
  void quick_sort(Container &c);
  void stooge_sort(Container &c);
}

#endif