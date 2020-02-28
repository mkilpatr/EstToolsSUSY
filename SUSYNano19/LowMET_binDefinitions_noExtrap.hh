#ifndef ESTTOOLS_LMBINDEFINITIONS_HH_
#define ESTTOOLS_LMBINDEFINITIONS_HH_

namespace EstTools{

std::vector<TString> srbins{
//---------- low deltaM ----------
  // 0b, 0 or >=1 ivf
  "lm_nb0_nivf0_highptisr_nj2to5_met400",
  "lm_nb0_nivf0_highptisr_nj6_met400",
  "lm_nb0_nivf1_highptisr_nj2to5_met400",
  "lm_nb0_nivf1_highptisr_nj6_met400",

  // 1b, 0 or >=1 ivf
  "lm_nb1_nivf0_lowmtb_lowptisr_lowptb_met300",
  "lm_nb1_nivf0_lowmtb_lowptisr_medptb_met300",
  "lm_nb1_nivf0_lowmtb_highptisr_lowptb_met400",
  "lm_nb1_nivf0_lowmtb_highptisr_medptb_met400",
  // ---
  "lm_nb1_nivf1_lowmtb_medptisr_lowptb_met300",

  // 2b
  "lm_nb2_lowmtb_lowptisr_lowptb12_met300",
  "lm_nb2_lowmtb_lowptisr_medptb12_met300",
  "lm_nb2_lowmtb_lowptisr_highptb12_nj7_met300",
  "lm_nb2_lowmtb_highptisr_lowptb12_met400",
  "lm_nb2_lowmtb_highptisr_medptb12_met400",
  "lm_nb2_lowmtb_highptisr_highptb12_nj7_met400",

  // Additional from Hui
  // 0b
  "lmVal_nb0_lowmtb_nivf0",
  "lmVal_nb0_lowmtb_nivf1",
  "lmVal_nbgeq1_lowmtb_nivf0",
  "lmVal_nbgeq1_lowmtb_nivf1",
  //---------- low deltaM ----------


  //---------- high deltaM ----------
  // low mtb
  "hmVal_nb1_lowmtb_nj7_nrtgeq1",
  "hmVal_nb2_lowmtb_nj7_nrtgeq1",

  // high mtb
  // 0 taggged
  "hmVal_nb1_highmtb_nj5_nt0_nrt0_nw0",
  "hmVal_nb2_highmtb_nj5_nt0_nrt0_nw0",

	// nb1
  // 1 tagged
  "hmVal_nb1_highmtb_nt1_nrt0_nw0",
  "hmVal_nb1_highmtb_nt0_nrt0_nw1",
  "hmVal_nb1_highmtb_nt0_nrt1_nw0",

  // 1+1
  "hmVal_nb1_highmtb_nrtntnwgeq2",

	// nb2
  // 1 tagged
  "hmVal_nb2_highmtb_nt1_nrt0_nw0",
  "hmVal_nb2_highmtb_nt0_nrt0_nw1",
  "hmVal_nb2_highmtb_nt0_nrt1_nw0",

  // 1+1
  "hmVal_nb2_highmtb_nrtntnwgeq2",
  
  //---------- high deltaM ----------
};

std::map<TString, std::vector<int>> srMETbins{
//---------- low deltaM ----------
  // 0b, 0 or >=1 ivf
  {"lm_nb0_nivf0_highptisr_nj2to5_met400", 		{250, 400}},
  {"lm_nb0_nivf0_highptisr_nj6_met400", 		{250, 400}},
  {"lm_nb0_nivf1_highptisr_nj2to5_met400", 		{250, 400}},
  {"lm_nb0_nivf1_highptisr_nj6_met400", 		{250, 400}},

  // 1b, 0 or >=1 ivf
  {"lm_nb1_nivf0_lowmtb_lowptisr_lowptb_met300", 	{250, 300}},
  {"lm_nb1_nivf0_lowmtb_lowptisr_medptb_met300", 	{250, 300}},
  {"lm_nb1_nivf0_lowmtb_highptisr_lowptb_met400", 	{250, 400}},
  {"lm_nb1_nivf0_lowmtb_highptisr_medptb_met400", 	{250, 400}},
  // ---
  {"lm_nb1_nivf1_lowmtb_medptisr_lowptb_met300", 	{250, 300}},

  // 2b
  {"lm_nb2_lowmtb_lowptisr_lowptb12_met300", 		{250, 300}},
  {"lm_nb2_lowmtb_lowptisr_medptb12_met300", 		{250, 300}},
  {"lm_nb2_lowmtb_lowptisr_highptb12_nj7_met300", 	{250, 300}},
  {"lm_nb2_lowmtb_highptisr_lowptb12_met400", 		{250, 400}},
  {"lm_nb2_lowmtb_highptisr_medptb12_met400", 		{250, 400}},
  {"lm_nb2_lowmtb_highptisr_highptb12_nj7_met400", 	{250, 400}},

  // Additional from Hui
  // 0b
  {"lmVal_nb0_lowmtb_nivf0", 		{250, 1000}},
  {"lmVal_nb0_lowmtb_nivf1", 		{250, 1000}},
  {"lmVal_nbgeq1_lowmtb_nivf0", 	{250, 1000}},
  {"lmVal_nbgeq1_lowmtb_nivf1", 	{250, 1000}},
  //---------- low deltaM ----------


  //---------- high deltaM ----------
  // low mtb
  {"hmVal_nb1_lowmtb_nj7_nrtgeq1", 		{250, 400, 1000}},
  {"hmVal_nb2_lowmtb_nj7_nrtgeq1", 		{250, 400, 1000}},

  // high mtb
  // 0 taggged
  {"hmVal_nb1_highmtb_nj5_nt0_nrt0_nw0", 		{250, 400, 1000}},
  {"hmVal_nb2_highmtb_nj5_nt0_nrt0_nw0", 		{250, 400, 1000}},

	// nb1
  // 1 tagged
  {"hmVal_nb1_highmtb_nt1_nrt0_nw0", 		{250, 400, 1000}},
  {"hmVal_nb1_highmtb_nt0_nrt0_nw1", 		{250, 400, 1000}},
  {"hmVal_nb1_highmtb_nt0_nrt1_nw0", 		{250, 400, 1000}},

  // 1+1
  {"hmVal_nb1_highmtb_nrtntnwgeq2", 		{250, 400, 1000}},

	// nb2
  // 1 tagged
  {"hmVal_nb2_highmtb_nt1_nrt0_nw0", 		{250, 400, 1000}},
  {"hmVal_nb2_highmtb_nt0_nrt0_nw1", 		{250, 400, 1000}},
  {"hmVal_nb2_highmtb_nt0_nrt1_nw0", 		{250, 400, 1000}},

  // 1+1
  {"hmVal_nb2_highmtb_nrtntnwgeq2", 		{250, 400, 1000}},
  
  //---------- high deltaM ----------

};

std::map<TString, TString> phocrMapping{
//---------- low deltaM ----------
  // 0b, 0 or >=1 ivf
  {"lm_nb0_nivf0_highptisr_nj2to5_met400",        "lm_nb0_nivf0_highptisr_nj2to5_met400"},
  {"lm_nb0_nivf0_highptisr_nj6_met400",           "lm_nb0_nivf0_highptisr_nj6_met400"},
  {"lm_nb0_nivf1_highptisr_nj2to5_met400",        "lm_nb0_nivf1_highptisr_nj2to5_met400"},
  {"lm_nb0_nivf1_highptisr_nj6_met400",           "lm_nb0_nivf1_highptisr_nj6_met400"},
                                            
  // 1b, 0 or >=1 ivf                     
  {"lm_nb1_nivf0_lowmtb_lowptisr_lowptb_met300",  "lm_nb1_nivf0_lowmtb_lowptisr_lowptb_met300"},
  {"lm_nb1_nivf0_lowmtb_lowptisr_medptb_met300",  "lm_nb1_nivf0_lowmtb_lowptisr_medptb_met300"},
  {"lm_nb1_nivf0_lowmtb_highptisr_lowptb_met400", "lm_nb1_nivf0_lowmtb_highptisr_lowptb_met400"},
  {"lm_nb1_nivf0_lowmtb_highptisr_medptb_met400", "lm_nb1_nivf0_lowmtb_highptisr_medptb_met400"},
  // ---                                 
  {"lm_nb1_nivf1_lowmtb_medptisr_lowptb_met300",  "lm_nb1_nivf1_lowmtb_medptisr_lowptb_met300"},
                                            
  // 2b                                 
  {"lm_nb2_lowmtb_lowptisr_lowptb12_met300",      "lm_nb2_lowmtb_lowptisr_lowptb12_met300"},
  {"lm_nb2_lowmtb_lowptisr_medptb12_met300",      "lm_nb2_lowmtb_lowptisr_medptb12_met300"},
  {"lm_nb2_lowmtb_lowptisr_highptb12_nj7_met300", "lm_nb2_lowmtb_lowptisr_highptb12_nj7_met300"},
  {"lm_nb2_lowmtb_highptisr_lowptb12_met400",     "lm_nb2_lowmtb_highptisr_lowptb12_met400"},
  {"lm_nb2_lowmtb_highptisr_medptb12_met400",     "lm_nb2_lowmtb_highptisr_medptb12_met400"},
  {"lm_nb2_lowmtb_highptisr_highptb12_nj7_met400","lm_nb2_lowmtb_highptisr_highptb12_nj7_met400"},
                                            
  // Additional from Hui               
  // 0b                               
  {"lmVal_nb0_lowmtb_nivf0",     "lmVal_nb0_lowmtb_nivf0"},
  {"lmVal_nb0_lowmtb_nivf1",     "lmVal_nb0_lowmtb_nivf1"},
  {"lmVal_nbgeq1_lowmtb_nivf0",   "lmVal_nbgeq1_lowmtb_nivf0"},
  {"lmVal_nbgeq1_lowmtb_nivf1",   "lmVal_nbgeq1_lowmtb_nivf1"},
  //---------- low deltaM ---------- 
                                            
                                            
  //---------- high deltaM ---------- 
  // low mtb                         
  {"hmVal_nb1_lowmtb_nj7_nrtgeq1",            "hmVal_nb1_lowmtb_nj7_nrtgeq1"},
  {"hmVal_nb2_lowmtb_nj7_nrtgeq1",            "hmVal_nb2_lowmtb_nj7_nrtgeq1"},
                                            
  // high mtb                       
  // 0 taggged                     
  {"hmVal_nb1_highmtb_nj5_nt0_nrt0_nw0",      "hmVal_nb1_highmtb_nj5_nt0_nrt0_nw0"},
  {"hmVal_nb2_highmtb_nj5_nt0_nrt0_nw0",      "hmVal_nb2_highmtb_nj5_nt0_nrt0_nw0"},
                                            
        // nb1                    
  // 1 tagged                    
  {"hmVal_nb1_highmtb_nt1_nrt0_nw0",          "hmVal_nb1_highmtb_nt1_nrt0_nw0"},
  {"hmVal_nb1_highmtb_nt0_nrt0_nw1",          "hmVal_nb1_highmtb_nt0_nrt0_nw1"},
  {"hmVal_nb1_highmtb_nt0_nrt1_nw0",          "hmVal_nb1_highmtb_nt0_nrt1_nw0"},
                                            
  // 1+1                        
  {"hmVal_nb1_highmtb_nrtntnwgeq2",           "hmVal_nb1_highmtb_nrtntnwgeq2"},
                                            
        // nb2                 
  // 1 tagged                 
  {"hmVal_nb2_highmtb_nt1_nrt0_nw0",          "hmVal_nb2_highmtb_nt1_nrt0_nw0"},
  {"hmVal_nb2_highmtb_nt0_nrt0_nw1",          "hmVal_nb2_highmtb_nt0_nrt0_nw1"},
  {"hmVal_nb2_highmtb_nt0_nrt1_nw0",          "hmVal_nb2_highmtb_nt0_nrt1_nw0"},
                                            
  // 1+1                     
  {"hmVal_nb2_highmtb_nrtntnwgeq2",           "hmVal_nb2_highmtb_nrtntnwgeq2"},         
  
  //---------- high deltaM ----------
};

std::map<TString, TString> lepcrMapping {
//---------- low deltaM ----------
  // 0b, 0 or >=1 ivf
  {"lm_nb0_nivf0_highptisr_nj2to5_met400",        "lm_nb0_nivf0_highptisr_nj2to5_met400"},
  {"lm_nb0_nivf0_highptisr_nj6_met400",           "lm_nb0_nivf0_highptisr_nj6_met400"},
  {"lm_nb0_nivf1_highptisr_nj2to5_met400",        "lm_nb0_nivf1_highptisr_nj2to5_met400"},
  {"lm_nb0_nivf1_highptisr_nj6_met400",           "lm_nb0_nivf1_highptisr_nj6_met400"},
                                            
  // 1b, 0 or >=1 ivf                     
  {"lm_nb1_nivf0_lowmtb_lowptisr_lowptb_met300",  "lm_nb1_nivf0_lowmtb_lowptisr_lowptb_met300"},
  {"lm_nb1_nivf0_lowmtb_lowptisr_medptb_met300",  "lm_nb1_nivf0_lowmtb_lowptisr_medptb_met300"},
  {"lm_nb1_nivf0_lowmtb_highptisr_lowptb_met400", "lm_nb1_nivf0_lowmtb_highptisr_lowptb_met400"},
  {"lm_nb1_nivf0_lowmtb_highptisr_medptb_met400", "lm_nb1_nivf0_lowmtb_highptisr_medptb_met400"},
  // ---                                 
  {"lm_nb1_nivf1_lowmtb_medptisr_lowptb_met300",  "lm_nb1_nivf1_lowmtb_medptisr_lowptb_met300"},
                                            
  // 2b                                 
  {"lm_nb2_lowmtb_lowptisr_lowptb12_met300",      "lm_nb2_lowmtb_lowptisr_lowptb12_met300"},
  {"lm_nb2_lowmtb_lowptisr_medptb12_met300",      "lm_nb2_lowmtb_lowptisr_medptb12_met300"},
  {"lm_nb2_lowmtb_lowptisr_highptb12_nj7_met300", "lm_nb2_lowmtb_lowptisr_highptb12_nj7_met300"},
  {"lm_nb2_lowmtb_highptisr_lowptb12_met400",     "lm_nb2_lowmtb_highptisr_lowptb12_met400"},
  {"lm_nb2_lowmtb_highptisr_medptb12_met400",     "lm_nb2_lowmtb_highptisr_medptb12_met400"},
  {"lm_nb2_lowmtb_highptisr_highptb12_nj7_met400","lm_nb2_lowmtb_highptisr_highptb12_nj7_met400"},
                                            
  // Additional from Hui               
  // 0b                               
  {"lmVal_nb0_lowmtb_nivf0",     "lmVal_nb0_lowmtb_nivf0"},
  {"lmVal_nb0_lowmtb_nivf1",     "lmVal_nb0_lowmtb_nivf1"},
  {"lmVal_nbgeq1_lowmtb_nivf0",   "lmVal_nbgeq1_lowmtb_nivf0"},
  {"lmVal_nbgeq1_lowmtb_nivf1",   "lmVal_nbgeq1_lowmtb_nivf1"},
  //---------- low deltaM ---------- 
                                            
                                            
  //---------- high deltaM ---------- 
  // low mtb                         
  {"hmVal_nb1_lowmtb_nj7_nrtgeq1",            "hmVal_nb1_lowmtb_nj7_nrtgeq1"},
  {"hmVal_nb2_lowmtb_nj7_nrtgeq1",            "hmVal_nb2_lowmtb_nj7_nrtgeq1"},
                                            
  // high mtb                       
  // 0 taggged                     
  {"hmVal_nb1_highmtb_nj5_nt0_nrt0_nw0",      "hmVal_nb1_highmtb_nj5_nt0_nrt0_nw0"},
  {"hmVal_nb2_highmtb_nj5_nt0_nrt0_nw0",      "hmVal_nb2_highmtb_nj5_nt0_nrt0_nw0"},
                                            
        // nb1                    
  // 1 tagged                    
  {"hmVal_nb1_highmtb_nt1_nrt0_nw0",          "hmVal_nb1_highmtb_nt1_nrt0_nw0"},
  {"hmVal_nb1_highmtb_nt0_nrt0_nw1",          "hmVal_nb1_highmtb_nt0_nrt0_nw1"},
  {"hmVal_nb1_highmtb_nt0_nrt1_nw0",          "hmVal_nb1_highmtb_nt0_nrt1_nw0"},
                                            
  // 1+1                        
  {"hmVal_nb1_highmtb_nrtntnwgeq2",           "hmVal_nb1_highmtb_nrtntnwgeq2"},
                                            
        // nb2                 
  // 1 tagged                 
  {"hmVal_nb2_highmtb_nt1_nrt0_nw0",          "hmVal_nb2_highmtb_nt1_nrt0_nw0"},
  {"hmVal_nb2_highmtb_nt0_nrt0_nw1",          "hmVal_nb2_highmtb_nt0_nrt0_nw1"},
  {"hmVal_nb2_highmtb_nt0_nrt1_nw0",          "hmVal_nb2_highmtb_nt0_nrt1_nw0"},
                                            
  // 1+1                     
  {"hmVal_nb2_highmtb_nrtntnwgeq2",           "hmVal_nb2_highmtb_nrtntnwgeq2"},         
  
  //---------- high deltaM ----------
};

}
#endif /* ESTTOOLS_LMBINDEFINITIONS_HH_ */
