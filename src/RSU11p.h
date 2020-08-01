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
#include "src/logging/Logging.h"
#include <iostream>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <cstdlib>

using namespace std;

class RSU11p : public BaseWaveApplLayer {
private:
    protected:
        // cycles
        int cycles = 0;


        // Stores the node information of mdp state and updates accordingly
        map<int, vector<int>> neighbours;

        // srcID, path & status
        map<int, pair<string, string>> nodeStatus;
        // sourID and State
        map<int, MDP*> conStatus;
        map<int, MDP*> finalStatus;
        map<int, int> hop_tracked;
        unordered_map<int, string> statusCheck;
        vector<pair<int, string>> vecStatusCheck;
        // track ids
        stack<int> track_nodes; // tracks the connected nodes

        // value results in here
        //map<int, double> results;
        int results;

        cMessage* start_flooding;
        cMessage* stop_flooding;
        cMessage* ack_msg;
        cMessage* finishing;
        cMessage* processing;

        double request_interval_size;
        double request_tolerance_size;
        double request_ending;

        MDP* connectivityStatus;

        // helper functions
        void printMaps(map<int, vector<int>> const &m);
        void printMaps(map<int, MDP*> const &m);
        void printMaps(int feq_msg[3][3]);
        void printMaps(double arr[3][3]);
        void printMaps(vector<pair<int, MDP*>> const &m);
        void prob_feq(int row, int col, int div_arr[3], int arr[3][3]);
        tuple<double, int> valueIter(map<int, MDP*> conStatu); // node id, value, state map<int, double, int>

        virtual void onWSM(WaveShortMessage* wsm);
        virtual void onWSA(WaveServiceAdvertisment* wsa);
        virtual void onBSM(BasicSafetyMessage* bsm);
        int search(); // returns the last id
        vector<pair<int, MDP*>> sortConStatus(map<int, MDP*> constatu);
        map<int, MDP*> compareStatus(map<int, MDP*> con, map<int, MDP*> final);


        tuple<double, int> Q(vector<tuple<int, double, int>> probs, double value, double discount);

        double max_double_val(vector<double> max_val);

        vector<pair<int, MDP*>> sortedStatus;

//        |  V2I  |   V2V  |  Null
//    ---------------------------
// V2I    |  11   |      2    |    1
//    ---------------------------
//
//  V2V   |  1    |      1     |    1
//  ---------------------------
//
// Null   |   4   |      2     |    1

        // MDP
        // Four Table
        //  Counter/Fequrency
                // counts the fequerncey of the msg
        int feq_msg[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

        //  Probablitity
            // The probablitiy of the fequencey
        double probablitiy_feq[3][3] = {{0.00, 0.00, 0.00}, {0.00, 0.00, 0.00}, {0.00, 0.00, 0.00}};

        //  Past Cycle Probability
            // Keeps track of the Probablity till the past cycle
        vector<vector<double>> Past_cycle_prob;

        //  Smoothed Probablity
            // Keeps the smooth probablity of the current cycle
        vector<double> Smoothed_Probality;



    public:
        virtual void initialize(int stage);
        virtual void handleSelfMsg(cMessage* msg);
        virtual void finish();


};

#endif /* SRC_RSU11P_H_ */
