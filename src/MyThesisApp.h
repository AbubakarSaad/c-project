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


#include <omnetpp.h>
#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "veins/modules/mobility/traci/TraCIScenarioManager.h"
#include "src/messages/BeaconMsg_m.h"
#include "src/messages/DataMsg_m.h"
#include "src/MDP.h"
#include <string.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <sstream>
//#include "RSU11p.h"

using namespace omnetpp;
using namespace std;

class MyThesisApp : public BaseWaveApplLayer {
private:

    string buildPaths(string path);

    public:
       virtual void initialize(int stage);


       int temp_rec = 0;



    protected:
       // meta info process

       // variables
       cMessage* start_flooding_node;
       cMessage* stop_flooding_node;
       cMessage* start_processing;
       cMessage* start_process_data;
       cMessage* ack_to_rsu;

       bool sendMessage; // beacon
       bool sendMessageData; // data
       bool correctNodeMsg; // Look for Correct Node
       bool rsu_id_flag = false;
       bool endMsg = false; // For node leaving the simulation


       simtime_t interval_flood;
       int currentSubscribedServiceId;
       int RSU_id;
       vector<int> rsu_ids;

       // Internal map
       map<int, string> nodes_ids;


       // Store MDP
       // Model info
       map<int, vector<int>> neighbours;
       MDP* connectivityStatus;
       map<int, MDP*> conStatus;
       double trans_probabilties[4][4] = {{0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}}; // 0 == !C, 1 == V, 2 == R, 3 == VR transition probablity matrix

       // helper functions
       void printMaps(map<int, vector<int>> const &m);
       void printMaps(map<int, MDP*> const &m);
       void printMaps(map<int, string> const &m);

       // functions
       virtual void onBSM(BasicSafetyMessage* bsm);
       virtual void onWSM(WaveShortMessage* wsm);
       virtual void onWSA(WaveServiceAdvertisment* wsa);


       virtual void handleSelfMsg(cMessage* msg);
       virtual void handlePositionUpdate(cObject* obj);
       virtual void finish();


       // "message" info process
};
