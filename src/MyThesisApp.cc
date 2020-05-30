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
        interval_flood = simTime().dbl();
        sendMessage = false;

        start_flooding_node = new cMessage("flooding_nodes");
        stop_flooding_node = new cMessage("stop_flooding");
        start_processing = new cMessage("processing");
        start_process_data = new cMessage("processing_data");


        // connectivity status
        connectivityStatus = new MDP();

        connectivityStatus->setAction("NOACTION");
        connectivityStatus->setState("NONE");
        connectivityStatus->setTranscation("NONE");
        connectivityStatus->setReward(0);


        scheduleAt(simTime() + 100, start_processing);

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
        rsu_ids.push_back(rsu_id);


        neighbours.insert(pair<int, vector<int> > (source_id, vector<int>()));
        neighbours[source_id].push_back(hop_count);
        neighbours[source_id].push_back(hop_end_count);
        neighbours[source_id].push_back(rsu_id);


        if(sendMessage == false){
            //BeaconMsg *msg = new BeaconMsg("Floods_nodes");
            temp_bsm->setSenderAddress(myId);
            temp_bsm->setSerial(4);
            temp_bsm->setHop(4);

            if(rsu_ids.size() > 0) {
                temp_bsm->setRsuID(rsu_ids[0]);
            }

            sendMessage = true;
            populateWSM(temp_bsm);
            sendDelayedDown(temp_bsm->dup(), 1 + uniform(0.01,0.2));
        }

        EV << "neigbours_CARS" << "RSU_id: " << rsu_ids[0] << endl;
        EV << "My id: " << myId << endl;
        for(auto &key: neighbours) {
             // pair<int, vector<int>> key(neighbour);
             EV << key.first << " | " << key.second[0] << " | " << key.second[1] << " | " << key.second[2] << endl;
         }
    }
}


void MyThesisApp::onWSM(WaveShortMessage* wsm) {

    EV << "ONWSM" << endl;
    findHost()->getDisplayString().updateWith("r=16,green");

    if(DataMsg* temp_wsm = dynamic_cast<DataMsg*>(wsm)) {
        EV << "DATAMSG: " << endl;
        int reward = 10;
        int source_id = temp_wsm->getSouId();
        int data_hop = temp_wsm->getHop();
        string nodeIds = temp_wsm->getNodesIds();
        int rsu_id = temp_wsm->getDesId();


        connectivityStatus->setState("CONNECTED");
        connectivityStatus->setAction("CONNECTION TO THIS NODE");
        connectivityStatus->setTranscation("SEND ACK BACK");

        if(data_hop == 1) {
            connectivityStatus->setReward(reward);
        } else if(data_hop == 2) {
            connectivityStatus->setReward(reward - 2);
        } else if(data_hop == 3) {
            connectivityStatus->setReward(reward - 4);
        } else if(data_hop == 4) {
            connectivityStatus->setReward(reward - 6);
        } else {
            connectivityStatus->setReward(reward - 8);
        }

        // Status of nodes
        conStatus.insert(pair<int, MDP*>(source_id, connectivityStatus));


        EV << "data_hop: " << data_hop << endl;
        EV << "RSU ID: " <<  rsu_id << endl;

        // pass the msg forward till the RSU_id is found
        if(sendMessage == false) {

            cancelEvent(start_processing);
            //scheduleAt(simTime() + 100 + uniform(0.01,0.2), start_process_data);
            string nodeIds_add = nodeIds + '-' + to_string(myId).c_str();
            temp_wsm->setNodesIds(nodeIds_add.c_str());
            temp_wsm->setHop(data_hop - 1);
            //temp_wsm->setSouId(temp_wsm->getSouId());
            populateWSM(temp_wsm);
            sendMessage = true;
            sendDelayedDown(temp_wsm->dup(), 1 + uniform(0.01,0.2));
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
        //if(rsu_ids.size()) {

        //}

        populateWSM(data_msg);
        sendDelayedDown(data_msg->dup(), 1 + uniform(0.01,0.2));
    } else if (msg == start_process_data) {
        EV << "start processing after data is sending" << endl;


    }else {
        BaseWaveApplLayer::handleSelfMsg(msg);
    }
}


void MyThesisApp::handlePositionUpdate(cObject* obj) {
    BaseWaveApplLayer::handlePositionUpdate(obj);

    EV << "Position Update " << endl;
    EV << "simTime: " << simTime() << endl;

    double sim_time = simTime().dbl();
    if(fmod(sim_time, 20) == 0 && sendMessage == false){
        //m = MDP();

    }
}

void MyThesisApp::finish() {
    BaseWaveApplLayer::finish();

    EV << "When does this work? " << endl;

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





