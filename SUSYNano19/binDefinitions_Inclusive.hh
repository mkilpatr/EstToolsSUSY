#ifndef ESTTOOLS_BINDEFINITIONS_CR_HH_
#define ESTTOOLS_BINDEFINITIONS_CR_HH_

namespace EstTools{

std::vector<TString> srbins{
  //---------- high deltaM ----------
  // low mtb
  "hm",
  //---------- high deltaM ----------

};

std::map<TString, std::vector<int>> srMETbins{
  //---------- high deltaM ----------
  // low mtb
  //{"hm",                    {250, 350, 450, 550, 650, 750, 1000}},
  {"hm",                    {400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000}},
  //{"hm",                    {0, 1, 2, 3}},
  //{"hm",                    {1, 2, 3, 4, 5}},
  //---------- high deltaM ----------

};

std::map<TString, TString> phocrMapping{
  // low mtb
  {"hm",                         "hm"},
  //---------- high deltaM ----------

};

std::map<TString, TString> lepcrMapping {
  //---------- high deltaM ----------
  // low mtb
  {"hm",                         "hm"},
  //---------- high deltaM ----------

};

std::map<TString, std::vector<int>> qcdcrMETbins {
  //---------- high deltaM ----------
  // low mtb
  //{"hm",                    {250, 350, 450, 550, 650, 750, 1000}},
  {"hm",                    {400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000}},
  //{"hm",                    {0, 1, 2, 3}},
  //{"hm",                    {1, 2, 3, 4, 5}},
};
}
#endif /* ESTTOOLS_LMPARAMETERS_HH_ */
