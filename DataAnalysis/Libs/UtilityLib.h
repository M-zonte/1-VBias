//
//  UtilityLib.h
//
//
//  Created by Matteo Capitani on 03/05/22.
//

#ifndef UtilityLib_hpp
#define UtilityLib_hpp

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>

#include "TCanvas.h"
#include "TH1F.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"
#include "TStyle.h"
#include "TLine.h"
#include "TMultiGraph.h"
#include "TFormula.h"

using namespace std;

double RAD (double);
double gaussiana (double, double, double);
long long int fattoriale (int);

double sec (double);
double csc (double);
double cot (double);

double ERRprod (double, double, double, double);
double ERRdiv (double, double, double, double);

Double_t retta(Double_t *, Double_t *);
Double_t rettaAB(Double_t *, Double_t *);
Double_t sinusoide(Double_t *, Double_t);
Double_t gaussiana_root(Double_t *, Double_t *);
Double_t ENC_V(Double_t *, Double_t *);
TString FindRemove(TString, char);

double VMG(TF1 *);

vector<double> readNUM (TString); //per la lettura da file di numeri
vector<TString> readCHAR (TString); //per la lettura da file di stringhe di testo
vector<vector<double>> readRANGE (TString); //per la lettura dei range da file (probabilmente posso modificare leggiNUM per fare sta cosa ma non ho tutta questa voglia)

#endif /* UtilityLib_h */
