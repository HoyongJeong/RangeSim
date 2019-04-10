////////////////////////////////////////////////////////////////////////////////
//   < DrawHist.C >                                                           //
//                                                                            //
//   Histogram drawing script.                                                //
//   - Argument explanation                                                   //
//     i)  range: Used to determine range histogram's x axis. Unit is mm.     //
//     ii) beamE: Used to determine eDep histogram;s x axis. Unit is MeV.     //
//                                                                            //
//                        2019. 3. 26. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "TString.h"
#include "TChain.h"
#include "TH1D.h"
#include "TCanvas.h"

void DrawHist(const Double_t range = 400., const Double_t beamE = 250.)
{
	// Cut
	const Double_t cut = beamE * 0.99; // 99 percent. You can change it.

	// Load data
	TString fileName = "Scint-250-2019-03-29_17-01-25";
	std::cout << "\033[1;33m[Notice] " << fileName.Data();
	std::cout << " will be processed.\033[0m" << std::endl;
	TString dataName = "../" + fileName + "*.root";
	TChain* data = new TChain("data");
	if ( !data -> Add(dataName.Data()) )
	{
		std::cerr << "\033[1;31m[Error] Fail to open file. ";
		std::cerr << "Check file name is right.\033[0m" << std::endl;
		return;
	}
	Int_t nEvents = data -> GetEntries();

	// Link addresses
	Int_t eventID = 0;
	Double_t eDepTotal = 0.;
	Double_t pathTotal = 0.;
	Double_t posXFinal = 0.;
	Double_t posYFinal = 0.;
	Double_t posZFinal = 0.;
	Double_t timeFinal = 0.;
	vector<Double_t>* eKinHistory = 0;
	vector<Double_t>* posXHistory = 0;
	vector<Double_t>* posYHistory = 0;
	vector<Double_t>* posZHistory = 0;
	vector<Double_t>* timeHistory = 0;
	data -> SetBranchAddress("eventID"    , &eventID    );
	data -> SetBranchAddress("eDepTotal"  , &eDepTotal  );
	data -> SetBranchAddress("pathTotal"  , &pathTotal  );
	data -> SetBranchAddress("posXFinal"  , &posXFinal  );
	data -> SetBranchAddress("posYFinal"  , &posYFinal  );
	data -> SetBranchAddress("posZFinal"  , &posZFinal  );
	data -> SetBranchAddress("timeFinal"  , &timeFinal  );
	data -> SetBranchAddress("eKinHistory", &eKinHistory);
	data -> SetBranchAddress("posXHistory", &posXHistory);
	data -> SetBranchAddress("posYHistory", &posYHistory);
	data -> SetBranchAddress("posZHistory", &posZHistory);
	data -> SetBranchAddress("timeHistory", &timeHistory);

	// Define histograms
	TH1D* hEDep   = new TH1D("hEDep"  , "Energy Deposition", nEvents / 100, 0, beamE*1.1);
	TH1D* hRange  = new TH1D("hRange" , "Range"            , nEvents / 100, 0,     range);
	TH1D* hRangeP = new TH1D("hRangeP", "Projected Range"  , nEvents / 100, 0,     range);
	hEDep   -> SetFillColor(kGreen);
	hRange  -> SetFillColor(kYellow);
	hRangeP -> SetFillColor(kOrange);

	// Looping over entries
	std::cout << "\033[1;33m[Notice] " << nEvents;
	std::cout << " events are going to be processed.\033[0m" << std::endl;
	for ( Int_t i = 0; i < nEvents; i++ )
	{
		// Get i-th entry
		data -> GetEntry(i);

		// Fill hists
		hEDep -> Fill(eDepTotal);
		if ( eDepTotal > cut ) // EDep cut
		{
			hRange  -> Fill(pathTotal);
			hRangeP -> Fill(posZFinal);
		}
	}

	// Prepare canvas
	TCanvas* c1 = new TCanvas("c1", "EDep and Range", 1800, 600);
	c1 -> Divide(3, 1);

	// Draw
	c1 -> cd(1) -> SetLogy();
	c1 -> cd(1) -> SetGrid();
	hEDep   -> Draw();
	c1 -> cd(2) -> SetLogy();
	c1 -> cd(2) -> SetGrid();
	hRange  -> Draw();
	c1 -> cd(3) -> SetLogy();
	c1 -> cd(3) -> SetGrid();
	hRangeP -> Draw();

	// Style
	hEDep   -> GetXaxis() -> SetTitle("E (MeV)");
	hRange  -> GetXaxis() -> SetTitle("R (mm)" );
	hRangeP -> GetXaxis() -> SetTitle("R (mm)" );

	// Fit
	Double_t rMax  = hRange  -> GetBinCenter(hRange  -> GetMaximumBin());
	hRange  -> Fit("gaus", "", "", rMax *0.9, rMax *1.1);
	Double_t rPMax = hRangeP -> GetBinCenter(hRangeP -> GetMaximumBin());
	hRangeP -> Fit("gaus", "", "", rPMax*0.9, rPMax*1.1);

	// Text box for fit result
	TPaveText* tRange  = new TPaveText(0.15, 0.75, 0.55, 0.85, "NDC");
	TPaveText* tRangeP = new TPaveText(0.15, 0.75, 0.55, 0.85, "NDC");
	TString cutText  = Form("Cut by EDep > %.1f MeV,", cut);
	TString fitResR  = Form("Peak center = %.2f mm", hRange  -> GetFunction("gaus") -> GetParameter(1));
	TString fitResRP = Form("Peak center = %.2f mm", hRangeP -> GetFunction("gaus") -> GetParameter(1));
	tRange  -> AddText(cutText  . Data());
	tRange  -> AddText(fitResR  . Data());
	tRangeP -> AddText(cutText  . Data());
	tRangeP -> AddText(fitResRP . Data());
	c1 -> cd(2);
	tRange  -> Draw();
	c1 -> cd(3);
	tRangeP -> Draw();

	// Save
	c1 -> SaveAs("hist.png");
	TFile* output = new TFile("hist.root", "RECREATE");
	c1      -> Write();
	hEDep   -> Write();
	hRange  -> Write();
	hRangeP -> Write();
	output -> Close();

	// Delete
//	delete output;
//	delete tRangRP;
//	delete tRange;
//	delete c1;
//	delete hRangeP;
//	delete hRange;
//	delete hEDep;
//	delete data;

	return;
}
