/*
 * JsonHelper.h
 *
 *  Created on: Jul 4, 2016
 *      Author: hqu
 */

#ifndef ESTTOOLS_JSONHELPER_H_
#define ESTTOOLS_JSONHELPER_H_

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include "TString.h"

#include "Quantity.h"
#include "json.hpp"


using json = nlohmann::json;

namespace EstTools{

class JsonHelper{
public:
  static json convertToJson(const std::map<TString, std::vector<Quantity>> &input, bool withError = true){
    if (withError){
      return convertToJsonWithError(input);
    }else {
      return convertToJsonWithoutError(input);
    }
  }

  static void dumpJson(std::string filename, const std::map<TString, std::vector<Quantity>> &input, bool withError = true){
    const auto &j = convertToJson(input, withError);
    dumpJson(filename, j);
  }

  static void dumpJson(std::string filename, const json &j){
    std::ofstream jout;
    jout.open(filename);
    jout << j.dump(2);
    jout.close();
  }


private:
  static json convertToJsonWithError(const std::map<TString, std::vector<Quantity>> &input){
    std::map<std::string, std::vector<std::vector<double>>> obj;
    for (const auto &it : input){
      std::string key(it.first.Data());
      obj[key] = std::vector<std::vector<double>>();
      for (const auto &q : it.second){
        obj.at(key).push_back({q.value, q.error});
      }
    }
    return json(obj);
  }

  static json convertToJsonWithoutError(const std::map<TString, std::vector<Quantity>> &input){
    std::map<std::string, std::vector<double>> obj;
    for (const auto &it : input){
      std::string key(it.first.Data());
      obj[key] = std::vector<double>();
      for (const auto &q : it.second){
        obj.at(key).push_back(q.value);
      }
    }
    return json(obj);
  }


};



}
#endif /* ESTTOOLS_JSONHELPER_H_ */
