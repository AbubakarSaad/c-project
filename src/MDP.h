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

#ifndef SRC_MDP_H_
#define SRC_MDP_H_

#include <iostream>
#include <stack>
#include <algorithm>
#include <map>
#include <vector>
#include <tuple>

using namespace std;

class MDP {
    /**
     * transactions
     */
    double transitionProbab[3][3] = {{0.33, 0.33, 0.33}, {0.33, 0.33, 0.33}, {0.33, 0.33, 0.33}};
    // discount factor
    double discount_factor = 0.3;

    // Total number of states in MDP
    int numStates;

    // Total number of actions in MDP
    int numActions;

    // state of the node
    int state_of_node;
    int perv_state_of_node;

    // Final hop count
    int final_hop_count;

    // value of the node
    double value = 0;

    // "State" === String
    string state_string;

public:
    MDP(int state); // constructor for MDP
    ~MDP();

    // state string
    string getStateString();
    void setStateString();

    // Current State
    int getCurState();
    int getPervState();

    // Start State
    int startState();

    // set State
    void setState(int state);
    void setPervState(int preState);

    // End State
    void setHopCount(int hop);
    int getHopCount();
    bool isEndState();

    // Discount factor
    double getDiscount();

    // value set
    void setVal(double val);
    double getVal();

    // return the list of actions
    vector<string> actions(int state);

    // return list of (newState, prob, reward) triples
    // state = s, action = a, s'=newState
    // prob = T(s, a, s'), reward= Reward(s, a, s')
    vector<tuple<int, double, int>> succProbReward(int state, string action, double prob[3][3], int pervState);


    // policy or assiging reward



};

#endif /* SRC_MDP_H_ */
