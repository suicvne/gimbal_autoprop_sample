/**
 * @file gimbal_autoprop.h
 * @author Mike Santiago
 * @brief The goal if this file is to extend the GBL_PROPERTIES, at compile time, to allow generating
 * getters/setters of properties without re-calling the GBL_PROPERTIES macro.
 * 
 * This will be accomplished by re-defining the GBL_PROPERTIES macro at compile IF a certain flag
 * is enabled. If this flag isn't enabled, then GBL_PROPERTIES will function as normal, simply declaring
 * the property ID enumeration.
 *
 * If this is enabled, then we should use the tuple pairs to generate a getter/setter based 
 * on the GblObject_property and GblObject_setProperty functions.
 *
 * @date 2025-10-26
 * 
 */

#ifndef GIMBAL_AUTOPROP_H
#define GIMBAL_AUTOPROP_H

#include "gimbal/meta/properties/gimbal_property.h"

#if GBL_AUTOPROP_GEN_GETTER
    
    #define GBL_AUTOPROP_GENERATE_GETTER(TOBJTYPE, ...) \
        static GBL_RESULT TOBJTYPE##_GblObject_property_(const GblObject* pObject, const GblProperty* pProp, GblVariant* pValue) {\
            TOBJTYPE* pObj = GBL_CAST(TOBJTYPE, pObject);\
            if((pProp->flags & GBL_PROPERTY_FLAG_READ) == 0) { return GBL_RESULT_ERROR_INVALID_KEY; }\
            switch(pProp->id) {\
                GBL_TUPLE_FOREACH(GBL_AUTOPROP_IDGETCASE_, TOBJTYPE, (__VA_ARGS__))\
                default: return GBL_RESULT_ERROR_INVALID_PROPERTY;\
            }\
            return GBL_RESULT_SUCCESS;\
        }\


    // This level of indirection is unfortunately necessary to get the type
    // to resolve.

    /**
     * @brief Expands to a single "getter" case.
     */
    #define GBL_AUTOPROP_IDGETCASE_(TOBJTYPE, PROPTBL) \
        GBL_AUTOPROP_IDGETCASE__(TOBJTYPE, GBL_EVAL PROPTBL)

    #define GBL_AUTOPROP_IDGETCASE__(...) \
        GBL_AUTOPROP_IDGETCASE___(__VA_ARGS__)

    #define GBL_AUTOPROP_IDGETCASE___(TOBJTYPE, PROPNAME, PROPTYPE, PROPFLAGS, PROPGBLTYPE) \
        case TOBJTYPE##_Property_Id_##PROPNAME: {\
            GblVariant_setValueCopy(pValue, PROPGBLTYPE, pObj->PROPNAME);\
            break;\
        }\

#else
    #define GBL_AUTOPROP_GENERATE_GETTER(TOBJTYPE, ...)
#endif

#if GBL_AUTOPROP_GEN_SETTER
    #define GBL_AUTOPROP_GENERATE_SETTER(...) #__VA_ARGS__
#else
    #define GBL_AUTOPROP_GENERATE_SETTER(...)
#endif

#if GBL_AUTOPROP_GEN_SETTER | GBL_AUTOPROP_GEN_GETTER

    // #if !defined(GBL_SELF_TYPE)
    //     #error GBL_SELF_TYPE must be defined before generating autoprop getters/setters.
    // #endif

    // Override GBL_PROPERTIES macro.
    #undef GBL_PROPERTIES

    #define GBL_PROPERTIES(...) \
        GBL_PROPERTIES_(__VA_ARGS__) \
        GBL_AUTOPROP_GENERATE_GETTER(__VA_ARGS__) \
        GBL_AUTOPROP_GENERATE_SETTER(__VA_ARGS__) \

#endif

#endif // GIMBAL_AUTOPROP_H