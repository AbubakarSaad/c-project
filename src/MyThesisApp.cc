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

#include "MyThesisApp.h"
#include <math.h>

Define_Module(MyThesisApp);


void MyThesisApp::initialize(int stage)
{
    BaseWaveApplLayer::initialize(stage);

    EV << "Initialize the stage1111?" << endl;

    if (stage == 0) {
        state = 0;

        interval_flood = simTime().dbl();
        sendMessage = false;
        sendMessageData = false;
        correctNodeMsg = false;

        start_flooding_node = new cMessage("flooding_nodes");
        stop_flooding_node = new cMessage("stop_flooding");
        start_processing = new cMessage("processing");
        start_process_data = new cMessage("processing_data");
        ack_to_rsu = new cMessage("ACKTO_RSU");
        end_processing = new cMessage("END");


        // connectivity status

        //scheduleAt(simTime() + 100, start_processing);
        //scheduleAt(simTime() + 800, end_processing);

    }
}

void MyThesisApp::onWSA(WaveServiceAdvertisment* wsa) {
    if (currentSubscribedServiceId == -1) {
        mac->changeServiceChannel(wsa->getTargetChannel());
        currentSubscribedServiceId = wsa->getPsid();
        if  (currentOfferedServiceId != wsa->getPsid()) {
            stopService();
            startService((Channels::ChannelNumber) wsa->getTargetChannel(), wsa->getPsid(), "Mirrored Traffic Service");
        }
    }
}


void MyThesisApp::printMaps(map<int, vector<int>> const &m) {
    EV << "PrintMaps for Neighbours" << endl;
    for(auto &key: m) {
          EV << key.first << " | " << key.second[0] << " | " << key.second[1] << " | " << key.second[2] << endl;
     }
}


void MyThesisApp::printMaps(map<int, MDP*> const &m) {
    EV << "PrintMaps for MDP" << endl;
}

void MyThesisApp::printMaps(map<int, string> const &m) {
    EV << "PrintMaps for Nodes Ids" << endl;
    for(auto &key: m) {
        EV << key.first << "|" << key.second.c_str() << endl;
    }
}

string MyThesisApp::buildPaths(string path) {
    return "failed";
}

// Ryan === Comment out my method of onBSM and create your own for flooding.
// void MyThesisApp::onBSM(BasicSafetyMessage* bsm) {}

void MyThesisApp::onBSM(BasicSafetyMessage* bsm) {
    EV << "ONBSM" << endl;

    // Nodes (Vehicle) ==== V2V or V2I commiuncation
    findHost()->getDisplayString().updateWith("r=16,yellow");

    if(BeaconMsg* temp_bsm = dynamic_cast<BeaconMsg*>(bsm)) {
        int source_id = temp_bsm->getSenderAddress();
        int hop_end_count = temp_bsm->getSerial();
        int hop_count = temp_bsm->getHop();
        int rsu_id = temp_bsm->getRsuID();
        RSU_id = temp_bsm->getRsuID();
        rsu_id_flag = true;
        rsu_ids.push_back(rsu_id);


        neighbours.insert(pair<int, vector<int> > (source_id, vector<int>()));
        neighbours[source_id].push_back(hop_count);
        neighbours[source_id].push_back(hop_end_count);
        neighbours[source_id].push_back(rsu_id);


        if(sendMessage == false){
            //BeaconMsg *msg = new BeaconMsg("Floods_nodes");
            temp_bsm->setSenderAddress(myId);
            temp_bsm->setSerial(3);
            temp_bsm->setHop(hop_count + 1);
            temp_bsm->setRsuID(RSU_id);

            sendMessage = true;
            populateWSM(temp_bsm);
            sendDelayedDown(temp_bsm->dup(), 1 + uniform(0.01,0.2));

            scheduleAt(simTime() + 1 + uniform(0.01,0.2), ack_to_rsu);
        }

        EV << "neigbours_CARS" << "RSU_id: " << rsu_ids[0] << endl;
        EV << "My id: " << myId << endl;
        printMaps(neighbours);
    }
}


void MyThesisApp::onWSM(WaveShortMessage* wsm) {
    EV << "ONWSM" << endl;
    findHost()->getDisplayString().updateWith("r=16,green");
    cancelEvent(start_processing);



    if(DataMsg* temp_wsm = dynamic_cast<DataMsg*>(wsm)) {
        EV << "DATAMSG: " << endl;
        int reward = 0;
        int source_id = temp_wsm->getSouId();
        int data_hop = temp_wsm->getHop();
        string nodeIds = temp_wsm->getNodesIds();
        int des_id = temp_wsm->getDesId();

        EV << "SOU ID: " << source_id << endl;
        EV << "data_hop: " << data_hop << endl;
        EV << "DES ID: " <<  des_id << endl;

        // getting msg from RSU
        if(temp_wsm->getAck() == true) {
            if(des_id == myId) {
                EV << "Ack Msg area" << endl;

                nodes_ids.insert(std::make_pair(source_id, nodeIds));

                printMaps(conStatus);
                printMaps(nodes_ids);

                correctNodeMsg = true;
                delete(temp_wsm);
            } else {
                // carry out till it reaches the proper node "connectivity"
                EV << "Replying to the correct node" << endl;
                if(correctNodeMsg == false) {

                    // cancelEvent(start_processing);
                    //scheduleAt(simTime() + 100 + uniform(0.01,0.2), start_process_data);


                    string nodeIds_add = nodeIds + '-' + to_string(myId);
                    temp_wsm->setNodesIds(nodeIds_add.c_str());
                    temp_wsm->setHop(data_hop + 1);
                    temp_wsm->setNodeState(1);
                    temp_wsm->setPervState(0);
                    //temp_wsm->setSouId(temp_wsm->getSouId());
                    populateWSM(temp_wsm);


                    correctNodeMsg = true;
                    sendDelayedDown(temp_wsm->dup(), 1 + uniform(0.01,0.2));
                }
            }
        } else if(temp_wsm->getEndMsg() == true) {
            // myId
            if(des_id == myId) {
                EV << "REACHED THE DESINTION" << endl;
            } else {
                cancelEvent(end_processing);
                EV << "forwarding the msg" << endl;
                if(endMsg == false) {
                    string nodeIds_add = nodeIds + '-' + to_string(myId).c_str();
                    temp_wsm->setNodesIds(nodeIds_add.c_str());
                    temp_wsm->setHop(data_hop + 1);

                    populateWSM(temp_wsm);

                    endMsg = true;
                    sendDelayedDown(temp_wsm->dup(), 1 + uniform(0.01,0.2));


                    scheduleAt(simTime() + 1, end_processing);
                }
            }

            // else

        } else if(temp_wsm->getAckRsu() == true) {

            if(rsu_id_flag == true) {
                // forward the message
                if(temp_wsm->getHop() <= 4 && temp_wsm->getDesId() == RSU_id && sendMessageData == false) {
                  EV << "MSG here" << endl;
                  EV << "MSG: " << des_id  << ":" << source_id << endl;

                  EV << "Path: In forwarding " << nodeIds << endl;

                  it = find(forward_track.begin(), forward_track.end(), temp_wsm->getSouId());
                  if(it != forward_track.end()) {
                      sendMessageData = true;
                  } else {
                      forward_track.push_back(temp_wsm->getSouId());

                      sendMessageData = false;
                  }

                  string nodeIds_add = nodeIds + '-' + to_string(myId);
                  temp_wsm->setName("Forwarding");
                  temp_wsm->setNodesIds(nodeIds_add.c_str());
                  temp_wsm->setHop(data_hop + 1);
                  temp_wsm->setNodeState(1);
                  temp_wsm->setPervState(0);
                  populateWSM(temp_wsm);

                  //sendMessageData = false;
                  sendDelayedDown(temp_wsm->dup(), 1 + uniform(0.01,0.2));
                } else {
                  EV <<"We will delete or drop this message" << endl;
                  sendMessageData = true;

                  // delete the msg if the temp_wsm is greater then 4
                }
            }
        }  else {
            // Getting msg from other nodes
            // des_id == rsu_id
            EV << "Find RSU" << endl;
//            if(sendMessageData == false && temp_wsm->getAckRsu() == false) {
//                string nodeIds_add = nodeIds + '-' + to_string(myId).c_str();
//                temp_wsm->setNodesIds(nodeIds_add.c_str());
//                populateWSM(temp_wsm);
//
//                sendMessageData = true;
//                sendDelayedDown(temp_wsm->dup(), 1 + uniform(0.01,0.2));
//                // scheduleAt(simTime() + 1 + uniform(0.01,0.2), start_processing); This changes the values os
//            }
        }
    }
}


void MyThesisApp::handleSelfMsg(cMessage* msg) {
    if(msg == start_processing){
        // send the data to the RSU
        // Every car has RSU id
        EV << "Start sending processing msg" << endl;
        DataMsg* data_msg = new DataMsg("Data");
        data_msg->setHop(4);
        data_msg->setNodesIds(to_string(myId).c_str());
        data_msg->setSouId(myId);
        data_msg->setDesId(RSU_id);

        EV << "RSU_id_WSM: " << RSU_id <<endl;

        populateWSM(data_msg);
        sendDelayedDown(data_msg->dup(), 1 + uniform(0.01,0.2));
    } else if (msg == end_processing) {
        cancelEvent(start_processing);
        cancelEvent(ack_to_rsu);
        cancelEvent(end_processing);

        EV << "Start the end processing" << endl;
//        DataMsg* end_msg = new DataMsg("End");
//
//        end_msg->setHop(1);
//        end_msg->setSouId(myId);
//        end_msg->setDesId(RSU_id);
//        end_msg->setEndMsg(true);
//
//        populateWSM(end_msg);
//        sendDelayedDown(end_msg->dup(), 1 + uniform(0.01,0.2));




    } else if (msg == ack_to_rsu) {
      EV << "ACK to RSU as soon as you receive the beacon msg" << endl;

      DataMsg* ack_rsu = new DataMsg("ACK_RSU");

      const char* nodeId = to_string(myId).c_str();
      ack_rsu->setNodesIds(nodeId);
      ack_rsu->setHop(1);
      ack_rsu->setSouId(myId);
      ack_rsu->setDesId(RSU_id);
      ack_rsu->setAckRsu(true);
      ack_rsu->setNodeState(state);
      ack_rsu->setPervState(0);

      populateWSM(ack_rsu);
      sendDown(ack_rsu->dup());
    } else {
        BaseWaveApplLayer::handleSelfMsg(msg);
    }
}


void MyThesisApp::handlePositionUpdate(cObject* obj) {
    BaseWaveApplLayer::handlePositionUpdate(obj);

    EV << "Position Update " << endl;
    EV << "simTime: " << simTime() << endl;

    double sim_time = simTime().dbl();
    if(sim_time == 800) {
        scheduleAt(simTime(), end_processing);
    }

//    if(fmod(sim_time, 20) == 0 && sendMessage == false){
//        //m = MDP()
//
//    }
}

void MyThesisApp::finish() {
    BaseWaveApplLayer::finish();

    EV << "When does this work? " << endl;

    // Send the message to RSU if "this" is done


     ofstream log;
     ostringstream o;

     log.open("./results/node_results.txt");
     log << "-hop count | vector for source id | hop_end_count-" << endl;
     for(auto &key: neighbours) {
         // pair<int, vector<int>> key(neighbour);
         log << key.first << " | " << key.second[0] << " | " << key.second[1] << endl;
     }
     log.close();
}





