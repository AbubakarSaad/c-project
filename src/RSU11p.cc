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

Define_Module(veins::RSU11p);
using namespace veins;

void RSU11p::initialize(int stage) {
    // Start the flooding after 10s and last for 10s = total of 20s
    DemoBaseApplLayer::initialize(stage);

    if(stage == 0) {
        EV << "Init stage of RSU" << endl;

        BeaconMsg* bsm = new BeaconMsg("Beacon");
        populateWSM(bsm);
        scheduleAt(simTime() + 15, bsm->dup());

    }else if (stage == 1) {

        EV << "Stage 1 in RSU" << endl;

    }

}

void RSU11p::handleSelfMsg(cMessage* msg) {

    if(BeaconMsg* bsm = dynamic_cast<BeaconMsg*> (msg)){
        string temp_ids = "";
        BeaconMsg* temp_bsm = new BeaconMsg("Beacon");

        temp_ids = temp_bsm->getNodesIds();

        if(bsm->isSelfMessage()) {
           if(simTime() >= 15 && simTime() <= 20) {
               temp_bsm->setSenderAddress(myId);
               //temp_bsm->setNodesIds(to_string(myId).c_str());
               temp_bsm->setSerial(4);

               temp_bsm->setHop(1);

               populateWSM(temp_bsm);
               sendDown(temp_bsm->dup());
           }
       }else if (simTime() > 20 && simTime() <= 35 ) {

       }
    } else {
        DemoBaseApplLayer::handleSelfMsg(msg);
    }

}

void RSU11p::onWSA(DemoServiceAdvertisment* wsa) {
    //if this RSU receives a WSA for service 42, it will tune to the chan
    EV << "RSUWSA" << endl;
    if (wsa->getPsid() == 42) {
        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel()));
    }
}
void RSU11p::onWSM(BaseFrame1609_4* wsm) {
    EV << "RSUWSM" << endl;
    //this rsu repeats the received traffic update in 2 seconds plus some random delay
    EV << "My id: " << myId << endl;
    //wsm->setSenderAddress(myId);
    //sendDelayedDown(wsm->dup(), 1 + uniform(0.01,0.2));
}

void RSU11p::onBSM(DemoSafetyMessage* bsm) {
    EV << "RSUBSM" << endl;

    if(BeaconMsg* temp_bsm = dynamic_cast<BeaconMsg*>(bsm)) {

        if(simTime() > 15 && simTime() < 20 && !is_flooded) {

           int source_id = temp_bsm->getSenderAddress();
           int hop_end_count = temp_bsm->getSerial();
           int hop_count = temp_bsm->getHop();

           neighbours.insert(pair<int, vector<int> > (hop_count, vector<int>()));
           neighbours[hop_count].push_back(source_id);
           neighbours[hop_count].push_back(hop_end_count);

           // "Kinda" flood networks
           temp_bsm->setSenderAddress(myId);

           hop_end_count = hop_end_count - 1;
           temp_bsm->setSerial(hop_end_count);

           hop_count = hop_count + 1;
           temp_bsm->setHop(hop_count);

           populateWSM(bsm);
           is_flooded = true;
           scheduleAt(simTime() + 1 + uniform(0.01,0.2), temp_bsm->dup());

       }

    }


}












