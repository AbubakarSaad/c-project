//
// Generated file, do not edit! Created by nedtool 5.5 from src/messages/DataMsg.msg.
//

#ifndef __DATAMSG_M_H
#define __DATAMSG_M_H

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
// }}

/**
 * Class generated from <tt>src/messages/DataMsg.msg:26</tt> by nedtool.
 * <pre>
 * packet Data
 * {
 *     double senderDirection = 0;
 * 
 *     double messageDirection;
 *     Coord messageOriginPosition;
 *     double messageROI;
 *     simtime_t messageOriginTime;
 *     simtime_t messageTTL = 60;
 *     int hops;
 * 
 *     bool fromSCF = false;
 * 
 * }
 * </pre>
 */
class Data : public ::omnetpp::cPacket
{
  protected:
    double senderDirection;
    double messageDirection;
    Coord messageOriginPosition;
    double messageROI;
    ::omnetpp::simtime_t messageOriginTime;
    ::omnetpp::simtime_t messageTTL;
    int hops;
    bool fromSCF;

  private:
    void copy(const Data& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Data&);

  public:
    Data(const char *name=nullptr, short kind=0);
    Data(const Data& other);
    virtual ~Data();
    Data& operator=(const Data& other);
    virtual Data *dup() const override {return new Data(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual double getSenderDirection() const;
    virtual void setSenderDirection(double senderDirection);
    virtual double getMessageDirection() const;
    virtual void setMessageDirection(double messageDirection);
    virtual Coord& getMessageOriginPosition();
    virtual const Coord& getMessageOriginPosition() const {return const_cast<Data*>(this)->getMessageOriginPosition();}
    virtual void setMessageOriginPosition(const Coord& messageOriginPosition);
    virtual double getMessageROI() const;
    virtual void setMessageROI(double messageROI);
    virtual ::omnetpp::simtime_t getMessageOriginTime() const;
    virtual void setMessageOriginTime(::omnetpp::simtime_t messageOriginTime);
    virtual ::omnetpp::simtime_t getMessageTTL() const;
    virtual void setMessageTTL(::omnetpp::simtime_t messageTTL);
    virtual int getHops() const;
    virtual void setHops(int hops);
    virtual bool getFromSCF() const;
    virtual void setFromSCF(bool fromSCF);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Data& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Data& obj) {obj.parsimUnpack(b);}


#endif // ifndef __DATAMSG_M_H

