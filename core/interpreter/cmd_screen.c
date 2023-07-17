//
// Copyright 2017 Timo Kloss
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#include "cmd_screen.h"
#include "core.h"
#include <assert.h>
#include <stdint.h>
#include "interpreter_utils.h"

enum ErrorCode cmd_PALETTE(struct Core *core)
{
    struct Interpreter *interpreter = core->interpreter;
    
    // PALETTE
    ++interpreter->pc;
    
    // n value
    struct TypedValue nValue = itp_evaluateNumericExpression(core, 0, NUM_PALETTES - 1);
    if (nValue.type == ValueTypeError) return nValue.v.errorCode;
    
    // comma
    if (interpreter->pc->type != TokenComma) return ErrorSyntax;
    ++interpreter->pc;
    
    // c0 value
    struct TypedValue c0Value = itp_evaluateOptionalNumericExpression(core, 0, 63);
    if (c0Value.type == ValueTypeError) return c0Value.v.errorCode;

    // comma
    if (interpreter->pc->type != TokenComma) return ErrorSyntax;
    ++interpreter->pc;
    
    // c1 value
    struct TypedValue c1Value = itp_evaluateOptionalNumericExpression(core, 0, 63);
    if (c1Value.type == ValueTypeError) return c1Value.v.errorCode;
    
    // comma
    if (interpreter->pc->type != TokenComma) return ErrorSyntax;
    ++interpreter->pc;
    
    // c2 value
    struct TypedValue c2Value = itp_evaluateOptionalNumericExpression(core, 0, 63);
    if (c2Value.type == ValueTypeError) return c2Value.v.errorCode;
    
    // comma
    if (interpreter->pc->type != TokenComma) return ErrorSyntax;
    ++interpreter->pc;
    
    // c3 value
    struct TypedValue c3Value = itp_evaluateOptionalNumericExpression(core, 0, 63);
    if (c3Value.type == ValueTypeError) return c3Value.v.errorCode;
    
    if (interpreter->pass == PassRun)
    {
        int n = nValue.v.floatValue;
        uint8_t *palColors = &core->machine->colorRegisters.colors[n * 4];
        if (c0Value.type != ValueTypeNull) palColors[0] = c0Value.v.floatValue;
        if (c1Value.type != ValueTypeNull) palColors[1] = c1Value.v.floatValue;
        if (c2Value.type != ValueTypeNull) palColors[2] = c2Value.v.floatValue;
        if (c3Value.type != ValueTypeNull) palColors[3] = c3Value.v.floatValue;
    }
    
    return itp_endOfCommand(interpreter);
}

enum ErrorCode cmd_SCROLL(struct Core *core)
{
    struct Interpreter *interpreter = core->interpreter;
    
    // SCROLL
    ++interpreter->pc;
    
    // bg value
    struct TypedValue bgValue = itp_evaluateNumericExpression(core, 0, 3);
    if (bgValue.type == ValueTypeError) return bgValue.v.errorCode;
    
    // comma
    if (interpreter->pc->type != TokenComma) return ErrorSyntax;
    ++interpreter->pc;
    
    // x value
    struct TypedValue xValue = itp_evaluateExpression(core, TypeClassNumeric);
    if (xValue.type == ValueTypeError) return xValue.v.errorCode;
    
    // comma
    if (interpreter->pc->type != TokenComma) return ErrorSyntax;
    ++interpreter->pc;
    
    // y value
    struct TypedValue yValue = itp_evaluateExpression(core, TypeClassNumeric);
    if (yValue.type == ValueTypeError) return yValue.v.errorCode;

    if (interpreter->pass == PassRun)
    {
        struct VideoRegisters *reg = &core->machine->videoRegisters;
        int bg = bgValue.v.floatValue;
        int x = (int)xValue.v.floatValue;
        int y = (int)yValue.v.floatValue;
        if (bg == 0)
        {
            reg->scrollAX = x & 0xFF;
            reg->scrollAY = y & 0xFF;
            reg->scrollMSB.aX = (x >> 8) & 1;
            reg->scrollMSB.aY = (y >> 8) & 1;
        }
        else if(bg == 1)
        {
            reg->scrollBX = x & 0xFF;
            reg->scrollBY = y & 0xFF;
            reg->scrollMSB.bX = (x >> 8) & 1;
            reg->scrollMSB.bY = (y >> 8) & 1;
        }
        else if(bg == 2)
        {
            reg->scrollCX = x & 0xFF;
            reg->scrollCY = y & 0xFF;
            reg->scrollMSB.cX = (x >> 8) & 1;
            reg->scrollMSB.cY = (y >> 8) & 1;
        }
        else if(bg == 3)
        {
            reg->scrollDX = x & 0xFF;
            reg->scrollDY = y & 0xFF;
            reg->scrollMSB.cX = (x >> 8) & 1;
            reg->scrollMSB.cY = (y >> 8) & 1;
        }
    }
    
    return itp_endOfCommand(interpreter);
}

// enum ErrorCode cmd_DISPLAY(struct Core *core)
// {
//     struct Interpreter *interpreter = core->interpreter;
    
//     // DISPLAY
//     ++interpreter->pc;
    
//     // obsolete syntax!
    
//     // atrb value
//     struct TypedValue aValue = itp_evaluateDisplayAttributes(core, core->machine->videoRegisters.attr);
//     if (aValue.type == ValueTypeError) return aValue.v.errorCode;
    
//     if (interpreter->pass == PassRun)
//     {
//          core->machine->videoRegisters.attr.value = aValue.v.floatValue;
//     }
    
//     return itp_endOfCommand(interpreter);
// }

enum ErrorCode cmd_SPRITE_VIEW(struct Core *core)
{
    struct Interpreter *interpreter = core->interpreter;
    
    // SPRITE VIEW
    ++interpreter->pc;
    ++interpreter->pc;
    
    // ON/OFF
    enum TokenType type = interpreter->pc->type;
    if (type != TokenON && type != TokenOFF) return ErrorSyntax;
    ++interpreter->pc;
    
    if (interpreter->pass == PassRun)
    {
        core->machine->videoRegisters.attr.spritesEnabled = type == TokenON ? 1 : 0;
    }
    
    return itp_endOfCommand(interpreter);
}

enum ErrorCode cmd_BG_VIEW(struct Core *core)
{
    struct Interpreter *interpreter = core->interpreter;
    
    // BG VIEW
    ++interpreter->pc;
    ++interpreter->pc;
    
    // ON/OFF
    enum TokenType type = interpreter->pc->type;
    if (type != TokenON && type != TokenOFF) return ErrorSyntax;
    ++interpreter->pc;
    
    // bg value
    struct TypedValue bgValue = itp_evaluateNumericExpression(core, 0, 3);
    if (bgValue.type == ValueTypeError) return bgValue.v.errorCode;
    
    if (interpreter->pass == PassRun)
    {
        int value = type == TokenON ? 1 : 0;
        if (bgValue.v.floatValue == 0)
        {
            core->machine->videoRegisters.attr.planeAEnabled = value;
        }
        else if (bgValue.v.floatValue == 1)
        {
            core->machine->videoRegisters.attr.planeBEnabled = value;
        }
        else if (bgValue.v.floatValue == 2)
        {
            core->machine->videoRegisters.attr.planeCEnabled = value;
        }
        else if (bgValue.v.floatValue == 3)
        {
            core->machine->videoRegisters.attr.planeDEnabled = value;
        }
    }

    return itp_endOfCommand(interpreter);
}

enum ErrorCode cmd_CELL_SIZE(struct Core *core)
{
    struct Interpreter *interpreter = core->interpreter;
    
    // CELL SIZE
    ++interpreter->pc;
    ++interpreter->pc;
    
    // bg value
    struct TypedValue bgValue = itp_evaluateNumericExpression(core, 0, 3);
    if (bgValue.type == ValueTypeError) return bgValue.v.errorCode;
    
    // comma
    if (interpreter->pc->type != TokenComma) return ErrorSyntax;
    ++interpreter->pc;
    
    // size value
    struct TypedValue sValue = itp_evaluateOptionalNumericExpression(core, 0, 1);
    if (sValue.type == ValueTypeError) return sValue.v.errorCode;
    
    if (interpreter->pass == PassRun)
    {
        if (bgValue.v.floatValue == 0)
        {
            core->machine->videoRegisters.attr.planeACellSize = sValue.v.floatValue;
        }
        else if(bgValue.v.floatValue == 1)
        {
            core->machine->videoRegisters.attr.planeBCellSize = sValue.v.floatValue;
        }
        else if(bgValue.v.floatValue == 2)
        {
            core->machine->videoRegisters.attr.planeCCellSize = sValue.v.floatValue;
        }
        else if(bgValue.v.floatValue == 3)
        {
            core->machine->videoRegisters.attr.planeDCellSize = sValue.v.floatValue;
        }
    }
    
    return itp_endOfCommand(interpreter);
}

struct TypedValue fnc_COLOR(struct Core *core)
{
    struct Interpreter *interpreter = core->interpreter;
    
    // COLOR
    ++interpreter->pc;
    
    // bracket open
    if (interpreter->pc->type != TokenBracketOpen) return val_makeError(ErrorSyntax);
    ++interpreter->pc;
    
    // pal expression
    struct TypedValue pValue = itp_evaluateNumericExpression(core, 0, NUM_PALETTES - 1);
    if (pValue.type == ValueTypeError) return pValue;
    
    // comma
    if (interpreter->pc->type != TokenComma) return val_makeError(ErrorSyntax);
    ++interpreter->pc;

    // pal expression
    struct TypedValue nValue = itp_evaluateNumericExpression(core, 0, 3);
    if (nValue.type == ValueTypeError) return nValue;
    
    // bracket close
    if (interpreter->pc->type != TokenBracketClose) return val_makeError(ErrorSyntax);
    ++interpreter->pc;
    
    struct TypedValue value;
    value.type = ValueTypeFloat;
    
    if (interpreter->pass == PassRun)
    {
        int p = pValue.v.floatValue;
        int n = nValue.v.floatValue;
        value.v.floatValue = core->machine->colorRegisters.colors[p * 4 + n];
    }
    return value;
}

struct TypedValue fnc_screen0(struct Core *core)
{
    struct Interpreter *interpreter = core->interpreter;
    
    // function
    enum TokenType type = interpreter->pc->type;
    ++interpreter->pc;
    
    struct TypedValue value;
    value.type = ValueTypeFloat;
    
    if (interpreter->pass == PassRun)
    {
        switch (type)
        {
            case TokenTIMER:
                value.v.floatValue = core->interpreter->timer;
                break;
                
            case TokenRASTER:
                value.v.floatValue = core->machine->videoRegisters.rasterLine;
                break;
                
            case TokenDISPLAY:
                // obsolete syntax!
                value.v.floatValue = core->machine->videoRegisters.attr.value;
                break;
                
            default:
                assert(0);
                break;
        }
    }
    return value;
}

struct TypedValue fnc_SCROLL_X_Y(struct Core *core)
{
    struct Interpreter *interpreter = core->interpreter;
    
    // SCROLL.?
    enum TokenType type = interpreter->pc->type;
    ++interpreter->pc;
    
    // bracket open
    if (interpreter->pc->type != TokenBracketOpen) return val_makeError(ErrorSyntax);
    ++interpreter->pc;
    
    // bg value
    struct TypedValue bgValue = itp_evaluateNumericExpression(core, 0, 3);
    if (bgValue.type == ValueTypeError) return bgValue;
    
    // bracket close
    if (interpreter->pc->type != TokenBracketClose) return val_makeError(ErrorSyntax);
    ++interpreter->pc;
    
    struct TypedValue value;
    value.type = ValueTypeFloat;
    
    if (interpreter->pass == PassRun)
    {
        int bg = bgValue.v.floatValue;
        struct VideoRegisters *reg = &core->machine->videoRegisters;
        switch (type)
        {
            case TokenSCROLLX:
                if (bg == 0)
                {
                    value.v.floatValue = reg->scrollAX | (reg->scrollMSB.aX << 8);
                }
                else if (bg == 1)
                {
                    value.v.floatValue = reg->scrollBX | (reg->scrollMSB.bX << 8);
                }
                else if (bg == 2)
                {
                    value.v.floatValue = reg->scrollCX | (reg->scrollMSB.cX << 8);
                }
                else if (bg == 3)
                {
                    value.v.floatValue = reg->scrollDX | (reg->scrollMSB.dX << 8);
                }
                break;
                
            case TokenSCROLLY:
                if (bg == 0)
                {
                    value.v.floatValue = reg->scrollAY | (reg->scrollMSB.aY << 8);
                }
                else if (bg == 1)
                {
                    value.v.floatValue = reg->scrollBY | (reg->scrollMSB.bY << 8);
                }
                else if (bg == 2)
                {
                    value.v.floatValue = reg->scrollCY | (reg->scrollMSB.cY << 8);
                }
                else if (bg == 3)
                {
                    value.v.floatValue = reg->scrollDY | (reg->scrollMSB.cY << 8);
                }
                break;
                
            default:
                assert(0);
                break;
        }
    }
    return value;
}
