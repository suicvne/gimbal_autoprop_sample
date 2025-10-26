#ifndef SAMPLE_OBJECT_H
#define SAMPLE_OBJECT_H

#include "gimbal/gimbal_core.h"

GBL_DECLS_BEGIN
GBL_FORWARD_DECLARE_STRUCT(SampleObject);
#define GBL_SELF_TYPE SampleObject
#define SAMPLE_OBJECT_TYPE (GBL_TYPEID(SampleObject))
#define SAMPLE_OBJECT(INST) (GBL_CAST(SampleObject, INST))

// Derive a simple object class.
GBL_CLASS_DERIVE(SampleObject, GblObject)
    GBL_RESULT (*PrintValues)(GBL_SELF);
    GBL_RESULT (*PrintValuesFromProps)(GBL_SELF);
GBL_CLASS_END

// Derive instance 
GBL_INSTANCE_DERIVE(SampleObject, GblObject)
    const char*     pStringValue;
    char            CharValue;
    GblBool         BoolValue;
    /*int8_t          Int8Value;*/
    int16_t         Int16Value;
    int32_t         Int32Value;
    int64_t         Int64Value;
    uint8_t         UInt8Value;
    uint16_t        UInt16Value;
    uint32_t        UInt32Value;
    uint64_t        UInt64Value;
    const void*     pPointerValue;
    GblObject*      pObjectPointerValue;
GBL_INSTANCE_END

// Meta bindings.
GBL_PROPERTIES(SampleObject,
    ( pStringValue, GBL_GENERIC, ( READ ), GBL_STRING_TYPE ),
    ( CharValue, GBL_GENERIC, ( READ ), GBL_CHAR_TYPE ),
    ( BoolValue, GBL_GENERIC, ( READ ), GBL_BOOL_TYPE ),
    ( Int16Value, GBL_GENERIC, ( READ ), GBL_INT16_TYPE ),
    ( Int32Value, GBL_GENERIC, ( READ ), GBL_INT32_TYPE ),
    ( Int64Value, GBL_GENERIC, ( READ ), GBL_INT64_TYPE ),

    ( UInt8Value, GBL_GENERIC, ( READ ), GBL_UINT8_TYPE ),
    ( UInt16Value, GBL_GENERIC, ( READ ), GBL_UINT16_TYPE ),
    ( UInt32Value, GBL_GENERIC, ( READ ), GBL_UINT32_TYPE ),
    ( UInt64Value, GBL_GENERIC, ( READ ), GBL_UINT64_TYPE ),

    ( pPointerValue, GBL_GENERIC, ( READ ), GBL_POINTER_TYPE ),
    ( pObjectPointerValue, GBL_GENERIC, ( READ ), GBL_OBJECT_TYPE )
);

// Ctors and dtors.
extern  SampleObject SampleObject_Create();
        void SampleObject_DestroySelf(GBL_SELF);





#undef GBL_SELF_TYPE
GBL_DECLS_END

#endif // SAMPLE_OBJECT_H