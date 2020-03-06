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

Define_Module(MyThesisApp);


void MyThesisApp::initialize(int stage)
{
    BaseWaveApplLayer::initialize(stage);

    EV << "Initialize the stage1111?" << endl;

    if (stage == 0) {
        init_obj->state_of_node = NOT_CONNECTED;
        init_obj->action =  NOT_CONNECTED;
        init_obj->transcation = NOT_CONNECTED;
        init_obj->reward = 0;

        is_flooded = false;
        is_paths = false; // to build paths;
        interval_flood = simTime();
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

    // 1. store the paths to your neighbours (done)
    // 2. Have RSU id (done)
    // 3. Send it back to the RSU
    // 4. RSU saves the path that is send back

    return "failed";
}

void MyThesisApp::onBSM(BasicSafetyMessage* bsm) {
    EV << "ONBSM" << endl;

    // Nodes (Vehicle) ==== V2V or V2I commiuncation
    findHost()->getDisplayString().updateWith("r=16,yellow");

    if(simTime() >= 15 && simTime() <= 20 && !is_flooded) {
        EV << "15 and UP" << endl;
        if(BeaconMsg* temp_bsm = dynamic_cast<BeaconMsg*>(bsm)) {
            int source_id = temp_bsm->getSenderAddress();
            int hop_end_count = temp_bsm->getSerial();
            int hop_count = temp_bsm->getHop();
            RSU_id = temp_bsm->getRsuID();

            neighbours.insert(pair<int, vector<int> > (hop_count, vector<int>()));
            neighbours[hop_count].push_back(source_id);
            neighbours[hop_count].push_back(hop_end_count);


            // "Kinda" flood networks
            temp_bsm->setSenderAddress(myId);

            hop_end_count = hop_end_count - 1;
            temp_bsm->setSerial(hop_end_count);

            hop_count = hop_count + 1;
            temp_bsm->setHop(hop_count);

            if(temp_bsm->getAckMsg() == false) {
                populateWSM(bsm);
                is_flooded = true;
                scheduleAt(simTime() + 1 + uniform(0.01,0.2), temp_bsm->dup());
            }

        }
    }

    if(simTime() >= 25 && simTime() <= 35 && !is_paths) {
        EV << "25 and up" << endl;
        if(Ack* temp_ack = dynamic_cast<Ack*>(bsm)){
            EV << "ON25" << endl;
            EV << "build paths" << endl;
            // Send it back to RSU
            // This will also attach the path, if they don't have the correct path to the destination
            int desID = RSU_id;
            int srcID = myId;
            string path = to_string(myId);

            Ack* ack_bsm = new Ack("ACK");

            ack_bsm->setDesID(desID);
            ack_bsm->setSrcID(srcID);
            ack_bsm->setPath(path.c_str());

            is_paths = true;




            if(ack_bsm->getDesID() != myId && temp_ack->getAckMsg() == true
                    ) {

                populateWSM(ack_bsm);
                scheduleAt(simTime() + 1 + uniform(0.01,0.2), ack_bsm->dup());
            // sendDelayedDown(ack_bsm->dup(), 1 + uniform(0.01,0.2));

            } else if (temp_ack->getAckMsg()) {

                string pre_path = temp_ack->getPath();
                string path = pre_path + "-" + to_string(myId);


                populateWSM(ack_bsm);
                scheduleAt(simTime() + 1 + uniform(0.01,0.2), ack_bsm->dup());
                // sendDelayedDown(ack_bsm->dup(), 1 + uniform(0.01,0.2));

            }
        }
    }
}


void MyThesisApp::onWSM(WaveShortMessage* wsm) {

    EV << "ONWSM" << endl;
    findHost()->getDisplayString().updateWith("r=16,green");



//    if (mobility->getRoadId()[0] != ':') traciVehicle->changeRoute(wsm->getWsmData(), 9999);
    if(wsm->getSenderAddress() != myId) {
//        WaveShortMessage* wsm1 = new WaveShortMessage();

        wsm->setSenderAddress(myId);
        wsm->setSerial(3);
        scheduleAt(simTime() + 3 + uniform(0.01,0.2), wsm->dup());
    }
}


void MyThesisApp::handleSelfMsg(cMessage* msg) {

    EV << "Reward: " << init_obj->reward << endl;
    if (BeaconMsg* bsm = dynamic_cast<BeaconMsg*>(msg)) {
        //send this message on the service channel until the counter is 3 or higher.
        //this code only runs when channel switching is enabled
        if(bsm->getAckMsg() == false) {
            if(bsm->isSelfMessage()) {
                sendDelayedDown(bsm->dup(), 1 + uniform(0.01,0.2));
            }
        }

    }else if(Ack* ack = dynamic_cast<Ack*>(msg)) {
        if(ack->getAckMsg()) {
            if(ack->isSelfMessage()) {
                sendDelayedDown(ack->dup(), 1 + uniform(0.01, 0.2));
            }
        }
    }
    else {
        BaseWaveApplLayer::handleSelfMsg(msg);
    }
}


void MyThesisApp::handlePositionUpdate(cObject* obj) {
    BaseWaveApplLayer::handlePositionUpdate(obj);

    EV << "Position Update " << endl;
    // Maybe don't use ack, do a boolean in beacon that acts as a ack...




    // Run this after every 20s interval
    // 20s simTime(); flood the network
    // else just wait
    if (simTime() < 50) {
       // if (sentMessage == false) {
        findHost()->getDisplayString().updateWith("r=16,red");
        BeaconMsg* wsm = new BeaconMsg();
    }

    if(simTime() > 50) {
        EV << "Stopping the flooding" << endl;
    }
}







