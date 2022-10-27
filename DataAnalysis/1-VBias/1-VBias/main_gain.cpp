//
//  test.cpp
//  
//
//  Created by Matteo Capitani on 20/10/22.
//

#include "/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/Libs/UtilityLib.cc"
using namespace std;

int main(int argc, char ** argv)
{
    
    vector<double> sigma(5, 0);
    vector<int> gains = {24, 35, 60, 70, 100};
    vector<double> media = sigma;
    vector<double> Emedia = sigma;
    

    vector<Double_t> y_point24 = readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/1-VBias/1-VBias/data/gain24.dat");
    vector<Double_t> y_point35 = readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/1-VBias/1-VBias/data/gain35.dat");
    vector<Double_t> y_point60 = readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/1-VBias/1-VBias/data/gain60.dat");
    vector<Double_t> y_point70 = readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/1-VBias/1-VBias/data/gain70.dat");
    vector<Double_t> y_point100 = readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/1-VBias/1-VBias/data/gain100.dat");
    
    
    TApplication theApp("theApp", &argc, argv);
    
    //Gain 24
    TCanvas c1;
    TH1F gr1("histo_24G", "histo_24G", 8192, 0, 8192);
    TF1 gr1_fit("gr1_fit", "gaus(0)+pol2(3)", 1200, 2000); //gaus(0) is a substitute for [0]*exp(-0.5*((x-[1])/[2])**2) and (0) means start numbering parameters at 0. expo(3) is a substitute for exp([3]+[4]*x).
    TPad *grid1  = new TPad("grid", "", 0,0,1,1);
    grid1->Draw();
    grid1->cd();
    grid1->SetGrid();
    grid1->SetFillStyle(4000);
    
    for (int i=0; i<y_point24.size(); ++i) {
        gr1.SetBinContent(i+1, y_point24.at(i));
    }
    
    gr1.FitPanel();
    gr1.GetXaxis()->SetTitle("# Bin");
    gr1.GetYaxis()->SetTitle("Counts");
    //gr1.SetFillColor(kOrange+1);
    gr1.SetTitle("Calibration Spectrum (600 V): Gain 24");
    gr1_fit.SetParName(0, "Amp");
    gr1_fit.SetParName(1, "#mu");
    gr1_fit.SetParName(2, "#sigma");
    gr1_fit.SetParName(3, "a");
    gr1_fit.SetParName(4, "b");
    gr1_fit.SetParName(5, "c");
    gr1_fit.SetParameter(0, 100);
    gr1_fit.SetParameter(1, VMG(&gr1_fit));
    gr1_fit.SetParameter(2, 50);
    gr1_fit.SetLineWidth(4);
    gStyle->SetOptFit(1111);
    //gPad->SetLogx();
    
    TFitResultPtr gr1_fit_result=gr1.Fit (&gr1_fit, "SR");
    gr1_fit_result->Prob();
    gr1.Draw();
    
    sigma.at(0) = gr1_fit.GetParameter(2);
    media.at(0) = gr1_fit.GetParameter(1);
    
    //Gain 35
    TCanvas c2;
    TH1F gr2("histo_35", "histo_35G", 8192, 0, 8192);
    TF1 gr2_fit("gr2_fit", "gaus(0)+pol2(3)", 1600, 2600);
    TPad *grid2  = new TPad("grid", "", 0,0,1,1);
    grid2->Draw();
    grid2->cd();
    grid2->SetGrid();
    grid2->SetFillStyle(4000);
    
    for (int i=0; i<y_point35.size(); ++i) {
        gr2.SetBinContent(i+1, y_point35.at(i));
    }
    
    gr2.FitPanel();
    gr2.GetXaxis()->SetTitle("# Bin");
    gr2.GetYaxis()->SetTitle("Counts");
    //gr1.SetFillColor(kOrange+1);
    gr2.SetTitle("Calibration Spectrum (600 V): Gain 35");
    gr2_fit.SetParName(0, "Amp");
    gr2_fit.SetParName(1, "#mu");
    gr2_fit.SetParName(2, "#sigma");
    gr2_fit.SetParName(3, "a");
    gr2_fit.SetParName(4, "b");
    gr2_fit.SetParName(5, "c");
    gr2_fit.SetParameter(0, 100);
    gr2_fit.SetParameter(1, VMG(&gr2_fit));
    gr2_fit.SetParameter(2, 200);
    gr2_fit.SetLineWidth(4);
    gStyle->SetOptFit(1111);
    //gPad->SetLogx();
    
    TFitResultPtr gr2_fit_result=gr2.Fit (&gr2_fit, "SR");
    gr2_fit_result->Prob();
    gr2.Draw();
    
    sigma.at(1) = gr2_fit.GetParameter(2);
    media.at(1) = gr2_fit.GetParameter(1);

    
    //Gain 60
    
    TCanvas c3;
    TH1F gr3("histo_60G", "histo_60G", 8192, 0, 8192);
    TF1 gr3_fit("gr3_fit", "gaus(0)+pol2(3)", 3000, 4500);
    TPad *grid3  = new TPad("grid", "", 0,0,1,1);
    grid3->Draw();
    grid3->cd();
    grid3->SetGrid();
    grid3->SetFillStyle(4000);
    
    for (int i=0; i<y_point60.size(); ++i) {
        gr3.SetBinContent(i+1, y_point60.at(i));
    }
    gr3.FitPanel();
    gr3.GetXaxis()->SetTitle("# Bin");
    gr3.GetYaxis()->SetTitle("Counts");
    //gr1.SetFillColor(kOrange+1);
    gr3.SetTitle("Calibration Spectrum (600 V): Gain 60");
    gr3_fit.SetParName(0, "Amp");
    gr3_fit.SetParName(1, "#mu");
    gr3_fit.SetParName(2, "#sigma");
    gr3_fit.SetParName(3, "a");
    gr3_fit.SetParName(4, "b");
    gr3_fit.SetParName(5, "c");
    gr3_fit.SetParameter(0, 100);
    gr3_fit.SetParameter(1, VMG(&gr3_fit));
    gr3_fit.SetParameter(2, 300);
    gr3_fit.SetLineWidth(4);
    gStyle->SetOptFit(1111);
    //gPad->SetLogx();
    
    TFitResultPtr gr3_fit_result=gr3.Fit (&gr3_fit, "SR");
    gr3_fit_result->Prob();
    gr3.Draw();
    
    sigma.at(2) = gr3_fit.GetParameter(2);
    media.at(2) = gr3_fit.GetParameter(1);

    
    //Gain 70
    TCanvas c4;
    TH1F gr4("histo_70G", "histo_70G", 8192, 0, 8192);
    TF1 gr4_fit("gr4_fit", "gaus(0)+pol2(3)", 3000, 4600);
    TPad *grid4  = new TPad("grid", "", 0,0,1,1);
    grid4->Draw();
    grid4->cd();
    grid4->SetGrid();
    grid4->SetFillStyle(4000);
    
    for (int i=0; i<y_point70.size(); ++i) {
        gr4.SetBinContent(i+1, y_point70.at(i));
    }
    
    gr4.FitPanel();
    gr4.GetXaxis()->SetTitle("# Bin");
    gr4.GetYaxis()->SetTitle("Counts");
    //gr4.SetFillColor(kOrange+1);
    gr4.SetTitle("Calibration Spectrum (600 V): Gain 70");
    gr4_fit.SetParName(0, "Amp");
    gr4_fit.SetParName(1, "#mu");
    gr4_fit.SetParName(2, "#sigma");
    gr4_fit.SetParName(3, "a");
    gr4_fit.SetParName(4, "b");
    gr4_fit.SetParName(5, "c");
    gr4_fit.SetParameter(0, 100);
    gr4_fit.SetParameter(1, VMG(&gr4_fit));
    gr4_fit.SetParameter(2, 200);
    gr4_fit.SetLineWidth(4);
    gStyle->SetOptFit(1111);
    //gPad->SetLogx();
    
    TFitResultPtr gr4_fit_result=gr4.Fit (&gr4_fit, "SR");
    gr4_fit_result->Prob();
    gr4.Draw();
    
    sigma.at(3) = gr4_fit.GetParameter(2);
    media.at(3) = gr4_fit.GetParameter(1);

    
    //Gain 100
    TCanvas c5;
    TH1F gr5("histo_100G", "histo_100G", 8192, 0, 8192);
    TF1 gr5_fit("gr5_fit", "gaus(0)+pol2(3)", 5000, 7000);
    TPad *grid5  = new TPad("grid", "", 0,0,1,1);
    grid5->Draw();
    grid5->cd();
    grid5->SetGrid();
    grid5->SetFillStyle(4000);
    
    for (int i=0; i<y_point100.size(); ++i) {
        gr5.SetBinContent(i+1, y_point100.at(i));
    }
    
    gr5.FitPanel();
    gr5.GetXaxis()->SetTitle("# Bin");
    gr5.GetYaxis()->SetTitle("Counts");
    //gr5.SetFillColor(kOrange+1);
    gr5.SetTitle("Calibration Spectrum (600 V): Gain 100");
    gr5_fit.SetParName(0, "Amp");
    gr5_fit.SetParName(1, "#mu");
    gr5_fit.SetParName(2, "#sigma");
    gr5_fit.SetParName(3, "a");
    gr5_fit.SetParName(4, "b");
    gr5_fit.SetParName(5, "c");
    gr5_fit.SetParameter(0, 50);
    gr5_fit.SetParameter(1, VMG(&gr5_fit));
    gr5_fit.SetParameter(2, 300);
    gr5_fit.SetLineWidth(4);
    gStyle->SetOptFit(1111);
    //gPad->SetLogx();
    
    TFitResultPtr gr5_fit_result=gr5.Fit (&gr5_fit, "SR");
    gr5_fit_result->Prob();
    gr5.Draw();
    
    sigma.at(4) = gr5_fit.GetParameter(2);
    media.at(4) = gr5_fit.GetParameter(1);

    
    //grafico del gain in funzione della sigma
    TGraph *gainFWHM = new TGraph;
    for (int i=0; i<sigma.size(); ++i) {
        sigma.at(i) *= 2*sqrt(2*M_LN2);
        gainFWHM->SetPoint(i, gains.at(i), sigma.at(i));
    }
    
    gainFWHM->SetTitle("Optimal Gain (FWHM)");
    gainFWHM->GetXaxis()->SetTitle("Gain");
    gainFWHM->GetYaxis()->SetTitle("#sigma");
    gainFWHM->SetMarkerStyle(8);
    gainFWHM->SetMarkerSize(0.7);
    
    gainFWHM->Draw();
    
    double sist_gainFWHM = (*max_element(sigma.begin(), sigma.end()) - *min_element(sigma.begin(), sigma.end())) / 2;
    cout << sist_gainFWHM << endl;
    
    TCanvas c6;
    TGraph *gainRES = new TGraph;
    for (int i=0; i<sigma.size(); ++i) {
        sigma.at(i) /= media.at(i);
        gainRES->SetPoint(i, gains.at(i), sigma.at(i));
    }
    
    gainRES->SetTitle("Optimal Gain (Resolution)");
    gainRES->GetXaxis()->SetTitle("Gain");
    gainRES->GetYaxis()->SetTitle("#frac{#sigma}{E}");
    gainRES->SetMarkerStyle(8);
    gainRES->SetMarkerSize(0.7);
    
    gainRES->Draw();
    
    ofstream output("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/output/sistematicoGAIN.txt");
    double sist_gainRES = (*max_element(sigma.begin(), sigma.end()) - *min_element(sigma.begin(), sigma.end())) / 2;
    cout << sist_gainRES << endl;
    
    output << sist_gainFWHM << endl;
    output << sist_gainRES << endl;

    
    theApp.Run();
}
