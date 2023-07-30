#include "container.hpp"

sv::Status::Status()
    : mode{sv::StatusMode::None} {}
sv::Status::Status(std::size_t idx1, std::size_t idx2, bool comp)
    : mode{comp ? sv::StatusMode::Compare : sv::StatusMode::Swap}, idx1{idx1}, idx2{idx2} {}
sv::Status::Status(std::size_t idx, int value)
    : mode{sv::StatusMode::Set}, idx{idx}, value{value} {}

constexpr static std::size_t initialSize{512};

sv::Container::Container()
    : mBase(initialSize), mDisplay(initialSize)
{
  for (std::size_t i{0}; i < initialSize; ++i)
  {
    mBase[i] = i;
    mDisplay[i] = i;
  }
}

const std::vector<int> &sv::Container::base() const
{
  return mBase;
}

const std::vector<int> &sv::Container::display() const
{
  return mDisplay;
}

const sv::Status sv::Container::peekStatus() const
{
  if (mStatusQ.empty())
  {
    return sv::Status{};
  }
  return mStatusQ.front();
}

const sv::Status sv::Container::popStatus()
{
  Status status{peekStatus()};
  if (status.mode != sv::StatusMode::None)
  {
    mStatusQ.pop();
    switch (status.mode)
    {
    case sv::StatusMode::Swap:
      std::swap(mDisplay[status.idx1], mDisplay[status.idx2]);
      break;
    case sv::StatusMode::Set:
      mDisplay[status.idx] = status.value;
      break;
    }
  }
  return status;
}

void sv::Container::resize(std::size_t size)
{
  mBase.resize(size);
  mDisplay.resize(size);
  reset();
}

void sv::Container::reset()
{
  for (std::size_t i{0}; i < mBase.size(); ++i)
  {
    mBase[i] = i;
    mDisplay[i] = i;
  }
  while (!mStatusQ.empty())
  {
    mStatusQ.pop();
  }
}

int sv::Container::compare(std::size_t idx1, std::size_t idx2)
{
  mStatusQ.push(sv::Status{idx1, idx2});
  if (mBase[idx1] < mBase[idx2])
  {
    return -1;
  }
  else if (mBase[idx1] > mBase[idx2])
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void sv::Container::swap(std::size_t idx1, std::size_t idx2)
{
  mStatusQ.push(sv::Status{idx1, idx2, false});
  std::swap(mBase[idx1], mBase[idx2]);
}

void sv::Container::set(std::size_t idx, int value)
{
  mStatusQ.push(sv::Status{idx, value});
  mBase[idx] = value;
}