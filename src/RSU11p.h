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

#pragma once

#include <fstream>
#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "src/messages/BeaconMsg_m.h"
#include "src/messages/DataMsg_m.h"
#include "src/MDP.h"
#include <iostream>

using namespace std;

class RSU11p : public BaseWaveApplLayer {
private:
    protected:
        // Stores the node information of mdp state and updates accordingly
        map<int, vector<int>> neighbours;

        // srcID, path & status
        map<int, pair<string, string>> nodeStatus;
        // rank status
        map<int, pair<string, MDP*>> conStatus;

        double trans_probabilties[5][5] = {{0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0}}; // 0 == !C, 1 == V, 2 == R, 3 == VR transition probablity matrix

        cMessage* start_flooding;
        cMessage* stop_flooding;
        cMessage* ack_msg;

        double request_interval_size;
        double request_tolerance_size;

        // helper functions
        void printMaps(map<int, vector<int>> const &m);
        void printMaps(map<int, MDP*> const &m);

        virtual void onWSM(WaveShortMessage* wsm);
        virtual void onWSA(WaveServiceAdvertisment* wsa);
        virtual void onBSM(BasicSafetyMessage* bsm);
        void statusUpdate(int id);

    public:
        virtual void initialize(int stage);
        virtual void handleSelfMsg(cMessage* msg);
        virtual void finish();
};
