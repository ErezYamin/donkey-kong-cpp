#include "Steps.h"
#include <fstream>
Steps Steps::loadSteps(const string& fileName) {
	Steps steps;
	std::ifstream steps_file(fileName);
	steps_file >> steps.randomSeed;
	size_t size;
	steps_file >> size;
	while (!steps_file.eof() && size-- != 0) {
		size_t iteration;
		char step;
		steps_file >> iteration >> step;
		steps.addStep(iteration, step);
	}
	steps_file.close();
	return steps;
}

void Steps::saveSteps(const std::string& filename) const {
	std::ofstream steps_file(filename);
	steps_file << randomSeed << '\n' << steps.size();
	for (const auto& step : steps) {
		steps_file << '\n' << step.first << ' ' << step.second;
	}
	steps_file.close();
}
void Steps::clearSteps() {
	this->randomSeed = 0;
	this->steps.clear();
}
bool Steps::isEmptyStepsFile(const std::string& filename)const {
	std::ifstream steps_file(filename);
	if (!steps_file) { return true; }
	return false;
}