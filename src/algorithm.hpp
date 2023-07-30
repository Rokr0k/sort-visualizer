#ifndef SV_ALGORITHM_HPP
#define SV_ALGORITHM_HPP

#include <queue>
#include <vector>

namespace sv
{
  enum class StatusMode
  {
    NONE,
    COMPARE,
    SWAP,
    SET,
  };

  typedef struct Status
  {
    std::size_t idx1, idx2;
    StatusMode mode;
  } Status;

  void randomize(std::vector<int> &b, std::queue<Status> &q);
  void bubble_sort(std::vector<int> &b, std::queue<Status> &q);
  void comb_sort(std::vector<int> &b, std::queue<Status> &q);
  void insertion_sort(std::vector<int> &b, std::queue<Status> &q);
  void shell_sort(std::vector<int> &b, std::queue<Status> &q);
  void selection_sort(std::vector<int> &b, std::queue<Status> &q);

  void heap_sort(std::vector<int> &b, std::queue<Status> &q);
  void merge_sort(std::vector<int> &b, std::queue<Status> &q);
  void quick_sort(std::vector<int> &b, std::queue<Status> &q);
  void stooge_sort(std::vector<int> &b, std::queue<Status> &q);
}

#endif