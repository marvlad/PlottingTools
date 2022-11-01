CXX = g++ 
#CXXFLAGS = -g -Wall -fPIC -Werror
CXXFLAGS = -g -Wall -fPIC
ROOTFLAGS = `root-config --cflags --glibs --libs`

BINARIES = GetHist 

GetHist: GetHist.cpp
	$(CXX) $(CXXFLAGS) $(ROOTFLAGS) GetHist.cpp -o GetHist


.PHONY: clean

clean:
	rm -f $(BINARIES)
