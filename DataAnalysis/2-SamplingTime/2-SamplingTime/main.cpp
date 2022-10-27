//
//  main.cpp
//  2-SamplingTime
//
//  Created by Matteo Capitani on 24/10/22.
//

#include <iostream>
#include "/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/Libs/UtilityLib.cc";
#include <ctime>
using namespace std;

int main(int argc, char ** argv) {
    
    clock_t t_begin;
    t_begin = clock();
    
    vector<TH1F *> gr;
    vector<TF1 *> gr_fit;
    vector<TFitResultPtr> fit_result;
    vector<TPad *> grid;
    vector<TCanvas *> c;
    
    vector<double> sigma;
    vector<vector<double>> y_point;
    
    vector<TString> titles;
    vector<vector<double>> ranges;

    
    //lettura dei file per il shaping time di 0.5 µs
    y_point.push_back(readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/2-SamplingTime/2-SamplingTime/data/0,5st550.dat"));
    y_point.push_back(readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/1-VBias/1-VBias/data/600.dat"));
    y_point.push_back(readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/2-SamplingTime/2-SamplingTime/data/0,5st650.dat"));
    y_point.push_back(readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/1-VBias/1-VBias/data/700.dat"));

    //lettura dei file per il shaping time di 1 µs
    y_point.push_back(readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/2-SamplingTime/2-SamplingTime/data/1st550.dat"));
    y_point.push_back(readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/2-SamplingTime/2-SamplingTime/data/1st600.dat"));
    y_point.push_back(readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/2-SamplingTime/2-SamplingTime/data/1st650.dat"));
    y_point.push_back(readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/2-SamplingTime/2-SamplingTime/data/1st700.dat"));

    //lettura dei file per il shaping time di 2 µs
    y_point.push_back(readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/2-SamplingTime/2-SamplingTime/data/2st550.dat"));
    y_point.push_back(readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/2-SamplingTime/2-SamplingTime/data/2st600.dat"));
    y_point.push_back(readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/2-SamplingTime/2-SamplingTime/data/2st650.dat"));
    y_point.push_back(readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/2-SamplingTime/2-SamplingTime/data/2st700.dat"));

    //lettura dei file per il shaping time di 3 µs
    y_point.push_back(readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/2-SamplingTime/2-SamplingTime/data/3st550.dat"));
    y_point.push_back(readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/2-SamplingTime/2-SamplingTime/data/3st600.dat"));
    y_point.push_back(readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/2-SamplingTime/2-SamplingTime/data/3st650.dat"));
    y_point.push_back(readNUM("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/2-SamplingTime/2-SamplingTime/data/3st700.dat"));

    //lettura da file dei titoli dei grafici
    titles = readCHAR("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/2-SamplingTime/2-SamplingTime/data/Titles.txt");
    ranges = readRANGE("/Users/matteocapitani/Desktop/Università/3 Anno/Lab Nucleare👨🏼‍🔬/DataAnalysis/2-SamplingTime/2-SamplingTime/data/Ranges.txt");
    
    TApplication theApp("theApp", &argc, argv);

    for (int k=0; k<y_point.size(); ++k){
        c.push_back(new TCanvas);
        gr.push_back(new TH1F("histo", "histo", y_point.at(k).size(), 0, y_point.at(k).size()));
        gr_fit.push_back(new TF1("gr1_fit", "gaus(0)+pol2(3)", ranges.at(0).at(k), ranges.at(1).at(k)));
        
        grid.push_back(new TPad("grid", "", 0,0,1,1));
        grid.at(k)->Draw();
        grid.at(k)->cd();
        grid.at(k)->SetGrid();
        grid.at(k)->SetFillStyle(4000);
        
        for (int i=0; i<y_point.at(k).size(); ++i) {
            gr.at(k)->SetBinContent(i+1, y_point.at(k).at(i));
        }
        
        gr.at(k)->GetXaxis()->SetTitle("# Bin");
        gr.at(k)->GetYaxis()->SetTitle("Counts");
        gr.at(k)->SetLineColor(kBlue);
        gr.at(k)->SetTitle(titles.at(k));
        
        gr_fit.at(k)->SetParName(0, "Amp");
        gr_fit.at(k)->SetParName(1, "#mu");
        gr_fit.at(k)->SetParName(2, "#sigma");
        gr_fit.at(k)->SetParName(3, "a");
        gr_fit.at(k)->SetParName(4, "b");
        gr_fit.at(k)->SetParName(5, "c");
        gr_fit.at(k)->SetParameter(0, 100);
        gr_fit.at(k)->SetParameter(1, VMG(gr_fit.at(k)));
        gr_fit.at(k)->SetParameter(2, 100);
        gr_fit.at(k)->SetLineWidth(4);
        
        gStyle->SetOptFit(1112);
        //gPad->SetLogx();
        
        fit_result.push_back(gr.at(k)->Fit (gr_fit.at(k), "SR"));
        fit_result.at(k)->Prob();
        gr.at(k)->Draw();
        
        sigma.push_back(gr_fit.at(k)->GetParameter(2) / gr_fit.at(k)->GetParameter(1));
    }

    for (int i=0; i<sigma.size(); ++i){
        cout << i+1 << "\t" << sigma.at(i) << endl;
    }
    cout << "L'errore minimo vale: " << *min_element(sigma.begin(), sigma.end()) << endl;
    TString S = titles.at(distance(sigma.begin(), min_element(sigma.begin(), sigma.end())));
    S.Replace(S.Index("#mu"), 3, "µ");
    cout << "Il grafico con l'errore minimo è: " << S << endl;
    
    t_begin = clock() - t_begin;
    cout << "Programma eseguito in " << (1.*t_begin/CLOCKS_PER_SEC) << " s" << endl;
    
    theApp.Run();
    return 0;
}
