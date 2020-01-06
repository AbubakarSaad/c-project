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
#include <iostream>

using namespace std;

class RSU11p : public BaseWaveApplLayer {
private:
    /**
     * Struct used for MDP of current node
     */
    struct MDPinfo {
        string state_of_rsu;
        string action; // Has to be enum
        string transcation; // This will perform the action
        int reward; // Needs to be calculated
    };

    /**
     * State of the Nodes
     */
    enum StateOfNodes {
        CONNECTED,
        NOT_CONNECTED
    };
    /**
     * Kind of actions and transcation
     */
    enum NodeActions {
        CONNECTED_RSU,
        CONNECTED_NODE,
    };



    protected:
        // Stores the node information of mdp state and updates accordingly
        map<int, vector<int>> neighbours;
        map<int, MDPinfo*> rsuTable;

        virtual void onWSM(WaveShortMessage* wsm);
        virtual void onWSA(WaveServiceAdvertisment* wsa);
        virtual void onBSM(BasicSafetyMessage* bsm);

    public:
        virtual void initialize(int stage);
        virtual void handleSelfMsg(cMessage* msg);
};

#endif /* SRC_RSU11P_H_ */
