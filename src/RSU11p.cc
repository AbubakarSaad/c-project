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
// RSU==================== id=11 =======================for what I noticed.

#include "RSU11p.h"

Define_Module(RSU11p);

void RSU11p::initialize(int stage) {
    // Start the flooding after 10s and last for 10s = total of 20s
    BaseWaveApplLayer::initialize(stage);

    if(stage == 0) {
        EV << "Init stage of RSU" << endl;

        start_flooding = new cMessage("Start_Flooding");
        stop_flooding = new cMessage("Stop_Flooding");
        ack_msg = new cMessage("Ack_Msg");
        finishing = new cMessage("FINISH");

        // Retrieving information from omnetpp.ini
        request_interval_size = par("request_interval").doubleValue();
        request_tolerance_size = par("request_tolerance").doubleValue();
        request_ending = par("request_ending").doubleValue();



        scheduleAt(simTime() + request_interval_size, start_flooding);
        scheduleAt(simTime() + request_ending, finishing);
        //EV << "MAX TIME" <<  << endl;

    }
}

void RSU11p::printMaps(map<int, vector<int>> const &m) {
    for(auto &key: m) {
          EV << key.first << " | " << key.second[0] << " | " << key.second[1] << " | " << key.second[2] << endl;
     }
}


void RSU11p::printMaps(map<int, MDP*> const &m) {
    for(auto &key: m) {
        EV << key.first << "|" << endl;
        //key.second->getAction() << "|" << key.second->getState()
    }
}

void RSU11p::printMaps(vector<pair<int, MDP*>> const &m) {
    for(auto &key: m) {
        //EV << key.first << "|" << key.second->getAction() << "|" << key.second->getState() << endl;
    }
}



void RSU11p::handleSelfMsg(cMessage* msg) {
    if(msg == start_flooding) {
        BeaconMsg* temp_bsm = new BeaconMsg("Beacon");

        temp_bsm->setSenderAddress(myId);
        temp_bsm->setSerial(4);

        temp_bsm->setHop(1);
        temp_bsm->setRsuID(myId);
        temp_bsm->setIsFlooding(true);
        populateWSM(temp_bsm);
        sendDown(temp_bsm->dup());

        // schedule the "event" every x seconds
        scheduleAt(simTime() + 40, start_flooding);

    } else if (msg == ack_msg) {
        DataMsg* ack = new DataMsg("ACK");

        int desId = search(); // returns the last id in the stack == LIFO

        EV << "hanldeselfmsg desId: " << desId << endl;

        ack->setSouId(myId);
        ack->setDesId(desId);
        ack->setAck(true);

        // data
        ack->setNodeState("CONNECTED");
        ack->setAction("Connected-RSU");
        ack->setTranscation("RSU-to-NODE");
        populateWSM(ack);

        sendDelayedDown(ack->dup(), 1 + uniform(0.01,0.2));
    } else if (msg == finishing) {
        cancelEvent(start_flooding);
        cancelEvent(ack_msg);

        EV << "RUNS AT 1500s" << endl;

        DataMsg* finishing_ack = new DataMsg("FIN_ACK");

        int desId = search();
        track_nodes.pop();



//        ack->setSouId(myId);
//        ack->setDesId(desId);
//        ack->setFinished(true);
//
//        populateWSM(ack);
//
//        sendDelayedDown(ack->dup(), 1 + uniform(0.01, 0.2));
    }
}

void RSU11p::onWSA(WaveServiceAdvertisment* wsa) {
    //if this RSU receives a WSA for service 42, it will tune to the chan
    EV << "RSUWSA" << endl;
    if (wsa->getPsid() == 42) {
        mac->changeServiceChannel(wsa->getTargetChannel());
    }
}

void RSU11p::onBSM(BasicSafetyMessage* bsm) {
    EV << "RSUBSM" << endl;

    if(BeaconMsg* temp_bsm = dynamic_cast<BeaconMsg*>(bsm)) {

       EV << "Temp senderaddress: " << temp_bsm->getSenderAddress() << endl;

       EV << "InsideIF" << endl;
       int source_id = temp_bsm->getSenderAddress();
       int hop_end_count = temp_bsm->getSerial();
       int hop_count = temp_bsm->getHop();

       neighbours.insert(pair<int, vector<int> > (source_id, vector<int>()));
       neighbours[source_id].push_back(hop_count);
       neighbours[source_id].push_back(hop_end_count);


       printMaps(neighbours);
    }
}

double RSU11p::Q(vector<tuple<int, double, int>> probs, vector<double> values, double discount) {
    double sum;

    for(auto &key : probs) {
        sum += get<1>(key) * (get<2>(key) + discount * values[get<0>(key)]);
    }
    EV << "sum: " << sum << endl;

    return sum;
}

double RSU11p::max_double_val(vector<double> max_val) {
    double max_v = max_val[0];

    for(auto &i : max_val) {
        if(max_v < i) {
            max_v = i;
        }
    }

    return max_v;
}

// valueIter
map<int, double> RSU11p::valueIter(map<int, MDP*> mdpMap) {
    // initailize
    vector<double> values;
    map<int, double> reward_nodes;

    for(auto &key: mdpMap) {
        values.push_back(0);
    }

    // compute the new values (newVal) given the old values
    while(true) {
        vector<double> newVal;
        for (auto &key: mdpMap) {
            // For Each State
            EV << "For Each State" << endl;
            if(key.second->isEndState()) {
                newVal.push_back(0);
                reward_nodes.insert({key.first, 0.0});
            } else {
                vector<string> actions = key.second->actions(key.second->getCurState());
                vector<double> sumQ;
               for(auto &act: actions) {
                   vector<tuple<int, double, int>> getProbs = key.second->succProbReward(key.second->getCurState(), act);
                   double sum = Q(getProbs, values, key.second->getDiscount());

                   sumQ.push_back(sum);
                   EV << "For Each Action: Sum === " << sum << endl;
               }

               double max_val = max_double_val(sumQ);
               EV << "MAX === " << max_val << endl;

               newVal.push_back(max_val);

               // Decides the best value of all the actions
               reward_nodes.insert({key.first, max_val});
            }
            //if()
        }

        break;
    }

    return reward_nodes;
}

void RSU11p::onWSM(WaveShortMessage* wsm) {
    EV << "RSUWSM" << endl;
    // cancelEvent(start_flooding);

    // if the data message finds is here. hit the event which will stop the data msg completely.
    if(DataMsg* temp_wsm = dynamic_cast<DataMsg*>(wsm)) {
        // msg recieved
        int temp_id = temp_wsm->getDesId();

        EV << "des: " << temp_id << endl;
        if(temp_id == myId && temp_wsm->getAckRsu() == true) {
            // store this in the rank table
            int souId = temp_wsm->getSouId();
            string hop_path = temp_wsm->getNodesIds();
            int hop_count = temp_wsm->getHop();
            int reward = 10;

            EV << "PATH Taken: " << hop_path << endl;

            // message has been recieved. Update the status for this node.
            connectivityStatus = new MDP();
            connectivityStatus->setState(0);
            connectivityStatus->setHopCount(hop_count);

            int state = connectivityStatus->getCurState();

            EV << "State: " << state << endl;

            // get the action it can perform
            vector<string> getActions = connectivityStatus->actions(connectivityStatus->getCurState());

            vector<tuple<int, double, int>> getProb = connectivityStatus->succProbReward(connectivityStatus->getCurState(), getActions[0]);

            conStatus.insert(std::make_pair(souId, connectivityStatus));

            track_nodes.push(souId);

            //sortConStatus(conStatus);

            printMaps(conStatus);

            EV << "SIZE OF ACTIONS" << getActions.size() << endl;

            for(auto &act : getActions) {
                EV << "Action: " << act << endl;
            }

            for(auto &key: getProb) {
                EV << "State: " << get<0>(key) << " |Prob " << get<1>(key) << " |Reward " << get<2>(key) << endl;
            }

            results = this->valueIter(conStatus);
        }else if(temp_id == myId && temp_wsm->getEndMsg() == true) {
            EV << "End MSG here..." << endl;

            int node_id = temp_wsm->getSouId();

            EV << "Sou Id: " << node_id << endl;
            conStatus.erase(node_id);
        }
    }
}

void RSU11p::finish() {
    BaseWaveApplLayer::finish();

    EV << "When does this work? " << endl;

    ofstream log;
    ostringstream o;

    log.open("./results/results.txt");
    log << "-Node_id | hop_end_count | -" << endl;
    for(auto &key: neighbours) {
     // pair<int, vector<int>> key(neighbour);
        log << key.first << " | " << key.second[0] << " | " << key.second[1] << endl;
    }
    log.close();


    log.open("./results/results_MDP.txt");
//    vector<pair<int, MDP*>> resultedConStatus = sortConStatus(conStatus);
    log << "-Node_Id | Value -" << endl;
    for(auto &key: results) {
        log << key.first << "|" << key.second << endl;
    }
    log.close();

}

int RSU11p::search() {
    EV << "Stack here: " << endl;

    int top_node = track_nodes.top();

    EV << "stack at top" << top_node << endl;
    return top_node;
}

// ranking table
vector<pair<int, MDP*>> RSU11p::sortConStatus(map<int, MDP*> constatu) {
    vector<pair<int, MDP*>> sortedConStatus;

//    auto cmp = [](pair<int, MDP*> const &a, pair<int, MDP*> const &b) {
//       return a.second->getReward() != b.second->getReward() ? a.second->getReward() < b.second->getReward() : b.second->getReward() < a.second->getReward();
//    };
//
//
//    map<int, MDP*> ::iterator it2;
//    for(it2=constatu.begin(); it2!=constatu.end(); it2++) {
//        sortedConStatus.push_back(make_pair(it2->first, it2->second));
//    }
//
//    sort(sortedConStatus.begin(), sortedConStatus.end(), cmp);

    return sortedConStatus;
}


