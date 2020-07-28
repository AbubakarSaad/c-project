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

#include "MDP.h"

MDP::MDP(int state) {
    state_of_node = state;
}

int MDP::getCurState() {
    return state_of_node;
}

int MDP::getPervState() {
    return perv_state_of_node;
}

// 0 == !C, 1 == V, 2 == R, 3 == VR transition probablity matrix
void MDP::setState(int state) {
    state_of_node = state;
}

void MDP::setPervState(int preState) {
    perv_state_of_node = preState;
}

void MDP::setHopCount(int hop) {
    final_hop_count = hop;
}

int MDP::getHopCount(){
    return final_hop_count;
}

void MDP::setVal(double val) {
    value = val;
}

double MDP::getVal() {
    return value;
}

bool MDP::isEndState() {
    // Hop can only be 4
    return final_hop_count == 4;
}

double MDP::getDiscount() {
    return discount_factor;
}

vector<string> MDP::actions(int state) {
    vector<string> actions;

    if(state_of_node == 0){
        actions.push_back("CONNECTED_TO_SELF");
    }
    if(state_of_node <= 1) {
        actions.push_back("CONNECTED_TO_V");
    }
    if(state_of_node <= 2) {
        actions.push_back("CONNECTED_TO_R");
    }

    return actions;
}


vector<tuple<int, double, int>> MDP::succProbReward(int state, string action, double prob[3][3], int pervState) {
   // newState, prob, reward
    vector<tuple<int, double, int>> result;

    double p = prob[pervState][state];

    if(action == "CONNECTED_TO_SELF") {
        result.push_back(std::make_tuple(state, p, -1));
    }else if(action == "CONNECTED_TO_V") {
        result.push_back(std::make_tuple(state, p, 1));
        //result.push_back(std::make_tuple(state, 0.5, 1));
    }else if(action == "CONNECTED_TO_R") {
        result.push_back(std::make_tuple(state, p, 5));
        // result.push_back(std::make_tuple(state, 0.5, 0));
    }

    return result;
}


// Ege === Create your function here

