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
    // mapping from action to probability transition matrix
    map<int, vector<double>> actionTransitions;

    /**
     *  where entry (i, j) is the reward associated with taking action j from state j
     */
    double actionRewards[2][2] = {{}}; // 0 == !C, 1 == V, 2 == R, 3 == VR transition probablity matrix
    /**
     * transactions
     */
    double transitionProbab[2][2] = {{}};
    // discount factor
    double discount = 0.5;

    // Total number of states in MDP
    int numStates;

    // Total number of actions in MDP
    int numActions;

    int state_of_node;


public:
    MDP(); // constructor for MDP
    ~MDP();

    // Current State
    int getCurState();

    // Start State
    int startState();

    // End State

    // return the list of actions
    vector<string> actions(int state);

    // return list of (newState, prob, reward) triples
    // state = s, action = a, s'=newState
    // prob = T(s, a, s'), reward= Reward(s, a, s')
    vector<tuple<int, double, int>> succProbReward(int state, string action);
};

#endif /* SRC_MDP_H_ */
