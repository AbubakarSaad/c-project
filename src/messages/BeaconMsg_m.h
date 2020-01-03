//
// Generated file, do not edit! Created by nedtool 5.5 from src/messages/BeaconMsg.msg.
//

#ifndef __VEINS_BEACONMSG_M_H
#define __VEINS_BEACONMSG_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0505
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif

// cplusplus {{
#include "veins/base/utils/Coord.h"
#include "veins/modules/messages/DemoSafetyMessage_m.h"
#include "veins/base/utils/SimpleAddress.h"
// }}


namespace veins {

/**
 * Class generated from <tt>src/messages/BeaconMsg.msg:32</tt> by nedtool.
 * <pre>
 * packet BeaconMsg extends DemoSafetyMessage
 * {
 *     Coord messageOriginPosition;
 *     double senderDirection;
 *     string nodesIds;
 *     LAddress::L2Type senderAddress = -1;
 *     int serial = 0;
 *     int hop;
 * }
 * </pre>
 */
class BeaconMsg : public ::veins::DemoSafetyMessage
{
  protected:
    Coord messageOriginPosition;
    double senderDirection;
    ::omnetpp::opp_string nodesIds;
    LAddress::L2Type senderAddress;
    int serial;
    int hop;

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
    virtual LAddress::L2Type& getSenderAddress();
    virtual const LAddress::L2Type& getSenderAddress() const {return const_cast<BeaconMsg*>(this)->getSenderAddress();}
    virtual void setSenderAddress(const LAddress::L2Type& senderAddress);
    virtual int getSerial() const;
    virtual void setSerial(int serial);
    virtual int getHop() const;
    virtual void setHop(int hop);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const BeaconMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, BeaconMsg& obj) {obj.parsimUnpack(b);}

} // namespace veins

#endif // ifndef __VEINS_BEACONMSG_M_H

