#ifndef WIDTHS_H
#define WIDTHS_H

#include <map>
#include <vector>
#include <iostream>
#include <TString.h>

using namespace std;

map<TString,map<TString,float>> widths = { };

inline void reset_widths() {
	widths.clear();
}
inline void set_widths() {
	widths.insert({"Y3", {}});
	widths["Y3"].insert({"100", 0.000872});
	widths["Y3"].insert({"200", 0.004015});
	widths["Y3"].insert({"400", 0.049430});
	widths["Y3"].insert({"700", 0.306252});
	widths["Y3"].insert({"1000", 0.913002});
	widths["Y3"].insert({"1500", 3.114878});
	widths["Y3"].insert({"2000", 7.410280});
	widths.insert({"DY3", {}});
	widths["DY3"].insert({"100", 0.002599});
	widths["DY3"].insert({"200", 0.017882});
	widths["DY3"].insert({"400", 0.157854});
	widths["DY3"].insert({"700", 0.888927});
	widths["DY3"].insert({"1000", 2.613129});
	widths["DY3"].insert({"1500", 8.855362});
	widths["DY3"].insert({"2000", 21.019506});
	widths.insert({"DYp3", {}});
	widths["DYp3"].insert({"100", 0.000849});
	widths["DYp3"].insert({"200", 0.005838});
	widths["DYp3"].insert({"400", 0.051549});
	widths["DYp3"].insert({"700", 0.290284});
	widths["DYp3"].insert({"1000", 0.853301});
	widths["DYp3"].insert({"1500", 2.891601});
	widths["DYp3"].insert({"2000", 6.863586});
	widths.insert({"B3mL2", {}});
	widths["B3mL2"].insert({"100", 0.001072});
	widths["B3mL2"].insert({"200", 0.008755});
	widths["B3mL2"].insert({"400", 0.078932});
	widths["B3mL2"].insert({"700", 0.441860});
	widths["B3mL2"].insert({"1000", 1.291954});
	widths["B3mL2"].insert({"1500", 4.363471});
	widths["B3mL2"].insert({"2000", 10.344343});
}

#endif
