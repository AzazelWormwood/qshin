
#include "headers/gaussianfiles.h"
#include "headers/qchemfiles.h"
#include "headers/spemulate.h"
#include "headers/gsemulate.h"


using namespace std;



struct availableCommands {
	string functions[8] = { "summarize", "emulate", "freq-arrange", "help", "quit", "test", "to-alex", "combine"};
	string funchelp[8] = {};
};

class configParser {
public:
	void parse(string filename);
	bool get_linearity() {
		return this->specify_linearity;
	}
private:
	bool specify_linearity;
};

class inputHandler {
public:

	void mainLoop();
	void summarize();
	void freq_arrange();
	void emulate();
	void help();
	void test();
	void to_alex();
	void combine();
	

private:
	int choice;
	availableCommands commands;
};

int main() {
	/*
		grep("temp/gs.log", "temp/input.dat");
		arrange("temp/input.dat", "temp/freq.dat");

		sp qchem;
		qchem.get("qchem.out", "temp_sp.txt");
		qchem.store("temp_sp.txt");
		qchem.emulate("sp.log");


		gaussRun khadiza;
		khadiza.summarize("gs.log", "temp.txt");
		return 0;


		gaussRun test;
		test.get("inputfiles/gs.log");
		test.print("outputfiles/sum.txt");
		*/

	inputHandler interface;
	interface.mainLoop();
	
}

void inputHandler::mainLoop() {
	while (true) {
		cout << "Available Commands:" << endl;
		for (string func : this->commands.functions) {
			cout << func << endl;
		}
		cout << "Please enter a command: ";
		string input;
		cin >> input;
		transform(input.begin(), input.end(), input.begin(), ::tolower); //makes input string lowercase
		int choice = 0;
		for (string func : this->commands.functions) {
			if (func == input) {
				break;
			}
			else {
				choice++;
			}
		}
		this->choice = choice;
		if (this->choice >= (sizeof(this->commands.functions) / sizeof(this->commands.functions[0]))) { //if command is not in functions array
			cout << "Invalid Command" << endl;
			cout << endl;
			continue;

		}
		switch (this->choice) {
		case 0: //if user input "summarize"
			this->summarize();
			break;
		case 1: //if user input "emulate"
			this->emulate();
			break;
		case 2: //if user input "freq_arrange"
			this->freq_arrange();
			break;
		case 3: //if user input "help"
			this->help();
			break;
		case 4: //if user input "quit"
			cout << "Exiting program..." << endl;
			return;
			break; //not strictly necessary, but follows convention
		case 5: //if user input test--here for an easy command for me to test certain functions with
			this->test();
			break;
		case 6:
			this->to_alex();
			break;
		case 7:
			this->combine();
			break;
		default:
			break;
		}
	
	}
}

void inputHandler::summarize() {
	cout << "----------------------------------------------" << endl;
	cout << "Would you like to summarize a Gaussian file or a QChem file? (input 'g' or 'q' for Gaussian or QChem respectively, or 'm' to return to the main menu): ";
	char input;

	while (true) {
		cin >> input;
		input = tolower(input);
		while (cin.get() != '\n'); //clears input stream if user inputs too many characters
		if (input == 'g') {
			
			cout << "Please enter the name of the file you would like to summarize (make sure the file is in the /inputfiles directory): ";
			string file;
			cin >> file;
			string infile;
			infile = "inputfiles/" + file;
			string outfile = "outputfiles/summary_" + file;
			gaussRun file_to_summarize;
			
			int error = file_to_summarize.get(infile);
		
			if (error == 0) {
				cout << "summary_" << file << " created in /outputfiles directory." << endl;
				file_to_summarize.print(outfile);
			}
			return;
			
		}
		if (input == 'q') {
			cout << "Please enter the name of the file you would like to summarize (make sure the file is in the /inputfiles directory): ";
			string file;
			cin >> file;
			string infile;
			infile = "inputfiles/" + file;
			string outfile = "outputfiles/summary_" + file;
			qchemRun file_to_summarize;
			int error = file_to_summarize.get(infile);
			
			if (error == 0) {
				file_to_summarize.print(outfile);
				cout << "summary_" << file << " created in /outputfiles directory." << endl;
				
			}
			return;
		}
		if (input == 'm') {
			return;
		}
		cout << "Invalid input. Enter 'g' to summarize a Gaussian file, or 'q' to summarize a QChem file. Otherwise, enter 'm' to return to the main menu: ";
		
	}
}

void inputHandler::freq_arrange() {
	cout << "----------------------------------------------" << endl;
	cout << "Would you like to arrange the frequencies from a Gaussian file or a QChem file? (input 'g' or 'q' for Gaussian or QChem respectively, or 'm' to return to the main menu): ";
	char input;
	while (true) {
		cin >> input;
		input = tolower(input);
		while (cin.get() != '\n'); //clears input stream if user inputs too many characters
		if (input == 'g') {
			cout << "Please enter the name of the file you would like to arrange (make sure the file is in the /inputfiles directory): ";
			string file;
			cin >> file;
			string infile;
			infile = "inputfiles/" + file;
			string outfile = "outputfiles/freq.dat";
			gaussRun freq_file;
			int error = freq_file.freq_get(infile);
			if (error == 0) {
				cout << "freq.dat created in /outputfiles directory." << endl;
				freq_file.arrange(outfile);
			}
			return;
		}

		if (input == 'q') {
			cout << "Please enter the name of the file you would like to arrange (make sure the file is in the /inputfiles directory): ";
			string file;
			cin >> file;
			string infile;
			infile = "inputfiles/" + file;
			string outfile = "outputfiles/freq.dat";
			qchemRun freq_file;
			int error = freq_file.freq_get(infile);
			if (error == 0) {
				cout << "freq.dat created in /outputfiles directory." << endl;
				freq_file.arrange(outfile);
			}
			return;
		}
		if (input == 'm') {
			return;
		}

		cout << "Invalid input. Enter 'g' to summarize a Gaussian file, or 'q' to summarize a QChem file. Otherwise, enter 'm' to return to the main menu: ";
	}
}


void inputHandler::emulate() {
	
	cout << "Please enter the name of the QChem file you would like to make look like a Gaussian file (make sure the file is in the /inputfiles directory): ";
	string file;
	cin >> file;
	string infile;
	cout << endl;
	cout << "Please enter the desired name of the output file: ";
	string filename;
	cin >> filename;
	infile = "inputfiles/" + file;
	string outfile = "outputfiles/" + filename;
	cout << "Does this file contain frequencies? (y/n): ";
	string resp;
	cin >> resp;
	resp = tolower(resp[0]);
	if (resp[0] == 'y') {
		gs file_to_emulate;


		int error = file_to_emulate.get(infile);
		if (error == 0) {
			cout << filename << " created in /outputfiles directory." << endl;
			file_to_emulate.emulate(outfile);
		}
	}
	else{
		sp file_to_emulate;
			
		int error = file_to_emulate.get(infile);
		if (error == 0) {
			cout << filename << " created in /outputfiles directory." << endl;
			file_to_emulate.emulate(outfile);
			}

		}
	
		
}

void inputHandler::help() {
	return;
}

void inputHandler::test() {
	
	//gs test;
	//test.get("tests/inputs/diacetylene.out");
	//test.emulate("tests/test-outputs/diacetylene.out");

	//gs test1;
	//test1.get("tests/inputs/n2_freq.out");
	//test1.emulate("tests/test-outputs/n2_freq.out");

	//sp test2;
	//test2.get("tests/inputs/excited_difluorodiphenyl.out");
	//test2.emulate("tests/test-outputs/excited_difluorodiphenyl.out");

	//gs test3;
	//test3.get("tests/inputs/difluorodiphenyl.out");
	//test3.emulate("tests/test-outputs/difluorodiphenyl.out");

	//gs test4;
	//test4.get("tests/inputs/c60.out");
	//test4.emulate("tests/test-outputs/c60.out");

	//gs test5;
	//test5.get("tests/inputs/co2.out");
	//test5.emulate("tests/test-outputs/co2.out");

	//sp test6;
	//test6.get("tests/inputs/n2.out");
	//test6.emulate("tests/test-outputs/n2.out");

 //   sp test7;
	//test7.get("tests/inputs/water.out");
	//test7.emulate("tests/test-outputs/water.out");

	//sp test8;
	//test8.get("tests/inputs/fe@c60.out");
	//test8.emulate("tests/test-outputs/fe@c60.out");

	supplem_to_alex("inputfiles/supplem.dat", "outputfiles/hrf.dat");

	//gaussRun roshan;
	//roshan.get("inputfiles/sp.log");
	//vector<atom> geo = roshan.getgeo();
	//double scf = 0;
	//int count = geo.size();

	//sp roshan_convert;
	//roshan_convert.setgeo(geo);
	//roshan_convert.setscf(scf);
	//roshan_convert.setcount(count);
	//roshan_convert.emulate("outputfiles/c.log");

	return;
}

void inputHandler::to_alex() {
	cout << "----------------------------------------------" << endl;
	cout << "Would you like to make input files for Alex's FGR code from a Gaussian file or a QChem file? (input 'g' or 'q' for Gaussian or QChem respectively, or 'm' to return to the main menu): ";
	char input;
	while (true) {
		cin >> input;
		input = tolower(input);
		while (cin.get() != '\n'); //clears input stream if user inputs too many characters
		if (input == 'm') {
			return;
		}
		if (input == 'g') {
			cout << "Please enter the name of the source file (make sure the file is in the /inputfiles directory): ";
			string file;
			cin >> file;
			string infile;
			cout << "Please enter the desired name of the output file: ";
			string filename;
			cin >> filename;
			infile = "inputfiles/" + file;
			string outfile = "outputfiles/" + filename;
			gaussRun run;
			run.to_alex(infile, outfile);
			cout << outfile << " created in /outputfiles directory." << endl;


			return;
		}

		if (input == 'q') {
			cout << "Please enter the name of the source file (make sure the file is in the /inputfiles directory): ";
			string file;
			cin >> file;
			string infile;
			cout << "Please enter the desired name of the output file: ";
			string filename;
			cin >> filename;
			infile = "inputfiles/" + file;
			string outfile = "outputfiles/" + filename;
			qchemRun run;
			run.get(infile);
			run.to_alex(outfile);
			cout << outfile << " created in /outputfiles directory." << endl;


			return;
		}
	}
}

void inputHandler::combine() {
	cout << "Please enter the file from which to pull the frequencies: ";
	string freq_file;
	cin >> freq_file;
	string freq_infile = "inputfiles/" + freq_file;
	cout << "Please enter the file from which to pull the geometry: ";
	string geo_file;
	cin >> geo_file;
	string geo_infile = "inputfiles/" + geo_file;
	string outfile = "outputfiles/gs.log";
	gs freqfile;

	int error = freqfile.get(freq_infile);
	
	gs geofile;
	error = geofile.get(geo_infile);
	freqfile.setgeo(geofile.getgeo());
	if (error == 0) {
		cout << outfile << " created in /outputfiles directory." << endl;
		freqfile.emulate(outfile);
	}
}

//void configParser::parse(string filename) {
//	string configs[] = {"set_linearity"};
//	string current;
//	string setting;
//	string trash;
//	ifstream ifile;
//	ifile.open(filename);
//	while (ifile.is_open()) {
//		ifile >> current;
//		transform(current.begin(), current.end(), current.begin(), ::tolower); //makes current lowercase
//		if (current.find("*") != string::npos || current.find("#") != string::npos) {
//			continue;
//		}
//		int i = 0;
//		for (string match : configs) {
//			
//			if (current == match) {
//				ifile >> trash;
//				ifile >> setting;
//				transform(setting.begin(), setting.end(), setting.begin(), ::tolower); //makes setting lowercase
//				switch (i) {
//				case 0:
//					if (setting == "true") {
//						this->specify_linearity = true;
//					}
//					else {
//						this->specify_linearity = false;
//					}
//					break;
//				}
//				
//
//
//			}
//			if (current == "END") {
//				return;
//			}
//		}
//		}
//	return;
//}