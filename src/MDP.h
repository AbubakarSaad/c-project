/*
 * MDP.h
 *
 *  Created on: Jan 27, 2020
 *      Author: abu
 */
class MDP {
    struct MDPinfo {
        string state_of_node;
        string action; // Has to be enum
        string transcation; // This will perform the action
        int reward; // Needs to be calculated
    };

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
     * Kind of actions and transcation
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


public:
    void initialize();

    void getState();
    void setState();

    void getAction();
    void setAction();

    void getTranscation();
    void setTranscation();

    void getReward();
    void setReward();

};



