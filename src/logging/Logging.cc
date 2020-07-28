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

#include "Logging.h"

Logging::Logging() {
    // TODO Auto-generated constructor stub
}

Logging::~Logging() {
    // TODO Auto-generated destructor stub
}

void Logging::printMaps(map<int, vector<int>> const &m) {
    for(auto &key: m) {
        cout << key.first << " | " << key.second[0] << " | " << key.second[1] << " | " << key.second[2] << endl;
    }
}

void Logging::printMaps(map<int, MDP*> const &m) {
    for(auto &key: m) {
        cout << key.first << "|" << endl;
        //key.second->getAction() << "|" << key.second->getState()
    }
}
//
void Logging::printMaps(vector<pair<int, MDP*>> const &m) {
    for(auto &key: m) {
        //EV << key.first << "|" << key.second->getAction() << "|" << key.second->getState() << endl;
    }
}

void Logging::storeNeighbours(map<int, vector<int>> neighbours, string fileName) {
    log.open(fileName); // ./results/results.txt
    log << "-Node_id | hop_end_count | -" << endl;
    for(auto &key: neighbours) {
     // pair<int, vector<int>> key(neighbour);
        log << key.first << " | " << key.second[0] << " | " << key.second[1] << endl;
    }
    log.close();
}

void Logging::storeConStatus(map<int, MDP*> conStatus, string fileName, string csvFileName) {
    log.open(fileName); //
    //    vector<pair<int, MDP*>> resultedConStatus = sortConStatus(conStatus);
    log << "-Node_Id | Value - | -HopCount- " << endl;
    for(auto &key: conStatus) {
        log << key.first << "|" << key.second->getVal() << "|" << key.second->getHopCount()  << endl;
    }

    log.close();


    log.open(csvFileName);
    log << "Node_Id" << "," <<  "Value" << "," << "HopCount" << endl;
    for(auto &key: conStatus) {
        log << key.first << "," << key.second->getVal() << "," << key.second->getHopCount() << endl;
    }
    log.close();
}
