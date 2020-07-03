//
// Generated file, do not edit! Created by nedtool 5.3 from src/messages/DataMsg.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __DATAMSG_M_H
#define __DATAMSG_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0503
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "veins/base/utils/Coord.h"
#include "veins/modules/messages/WaveShortMessage_m.h"
// }}

/**
 * Class generated from <tt>src/messages/DataMsg.msg:27</tt> by nedtool.
 * <pre>
 * packet DataMsg extends WaveShortMessage
 * {
 *     // meta info
 *     Coord messageOriginPosition;
 *     double senderDirection;
 *     string nodesIds;
 *     int hop;
 *     int souId;
 *     int desId;
 *     bool ack = false;
 *     bool ackRsu = false;
 *     bool endMsg = false;
 * 
 *     // data info
 *     string nodeState;
 *     string action;
 *     string transcation;
 * 
 * }
 * </pre>
 */
class DataMsg : public ::WaveShortMessage
{
  protected:
    Coord messageOriginPosition;
    double senderDirection;
    ::omnetpp::opp_string nodesIds;
    int hop;
    int souId;
    int desId;
    bool ack;
    bool ackRsu;
    bool endMsg;
    ::omnetpp::opp_string nodeState;
    ::omnetpp::opp_string action;
    ::omnetpp::opp_string transcation;

  private:
    void copy(const DataMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const DataMsg&);

  public:
    DataMsg(const char *name=nullptr, short kind=0);
    DataMsg(const DataMsg& other);
    virtual ~DataMsg();
    DataMsg& operator=(const DataMsg& other);
    virtual DataMsg *dup() const override {return new DataMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual Coord& getMessageOriginPosition();
    virtual const Coord& getMessageOriginPosition() const {return const_cast<DataMsg*>(this)->getMessageOriginPosition();}
    virtual void setMessageOriginPosition(const Coord& messageOriginPosition);
    virtual double getSenderDirection() const;
    virtual void setSenderDirection(double senderDirection);
    virtual const char * getNodesIds() const;
    virtual void setNodesIds(const char * nodesIds);
    virtual int getHop() const;
    virtual void setHop(int hop);
    virtual int getSouId() const;
    virtual void setSouId(int souId);
    virtual int getDesId() const;
    virtual void setDesId(int desId);
    virtual bool getAck() const;
    virtual void setAck(bool ack);
    virtual bool getAckRsu() const;
    virtual void setAckRsu(bool ackRsu);
    virtual bool getEndMsg() const;
    virtual void setEndMsg(bool endMsg);
    virtual const char * getNodeState() const;
    virtual void setNodeState(const char * nodeState);
    virtual const char * getAction() const;
    virtual void setAction(const char * action);
    virtual const char * getTranscation() const;
    virtual void setTranscation(const char * transcation);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const DataMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, DataMsg& obj) {obj.parsimUnpack(b);}


#endif // ifndef __DATAMSG_M_H

