#include <iostream>
#include <vector>
using namespace std;

class Container {
protected:
  Container(){};

public:
  virtual unsigned int Count() const = 0;
  virtual bool IsEmpty() const { return Count() == 0; };
  virtual bool IsFull() const = 0;
  virtual void MakeNull() = 0;
};

template <typename T> class PriorityQueue : public Container {
public:
  virtual void Enqueue(T element) = 0;
  virtual T FindMin() const = 0;
  virtual T DequeueMin() = 0;
};

template <typename T> class BinaryHeap : public PriorityQueue<T> {
protected:
  int count;
  std::vector<T> data;

public:
  BinaryHeap(unsigned int n);
  BinaryHeap();
  ~BinaryHeap() { ; };
  void MakeNull();
  void Enqueue(T element);
  T FindMin() const;
  T DequeueMin();
  bool IsEmpty() const;
  bool IsFull() const;
  void Wypisz() const;
  unsigned int Count() const { return count; }
};

template <typename T>
BinaryHeap<T>::BinaryHeap(unsigned int n) : count(0), data(n){};
template <typename T> BinaryHeap<T>::BinaryHeap() : count(0), data(10){};

template <typename T> bool BinaryHeap<T>::IsEmpty() const {
  return (count == 0);
}

template <typename T> bool BinaryHeap<T>::IsFull() const { return false; }
template <typename T> void BinaryHeap<T>::MakeNull() { count = 0; }

template <typename T> T BinaryHeap<T>::FindMin() const {
  if (count > 0)
    return data[0];
}

template <typename T> void BinaryHeap<T>::Enqueue(T element) {
  if (count >= data.size())
    data.resize(count + 1);
  ++count;
  int i = count - 1;
  while ((i > 0) && (data[(i - 1) / 2] > element)) {
    data[i] = data[(i - 1) / 2];
    i = (i - 1) / 2;
  }
  data[i] = element;
}

template <typename T> T BinaryHeap<T>::DequeueMin() {
  if (count > 0) {
    T result = data[0];
    T last = data[count - 1];
    --count;
    int i = 0;
    while (2 * i + 1 < count) {
      int child = 2 * i + 1;
      if ((child + 1 < count) && (data[child + 1] < data[child]))
        child = child + 1;
      if (last <= data[child])
        break;
      data[i] = data[child];
      i = child;
    }
    data[i] = last;
    return result;
  }
}

template <typename T> void BinaryHeap<T>::Wypisz() const {
  int i = count;
  for (int k = 0; k < i; k++)
    std::cout << "data=" << data[k] << endl;
}

int main(int argc, char **argv) {
  BinaryHeap<int> K(2);
  std::cout << "Pusta:" << K.IsEmpty() << endl;
  K.Enqueue(23);
  K.Wypisz();
  std::cout << "Pusta:" << K.IsEmpty() << endl;
  std::cout << "Min:" << K.FindMin() << endl;
  K.Enqueue(25);
  K.Wypisz();
  std::cout << "Min:" << K.FindMin() << endl;
  K.Enqueue(20);
  K.Wypisz();
  std::cout << "Min:" << K.FindMin() << endl;
  K.Enqueue(8);
  K.Wypisz();
  std::cout << "Min:" << K.FindMin() << endl;
  K.DequeueMin();
  K.Wypisz();
  std::cout << "Min:" << K.FindMin() << endl;
  K.MakeNull();
  std::cout << "Pusta:" << K.IsEmpty() << endl;
  return 0;
}