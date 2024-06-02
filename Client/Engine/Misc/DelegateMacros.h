#pragma once
#include "Delegate.h"

#define FUNC_DECLARE_DELEGATE(DelegateName, ReturnType, ...) \
    typedef Delegate<ReturnType(__VA_ARGS__)> DelegateName;

#define DECLARE_DELEGATE(DelegateName) FUNC_DECLARE_DELEGATE(DelegateName, void)
#define DECLARE_DELEGATE_RetVal(DelegateName, ReturnType) FUNC_DECLARE_DELEGATE(DelegateName, ReturnType)

#define DECLARE_DELEGATE_OneParam(DelegateName, Param1Type) FUNC_DECLARE_DELEGATE(DelegateName, void, Param1Type)
#define DECLARE_DELEGATE_RetVal_OneParam(DelegateName, ReturnType, Param1Type) FUNC_DECLARE_DELEGATE(DelegateName, ReturnType, Param1Type)

#define DECLARE_DELEGATE_TwoParams(DelegateName, Param1Type, Param2Type) FUNC_DECLARE_DELEGATE(DelegateName, void, Param1Type, Param2Type)
#define DECLARE_DELEGATE_RetVal_TwoParams(DelegateName, ReturnType, Param1Type, Param2Type) FUNC_DECLARE_DELEGATE(DelegateName, ReturnType, Param1Type, Param2Type)

#define DECLARE_DELEGATE_ThreeParams(DelegateName, Param1Type, Param2Type, Param3Type) FUNC_DECLARE_DELEGATE(DelegateName, void, Param1Type, Param2Type, Param3Type)
#define DECLARE_DELEGATE_RetVal_ThreeParams(DelegateName, ReturnType, Param1Type, Param2Type, Param3Type) FUNC_DECLARE_DELEGATE(DelegateName, ReturnType, Param1Type, Param2Type, Param3Type)

#define DECLARE_DELEGATE_FourParams(DelegateName, Param1Type, Param2Type, Param3Type, Param4Type) FUNC_DECLARE_DELEGATE(DelegateName, void, Param1Type, Param2Type, Param3Type, Param4Type)
#define DECLARE_DELEGATE_RetVal_FourParams(DelegateName, ReturnType, Param1Type, Param2Type, Param3Type, Param4Type) FUNC_DECLARE_DELEGATE(DelegateName, ReturnType, Param1Type, Param2Type, Param3Type, Param4Type)

#define DECLARE_DELEGATE_FiveParams(DelegateName, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type) FUNC_DECLARE_DELEGATE(DelegateName, void, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type)
#define DECLARE_DELEGATE_RetVal_FiveParams(DelegateName, ReturnType, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type) FUNC_DECLARE_DELEGATE(DelegateName, ReturnType, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type)

#define DECLARE_DELEGATE_SixParams(DelegateName, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type) FUNC_DECLARE_DELEGATE(DelegateName, void, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type)
#define DECLARE_DELEGATE_RetVal_SixParams(DelegateName, ReturnType, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type) FUNC_DECLARE_DELEGATE(DelegateName, ReturnType, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type)

#define DECLARE_DELEGATE_SevenParams(DelegateName, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type, Param7Type) FUNC_DECLARE_DELEGATE(DelegateName, void, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type, Param7Type)
#define DECLARE_DELEGATE_RetVal_SevenParams(DelegateName, ReturnType, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type, Param7Type) FUNC_DECLARE_DELEGATE(DelegateName, ReturnType, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type, Param7Type)

#define DECLARE_DELEGATE_EightParams(DelegateName, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type, Param7Type, Param8Type) FUNC_DECLARE_DELEGATE(DelegateName, void, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type, Param7Type, Param8Type)
#define DECLARE_DELEGATE_RetVal_EightParams(DelegateName, ReturnType, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type, Param7Type, Param8Type) FUNC_DECLARE_DELEGATE(DelegateName, ReturnType, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type, Param7Type, Param8Type)

#define DECLARE_DELEGATE_NineParams(DelegateName, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type, Param7Type, Param8Type, Param9Type) FUNC_DECLARE_DELEGATE(DelegateName, void, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type, Param7Type, Param8Type, Param9Type)
#define DECLARE_DELEGATE_RetVal_NineParams(DelegateName, ReturnType, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type, Param7Type, Param8Type, Param9Type) FUNC_DECLARE_DELEGATE(DelegateName, ReturnType, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type, Param7Type, Param8Type, Param9Type)
