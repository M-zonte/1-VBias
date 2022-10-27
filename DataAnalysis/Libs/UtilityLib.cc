//
//  UtilityLib.cc
//
//
//  Created by Matteo Capitani on 03/05/22.
//  test

#include "UtilityLib.h"
using namespace std;

const double sist_model = 0.1; //calcolato variando il modello e confrontando i valori di sigma

double RAD(double x)
{
    return (x*M_PI)/180.;
}

double gaussiana (double media, double sigma, double x)
{
    return 1./sqrt(2*M_PI*sigma*sigma) * exp(-(x-media)*(x-media)/2*sigma*sigma);
}

long long int fattoriale (int n)
{
    if (n <= 1) {
        return 1;
    }
        long long int f = n;
        for (int i=n-1; i>1; --i) {
            f *= i;
    }
    return f;
}

double sec (double x)
{
    return 1./sin(x);
}

double csc (double x)
{
    return 1./cos(x);
}

double cot (double x)
{
    return cos(x)/sin(x);
}


//funzione per calcolare l'errore sul prodotto
double ERRprod (double mis1, double err1, double mis2, double err2)
{
    return (mis1*mis2) * sqrt(pow(err1/mis1, 2) + pow(err2/mis2, 2));
}
//funzione per calcolare l'errore sul rapporto
double ERRdiv (double mis1, double err1, double mis2, double err2)
{
    return (mis1/mis2) * sqrt(pow(err1/mis1, 2) + pow(err2/mis2, 2));
}

Double_t rettaAB(Double_t *x, Double_t *par)
{
    return par[0]+par[1]*x[0];
}
//retta passante da 0: y=Ax
Double_t retta(Double_t *x, Double_t *par)
{
    return par[0]*x[0];
}
//funzione sinusoidale A*sin(wx+phi)+k
Double_t sinusoide (Double_t *x, Double_t *par)
{
    return (par[0]*sin((par[1]*x[0])+par[2]))+par[3];
}
//gaussiana
Double_t gaussiana_root (Double_t *x, Double_t *par)
{
    return 1./(sqrt(2*M_PI*par[1]*par[1])) * exp(-(x[0]-par[0])*(x[0]-par[0])/(2*par[1]*par[1]));
}
//ENC^2 per il voltaggio
Double_t ENC_V (Double_t *x, Double_t *par)
{
    return sqrt(par[0]*(1/x[0]) + par[1]*x[0] + par[2]);
}
//funzione per rimuovere un carattere da una stringa (potrei passarli per ref così cambia il valore della stringa)
TString FindRemove(TString s1, char c)
{
    vector<char> cloneString;
    for (int j=0; j<s1.Sizeof(); ++j) {
        if (s1[j] != c && s1[j] != '\0' ) {
            cloneString.push_back(s1[j]);
        }
    }
    TString s;
    for (int j=0; j<cloneString.size(); ++j) {
        s.Append(cloneString.at(j));
    }
    return s;
}

TString FindRemove(TString s1, TString c)
{
    vector<char> cloneString;
    for (int j=0; j<s1.Sizeof(); ++j) {
        if (s1[j] != c && s1[j] != '\0' ) {
            cloneString.push_back(s1[j]);
        }
    }
    TString s;
    for (int j=0; j<cloneString.size(); ++j) {
        s.Append(cloneString.at(j));
    }
    return s;
}

vector<Double_t> readNUM (TString filepath)
{
    vector<Double_t> dati;
    
    // Legge i dati e li caccia in un vettore
    fstream bin_file;
    bin_file.open (filepath, ios::in);
    if (bin_file.good() != true)
    { cout << "READING FAILED" << endl; exit(EXIT_FAILURE); }
    
    while (bin_file.eof() != true)
    {
        Double_t n = 0;
        if (bin_file.eof() != true)
        {
            bin_file >> n;
            dati.push_back(n);
        }
    }
    
    bin_file.close();
        
    return dati;
}

//probabilmente posso farlo con i template ma non ho voglia di perderci 4 ore per capire come
vector<TString> readCHAR (TString filepath)
{
    vector<TString> dati;
    
    // Legge i dati e li caccia in un vettore
    fstream file;
    file.open (filepath, ios::in);
    if (file.good() != true)
    { cout << "READING FAILED" << endl; exit(EXIT_FAILURE); }
    
    while (file.eof() != true)
    {
        TString s;
        s.ReadToDelim(file, '\n');
        dati.push_back(s);
    }
    
    file.close();
        
    return dati;
}

vector<vector<double>> readRANGE (TString filepath)
{
    vector<vector<double>> data(2);
    
    fstream file;
    file.open (filepath, ios::in);
    if (file.good() != true)
    { cout << "READING FAILED" << endl; exit(EXIT_FAILURE); }
    
    while (file.eof() != true)
    {
        double n = 0.;
        if (file.eof() != true)
        {
            for(int i=0; i<2; i++){
                file >> n;
                data.at(i).push_back(n);
            }
        }
    }
    return data;
}
//piccola funzione per calcolare velocemente il punto per settare il parametro della media di un fit gaussiano facendo la media del range (Valor Medio Gaussiana)
double VMG (TF1 *f)
{
    return f->GetXmin() + (f->GetXmax() - f->GetXmin())/2 ;
}
