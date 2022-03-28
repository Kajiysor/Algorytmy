#include <iostream>
#include <vector>

template <typename T> class Iterator {
public:
  Iterator(){};
  virtual ~Iterator(){};
  virtual bool isDone() const = 0;
  const virtual T &operator*() = 0;
  virtual void operator++() = 0;
};
template <typename T> class Visitor {
public:
  virtual void Visit(T &element){};
  virtual bool IsDone() const { return false; }
};

class PrintVisitor : public Visitor<int> {
public:
  void Visit(int &element) { std::cout << element << std::endl; }
};

class AddingVisitor : public Visitor<int> {
public:
  int Result(bool reset = true) {
    int tmp = sum;
    if (reset)
      sum = 0;
    return tmp;
  }
  void Visit(int &element) { sum += element; }

private:
  int sum{0};
};

template <typename T> class Container {
public:
  virtual unsigned int Count() const = 0;
  virtual bool IsEmpty() const { return Count() == 0; }
  virtual bool IsFull() const = 0;
  virtual void MakeNull() = 0;
  virtual void Accept(Visitor<T> &) const = 0;

protected:
  Container(){};
};

template <typename T> class Set : public virtual Container<T> {
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
  class Iter : public Iterator<int> {
    std::vector<bool> data;
    int universeSize;
    int index;

  public:
    ~Iter(){};
    Iter(std::vector<bool> array, int us) {
      data.assign(array.begin(), array.end());
      universeSize = us;
      for (auto i = 0; i < universeSize; i++) {
        if (data[i] == true) {
          index = i;
          break;
        }
      }
    }

    const int &operator*() { return index; }

    void operator++() {
      for (auto i = index; i < universeSize; i++) {
        if (data[i] == true) {
          index = i;
          break;
        }
      }
    }
    bool isDone() const {
      if (index >= universeSize)
        return true;
      else
        return false;
    }
  };

public:
  SetAsArray(unsigned int n) : Set(n), array(n, false) {}
  bool IsFull() const { return Count() == UniverseSize(); }
  void MakeNull() {
    std::fill(array.begin(), array.end(), false);
    count = 0;
  }
  bool IsMember(int element) const { return array[element]; }
  void Insert(int element) {
    if (!IsMember(element)) {
      array[element] = true;
      count++;
    }
  }
  void Withdraw(int element) {
    if (IsMember(element)) {
      array[element] = false;
      count--;
    }
  }
  void Show() {
    int last;
    for (last = UniverseSize() - 1; !array[last]; last--)
      ;
    std::cout << "SetAsArray: {";
    for (int i = 0; i < UniverseSize(); i++) {
      if (array[i])
        std::cout << i;
      if (i != last && array[i])
        std::cout << ", ";
    }
    std::cout << "}" << std::endl;
  }
  static bool same_universe(SetAsArray const &A, SetAsArray const &B) {
    return A.UniverseSize() == B.UniverseSize();
  }
  friend SetAsArray operator+(SetAsArray const &A, SetAsArray const &B) {
    if (!same_universe(A, B))
      throw std::out_of_range("Wrong universe!");
    SetAsArray to_return(A.UniverseSize());
    for (int i = 0; i < to_return.universeSize; i++) {
      if (A.IsMember(i) || B.IsMember(i))
        to_return.Insert(i);
    }
    return to_return;
  }
  friend SetAsArray operator-(SetAsArray const &A, SetAsArray const &B) {
    if (!same_universe(A, B))
      throw std::out_of_range("Wrong universe!");
    SetAsArray to_return(A.UniverseSize());
    for (int i = 0; i < to_return.universeSize; i++) {
      if (A.IsMember(i) && !B.IsMember(i))
        to_return.Insert(i);
    }
    return to_return;
  }
  friend SetAsArray operator*(SetAsArray const &A, SetAsArray const &B) {
    if (!same_universe(A, B))
      throw std::out_of_range("Wrong universe!");
    SetAsArray to_return(A.UniverseSize());
    for (int i = 0; i < to_return.universeSize; i++) {
      if (A.IsMember(i) && B.IsMember(i))
        to_return.Insert(i);
    }
    return to_return;
  }
  friend bool operator==(SetAsArray const &A, SetAsArray const &B) {
    if (!same_universe(A, B))
      throw std::out_of_range("Wrong universe!");
    for (int i = 0; i < A.UniverseSize(); i++) {
      if ((A.IsMember(i) ^ B.IsMember(i)))
        return false;
    }
    return true;
  }
  friend bool operator<=(SetAsArray const &A, SetAsArray const &B) {
    if (!same_universe(A, B))
      throw std::out_of_range("Wrong universe!");
    for (int i = 0; i < A.UniverseSize(); i++) {
      if (A.IsMember(i) && !B.IsMember(i))
        return false;
    }
    return true;
  }
  friend std::ostream &operator<<(std::ostream &ost, SetAsArray const &A) {
    int last;
    for (last = A.UniverseSize() - 1; last >= 0 && !A.array[last]; last--)
      ;
    ost << "{";
    if (last == -1) {
      ost << "}";
      return ost;
    }
    for (int i = 0; i < A.UniverseSize(); i++) {
      if (A.array[i])
        ost << i;
      if (i != last && A.array[i])
        ost << ", ";
    }
    ost << "}";
    return ost;
  }

  void Accept(Visitor<int> &v) const {
    for (int i = 0; i < universeSize; i++) {
      if (array[i])
        v.Visit(i);
    }
  }

  Iter &NewIterator() { return *new Iter(array, universeSize); }

  void ShowViaIter() {
    auto testIter = NewIterator();
    while (!testIter.isDone()) {
      std::cout << *testIter << std::endl;
      ++testIter;
    }
  }

private:
  std::vector<bool> array;
};

void Test() {
  std::cout << "==== Running Test ====\n";
  SetAsArray A(10), B(10), C(10), D(10), E(10);

  // Do A wstaw parzyste, do B wstaw nieparzyste
  for (int i = 0; i < 10; i++)
    !(i % 2) ? A.Insert(i) : B.Insert(i);

  A.ShowViaIter();
  // SetAsArray Test
  C = A + B;
  D = C - B;
  std::cout << "A = ";
  A.Show();
  std::cout << "Ilosc elementow w A: " << A.Count() << std::endl;
  std::cout << "B = ";
  B.Show();
  std::cout << "Ilosc elementow w B: " << B.Count() << std::endl;
  std::cout << "C = ";
  C.Show();
  std::cout << "Ilosc elementow w C: " << C.Count() << std::endl;
  std::cout << "D = ";
  D.Show();
  std::cout << "Ilosc elementow w D: " << D.Count() << std::endl;

  std::cout << std::endl << std::boolalpha;
  std::cout << "D == A: " << (D == A) << std::endl;
  std::cout << "D <= A: " << (D <= A) << std::endl;
  std::cout << "C == B: " << (C == B) << std::endl;
  std::cout << "B <= C: " << (B <= C) << std::endl;
  A.Insert(1);
  std::cout << "D == A: " << (D == A) << std::endl;
  std::cout << "D <= A: " << (D <= A) << std::endl;

  // Visitor Test
  std::cout << std::endl;
  A.Insert(5);
  AddingVisitor addingVisitor;
  A.Accept(addingVisitor);
  E = A * B;
  std::cout << "A Sum = " << addingVisitor.Result() << std::endl;
  E.Accept(addingVisitor);
  std::cout << "E Sum = " << addingVisitor.Result() << std::endl;
  E.Withdraw(1);
  E.Accept(addingVisitor);
  std::cout << "E Sum = " << addingVisitor.Result() << std::endl;
  std::cout << "==== Test Finished ====" << std::endl;
}

int main(int argc, char const *argv[]) {
  Test();
  return 0;
}
