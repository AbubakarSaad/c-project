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
        processing = new cMessage("MDP-Processing");

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
        EV << key.first << "|" << key.second->getVal() << endl;
        //key.second->getAction() << "|" << key.second->getState()
    }
}

void RSU11p::printMaps(int arr[3][3]) {

    int row = sizeof(*arr)/sizeof(*arr[0]);
    int col = sizeof(arr[0])/sizeof(arr[0][0]);

    //int row = total / col;

    EV << "Row: " << row << " COL: " << col << endl;


    for(int i=0; i<row; i++) {
        for(int j=0; j<col; j++) {
            EV << "element: " << feq_msg[i][j] << " ";
        }
        EV << endl;
    }
}

void RSU11p::printMaps(double arr[3][3]) {
    int row = sizeof(*arr)/sizeof(*arr[0]);
    int col = sizeof(arr[0])/sizeof(arr[0][0]);

    //int row = total / col;

    EV << "Row: " << row << " COL: " << col << endl;


    for(int i=0; i<row; i++) {
        for(int j=0; j<col; j++) {
            EV << "element: " << arr[i][j] << " ";
        }
        EV << endl;
    }
}

void RSU11p::printMaps(vector<pair<int, MDP*>> const &m) {
    for(auto &key: m) {
        EV << key.first << "|" << key.second->getVal() << endl;
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
        sendDelayedDown(temp_bsm->dup(), 1 + uniform(0.01,0.2));
        cycles += 1;

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
        ack->setNodeState(0);
        ack->setAction("Connected-RSU");
        ack->setTranscation("RSU-to-NODE");
        populateWSM(ack);

        sendDelayedDown(ack->dup(), 1 + uniform(0.01,0.2));
    } else if (msg == finishing) {
        cancelEvent(start_flooding);
        cancelEvent(ack_msg);

        EV << "RUNS AT 1500s" << endl;

        // get the top 10 and bottom 10
        // concentate them into a string and send that message
        // if the id exist in the list, the vehicle replies
        // if it doesn't exist, then 'somehow' check the vehicle in RSU of not replying: maybe the value becomes zero










    } else if(msg == processing) {

        EV << "Do all the processing here" << endl;

        // Call the value iteration algo here.....
        this->valueIter(conStatus);

        printMaps(conStatus);


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

tuple<double, int> RSU11p::Q(vector<tuple<int, double, int>> probs, double value, double discount) {
    double sum;
    int state;

    // get<1>(key)
    double pro = 0;

    for(auto &key : probs) {

        sum += get<1>(key) * (get<2>(key) + (1 * value));

        state = get<0>(key);
    }

    tuple<double, int> res (sum, state);

    EV << "sum: " << sum << endl;

    return res;
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

tuple<double, int> RSU11p::valueIter(map<int, MDP*> conStatu) {
    // initailize
    double value = 0;


    double reward_value;

    tuple<double, int> res_reward;

    // compute the new values (newVal) given the old values
    while(true) {
        vector<double> newVal;

        for(auto &o : conStatu) {
            MDP* obj = o.second;

//            if(obj->getVal() > 0) {
//                value = obj->getVal();
//            }


            EV << "For Each State" << endl;
            if(obj->isEndState()) {
                newVal.push_back(0);
                //reward_nodes.insert({key.first, 0.0});
            } else {
                vector<string> actions = obj->actions(obj->getCurState());
                vector<double> sumQ;
                vector<int> stateQ;
               for(auto &act: actions) {
                   // check if the Q returns the double
                   // fixed probablity == 0.33 and check results differeaita
                   // discount factor at 0.8
                   // If the more hops away, apply by discount factor again. 10% reward decrease per hop
                   // use the transition matrix
                   vector<tuple<int, double, int>> getProbs = obj->succProbReward(obj->getCurState(), act, probablitiy_feq, obj->getPervState());
                   tuple<double, int> sum = Q(getProbs, value, 0.001);

                   EV << "SUM Q: " << get<0>(sum) << endl;

                   sumQ.push_back(get<0>(sum));
                   stateQ.push_back(get<1>(sum));
                   EV << "For Each Action: Sum === " << get<0>(sum) << endl;
               }

               double max_val = max_double_val(sumQ);
               EV << "MAX === " << max_val << endl;

               vector<double>::iterator it = find(sumQ.begin(), sumQ.end(), max_val);
               int index;


               if(it != sumQ.end()) {
                   EV << "ELEMENT FOUND" << endl;
                   index = distance(sumQ.begin(), it);
                   EV << "INDEX " << index << endl;
                   EV << "State: " << stateQ[index] << endl;
               } else {
                   EV << "ELEMENT NOT FOUND " << endl;
                   index = -1;
               }

               newVal.push_back(max_val);

               // Decides the best value of all the actions
               //reward_nodes.insert({key.first, max_val});
               reward_value = max_val;

               res_reward = make_tuple(reward_value, index);

               obj->setPervState(obj->getCurState());
               obj->setState(index);
               obj->setVal(reward_value);


            }
        }
        //if(value < reward_value) break;

        break;
    }

    return res_reward;
}

// valueIter map<int, double, int> map<int, MDP*> mdpMap
//tuple<double, int> RSU11p::valueIter(MDP* obj) {
//    // initailize
//    double value = 0;
//
//    if(obj->getVal() > 0) {
//        value = obj->getVal();
//    }
//    double reward_value;
//
//    tuple<double, int> res_reward;
//
//    // compute the new values (newVal) given the old values
//    while(true) {
//        vector<double> newVal;
//
//        EV << "For Each State" << endl;
//        if(obj->isEndState()) {
//            newVal.push_back(0);
//            //reward_nodes.insert({key.first, 0.0});
//        } else {
//            vector<string> actions = obj->actions(obj->getCurState());
//            vector<double> sumQ;
//            vector<int> stateQ;
//           for(auto &act: actions) {
//               // check if the Q returns the double
//               // fixed probablity == 0.33 and check results differeaita
//               // discount factor at 0.8
//               // If the more hops away, apply by discount factor again. 10% reward decrease per hop
//               // use the transition matrix
//               vector<tuple<int, double, int>> getProbs = obj->succProbReward(obj->getCurState(), act, probablitiy_feq, obj->getPervState());
//               tuple<double, int> sum = Q(getProbs, value, 0.001);
//
//               EV << "SUM Q: " << get<0>(sum) << endl;
//
//               sumQ.push_back(get<0>(sum));
//               stateQ.push_back(get<1>(sum));
//               EV << "For Each Action: Sum === " << get<0>(sum) << endl;
//           }
//
//           double max_val = max_double_val(sumQ);
//           EV << "MAX === " << max_val << endl;
//
//           vector<double>::iterator it = find(sumQ.begin(), sumQ.end(), max_val);
//           int index;
//
//
//           if(it != sumQ.end()) {
//               EV << "ELEMENT FOUND" << endl;
//               index = distance(sumQ.begin(), it);
//               EV << "INDEX " << index << endl;
//               EV << "State: " << stateQ[index] << endl;
//           } else {
//               EV << "ELEMENT NOT FOUND " << endl;
//               index = -1;
//           }
//
//           newVal.push_back(max_val);
//
//           // Decides the best value of all the actions
//           //reward_nodes.insert({key.first, max_val});
//           reward_value = max_val;
//
//           res_reward = make_tuple(reward_value, index);
//
//
//        }
//        //if(value < reward_value) break;
//
//        break;
//    }
//
//    return res_reward;
//}


int sum(int arr[]) {
   int sum=0;

   int row = sizeof(arr)/sizeof(*arr);

   EV << "size of: " << row << endl;

   for(int i=0; i<=row; i++) {
       sum += arr[i];
   }

   return sum;
}

void RSU11p::prob_feq(int row, int col, int div_arr[3], int arr[3][3]) {
    double res[3][3];

    // memcpy(res, feq_msg, row*col*sizeof(int));

    EV << "arr: " << endl;
//    printMaps(arr);

    for(int i=0; i<row; i++) {
        for(int j=0; j<col; j++) {
           if(div_arr[i] != 0) {
               double val = static_cast<double>(arr[i][j]) / static_cast<double>(div_arr[i]);

               EV << "val: " << val << endl;

               res[i][j] = val;
               probablitiy_feq[i][j] = val;
           } else {
               res[i][j] = 0;
               probablitiy_feq[i][j] = 0;
           }
        }
    }

    EV << "probability of fequeres: " << endl;

    printMaps(res);
}

void RSU11p::onWSM(WaveShortMessage* wsm) {
    EV << "RSUWSM" << endl;
    // cancelEvent(start_flooding);
    int count = 0;
    map<int, MDP*>::iterator it;
    // if the data message finds is here. hit the event which will stop the data msg completely.
    if(DataMsg* temp_wsm = dynamic_cast<DataMsg*>(wsm)) {
        // msg recieved
        int temp_id = temp_wsm->getDesId();


        EV << "des: " << temp_id << endl;
        //&& conStatus.find(temp_wsm->getSouId()) != conStatus.end()

        // Value iteration works on during the certain time interval
        // Create the peroidic interval for x amount of beacons
        // x amount of beacons collects information
        // then timeout for value iteration
        // and possibly contacting back the successful or unsuccessful for vehicles
        // for the ranking system.
        if(temp_id == myId && temp_wsm->getAckRsu() == true ) {
            // store this in the rank table
            int souId = temp_wsm->getSouId();
            int hop_count = temp_wsm->getHop();
            string hop_path = temp_wsm->getNodesIds();

            int state;
            int pervState;

            // 0 == NULL, 1 == V2V, 2 == V2I

            it = conStatus.find(souId);
            if(it != conStatus.end()) {
                state = it->second->getCurState();
                pervState = it->second->getPervState();

                EV << "cur_state: " << state << " pervState: " << pervState << endl;

               hop_tracked.insert(std::make_pair(souId, hop_count));

               // pervious state, p and current state, c
              // if state == p, c == 0, 0 == feq_msg[0][0]++ == !C, !C
              // if state == p, c == 0, 1 == feq_msg[0][1]++ == !C, V2V
              // if state == p, c == 0, 2 == feq_msg[0][2]++ == !C, V2I
              // if state == p, c == 1, 0 == feq_msg[1][0]++ == V2V, !C
              // if state == p, c == 1, 1 == feq_msg[1][1]++ == V2V, V2V
              // if state == p, c == 1, 2 == feq_msg[1][2]++ == V2V, V2I
              // if state == p, c == 2, 0 == feq_msg[2][0]++ == V2I, !C
              // if state == p, c == 2, 1 == feq_msg[2][1]++ == V2I, V2V
              // if state == p, c == 2, 2 == feq_msg[2][2]++ == V2I, V2I
              //feq_msg[pervState][state] += 1;

               feq_msg[pervState][state] += 1;

               printMaps(feq_msg);


               // Past cycles
               // Collect the pass cycle


               // smoothed probability
               // smoothed out the probability

               // Porbablitity of fequeces;

            } else {
                if(hop_count == 1) {
                    state = 2;
                    pervState = 0;
                } else if(hop_count > 1) {
                    state = temp_wsm->getNodeState();
                    pervState = temp_wsm->getPervState();
                } else {
                    state = temp_wsm->getNodeState();
                    pervState = temp_wsm->getPervState();
                }


               EV << "cur_state: " << state << " pervState: " << pervState << endl;

               hop_tracked.insert(std::make_pair(souId, hop_count));

               // pervious state, p and current state, c
              // if state == p, c == 0, 0 == feq_msg[0][0]++ == !C, !C
              // if state == p, c == 0, 1 == feq_msg[0][1]++ == !C, V2V
              // if state == p, c == 0, 2 == feq_msg[0][2]++ == !C, V2I
              // if state == p, c == 1, 0 == feq_msg[1][0]++ == V2V, !C
              // if state == p, c == 1, 1 == feq_msg[1][1]++ == V2V, V2V
              // if state == p, c == 1, 2 == feq_msg[1][2]++ == V2V, V2I
              // if state == p, c == 2, 0 == feq_msg[2][0]++ == V2I, !C
              // if state == p, c == 2, 1 == feq_msg[2][1]++ == V2I, V2V
              // if state == p, c == 2, 2 == feq_msg[2][2]++ == V2I, V2I
              //feq_msg[pervState][state] += 1;

               feq_msg[pervState][state] += 1;

               printMaps(feq_msg);

               // Porbablitity of fequeces;
               int state_not_connected = sum(feq_msg[0]);
               int state_v2v = sum(feq_msg[1]);
               int state_v2i = sum(feq_msg[2]);

               EV << "!C == " << state_not_connected << " V2V == " << state_v2v << " V2I == " << state_v2i << endl;

               int div_arr[3] = {state_not_connected, state_v2v, state_v2i};

               int row = sizeof(*feq_msg)/sizeof(*feq_msg[0]);
               int col = sizeof(feq_msg[0])/sizeof(feq_msg[0][0]);

               prob_feq(row, col, div_arr, feq_msg);

               // Past cycles
               // Collect the pass cycle


               // smoothed probability
               // smoothed out the probability


               // message has been recieved. Update the status for this node.
               connectivityStatus = new MDP(state); // current state

               connectivityStatus->setPervState(pervState);

               // need the state from the message
               connectivityStatus->setHopCount(hop_count);

               EV << "State: " << state << endl;

               // schedule a event here after 5 cycles....
               if(cycles % 5 == 0) {
                   scheduleAt(simTime(), processing);
               }

//               tuple<double, int> val_state = this->valueIter(connectivityStatus);
//
//               EV << "Value: " << get<0>(val_state) << " State: " << get<1>(val_state) << endl;
//
//               connectivityStatus->setPervState(state);
//
//               connectivityStatus->setVal(get<0>(val_state));
//               connectivityStatus->setState(get<1>(val_state));

               conStatus.insert(std::make_pair(souId, connectivityStatus));

               track_nodes.push(souId);

                   //sortConStatus(conStatus);

               printMaps(conStatus);
            }

        }else if(temp_id == myId && temp_wsm->getEndMsg() == true) {
            // cancelEvent(start_flooding);
            EV << "End MSG here..." << endl;

            int node_id = temp_wsm->getSouId();

            EV << "Sou Id: " << node_id << endl;
            map<int,MDP*>::iterator it = conStatus.find(node_id);

            // Should I run the value iteration here again?

            if(it != conStatus.end()) {
                int id = it->first;
                MDP* temp = it->second;

//                tuple<double, int> val_state = valueIter(temp);
//
//                temp->setVal(get<0>(val_state));
//                temp->setPervState(temp->getCurState());
//                temp->setState(get<1>(val_state));


                EV << "id: " << id << "MDP: " << temp << endl;

                finalStatus.insert(std::make_pair(id, temp));
            }

            compareStatus(conStatus, finalStatus);

            vector<pair<int, MDP*>> sorted = sortConStatus(conStatus);

            printMaps(sorted);
            printMaps(conStatus);
        }
    }
}

map<int, MDP*> RSU11p::compareStatus(map<int, MDP*> con, map<int, MDP*> final) {
    map<int, MDP*> res;

    for(auto &c: con) {
        for(auto &f: final) {
            if(c.first == f.first) {
                res.insert(std::make_pair(f.first, c.second));
            } else {
                c.second->setVal(0.0);

                res.insert(std::make_pair(c.first, c.second));
            }
        }
    }

    return res;
}

void RSU11p::finish() {
    BaseWaveApplLayer::finish();

    EV << "When does this work? " << endl;

    Logging* log = new Logging();

    EV << "Feq_msg" << endl;
    printMaps(feq_msg);

    EV << "Prob_feq" << endl;
    printMaps(probablitiy_feq);


    log->storeNeighbours(neighbours, "./results/results.txt");
    log->storeConStatus(conStatus, "./results/results_MDP.txt", "./results/results_MDP.csv");

    EV << "Cycles : " << cycles << endl;


//    log.open("./results/results_MDP.txt");
////    vector<pair<int, MDP*>> resultedConStatus = sortConStatus(conStatus);
//    log << "-Node_Id | Value - | -HopCount- " << endl;
//    for(auto &key: conStatus) {
//        log << key.first << "|" << key.second->getVal() << "|" << key.second->getHopCount()  << endl;
//
//    }
//    log.close();
//
//    log.open("./results/final_status.txt");
//    //    vector<pair<int, MDP*>> resultedConStatus = sortConStatus(conStatus);
//    log << "-Node_Id | Value - | -HopCount- " << endl;
//    for(auto &key: finalStatus) {
//        log << key.first << "|" << key.second->getVal() << "|" << key.second->getHopCount()  << endl;
//
//    }
//    log.close();
//
//

    // map<int, MDP*> final_MDP_res = compareStatus(conStatus, finalStatus);


//    log.open("./results/MPD_Status_f.txt");
//    log << "-Node_Id | Value - | -HopCount- " << endl;
//    for(auto &key: final_MDP_res) {
//        log << key.first << "|" << key.second->getVal() << "|" << key.second->getHopCount()  << endl;
//
//    }
//    log.close();



//    log.open("./results/MDP_Sorted.txt");
//    log << "-Node_Id | Value - | -HopCount- " << endl;
//    for (auto &key: sortedStatus) {
//        log << key.first << "|" << key.second->getVal() << "|" << key.second->getHopCount()  << endl;
//    }
//    log.close();

}

int RSU11p::search() {
    EV << "Stack here: " << endl;

    int top_node = track_nodes.top();

    EV << "stack at top" << top_node << endl;
    return top_node;
}

bool sortBysec(const pair<int, MDP*> &a, const pair<int, MDP*> &b) {
    return (a.second->getVal() < b.second->getVal());
}

// ranking table
vector<pair<int, MDP*>> RSU11p::sortConStatus(map<int, MDP*> constatu) {
    vector<pair<int, MDP*>> sortedConStatus;

    auto cmp = [](const pair<int, MDP*> &a, const pair<int, MDP*> &b) {
        if(a.second->getVal() < b.second->getVal()) {
            return a.second->getVal() < b.second->getVal();
        }
        return b.second->getVal() < a.second->getVal();
      // return a.second->getVal() < b.second->getVal() ? b.second->getVal() : a.second->getVal();
    };

    map<int, MDP*>::iterator it2;
    for(it2=constatu.begin(); it2!=constatu.end(); it2++) {
        int id = it2->first;
        MDP* temp = it2->second;
        sortedConStatus.push_back(std::make_pair(id, temp));
    }

    sort(sortedConStatus.begin(), sortedConStatus.end(), sortBysec);

    return sortedConStatus;
}


