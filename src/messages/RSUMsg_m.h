//
// Generated file, do not edit! Created by nedtool 5.5 from src/messages/RSUMsg.msg.
//

#ifndef __VEINS_RSUMSG_M_H
#define __VEINS_RSUMSG_M_H

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
#include "veins/modules/messages/BaseFrame1609_4_m.h"
// }}


namespace veins {

/**
 * Class generated from <tt>src/messages/RSUMsg.msg:33</tt> by nedtool.
 * <pre>
 * packet RSUMsg extends BaseFrame1609_4
 * {
 *     int psid = -100;
 *     string msg = "from rsu";
 * }
 * </pre>
 */
class RSUMsg : public ::veins::BaseFrame1609_4
{
  protected:
    int psid;
    ::omnetpp::opp_string msg;

  private:
    void copy(const RSUMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RSUMsg&);

  public:
    RSUMsg(const char *name=nullptr, short kind=0);
    RSUMsg(const RSUMsg& other);
    virtual ~RSUMsg();
    RSUMsg& operator=(const RSUMsg& other);
    virtual RSUMsg *dup() const override {return new RSUMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getPsid() const;
    virtual void setPsid(int psid);
    virtual const char * getMsg() const;
    virtual void setMsg(const char * msg);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RSUMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RSUMsg& obj) {obj.parsimUnpack(b);}

} // namespace veins

#endif // ifndef __VEINS_RSUMSG_M_H

