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

MDP::MDP() {
    state_of_node = NOT_CONNECTED;
    action =  NOT_CONNECTED;
    transcation = NOT_CONNECTED;
    reward = 0;
}

MDP::~MDP() {

}

string MDP::getState() {
    return state_of_node;
}

void MDP::setState(string state) {
    state_of_node = state;
}

string MDP::getAction() {
    return action;
}

void MDP::setAction(string act) {
    action = act;
}

string MDP::getTranscation() {
    return transcation;
}

void MDP::setTranscation(string trans) {
    transcation = trans;
}

int MDP::getReward() {
    return reward;
}

void MDP::setReward(int result) {
    reward = result;
}

int MDP::calculateReward(int data_hop) {
    // calculate the reward here
    switch(data_hop) {
        case 1:
            return reward - 0;
        case 2:
            return reward - 2;
        case 3:
            return reward - 4;
        case 4:
            return reward - 6;
        default:
            return reward - 8;
    }

    return 0;
}

// Ege === Create your function here

