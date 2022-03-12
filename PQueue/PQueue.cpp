#include <iostream>
#include <vector>

#define QUEUE_ERROR -999999

class Container {
public:
  virtual unsigned int Count() const = 0;
  virtual bool IsEmpty() const { return Count() == 0; };
  virtual bool IsFull() const = 0;
  virtual void MakeNull() = 0;

protected:
  Container(){};
};

template <typename T> class PriorityQueue : public Container {
public:
  virtual void Enqueue(T element) = 0;
  virtual T FindMin() const = 0;
  virtual T DequeueMin() = 0;
};

template <typename T> class BinaryHeap : public PriorityQueue<T> {

public:
  BinaryHeap(unsigned int n);
  BinaryHeap();
  ~BinaryHeap(){};

  void MakeNull();
  void Enqueue(T element);
  T FindMin() const;
  T DequeueMin();
  bool IsEmpty() const;
  bool IsFull() const;
  unsigned int Count() const { return count; }

  void Show() const;
  void ShowEmpty() const;
  void ShowMin() const;

protected:
  int count;
  std::vector<T> elements;
};

template <typename T>
BinaryHeap<T>::BinaryHeap(unsigned int n) : count(0), elements(n){};
template <typename T> BinaryHeap<T>::BinaryHeap() : count(0), elements(10){};

template <typename T> bool BinaryHeap<T>::IsEmpty() const {
  return (count == 0);
}

template <typename T> bool BinaryHeap<T>::IsFull() const { return false; }
template <typename T> void BinaryHeap<T>::MakeNull() { count = 0; }

template <typename T> T BinaryHeap<T>::FindMin() const {
  if (count > 0)
    return elements[0];
  else
    return QUEUE_ERROR;
}

template <typename T> void BinaryHeap<T>::Enqueue(T element) {
  if (count >= elements.size())
    elements.resize(count + 1);
  count++;
  int i = count - 1;
  while ((i > 0) && (elements[(i - 1) / 2] > element)) {
    elements[i] = elements[(i - 1) / 2];
    i = (i - 1) / 2;
  }
  elements[i] = element;
}

template <typename T> T BinaryHeap<T>::DequeueMin() {
  if (count > 0) {
    T result = elements[0];
    T last = elements[count - 1];
    count--;
    int i = 0;
    while (2 * i + 1 < count) {
      int child_node = 2 * i + 1;
      if ((child_node + 1 < count) &&
          (elements[child_node + 1] < elements[child_node]))
        child_node = child_node + 1;
      if (last <= elements[child_node])
        break;
      elements[i] = elements[child_node];
      i = child_node;
    }
    elements[i] = last;
    return result;
  } else {
    return QUEUE_ERROR;
  }
}

template <typename T> void BinaryHeap<T>::Show() const {
  std::cout << "-- Elements Top -- " << std::endl;
  for (int j = 0; j < count; j++)
    std::cout << "Element: " << elements[j] << std::endl;
  std::cout << "-- Elements Bot -- " << std::endl;
}

template <typename T> void BinaryHeap<T>::ShowMin() const {
  try {
    std::cout << "Min: " << this->FindMin() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
}

template <typename T> void BinaryHeap<T>::ShowEmpty() const {
  try {
    std::cout << "IsEmpty: " << std::boolalpha << this->IsEmpty() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
}

void test(int size) {
  BinaryHeap<int> PrioQ(size);
  PrioQ.ShowEmpty();
  PrioQ.Enqueue(5);
  PrioQ.ShowEmpty();
  PrioQ.Show();
  PrioQ.ShowMin();
  PrioQ.Enqueue(6);
  PrioQ.Show();
  PrioQ.ShowMin();
  PrioQ.Enqueue(8);
  PrioQ.Show();
  PrioQ.ShowMin();
  PrioQ.Enqueue(3);
  PrioQ.Show();
  PrioQ.ShowMin();
  PrioQ.Enqueue(9);
  PrioQ.Show();
  PrioQ.ShowMin();
  PrioQ.Enqueue(2);
  PrioQ.Show();
  PrioQ.ShowMin();
  PrioQ.Enqueue(1);
  PrioQ.Show();
  PrioQ.ShowMin();
  PrioQ.DequeueMin();
  PrioQ.Show();
  PrioQ.ShowMin();
  PrioQ.DequeueMin();
  PrioQ.Show();
  PrioQ.ShowMin();
  PrioQ.MakeNull();
  PrioQ.ShowEmpty();
}

int main() {
  std::cout << "========== Wywolanie testu ==========" << std::endl;
  test(10);
  std::cout << "========== Wywolanie testu ==========" << std::endl;
  test(2);
  return 0;
}