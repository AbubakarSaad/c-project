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

DataMsg::DataMsg(const char *name, short kind) : ::veins::BaseFrame1609_4(name,kind)
{
    this->senderDirection = 0;
    this->senderAddress = -1;
    this->serial = 0;
    this->hop = 0;
}

DataMsg::DataMsg(const DataMsg& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

DataMsg::~DataMsg()
{
}

DataMsg& DataMsg::operator=(const DataMsg& other)
{
    if (this==&other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void DataMsg::copy(const DataMsg& other)
{
    this->messageOriginPosition = other.messageOriginPosition;
    this->senderDirection = other.senderDirection;
    this->nodesIds = other.nodesIds;
    this->senderAddress = other.senderAddress;
    this->serial = other.serial;
    this->hop = other.hop;
}

void DataMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->messageOriginPosition);
    doParsimPacking(b,this->senderDirection);
    doParsimPacking(b,this->nodesIds);
    doParsimPacking(b,this->senderAddress);
    doParsimPacking(b,this->serial);
    doParsimPacking(b,this->hop);
}

void DataMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->messageOriginPosition);
    doParsimUnpacking(b,this->senderDirection);
    doParsimUnpacking(b,this->nodesIds);
    doParsimUnpacking(b,this->senderAddress);
    doParsimUnpacking(b,this->serial);
    doParsimUnpacking(b,this->hop);
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

LAddress::L2Type& DataMsg::getSenderAddress()
{
    return this->senderAddress;
}

void DataMsg::setSenderAddress(const LAddress::L2Type& senderAddress)
{
    this->senderAddress = senderAddress;
}

int DataMsg::getSerial() const
{
    return this->serial;
}

void DataMsg::setSerial(int serial)
{
    this->serial = serial;
}

int DataMsg::getHop() const
{
    return this->hop;
}

void DataMsg::setHop(int hop)
{
    this->hop = hop;
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

DataMsgDescriptor::DataMsgDescriptor() : omnetpp::cClassDescriptor("veins::DataMsg", "veins::BaseFrame1609_4")
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
    return basedesc ? 6+basedesc->getFieldCount() : 6;
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
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
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
        "senderAddress",
        "serial",
        "hop",
    };
    return (field>=0 && field<6) ? fieldNames[field] : nullptr;
}

int DataMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageOriginPosition")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderDirection")==0) return base+1;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodesIds")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderAddress")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "serial")==0) return base+4;
    if (fieldName[0]=='h' && strcmp(fieldName, "hop")==0) return base+5;
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
        "LAddress::L2Type",
        "int",
        "int",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : nullptr;
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
        case 3: {std::stringstream out; out << pp->getSenderAddress(); return out.str();}
        case 4: return long2string(pp->getSerial());
        case 5: return long2string(pp->getHop());
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
        case 4: pp->setSerial(string2long(value)); return true;
        case 5: pp->setHop(string2long(value)); return true;
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
        case 3: return omnetpp::opp_typename(typeid(LAddress::L2Type));
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
        case 3: return (void *)(&pp->getSenderAddress()); break;
        default: return nullptr;
    }
}

} // namespace veins

