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

using namespace std;

class MDP {
    /**
     * State of the Nodes
     */
    enum StateOfNodes {
        NOT_CONNECTED,
        RSU,
        NODE,
        BOTH
    };

    /**
     * Kind of actions and transaction
     */
    enum NodeActions {
        CONNECTING_TO_RSU,
        CONNECTING_TO_NODE,
        CONNECTING_TO_BOTH,
    };

    /**
     * transactions
     */
    enum NodeTransactions {
        CONNECTED_TO_RSU,
        CONNECTED_TO_NODE,
        CONNECTED_TO_BOTH,
    };


    string state_of_node;
    string action; // Has to be enum
    string transcation; // This will perform the action
    int reward; // Needs to be calculated
public:
    MDP(); // constructor for MDP
    ~MDP();
    string getState();
    void setState(string state);

    string getAction();
    void setAction(string act);

    string getTranscation();
    void setTranscation(string trans);

    int getReward();
    void setReward(int result);

    void calculateReward();
};

#endif /* SRC_MDP_H_ */
