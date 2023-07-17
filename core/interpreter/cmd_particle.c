#include "cmd_particle.h"
#include "particles_lib.h"

#include "core.h"
#include "value.h"
#include "video_chip.h"

enum ErrorCode cmd_PARTICLE(struct Core *core)
{
    struct Interpreter *interpreter = core->interpreter;
    struct ParticlesLib *lib=&interpreter->particlesLib;

    // PARTICLE
    ++interpreter->pc;

    // PARTICLE <NUM>
    // PARTICLE <APPAREANCE>
    struct TypedValue nValue = itp_evaluateExpression(core, TypeClassNumeric);

    if(interpreter->pc->type==TokenComma)
    {
        // PARTICLE <NUM>
        if(core->interpreter->pass==PassPrepare && nValue.type!=ValueTypeFloat) return ErrorTypeMismatch;
        else if(core->interpreter->pass==PassRun && ((int)nValue.v.floatValue<0 || (int)nValue.v.floatValue>NUM_SPRITES-1)) return ErrorInvalidParameter;

        ++interpreter->pc;

        // PARTICLE <NUM>,<COUNT>
        struct TypedValue cValue=itp_evaluateNumericExpression(core,0,NUM_SPRITES);
        if(cValue.type==ValueTypeError) return cValue.v.errorCode;

        // PARTICLE <NUM>,<COUNT> AT
        if(interpreter->pc->type!=TokenAT) return ErrorSyntax;
        ++interpreter->pc;

        // PARTICLE <NUM>,<COUNT> AT <ADDR>
        struct TypedValue aValue=itp_evaluateExpression(core,TypeClassNumeric);
        if(aValue.type==ValueTypeError) return aValue.v.errorCode;

        // TODO: check if last particle is out of RAM

        // TODO: deal with Pass
        
        prtclib_setupPool(lib,(int)nValue.v.floatValue,(int)cValue.v.floatValue,(int)aValue.v.floatValue);
    }
    else if(interpreter->pc->type==TokenAT)
    {
        // PARTICLE <APPAREANCE>
        if(core->interpreter->pass==PassPrepare && nValue.type!=ValueTypeFloat) return ErrorTypeMismatch;
        else if(core->interpreter->pass==PassRun && ((int)nValue.v.floatValue<0 || (int)nValue.v.floatValue>APPERANCE_MAX-1)) return ErrorInvalidParameter;

        // PARTICLE <APPAREANCE> DATA
        if(interpreter->pc->type!=TokenDATA) return ErrorSyntax;
        ++interpreter->pc;

        // PARTICLE <APPAREANCE> DATA <LABEL>
        if(interpreter->pc->type!=TokenIdentifier) return ErrorExpectedLabel;
        struct Token *tk=interpreter->pc;
        ++interpreter->pc;

        // TODO: deal with Pass

        prtclib_setApperanceLabel(lib,(int)nValue.v.floatValue,interpreter->pc);
    }
    else return ErrorSyntax;

/*

        enum ValueType varType = ValueTypeNull;
        enum ErrorCode errorCode = ErrorNone;
        union Value *varValue = itp_readVariable(core, &varType, &errorCode, true);
        if (!varValue) return errorCode;
            
        if (interpreter->pass == PassRun)
        {
            if (!interpreter->currentDataValueToken) return ErrorOutOfData;
            
            struct Token *dataValueToken = interpreter->currentDataValueToken;
            if (dataValueToken->type == TokenFloat)
            {
                if (varType != ValueTypeFloat) return ErrorTypeMismatch;
                varValue->floatValue = dataValueToken->floatValue;
            }
            else if (dataValueToken->type == TokenMinus)
            {
                if (varType != ValueTypeFloat) return ErrorTypeMismatch;
                interpreter->currentDataValueToken++;
                varValue->floatValue = -interpreter->currentDataValueToken->floatValue;
            }
            else if (dataValueToken->type == TokenString)
            {
                if (varType != ValueTypeString) return ErrorTypeMismatch;
                if (varValue->stringValue)
                {
                    rcstring_release(varValue->stringValue);
                }
                varValue->stringValue = dataValueToken->stringValue;
                rcstring_retain(varValue->stringValue);
            }
            
            dat_nextData(interpreter);
        }
    }
    while (interpreter->pc->type == TokenComma);
    
    return itp_endOfCommand(interpreter);
*/

    return itp_endOfCommand(interpreter);
}
