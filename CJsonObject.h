/*******************************************************************************
    Project:  neb
    @file     CJsonObject.hpp
    @brief    Json
    @author   bwarliao
    @date:    2014-7-16
    @note
    Modify history:
 ******************************************************************************/

#ifndef CJSONOBJECT_HPP_
#define CJSONOBJECT_HPP_

#include <stdio.h>
#include <stddef.h>
#if defined(__APPLE__)
#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <type_traits>

#if __cplusplus >= 201101L
#include <unordered_map>
#endif
#ifdef __cplusplus
extern "C" {
#endif
#include "cJSON.h"
#ifdef __cplusplus
}
#endif


class CJsonObject
{
public:     // method of ordinary json object or json array
    CJsonObject();
    CJsonObject(const std::string& strJson);
    CJsonObject(const CJsonObject* pJsonObject);
    CJsonObject(const CJsonObject& oJsonObject);
#if __cplusplus >= 201101L
    CJsonObject(CJsonObject&& oJsonObject);
#endif
    virtual ~CJsonObject();

    CJsonObject& operator=(const CJsonObject& oJsonObject);
#if __cplusplus >= 201101L
    CJsonObject& operator=(CJsonObject&& oJsonObject);
#endif
    bool operator==(const CJsonObject& oJsonObject) const;
    bool Parse(const std::string& strJson);
    void Clear();
    bool IsEmpty() const;
    bool IsArray() const;
    std::string ToString() const;
    std::string ToFormattedString() const;
    const std::string& GetErrMsg() const
    {
        return(m_strErrMsg);
    }

public:     // method of ordinary json object
    bool AddEmptySubObject(const std::string& strKey);
    bool AddEmptySubArray(const std::string& strKey);
    bool GetKey(std::string& strKey) const;
    void ResetTraversing() const;
    CJsonObject& operator[](const std::string& strKey);
    std::string operator()(const std::string& strKey) const;
    bool KeyExist(const std::string& strKey) const;
    bool Get(const std::string& strKey, CJsonObject& oJsonObject) const;
    bool Get(const std::string& strKey, char* charArray) const;
    bool Get(const std::string& strKey, const char* charArray) const;
    bool Get(const std::string& strKey, std::string& strValue) const;
    bool Get(const std::string& strKey, char& iValue) const;
    bool Get(const std::string& strKey, int8_t& iValue) const;
    bool Get(const std::string& strKey, uint8_t& uiValue) const;
    bool Get(const std::string& strKey, int16_t& iValue) const;
    bool Get(const std::string& strKey, uint16_t& uiValue) const;
    bool Get(const std::string& strKey, int32_t& iValue) const;
    bool Get(const std::string& strKey, uint32_t& uiValue) const;
    bool Get(const std::string& strKey, int64_t& llValue) const;
    bool Get(const std::string& strKey, uint64_t& ullValue) const;
    bool Get(const std::string& strKey, bool& bValue) const;
    bool Get(const std::string& strKey, float& fValue) const;
    bool Get(const std::string& strKey, double& dValue) const;
    template<class T>
    bool Get(const std::string& strKey, std::vector<T>& list) const
    {
        CJsonObject json_sub;
        if(Get(strKey, json_sub) == false)
        {
            return false;
        }
        for(int i = 0; i < json_sub.GetArraySize(); i++)
        {
            T val;
            if(json_sub.Get(i, val))
            {
                list.push_back(val);
            }
        }
        return true;
    }
    template<class T>
    bool Get(const std::string& strKey, std::set<T>& list) const
    {
        CJsonObject json_sub;
        if(Get(strKey, json_sub) == false)
        {
            return false;
        }
        for(int i = 0; i < json_sub.GetArraySize(); i++)
        {
            T val;
            if(json_sub.Get(i, val))
            {
                list.insert(val);
            }
        }
        return true;
    }
    template<class T>
    bool Get(const std::string& strKey, std::deque<T>& list) const
    {
        CJsonObject json_sub;
        if(Get(strKey, json_sub) == false)
        {
            return false;
        }
        for(int i = 0; i < json_sub.GetArraySize(); i++)
        {
            T val;
            if(json_sub.Get(i, val))
            {
                list.push_back(val);
            }
        }
        return true;
    }
    template<class T>
    bool Get(const std::string& strKey, std::queue<T>& list) const
    {
        CJsonObject json_sub;
        if(Get(strKey, json_sub) == false)
        {
            return false;
        }
        for(int i = 0; i < json_sub.GetArraySize(); i++)
        {
            T val;
            if(json_sub.Get(i, val))
            {
                list.push(val);
            }
        }
        return true;
    }
    template<class T>
    bool Get(const std::string& strKey, std::list<T>& list) const
    {
        CJsonObject json_sub;
        if(Get(strKey, json_sub) == false)
        {
            return false;
        }
        for(int i = 0; i < json_sub.GetArraySize(); i++)
        {
            T val;
            if(json_sub.Get(i, val))
            {
                list.push_back(val);
            }
        }
        return true;
    }
    template<class T>
    bool Get(const std::string& strKey, std::map<std::string, T>& list) const
    {
        CJsonObject json_sub;
        if(Get(strKey, json_sub) == false)
        {
            return false;
        }
        std::string key;
        json_sub.ResetTraversing();
        while(json_sub.GetKey(key))
        {
            T val;
            if(json_sub.Get(key, val))
            {
                list[key] = val;
            }
        }
        return true;
    }
#if __cplusplus >= 201101L
    template<class T>
    bool Get(const std::string& strKey, std::unordered_map<std::string, T>& list) const
    {
        CJsonObject json_sub;
        if(Get(strKey, json_sub) == false)
        {
            return false;
        }
        std::string key;
        json_sub.ResetTraversing();
        while(json_sub.GetKey(key))
        {
            T val;
            if(json_sub.Get(key, val))
            {
                list[key] = val;
            }
        }
        return true;
    }
#endif
    template<typename T, void (T::*)(const char*) = &T::fromJson>
    bool Get(const std::string& strKey, T& value)
    {
        AddEmptySubObject(strKey);
        CJsonObject json_sub;
        if(Get(strKey, json_sub) == false)
        {
            return false;
        }
        value.fromJson(json_sub.ToString().c_str());
        return true;
    }
    int GetValueType(const std::string& strKey) const;
    bool IsNull(const std::string& strKey) const;
    bool Add(const std::string& strKey, const CJsonObject& oJsonObject);
#if __cplusplus < 201101L
    bool AddWithMove(const std::string& strKey, CJsonObject& oJsonObject);
#else
    bool Add(const std::string& strKey, CJsonObject&& oJsonObject);
#endif
    bool Add(const std::string& strKey, const char* charArray);
    bool Add(const std::string& strKey, const std::string& strValue);
    bool Add(const std::string& strKey, char cValue);
    bool Add(const std::string& strKey, int8_t iValue);
    bool Add(const std::string& strKey, uint8_t uiValue);
    bool Add(const std::string& strKey, int16_t iValue);
    bool Add(const std::string& strKey, uint16_t uiValue);
    bool Add(const std::string& strKey, int32_t iValue);
    bool Add(const std::string& strKey, uint32_t uiValue);
    bool Add(const std::string& strKey, int64_t llValue);
    bool Add(const std::string& strKey, uint64_t ullValue);
    bool Add(const std::string& strKey, const bool bValue);
    bool Add(const std::string& strKey, float fValue);
    bool Add(const std::string& strKey, double dValue);
    template<class T>
    bool Add(const std::string& strKey, const std::vector<T>& list)
    {
        AddEmptySubArray(strKey);
        for(auto it = list.begin(); it != list.end(); it++)
        {
            (*this)[strKey].Add(*it);
        }
        return true;
    }
    template<class T>
    bool Add(const std::string& strKey, const std::set<T>& list)
    {
        AddEmptySubArray(strKey);
        for(auto it = list.begin(); it != list.end(); it++)
        {
            (*this)[strKey].Add(*it);
        }
        return true;
    }
    template<class T>
    bool Add(const std::string& strKey, const std::deque<T>& list)
    {
        AddEmptySubArray(strKey);
        for(auto it = list.begin(); it != list.end(); it++)
        {
            (*this)[strKey].Add(*it);
        }
        return true;
    }
    template<class T>
    bool Add(const std::string& strKey, const std::queue<T>& list)
    {
        std::queue<T> tmp = list;
        AddEmptySubArray(strKey);
        while(tmp.size() > 0)
        {
            (*this)[strKey].Add(tmp.front());
            tmp.pop();
        }
        return true;
    }
    template<class T>
    bool Add(const std::string& strKey, const std::list<T>& list)
    {
        AddEmptySubArray(strKey);
        for(auto it = list.begin(); it != list.end(); it++)
        {
            (*this)[strKey].Add(*it);
        }
        return true;
    }
    template<class T>
    bool Add(const std::string& strKey, const std::map<std::string, T>& list)
    {
        AddEmptySubObject(strKey);
        for(auto it = list.begin(); it != list.end(); it++)
        {
            (*this)[strKey].Add(it->first, it->second);
        }
        return true;
    }
#if __cplusplus >= 201101L
    template<class T>
    bool Add(const std::string& strKey, const std::unordered_map<std::string, T>& list)
    {
        AddEmptySubObject(strKey);
        for(auto it = list.begin(); it != list.end(); it++)
        {
            (*this)[strKey].Add(it->first, it->second);
        }
        return true;
    }
#endif
    template<typename T, std::string(T::*)(bool) const = &T::toJson>
    bool Add(const std::string& strKey, const T& value)
    {
        CJsonObject json_sub(value.toJson());
        return Add(strKey, json_sub);
    }
    bool AddNull(const std::string& strKey);    // add null like this:   "key":null
    bool Delete(const std::string& strKey);
    bool Replace(const std::string& strKey, const CJsonObject& oJsonObject);
#if __cplusplus < 201101L
    bool ReplaceWithMove(const std::string& strKey, CJsonObject& oJsonObject);
#else
    bool Replace(const std::string& strKey, CJsonObject&& oJsonObject);
#endif
    bool Replace(const std::string& strKey, const std::string& strValue);
    bool Replace(const std::string& strKey, int32_t iValue);
    bool Replace(const std::string& strKey, uint32_t uiValue);
    bool Replace(const std::string& strKey, int64_t llValue);
    bool Replace(const std::string& strKey, uint64_t ullValue);
    bool Replace(const std::string& strKey, const bool bValue);
    bool Replace(const std::string& strKey, float fValue);
    bool Replace(const std::string& strKey, double dValue);
    bool ReplaceWithNull(const std::string& strKey);    // replace value with null
#if __cplusplus < 201101L
    bool ReplaceAdd(const std::string& strKey, const CJsonObject& oJsonObject);
    bool ReplaceAdd(const std::string& strKey, const std::string& strValue);
    template <typename T>
    bool ReplaceAdd(const std::string& strKey, T value)
    {
        if(KeyExist(strKey))
        {
            return(Replace(strKey, value));
        }
        return(Add(strKey, value));
    }
#else
    template <typename T>
    bool ReplaceAdd(const std::string& strKey, T&& value)
    {
        if(KeyExist(strKey))
        {
            return(Replace(strKey, std::forward<T>(value)));
        }
        return(Add(strKey, std::forward<T>(value)));
    }
#endif
    template<typename T, std::string (T::*)(bool) const = &T::toJson>
    bool ReplaceAdd(const std::string& strKey, T& value)
    {
        CJsonObject json_sub(value.toJson());
        return ReplaceAdd(strKey, json_sub);
    }

public:     // method of json array
    int GetArraySize() const;
    CJsonObject& operator[](unsigned int uiWhich);
    std::string operator()(unsigned int uiWhich) const;
    bool Get(int iWhich, CJsonObject& oJsonObject) const;
    bool Get(int iWhich, std::string& strValue) const;
    bool Get(int iWhich, int32_t& iValue) const;
    bool Get(int iWhich, uint32_t& uiValue) const;
    bool Get(int iWhich, int64_t& llValue) const;
    bool Get(int iWhich, uint64_t& ullValue) const;
    bool Get(int iWhich, bool& bValue) const;
    bool Get(int iWhich, float& fValue) const;
    bool Get(int iWhich, double& dValue) const;
    template<typename T, void (T::*)(const char*) = &T::fromJson>
    bool Get(int iWhich, T& value) const
    {
        CJsonObject json_sub;
        if(Get(iWhich, json_sub) == false)
        {
            return false;
        }
        value.fromJson(json_sub.ToString().c_str());
        return true;
    }
    int GetValueType(int iWhich) const;
    bool IsNull(int iWhich) const;
    bool Add(const CJsonObject& oJsonObject);
#if __cplusplus < 201101L
    bool AddWithMove(CJsonObject& oJsonObject);
#else
    bool Add(CJsonObject&& oJsonObject);
#endif
    bool Add(const std::string& strValue);
    bool Add(int32_t iValue);
    bool Add(uint32_t uiValue);
    bool Add(int64_t llValue);
    bool Add(uint64_t ullValue);
    bool Add(const bool bValue);
    bool Add(float fValue);
    bool Add(double dValue);
    template<typename T, std::string (T::*)(bool) const = &T::toJson>
    bool Add(const T& value)
    {
        CJsonObject json_sub(value.toJson());
        return Add(json_sub);
    }
    bool AddNull();   // add a null value
    bool AddAsFirst(const CJsonObject& oJsonObject);
#if __cplusplus < 201101L
    bool AddAsFirstWithMove(CJsonObject& oJsonObject);
#else
    bool AddAsFirst(CJsonObject&& oJsonObject);
#endif
    bool AddAsFirst(const std::string& strValue);
    bool AddAsFirst(int32_t iValue);
    bool AddAsFirst(uint32_t uiValue);
    bool AddAsFirst(int64_t llValue);
    bool AddAsFirst(uint64_t ullValue);
    bool AddAsFirst(const bool bValue);
    bool AddAsFirst(float fValue);
    bool AddAsFirst(double dValue);
    template<typename T, std::string (T::*)(bool) const = &T::toJson>
    bool AddAsFirst(const T& value)
    {
        CJsonObject json_sub(value.toJson());
        return AddAsFirst(json_sub);
    }
    bool AddNullAsFirst();     // add a null value
    bool Delete(int iWhich);
    bool Replace(int iWhich, const CJsonObject& oJsonObject);
#if __cplusplus < 201101L
    bool ReplaceWithMove(int iWhich, CJsonObject& oJsonObject);
#else
    bool Replace(int iWhich, CJsonObject&& oJsonObject);
#endif
    bool Replace(int iWhich, const std::string& strValue);
    bool Replace(int iWhich, int32_t iValue);
    bool Replace(int iWhich, uint32_t uiValue);
    bool Replace(int iWhich, int64_t llValue);
    bool Replace(int iWhich, uint64_t ullValue);
    bool Replace(int iWhich, const bool bValue);
    bool Replace(int iWhich, float fValue);
    bool Replace(int iWhich, double dValue);
    bool ReplaceWithNull(int iWhich);      // replace with a null value
    template<typename T, std::string (T::*)(bool) const = &T::toJson>
    bool Replace(int iWhich, T& value)
    {
        CJsonObject json_sub(value.toJson());
        return Replace(iWhich, json_sub);
    }

private:
    CJsonObject(cJSON* pJsonData);

private:
    cJSON* m_pJsonData;
    cJSON* m_pExternJsonDataRef;
    mutable cJSON* m_pKeyTravers;
    const char* mc_pError;
    std::string m_strErrMsg;
#if __cplusplus < 201101L
    std::map<unsigned int, CJsonObject*> m_mapJsonArrayRef;
    std::map<unsigned int, CJsonObject*>::iterator m_array_iter;
    std::map<std::string, CJsonObject*> m_mapJsonObjectRef;
    std::map<std::string, CJsonObject*>::iterator m_object_iter;
#else
    std::unordered_map<unsigned int, CJsonObject*> m_mapJsonArrayRef;
    std::unordered_map<std::string, CJsonObject*>::iterator m_object_iter;
    std::unordered_map<std::string, CJsonObject*> m_mapJsonObjectRef;
    std::unordered_map<unsigned int, CJsonObject*>::iterator m_array_iter;
#endif
};

#endif /* CJSONHELPER_HPP_ */
