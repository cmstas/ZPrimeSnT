from collections import OrderedDict

beforeSel = False

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
