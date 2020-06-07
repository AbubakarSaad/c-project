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

        // Retrieving information from omnetpp.ini
        request_interval_size = par("request_interval").doubleValue();
        request_tolerance_size = par("request_tolerance").doubleValue();

        scheduleAt(simTime() + request_interval_size, start_flooding);
    }
}

void RSU11p::printMaps(map<int, vector<int>> const &m) {
    for(auto &key: m) {
          EV << key.first << " | " << key.second[0] << " | " << key.second[1] << " | " << key.second[2] << endl;
     }
}


void RSU11p::printMaps(map<int, MDP*> const &m) {
    for(auto &key: m) {
        EV << key.first << "|" << key.second->getAction() << "|" << key.second->getState() << endl;
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

    } else if (msg == stop_flooding) {


    }  else if (msg == ack_msg) {
        cancelEvent(ack_msg);

        DataMsg* ack = new DataMsg("ACK");


    }
}

void RSU11p::onWSA(WaveServiceAdvertisment* wsa) {
    //if this RSU receives a WSA for service 42, it will tune to the chan
    EV << "RSUWSA" << endl;
    if (wsa->getPsid() == 42) {
        mac->changeServiceChannel(wsa->getTargetChannel());
    }
}

void RSU11p::statusUpdate(int id) {
    EV << "Print the ID: " << id << endl;
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

void RSU11p::onWSM(WaveShortMessage* wsm) {
    EV << "RSUWSM" << endl;
    // cancelEvent(start_flooding);

    // if the data message finds is here. hit the event which will stop the data msg completely.
    if(DataMsg* temp_wsm = dynamic_cast<DataMsg*>(wsm)) {
        // msg recieved
        int temp_id = temp_wsm->getDesId();

        EV << "des: " << temp_id << endl;

        if(temp_id == myId) {
            // store this in the rank table
            int souId = temp_wsm->getSouId();
            string hop_path = temp_wsm->getNodesIds();
            int hop_count = temp_wsm->getHop();

            // message has been recieved. Update the status for this node.
            statusUpdate(souId);

            // send the ack back
            //scheduleAt(simTime() + 1 + uniform(0.01,0.2), ack_msg);
            DataMsg* ack = new DataMsg("ACK");
            ack->setSouId(myId);
            ack->setDesId(souId);
            ack->setAck(true);

            // data
            ack->setNodeState("CONNECTED");
            ack->setAction("Connected-RSU");
            ack->setTranscation("RSU-to-NODE");
            populateWSM(ack);

            sendDelayedDown(ack->dup(), 1 + uniform(0.01,0.2));
        }
    }
}

void RSU11p::finish() {
    BaseWaveApplLayer::finish();

    EV << "When does this work? " << endl;

    ofstream log;
    ostringstream o;

    log.open("./results/results.txt");
    log << "-hop count | vector for source id | hop_end_count-" << endl;
    for(auto &key: neighbours) {
     // pair<int, vector<int>> key(neighbour);
        log << key.first << " | " << key.second[0] << " | " << key.second[1] << endl;
    }
    log.close();

}
