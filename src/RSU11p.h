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

#ifndef SRC_RSU11P_H_
#define SRC_RSU11P_H_

#include <fstream>
#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "src/messages/BeaconMsg_m.h"
#include "src/messages/DataMsg_m.h"
#include "src/MDP.h"
#include <iostream>
#include <stack>
#include <algorithm>
#include <cstdlib>

using namespace std;

class RSU11p : public BaseWaveApplLayer {
private:
    protected:
        // Stores the node information of mdp state and updates accordingly
        map<int, vector<int>> neighbours;

        // srcID, path & status
        map<int, pair<string, string>> nodeStatus;
        // sourID and State
        map<int, MDP*> conStatus;
        // track ids
        stack<int> track_nodes; // tracks the connected nodes

        // value results in here
        map<int, double> results;

        cMessage* start_flooding;
        cMessage* stop_flooding;
        cMessage* ack_msg;
        cMessage* finishing;

        double request_interval_size;
        double request_tolerance_size;
        double request_ending;

        MDP* connectivityStatus;

        // helper functions
        void printMaps(map<int, vector<int>> const &m);
        void printMaps(map<int, MDP*> const &m);\
        void printMaps(vector<pair<int, MDP*>> const &m);
        map<int, double> valueIter(map<int, MDP*> mdpMap);

        virtual void onWSM(WaveShortMessage* wsm);
        virtual void onWSA(WaveServiceAdvertisment* wsa);
        virtual void onBSM(BasicSafetyMessage* bsm);
        int search(); // returns the last id
        vector<pair<int, MDP*>> sortConStatus(map<int, MDP*> constatu);


        double Q(vector<tuple<int, double, int>> probs, vector<double> values, double discount);

        double max_double_val(vector<double> max_val);

    public:
        virtual void initialize(int stage);
        virtual void handleSelfMsg(cMessage* msg);
        virtual void finish();


};

#endif /* SRC_RSU11P_H_ */
