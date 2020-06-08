//
// Generated file, do not edit! Created by nedtool 5.3 from src/messages/BeaconMsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "BeaconMsg_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace veins {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(BeaconMsg)

BeaconMsg::BeaconMsg(const char *name, short kind) : ::veins::WaveShortMessage(name,kind)
{
    this->senderDirection = 0;
    this->hop = 0;
    this->RsuID = 0;
    this->DesID = 0;
    this->SrcID = 0;
    this->AckMsg = false;
    this->IsFlooding = true;
}

BeaconMsg::BeaconMsg(const BeaconMsg& other) : ::veins::WaveShortMessage(other)
{
    copy(other);
}

BeaconMsg::~BeaconMsg()
{
}

BeaconMsg& BeaconMsg::operator=(const BeaconMsg& other)
{
    if (this==&other) return *this;
    ::veins::WaveShortMessage::operator=(other);
    copy(other);
    return *this;
}

void BeaconMsg::copy(const BeaconMsg& other)
{
    this->messageOriginPosition = other.messageOriginPosition;
    this->senderDirection = other.senderDirection;
    this->Path = other.Path;
    this->hop = other.hop;
    this->RsuID = other.RsuID;
    this->DesID = other.DesID;
    this->SrcID = other.SrcID;
    this->AckMsg = other.AckMsg;
    this->IsFlooding = other.IsFlooding;
}

void BeaconMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::WaveShortMessage::parsimPack(b);
    doParsimPacking(b,this->messageOriginPosition);
    doParsimPacking(b,this->senderDirection);
    doParsimPacking(b,this->Path);
    doParsimPacking(b,this->hop);
    doParsimPacking(b,this->RsuID);
    doParsimPacking(b,this->DesID);
    doParsimPacking(b,this->SrcID);
    doParsimPacking(b,this->AckMsg);
    doParsimPacking(b,this->IsFlooding);
}

void BeaconMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::WaveShortMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->messageOriginPosition);
    doParsimUnpacking(b,this->senderDirection);
    doParsimUnpacking(b,this->Path);
    doParsimUnpacking(b,this->hop);
    doParsimUnpacking(b,this->RsuID);
    doParsimUnpacking(b,this->DesID);
    doParsimUnpacking(b,this->SrcID);
    doParsimUnpacking(b,this->AckMsg);
    doParsimUnpacking(b,this->IsFlooding);
}

Coord& BeaconMsg::getMessageOriginPosition()
{
    return this->messageOriginPosition;
}

void BeaconMsg::setMessageOriginPosition(const Coord& messageOriginPosition)
{
    this->messageOriginPosition = messageOriginPosition;
}

double BeaconMsg::getSenderDirection() const
{
    return this->senderDirection;
}

void BeaconMsg::setSenderDirection(double senderDirection)
{
    this->senderDirection = senderDirection;
}

const char * BeaconMsg::getPath() const
{
    return this->Path.c_str();
}

void BeaconMsg::setPath(const char * Path)
{
    this->Path = Path;
}

int BeaconMsg::getHop() const
{
    return this->hop;
}

void BeaconMsg::setHop(int hop)
{
    this->hop = hop;
}

int BeaconMsg::getRsuID() const
{
    return this->RsuID;
}

void BeaconMsg::setRsuID(int RsuID)
{
    this->RsuID = RsuID;
}

int BeaconMsg::getDesID() const
{
    return this->DesID;
}

void BeaconMsg::setDesID(int DesID)
{
    this->DesID = DesID;
}

int BeaconMsg::getSrcID() const
{
    return this->SrcID;
}

void BeaconMsg::setSrcID(int SrcID)
{
    this->SrcID = SrcID;
}

bool BeaconMsg::getAckMsg() const
{
    return this->AckMsg;
}

void BeaconMsg::setAckMsg(bool AckMsg)
{
    this->AckMsg = AckMsg;
}

bool BeaconMsg::getIsFlooding() const
{
    return this->IsFlooding;
}

void BeaconMsg::setIsFlooding(bool IsFlooding)
{
    this->IsFlooding = IsFlooding;
}

class BeaconMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    BeaconMsgDescriptor();
    virtual ~BeaconMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(BeaconMsgDescriptor)

BeaconMsgDescriptor::BeaconMsgDescriptor() : omnetpp::cClassDescriptor("veins::BeaconMsg", "veins::WaveShortMessage")
{
    propertynames = nullptr;
}

BeaconMsgDescriptor::~BeaconMsgDescriptor()
{
    delete[] propertynames;
}

bool BeaconMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BeaconMsg *>(obj)!=nullptr;
}

const char **BeaconMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *BeaconMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int BeaconMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 9+basedesc->getFieldCount() : 9;
}

unsigned int BeaconMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<9) ? fieldTypeFlags[field] : 0;
}

const char *BeaconMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "messageOriginPosition",
        "senderDirection",
        "Path",
        "hop",
        "RsuID",
        "DesID",
        "SrcID",
        "AckMsg",
        "IsFlooding",
    };
    return (field>=0 && field<9) ? fieldNames[field] : nullptr;
}

int BeaconMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageOriginPosition")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderDirection")==0) return base+1;
    if (fieldName[0]=='P' && strcmp(fieldName, "Path")==0) return base+2;
    if (fieldName[0]=='h' && strcmp(fieldName, "hop")==0) return base+3;
    if (fieldName[0]=='R' && strcmp(fieldName, "RsuID")==0) return base+4;
    if (fieldName[0]=='D' && strcmp(fieldName, "DesID")==0) return base+5;
    if (fieldName[0]=='S' && strcmp(fieldName, "SrcID")==0) return base+6;
    if (fieldName[0]=='A' && strcmp(fieldName, "AckMsg")==0) return base+7;
    if (fieldName[0]=='I' && strcmp(fieldName, "IsFlooding")==0) return base+8;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *BeaconMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "Coord",
        "double",
        "string",
        "int",
        "int",
        "int",
        "int",
        "bool",
        "bool",
    };
    return (field>=0 && field<9) ? fieldTypeStrings[field] : nullptr;
}

const char **BeaconMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *BeaconMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int BeaconMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    BeaconMsg *pp = (BeaconMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *BeaconMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BeaconMsg *pp = (BeaconMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BeaconMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BeaconMsg *pp = (BeaconMsg *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getMessageOriginPosition(); return out.str();}
        case 1: return double2string(pp->getSenderDirection());
        case 2: return oppstring2string(pp->getPath());
        case 3: return long2string(pp->getHop());
        case 4: return long2string(pp->getRsuID());
        case 5: return long2string(pp->getDesID());
        case 6: return long2string(pp->getSrcID());
        case 7: return bool2string(pp->getAckMsg());
        case 8: return bool2string(pp->getIsFlooding());
        default: return "";
    }
}

bool BeaconMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    BeaconMsg *pp = (BeaconMsg *)object; (void)pp;
    switch (field) {
        case 1: pp->setSenderDirection(string2double(value)); return true;
        case 2: pp->setPath((value)); return true;
        case 3: pp->setHop(string2long(value)); return true;
        case 4: pp->setRsuID(string2long(value)); return true;
        case 5: pp->setDesID(string2long(value)); return true;
        case 6: pp->setSrcID(string2long(value)); return true;
        case 7: pp->setAckMsg(string2bool(value)); return true;
        case 8: pp->setIsFlooding(string2bool(value)); return true;
        default: return false;
    }
}

const char *BeaconMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(Coord));
        default: return nullptr;
    };
}

void *BeaconMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    BeaconMsg *pp = (BeaconMsg *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getMessageOriginPosition()); break;
        default: return nullptr;
    }
}

} // namespace veins

