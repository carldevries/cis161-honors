//Included libraries
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

//Function prototypes
void rk4(double x, vector<double> &y, double h, int nEqns);
void fEval(double x, vector<double> y, vector<double> &f);

//Main Function
int main(){
	//Declare variables
	int n, nEqns;
	double h, x, xn;
	ofstream outStream;
	string fileName = "";

	//Get user input - Number of equations and Initial x value
	cout << "Enter the number of equations: ";
	cin >> nEqns;
	
	cout << "Enter the initial x value: ";
	cin >> x;

	//Declare and initialize two vectors - One for file names and one for yvalues
	vector<string> files (nEqns);
	vector<double> y(nEqns);

	for (int i = 0; i < nEqns; i++){
		//Get user input - Initial y values
		double tempY;
		cout << "Enter the initial y value for equation y" << i << ": ";
		cin >> tempY;
		y[i] = tempY;

		//Create an associated file for data output
		fileName = "xyData" + to_string(static_cast<long double>(i + 1)) + ".dat"; //static_cast<long double>(i + 1) is needed for compilers at school VC 2010 - Fixes some compiler specific error
		outStream.open(fileName);

		//Check the file was created and close it. Store the file name in the corresponding vector index
		if (outStream.is_open()){
			outStream.close();
			files[i] = fileName;
		}
		else{
			cout << "There was an error creating the file \"" << fileName << "\"" << endl;
		}
	}
		//Get user input - Upper limit and steps
		cout << "Enter the upper limit of integration: ";
		cin >> xn;

		cout << "Enter the number of intervals: ";
		cin >> n;

		//Calculate the step size
		h = (xn - x) / n;

		outStream.precision(7);

		//Run for the given number of steps
		for (int i = 0; i <= n; i++){
			//Run for the given number of equations
			for (int j = 0; j < nEqns; j++){

				//Get the file name, open the file to append data, write the data, close the outfile stream
				fileName = files[j];
				outStream.open(fileName, ofstream::app);
				outStream << i << " " << x << " " << y[j] << endl;
			
				outStream.close();
				fileName.clear();
			}

			//Get the approximation and increment x by the step size
			rk4(x, y, h, nEqns);
			x += h;
			
		}

		//Report completion and return zero
		cout << "Complete." << endl;
		return 0;
	}

	//Functions
	void rk4(double x, vector<double> &y, double h, int nEqns){
		//Declare variables
		vector<double> k1(nEqns);
		vector<double> k2(nEqns);
		vector<double> k3(nEqns);
		vector<double> k4(nEqns);
		vector<double> yTemp(nEqns);
		double xTemp;

		//Calculate k1
		xTemp = x;
		for (int i = 0; i < nEqns; i++)
			yTemp[i] = y[i];
		fEval(xTemp, yTemp, k1);

		//Calculate k2
		xTemp = x + (h * 0.5);
		for (int i = 0; i < nEqns; i++)
			yTemp[i] = y[i] +(k1[i] * h * 0.5);
		fEval(xTemp, yTemp, k2);

		//Calculate k3
		//xTemp stays the same
		for (int i = 0; i < nEqns; i++)
			yTemp[i] = y[i] + (k2[i] * h * 0.5);
		fEval(xTemp, yTemp, k3);

		//Calculate k4
		xTemp = x + h;
		for (int i = 0; i < nEqns; i++)
			yTemp[i] = y[i] + (k3[i] * h) ;
		fEval(xTemp, yTemp, k4);
		
		//Calculate the new approximation
		for (int i = 0; i < nEqns; i++)
			y[i] += (h / 6) * (k1[i] + 2 * (k2[i] + k3[i]) + k4[i]);

		}

	void fEval(double x, vector<double> y, vector<double> &f){

		//User must enter the same number of equations as nEqns before running the program
		

		f[0] = y[1];
		f[1] = 4 - (4.9044 * pow(10.0, 12.0) / pow(y[0], 2.0));
		
	}
	
	//Application problem equations
	//f[0] = y[1];
	//f[1] = 4 - (4.9044 * pow(10.0, 12.0) / pow(y[0], 2.0));

	//Sample problem equations
	//f[0] = x * sqrt(y[0]);