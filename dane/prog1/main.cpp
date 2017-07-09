#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <TH1F.h>
#include <TROOT.h>
#include <TCanvas.h>

using namespace std;
using namespace std::chrono;

int main()
{
    vector<int> timestamps;
    vector<float> values;
    string line;
    ifstream fd("dane1");
    if(!fd.is_open())
    {
        cout << "Could not open file" << endl;
        return 1;
    }

    bool endOfData = false;
    while(getline(fd, line))
    {
        if(endOfData)
        {
            break;
        }
        stringstream ss(line);
        string buf;
        int i = 0;
        bool noEmptyLine = false;
        string date = "";
        while(ss >> buf)
        {
            noEmptyLine = true;
            if(i == 1)
            {
                float numberValue = atof(buf.c_str());
                values.push_back(numberValue);
            }
            else if(i == 2)
            {
                date += buf;
                date += " ";
            }
            else if(i == 3)
            {
                date += buf;
                struct tm tm;
                strptime(date.c_str(), "%d-%m-%Y %H:%M:%S", &tm);
                time_t epochTime = mktime(&tm);
                timestamps.push_back(epochTime);
            }
            i++;
        }
        if(!noEmptyLine)
        {
            endOfData = true;
        }
    }

    if(values.size() != timestamps.size())
    {
        cout << "Different number of values and timestamps" << endl;
        return 1;
    }

    TH1F* hist = new TH1F("hist", "hist", 10, 1268734859.0, 1268824870.0);
    for(int i = 0; i<values.size(); i++)
    {
//        hist->SetBinContent(timestamps.at(i), hist->GetBinContent(timestamps.at(i)) + values.at(i));
        cout << values[i] << endl;
        hist->Fill(timestamps[i], values[i]);
    }

    TCanvas canv;
    canv.Clear();

    hist->Draw("P");

    canv.SaveAs("test.jpg");


    return 0;
}

