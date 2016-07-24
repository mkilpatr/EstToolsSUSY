/*
 * QuantityAsymmErrors.hh
 *
 *  Created on: Jul 20, 2016
 *      Author: hqu
 */

#ifndef ESTTOOLS_QUANTITYASYMMERRORS_H_
#define ESTTOOLS_QUANTITYASYMMERRORS_H_

#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>
#include <map>
#include <algorithm>
#include <random>

#include "Quantity.h"
#include "TH1.h"

namespace EstTools{

class QuantityAsymmErrors : public Quantity {

public:

  enum Styles {PLAIN, LATEX, ROOT};
  static Styles printStyle;

  enum Distributions {UNKNOWN, GAUSSIAN, POISSON};
  const static std::vector<std::string> distNames;

  static bool ignoreTypes;

  QuantityAsymmErrors(double v = 0) : Quantity(v), errLow(0), errHigh(0), type(UNKNOWN) {}
  QuantityAsymmErrors(double value, double errLow, double errHigh, Distributions type=UNKNOWN) : Quantity(value, (errHigh+errLow)/2), errLow(errLow), errHigh(errHigh), type(type) {}
  QuantityAsymmErrors(double value, double error) : Quantity(value, error), errLow(error), errHigh(error), type(GAUSSIAN) {}
  QuantityAsymmErrors(const QuantityAsymmErrors &q) : QuantityAsymmErrors(q.value, q.errLow, q.errHigh, q.type) {}
  QuantityAsymmErrors(const Quantity &q) : QuantityAsymmErrors(q.value, q.error) {}

  virtual ~QuantityAsymmErrors() {}

  static QuantityAsymmErrors getPoisson(double value){
    QuantityAsymmErrors q;
    q.value = value;
    q.type = POISSON;

    TH1D h("htmp", "htmp", 1, 0, 1);
    h.Sumw2(kFALSE);
    h.SetBinContent(1, value);
    h.SetBinErrorOption(TH1::kPoisson);
    q.errLow = h.GetBinErrorLow(1);
    q.errHigh = h.GetBinErrorUp(1);

    q.error = value<10 ? q.errHigh : std::sqrt(value);

    return q;
  }

  Quantity getQuantity(bool force = false) const {
    double err = error==0 ? (errHigh + errLow) / 2 : error;
    if (type == GAUSSIAN || force) {
      return Quantity(value, err);
    }
    else
      throw std::domain_error("[QuantityAsymmErrors::getQuantity]: Cannot convert. Type is " + distNames.at(type));
  }

  friend QuantityAsymmErrors operator+(const QuantityAsymmErrors &a, const QuantityAsymmErrors &b){
    QuantityAsymmErrors q;
    if (a.type == b.type) {
      if (a.type == POISSON)
        q = getPoisson(a.value + b.value);
      else if (a.type == GAUSSIAN)
        q = QuantityAsymmErrors(a.getQuantity() + b.getQuantity());
    }else{
      if (ignoreTypes) {
        double value = a.value + b.value;
        double errLow = std::sqrt(a.errLow*a.errLow + b.errLow+b.errLow);
        double errHigh = std::sqrt(a.errHigh*a.errHigh + b.errHigh+b.errHigh);
        q = QuantityAsymmErrors(value, errLow, errHigh, UNKNOWN);
      }else{
        throw std::domain_error("[QuantityAsymmErrors::operator+]: Cannot add type " + distNames.at(a.type) + " and " + distNames.at(b.type));
      }
    }
    return q;
  }

  friend std::ostream &operator<<(std::ostream &os, const QuantityAsymmErrors &q){
    switch(printStyle){
    case PLAIN:
      os << q.value << "(+" << q.errHigh << ")(-" << q.errLow << ")";
      break;
    case LATEX:
      os << "$" << q.value << "^{+" << q.errHigh << "}_{-" << q.errLow << "}$";
      break;
    case ROOT:
      os << q.value << "^{+" << q.errHigh << "}_{-" << q.errLow << "}";
      break;
    default:
      os << q.value << "(+" << q.errHigh << ")(-" << q.errLow << ")";
      break;
    }
    return os;
  }

  double errLow;
  double errHigh;

  Distributions type;

};

QuantityAsymmErrors::Styles QuantityAsymmErrors::printStyle = QuantityAsymmErrors::PLAIN;
bool QuantityAsymmErrors::ignoreTypes = false;
const std::vector<std::string> QuantityAsymmErrors::distNames = {"Unknown", "Gaussian", "Poisson"};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class ToyCombination{

public:

  ToyCombination(UInt_t seed=0) : gen_(seed!=0 ? seed : rd()), nbins(0) {}
  virtual ~ToyCombination() {}

  struct EstInfo{
    // set at initialization
    std::string name;
    std::vector<Quantity> data_cr;
    std::vector<Quantity> transfer_factors;
    std::vector<Quantity> raw_mc;

    // filled bin by bin
    std::vector<QuantityAsymmErrors> pred;
  };

  static double alpha;
  unsigned nToys = 1000000;
  unsigned useGaussianWhenAbove = 10;

  template<typename Number>
  static std::pair<Number, Number> getLowHighQuantiles(const std::vector<Number> &sample, double alpha){
    std::vector<Number> vec(sample);
    std::sort(vec.begin(), vec.end());
    unsigned lowPos = vec.size() * alpha/2;
    unsigned highPos = vec.size() * (1-alpha/2);
    return std::make_pair(vec.at(lowPos), vec.at(highPos));
  }


  void addBackground(std::string name, const std::vector<Quantity> *data_cr, const std::vector<Quantity> *transfer_factors, const std::vector<Quantity> *raw_mc = nullptr){
    cerr << "\n--->" << __func__ << ": " << name << endl;

    if (nbins==0)
      nbins = data_cr ? data_cr->size() : raw_mc->size();
    else if((data_cr && nbins!=data_cr->size()) || (transfer_factors && nbins!=transfer_factors->size()) || (raw_mc && nbins!=raw_mc->size()))
      throw std::invalid_argument("ToyCombination::addBackground: Incompatible bin numbers!");
    EstInfo info;
    info.name = name;
    if(data_cr) info.data_cr = *data_cr;
    if(transfer_factors) info.transfer_factors = *transfer_factors;
    if(raw_mc) info.raw_mc = *raw_mc;
    bkgs[name] = info;
  }

  std::vector<QuantityAsymmErrors> combine(){
    cerr << "\n--->" << __func__ << endl;

    for (unsigned ibin = 0; ibin < nbins; ++ibin){
      // gaussian part
      std::vector<std::string> gaus_samples;
      Quantity gaus_sum(0, 0);

      // poisson part
      std::vector<std::string> poisson_samples;
      double c_sum = 0;
      std::vector<double> sum_low(nToys, 0);
      std::vector<double> sum_high(nToys, 0);

      // check if needs to be treated as Poisson
      for (auto &s : bkgs){

        auto &info = s.second;

        if(info.data_cr.empty()){
          // raw MC
          gaus_samples.push_back(s.first);
          auto pred = info.raw_mc.at(ibin);
          info.pred.emplace_back(pred);
          gaus_sum = gaus_sum + pred;
        }else if (info.data_cr.at(ibin).value > useGaussianWhenAbove){
          // use Gaussian errors
          gaus_samples.push_back(s.first);
          auto pred = info.data_cr.at(ibin) * info.transfer_factors.at(ibin);
          info.pred.emplace_back(pred);
          gaus_sum = gaus_sum + pred;
        }else{
          // use Poisson errors
          poisson_samples.push_back(s.first);

          const auto &data = info.data_cr.at(ibin);
          const auto &tf   = info.transfer_factors.at(ibin);

          // calc central value
          double c_val = data.value * tf.value;

          // throw toys
          std::vector<double> toy_samp_low, toy_samp_high;
          toy_samp_low.reserve(nToys);
          toy_samp_high.reserve(nToys);
          std::gamma_distribution<> r_gammaN(data.value, 1);
          std::gamma_distribution<> r_gammaNp1(data.value+1, 1);
          std::normal_distribution<> r_gaus(tf.value, tf.error);
          for (unsigned itoy = 0; itoy < nToys; ++itoy){
            double m_dataN = r_gammaN(gen_);
            double m_dataNp1 = r_gammaNp1(gen_);
            double m_tf   = r_gaus(gen_);
            if (m_tf<0) m_tf = 1.e-9;
            double m_predLow = m_dataN * m_tf;
            double m_predHigh = m_dataNp1 * m_tf;
            toy_samp_low.push_back(m_predLow);
            toy_samp_high.push_back(m_predHigh);

    //        std::cout << "itoy = " << itoy
    //            << ", m_data = " << m_dataN << ", m_tf = " << m_tf << ", m_pred = " << m_predLow
    //            << ", m_dataH = " << m_dataNp1 << ", m_tf = " << m_tf << ", m_predH = " << m_predHigh << std::endl;
          }

          // set individual pred
          auto qnLow = getLowHighQuantiles(toy_samp_low, alpha).first;
          auto qnHigh = getLowHighQuantiles(toy_samp_high, alpha).second;
          info.pred.emplace_back(c_val, c_val - qnLow, qnHigh - c_val);

          c_sum += c_val;
          sum_low = sum_low + toy_samp_low;
          sum_high = sum_high + toy_samp_high;
        }
      }

      if (poisson_samples.empty()){
        // if only gaussian
        totals.emplace_back(gaus_sum);
      }else {
        // mixer of poisson and gaussian
        std::vector<double> samp_gaus;
        samp_gaus.reserve(nToys);
        std::normal_distribution<> r_gaus(gaus_sum.value, gaus_sum.error);
        for (unsigned itoy=0; itoy<nToys; ++itoy){
          samp_gaus.push_back(r_gaus(gen_));
        }
        c_sum += gaus_sum.value;
        sum_low = sum_low + samp_gaus;
        sum_high = sum_high + samp_gaus;

        auto qnLow = getLowHighQuantiles(sum_low, alpha).first;
        auto qnHigh = getLowHighQuantiles(sum_high, alpha).second;
        totals.emplace_back(c_sum, c_sum - qnLow, qnHigh - c_sum);
      }


    }

    // return
    return totals;
  }

  std::vector<QuantityAsymmErrors> getPrediction(std::string process = "") const {
    if (process=="") return totals;
    else return bkgs.at(process).pred;
  }

public:
  unsigned nbins;
  std::map<std::string, EstInfo> bkgs;
  std::vector<QuantityAsymmErrors> totals;

  std::vector<std::vector<double>> samp_sum_high;
  std::vector<std::vector<double>> samp_sum_low;

protected:
  std::random_device rd;
  std::mt19937 gen_;

};

double ToyCombination::alpha = 1 - 0.6827;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//void testQuantile(){
//  std::vector<double> v;
//  for(unsigned i=0; i<100; ++i) v.push_back(300-i);
//  auto qt = ToyCombination::getLowHighQuantiles(v, ToyCombination::alpha);
//  std::cout << qt.first << ", " << qt.second << std::endl;
//}
//
//void testToyOne(){
//
//  std::vector<Quantity> data;
//  data.emplace_back(0, 0);
//  data.emplace_back(1, 1);
//  data.emplace_back(10000, 100);
//
//  std::vector<Quantity> tf;
//  tf.emplace_back(1, 0.0000000001);
//  tf.emplace_back(1, 0.0000000001);
//  tf.emplace_back(1, 0.0000000001);
//
//  ToyCombination c;
//  c.addBackground("dummy", &data, &tf);
//
//  std::cout << c.combine() << std::endl;
//
//  std::cout << "gaussian propagation:" << std::endl;
//  for (unsigned i=0; i<data.size(); ++i){
//    std::cout << data.at(i) * tf.at(i) << std::endl;
//  }
//
//}
//
//void testToySum(double nd, double nd2){
//  std::vector<Quantity> data;
//  data.emplace_back(nd, std::sqrt(nd));
//
//  std::vector<Quantity> tf;
//  tf.emplace_back(0.5, 0.0000000001);
//
//  std::vector<Quantity> data2;
//  data2.emplace_back(nd2, std::sqrt(nd2));
//
//  std::vector<Quantity> tf2;
//  tf2.emplace_back(0.5, 0.0000000001);
//
//
//  ToyCombination c;
//  c.addBackground("p1", &data, &tf);
//  c.addBackground("p2", &data2, &tf2);
//  std::cout << c.combine() << std::endl;
//
//  std::cout << "Treated as Gaussian: " << std::endl;
//  std::cout << data*tf + data2*tf2 << std::endl;
//
//}
//

}
#endif /* ESTTOOLS_QUANTITYASYMMERRORS_H_ */
