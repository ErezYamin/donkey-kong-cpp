#include "General.h"
int main(int argc, char** argv) {
	bool isLoad, isSilent, isSave;
	if (argc == 1) {
		isLoad = false;
		isSilent = false;
		isSave = false;
	}
	else {
		isLoad = argc > 1 && string(argv[1]) == "-load";
		isSilent = isLoad && argc > 2 && string(argv[2]) == "-silent";
		isSave = !(isLoad || isSilent);
	}
	General general(isLoad, isSilent, isSave);
	general.start();
}