# EstTools
Standalone scripts for background estimation

General estimation methods:
```
root -l
.L LLBEstimator.C+
plot1LepCRAllEras()
LLBPredSeparate()
```

How to get final plots:
Must run datacard maker from Limits directory first.
```
root -l -b formatFinalPlots.C+
python getUncertainty.py getFinalPlot/SumOgBkg.root --printTable
root -l -b getFinalPlot.C+
```
