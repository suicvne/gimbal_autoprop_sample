#include "sample_object.h"

int main(int argc, const char** pArgv)
{
    GBL_CTX_BEGIN(NULL);

    // Construct instance of our sample object,
    // print values, then destruct
    SampleObject Obj = SampleObject_Create();
    GBL_VCALL(SampleObject, PrintValues, &Obj);
    GBL_VCALL(SampleObject, PrintValuesFromProps, &Obj);
    SampleObject_DestroySelf(&Obj);

    GBL_CTX_END();
}