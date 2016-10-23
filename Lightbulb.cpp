// Lightbulb.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// IDENTIFIERS <
//
string calculateChromaticityCoordenates();
string getColorFunction(int wavelength);
int getWaveLengthIndex(int wavelength);
string getIntensityForWavelenght(int wavelength);
void split(const string &s, char delim, vector<string> &elems);
vector<string> split(const string &s, char delim);
//
// IDENTIFIERS >

int _tmain(int argc, _TCHAR* argv[])
{
	string 	header = "###########################################################\n";
	header = header + "# Vanhackathon 2016\n";
	header = header + "# Challenge: Thalmic Labs C++ Challenge\n";
	header = header + "# Lightbulb - Chromaticity Coordenates calculator\n";
	header = header + "###########################################################\n\n\n";
	cout << header + ">> Calculating... (wait just a few moments)...\n\n";
	calculateChromaticityCoordenates();
	cin.get();
	return 0;
}

// Calculate the chromaticity coordenates for a wavelength ranging
string calculateChromaticityCoordenates(){
	string result;
	float cfX, cfY, cfZ;		// color functions
	float X = 0, Y = 0, Z = 0;  // tristimulus
	float ccx, ccy;				// chromaticity coordenates

	cout << ">> Follows the chromaticity coordenates (x, y) for Wavelenght between 360nm to 400nm:\n\n";
	cout << ">> Wavelength: (x,y)\n";

	//get index to the wavelenght
	for (int count = 360; count < 405; count += 5){
		vector<string> intensities = split(getIntensityForWavelenght(count), ',');	// gets intensity values for the specific wavelenght
		vector<string> c_functions = split(getColorFunction(count), ',');			// gets color functions for the specific wavelenght

		vector<int>::size_type cfsize = c_functions.size();

		cfX = stof(c_functions[0]);
		cfY = stof(c_functions[1]);
		cfZ = stof(c_functions[2]);

		vector<int>::size_type isize = intensities.size();

		for (unsigned i = 0; i < isize; i++)
		{
			// Calculates the tristimulus for the specific wavelength
			X = X + (stof(intensities[i]) * cfX);
			Y = Y + (stof(intensities[i]) * cfY);
			Z = Z + (stof(intensities[i]) * cfZ);
		}

		// Now that we have the tristimulus, we can calculate the chromaticity coordenates
		ccx = (X / (X + Y + Z));
		ccy = (Y / (X + Y + Z));

		// Add this to the result, and it's done
		cout << ">> " + to_string(count) + "nm: (" + to_string(ccx) + "," + to_string(ccy) + ")\n";
	}
	return result;
}

// Gets the color functions values for the wavelenght.
string getColorFunction(int wavelength){
	string X, Y, Z;
	string result;
	string line;

	ifstream c_functions("c_functions.csv");

	if (c_functions.is_open())
	{

		while (c_functions.good())
		{
			getline(c_functions, line);
			vector<string> row = split(line, ',');

			if (stoi(row[0]) == wavelength){
				X = row[1];
				Y = row[2];
				Z = row[3];
				result = X + "," + Y + "," + Z;
				row.clear();
				break;
			}
		}

		c_functions.close();
	}
	else cout << ">> Unable to open the color functions file. Make sure it's is located in the same directory as the executable.\n\n";

	return result;
}

// getIntensityForWavelenght:
// Gets the first 20 intensities for a specific wavelenght.
// The 20 entries will be enougth for our test.
string getIntensityForWavelenght(int wavelength){

	int index;
	int counter = 0;
	int limit = 20;
	string result;
	string line;

	index = getWaveLengthIndex(wavelength); // gets the index for the wavelength

	ifstream intensities("intensities.csv");

	if (intensities.is_open())
	{

		while (counter < limit)
		{
			getline(intensities, line);
			vector<string> row = split(line, ',');
			vector<int>::size_type size = row.size();

			if (index < size){
				result = result + row[index] + ",";
			}
			
			row.clear();
			counter = counter + 1;
		}

		intensities.close();
	}
	else cout << ">> Unable to open intensities file. Make sure it's is located in the same directory as the executable.\n\n";

	// we have to eliminate the last comma
	return result.substr(0, result.length() - 1);
}

// getWaveLengthIndex:
// Gets the index/position of the first occurance of a wavelenght in the file.
// The index is used to get the right intensity out of the intensity file.
int getWaveLengthIndex(int wavelength){
	
	ifstream f_wavelenghts("wavelengths.csv");
	
	int index;
	float value = 0;

	if (f_wavelenghts.is_open())
	{
		string value;
		while (f_wavelenghts.end)
		{
			getline(f_wavelenghts, value);
			vector<string> row = split(value, ',');

			if (stoi(row[1]) == wavelength) {
				index = stoi(row[0]);
				row.clear();
				break;
			}
		}

		f_wavelenghts.close();
	}
	else cout << ">> Unable to open wavelengths file. Make sure it's is located in the same directory as the executable.\n\n";

	return index;
}

// Split function to help with the csv and other string operations
void split(const string &s, char delim, vector<string> &elems) {
	stringstream ss;
	ss.str(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

vector<string> split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}



