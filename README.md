# gimbal_autoprop_sample
A small sample program showing a concept of how libGimbal GBL_PROPERTIES can be used to auto-generate getters/setters.

## About Gimbal Properties
In libGimbal, properties can be registered and then queried later down the line. Registering properties on a type
in libGimbal will generate a "property ID enumeration", it is then up to the type's developer to manually override
the `GblObject::property` method and handle each property case manually.

This allows the greatest flexibility for cases where properties are exposed and don't have a direct field
on their corresponding `GblInstance`. However, for the vast majority of cases, this ends up becoming boilerplate.

The purpose of this example is to show how we could, potentially, expand the `GBL_PROPERTIES` macro to also generate
these getters/setters. 

### Corner cases / Things to Know
* Requires an extra preprocessor directive in the translation unit + extra header include
    * This is to indicate we want to generate getters/setters, then the extra include actually contains the 
      expanded `GBL_PROPERTIES` macro.
* Requires careful header inclusion - Otherwise, all types in headers INCLUDED by your type will also have getters/setters generated.
* It's all or nothing - All properties listed in the `GBL_PROPERTIES` will have getters/setters generated.
    * Properties that do not have READ flag will still have a case generated, but will be blocked by an early return clause.

## Generated Getters
The generated getter, for the `SampleObject` given, once expanded, should be as follows:

```c
static GBL_RESULT SampleObject_GblObject_property_(const GblObject *pObject,
                                                   const GblProperty *pProp,
                                                   GblVariant *pValue) {
  SampleObject *pObj = ((SampleObject *)GblInstance_cast((GblInstance *)pObject,
                                                         SampleObject_type()));
  if ((pProp->flags & GBL_PROPERTY_FLAG_READ) == 0) {
    return GBL_RESULT_ERROR_INVALID_KEY;
  }
  switch (pProp->id) {
  case SampleObject_Property_Id_pStringValue: {
    GblVariant_setValueCopy(pValue, ((GblType_fromBuiltinIndex(17))),
                            pObj->pStringValue);
    break;
  }
  case SampleObject_Property_Id_CharValue: {
    GblVariant_setValueCopy(pValue, ((GblType_fromBuiltinIndex(7))),
                            pObj->CharValue);
    break;
  }
  case SampleObject_Property_Id_BoolValue: {
    GblVariant_setValueCopy(pValue, ((GblType_fromBuiltinIndex(6))),
                            pObj->BoolValue);
    break;
  }
  case SampleObject_Property_Id_Int16Value: {
    GblVariant_setValueCopy(pValue, ((GblType_fromBuiltinIndex(9))),
                            pObj->Int16Value);
    break;
  }
  case SampleObject_Property_Id_Int32Value: {
    GblVariant_setValueCopy(pValue, ((GblType_fromBuiltinIndex(11))),
                            pObj->Int32Value);
    break;
  }
  case SampleObject_Property_Id_Int64Value: {
    GblVariant_setValueCopy(pValue, ((GblType_fromBuiltinIndex(13))),
                            pObj->Int64Value);
    break;
  }
  case SampleObject_Property_Id_UInt8Value: {
    GblVariant_setValueCopy(pValue, ((GblType_fromBuiltinIndex(8))),
                            pObj->UInt8Value);
    break;
  }
  case SampleObject_Property_Id_UInt16Value: {
    GblVariant_setValueCopy(pValue, ((GblType_fromBuiltinIndex(10))),
                            pObj->UInt16Value);
    break;
  }
  case SampleObject_Property_Id_UInt32Value: {
    GblVariant_setValueCopy(pValue, ((GblType_fromBuiltinIndex(12))),
                            pObj->UInt32Value);
    break;
  }
  case SampleObject_Property_Id_UInt64Value: {
    GblVariant_setValueCopy(pValue, ((GblType_fromBuiltinIndex(14))),
                            pObj->UInt64Value);
    break;
  }
  case SampleObject_Property_Id_pPointerValue: {
    GblVariant_setValueCopy(pValue, ((GblType_fromBuiltinIndex(18))),
                            pObj->pPointerValue);
    break;
  }
  case SampleObject_Property_Id_pObjectPointerValue: {
    GblVariant_setValueCopy(pValue, (GblObject_type()),
                            pObj->pObjectPointerValue);
    break;
  }
  default:
    return GBL_RESULT_ERROR_INVALID_PROPERTY;
  }
  return GBL_RESULT_SUCCESS;
};
```