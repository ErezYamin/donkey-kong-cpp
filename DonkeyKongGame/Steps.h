#pragma once
#include <string>
#include <list>
#include <utility>
using namespace std;
class Steps
{
	long randomSeed = 0;
	list <pair<size_t, char>> steps;
public:
	bool isEmptyStepsFile(const std::string& filename)const;
	void clearSteps();
	void saveSteps(const string& fileName)const;
	static Steps loadSteps(const std::string& filename);
	long getRandomSeed() const {
		return randomSeed;
	}
	void setRandomSeed(long seed) {
		randomSeed = seed;
	}
	void addStep(size_t iteration, char step) {
		steps.push_back({ iteration, step });
	}
	bool isNextStepOnIteration(size_t iteration) const {
		return !steps.empty() && steps.front().first == iteration;
	}
	char popStep() {
		char step = steps.front().second;
		steps.pop_front();
		return step;
	}
};
