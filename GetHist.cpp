#include <iostream>
#include <fstream>
#include "TH1D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TRandom.h"

using namespace std;
int channels = 60;

// To add color to the histograms
int randomColor(int seed){
	//Color taken from https://davidmathlogic.com/colorblind/#%23FEFE62-%23D35FB7
        std::string CB_colors[23] = {"#D41159", "#FFC20A", "#0C7BDC", "#E1BE6A", "#40B0A6",
                                     "#1AFF1A", "#4B0092", "#005AB5", "#DC3220", "#994F00",
                                     "#006CD1", "#E66100", "#5D3A9B", "#FEFE62", "#D35FB7",
                                     "#1A85FF", "#2E4052", "#6FDE6E", "#848FA2", "#929084",
                                     "#235FA4","#BDD9BF","#004949"};
	TColor color;
	static Int_t c_index;
	TRandom *RN = new TRandom(seed);
	int val = RN->Integer(23);
	c_index = color.GetColor(CB_colors[val].c_str());
	return c_index;
}

void make_plot(std::string outnamef="Report_date_here"){
    cout<<"---------------------------------------------\n";
    cout<<" Reading rootfile and making plots, wait.... \n";
    cout<<"---------------------------------------------\n";

    system("mkdir plots");
    std::string filename_output = "Report_"+outnamef+".root";
    TFile *o = new TFile(filename_output.c_str(),"RECREATE");
    TFile *f = TFile::Open("../WaveForms_rawblsub.root");

    std::string hist1 = "wavs/wav_ch";
    std::string hist2 = "_wav0_evt";
    for(int i = 0; i < channels; i++){
        TCanvas *c = new TCanvas("c","c",1700.,500.);
        for(int j=0; j < 400; j++){
            int val = 1000 + i;
            //int val = i;
            std::string name = hist1 + std::to_string(val) + hist2 + std::to_string(j);
            //cout<<"Getting "<<name.c_str()<<endl;
            TH1D* h = (TH1D*)f->Get(name.c_str());
	          h->SetLineColor(randomColor(i+j));
            h->SetLineWidth(2);
	          h->SetStats(0);
            if(j==0){
                h->GetYaxis()->SetTitle("Amplitude [mV]");
                h->GetXaxis()->SetTitle("Time [ps]");
                //h->GetXaxis()->SetRangeUser(1000,5000);
                if(i==5) h->GetYaxis()->SetRangeUser(-400,400);
                if((i==35)||(i==5)) h->GetYaxis()->SetRangeUser(-400,400);
                else h->GetYaxis()->SetRangeUser(-100,100);
            }
            h->Draw(j==0 ? "hist l" : "hist l same");
        }
        std::string outname = "./plots/C_"+std::to_string(i)+".png";
        c->SaveAs(outname.c_str());
        o->cd();
        c->Write();
	      delete c;
    }
}

void make_inform(std::string title="this is a random title", std::string report="date_here"){
	
	cout<<"---------------------------------------------\n";
	cout<<" Making report, wait.....                    \n";
	cout<<"---------------------------------------------\n";
	std::string loop = "0";
	for(int i = 0; i<channels-1; i++){ loop += ", "+std::to_string(i+1);}

	std::string latex  = "\\documentclass{beamer} \n";
		    latex += "\\usepackage{hyperref} \n";
		    latex += "\\usepackage[utf8]{inputenc} \n";
		    latex += "\\usepackage{xcolor} \n";
		    latex += "\\usepackage{pgffor} \n";
		    latex += "\n";
		    latex += "\\begin{document} \n";
		    latex += "\\title{"+title+"} \n";
		    latex += "\\date{\\today} \n";
		    latex += "\n";
		    latex += "\\frame{\\titlepage} \n";
		    latex += "\\section{Section 1} \n";
		    latex += "\\foreach \\n in {"+loop+"}{ \n";
		    latex += "\\begin{frame} \n";
		    latex += "\\frametitle{Channel $\\text{\\n}$} \n";
		    latex += "\\begin{figure} \n";
		    latex += "\\begin{center} \n";
		    latex += "\\includegraphics[scale=0.2]{./plots/C_\\n.png} \n";
		    latex += "\\end{center} \n";
		    latex += "\\end{figure} \n";
		    latex += "\\end{frame} \n";
		    latex += "} \n";
		    latex += "\\end{document} \n";
		
	ofstream myfile;
	std::string filename = "Report_"+report+".tex";
	myfile.open (filename.c_str());
	myfile << latex;
	myfile.close();
	std::string run = "pdflatex "+filename+" > NUL 2>&1";
	system(run.c_str());
	system("rm *.aux *.log *.out *.snm *.toc *.nav *.tex NUL");
	cout<<" done!\n";

}

int main(int argc, char *argv[])
{
 if (argc < 2) {
        printf("Error: missing command line arguments. It must be ");
        printf("./GetHist [file_name] [title description]\n");
        printf("Example: ./GetHist 10312022 \"This data was taken on Friday, 10292022 bla bla bla bla\" \n");
        return 1;
 }

 std::string filename = "date_here";
 std::string title = "[This a random title]";
 
 filename = std::string(argv[1]);
 title = std::string(argv[2]);
  
 make_plot(filename);
 make_inform(title,filename);

 return 0;
}
