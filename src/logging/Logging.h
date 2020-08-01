//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef SRC_LOGGING_LOGGING_H_
#define SRC_LOGGING_LOGGING_H_

#include "src/MDP.h"
#include <omnetpp.h>
#include <fstream>
#include <iostream>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <cstdlib>

using namespace std;

class Logging {
public:
    Logging();
    void printMaps(map<int, vector<int>> const &m);
    void printMaps(map<int, MDP*> const &m);
    void printMaps(vector<pair<int, MDP*>> const &m);

    void storeSuccessful(unordered_map<int, string> statusCheck, string fileName);
    void storeNeighbours(map<int, vector<int>> neighbours, string fileName);
    void storeConStatus(map<int, MDP*> conStatus, string fileName, string csvFileName);

    virtual ~Logging();

private:
    ofstream log;
    ostringstream o;
};

#endif /* SRC_LOGGING_LOGGING_H_ */
