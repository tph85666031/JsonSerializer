#ifndef __JSON_SERIALIZER_H__
#define __JSON_SERIALIZER_H__

#include <string.h>
#include "CJsonObject.h"

std::string& com_string_trim_left(std::string& str, const char* t = " \t\n\r\f\v")
{
    if(t == NULL)
    {
        t = " \t\n\r\f\v";
    }
    str.erase(0, str.find_first_not_of(t));
    return str;
}

std::string& com_string_trim_right(std::string& str, const char* t = " \t\n\r\f\v")
{
    if(t == NULL)
    {
        t = " \t\n\r\f\v";
    }
    str.erase(str.find_last_not_of(t) + 1);
    return str;
}

std::string& com_string_trim(std::string& str, const char* t = " \t\n\r\f\v")
{
    return com_string_trim_left(com_string_trim_right(str, t), t);
}

std::vector<std::string> com_string_split(const char* str, const char* delim)
{
    std::vector<std::string> vals;
    if(str != NULL && delim != NULL)
    {
        std::string orgin = str;
        int delim_len = strlen(delim);
        std::string::size_type pos = 0;
        std::string::size_type pos_pre = 0;
        while(true)
        {
            pos = orgin.find_first_of(delim, pos_pre);
            if(pos == std::string::npos)
            {
                vals.push_back(orgin.substr(pos_pre));
                break;
            }
            vals.push_back(orgin.substr(pos_pre, pos - pos_pre));
            pos_pre = pos + delim_len;
        }
    }
    return vals;
}

template<typename T, size_t N>
struct __struct_tuple_serializer_json
{
    static void serializer(CJsonObject& j, const T& t, std::vector<std::string>& n)
    {
        __struct_tuple_serializer_json < T, N - 1 >::serializer(j, t, n);
        auto& val = std::get < N - 1 > (t);
        std::string name = n[N - 1];
        com_string_trim(name);
        j.Add(name, val);
    }
    static void deserializer(CJsonObject& j, T& t, std::vector<std::string>& n)
    {
        __struct_tuple_serializer_json < T, N - 1 >::deserializer(j, t, n);
        auto& val = std::get < N - 1 > (t);
        std::string name = n[N - 1];
        com_string_trim(name);
        j.Get(name, val);
    }
};

template<typename T>
struct __struct_tuple_serializer_json<T, 1>
{
    static void serializer(CJsonObject& j, const T& t, std::vector<std::string>& n)
    {
        auto& val = std::get<0>(t);
        std::string name = n[0];
        com_string_trim(name);
        j.Add(name, val);
    }
    static void deserializer(CJsonObject& j, T& t, std::vector<std::string>& n)
    {
        auto& val = std::get<0>(t);
        std::string name = n[0];
        com_string_trim(name);
        j.Get(name, val);
    }
};

template<typename... Args>
void __tuple_serializer_json_encode(CJsonObject& j, const std::tuple<Args...>& t, std::vector<std::string>& n)
{
    __struct_tuple_serializer_json<decltype(t), sizeof...(Args)>::serializer(j, t, n);
}

template<typename... Args>
void __tuple_serializer_json_decode(CJsonObject& j, std::tuple<Args...>& t, std::vector<std::string>& n)
{
    __struct_tuple_serializer_json<decltype(t), sizeof...(Args)>::deserializer(j, t, n);
}

#define META_J(...) \
std::string toJson(bool pretty=false) const{\
    auto __t = std::forward_as_tuple(__VA_ARGS__);\
    std::vector<std::string> __n = com_string_split(#__VA_ARGS__, ",");\
    CJsonObject __j;\
    __tuple_serializer_json_encode(__j,__t,__n);\
    return pretty?__j.ToFormattedString():__j.ToString();\
}\
void fromJson(const char* json){\
    auto __t = std::forward_as_tuple(__VA_ARGS__);\
    std::vector<std::string> __n = com_string_split(#__VA_ARGS__, ",");\
    CJsonObject __j(json);\
    __tuple_serializer_json_decode(__j,__t,__n);\
}

#endif /* __JSON_SERIALIZER_H__ */

