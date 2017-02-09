/*
 * SimpleError.hh
 *
 *  Created on: Sep 10, 2015
 *      Author: hqu
 */

#ifndef ESTTOOLS_QUANTITY_H_
#define ESTTOOLS_QUANTITY_H_

#include <iostream>
#include <cmath>
#include <cassert>

namespace EstTools{

class Quantity {

  // Class to handle simple uncorrelated error propagation.

public:

  enum Styles {PLAIN, LATEX, ROOT};
  static Styles printStyle;

  Quantity(double v = 0) : value(v), error(0) {}
  Quantity(double value, double error) : value(value), error(error) {}
  Quantity(const Quantity &q) : Quantity(q.value, q.error) {}

  virtual ~Quantity() {}

  friend Quantity operator+(const Quantity &a, const Quantity &b){
    double val = a.value + b.value;
    double err = std::sqrt(a.error*a.error + b.error*b.error);
    return Quantity(val, err);
  }

  friend Quantity operator-(const Quantity &a, const Quantity &b){
    double val = a.value - b.value;
    double err = std::sqrt(a.error*a.error + b.error*b.error);
    return Quantity(val, err);
  }

  friend Quantity operator*(const Quantity &a, const Quantity &b){
    double val = a.value * b.value;
    double err = std::sqrt(b.value*b.value * a.error*a.error + a.value*a.value * b.error*b.error);
    return Quantity(val, err);
  }

  friend Quantity operator*(const Quantity &a, double b){
    double val = a.value * b;
    double err = a.error * b;
    return Quantity(val, err);
  }

  friend Quantity operator*(double b, const Quantity &a){
    return a * b;
  }

  friend Quantity operator/(const Quantity &a, const Quantity &b){
    double val = a.value / b.value;
    double err = std::sqrt(a.error*a.error / (b.value*b.value) + a.value*a.value/(b.value*b.value*b.value*b.value) * b.error*b.error);
    return Quantity(val, err);
  }

  friend Quantity operator/(const Quantity &a, double b){
      double val = a.value / b;
      double err = a.error / b;
      return Quantity(val, err);
    }

  Quantity power(double exp){
    double val = std::pow(value, exp);
    double err = exp*val/value * error;
    return Quantity(val, err);
  }

  friend std::ostream &operator<<(std::ostream &os, const Quantity &q){
    std::string pm;
    switch(printStyle){
    case PLAIN:
      pm = "+/-";
      break;
    case LATEX:
      pm = R"($\pm$)";
      break;
    case ROOT:
      pm = "#pm";
      break;
    default:
      pm = "+/-";
      break;
    }
    os << q.value << pm << q.error;
    return os;
  }

  static Quantity sum(const std::vector<Quantity> vec){
    Quantity sum(0,0);
    for (auto &q : vec) sum = sum + q;
    return sum;
  }

  static void removeNegatives(std::vector<Quantity> &vec){
    for (auto &q : vec){
      if (q.value < 0){
        q.error += std::abs(q.value);
        q.value = 0;
      }
    }
  }

  static void removeZeroes(std::vector<Quantity> &vec, double setVal = 1, double setUnc = 0.8){
    for (auto &q : vec){
      if (q.value == 0){
        q.value = setVal;
        q.error = setUnc;
      }
    }
  }

  static std::vector<Quantity> normalize(const std::vector<Quantity> vec, double norm = 1.){
    auto scale = norm / sum(vec).value;
    std::vector<Quantity> normvec;
    for (auto &q : vec){
      normvec.push_back(q * scale);
    }
    return normvec;
  }

  static std::vector<Quantity> combineUpDownUncs(const std::vector<Quantity> &up, const std::vector<Quantity> &down){
    // input need to be relative unc: "up/nominal", "down/nominal"
    assert(up.size() == down.size());
    std::vector<Quantity> unc;
    for (unsigned i=0; i<up.size(); ++i){
      double sign = (up[i].value >= 1) ? 1 : -1; // take the sign based on the up variation
      double val = 0.5 * (std::abs(up[i].value-1) + std::abs(1-down[i].value)); // take the avg of abs. diff.
      unc.emplace_back(1 + sign * val, 0); // don't forget to plus 1
    }
    return unc;
  }

  Quantity& setSqrtN(bool setAtLeastOne = false){
    if (setAtLeastOne && value<1){
      value = 1;
      error = 1;
    }else
      error = std::sqrt(value);
    return *this;
  }

  double value;
  double error;

};

Quantity::Styles Quantity::printStyle = Quantity::PLAIN;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template<typename Number>
std::vector<Number> operator+(const std::vector<Number> &a, const std::vector<Number> &b){
  assert(a.size()==b.size());
  std::vector<Number> rlt;
  for (unsigned i=0; i<a.size(); ++i)
    rlt.push_back(a.at(i) + b.at(i));
  return rlt;
}

template<typename Number>
std::vector<Number> operator-(const std::vector<Number> &a, const std::vector<Number> &b){
  assert(a.size()==b.size());
  std::vector<Number> rlt;
  for (unsigned i=0; i<a.size(); ++i)
    rlt.push_back(a.at(i) - b.at(i));
  return rlt;
}

template<typename Number, typename NumberB>
std::vector<Number> operator*(const std::vector<Number> &a, const std::vector<NumberB> &b){
  assert(a.size()==b.size());
  std::vector<Number> rlt;
  for (unsigned i=0; i<a.size(); ++i)
    rlt.push_back(a.at(i) * b.at(i));
  return rlt;
}

template<typename Number, typename NumberB>
std::vector<Number> operator*(const std::vector<Number> &a, const NumberB &b){
  std::vector<Number> rlt;
  for (unsigned i=0; i<a.size(); ++i)
    rlt.push_back(a.at(i) * b);
  return rlt;
}

template<typename Number, typename NumberB>
std::vector<Number> operator/(const std::vector<Number> &a, const std::vector<NumberB> &b){
  assert(a.size()==b.size());
  std::vector<Number> rlt;
  for (unsigned i=0; i<a.size(); ++i)
    rlt.push_back(a.at(i) / b.at(i));
  return rlt;
}

template<typename Number, typename NumberB>
std::vector<Number> operator/(const std::vector<Number> &a, const NumberB &b){
  std::vector<Number> rlt;
  for (unsigned i=0; i<a.size(); ++i)
    rlt.push_back(a.at(i) / b);
  return rlt;
}

template<typename Number>
std::ostream &operator<<(std::ostream &os, const std::vector<Number> &vec){
  for (const auto &q : vec){
    os << q << ", ";
  }
  return os;
}

template<typename Number>
Number sumVector(const std::vector<Number> &vec){
  Number sum(0);
  for (auto &q : vec) sum = sum + q;
  return sum;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


/*
void testQuantity(){
  Quantity a(3.14, 0.23);
  Quantity b(125.6, 1.5);
  Quantity c(6.2606, 1.24);
  Quantity d(49, 7);

  std::cout << a+b << std::endl;
  std::cout << a-b << std::endl;
  std::cout << a*b << std::endl;
  std::cout << a/b << std::endl;
  std::cout << a*2 << std::endl;
  std::cout << a/3 << std::endl;
  std::cout << a.power(2) << std::endl;

  std::vector<Quantity> v1{a,c}, v2{b,d};
  std::cout << v1+v2 << std::endl;
  std::cout << v1-v2 << std::endl;
  std::cout << v1*v2 << std::endl;
  std::cout << v1/v2 << std::endl;
  std::cout << v1*2 << std::endl;
  std::cout << v1/3 << std::endl;


  std::cout << a+b+c-d << std::endl;
  std::cout << a+b*c/d << std::endl;
  std::cout << a*b/c*d << std::endl;
  std::cout << a+b/c-d << std::endl;

}
*/
}
#endif /* ESTTOOLS_QUANTITY_H_ */
