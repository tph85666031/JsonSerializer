**JsonSerializer** 
---
* c++ json serialize tool, base on c\+\+11.
* Add 'META_J' to class defination
* Use obj.toJson() to convert the C++ class to json string.
* Use obj.fromJson(char\* json) to convert a json string to C++ Class.
---
**build:** 
* mkdir build
* cd build
* cmake ../
* make

**run test:**
* cd build
* ./SerializerTest

**example:**
```
class B
{
int a;
std::set<std::string> s;

META_J(a,s); // <----------------add this to support auto serializtion
};

class A
{
int x;
std::string y;
std::vector<int> z;
std::map<std::strng,int> m;
B b;

META_J(x,y,z,m,b); // <----------------add this to support auto serializtion
};

A a1;
std::string json= a1.toJson();

A a2;
a2.fromJson(json.c_str());
```