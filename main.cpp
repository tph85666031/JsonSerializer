#include "json_serializer.h"

typedef struct
{
    int x = 0;
    std::string y;
    uint8_t z = 0;
    char cc[128] = {};
    std::vector<std::string> list;
    META_J(x, y, z, cc, list);
    void reset()
    {
        x = rand() % 100;
        y = "this is Y";
        z = rand() % 100;
        strcpy(cc, "this is cc");
        list.push_back("list1");
        list.push_back("list2");
        list.push_back("list3");
    }
} DD;

typedef struct
{
    bool a = false;
    char b = '\0';
    int8_t c = 0;
    uint8_t d = 0;
    int16_t e = 0;
    uint16_t f = 0;
    int32_t g = 0;
    uint32_t h = 0;
    int64_t i = 0;
    uint64_t j = 0;
    char k[12] = {};
    const char* l = NULL;
    const char* m = NULL;
    std::string n;
    std::vector<int> o;
    std::set<int> p;
    std::deque<int> q;
    std::queue<int> r;
    std::list<int> s;
    std::map<std::string, int> t;
    std::unordered_map<std::string, int> u;
    DD x;
    void reset()
    {
        srand(time(NULL));
        a = rand() % 1;
        b = rand() % 127;
        c = rand() % 256;
        d = rand() % 256;
        e = rand();
        f = rand();
        g = rand();
        h = rand();
        i = rand();
        j = rand();
        strcpy(k, "1234567");
        l = "this is L";
        m = "this is M";
        n = "this is N";
        o.push_back(11);
        o.push_back(12);
        o.push_back(13);
        p.insert(21);
        p.insert(22);
        p.insert(23);
        q.push_back(31);
        q.push_back(32);
        q.push_back(33);
        r.push(41);
        r.push(42);
        r.push(43);
        s.push_back(51);
        s.push_back(52);
        s.push_back(53);
        t["m1"] = 61;
        t["m2"] = 62;
        t["m3"] = 63;
        u["m1"] = 71;
        u["m2"] = 72;
        u["m3"] = 73;
        x.reset();
    }
    META_J(a, b, c, d, e, f, g, h, j, k, l, m, n, o, p, q, r, s, t, u, x);
} EE;

typedef struct
{
    EE e1;
    int g = 0;
    META_J(e1, g);
    void reset()
    {
        g = rand();
        e1.reset();
    }
} FF;

int main()
{
    DD d1;
    d1.x = 1;
    d1.y = "yyyy";
    //d1.cc = "ccc";
    strcpy(d1.cc, "cccc");
    d1.z = 8;
    for(int i = 0; i < 5; i++)
    {
        d1.list.push_back(std::to_string(i));
    }
    std::string json = d1.toJson();
    printf("json=%s\n", json.c_str());

    DD d2;
    d2.x = 10;
    d2.z = 2;
    d2.fromJson(json.c_str());

    EE e1;
    e1.reset();
    printf("json_e1=%s\n", e1.toJson().c_str());

    EE e2;
    e2.a = true;
    e2.b = 22;
    e2.fromJson(e1.toJson().c_str());
    printf("json_e2=%s\n", e2.toJson().c_str());

    FF f1;
    f1.reset();
    printf("json_f1=%s\n", f1.toJson().c_str());

    FF f2;
    f2.fromJson(f1.toJson().c_str());
    printf("json_f2=%s\n", f2.toJson().c_str());
    
    return 0;
}