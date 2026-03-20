
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

struct Patient {
    string name;
    double heartRate;
    double systolicBP;
    double diastolicBP;
    double temperature;
};

// Function to safely convert string to double
bool safeConvert(const string& str, double& value) {
    try {
        value = stod(str);
        return true;
    } catch (...) {
        return false;
    }
}

// Function to read CSV file
vector<Patient> readData(const string& filename) {
    vector<Patient> patients;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file: " << filename << endl;
        return patients;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string word;
        Patient p;

        if (!getline(ss, p.name, ',')) continue;

        if (getline(ss, word, ',') && safeConvert(word, p.heartRate) &&
            getline(ss, word, ',') && safeConvert(word, p.systolicBP) &&
            getline(ss, word, ',') && safeConvert(word, p.diastolicBP) &&
            getline(ss, word, ',') && safeConvert(word, p.temperature)) {
            
            patients.push_back(p);
        }
    }

    file.close();
    return patients;
}

// Function to compute statistics
void analyzeData(const vector<Patient>& patients) {
    if (patients.empty()) {
        cout << "No valid data available.\n";
        return;
    }

    double sumHR = 0, sumTemp = 0;
    double maxHR = numeric_limits<double>::lowest();
    double minHR = numeric_limits<double>::max();

    for (const auto& p : patients) {
        sumHR += p.heartRate;
        sumTemp += p.temperature;

        if (p.heartRate > maxHR) maxHR = p.heartRate;
        if (p.heartRate < minHR) minHR = p.heartRate;
    }

    double meanHR = sumHR / patients.size();
    double meanTemp = sumTemp / patients.size();

    cout << fixed << setprecision(2);

    cout << "\n=== Patient Vitals Report ===\n";
    cout << "Total Patients: " << patients.size() << "\n";
    cout << "----------------------------------\n";
    cout << "Heart Rate -> Mean: " << meanHR
         << " | Min: " << minHR
         << " | Max: " << maxHR << "\n";
    cout << "Temperature -> Mean: " << meanTemp << "\n";

    cout << "\n=== Abnormal Readings ===\n";

    bool found = false;

    for (const auto& p : patients) {
        bool abnormal = false;

        if (p.heartRate < 60 || p.heartRate > 100) {
            cout << p.name << " -> Abnormal Heart Rate: " << p.heartRate << "\n";
            abnormal = true;
        }

        if (p.temperature < 36.1 || p.temperature > 37.8) {
            cout << p.name << " -> Abnormal Temperature: " << p.temperature << "\n";
            abnormal = true;
        }

        if (abnormal) found = true;
    }

    if (!found) {
        cout << "No abnormal readings detected.\n";
    }
}

int main() {
    string filename = "../data/patient_data.csv";

    vector<Patient> patients = readData(filename);

    analyzeData(patients);

    return 0;
}