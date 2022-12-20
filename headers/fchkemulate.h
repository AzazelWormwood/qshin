#pragma once
#include "qchemfiles.h"

class fchk : public qchemRun {
public:
	void emulate(string outfile) {
		ofstream ofile(outfile);
		ofile << "Current cartesian coordinates              R   N=         ";
		ofile << this->getcount() * 3 << endl;
		int coords_printed = 0;
		for (int i = 0; i < this->getcount(); i++) {
			for (int j = 0; j <= 2; j++) {
				ofile << scientific << this->getgeo().at(i).coords[j] << "  ";
				coords_printed++;
				if (coords_printed % 5 == 0) {
					ofile << endl;
				}
			}
		}
		ofile << "Cartesian Force Constants              R   N=         ";
		ofile << 16920 << endl;
		//ofile << this->getnmodes().size() << endl;
		int forces_printed = 0;
		for (int i = 0; i < 16920; i++) {
			
				ofile << scientific << this->getnmodes().at(i%174).frc << "  ";
				forces_printed++;
				if (forces_printed % 5 == 0) {
					ofile << endl;
				}
			}
		}
	
};



			

//i believe this need force constants, cartesian coordinates, and some sort of frequency? i can't find frequencies in this file, but dushin is reading them somehow and causing conflicts