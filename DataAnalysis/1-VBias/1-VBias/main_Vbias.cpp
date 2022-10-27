//
//  main.cpp
//  1-VBias
//
//  Created by Matteo Capitani on 19/10/22.
//

#include <iostream>
#include "/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/Libs/UtilityLib.cc"

using namespace std;
int main(int argc, char ** argv) {
    
    vector<double> sigma1(6, 0);
    vector<double> media1 = sigma1;
    vector<double> voltage(6, 400);
    vector<double> Evoltage(sigma1.size(), 0);
    vector<double> Esigma1(sigma1.size(), 0);
    vector<double> Emedia = sigma1;
    
    
    for (int i=0; i<voltage.size(); ++i){
        voltage.at(i)+=i*100;
    }
    
    vector<Double_t> y_point400 = readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/1-VBias/1-VBias/data/400.dat");
    vector<Double_t> y_point500 = readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/1-VBias/1-VBias/data/500.dat");
    vector<Double_t> y_point600 = readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/1-VBias/1-VBias/data/600.dat");
    vector<Double_t> y_point700 = readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/1-VBias/1-VBias/data/700.dat");
    vector<Double_t> y_point800 = readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/1-VBias/1-VBias/data/800.dat");
    vector<Double_t> y_point900 = readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/1-VBias/1-VBias/data/900.dat");
    
    
    TApplication theApp("theApp", &argc, argv);
    
    //400 V forse va usato un fondo esponenziale oppure prova a modificare i range di fitting
    TCanvas c1;
    TH1F gr1("histo_400V", "histo_400V", 8192, 0, 8192);
    TF1 gr1a_fit("gr1a_fit", "gaus(0)+pol2(3)", 250, 450); //gaus(0) is a substitute for [0]*exp(-0.5*((x-[1])/[2])**2) and (0) means start numbering parameters at 0. expo(3) is a substitute for exp([3]+[4]*x).
    TF1 gr1b_fit("gr1b_fit", "gaus(0)+pol2(3)", 650, 870); //gaus(0) is a substitute for [0]*exp(-0.5*((x-[1])/[2])**2) and (0) means start numbering parameters at 0. expo(3) is a substitute for exp([3]+[4]*x).
    TPad *grid1  = new TPad("grid", "", 0,0,1,1);
    grid1->Draw();
    grid1->cd();
    grid1->SetGrid();
    grid1->SetFillStyle(4000);
    
    for (int i=0; i<y_point400.size(); ++i) {
        gr1.SetBinContent(i+1, y_point400.at(i));

    }
    
    gr1.FitPanel();
    gr1.GetXaxis()->SetTitle("# Bin");
    gr1.GetYaxis()->SetTitle("Counts");
    gr1.SetLineColor(kBlue);
    gr1.SetTitle("Calibration Spectrum: 400 V");
    
    gr1a_fit.SetParName(0, "Amp_{1}");
    gr1a_fit.SetParName(1, "#mu_{1}");
    gr1a_fit.SetParName(2, "#sigma_{1}");
    gr1a_fit.SetParName(3, "a_{1}");
    gr1a_fit.SetParName(4, "b_{1}");
    //gr1a_fit.SetParName(5, "c_{1}");
    gr1a_fit.SetParameter(0, 300);
    gr1a_fit.SetParameter(1, VMG(&gr1a_fit));
    gr1a_fit.SetParameter(2, 50);
    gr1a_fit.SetLineWidth(4);
    
    gr1b_fit.SetParName(0, "Amp_{2}");
    gr1b_fit.SetParName(1, "#mu_{2}");
    gr1b_fit.SetParName(2, "#sigma_{2}");
    gr1b_fit.SetParName(3, "a_{2}");
    gr1b_fit.SetParName(4, "b_{2}");
    gr1b_fit.SetParName(5, "c_{2}");
    gr1b_fit.SetParameter(0, 300);
    gr1b_fit.SetParameter(1, VMG(&gr1b_fit));
    gr1b_fit.SetParameter(2, 50);
    gr1b_fit.SetLineWidth(4);
    gStyle->SetOptFit(1112);
    //gPad->SetLogx();
    
    TFitResultPtr gr1a_fit_result=gr1.Fit (&gr1a_fit, "SR");
    gr1a_fit_result->Prob();
    TFitResultPtr gr1b_fit_result=gr1.Fit (&gr1b_fit, "SR+");
    gr1b_fit_result->Prob();
    gr1.Draw();
    
    sigma1.at(0) = gr1a_fit.GetParameter(2);
    media1.at(0) = gr1a_fit.GetParameter(1);
    Esigma1.at(0) = gr1a_fit.GetParError(2);
    
    
    //500 V
    
    TCanvas c2;
    TH1F gr2("histo_500V", "histo_500V", 8192, 0, 8192);
    TF1 gr2a_fit("gr2a_fit", "gaus(0)+pol2(3)", 900, 1450); //gaus(0) is a substitute for [0]*exp(-0.5*((x-[1])/[2])**2) and (0) means start numbering parameters at 0. expo(3) is a substitute for exp([3]+[4]*x).
    TF1 gr2b_fit("gr2b_fit", "gaus(0)+pol2(3)", 2300, 2800); //gaus(0) is a substitute for [0]*exp(-0.5*((x-[1])/[2])**2) and (0) means start numbering parameters at 0. expo(3) is a substitute for exp([3]+[4]*x).
    TPad *grid2  = new TPad("grid", "", 0,0,1,1);
    grid2->Draw();
    grid2->cd();
    grid2->SetGrid();
    grid2->SetFillStyle(4000);
    
    for (int i=0; i<y_point500.size(); ++i) {
        gr2.SetBinContent(i+1, y_point500.at(i));
    }
    
    gr2.FitPanel();
    gr2.GetXaxis()->SetTitle("# Bin");
    gr2.GetYaxis()->SetTitle("Counts");
    gr2.SetLineColor(kBlue);
    gr2.SetTitle("Calibration Spectrum: 500 V");
    
    gr2a_fit.SetParName(0, "Amp_{1}");
    gr2a_fit.SetParName(1, "#mu_{1}");
    gr2a_fit.SetParName(2, "#sigma_{1}");
    gr2a_fit.SetParName(3, "a_{1}");
    gr2a_fit.SetParName(4, "b_{1}");
    gr2a_fit.SetParName(5, "c_{1}");
    gr2a_fit.SetParameter(0, 300);
    gr2a_fit.SetParameter(1, VMG(&gr2a_fit));
    gr2a_fit.SetParameter(2, 50);
    gr2a_fit.SetLineWidth(4);
    
    gr2b_fit.SetParName(0, "Amp_{2}");
    gr2b_fit.SetParName(1, "#mu_{2}");
    gr2b_fit.SetParName(2, "#sigma_{2}");
    gr2b_fit.SetParName(3, "a_{2}");
    gr2b_fit.SetParName(4, "b_{2}");
    gr2b_fit.SetParName(5, "c_{2}");
    gr2b_fit.SetParameter(0, 300);
    gr2b_fit.SetParameter(1, VMG(&gr2b_fit));
    gr2b_fit.SetParameter(2, 50);
    gr2b_fit.SetLineWidth(4);
    gStyle->SetOptFit(1112);
    //gPad->SetLogx();
    
    TFitResultPtr gr2a_fit_result=gr2.Fit (&gr2a_fit, "SR");
    gr2a_fit_result->Prob();
    TFitResultPtr gr2b_fit_result=gr2.Fit (&gr2b_fit, "SR+");
    gr2b_fit_result->Prob();
    gr2.Draw();
    
    sigma1.at(1) = gr2a_fit.GetParameter(2);
    media1.at(1) = gr2a_fit.GetParameter(1);
    Esigma1.at(1) = gr2a_fit.GetParError(2);

    
    //600 V
    
    TCanvas c3;
    TH1F gr3("histo_600V", "histo_600V", 8192, 0, 8192);
    TF1 gr3a_fit("gr3a_fit", "gaus(0)+pol2(3)", 900, 1450); //gaus(0) is a substitute for [0]*exp(-0.5*((x-[1])/[2])**2) and (0) means start numbering parameters at 0. expo(3) is a substitute for exp([3]+[4]*x).
    TF1 gr3b_fit("gr3b_fit", "gaus(0)+pol2(3)", 2300, 2800); //gaus(0) is a substitute for [0]*exp(-0.5*((x-[1])/[2])**2) and (0) means start numbering parameters at 0. expo(3) is a substitute for exp([3]+[4]*x).
    TPad *grid3  = new TPad("grid", "", 0,0,1,1);
    grid3->Draw();
    grid3->cd();
    grid3->SetGrid();
    grid3->SetFillStyle(4000);
    
    for (int i=0; i<y_point600.size(); ++i) {
        gr3.SetBinContent(i+1, y_point600.at(i));
    }
    
    gr3.FitPanel();
    gr3.GetXaxis()->SetTitle("# Bin");
    gr3.GetYaxis()->SetTitle("Counts");
    gr3.SetLineColor(kBlue);
    gr3.SetTitle("Calibration Spectrum: 600 V");
    
    gr3a_fit.SetParName(0, "Amp_{1}");
    gr3a_fit.SetParName(1, "#mu_{1}");
    gr3a_fit.SetParName(2, "#sigma_{1}");
    gr3a_fit.SetParName(3, "a_{1}");
    gr3a_fit.SetParName(4, "b_{1}");
    gr3a_fit.SetParName(5, "c_{1}");
    gr3a_fit.SetParameter(0, 300);
    gr3a_fit.SetParameter(1, VMG(&gr3a_fit));
    gr3a_fit.SetParameter(2, 50);
    gr3a_fit.SetLineWidth(4);
    
    gr3b_fit.SetParName(0, "Amp_{2}");
    gr3b_fit.SetParName(1, "#mu_{2}");
    gr3b_fit.SetParName(2, "#sigma_{2}");
    gr3b_fit.SetParName(3, "a_{2}");
    gr3b_fit.SetParName(4, "b_{2}");
    gr3b_fit.SetParName(5, "c_{2}");
    gr3b_fit.SetParameter(0, 300);
    gr3b_fit.SetParameter(1, VMG(&gr3b_fit));
    gr3b_fit.SetParameter(2, 50);
    gr3b_fit.SetLineWidth(4);
    gStyle->SetOptFit(1112);
    //gPad->SetLogx();
    
    TFitResultPtr gr3a_fit_result=gr3.Fit (&gr3a_fit, "SR");
    gr3a_fit_result->Prob();
    TFitResultPtr gr3b_fit_result=gr3.Fit (&gr3b_fit, "SR+");
    gr3b_fit_result->Prob();
    gr3.Draw();
    
    sigma1.at(2) = gr3a_fit.GetParameter(2);
    media1.at(2) = gr3a_fit.GetParameter(1);
    Esigma1.at(2) = gr3a_fit.GetParError(2);

    
    //700 V
    
    TCanvas c4;
    TH1F gr4("histo_700V", "histo_700V", 8192, 0, 8192);
    TF1 gr4a_fit("gr4a_fit", "gaus(0)+pol2(3)", 600, 1000); //gaus(0) is a substitute for [0]*exp(-0.5*((x-[1])/[2])**2) and (0) means start numbering parameters at 0. expo(3) is a substitute for exp([3]+[4]*x).
    TF1 gr4b_fit("gr4b_fit", "gaus(0)+pol2(3)", 1600, 2000); //gaus(0) is a substitute for [0]*exp(-0.5*((x-[1])/[2])**2) and (0) means start numbering parameters at 0. expo(3) is a substitute for exp([3]+[4]*x).
    TPad *grid4  = new TPad("grid", "", 0,0,1,1);
    grid4->Draw();
    grid4->cd();
    grid4->SetGrid();
    grid4->SetFillStyle(4000);
    
    for (int i=0; i<y_point700.size(); ++i) {
        gr4.SetBinContent(i+1, y_point700.at(i));
    }
    
    gr4.FitPanel();
    gr4.GetXaxis()->SetTitle("# Bin");
    gr4.GetYaxis()->SetTitle("Counts");
    gr4.SetLineColor(kBlue);
    gr4.SetTitle("Calibration Spectrum: 700 V");
    
    gr4a_fit.SetParName(0, "Amp_{1}");
    gr4a_fit.SetParName(1, "#mu_{1}");
    gr4a_fit.SetParName(2, "#sigma_{1}");
    gr4a_fit.SetParName(3, "a_{1}");
    gr4a_fit.SetParName(4, "b_{1}");
    gr4a_fit.SetParName(5, "c_{1}");
    gr4a_fit.SetParameter(0, 300);
    gr4a_fit.SetParameter(1, VMG(&gr4a_fit));
    gr4a_fit.SetParameter(2, 50);
    gr4a_fit.SetLineWidth(4);
    
    gr4b_fit.SetParName(0, "Amp_{2}");
    gr4b_fit.SetParName(1, "#mu_{2}");
    gr4b_fit.SetParName(2, "#sigma_{2}");
    gr4b_fit.SetParName(3, "a_{2}");
    gr4b_fit.SetParName(4, "b_{2}");
    gr4b_fit.SetParName(5, "c_{2}");
    gr4b_fit.SetParameter(0, 300);
    gr4b_fit.SetParameter(1, VMG(&gr4b_fit));
    gr4b_fit.SetParameter(2, 50);
    gr4b_fit.SetLineWidth(4);
    gStyle->SetOptFit(1112);
    //gPad->SetLogx();
    
    TFitResultPtr gr4a_fit_result=gr4.Fit (&gr4a_fit, "SR");
    gr4a_fit_result->Prob();
    TFitResultPtr gr4b_fit_result=gr4.Fit (&gr4b_fit, "SR+");
    gr4b_fit_result->Prob();
    gr4.Draw();
    
    sigma1.at(3) = gr4a_fit.GetParameter(2);
    media1.at(3) = gr4a_fit.GetParameter(1);
    Esigma1.at(3) = gr4a_fit.GetParError(2);

    
    //800 V
    
    TCanvas c5;
    TH1F gr5("histo_800V", "histo_800V", 8192, 0, 8192);
    TF1 gr5a_fit("gr5a_fit", "gaus(0)+pol2(3)", 1700, 3000); //gaus(0) is a substitute for [0]*exp(-0.5*((x-[1])/[2])**2) and (0) means start numbering parameters at 0. expo(3) is a substitute for exp([3]+[4]*x).
    TF1 gr5b_fit("gr5b_fit", "gaus(0)+pol2(3)", 4700, 6000); //gaus(0) is a substitute for [0]*exp(-0.5*((x-[1])/[2])**2) and (0) means start numbering parameters at 0. expo(3) is a substitute for exp([3]+[4]*x).
    TPad *grid5  = new TPad("grid", "", 0,0,1,1);
    grid5->Draw();
    grid5->cd();
    grid5->SetGrid();
    grid5->SetFillStyle(4000);
    
    for (int i=0; i<y_point800.size(); ++i) {
        gr5.SetBinContent(i+1, y_point800.at(i));
    }
    
    gr5.FitPanel();
    gr5.GetXaxis()->SetTitle("# Bin");
    gr5.GetYaxis()->SetTitle("Counts");
    gr5.SetLineColor(kBlue);
    gr5.SetTitle("Calibration Spectrum: 800 V");
    
    gr5a_fit.SetParName(0, "Amp_{1}");
    gr5a_fit.SetParName(1, "#mu_{1}");
    gr5a_fit.SetParName(2, "#sigma_{1}");
    gr5a_fit.SetParName(3, "a_{1}");
    gr5a_fit.SetParName(4, "b_{1}");
    gr5a_fit.SetParName(5, "c_{1}");
    gr5a_fit.SetParameter(0, 100);
    gr5a_fit.SetParameter(1, VMG(&gr5a_fit));
    gr5a_fit.SetParameter(2, 100);
    gr5a_fit.SetLineWidth(4);
    
    gr5b_fit.SetParName(0, "Amp_{2}");
    gr5b_fit.SetParName(1, "#mu_{2}");
    gr5b_fit.SetParName(2, "#sigma_{2}");
    gr5b_fit.SetParName(3, "a_{2}");
    gr5b_fit.SetParName(4, "b_{2}");
    gr5b_fit.SetParName(5, "c_{2}");
    gr5b_fit.SetParameter(0, 100);
    gr5b_fit.SetParameter(1, VMG(&gr5b_fit));
    gr5b_fit.SetParameter(2, 100);
    gr5b_fit.SetLineWidth(4);
    gStyle->SetOptFit(1112);
    //gPad->SetLogx();
    
    TFitResultPtr gr5a_fit_result=gr5.Fit (&gr5a_fit, "SR");
    gr5a_fit_result->Prob();
    TFitResultPtr gr5b_fit_result=gr5.Fit (&gr5b_fit, "SR+");
    gr5b_fit_result->Prob();
    gr5.Draw();
    
    sigma1.at(4) = gr5a_fit.GetParameter(2);
    media1.at(4) = gr5a_fit.GetParameter(1);
    Esigma1.at(4) = gr5a_fit.GetParError(2);

    
    //900 V
    TCanvas c6;
    TH1F gr6("histo_900V", "histo_900V", 8192, 0, 8192);
    TF1 gr6_fit("gr1_fit", "gaus(0)+pol2(3)", 3000, 7000); //gaus(0) is a substitute for [0]*exp(-0.5*((x-[1])/[2])**2) and (0) means start numbering parameters at 0. expo(3) is a substitute for exp([3]+[4]*x).
    TPad *grid6  = new TPad("grid", "", 0,0,1,1);
    grid6->Draw();
    grid6->cd();
    grid6->SetGrid();
    grid6->SetFillStyle(4000);
    
    for (int i=0; i<y_point900.size(); ++i) {
        gr6.SetBinContent(i+1, y_point900.at(i));
    }
    
    gr6.FitPanel();
    gr6.GetXaxis()->SetTitle("# Bin");
    gr6.GetYaxis()->SetTitle("Counts");
    //gr1.SetFillColor(kOrange+1);
    gr6.SetTitle("Calibration Spectrum: 900 V");
    gr6_fit.SetParName(0, "Amp");
    gr6_fit.SetParName(1, "#mu");
    gr6_fit.SetParName(2, "#sigma");
    gr6_fit.SetParName(3, "a");
    gr6_fit.SetParName(4, "b");
    gr6_fit.SetParName(5, "c");
    gr6_fit.SetParameter(0, 100);
    gr6_fit.SetParameter(1, VMG(&gr6_fit));
    gr6_fit.SetParameter(2, 500);
    gr6_fit.SetLineWidth(4);
    gStyle->SetOptFit(1111);
    //gPad->SetLogx();
    
    TFitResultPtr gr6_fit_result=gr6.Fit (&gr6_fit, "SR");
    gr6_fit_result->Prob();
    gr6.Draw();
    
    sigma1.at(5) = gr6_fit.GetParameter(2);
    media1.at(5) = gr6_fit.GetParameter(1);
    Esigma1.at(5) = gr6_fit.GetParError(2);

    
    
    //studio delle FWHM in funzione del voltaggio per la determinazione del minimo
    
    vector<double> sist = readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/Output/sistematicoGAIN.txt");
    for(int i=0; i<sigma1.size(); ++i)
    {
        sigma1.at(i) = fabs(sigma1.at(i)) / media1.at(i);
        sigma1.at(i) *= 2*sqrt(2*M_LN2);
        Esigma1.at(i) = 2*sqrt(2*M_LN2) * sqrt(sist_model*sist_model + Esigma1.at(i)*Esigma1.at(i) + sist.at(1)*sist.at(1)) / media1.at(i);
        cout << Esigma1.at(i) << endl;
    }
/*
    TCanvas c7;
    TPad *grid7  = new TPad("grid", "", 0,0,1,1);
    grid7->Draw();
    grid7->cd();
    grid7->SetGrid();
    grid7->SetFillStyle(4000);
    
    /*
    TGraph *Gsigma1 = new TGraph(sigma1.size(), &voltage[0], &sigma1[0]);
    TGraph *Gsigma2 = new TGraph(sigma2.size(), &voltage[0], &sigma2[0]);
    TMultiGraph *mg1 = new TMultiGraph;
    mg1->SetTitle("Optimal V_{bias}");
    mg1->Add(Gsigma1, "ACP");
    mg1->Add(Gsigma2, "ACP");
    
    Gsigma1->SetMarkerStyle(8);
    Gsigma1->SetMarkerSize(0.7);
    Gsigma1->SetLineColor(kGreen+1);
    gStyle->SetOptFit(1);
    Gsigma2->SetMarkerStyle(8);
    Gsigma2->SetMarkerSize(0.7);
    Gsigma2->SetLineColor(kBlue);
    
    mg1->Draw("ALP");
    
    
    //Grafico dell'ENC calcolata direttamente con il FWHM per la risoluzione (Roba da elettronici)
    TGraphErrors *GsigmaFWHM = new TGraphErrors(sigma1.size(), &voltage[0], &sigma1[0], &Evoltage[0], &Esigma1[0]);
    TF1 GsigmaFWHM_fit("Gsigma_fit", ENC_V, 500, 900, 3);
    
    GsigmaFWHM->SetTitle("Optimal V_{bias} (FWHM)");
    GsigmaFWHM->GetXaxis()->SetTitle("Voltage (V)");
    GsigmaFWHM->GetYaxis()->SetTitle("ENC^{2}");
    GsigmaFWHM->SetMarkerStyle(8);
    GsigmaFWHM->SetMarkerSize(0.7);
    GsigmaFWHM_fit.SetParameter(0, 10000);
    GsigmaFWHM_fit.SetParameter(1, 10);
    gStyle->SetOptFit(1);
    
    TFitResultPtr GsigmaFWHM_fit_result=GsigmaFWHM->Fit (&GsigmaFWHM_fit, "SR");
    GsigmaFWHM_fit_result->Prob();
    
    GsigmaFWHM->Draw();
    */
    //grafico dell'ENC calcolata dividendo FWHM/media per ottenere la risoluzione (roba da fisici)
    TCanvas c8;
    TPad *grid8  = new TPad("grid", "", 0,0,1,1);
    grid8->Draw();
    grid8->cd();
    grid8->SetGrid();
    grid8->SetFillStyle(4000);
    
    TGraphErrors *GsigmaRES = new TGraphErrors;
    for (int i=0; i<sigma1.size(); ++i)
    {
        //sigma1.at(i) /= media1.at(i);
        //Esigma1.at(i) = ERRdiv(sigma1.at(i), Esigma1.at(i), media1.at(i), Emedia.at(i));
        GsigmaRES->SetPoint(i, voltage.at(i), sigma1.at(i));
        GsigmaRES->SetPointError(i, Evoltage.at(i), Esigma1.at(i));
    }
    TF1 GsigmaRES_fit("Gsigma_fit", ENC_V, 500, 900, 3);
    
    GsigmaRES->SetTitle("Optimal V_{bias} (#frac{#sigma}{E})");
    GsigmaRES->GetXaxis()->SetTitle("Voltage (V)");
    GsigmaRES->GetYaxis()->SetTitle("#frac{#sigma}{E})");
    GsigmaRES->SetMarkerStyle(8);
    GsigmaRES->SetMarkerSize(0.7);
    //GsigmaRES_fit.SetParameter(0, 10000);
    //GsigmaRES_fit.SetParameter(1, 10);
    //GsigmaRES_fit.SetParameter(2, 700);
    gStyle->SetOptFit(1);
    
    TFitResultPtr GsigmaRES_fit_result = GsigmaRES->Fit (&GsigmaRES_fit, "SR");
    GsigmaRES->Draw();

    //quindi se mi metto tra 500-900 V il gain non mi porta errori sistematici, quindi posso variarlo a piacere senza introdurre errori
    
    
    theApp.Run();
    
    return 0;
}
