//
// Generated file, do not edit! Created by nedtool 5.3 from src/messages/DataMsg.msg.
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
#include "DataMsg_m.h"

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

Register_Class(DataMsg)

DataMsg::DataMsg(const char *name, short kind) : ::veins::WaveShortMessage(name,kind)
{
    this->senderDirection = 0;
    this->hop = 0;
    this->souId = 0;
    this->desId = 0;
    this->ack = false;
}

DataMsg::DataMsg(const DataMsg& other) : ::veins::WaveShortMessage(other)
{
    copy(other);
}

DataMsg::~DataMsg()
{
}

DataMsg& DataMsg::operator=(const DataMsg& other)
{
    if (this==&other) return *this;
    ::veins::WaveShortMessage::operator=(other);
    copy(other);
    return *this;
}

void DataMsg::copy(const DataMsg& other)
{
    this->messageOriginPosition = other.messageOriginPosition;
    this->senderDirection = other.senderDirection;
    this->nodesIds = other.nodesIds;
    this->hop = other.hop;
    this->souId = other.souId;
    this->desId = other.desId;
    this->ack = other.ack;
    this->nodeState = other.nodeState;
    this->action = other.action;
    this->transcation = other.transcation;
}

void DataMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::WaveShortMessage::parsimPack(b);
    doParsimPacking(b,this->messageOriginPosition);
    doParsimPacking(b,this->senderDirection);
    doParsimPacking(b,this->nodesIds);
    doParsimPacking(b,this->hop);
    doParsimPacking(b,this->souId);
    doParsimPacking(b,this->desId);
    doParsimPacking(b,this->ack);
    doParsimPacking(b,this->nodeState);
    doParsimPacking(b,this->action);
    doParsimPacking(b,this->transcation);
}

void DataMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::WaveShortMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->messageOriginPosition);
    doParsimUnpacking(b,this->senderDirection);
    doParsimUnpacking(b,this->nodesIds);
    doParsimUnpacking(b,this->hop);
    doParsimUnpacking(b,this->souId);
    doParsimUnpacking(b,this->desId);
    doParsimUnpacking(b,this->ack);
    doParsimUnpacking(b,this->nodeState);
    doParsimUnpacking(b,this->action);
    doParsimUnpacking(b,this->transcation);
}

Coord& DataMsg::getMessageOriginPosition()
{
    return this->messageOriginPosition;
}

void DataMsg::setMessageOriginPosition(const Coord& messageOriginPosition)
{
    this->messageOriginPosition = messageOriginPosition;
}

double DataMsg::getSenderDirection() const
{
    return this->senderDirection;
}

void DataMsg::setSenderDirection(double senderDirection)
{
    this->senderDirection = senderDirection;
}

const char * DataMsg::getNodesIds() const
{
    return this->nodesIds.c_str();
}

void DataMsg::setNodesIds(const char * nodesIds)
{
    this->nodesIds = nodesIds;
}

int DataMsg::getHop() const
{
    return this->hop;
}

void DataMsg::setHop(int hop)
{
    this->hop = hop;
}

int DataMsg::getSouId() const
{
    return this->souId;
}

void DataMsg::setSouId(int souId)
{
    this->souId = souId;
}

int DataMsg::getDesId() const
{
    return this->desId;
}

void DataMsg::setDesId(int desId)
{
    this->desId = desId;
}

bool DataMsg::getAck() const
{
    return this->ack;
}

void DataMsg::setAck(bool ack)
{
    this->ack = ack;
}

const char * DataMsg::getNodeState() const
{
    return this->nodeState.c_str();
}

void DataMsg::setNodeState(const char * nodeState)
{
    this->nodeState = nodeState;
}

const char * DataMsg::getAction() const
{
    return this->action.c_str();
}

void DataMsg::setAction(const char * action)
{
    this->action = action;
}

const char * DataMsg::getTranscation() const
{
    return this->transcation.c_str();
}

void DataMsg::setTranscation(const char * transcation)
{
    this->transcation = transcation;
}

class DataMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    DataMsgDescriptor();
    virtual ~DataMsgDescriptor();

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

Register_ClassDescriptor(DataMsgDescriptor)

DataMsgDescriptor::DataMsgDescriptor() : omnetpp::cClassDescriptor("veins::DataMsg", "veins::WaveShortMessage")
{
    propertynames = nullptr;
}

DataMsgDescriptor::~DataMsgDescriptor()
{
    delete[] propertynames;
}

bool DataMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<DataMsg *>(obj)!=nullptr;
}

const char **DataMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *DataMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int DataMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 10+basedesc->getFieldCount() : 10;
}

unsigned int DataMsgDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISEDITABLE,
    };
    return (field>=0 && field<10) ? fieldTypeFlags[field] : 0;
}

const char *DataMsgDescriptor::getFieldName(int field) const
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
        "nodesIds",
        "hop",
        "souId",
        "desId",
        "ack",
        "nodeState",
        "action",
        "transcation",
    };
    return (field>=0 && field<10) ? fieldNames[field] : nullptr;
}

int DataMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageOriginPosition")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderDirection")==0) return base+1;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodesIds")==0) return base+2;
    if (fieldName[0]=='h' && strcmp(fieldName, "hop")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "souId")==0) return base+4;
    if (fieldName[0]=='d' && strcmp(fieldName, "desId")==0) return base+5;
    if (fieldName[0]=='a' && strcmp(fieldName, "ack")==0) return base+6;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeState")==0) return base+7;
    if (fieldName[0]=='a' && strcmp(fieldName, "action")==0) return base+8;
    if (fieldName[0]=='t' && strcmp(fieldName, "transcation")==0) return base+9;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *DataMsgDescriptor::getFieldTypeString(int field) const
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
        "bool",
        "string",
        "string",
        "string",
    };
    return (field>=0 && field<10) ? fieldTypeStrings[field] : nullptr;
}

const char **DataMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *DataMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int DataMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    DataMsg *pp = (DataMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *DataMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    DataMsg *pp = (DataMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string DataMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    DataMsg *pp = (DataMsg *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getMessageOriginPosition(); return out.str();}
        case 1: return double2string(pp->getSenderDirection());
        case 2: return oppstring2string(pp->getNodesIds());
        case 3: return long2string(pp->getHop());
        case 4: return long2string(pp->getSouId());
        case 5: return long2string(pp->getDesId());
        case 6: return bool2string(pp->getAck());
        case 7: return oppstring2string(pp->getNodeState());
        case 8: return oppstring2string(pp->getAction());
        case 9: return oppstring2string(pp->getTranscation());
        default: return "";
    }
}

bool DataMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    DataMsg *pp = (DataMsg *)object; (void)pp;
    switch (field) {
        case 1: pp->setSenderDirection(string2double(value)); return true;
        case 2: pp->setNodesIds((value)); return true;
        case 3: pp->setHop(string2long(value)); return true;
        case 4: pp->setSouId(string2long(value)); return true;
        case 5: pp->setDesId(string2long(value)); return true;
        case 6: pp->setAck(string2bool(value)); return true;
        case 7: pp->setNodeState((value)); return true;
        case 8: pp->setAction((value)); return true;
        case 9: pp->setTranscation((value)); return true;
        default: return false;
    }
}

const char *DataMsgDescriptor::getFieldStructName(int field) const
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

void *DataMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    DataMsg *pp = (DataMsg *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getMessageOriginPosition()); break;
        default: return nullptr;
    }
}

} // namespace veins

