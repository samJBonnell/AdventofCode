#ifndef DAY06_H
#define DAY06_h

#include <iostream>
#include <vector>
#include <map>
#include <istream>
#include <string>

class _responseGroup {
public:
	_responseGroup() = default;

	void setGroup(std::istream& in, bool& _endIOStream);
	const uint64_t check_responses_total();
	const uint64_t check_responses_single();
	void clear();
	
private:
    std::map<char, uint32_t> 	_responseRecord;
	uint64_t 					_responseSum = 0;
	uint64_t					_totalResponses = 0;
};

void _responseGroup::setGroup(std::istream& in, bool& _endIOStream) {
	std::string inputString;

	if (!in) {					// Catch if the input stream has ended.
		_endIOStream = true;
		return;
	}

	while (std::getline(in, inputString) && !inputString.empty()) {
		for (const auto& it : inputString) {
			_responseRecord[it]++;
		}
		_responseSum++;
	}

}

const uint64_t _responseGroup::check_responses_total() {
	for (const auto& it : _responseRecord) {
		if (it.second == _responseSum) _totalResponses++;
	}

	return _totalResponses;
}

const uint64_t _responseGroup::check_responses_single() {
	return _responseRecord.size();
}

void _responseGroup::clear() {
	_responseRecord.clear();
	_responseSum = 0;
	_totalResponses = 0;
}

#endif
