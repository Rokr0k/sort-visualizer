#ifndef SV_CONTAINER_HPP
#define SV_CONTAINER_HPP

#include <vector>
#include <queue>

namespace sv
{
  enum class StatusMode
  {
    None,
    Compare,
    Swap,
    Set,
  };

  typedef struct Status
  {
    StatusMode mode;
    union
    {
      struct
      {
        std::size_t idx1, idx2;
      };
      struct
      {
        std::size_t idx;
        int value;
      };
    };

    Status();
    Status(std::size_t idx1, std::size_t idx2, bool comp = true);
    Status(std::size_t idx, int value);
  } Status;

  struct Container
  {
    Container();

    const std::vector<int> &base() const;
    const std::vector<int> &display() const;
    const Status peekStatus() const;
    const Status popStatus();

    void resize(std::size_t size);
    void reset();

    int compare(std::size_t idx1, std::size_t idx2);
    void swap(std::size_t idx1, std::size_t idx2);
    void set(std::size_t idx, int value);

  private:
    std::vector<int> mBase;
    std::vector<int> mDisplay;
    std::queue<Status> mStatusQ;
  };
}

#endif