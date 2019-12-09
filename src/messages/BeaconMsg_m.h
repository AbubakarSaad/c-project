//
// Generated file, do not edit! Created by nedtool 5.3 from src/messages/BeaconMsg.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __BEACONMSG_M_H
#define __BEACONMSG_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0503
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "veins/base/utils/Coord.h"
#include "veins/modules/messages/BasicSafetyMessage_m.h"
// }}

/**
 * Class generated from <tt>src/messages/BeaconMsg.msg:28</tt> by nedtool.
 * <pre>
 * packet BeaconMsg extends BasicSafetyMessage
 * {
 *     Coord messageOriginPosition;
 *     double senderDirection;
 *     string nodesIds;
 *     int hop;
 *     int hopAddress;
 * }
 * </pre>
 */
class BeaconMsg : public ::BasicSafetyMessage
{
  protected:
    Coord messageOriginPosition;
    double senderDirection;
    ::omnetpp::opp_string nodesIds;
    int hop;
    int hopAddress;

  private:
    void copy(const BeaconMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const BeaconMsg&);

  public:
    BeaconMsg(const char *name=nullptr, short kind=0);
    BeaconMsg(const BeaconMsg& other);
    virtual ~BeaconMsg();
    BeaconMsg& operator=(const BeaconMsg& other);
    virtual BeaconMsg *dup() const override {return new BeaconMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual Coord& getMessageOriginPosition();
    virtual const Coord& getMessageOriginPosition() const {return const_cast<BeaconMsg*>(this)->getMessageOriginPosition();}
    virtual void setMessageOriginPosition(const Coord& messageOriginPosition);
    virtual double getSenderDirection() const;
    virtual void setSenderDirection(double senderDirection);
    virtual const char * getNodesIds() const;
    virtual void setNodesIds(const char * nodesIds);
    virtual int getHop() const;
    virtual void setHop(int hop);
    virtual int getHopAddress() const;
    virtual void setHopAddress(int hopAddress);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const BeaconMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, BeaconMsg& obj) {obj.parsimUnpack(b);}


#endif // ifndef __BEACONMSG_M_H

