#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include "day06.h"

int main(void) {
    std::vector<_responseGroup> responseGroups;
    _responseGroup inputGroup;

    uint64_t singleResponseSum = 0;
    uint64_t totalResponseSum  = 0;
    bool _endIOStream = false;

    while (!_endIOStream) {
        inputGroup.setGroup(std::cin, _endIOStream);

        // This catch block is not my favourite function progression but was a quick fix to a stream issue.
        // Originally, the .setGroup() function returned a reference to std::cin and the while loop was called on the state of that stream
        // When getline() is called inside the .setGroup function on the final stream element it reached the eof and the while loop would not fire and add the final elements into the responseGroup vector
        // Now the system checks the state of the stream from inside the .setGroup() function and sets _endIOStream based on the state of the stream.

        if (!_endIOStream) {                        
            responseGroups.push_back(inputGroup);
            inputGroup.clear();
        }
    }

    for (auto& group : responseGroups) {
        singleResponseSum += group.check_responses_single();
        totalResponseSum  += group.check_responses_total();
    }

    std::cout << "Single Response: " << singleResponseSum << std::endl;
    std::cout << "Total Response:  " << totalResponseSum  << std::endl;

    return 0;
}