#include <iostream>
#include <stddef.h>

using namespace std;

#pragma pack(push, 1)

// only 
//typedef enum { VALUE_1 = 1, VALUE_2, VALUE_3 }__attribute__ ((__packed__)) TheRealEnum;
typedef enum { VALUE_1 = 1, VALUE_2, VALUE_3 } TheRealEnum;


typedef struct
{
    uint16_t v1;
    uint8_t enumValue;
    uint16_t v2;
}__attribute__((packed)) ShortStruct;

typedef struct
{
    uint16_t v1;
    TheRealEnum enumValue;
    uint16_t v2;
}__attribute__((packed)) LongStruct;

class HackedEnum
{
private:
    uint8_t evalue;
public:
    void operator=(const TheRealEnum v) { evalue = v; };
    operator TheRealEnum() { return (TheRealEnum)evalue; };
}__attribute__((packed));

typedef struct
{
    uint16_t v1;
    HackedEnum enumValue;
    uint16_t v2;
}__attribute__((packed)) HackedStruct;

#pragma pop()

int main(int argc, char **argv)
{
    cout << "Sizes: " << endl
         << "TheRealEnum: " << sizeof(TheRealEnum) << endl
         << "ShortStruct: " << sizeof(ShortStruct) << endl
         << "LongStruct: " << sizeof(LongStruct) << endl
         << "HackedStruct: " << sizeof(HackedStruct) << endl;
    
    ShortStruct ss;
    cout << "address of ss: " << &ss <<  " size " << sizeof(ss) <<endl
         << "address of ss.v1: " << (void*)&ss.v1 << endl
         << "address of ss.ev: " << (void*)&ss.enumValue << endl
         << "address of ss.v2: " << (void*)&ss.v2 << endl;
    
    LongStruct ls;
    cout << "address of ls: " << &ls <<  " size " << sizeof(ls) <<endl
         << "address of ls.v1: " << (void*)&ls.v1 << endl
         << "address of ls.ev: " << (void*)&ls.enumValue << endl
         << "address of ls.v2: " << (void*)&ls.v2 << endl;
    
    HackedStruct hs;
    cout << "address of hs: " << &hs <<  " size " << sizeof(hs) <<endl
         << "address of hs.v1: " << (void*)&hs.v1 << endl
         << "address of hs.ev: " << (void*)&hs.enumValue << endl
         << "address of hs.v2: " << (void*)&hs.v2 << endl;
    
    
    uint8_t buffer[512] = {0};
    
    ShortStruct * short_ptr = (ShortStruct*)buffer;
    LongStruct * long_ptr = (LongStruct*)buffer;
    HackedStruct * hacked_ptr = (HackedStruct*)buffer;
    
    short_ptr->v1 = 1;
    short_ptr->enumValue = VALUE_2;
    short_ptr->v2 = 3;
    
    cout << "Values of short: " << endl
            << "v1 = " << short_ptr->v1 << endl
            << "ev = " << (int)short_ptr->enumValue << endl
            << "v2 = " << short_ptr->v2 << endl;
    
    cout << "Values of long: " << endl
            << "v1 = " << long_ptr->v1 << endl
            << "ev = " << long_ptr->enumValue << endl
            << "v2 = " << long_ptr->v2 << endl;
    
    cout << "Values of hacked: " << endl
            << "v1 = " << hacked_ptr->v1 << endl
            << "ev = " << hacked_ptr->enumValue << endl
            << "v2 = " << hacked_ptr->v2 << endl;
    
    
    
    HackedStruct hs1, hs2;
    
    // hs1.enumValue = 1; // error, the value is not the wanted enum
    
    hs1.enumValue = VALUE_1;
    int a = hs1.enumValue;
    TheRealEnum b = hs1.enumValue;
    hs2.enumValue = hs1.enumValue;
    
    return 0;
}  