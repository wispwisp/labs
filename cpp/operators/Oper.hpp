#ifndef OPER_H
#define OPER_H

#include <iostream>
#include <typeinfo>

namespace Oper
{
  template<class T>
  class Oper {
  public:
    Oper(const T&);
    Oper(const Oper<T>&) = default;
    ~Oper();

    Oper<T>& operator= (const Oper<T>&);
    Oper<T>& operator+= (const Oper<T>&);
    Oper<T>& operator-= (const Oper<T>&);

    // operator+ is outside
    // operator- is outside

    bool operator== (const Oper<T>&);
    bool operator!= (const Oper<T>&);
    bool operator> (const Oper<T>&);
    bool operator< (const Oper<T>&);
    bool operator>= (const Oper<T>&);
    bool operator<= (const Oper<T>&);

    // index operators
    Oper<T>& operator++();
    const Oper<T> operator++ (int); // const prevent things like "i++++;"
    Oper<T>& operator--();
    const Oper<T> operator-- (int);

    // range operators
    const T& operator[] (int i) const = delete;
    T& operator[] (int i) = delete;

    // stream operators
    friend std::ostream& operator<< (std::ostream& os, const Oper<T>& rhs) {
      return os << "Oper[type:" << typeid(T).name() << "]: "<< rhs.m_elem ;
    }
    friend std::istream& operator>> (std::istream& is, const Oper<T>& rhs) {
      return is;
    }

  private:
    T m_elem;
  };

  // **********
  
  template<class T>
  Oper<T>::Oper(const T& a_elem)
    : m_elem(a_elem) {
    std::cout << "Created: " << m_elem << std::endl;
  }

  template<class T>
  Oper<T>::~Oper() {
    std::cout << "Destroyed: " << m_elem << std::endl;
  }

  // *** operators: ***

  // =
  template<class T>
  Oper<T>& Oper<T>::operator= (const Oper<T>& rhs) {
    if (this == &rhs)
      return *this;
    this->m_elem = rhs.m_elem;
    return *this;
  }

  // += , -=
  template<class T>
  Oper<T>& Oper<T>::operator+= (const Oper<T>& rhs) {
    this->m_elem += rhs.m_elem;
    return *this;
  }

  template<class T>
  Oper<T>& Oper<T>::operator-= (const Oper<T>& rhs) {
    this->m_elem += rhs.m_elem;
    return *this;
  }

  // == , !=
  template<class T>
  bool Oper<T>::operator== (const Oper<T>& rhs){
    return m_elem == rhs.m_elem;
  }

  template<class T>
  bool Oper<T>::operator!= (const Oper<T>& rhs) {
    return !(*this == rhs);
  }

  // >=, <=, <, >
  template<class T>
  bool Oper<T>::operator> (const Oper<T>& rhs) {
    return m_elem > rhs.m_elem;
  }

  template<class T>
  bool Oper<T>::operator< (const Oper<T>& rhs) {
    return m_elem < rhs.m_elem;
  }

  // inversive above
  template<class T>
  bool Oper<T>::operator>= (const Oper<T>& rhs) {
    return !(*this < rhs);
  }

  template<class T>
  bool Oper<T>::operator<= (const Oper<T>& rhs) {
    return !(*this > rhs);
  }

  // increments
  template<class T>
  Oper<T>& Oper<T>::operator++() {
    ++m_elem;
    return *this;
  }

  template<class T>
  const Oper<T> Oper<T>::operator++ (int) { // uses ++Oper<T> above
    Oper<T> oldVal = *this;
    ++(*this);
    return oldVal;
  }

  template<class T>
  Oper<T>& Oper<T>::operator--() {
    --m_elem;
    return *this;
  }

  template<class T>
  const Oper<T> Oper<T>::operator-- (int) { // uses --Oper<T> above
    Oper<T> oldVal = *this;
    --(*this);
    return oldVal;
  }

  // friends
  template<class T>
  Oper<T> operator+ (const Oper<T>& lhs, const Oper<T>& rhs) {
    Oper<T> result = lhs;
    return result += rhs;
  }
  
  template<class T>
  Oper<T> operator- (const Oper<T>& lhs, const Oper<T>& rhs) {
    Oper<T> result = lhs;
    return result -= rhs;
  }
}

#endif // OPER_H
