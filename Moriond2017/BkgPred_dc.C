/*
 * Znunu.C
 *
 *  Created on: Sep 23, 2015
 *      Author: hqu
 */

#include <fstream>

#include "../utils/json.hpp"
using json = nlohmann::json;

#include "../EstMethods/LLBEstimator.hh"
#include "../EstMethods/ZnunuEstimator.hh"
#include "../EstMethods/QCDEstimator.hh"
#include "SRParameters_dc.hh"


using namespace EstTools;

void runBkgPred(){
  auto start = chrono::steady_clock::now();

  vector<std::string> binlist;
  map<std::string, map<std::string, std::string>> binMaps;
  map<std::string, map<std::string, vector<double>>> yieldsMap;

  auto updateBinMap = [](const map<std::string, std::string>& orig, const map<std::string, std::string> &manual, const vector<std::string>& binlist){
    map<std::string, std::string> binmap;
    for (const auto &bin : binlist){
      try{
        binmap[bin] = orig.at(bin);
      }catch(const std::out_of_range &e){}
    }
    for (const auto &bin : binlist){
      try{
        binmap[bin] = manual.at(bin);
      }catch(const std::out_of_range &e){}
    }
    assert(binlist.size() == binmap.size());
    return binmap;
  };

  auto srcfg = srConfig();
  BaseEstimator s(srcfg);
  s.calcYields();
  Quantity::removeNegatives(s.yields.at("ttZ"));
  Quantity::removeNegatives(s.yields.at("diboson"));
  for (const auto &samp : srcfg.samples){
    s.convertYields(samp.first, "");
  }
  binlist = s.binlist;

  auto phocfg = phoConfig();
  ZnunuEstimator z(phocfg);
  z.zllcr_cfg = zllConfig();
  z.zll_normMap = normMap;
  z.phocr_normMap = phoNormMap;
  z.pred();
  z.printYields();
  z.prepDatacard();
  binMaps["phocr"] = updateBinMap(z.binMap, phocrBinMap, binlist);

  auto qcdcfg = qcdConfig();
  QCDEstimator q(qcdcfg);
  q.pred();
  q.printYields();
  q.prepDatacard();
  binMaps["qcdcr"] = updateBinMap(q.binMap, qcdcrBinMap, binlist);

  auto llbcfg = lepConfig();
  LLBEstimator l(llbcfg);
  l.pred();
  l.printYields();
  l.prepDatacard();
  binMaps["lepcr"] = updateBinMap(l.binMap, lepcrBinMap, binlist);


  vector<const BaseEstimator*> allPreds = {&z, &q, &l, &s};

  for (const auto *v : allPreds){
    yieldsMap.insert(v->std_yields.begin(), v->std_yields.end());
  }

  // manually fix any zero/negative yields
  for (auto &s : yieldsMap){
    if (s.first.find("data")!=std::string::npos) continue; // ignore data
    double default_value = 1e-6;
    for (auto &b : s.second){
      auto &v = b.second;
      if (v.size() && v.front()<=0){
        cout << "fixing " << s.first << "," << b.first << " from " << v.front() << " to " << default_value << endl;
        v.front() = default_value;
        v.back()  = default_value;
      }
    }
  }

  json j;
  j["binlist"] = binlist;
  j["binMaps"] = binMaps;
  j["yieldsMap"] = yieldsMap;
  std::ofstream jout;
  jout.open(outputdir+"/dc_BkgPred.json");
  jout << j.dump(2);
  jout.close();

//  cout << "\n Summary Traditional \n";
//  s.printSummary({z.yields.at("_pred"), l.yields.at("_pred"), q.yields.at("_pred"), l.yields.at("ttZ-sr"), l.yields.at("diboson-sr")}, s.yields.at("data-sr"));

  auto end = chrono::steady_clock::now();
  auto diff = end - start;
  cout << chrono::duration <double> (diff).count() << " s" << endl;

}

void runSignalYields(){
  auto start = chrono::steady_clock::now();

  map<std::string, map<std::string, vector<double>>> yieldsMap;

  for (const auto &signal : signals){
    BaseEstimator s(signalConfig(signal));
    s.calcYields();
    s.convertYields(signal, "");
    yieldsMap.insert(s.std_yields.begin(), s.std_yields.end());

    LLBEstimator l(lepcrSignalConfig(signal));
    l.calcYields();
    l.convertYields("lepcr_"+signal, "lepcr");
    yieldsMap.insert(l.std_yields.begin(), l.std_yields.end());
  }

  // manually fix any zero/negative yields
  for (auto &s : yieldsMap){
    if (s.first.find("data")!=std::string::npos) continue; // ignore data
    double default_value = 1e-6;
    for (auto &b : s.second){
      auto &v = b.second;
      if (v.size() && v.front()<=0){
        cout << "fixing " << s.first << "," << b.first << " from " << v.front() << " to " << default_value << endl;
        v.front() = default_value;
        v.back()  = default_value;
      }
    }
  }

  json j;
  j["signals"] = signals;
  j["yieldsMap"] = yieldsMap;
  std::ofstream jout;
  jout.open(outputdir+"/dc_SigYields.json");
  jout << j.dump(2);
  jout.close();

  auto end = chrono::steady_clock::now();
  auto diff = end - start;
  cout << chrono::duration <double> (diff).count() << " s" << endl;
}


void BkgPred_dc(){
//  runBkgPred();
  runSignalYields();
}
