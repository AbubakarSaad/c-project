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

using namespace veins;

Define_Module(veins::MyThesisApp);


void MyThesisApp::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);

    EV << "Initialize the stage1111?" << endl;

    if (stage == 0) {
        init_obj->state_of_node = NOT_CONNECTED;
        init_obj->action =  NOT_CONNECTED;
        init_obj->transcation = NOT_CONNECTED;
        init_obj->reward = 0;

        is_flooded = false;
        interval_flood = simTime();

    }
}

void MyThesisApp::onWSA(DemoServiceAdvertisment* wsa) {
    if (currentSubscribedServiceId == -1) {
        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel()));
        currentSubscribedServiceId = wsa->getPsid();
        if  (currentOfferedServiceId != wsa->getPsid()) {
            stopService();
            startService(static_cast<Channel>(wsa->getTargetChannel()), wsa->getPsid(), "Mirrored Traffic Service");
        }
    }
}

string MyThesisApp::buildPaths(string path) {

    vector <int> tokens;

    stringstream check1(path);

    string intermediate;

    while(getline(check1, intermediate, '-')) {
        tokens.push_back(stoi(intermediate));
    }

    if(tokens.size() > 1) {
        return "worked";
    }

    return "failed";
}

void MyThesisApp::onBSM(DemoSafetyMessage* bsm) {
    EV << "ONBSM" << endl;
    findHost()->getDisplayString().updateWith("r=16,yellow");

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



            // Changing the parameters
        }

    }

}


void MyThesisApp::onWSM(BaseFrame1609_4* wsm) {

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
    //BaseWaveApplLayer::handleSelfMsg(msg);
    EV << "handleselfmsg " << endl;


    EV << "Reward: " <<init_obj->reward << endl;
    if (BeaconMsg* bsm = dynamic_cast<BeaconMsg*>(msg)) {
        //send this message on the service channel until the counter is 3 or higher.
        //this code only runs when channel switching is enabled
        if(bsm->isSelfMessage()) {
            sendDelayedDown(bsm->dup(), 1 + uniform(0.01,0.2));
        }

    }
    else {
        DemoBaseApplLayer::handleSelfMsg(msg);
    }
}


void MyThesisApp::handlePositionUpdate(cObject* obj) {
    DemoBaseApplLayer::handlePositionUpdate(obj);

    EV << "Position Update " << endl;

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







