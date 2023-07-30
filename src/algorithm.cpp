#include "algorithm.hpp"
#include <cstdlib>
#include <ctime>

void sv::randomize(sv::Container &c)
{
  std::size_t size{c.base().size()};

  std::srand(std::time(NULL));

  for (std::size_t i{0}; i < size - 1; ++i)
  {
    std::size_t j{std::rand() % (size - i) + i};
    c.swap(i, j);
  }
}

void sv::bubble_sort(sv::Container &c)
{
  std::size_t size{c.base().size()};
  bool swapped;
  for (std::size_t i{0}; i < size - 1; ++i)
  {
    swapped = false;
    for (std::size_t j{0}; j < size - i - 1; ++j)
    {
      if (c.compare(j, j + 1) > 0)
      {
        c.swap(j, j + 1);
        swapped = true;
      }
    }
    if (!swapped)
    {
      break;
    }
  }
}

void sv::comb_sort(sv::Container &c)
{
  std::size_t size{c.base().size()};
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
      if (c.compare(i, i + j) > 0)
      {
        c.swap(i, i + j);
        swapped = true;
      }
    }
  }
}

void sv::insertion_sort(sv::Container &c)
{
  std::size_t size{c.base().size()};
  for (std::size_t i{1}; i < size; ++i)
  {
    for (std::size_t j{i}; j > 0 && c.compare(j - 1, j) > 0; --j)
    {
      c.swap(j - 1, j);
    }
  }
}

void sv::shell_sort(sv::Container &c)
{
  std::size_t size{c.base().size()};
  for (std::size_t k{size / 2}; k > 0; k /= 2)
  {
    for (std::size_t i{k}; i < size; ++i)
    {
      for (std::size_t j{i}; j >= k && c.compare(j - k, j) > 0; j -= k)
      {
        c.swap(j - k, j);
      }
    }
  }
}

void sv::selection_sort(sv::Container &c)
{
  std::size_t size{c.base().size()};
  std::size_t i, j, k;
  for (std::size_t i{0}; i < size - 1; ++i)
  {
    k = i;
    for (j = i + 1; j < size; ++j)
    {
      if (c.compare(j, k) < 0)
      {
        k = j;
      }
    }
    if (i != k)
    {
      c.swap(i, k);
    }
  }
}

static void heapify(sv::Container &c, std::size_t size, std::size_t root)
{
  std::size_t i = root;
  std::size_t l = i * 2 + 1;
  std::size_t r = i * 2 + 2;

  if (l < size && c.compare(i, l) < 0)
  {
    i = l;
  }
  if (r < size && c.compare(i, r) < 0)
  {
    i = r;
  }
  if (i != root)
  {
    c.swap(i, root);
    heapify(c, size, i);
  }
}

void sv::heap_sort(sv::Container &c)
{
  std::size_t size{c.base().size()};
  for (std::size_t i{size / 2 - 1}; i > 0; --i)
  {
    heapify(c, size, i);
  }
  heapify(c, size, 0);

  for (std::size_t i{size - 1}; i > 0; --i)
  {
    c.swap(0, i);
    heapify(c, i, 0);
  }
}

static void merge(sv::Container &c, std::size_t l, std::size_t m, std::size_t r)
{
  std::vector<int> aux(r - l + 1);

  std::size_t i{l};
  std::size_t j{m + 1};
  std::size_t k{0};
  while (i <= m && j <= r)
  {
    if (c.compare(i, j) <= 0)
    {
      aux[k] = c.base()[i];
      ++i;
    }
    else
    {
      aux[k] = c.base()[j];
      ++j;
    }
    ++k;
  }

  while (i <= m)
  {
    aux[k] = c.base()[i];
    ++k;
    ++i;
  }
  while (j <= r)
  {
    aux[k] = c.base()[j];
    ++k;
    ++j;
  }

  for (i = l; i <= r; ++i)
  {
    c.set(i, aux[i - l]);
  }
}

static void mergeRec(sv::Container &c, std::size_t l, std::size_t r)
{
  if (l < r)
  {
    std::size_t m{l + (r - l) / 2};

    mergeRec(c, l, m);
    mergeRec(c, m + 1, r);
    merge(c, l, m, r);
  }
}

void sv::merge_sort(sv::Container &c)
{
  std::size_t size{c.base().size()};
  mergeRec(c, 0, size - 1);
}

static std::size_t partition(sv::Container &c, std::size_t l, std::size_t r)
{
  c.swap(l + (r - l) / 2, r);
  std::size_t p{r};

  std::size_t i{l};
  for (std::size_t j{l}; j < r; ++j)
  {
    if (c.compare(j, p) < 0)
    {
      c.swap(i, j);
      ++i;
    }
  }
  c.swap(i, p);
  return i;
}

static void quickRec(sv::Container &c, std::size_t l, std::size_t r)
{
  if (l < r)
  {
    std::size_t p{partition(c, l, r)};

    if (p > 0)
    {
      quickRec(c, l, p - 1);
    }
    if (p < r)
    {
      quickRec(c, p + 1, r);
    }
  }
}

void sv::quick_sort(sv::Container &c)
{
  std::size_t size{c.base().size()};
  quickRec(c, 0, size - 1);
}

static void stooge(sv::Container &c, std::size_t l, std::size_t r)
{
  if (c.compare(l, r) > 0)
  {
    c.swap(l, r);
  }
  if (r - l + 1 > 2)
  {
    std::size_t t{(r - l + 1) / 3};
    stooge(c, l, r - t);
    stooge(c, l + t, r);
    stooge(c, l, r - t);
  }
}

void sv::stooge_sort(sv::Container &c)
{
  std::size_t size{c.base().size()};
  stooge(c, 0, size - 1);
}