#pragma once
#include <list>
#include <fstream>
class Results
{
	enum ResultValue { LoseLife, Finished, Score, noResult };
private:
	std::list<std::pair<size_t, ResultValue>> results; // pair: iteration, result
public:
	friend class General;
	bool isEmptyResultFile(const std::string& filename)const;
	static Results loadResults(const std::string& filename);
	void saveResults(const std::string& filename) const;
	void addResult(size_t iteration, ResultValue result) {
		results.push_back({ iteration, result });
	}
	std::pair<size_t, ResultValue> popResult() {
		if (results.empty()) return { 0, Results::noResult };
		auto result = results.front();
		results.pop_front();
		return result;
	}
	void clearResults();
};
