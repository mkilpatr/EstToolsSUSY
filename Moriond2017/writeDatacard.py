import os
import math
import CombineHarvester.CombineTools.ch as ch

json_file = '/tmp/testAll.json'
outputdir = '/tmp/testDC'

def json_load_byteified(file_handle):
#     https://stackoverflow.com/questions/956867/how-to-get-string-objects-instead-of-unicode-ones-from-json-in-python/13105359#13105359
    import json
    return _byteify(
        json.load(file_handle, object_hook=_byteify),
        ignore_dicts=True
    )
def _byteify(data, ignore_dicts = False):
    # if this is a unicode string, return its string representation
    if isinstance(data, unicode):
        return data.encode('utf-8')
    # if this is a list of values, return list of byteified values
    if isinstance(data, list):
        return [ _byteify(item, ignore_dicts=True) for item in data ]
    # if this is a dictionary, return dictionary of byteified keys and values
    # but only if we haven't already byteified it
    if isinstance(data, dict) and not ignore_dicts:
        return {
            _byteify(key, ignore_dicts=True): _byteify(value, ignore_dicts=True)
            for key, value in data.iteritems()
        }
    # if it's anything else, return it in its original form
    return data

with open(json_file) as jf:
    results = json_load_byteified(jf)

binlist = results['binlist']
binMaps = results['binMaps']
yields = results['yieldsMap']
processMap = {'ttbarplusw':'lepcr', 'znunu':'phocr', 'qcd':'qcdcr'}

lepcr_binlist = yields['lepcr_data'].keys()
phocr_binlist = yields['phocr_data'].keys()
qcdcr_binlist = yields['qcdcr_data'].keys()

signals = [
#   "T2fbd_500_450",
"T2tt_1000_1",    
]

def toUnc(q):
    return 2.0 if q[0]==0 else min([1+q[1]/q[0], 2.0])

def parseBinMap(process, cr_description, yields_dict):
    values = []
    params = []
    sumE2 = 0
    for entry in cr_description.replace(' ','').split('+'):
        sr, cr = entry.split('*')
        if '<' in cr: sr, cr = cr, sr
        sr = sr.strip('<>')
        values.append(yields_dict[process][sr][0])
        sumE2 += yields_dict[process][sr][1]*yields_dict[process][sr][1]
        cr = 'R_'+cr.strip('()')
        params.append(cr)
    results = {}
    results['yield'] = (sum(values), math.sqrt(sumE2))
    parts = ['@%d*%f'%(i, values[i]) for i in range(len(values))]
    results['rateParam'] = ('(%s)'%('+'.join(parts)), ','.join(params))
    print results
    return results

def readUncs():
    pass


def writeLepcr(signal):
    for crbin in lepcr_binlist:
        cb = ch.CombineHarvester()
        print crbin
        cb.AddObservations(['*'], ['stop'], ['13TeV'], ['0l'], [(0, crbin)])
        cb.AddProcesses(procs = ['signal'],     bin = [(0, crbin)], signal=True)
        cb.AddProcesses(procs = ['ttbarplusw'], bin = [(0, crbin)], signal=False)
        cb.ForEachObs(lambda obs : obs.set_rate(yields['lepcr_data'][crbin][0]))
        cb.cp().process(['ttbarplusw']).ForEachProc(lambda p : p.set_rate(yields['lepcr_ttbarplusw'][crbin][0]))
        cb.cp().process(['signal']).ForEachProc(lambda p : p.set_rate(yields['lepcr_'+signal][crbin][0]))
        # uncs
        cb.cp().process(['ttbarplusw']).AddSyst(cb, "R_$BIN", "rateParam", ch.SystMap()(1.0))
        cb.AddSyst(cb, "mcstats_$PROCESS_$BIN", "lnN", ch.SystMap('process')
                   (['ttbarplusw'], toUnc(yields['lepcr_ttbarplusw'][crbin]))
                   (['signal'],     toUnc(yields['lepcr_'+signal][crbin]))
                   )
        # FIXME: add syst uncs
        cb.WriteDatacard(os.path.join(outputdir, signal, '%s.txt'%crbin))

def writePhocr(signal):
    for crbin in phocr_binlist:
        cb = ch.CombineHarvester()
        print crbin
        cb.AddObservations(['*'], ['stop'], ['13TeV'], ['0l'], [(0, crbin)])
        cb.AddProcesses(procs = ['gjets'], bin = [(0, crbin)], signal=False)
        cb.ForEachObs(lambda obs : obs.set_rate(yields['phocr_data'][crbin][0]))
        cb.cp().process(['gjets']).ForEachProc(lambda p : p.set_rate(yields['phocr_gjets'][crbin][0]))
        # uncs
        cb.cp().process(['gjets']).AddSyst(cb, "R_$BIN", "rateParam", ch.SystMap()(1.0))
        cb.AddSyst(cb, "mcstats_gjets_$BIN", "lnN", ch.SystMap()(toUnc(yields['phocr_gjets'][crbin])))
        # FIXME: add syst uncs
        cb.WriteDatacard(os.path.join(outputdir, signal, '%s.txt'%crbin))

def writeQCDcr(signal):
    for crbin in qcdcr_binlist:
        cb = ch.CombineHarvester()
        print crbin
        cb.AddObservations(['*'], ['stop'], ['13TeV'], ['0l'], [(0, crbin)])
        cb.AddProcesses(procs = ['qcd', 'otherbkgs'], bin = [(0, crbin)], signal=False)
        cb.ForEachObs(lambda obs : obs.set_rate(yields['qcdcr_data'][crbin][0]))
        cb.cp().process(['qcd']).ForEachProc(lambda p : p.set_rate(yields['qcdcr_qcd'][crbin][0]))
        cb.cp().process(['otherbkgs']).ForEachProc(lambda p : p.set_rate(yields['qcdcr_otherbkgs'][crbin][0]))
        # uncs
        cb.cp().process(['qcd']).AddSyst(cb, "R_$BIN", "rateParam", ch.SystMap()(1.0))
        cb.AddSyst(cb, "mcstats_$PROCESS_$BIN", "lnN", ch.SystMap('process')
                   (['qcd'],        toUnc(yields['qcdcr_qcd'][crbin]))
                   (['otherbkgs'],  2.0)
                   )
        # FIXME: add syst uncs
        cb.WriteDatacard(os.path.join(outputdir, signal, '%s.txt'%crbin))

def writeSR(signal):
    mergedbins = [bin for bin in binlist if '+' in binMaps['lepcr'][bin]]
    for bin in binlist:
        rateParamFixes = {}
        cb = ch.CombineHarvester()
        print bin
        cb.AddObservations(['*'], ['stop'], ['13TeV'], ['0l'], [(0, bin)])
        cb.AddProcesses(procs = ['signal'],     bin = [(0, bin)], signal=True)
        cb.AddProcesses(procs = ['ttbarplusw', 'znunu', 'qcd', 'ttZ', 'diboson'], bin = [(0, bin)], signal=False)
        cb.ForEachObs(lambda obs : obs.set_rate(yields['data'][bin][0]))
        cb.cp().process(['signal']).ForEachProc(lambda p : p.set_rate(yields[signal][bin][0]))
        cb.cp().process(['ttZ','diboson']).ForEachProc(lambda p : p.set_rate(yields[p.process()][bin][0]))
        cb.cp().process(['signal','ttZ','diboson']).AddSyst(cb, "mcstats_$PROCESS_$BIN", "lnN", ch.SystMap('process')
                   (['signal'],         toUnc(yields[signal][bin]))
                   (['ttZ'],            toUnc(yields['ttZ'][bin]))
                   (['diboson'],        toUnc(yields['diboson'][bin]))
                   )
        if bin not in mergedbins:
            # one to one CR
            cb.cp().process(['ttbarplusw','znunu','qcd']).ForEachProc(lambda p : p.set_rate(yields[p.process()][bin][0]))
            cb.cp().process(['ttbarplusw']).AddSyst(cb, "R_%s"%binMaps['lepcr'][bin], "rateParam", ch.SystMap()(1.0))
            cb.cp().process(['znunu'     ]).AddSyst(cb, "R_%s"%binMaps['phocr'][bin], "rateParam", ch.SystMap()(1.0))
            cb.cp().process(['qcd'       ]).AddSyst(cb, "R_%s"%binMaps['qcdcr'][bin], "rateParam", ch.SystMap()(1.0))
            cb.cp().process(['ttbarplusw','znunu','qcd']).AddSyst(cb, "mcstats_$PROCESS_$BIN", "lnN", ch.SystMap('process')
                       (['ttbarplusw'],     toUnc(yields['ttbarplusw'][bin]))
                       (['znunu'],          toUnc(yields['znunu'][bin]))
                       (['qcd'],            toUnc(yields['qcd'][bin]))
                       )
        else:
            cb.cp().process(['ttbarplusw','znunu','qcd']).ForEachProc(lambda p : p.set_rate(1))
            for proc in ['ttbarplusw','znunu','qcd']:
                rlt = parseBinMap(proc, binMaps[processMap[proc]][bin], yields)
                rName = "R_%s_%s"%(proc, bin)
                cb.cp().process([proc]).AddSyst(cb, rName, "rateParam", ch.SystMap()(999999.0)) # error if put formula here: need a workaround
                rateParamFixes[rName] = rlt['rateParam']
                cb.cp().process([proc]).AddSyst(cb, "mcstats_$PROCESS_$BIN", "lnN", ch.SystMap('process')
                        ([proc],            toUnc(rlt['yield']))
                        )
        # FIXME: add syst uncs
        cb.WriteDatacard(os.path.join(outputdir, signal, '%s.tmp'%bin)) # write to a tmp file first
        with open(os.path.join(outputdir, signal, '%s.tmp'%bin)) as tmpfile:
            with open(os.path.join(outputdir, signal, '%s.txt'%bin), 'w') as dc:
                for line in tmpfile:
                    for rName in rateParamFixes:
                        if rName not in line: continue
                        line = line.replace('999999', ' '.join(rateParamFixes[rName]))
                        break
                    dc.write(line)
        os.remove(os.path.join(outputdir, signal, '%s.tmp'%bin))
        

for sig in signals:
    dest = os.path.join(outputdir, sig)
    if not os.path.exists(dest):
        os.makedirs(dest)
    writeLepcr(sig)
    writePhocr(sig)
    writeQCDcr(sig)
    writeSR(sig)