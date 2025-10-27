// HACK: Have to include this first so only SampleObject's header is actually
//       "processed".
#include "gimbal/gimbal_core.h"
#include <inttypes.h> // for PRId64 PRIx64

// Pre-amble for auto prop getters/setters
#define GBL_AUTOPROP_GEN_GETTER 1
#include "gimbal_autoprop.h"

// Standard object definition.
// When this header is included, the definition of the GBL_PROPERTIES macro is now changed.
// Invocation of that macro will now also, in this case, auto-generate a getter.
#include "sample_object.h"

#define GBL_SELF_TYPE SampleObject

// Forward declaring instance function(s)
static GBL_RESULT SampleObject_PrintValues(GBL_SELF);
static GBL_RESULT SampleObject_PrintValuesFromProps(GBL_SELF);

// ============================================= Class/type init =============================================

static GBL_RESULT SampleObjectClass_init_(GblClass* pClass, const void* pUserData)
{
    // Register props if needed.
    if(!GblType_classRefCount(SAMPLE_OBJECT_TYPE)) {
        GBL_PROPERTIES_REGISTER(SampleObject);
    }

    // Initialize class with our VTable functions.
    SampleObjectClass* pSelfClass = (SampleObjectClass*)pClass;
    pSelfClass->PrintValues = SampleObject_PrintValues;
    pSelfClass->PrintValuesFromProps = SampleObject_PrintValuesFromProps;

    // Assign property getter/setter as needed.
    GBL_OBJECT_CLASS(pSelfClass)->pFnProperty = SampleObject_GblObject_property_;

    // If you want to generate setters:
    // GBL_OBJECT_CLASS(pSelfClass)->pFnSetProperty = SampleObject_GblObject_setProperty_;

    return GBL_RESULT_SUCCESS;
}

GblType SampleObject_type()
{
    static GblType TSampleObjectType = GBL_INVALID_TYPE;
    static GblTypeInfo TISampleObject = {
        .pFnClassInit = SampleObjectClass_init_,
        .classSize = sizeof(SampleObjectClass),
        .instanceSize = sizeof(SampleObject)
    };

    // register, if needed.
    if(TSampleObjectType == GBL_INVALID_TYPE) GBL_UNLIKELY {
        TSampleObjectType = GblType_register("SampleObject", 
            GBL_OBJECT_TYPE, 
            &TISampleObject, 
            GBL_TYPE_FLAG_TYPEINFO_STATIC
        );
    }

    return TSampleObjectType;
}

// ============================================= Class/type init =============================================


// ============================================= Instance Impls =============================================

extern inline SampleObject SampleObject_Create()
{
    SampleObject NewInst = { 0 };
    GblInstance_construct((GblInstance*)&NewInst, SAMPLE_OBJECT_TYPE);

    NewInst.pStringValue = "Hello world!!!";
    NewInst.CharValue = 'T';
    NewInst.Int16Value = -32767;
    NewInst.Int32Value = -42049850;
    NewInst.Int64Value = INT64_MIN;
    NewInst.UInt8Value = 255;
    NewInst.UInt16Value = 65535;
    NewInst.UInt32Value = 430529293;
    NewInst.UInt64Value = UINT64_MAX;

    return NewInst;
}

void SampleObject_DestroySelf(GBL_SELF)
{
    GblInstance_destruct((GblInstance*)pSelf);
}

static GBL_RESULT SampleObject_PrintValues(GBL_SELF)
{
    GBL_CTX_INFO("SampleObject::PrintValues called");

    GBL_LOG_PUSH();
        GBL_CTX_INFO(" pStringValue = %s", pSelf->pStringValue);
        GBL_CTX_INFO(" CharValue = %c", pSelf->CharValue);
        GBL_CTX_INFO(" BoolValue = %d", pSelf->BoolValue);
        GBL_CTX_INFO(" Int16Value = %d", pSelf->Int16Value);
        GBL_CTX_INFO(" Int32Value = %d", pSelf->Int32Value);
        GBL_CTX_INFO(" Int64Value = %" PRId64, pSelf->Int64Value);
        GBL_CTX_INFO(" UInt8Value = %u", pSelf->UInt8Value);
        GBL_CTX_INFO(" UInt16Value = %u", pSelf->UInt16Value);
        GBL_CTX_INFO(" UInt32Value = %u", pSelf->UInt32Value);
        GBL_CTX_INFO(" UInt64Value = %llu", pSelf->UInt64Value);
        GBL_CTX_INFO(" pPointerValue = %p", pSelf->pPointerValue);
        GBL_CTX_INFO(" pObjectPointerValue = %p", pSelf->pObjectPointerValue);
    GBL_LOG_POP(1);

    GBL_CTX_INFO("SampleObject::PrintValues complete");
    
    return GBL_RESULT_SUCCESS;
}

static GBL_RESULT SampleObject_PrintValuesFromProps(GBL_SELF)
{
    GBL_CTX_INFO("SampleObject::PrintValuesFromProps called");

    #define PRINT_PROP(PROP_NAME) \
        do {\
            OutVariant = (GblVariant){ 0 };\
            GblObject_propertyVariant((GblObject*)pSelf, #PROP_NAME, &OutVariant);\
            GBL_CTX_INFO(" %s = %s", #PROP_NAME, GblVariant_toString(&OutVariant));\
        } while(0)\

    GblVariant OutVariant = { 0 };
    

    GBL_LOG_PUSH();
        PRINT_PROP(pStringValue);
        PRINT_PROP(CharValue);
        PRINT_PROP(BoolValue);
        PRINT_PROP(Int16Value);
        PRINT_PROP(Int32Value);
        PRINT_PROP(Int64Value);
        PRINT_PROP(UInt8Value);
        PRINT_PROP(UInt16Value);
        PRINT_PROP(UInt32Value);
        PRINT_PROP(UInt64Value);
        PRINT_PROP(pPointerValue);
        PRINT_PROP(pObjectPointerValue);
    GBL_LOG_POP(1);

    GBL_CTX_INFO("SampleObject::PrintValuesFromProps complete");
    
    return GBL_RESULT_SUCCESS;
}

// ============================================= Instance Impls =============================================

#undef GBL_SELF_TYPE