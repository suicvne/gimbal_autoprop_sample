#include "sample_object.h"

int main(int argc, const char** pArgv)
{
    // Construct instance of our sample object,
    // print values, then destruct
    SampleObject Obj = SampleObject_Create();
    Obj.pClass->PrintValues(&Obj);
    Obj.pClass->PrintValuesFromProps(&Obj);
    SampleObject_DestroySelf(&Obj);
    
    return 0;
}