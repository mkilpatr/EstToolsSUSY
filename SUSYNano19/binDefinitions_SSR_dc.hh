#ifndef ESTTOOLS_BINDEFINITIONSDATACARD_HH_
#define ESTTOOLS_BINDEFINITIONSDATACARD_HH_

namespace EstTools{

std::vector<TString> srbins{
  //---------- low deltaM ----------
  // 0b, 0 or >=1 ivf
  "lm_nb0_nivf0_highptisr_nj2to5",
  "lm_nb0_nivf0_highptisr_nj6",
  "lm_nb0_nivf1_highptisr_nj2to5",
  "lm_nb0_nivf1_highptisr_nj6",

  // 1b, 0 or >=1 ivf
  "lm_nb1_nivf0_lowmtb_highptisr_lowptb",
  "lm_nb1_nivf0_lowmtb_highptisr_medptb",

  // 2b
  "lm_nb2_lowmtb_highptisr_lowptb12",
  "lm_nb2_lowmtb_highptisr_medptb12",
  //---------- low deltaM ----------


  //---------- high deltaM ----------
  // low mtb
  "hm_nb1_lowmtb_nj7_nrtgeq1",
  "hm_nb2_lowmtb_nj7_nrtgeq1",

  // 1 tagged
  "hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1000to1300",
  "hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1300to1500",
  "hm_nbeq2_highmtb_nt1_nrt0_nw0_htgt1500",
  "hm_nbeq2_highmtb_nt0_nrt0_nw1_ht1300to1500",
  "hm_nbeq2_highmtb_nt0_nrt0_nw1_htgt1500",
  "hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1000to1300",
  "hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1300to1500",
  "hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1500",

  // 1+1eq
  "hm_nbeq2_highmtb_nt1_nrt0_nw1_htlt1000",
  "hm_nbeq2_highmtb_nt1_nrt0_nw1_ht1000to1300",
  "hm_nbeq2_highmtb_nt1_nrt0_nw1_ht1300to1500",
  "hm_nbeq2_highmtb_nt1_nrt0_nw1_htgt1500",
  "hm_nbeq2_highmtb_nt1_nrt1_nw0_htlt1000",
  "hm_nbeq2_highmtb_nt1_nrt1_nw0_ht1000to1300",
  "hm_nbeq2_highmtb_nt1_nrt1_nw0_ht1300to1500",
  "hm_nbeq2_highmtb_nt1_nrt1_nw0_htgt1500",
  "hm_nbeq2_highmtb_nt0_nrt1_nw1_htlt1000",
  "hm_nbeq2_highmtb_nt0_nrt1_nw1_ht1000to1300",
  "hm_nbeq2_highmtb_nt0_nrt1_nw1_ht1300to1500",
  "hm_nbeq2_highmtb_nt0_nrt1_nw1_htgt1500",

  // 2
  "hm_nbeq2_highmtb_nt2_nrt0_nw0_htlt1000",
  "hm_nbeq2_highmtb_nt2_nrt0_nw0_ht1000to1300",
  "hm_nbeq2_highmtb_nt2_nrt0_nw0_ht1300to1500",
  "hm_nbeq2_highmtb_nt2_nrt0_nw0_htgt1500",
  "hm_nbeq2_highmtb_nt0_nrt0_nw2_htlt1000",
  "hm_nbeq2_highmtb_nt0_nrt0_nw2_ht1000to1300",
  "hm_nbeq2_highmtb_nt0_nrt0_nw2_ht1300to1500",
  "hm_nbeq2_highmtb_nt0_nrt0_nw2_htgt1500",
  "hm_nbeq2_highmtb_nt0_nrt2_nw0_htlt1000",
  "hm_nbeq2_highmtb_nt0_nrt2_nw0_ht1000to1300",
  "hm_nbeq2_highmtb_nt0_nrt2_nw0_ht1300to1500",
  "hm_nbeq2_highmtb_nt0_nrt2_nw0_htgt1500",

  // 3
  "hm_nbeq2_highmtb_nrtntnwgeq3_htlt1000",
  "hm_nbeq2_highmtb_nrtntnwgeq3_ht1000to1300",
  "hm_nbeq2_highmtb_nrtntnwgeq3_ht1300to1500",
  "hm_nbeq2_highmtb_nrtntnwgeq3_htgt1500",

  // nb3
  //1 tagged
  "hm_nb3_highmtb_nt1_nrt0_nw0_htlt1000",
  "hm_nb3_highmtb_nt1_nrt0_nw0_ht1000to1500",
  "hm_nb3_highmtb_nt1_nrt0_nw0_htgt1500",
  "hm_nb3_highmtb_nt0_nrt0_nw1_htlt1000",
  "hm_nb3_highmtb_nt0_nrt0_nw1_ht1000to1500",
  "hm_nb3_highmtb_nt0_nrt0_nw1_htgt1500",
  "hm_nb3_highmtb_nt0_nrt1_nw0_htlt1000",
  "hm_nb3_highmtb_nt0_nrt1_nw0_ht1000to1500",
  "hm_nb3_highmtb_nt0_nrt1_nw0_htgt1500",

  //1+1
  "hm_nb3_highmtb_nt1_nrt0_nw1_htlt1000",
  "hm_nb3_highmtb_nt1_nrt0_nw1_ht1000to1500",
  "hm_nb3_highmtb_nt1_nrt0_nw1_htgt1500",
  "hm_nb3_highmtb_nt1_nrt1_nw0_htlt1000",
  "hm_nb3_highmtb_nt1_nrt1_nw0_ht1000to1500",
  "hm_nb3_highmtb_nt1_nrt1_nw0_htgt1500",
  "hm_nb3_highmtb_nt0_nrt1_nw1_htlt1000",
  "hm_nb3_highmtb_nt0_nrt1_nw1_ht1000to1500",
  "hm_nb3_highmtb_nt0_nrt1_nw1_htgt1500",

  //2
  "hm_nb3_highmtb_nt2_nrt0_nw0_htlt1000",
  "hm_nb3_highmtb_nt2_nrt0_nw0_ht1000to1500",
  "hm_nb3_highmtb_nt2_nrt0_nw0_htgt1500",
  "hm_nb3_highmtb_nt0_nrt0_nw2_htlt1000",
  "hm_nb3_highmtb_nt0_nrt0_nw2_ht1000to1500",
  "hm_nb3_highmtb_nt0_nrt0_nw2_htgt1500",
  "hm_nb3_highmtb_nt0_nrt2_nw0_htlt1000",
  "hm_nb3_highmtb_nt0_nrt2_nw0_ht1000to1500",
  "hm_nb3_highmtb_nt0_nrt2_nw0_htgt1500",

  // 3
  "hm_nb3_highmtb_nrtntnwgeq3_htlt1000",
  "hm_nb3_highmtb_nrtntnwgeq3_ht1000to1500",
  "hm_nb3_highmtb_nrtntnwgeq3_htgt1500",
  
  //---------- high deltaM ----------

};

std::map<TString, std::vector<int>> srMETbins{
  //---------- low deltaM ----------
  // 0b, 0 or >=1 ivf
  {"lm_nb0_nivf0_highptisr_nj2to5",              {     750, 1000}},
  {"lm_nb0_nivf0_highptisr_nj6",                 {     550, 650, 750, 1000}},
  {"lm_nb0_nivf1_highptisr_nj2to5",              {     750, 1000}},
  {"lm_nb0_nivf1_highptisr_nj6",                 {     550, 650, 750, 1000}},

  // 1b, 0 or >=1 ivf
  {"lm_nb1_nivf0_lowmtb_highptisr_lowptb",            {550, 650, 750, 1000}},
  {"lm_nb1_nivf0_lowmtb_highptisr_medptb",            {550, 650, 750, 1000}},

  // 2b
  {"lm_nb2_lowmtb_highptisr_lowptb12",                {650, 1000}},
  {"lm_nb2_lowmtb_highptisr_medptb12",                {450, 550, 650, 1000}},
  //---------- low deltaM ----------


  //---------- high deltaM ----------
  // low mtb
  {"hm_nb1_lowmtb_nj7_nrtgeq1",                    {400, 500, 1000}},
  {"hm_nb2_lowmtb_nj7_nrtgeq1",                    {400, 500, 1000}},

  //1
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1000to1300",   {650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1300to1500",   {650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_htgt1500",       {650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_ht1300to1500",   {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_htgt1500",       {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1000to1300",   {650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1300to1500",   {650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1500",       {650, 1000}},

  // 1+1
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_htlt1000",       {550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_ht1000to1300",   {550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_ht1300to1500",   {550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_htgt1500",       {550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htlt1000",       {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_ht1000to1300",   {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_ht1300to1500",   {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htgt1500",       {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_htlt1000",       {550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_ht1000to1300",   {550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_ht1300to1500",   {550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_htgt1500",       {550, 650, 1000}},

  // 2
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_htlt1000",       {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_ht1000to1300",   {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_ht1300to1500",   {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_htgt1500",       {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_htgt1500",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htlt1000",       {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_ht1000to1300",   {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_ht1300to1500",   {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htgt1500",       {450, 550, 650, 1000}},
  
  // 3
  {"hm_nbeq2_highmtb_nrtntnwgeq3_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_htgt1500",       {250, 350, 450, 550, 650, 1000}},

  // nb3
  //1 tagged
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htlt1000",         {550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_ht1000to1500",     {550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htgt1500",         {550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_htlt1000",         {550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_ht1000to1500",     {550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_htgt1500",         {550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htlt1000",         {550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_ht1000to1500",     {550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htgt1500",         {550, 1000}},

  //1+1
  {"hm_nb3_highmtb_nt1_nrt0_nw1_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt0_nw1_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt0_nw1_htgt1500",         {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_htgt1500",         {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_htgt1500",         {250, 350, 450, 550, 1000}},

  //2
  {"hm_nb3_highmtb_nt2_nrt0_nw0_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt2_nrt0_nw0_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt2_nrt0_nw0_htgt1500",         {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_htgt1500",         {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_htgt1500",         {250, 350, 450, 550, 1000}},

  // 3
  {"hm_nb3_highmtb_nrtntnwgeq3_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nrtntnwgeq3_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nrtntnwgeq3_htgt1500",         {250, 350, 450, 550, 1000}},
  
  //---------- high deltaM ----------

};

std::map<TString, TString> phocrMapping{
  //---------- low deltaM ----------
  // 0b, 0 or >=1 ivf
  {"lm_nb0_nivf0_highptisr_nj2to5",              "lm_nb0_nivf0_highptisr_nj2to5"},
  {"lm_nb0_nivf0_highptisr_nj6",                 "lm_nb0_nivf0_highptisr_nj6"},
  {"lm_nb0_nivf1_highptisr_nj2to5",              "lm_nb0_nivf1_highptisr_nj2to5"},
  {"lm_nb0_nivf1_highptisr_nj6",                 "lm_nb0_nivf1_highptisr_nj6"},

  // 1b, 0 or >=1 ivf
  {"lm_nb1_nivf0_lowmtb_highptisr_lowptb",       "lm_nb1_nivf0_lowmtb_highptisr_lowptb"},
  {"lm_nb1_nivf0_lowmtb_highptisr_medptb",       "lm_nb1_nivf0_lowmtb_highptisr_medptb"},

  // 2b
  {"lm_nb2_lowmtb_highptisr_lowptb12",           "lm_nb2_lowmtb_highptisr_lowptb12"},
  {"lm_nb2_lowmtb_highptisr_medptb12",           "lm_nb2_lowmtb_highptisr_medptb12"},
  //---------- low deltaM ----------

  //---------- high deltaM ----------
  // low mtb
  {"hm_nb1_lowmtb_nj7_nrtgeq1",                         "hm_nb1_lowmtb_nj7_nrtgeq1"},
  {"hm_nb2_lowmtb_nj7_nrtgeq1",                         "hm_nb2_lowmtb_nj7_nrtgeq1"},
  
  // 1 tagged                                          
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},

  // 1+1eq                                             
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},

  // 2                                                 
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},

  // 3                                                 
  {"hm_nbeq2_highmtb_nrtntnwgeq3_htlt1000",             "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_ht1000to1300",         "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_ht1300to1500",         "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_htgt1500",             "hm_nbeq2_highmtb_htgt1500"},

  // nb3                                               
  //1 tagged                                           
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htgt1500",              "hm_nb3_highmtb_htgt1500"},

  //1+1                                                
  {"hm_nb3_highmtb_nt1_nrt0_nw1_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt1_nrt0_nw1_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt1_nrt0_nw1_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_htgt1500",              "hm_nb3_highmtb_htgt1500"},

  //2                                                  
  {"hm_nb3_highmtb_nt2_nrt0_nw0_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt2_nrt0_nw0_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt2_nrt0_nw0_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  
  // 3                                                 
  {"hm_nb3_highmtb_nrtntnwgeq3_htlt1000",               "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nrtntnwgeq3_ht1000to1500",           "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nrtntnwgeq3_htgt1500",               "hm_nb3_highmtb_htgt1500"},
  
  //---------- high deltaM ----------
};

std::map<TString, TString> lepcrMapping {
  //---------- low deltaM ----------
  // 0b, 0 or >=1 ivf
  {"lm_nb0_nivf0_highptisr_nj2to5",              "lm_nb0_nivf0_highptisr_nj2to5"},
  {"lm_nb0_nivf0_highptisr_nj6",                 "lm_nb0_nivf0_highptisr_nj6"},
  {"lm_nb0_nivf1_highptisr_nj2to5",              "lm_nb0_nivf1_highptisr_nj2to5"},
  {"lm_nb0_nivf1_highptisr_nj6",                 "lm_nb0_nivf1_highptisr_nj6"},

  // 1b, 0 or >=1 ivf
  {"lm_nb1_nivf0_lowmtb_highptisr_lowptb",       "lm_nb1_nivf0_lowmtb_highptisr_lowptb"},
  {"lm_nb1_nivf0_lowmtb_highptisr_medptb",       "lm_nb1_nivf0_lowmtb_highptisr_medptb"},

  // 2b
  {"lm_nb2_lowmtb_highptisr_lowptb12",           "lm_nb2_lowmtb_highptisr_lowptb12"},
  {"lm_nb2_lowmtb_highptisr_medptb12",           "lm_nb2_lowmtb_highptisr_medptb12"},
  //---------- low deltaM ----------


  //---------- high deltaM ----------
  // low mtb
  {"hm_nb1_lowmtb_nj7_nrtgeq1",                         "hm_nb1_lowmtb_nj7_nrtgeq1"},
  {"hm_nb2_lowmtb_nj7_nrtgeq1",                         "hm_nb2_lowmtb_nj7_nrtgeq1"},
  
  // 1 tagged                                          
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},

  // 1+1eq                                             
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},

  // 2                                                 
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htlt1000",            "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_ht1000to1300",        "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_ht1300to1500",        "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htgt1500",            "hm_nbeq2_highmtb_htgt1500"},

  // 3                                                 
  {"hm_nbeq2_highmtb_nrtntnwgeq3_htlt1000",             "hm_nbeq2_highmtb_htlt1000"},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_ht1000to1300",         "hm_nbeq2_highmtb_ht1000to1300"},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_ht1300to1500",         "hm_nbeq2_highmtb_ht1300to1500"},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_htgt1500",             "hm_nbeq2_highmtb_htgt1500"},

  // nb3                                               
  //1 tagged                                           
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htgt1500",              "hm_nb3_highmtb_htgt1500"},

  //1+1                                                
  {"hm_nb3_highmtb_nt1_nrt0_nw1_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt1_nrt0_nw1_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt1_nrt0_nw1_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_htgt1500",              "hm_nb3_highmtb_htgt1500"},

  //2                                                  
  {"hm_nb3_highmtb_nt2_nrt0_nw0_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt2_nrt0_nw0_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt2_nrt0_nw0_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_htlt1000",              "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_ht1000to1500",          "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_htgt1500",              "hm_nb3_highmtb_htgt1500"},
  
  // 3                                                 
  {"hm_nb3_highmtb_nrtntnwgeq3_htlt1000",               "hm_nb3_highmtb_htlt1000"},
  {"hm_nb3_highmtb_nrtntnwgeq3_ht1000to1500",           "hm_nb3_highmtb_ht1000to1500"},
  {"hm_nb3_highmtb_nrtntnwgeq3_htgt1500",               "hm_nb3_highmtb_htgt1500"},
  
  //---------- high deltaM ----------

};

std::map<TString, std::vector<int>> qcdcrMETbins {
  //---------- low deltaM ----------
  // 0b, 0 or >=1 ivf
  {"lm_nb0_nivf0_highptisr_nj2to5",              {     750, 1000}},
  {"lm_nb0_nivf0_highptisr_nj6",                 {     550, 650, 750, 1000}},
  {"lm_nb0_nivf1_highptisr_nj2to5",              {     750, 1000}}, // merge last 2 bins
  {"lm_nb0_nivf1_highptisr_nj6",                 {     450,                1000}}, // merge last 3 bins
  
  // 1b, 0 or >=1 ivf
  {"lm_nb1_nivf0_lowmtb_highptisr_lowptb",            {550, 650,      1000}}, // merge last 2 bins
  {"lm_nb1_nivf0_lowmtb_highptisr_medptb",            {550, 650,      1000}}, // merge last 2 bins
  
  // 2b
  {"lm_nb2_lowmtb_highptisr_lowptb12",                {450,           1000}}, // merge all 3 bins
  {"lm_nb2_lowmtb_highptisr_medptb12",                {450,           1000}}, // merge all 3 bins
  //---------- low deltaM ----------
  
  //---------- high deltaM ----------
  // low mtb
  {"hm_nb1_lowmtb_nj7_nrtgeq1",                    {400, 500, 1000}},
  {"hm_nb2_lowmtb_nj7_nrtgeq1",                    {400, 500, 1000}},

  //1
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1000to1300",   {650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1300to1500",   {650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_htgt1500",       {650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_ht1300to1500",   {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_htgt1500",       {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1000to1300",   {650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1300to1500",   {650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1500",       {650, 1000}},

  // 1+1
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_htlt1000",       {550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_ht1000to1300",   {550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_ht1300to1500",   {550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1_htgt1500",       {550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htlt1000",       {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_ht1000to1300",   {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_ht1300to1500",   {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htgt1500",       {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_htlt1000",       {550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_ht1000to1300",   {550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_ht1300to1500",   {550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1_htgt1500",       {550, 650, 1000}},

  // 2
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_htlt1000",       {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_ht1000to1300",   {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_ht1300to1500",   {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0_htgt1500",       {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2_htgt1500",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htlt1000",       {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_ht1000to1300",   {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_ht1300to1500",   {450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htgt1500",       {450, 550, 650, 1000}},
  
  // 3
  {"hm_nbeq2_highmtb_nrtntnwgeq3_htlt1000",       {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_ht1000to1300",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_ht1300to1500",   {250, 350, 450, 550, 650, 1000}},
  {"hm_nbeq2_highmtb_nrtntnwgeq3_htgt1500",       {250, 350, 450, 550, 650, 1000}},

  // nb3
  //1 tagged
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htgt1500",         {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw1_htgt1500",         {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htgt1500",         {250, 350, 450, 550, 1000}},

  //1+1
  {"hm_nb3_highmtb_nt1_nrt0_nw1_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt0_nw1_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt0_nw1_htgt1500",         {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt1_nw0_htgt1500",         {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw1_htgt1500",         {250, 350, 450, 550, 1000}},

  //2
  {"hm_nb3_highmtb_nt2_nrt0_nw0_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt2_nrt0_nw0_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt2_nrt0_nw0_htgt1500",         {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw2_htgt1500",         {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt2_nw0_htgt1500",         {250, 350, 450, 550, 1000}},

  // 3
  {"hm_nb3_highmtb_nrtntnwgeq3_htlt1000",         {250, 350, 550, 1000}},
  {"hm_nb3_highmtb_nrtntnwgeq3_ht1000to1500",     {250, 350, 450, 550, 1000}},
  {"hm_nb3_highmtb_nrtntnwgeq3_htgt1500",         {250, 350, 450, 550, 1000}},
  
  //---------- high deltaM ----------

};

// --------------
std::vector<TString> mergedSSRbins{
//---------- low deltaM ----------
  // 0b, 0 or >=1 ivf
  "lm_nb0_nivf0_highptisr_nj2to5",
  "lm_nb0_nivf0_highptisr_nj6",
  "lm_nb0_nivf1_highptisr_nj2to5",
  "lm_nb0_nivf1_highptisr_nj6",

  // 1b, 0 or >=1 ivf
  "lm_nb1_nivf0_lowmtb_highptisr_lowptb",
  "lm_nb1_nivf0_lowmtb_highptisr_medptb",

  // 2b
  "lm_nb2_lowmtb_highptisr_lowptb12",
  "lm_nb2_lowmtb_highptisr_medptb12",
  //---------- low deltaM ----------


  //---------- high deltaM ----------
  // low mtb
  "hm_nb1_lowmtb_nj7_nrtgeq1",
  "hm_nb2_lowmtb_nj7_nrtgeq1",

  // nb2
  // 1 tagged
  "hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1000to1500",
  "hm_nbeq2_highmtb_nt1_nrt0_nw0_htgt1500",
  "hm_nbeq2_highmtb_nt0_nrt0_nw1_htgt1300",
  "hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1000to1500",
  "hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1500",

  // 1+1eq
  "hm_nbeq2_highmtb_nt1_nrt0_nw1",
  "hm_nbeq2_highmtb_nt1_nrt1_nw0_htlt1300",
  "hm_nbeq2_highmtb_nt1_nrt1_nw0_htgt1300",
  "hm_nbeq2_highmtb_nt0_nrt1_nw1",

  // 2
  "hm_nbeq2_highmtb_nt2_nrt0_nw0",
  "hm_nbeq2_highmtb_nt0_nrt0_nw2",
  "hm_nbeq2_highmtb_nt0_nrt2_nw0_htlt1300",
  "hm_nbeq2_highmtb_nt0_nrt2_nw0_htgt1300",

  // 3
  "hm_nbeq2_highmtb_nrtntnwgeq3",

  // nb3
  //1 tagged
  "hm_nb3_highmtb_nt1_nrt0_nw0_htlt1000",
  "hm_nb3_highmtb_nt1_nrt0_nw0_ht1000to1500",
  "hm_nb3_highmtb_nt1_nrt0_nw0_htgt1500",
  "hm_nb3_highmtb_nt0_nrt0_nw1",
  "hm_nb3_highmtb_nt0_nrt1_nw0_htlt1000",
  "hm_nb3_highmtb_nt0_nrt1_nw0_ht1000to1500",
  "hm_nb3_highmtb_nt0_nrt1_nw0_htgt1500",

  //1+1
  "hm_nb3_highmtb_nt1_nrt0_nw1",
  "hm_nb3_highmtb_nt1_nrt1_nw0",
  "hm_nb3_highmtb_nt0_nrt1_nw1",

  //2
  "hm_nb3_highmtb_nt2_nrt0_nw0",
  "hm_nb3_highmtb_nt0_nrt0_nw2",
  "hm_nb3_highmtb_nt0_nrt2_nw0",

  // 3
  "hm_nb3_highmtb_nrtntnwgeq3",
  
  //---------- high deltaM ----------

};

std::map<TString, std::vector<int>> mergedSSRMETbins{
//---------- low deltaM ----------
  // 0b, 0 or >=1 ivf
  {"lm_nb0_nivf0_highptisr_nj2to5",              {     750, 1000}},
  {"lm_nb0_nivf0_highptisr_nj6",                 {     550, 650, 750, 1000}},
  {"lm_nb0_nivf1_highptisr_nj2to5",              {     750, 1000}},
  {"lm_nb0_nivf1_highptisr_nj6",                 {     550, 650, 750, 1000}},

  // 1b, 0 or >=1 ivf
  {"lm_nb1_nivf0_lowmtb_highptisr_lowptb",            {550, 650, 750, 1000}},
  {"lm_nb1_nivf0_lowmtb_highptisr_medptb",            {550, 650, 750, 1000}},

  // 2b
  {"lm_nb2_lowmtb_highptisr_lowptb12",                {650, 1000}},
  {"lm_nb2_lowmtb_highptisr_medptb12",                {450, 550, 650, 1000}},
  //---------- low deltaM ----------


  //---------- high deltaM ----------
  // low mtb
  {"hm_nb1_lowmtb_nj7_nrtgeq1",                    {400, 500, 1000}},
  {"hm_nb2_lowmtb_nj7_nrtgeq1",                    {400, 500, 1000}},

  // nb2
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1000to1500",   {650, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_htgt1500",       {650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_htgt1300",       {450, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1000to1500",   {650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1500",       {650, 1000}},

  // 1+1
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1",                {550, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htlt1300",       {450, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0_htgt1300",       {450, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1",                {550, 1000}},

  // 2
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0",       	   {450, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2",                {250, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htlt1300",       {450, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0_htgt1300",       {450, 1000}},

  // 3
  {"hm_nbeq2_highmtb_nrtntnwgeq3",        	   {250, 1000}},

        // nb3
  //1 tagged
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htlt1000",         {550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_ht1000to1500",     {550, 1000}},
  {"hm_nb3_highmtb_nt1_nrt0_nw0_htgt1500",         {550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw1",                  {550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htlt1000",         {550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_ht1000to1500",     {550, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw0_htgt1500",         {550, 1000}},

  //1+1
  {"hm_nb3_highmtb_nt1_nrt0_nw1",                  {250, 1000}},
  {"hm_nb3_highmtb_nt1_nrt1_nw0",         	   {250, 350, 1000}},
  {"hm_nb3_highmtb_nt0_nrt1_nw1",                  {250, 1000}},

  //2
  {"hm_nb3_highmtb_nt2_nrt0_nw0",         	   {250, 1000}},
  {"hm_nb3_highmtb_nt0_nrt0_nw2",                  {250, 1000}},
  {"hm_nb3_highmtb_nt0_nrt2_nw0",         	   {250, 350, 1000}},

  // 3
  {"hm_nb3_highmtb_nrtntnwgeq3",                   {250, 1000}},
  
  //---------- high deltaM ----------
};


// --------------
std::vector<TString> mergedSRbins{
//---------- low deltaM ----------
  // 0b, 0 or >=1 ivf
  "lm_nb0_nivfgt0_highptisr_nj2to5",
  "lm_nb0_nivfgt0_highptisr_nj6",

  // 1b, 0 or >=1 ivf
  "lm_nb1_nivf0_lowmtb_highptisr_lowptb",
  "lm_nb1_nivf0_lowmtb_highptisr_medptb",

  // 2b
  "lm_nb2_lowmtb_highptisr_lowptb12",
  "lm_nb2_lowmtb_highptisr_medptb12",
  //---------- low deltaM ----------


  //---------- high deltaM ----------
  // low mtb
  "hm_nb1_lowmtb_nj7_nrtgeq1",
  "hm_nb2_lowmtb_nj7_nrtgeq1",

  // nb2
  // 1 tagged
  "hm_nbeq2_highmtb_nt1_nrt0_nw0_htgt1000",
  "hm_nbeq2_highmtb_nt0_nrt0_nw1_htgt1300",
  "hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1000",

  // 1+1eq
  "hm_nbeq2_highmtb_nt1_nrt0_nw1",
  "hm_nbeq2_highmtb_nt1_nrt1_nw0",
  "hm_nbeq2_highmtb_nt0_nrt1_nw1",

  // 2
  "hm_nbeq2_highmtb_nt2_nrt0_nw0",
  "hm_nbeq2_highmtb_nt0_nrt0_nw2",
  "hm_nbeq2_highmtb_nt0_nrt2_nw0",

  // 3
  "hm_nbeq2_highmtb_nrtntnwgeq3",

  // nb3
  //1 tagged
  "hm_nb3_highmtb_nrtntnw1",

  //1+1
  "hm_nb3_highmtb_nrtntnw2",

  // 3
  "hm_nb3_highmtb_nrtntnwgeq3",
  
  //---------- high deltaM ----------

};

std::map<TString, std::vector<int>> mergedSRMETbins{
//---------- low deltaM ----------
  // 0b, 0 or >=1 ivf
  {"lm_nb0_nivfgt0_highptisr_nj2to5", 	{750, 1000}},
  {"lm_nb0_nivfgt0_highptisr_nj6", 	{550, 750, 1000}},

  // 1b, 0 or >=1 ivf
  {"lm_nb1_nivf0_lowmtb_highptisr_lowptb", 	{550, 750, 1000}},
  {"lm_nb1_nivf0_lowmtb_highptisr_medptb", 	{550, 750, 1000}},

  // 2b
  {"lm_nb2_lowmtb_highptisr_lowptb12", 	{650, 1000}},
  {"lm_nb2_lowmtb_highptisr_medptb12", 	{450, 650, 1000}},
  //---------- low deltaM ----------


  //---------- high deltaM ----------
  // low mtb
  {"hm_nb1_lowmtb_nj7_nrtgeq1", 	{400, 500, 1000}},
  {"hm_nb2_lowmtb_nj7_nrtgeq1", 	{400, 500, 1000}},

  // nb2
  // 1 tagged
  {"hm_nbeq2_highmtb_nt1_nrt0_nw0_htgt1000", 	{650, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw1_htgt1300", 	{450, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1000", 	{650, 1000}},

  // 1+1eq
  {"hm_nbeq2_highmtb_nt1_nrt0_nw1", 	{550, 1000}},
  {"hm_nbeq2_highmtb_nt1_nrt1_nw0", 	{450, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt1_nw1", 	{550, 1000}},

  // 2
  {"hm_nbeq2_highmtb_nt2_nrt0_nw0", 	{450, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt0_nw2", 	{250, 1000}},
  {"hm_nbeq2_highmtb_nt0_nrt2_nw0", 	{450, 1000}},

  // 3
  {"hm_nbeq2_highmtb_nrtntnwgeq3", 	{250, 1000}},

  // nb3
  //1 tagged
  {"hm_nb3_highmtb_nrtntnw1", 	{550, 1000}},

  //1+1
  {"hm_nb3_highmtb_nrtntnw2", 	{250, 1000}},

  // 3
  {"hm_nb3_highmtb_nrtntnwgeq3", 	{250, 1000}},
  
  //---------- high deltaM ----------

};

}
#endif /* ESTTOOLS_BINDEFINITIONSDATACARD_HH_ */
