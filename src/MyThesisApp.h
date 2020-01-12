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

#include "veins/veins.h"

#include <omnetpp.h>
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include "veins/modules/mobility/traci/TraCIScenarioManager.h"
#include "src/messages/BeaconMsg_m.h"
#include "src/messages/DataMsg_m.h"
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

namespace veins {

class VEINS_API MyThesisApp : public DemoBaseApplLayer {
private:
    /**
     * Struct used for MDP of current node
     */
    struct MDPinfo {
        string state_of_node;
        string action; // Has to be enum
        string transcation; // This will perform the action
        int reward; // Needs to be calculated
    };

    /**
     * State of the Nodes
     */
    enum StateOfNodes {
        NOT_CONNECTED,
        RSU,
        NODE,
        BOTH
    };

    /**
     * Kind of actions and transcation
     */
    enum NodeActions {
        CONNECTING_TO_RSU,
        CONNECTING_TO_NODE,
        CONNECTING_TO_BOTH,
    };

    /**
     * transactions
     */
    enum NodeTransactions {
        CONNECTED_TO_RSU,
        CONNECTED_TO_NODE,
        CONNECTED_TO_BOTH,
    };

    string buildPaths(string path);




    public:
       virtual void initialize(int stage);
       int temp_rec = 0;

    protected:
       bool is_flooded;
       simtime_t interval_flood;
       int currentSubscribedServiceId;

       map<int, vector<int>> neighbours;

       MDPinfo* init_obj = new MDPinfo;
       // Stores the node information of mdp state and updates accordingly
       map<int, MDPinfo*> nodesTable;

       virtual void onBSM(DemoSafetyMessage* bsm);
       virtual void onWSM(BaseFrame1609_4* wsm);
       virtual void onWSA(DemoServiceAdvertisment* wsa);

       virtual void handleSelfMsg(cMessage* msg);
       virtual void handlePositionUpdate(cObject* obj);
};
};
