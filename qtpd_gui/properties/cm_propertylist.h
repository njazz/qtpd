#ifndef CM_PROPERTYLIST_H
#define CM_PROPERTYLIST_H

#include "cm_property.h"

#include <map>

#include <QDebug>

namespace qtpd
{

typedef std::map<std::string, Property*> UIPropertyData;
typedef std::map<std::string, UIPropertyData*> UIPropertyGroups;

typedef std::map<std::string, Property*>::iterator UIPropertyDataIterator;

////
/// \brief yet another property handling class for ui object. List
///
class PropertyList
{
private:
    UIPropertyData data_;
    UIPropertyGroups groups_;

public:
    PropertyList(){};

    UIPropertyData* fromGroup(std::string grpName)
    {
        UIPropertyData* ret;
        ret = this->groups_[grpName];
        return ret;
    }

    UIPropertyData* fromGroup(QString grpName)
    {
        UIPropertyData* ret;
        ret = this->groups_[grpName.toStdString()];
        return ret;
    }

    template <typename T>
    void create(std::string pName, std::string pGroup, std::string pVersion, T defaultData)
    {
        Property *newP = new Property;

        //newP->setGroup(pGroup);
        newP->setVersion(pVersion);
        newP->set(defaultData);
        newP->setDefault();

        data_[pName] = newP;
        //fix
        //groups_[pGroup][pName] = newP;

        qDebug() << "new property" << data_[pName]->asQString();

    }

    // todo []

    template <typename U>
    void set(std::string pName, U value)
    {
        this->data_[pName]->set(value);
    };

    Property *get(std::string pName)
    {
        Property *ret = 0;
        std::map<std::string, Property*>::iterator it = data_.find(pName);
        if ( it != data_.end() )
            ret = this->data_[pName];
        return ret;
    };


    //////////

    ////
    /// \brief returns string for saving in file
    /// \return
    ///
    std::string asPdFileString()
    {
        std::string ret;

        UIPropertyDataIterator it;
        for (it = this->data_.begin(); it != this->data_.end(); ++it)
        {
            //save only modified values
            if (it->second->data() != it->second->defaultData())
            {
                ret += "@" + it->first + " ";
                ret += it->second->asStdString()+" ";
            }

        }

        return ret;

    }

};
}

#endif // CM_PROPERTYLIST_H