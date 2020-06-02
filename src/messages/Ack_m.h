//
// Generated file, do not edit! Created by nedtool 5.3 from src/messages/Ack.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __ACK_M_H
#define __ACK_M_H

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
 * Class generated from <tt>src/messages/Ack.msg:27</tt> by nedtool.
 * <pre>
 * packet Ack extends BasicSafetyMessage
 * {
 *     // meta info
 *     string Path;
 *     int hop;
 *     int RsuID;
 *     int DesID;
 *     int SrcID;
 *     bool AckMsg = true;
 *     // message info
 * }
 * </pre>
 */
class Ack : public ::BasicSafetyMessage
{
  protected:
    ::omnetpp::opp_string Path;
    int hop;
    int RsuID;
    int DesID;
    int SrcID;
    bool AckMsg;

  private:
    void copy(const Ack& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ack&);

  public:
    Ack(const char *name=nullptr, short kind=0);
    Ack(const Ack& other);
    virtual ~Ack();
    Ack& operator=(const Ack& other);
    virtual Ack *dup() const override {return new Ack(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const char * getPath() const;
    virtual void setPath(const char * Path);
    virtual int getHop() const;
    virtual void setHop(int hop);
    virtual int getRsuID() const;
    virtual void setRsuID(int RsuID);
    virtual int getDesID() const;
    virtual void setDesID(int DesID);
    virtual int getSrcID() const;
    virtual void setSrcID(int SrcID);
    virtual bool getAckMsg() const;
    virtual void setAckMsg(bool AckMsg);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ack& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ack& obj) {obj.parsimUnpack(b);}


#endif // ifndef __ACK_M_H

