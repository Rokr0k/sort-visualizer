#include "algorithm.hpp"
#include <cstdlib>
#include <ctime>

static int compare(std::vector<int> &b, std::queue<sv::Status> &q, std::size_t idx1, std::size_t idx2)
{
  sv::Status status{idx1, idx2, sv::StatusMode::COMPARE};
  q.push(status);
  if (b[idx1] < b[idx2])
  {
    return -1;
  }
  else if (b[idx1] > b[idx2])
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

static void swap(std::vector<int> &b, std::queue<sv::Status> &q, std::size_t idx1, std::size_t idx2)
{
  sv::Status status{idx1, idx2, sv::StatusMode::SWAP};
  q.push(status);
  std::swap(b[idx1], b[idx2]);
}

static void set(std::vector<int> &b, std::queue<sv::Status> &q, std::size_t idx, int value)
{
  sv::Status status{idx, static_cast<std::size_t>(value), sv::StatusMode::SET};
  q.push(status);
  b[idx] = value;
}

void sv::randomize(std::vector<int> &b, std::queue<sv::Status> &q)
{
  std::size_t size{b.size()};

  std::srand(std::time(NULL));

  for (std::size_t i{0}; i < size - 1; ++i)
  {
    std::size_t j{std::rand() % (size - i) + i};
    swap(b, q, i, j);
  }
}

void sv::bubble_sort(std::vector<int> &b, std::queue<sv::Status> &q)
{
  std::size_t size{b.size()};
  bool swapped;
  for (std::size_t i{0}; i < size - 1; ++i)
  {
    swapped = false;
    for (std::size_t j{0}; j < size - i - 1; ++j)
    {
      if (compare(b, q, j, j + 1) > 0)
      {
        swap(b, q, j, j + 1);
        swapped = true;
      }
    }
    if (!swapped)
    {
      break;
    }
  }
}

void sv::comb_sort(std::vector<int> &b, std::queue<sv::Status> &q)
{
  std::size_t size{b.size()};
  std::size_t j{size};
  bool swapped;
  while (j != 1 || swapped)
  {
    j = (j * 10) / 13;
    if (j < 1)
    {
      j = 1;
    }
    swapped = false;
    for (std::size_t i{0}; i < size - j; ++i)
    {
      if (compare(b, q, i, i + j) > 0)
      {
        swap(b, q, i, i + j);
        swapped = true;
      }
    }
  }
}

void sv::insertion_sort(std::vector<int> &b, std::queue<sv::Status> &q)
{
  std::size_t size{b.size()};
  for (std::size_t i{1}; i < size; ++i)
  {
    for (std::size_t j{i}; j > 0 && compare(b, q, j - 1, j) > 0; --j)
    {
      swap(b, q, j - 1, j);
    }
  }
}

void sv::shell_sort(std::vector<int> &b, std::queue<sv::Status> &q)
{
  std::size_t size{b.size()};
  for (std::size_t k{size / 2}; k > 0; k /= 2)
  {
    for (std::size_t i{k}; i < size; ++i)
    {
      for (std::size_t j{i}; j >= k && compare(b, q, j - k, j) > 0; j -= k)
      {
        swap(b, q, j - k, j);
      }
    }
  }
}

void sv::selection_sort(std::vector<int> &b, std::queue<sv::Status> &q)
{
  std::size_t size{b.size()};
  std::size_t i, j, k;
  for (std::size_t i{0}; i < size - 1; ++i)
  {
    k = i;
    for (j = i + 1; j < size; ++j)
    {
      if (compare(b, q, j, k) < 0)
      {
        k = j;
      }
    }
    if (i != k)
    {
      swap(b, q, i, k);
    }
  }
}

static void heapify(std::vector<int> &b, std::queue<sv::Status> &q, std::size_t size, std::size_t root)
{
  std::size_t i = root;
  std::size_t l = i * 2 + 1;
  std::size_t r = i * 2 + 2;

  if (l < size && compare(b, q, i, l) < 0)
  {
    i = l;
  }
  if (r < size && compare(b, q, i, r) < 0)
  {
    i = r;
  }
  if (i != root)
  {
    swap(b, q, i, root);
    heapify(b, q, size, i);
  }
}

void sv::heap_sort(std::vector<int> &b, std::queue<sv::Status> &q)
{
  std::size_t size{b.size()};
  for (std::size_t i{size / 2 - 1}; i > 0; --i)
  {
    heapify(b, q, size, i);
  }
  heapify(b, q, size, 0);

  for (std::size_t i{size - 1}; i > 0; --i)
  {
    swap(b, q, 0, i);
    heapify(b, q, i, 0);
  }
}

static void merge(std::vector<int> &b, std::queue<sv::Status> &q, std::size_t l, std::size_t m, std::size_t r)
{
  std::vector<int> aux(r - l + 1);

  std::size_t i{l};
  std::size_t j{m + 1};
  std::size_t k{0};
  while (i <= m && j <= r)
  {
    if (compare(b, q, i, j) <= 0)
    {
      aux[k] = b[i];
      ++i;
    }
    else
    {
      aux[k] = b[j];
      ++j;
    }
    ++k;
  }

  while (i <= m)
  {
    aux[k] = b[i];
    ++k;
    ++i;
  }
  while (j <= r)
  {
    aux[k] = b[j];
    ++k;
    ++j;
  }

  for (i = l; i <= r; ++i)
  {
    set(b, q, i, aux[i - l]);
  }
}

static void mergeRec(std::vector<int> &b, std::queue<sv::Status> &q, std::size_t l, std::size_t r)
{
  if (l < r)
  {
    std::size_t m{l + (r - l) / 2};

    mergeRec(b, q, l, m);
    mergeRec(b, q, m + 1, r);
    merge(b, q, l, m, r);
  }
}

void sv::merge_sort(std::vector<int> &b, std::queue<sv::Status> &q)
{
  std::size_t size{b.size()};
  mergeRec(b, q, 0, size - 1);
}

static std::size_t partition(std::vector<int> &b, std::queue<sv::Status> &q, std::size_t l, std::size_t r)
{
  swap(b, q, l + (r - l) / 2, r);
  std::size_t p{r};

  std::size_t i{l};
  for (std::size_t j{l}; j < r; ++j)
  {
    if (compare(b, q, j, p) < 0)
    {
      swap(b, q, i, j);
      ++i;
    }
  }
  swap(b, q, i, p);
  return i;
}

static void quickRec(std::vector<int> &b, std::queue<sv::Status> &q, std::size_t l, std::size_t r)
{
  if (l < r)
  {
    std::size_t p{partition(b, q, l, r)};

    if (p > 0)
    {
      quickRec(b, q, l, p - 1);
    }
    if (p < r)
    {
      quickRec(b, q, p + 1, r);
    }
  }
}

void sv::quick_sort(std::vector<int> &b, std::queue<sv::Status> &q)
{
  std::size_t size{b.size()};
  quickRec(b, q, 0, size - 1);
}

static void stooge(std::vector<int> &b, std::queue<sv::Status> &q, std::size_t l, std::size_t r)
{
  if (compare(b, q, l, r) > 0)
  {
    swap(b, q, l, r);
  }
  if (r - l + 1 > 2)
  {
    std::size_t t{(r - l + 1) / 3};
    stooge(b, q, l, r - t);
    stooge(b, q, l + t, r);
    stooge(b, q, l, r - t);
  }
}

void sv::stooge_sort(std::vector<int> &b, std::queue<sv::Status> &q)
{
  std::size_t size{b.size()};
  stooge(b, q, 0, size - 1);
}