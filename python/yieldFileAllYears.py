from collections import OrderedDict

beforeSel   = False
splitInputs = False

if splitInputs and not beforeSel:
  years = ["2018","2017","2016APV","2016nonAPV"]
  signals = ["Y3","DY3","DYp3","B3mL2"]
  ifilenames = []
  for y in years:
    for s in signals:
      ifilenames.append("./cpp/temp_data_"+s+"_"+y+"/yieldFile_AfterSel.txt")
  tof = open('./cpp/yieldFile_AfterSel.txt',"w")
  for ifnn,ifn in enumerate(ifilenames):
    tif = open(ifn)
    for ln,line in enumerate(tif.readlines()):
      if ifnn>0 and ln==0:
        continue
      tof.write(line)
    tif.close()
  tof.close()

ifile = open('./cpp/yieldFile_'+('Before' if beforeSel else 'After')+'Sel.txt')
ofile = open('./cpp/yieldFileAllYears_'+('Before' if beforeSel else 'After')+'Sel.txt',"w")

newWords = OrderedDict()

header = ifile.readline()
header = header[header.find(",")+1:]
for line in ifile:
  words = line.split(",")
  if beforeSel:
    if words[0]=="2018": newWords[words[1]+"_M"+words[2]] = words[1:] # Initialize with 2018
    else:
      for i in range(3,len(words)): newWords[words[1]+"_M"+words[2]][i-1] = float(newWords[words[1]+"_M"+words[2]][i-1]) + float(words[i]) # Add the other years
  else:
    if words[0]=="2018": newWords[words[1]+"_M"+words[4]] = words[1:] # Initialize with 2018
    else:
      for i in range(5,len(words)): newWords[words[1]+"_M"+words[4]][i-1] = float(newWords[words[1]+"_M"+words[4]][i-1]) + float(words[i]) # Add the other years

ofile.writelines(header)
for key in newWords:
  if not beforeSel:
    newWords[key][5] = float(newWords[key][7]) / float(newWords[key][4]) # Recalculate f, because adding them is not right
    newWords[key][15] = float(newWords[key][17]) / float(newWords[key][14]) # Recalculate f, because adding them is not right
  ofile.writelines((str(newWords[key][0])))
  for i in range(1,len(newWords[key])): ofile.writelines((","+str(newWords[key][i])))
  ofile.writelines("\n")

ifile.close()
ofile.close()
