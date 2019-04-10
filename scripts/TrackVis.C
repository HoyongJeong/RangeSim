////////////////////////////////////////////////////////////////////////////////
//   < TrackVis.C >                                                           //
//                                                                            //
//   Track visualization script.                                              //
// Note that making GIF works only with batch mode.                           //
//                                                                            //
//                        2019. 3. 26. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "TString.h"
#include "TChain.h"
#include "TGraph2D.h"
#include "TCanvas.h"

void TrackVis(const Int_t nTracks = 100, const Double_t range = 400., const Bool_t anim = kFALSE, const Bool_t makeGIF = kFALSE)
{
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

	// Link addresses
	Int_t eventID;
	Double_t eDepTotal;
	Double_t pathTotal;
	Double_t posXFinal;
	Double_t posYFinal;
	Double_t posZFinal;
	Double_t timeFinal;
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

	// Define graphs
	TGraph2D* gTrack[nTracks];
	
	for ( Int_t i = 0; i < nTracks; i++ )
	{
		// Get i-th entry
		data -> GetEntry(i);

		// Define i-th graph
		TString gName = Form("track_%d", i);
		gTrack[i] = new TGraph2D(gName.Data(), gName.Data(), posXHistory -> size(), &posXHistory -> front(), &posYHistory -> front(), &posZHistory -> front());
		gTrack[i] -> SetMarkerStyle(20);
		gTrack[i] -> SetMarkerSize(0.3);
		gTrack[i] -> SetLineColor(kBlue);
		gTrack[i] -> SetMarkerColor(kYellow);
	}

	// Prepare canvas
	TCanvas* cTracks = new TCanvas("cTracks", "Tracks", 900, 900);
	TGraph2D* gFrame = new TGraph2D();
	gFrame -> SetTitle("Track Visualization");
	gFrame -> SetPoint(0, - range / 2., - range / 2., 0.   );
	gFrame -> SetPoint(1,   range / 2.,   range / 2., range);
	gFrame -> Draw("P");

	// Style
	gFrame -> GetXaxis() -> SetTitle("x (mm)");
	gFrame -> GetYaxis() -> SetTitle("y (mm)");
	gFrame -> GetZaxis() -> SetTitle("z (mm)");
	gFrame -> GetXaxis() -> SetTitleOffset(1.5);
	gFrame -> GetYaxis() -> SetTitleOffset(1.5);
	gFrame -> GetZaxis() -> SetTitleOffset(1.5);

	// Draw tracks
	for ( Int_t i = 0; i < nTracks; i++ )
	{
		if ( anim && makeGIF && gROOT -> IsBatch() ) cTracks -> Print("trackVis.gif+1");

		gTrack[i] -> Draw("PLINESAME");
		if ( anim ) cTracks -> Modified();
		if ( anim ) cTracks -> Update();

	}

	if ( anim && makeGIF && gROOT -> IsBatch() ) cTracks -> Print("trackVis.gif++");

	// Delete
//	delete gFrame;
//	delete cTracks;
//	for ( Int_t i = 0; i < nTracks; i++ ) delete gTrack[i];
//	delete data;

	return;
}
