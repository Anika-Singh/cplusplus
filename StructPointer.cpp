/*
The data set describes sales data for a company.  The source file is in the form of;

	OrderDate, 	Region,	 Rep, 	Item, 	Units, 	UnitCost, 	Total
	1/6/2015, 	East,	 	Jones, 	Pencil,	95, 	1.99, 		189.05
	1/23/2015, 	Central, 	Kivell, Binder, 50, 	19.99, 		999.50
	2/9/2015, 	Central, 	Jardine, Pencil, 36, 	4.99, 		179.64
	2/26/2015, 	Central, 	Gill, 	Pen, 	27, 	19.99, 		539.73
	...


Objective of this program is to read the data into a structure and then order it in particular ways.
In this case we will sort in ascending order of the value in each records “Total”.
We will create an array of structures to hold all of the records in memory.
*/


#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;

struct SALESREC
{
	char     date[10];
	char     region[10];
	char     rep[10];
	char     item[10];
	int      units;
	float    unitCost;
	float    Total;
};

void simpleSortTotal(SALESREC* s[40], int c);

int main()
{
	ifstream infile;
	int i=0;
	char cNum[10] ;
	SALESREC salesArr[40];
	int   salesArrayCount;
	SALESREC* s[40];

    infile.open ("SalesData.txt", ifstream::in);
    if (infile.is_open())
    {
		int   c=0;
		while (infile.good())
		{
			infile.getline(salesArr[c].date, 256, ',');
			infile.getline(salesArr[c].region, 256, ',');
			infile.getline(salesArr[c].rep, 256, ',');
			infile.getline(salesArr[c].item, 256, ',');
			infile.getline(cNum, 256, ',');
			salesArr[c].units = atoi(cNum);
			infile.getline(cNum, 256, ',');
			salesArr[c].unitCost = atof(cNum);
			infile.getline(cNum, 256, '\n');
			salesArr[c].Total = atof(cNum);

			i++ ;
			c++;
		}
		salesArrayCount = c-1;
		infile.close();
	}
	else
	{
		cout << "Error opening file";
	}

	// Initialize the sort array pointers
	for (int i=0; i < salesArrayCount; i++)
		s[i] = &salesArr[i];

	simpleSortTotal (s, salesArrayCount);

	for (int i=0; i < salesArrayCount; i++)
		cout << "Record: " << s[i]->date <<", " << s[i]->region << ", " << s[i]->rep << ", " << s[i]->item << ", " << s[i]->units << ", " << s[i]->unitCost << ", " << s[i]->Total << endl;

}

// arguments will be an array of pointers and a count
void simpleSortTotal( SALESREC* s[40], int c)
{
	for (int i=0; i < c; i++)
    {
        int iMin = i;
		for (int j=i; j < c; j++)
        {
           if ( s[j]->Total < s[iMin]->Total )
            iMin = j;
		}

		if (iMin != i)
        {
            SALESREC* temp;
            temp = s[iMin];
            s[iMin] = s[i];
            s[i] = temp;
        }
    }
}
