Patient Vitals Analyzer

This project is a simple C++ program that reads patient vital signs from a CSV file and analyzes them to identify potential abnormalities.

The program calculates basic statistics such as average heart rate and temperature, and highlights values that fall outside normal ranges.

Tools Used in this Project
	a.	C++ (standard library)
	b.	File handling and data parsing

Project Structure 
	a.	data/ - contains the dataset
	b. 	src/ - contains the C++ source code

What the Program Does
	a.	Reads patient data from a CSV file
	b. 	Computes basic statistics (mean, min, max)
	c.	Detects abnormal heart rate and temperature values
	d.	Outputs a simple report in the terminal

How to Run
	1.	Navigate to the src folder: 
	cd src

	2.	Compile the program: 
	g++ -std=c++11 main.cpp -o vitals

	3.	Run the program: 
	./vitals

