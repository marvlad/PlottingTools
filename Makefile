CXX = g++ 
#CXXFLAGS = -g -Wall -fPIC -Werror
CXXFLAGS = -g -Wall -fPIC
ROOTFLAGS = `root-config --cflags --glibs --libs`
#INCLUDE = -I$(MECCOMMON)/ -I$(PLOTUTILSROOT)/ -I$(UNFOLDUTILSROOT)/
#LDLIBS = -L$(ROOTSYS)/lib -lHistPainter -lCintex -L$(PLOTUTILSROOT)/$(CMTCONFIG) -lplotutils -L$(UNFOLDUTILSROOT)/$(CMTCONFIG) -lUnfoldUtils

BINARIES = GetHist 

GetHist: GetHist.cpp
	$(CXX) $(CXXFLAGS) $(ROOTFLAGS) GetHist.cpp -o GetHist


.PHONY: clean

clean:
	rm -f $(BINARIES)
