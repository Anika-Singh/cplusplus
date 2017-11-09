/** The objective for this sample is to read a csv file and write a csv file.
We are going to read and analyze input from the U.N. Department of Economic and Social Affairs on mortality rates.
We create an ordered list by longest lived population from 2000-2005 year group.
Where does the United States rank in the list by more developed regions (comprised of Europe,
Northern America, Australia/New Zealand and Japan)?  Where is it ranked overall?
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

typedef  struct population {
    int countryCode;
    string countryName;
    string life50_55;
    string life55_60;
    float life2000_2005;
} Population;

bool is_lower(const Population& x, const Population& y)
{ return x.life2000_2005 < y.life2000_2005; }

int main()
{
    ifstream infile("WPP2015_MORT_F07_1_LIFE_EXPECTANCY_0_BOTH_SEXES.csv");
    string line;
    int linenum = 0;
    bool bSkip = true;
    vector<Population> pv;

    while (getline(infile, line))
    {
        size_t headerFound = line.find("Major area, region, country or area *");
        if (headerFound !=std::string::npos)
            bSkip = false;

        // skip lines upto header
        if ( bSkip )
            continue;

        // skip header also
        if (headerFound != std::string::npos)
            continue;

        istringstream linestream(line);
        string item;
        int itemnum = 0;
        Population p;
        while (getline (linestream, item, ','))
        {
            itemnum++;
            if ( itemnum == 3)
            {
                p.countryName = item;
                //cout << item << endl;
            }

            if ( itemnum == 5) {
                p.countryCode = atoi(item.c_str());
                //cout << item << endl;
            }
            if ( itemnum == 16) {
                p.life2000_2005 = atof(item.c_str());
                //cout << item << endl;
            }

        }
        pv.push_back(p);
    }

    sort(pv.begin(), pv.end(), is_lower);

    // US overall rank
    for(vector<int>::size_type i = 0; i != pv.size(); i++) {
     //cout << pv[i].countryName << endl;
     //cout << pv[i].life2000_2005 << endl;
     if ( pv[i].countryCode == 840 )
     {
        cout << "United Stated Rank Overall:" << i << endl;
        break;
     }
    }

    // US rank in developed
    int developRank = 0;

    for(vector<int>::size_type i = 0; i != pv.size(); i++) {
     if ( pv[i].countryCode == 908 ) // Europe
        developRank++;
     if ( pv[i].countryCode == 905 ) // North America
        developRank++;
     if ( pv[i].countryCode == 927 ) // Australia/New Zealand
        developRank++;
     if ( pv[i].countryCode == 392 ) // Japan
        developRank++;

     if ( pv[i].countryCode == 840 )
     {
        cout << "United Stated Rank in Developed:" << developRank;
        break;
     }
    }



    return 0;
}
