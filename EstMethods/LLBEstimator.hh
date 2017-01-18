#ifndef ESTTOOLS_ESTMETHODS_LLBESTIMATOR_HH_
#define ESTTOOLS_ESTMETHODS_LLBESTIMATOR_HH_

#if !defined(__CINT__) || defined(__MAKECINT__)

#include "../utils/Estimator.hh"

using namespace std;
#endif

namespace EstTools{

class LLBEstimator : public BaseEstimator {
public:
  LLBEstimator() {}
  LLBEstimator(TString outputdir, TString outputfile = "LLB_output.root") :
    BaseEstimator(outputdir, outputfile) {}
  LLBEstimator(const BaseConfig &config) :
    BaseEstimator(config) {}

  virtual ~LLBEstimator() {}

  vector<Quantity> calcSLep(){
    // calculate correction factors from single lepton control regions

    cerr << "\n--->" << __func__ << endl;

    auto data = yields.at("singlelep");
    Quantity::removeZeroes(data, 0.001, 1.8);
    auto mc   = yields.at("ttbarplusw");

    auto s_lep = data / mc;
    cout << "    ---> " << s_lep << endl;
    return s_lep;

  }

  void pred(){
    cerr << "\n--->" << "Running LLB prediction ..." << endl << endl;

    // Yields
    calcYields();
    sumYields({"ttbar", "wjets", "tW", "ttW"}, "ttbarplusw");
    sumYields({"ttbar-sr", "wjets-sr", "tW-sr", "ttW-sr"}, "ttbarplusw-sr");
    sumYields({"ttbar-sr-int", "wjets-sr-int", "tW-sr-int", "ttW-sr-int"}, "ttbarplusw-sr-int");

    // _SLep = N(Data,CR)/N(MC,CR)
    // _TF   = N(MC,SR)/N(MC,CR)
    // _pred = _TF * N(Data,CR)
    // _TF_CR_to_SR_noextrap = N(MC,SR with no extrapolation [= cr cats this round])/N(MC,CR)
    // _TF_SR_extrap         = N(MC,SR with extrapolation)/N(MC,SR with no extrapolation)
    yields["_SLep"] = calcSLep(); // is yields.at("singlelep")/yields.at("ttbarplusw")
    yields["_TF"]                   = yields.at("ttbarplusw-sr")/yields.at("ttbarplusw");
    yields["_pred"]                 = yields.at("singlelep") * yields.at("_TF");
    yields["_TF_CR_to_SR_noextrap"] = yields.at("ttbarplusw-sr-int")/yields.at("ttbarplusw");
    yields["_TF_SR_extrap"]         = yields.at("ttbarplusw-sr")/yields.at("ttbarplusw-sr-int");

    printVec(yields["_pred"], "Final prediction", true);
  }

  // spits out latex-formatted table for Moriond17 results
  // design to be consistent with 'results' tables
  // req's category names starting with either lm_ or hm_
  // bool parameter can output the tables to two (LM/HM) text files
  // categories are traversed linearly with no special cases other than 'lm_' or 'hm_' (lm has 1 LLB TF, hm splits it into 2 LLB TFs)
  void printMoriond17Table(const map<TString, TString> &labelMap, bool saveToFile = false){

    Quantity::printStyle = Quantity::LATEX;
    fstream outStreamLM, outStreamHM; ostringstream outString; // form string in outString, then conditionally write outString to cout or file
    if(saveToFile){
      outStreamLM.open("Moriond17_LLB_LM.txt",ios::out);
      outStreamHM.open("Moriond17_LLB_HM.txt",ios::out);
    }

    // linearly traverse all bins (hm and lm)
    int ibin = 0;
    for (const auto &cat_name : config.categories){
      bool isLM = false;
      // simple check for any changes in category names which would cause unexpected behavior
      if(cat_name.Contains("lm_")) { isLM = true; }
      else if(cat_name.Contains("hm_")) { isLM = false; }
      else { throw std::runtime_error(TString::Format("LLBEstimator.hh/printMoriond17Table: category name, %s, must start with lm_ or hm_. New categories? Update this function!\n",cat_name.Data())); }
      const auto & cat = config.catMaps.at(cat_name);

      // latex format for each category header: hline, multicolumn with cat label, hline
      auto cat_label = translateString(cat_name, labelMap, "_", ", ");
      int ncols = (isLM) ? 5 : 6; // HM has one extra column for second TF
      outString << R"(\hline)" << endl << R"(\multicolumn{)"+to_string(ncols)+R"(}{c}{)" + cat_label + R"(} \\)" << endl << R"(\hline)" << endl;

      // a latex comment with raw cat label for clarity
      outString << " % " << setw(30) << cat.label << endl;
      //cout << outString.str();

      // latex format for each met bin in the category: search region, met, ----numbers
      auto metlabels = convertBinRangesToLabels(cat.bin.plotbins, true);
      for (const auto &p : metlabels){
        const auto &data = yields["singlelep"].at(ibin);
        const auto &tf1  = yields["_TF_CR_to_SR_noextrap"].at(ibin);
        const auto &tf2  = yields["_TF_SR_extrap"].at(ibin);
        const auto &tf   = yields["_TF"].at(ibin);
        const auto &pred = yields["_pred"].at(ibin);
        // if LM, just one TF column. if HM, two TF columns.
        outString << ibin << " & " << p << " & " << fixed << setprecision(0) << setw(0) << data.value << " & " << fixed << setprecision(3) << setw(10);
        if(isLM){
          outString << tf;
        }else{
          outString << tf1 << " & " << fixed << setprecision(3) << setw(10) << tf2;
        }
        outString << " & " << setprecision(2) << setw(10) << pred << " \\\\" << endl;

        // send it
        cout << outString.str();
        if(saveToFile){
          if(isLM) { outStreamLM << outString.str(); }
          else { outStreamHM << outString.str(); }
        }
        outString.str(""); // reset
        ibin++;
      }//for met
    }//for cat
  }//for country

  void printTable(bool doLM) {
    Quantity::printStyle = Quantity::LATEX;
    int ibin = 0, ibin_nb2 = 0;
    for (const auto &cat_name : config.categories){
      const auto & cat = config.catMaps.at(cat_name);
      if((doLM && (cat_name.Contains("highnj") || cat_name.Contains("medptb"))) || (!doLM && cat_name.Contains("nb2"))) {
        ibin += cat.bin.cuts.size();
        continue;
      }
      TString cat_name_nb2 = cat_name;
      if(!doLM) cat_name_nb2.ReplaceAll("nb1","nb2");
      else {
        cat_name_nb2.ReplaceAll("lownj","highnj");
        cat_name_nb2.ReplaceAll("lowptb","medptb");
      }
      cout << setw(30) << cat.label << endl;
      auto metlabels = convertBinRangesToLabels(cat.bin.plotbins, true);
      for (const auto &p : metlabels){
        if(cat_name.Contains("mtb0")) ibin_nb2 = ibin + 8;
        else if(cat_name.Contains("mtb175")) ibin_nb2 = ibin + 22;
        else ibin_nb2 = ibin + 4;
        const auto &data_nb1 = yields["singlelep"].at(ibin);
        const auto &data_nb2 = yields["singlelep"].at(ibin_nb2);
        const auto &tf_nb1 = yields["_TF"].at(ibin);
        const auto &tf_nb2 = yields["_TF"].at(ibin_nb2);
        const auto &pred_nb1 = yields["_pred"].at(ibin);
        const auto &pred_nb2 = yields["_pred"].at(ibin_nb2);
        cout << p << " & " << fixed << setprecision(0) << setw(0) << data_nb1.value << " & " << fixed << setprecision(2) << setw(10) << tf_nb1 << " & " << fixed << setprecision(2) << setw(10) << pred_nb1 << " & " << fixed << setprecision(0) << setw(10) << data_nb2 << " & " << fixed << setprecision(2) << setw(10) << tf_nb2 << " & " << fixed << setprecision(2) << setw(10) << pred_nb2 << " \\\\" << endl;
       ibin++;
      }
    }

  }


};


}

#endif /*ESTTOOLS_ESTMETHODS_LLBESTIMATOR_HH_*/
