#include <iostream>
#include <vector>

class Container {
protected:
  Container(){};

public:
  virtual unsigned int Count() const = 0;
  virtual bool IsEmpty() const { return Count() == 0; }
  virtual bool IsFull() const = 0;
  virtual void MakeNull() = 0;
};

template <typename T> class Set : public virtual Container {

public:
  Set(unsigned int n) : count{0}, universeSize(n) {}
  int UniverseSize() const { return universeSize; }
  unsigned int Count() const { return count; }
  virtual void Insert(T element) = 0;
  virtual bool IsMember(T element) const = 0;
  virtual void Withdraw(T element) = 0;

protected:
  int count;
  int universeSize;
};

class SetAsArray : public Set<int> {
public:
  SetAsArray(unsigned int n) : Set(n), array(n, false) {}
  bool IsFull() const { return (Count() == UniverseSize()); }
  bool IsMember(int element) const { return array[element]; }

  void MakeNull() {
    for (int i = 0; i < universeSize; i++)
      array[i] = false;
    count = 0;
  }
  void Insert(int element);
  void Withdraw(int element);

private:
  std::vector<bool> array;
};