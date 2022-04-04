import numpy as np

import uproot

from jagged_operations import jagged_operation

class HackyJaggedArray(np.ndarray):

    def set(self, offsets=None, starts=None, stops=None):
        if offsets is not None:
            self.offsets = offsets
        elif (starts is not None) and (stops is not None):
            self.offsets = np.append(starts,stops[-1])
        else:
            raise Exception("need info dude")
        # NOTE: only need this because jagged_operation() thinks we feed in an uproot JaggedArray and checks
        # the content, offsets members.
        self.content = self
        return self

    def foreach(self, typ, idxs=None, masks=None, func=None):
        return jagged_operation(jagged_arr=self, jagged_idxs=idxs, typ=typ, masks=masks, func=func)

    """
    repr/str stolen from https://github.com/scikit-hep/uproot/blob/dc447f865db387015a7dfe10b9d8997fc032f749/uproot/interp/jagged.py#L298
    """
    def __repr__(self, indent="", linewidth=None):
        if linewidth is None:
            linewidth = np.get_printoptions()["linewidth"]
        dtypestr = repr(self.dtype).replace("(", "=").rstrip(")")
        linewidth = linewidth - 12 - 2 - len(dtypestr)
        return "jaggedarray({0})".format(self.__str__(indent=" " * 12, linewidth=linewidth))

    def __str__(self, indent="", linewidth=None):
        if linewidth is None:
            linewidth = np.get_printoptions()["linewidth"]

        def single(a):
            if len(a) > 6:
                return np.array_str(a[:3], max_line_width=np.inf).rstrip("]") + " ... " + np.array_str(a[-3:], max_line_width=np.inf).lstrip("[")
            else:
                return np.array_str(a, max_line_width=np.inf)

        if len(self.offsets) > 10:
            content = [single(self[self.offsets[i]:self.offsets[i+1]]) for i in range(3)] \
                    + ["..."] \
                    + [single(self[self.offsets[i]:self.offsets[i+1]]) for i in range(-3, -1)]
        else:
            content = [single(self[self.offsets[i]:self.offsets[i+1]]) for i in range(len(self.offsets)-1)]

        if sum(len(x) for x in content) + 2*(len(content) - 1) + 2 <= np.get_printoptions()["linewidth"]:
            return "[" + ", ".join(content) + "]"
        else:
            return "[" + (",\n " + indent).join(content) + "]"

if __name__ == "__main__":

    JaggedArray = uproot.interp.jagged.JaggedArray

    # let's pretend these are jet pts so that my examples are more motivated
    content = np.array([34.2,56.1,10.3,25.6,90.1,112.5,67.1,10.2])
    offsets = np.array([0,0,1,2,4,4,7,8])
    starts = offsets[:-1]
    stops = offsets[1:]

    uproot_ja = JaggedArray(content,starts,stops)
    print "uproot", uproot_ja

    HJA = HackyJaggedArray
    ja = content.view(HJA).set(offsets=offsets)
    print "np", ja
    print "offsets", ja.offsets
    # what's the max jetpt per event?
    print "max pts",ja.foreach("max")
    # what about HT (for jets with pt>40)?
    print "hts (pt>40)", ja.foreach("sum",masks=ja>40.0)

