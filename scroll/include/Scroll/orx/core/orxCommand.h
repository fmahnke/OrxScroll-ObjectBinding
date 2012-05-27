/* Orx - Portable Game Engine
 *
 * Copyright (c) 2008-2012 Orx-Project
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source
 *    distribution.
 */

/**
 * @file orxCommand.h
 * @date 29/04/2012
 * @author iarwain@orx-project.org
 *
 */

/**
 * @addtogroup orxCommand
 *
 * Command module
 * Module that can execute custom registered commands.
 * @{
 */

#ifndef _orxCOMMAND_H_
#define _orxCOMMAND_H_


#include "orxInclude.h"
#include "utils/orxString.h"


/** Event enum
 */
typedef enum __orxCOMMAND_EVENT_t
{
  orxCOMMAND_EVENT_REGISTER = 0,                      /**< Event sent when a command is registerd */
  orxCOMMAND_EVENT_UNREGISTER,                        /**< Event sent when a command is unregistered */
  orxCOMMAND_EVENT_EXECUTE,                           /**< Event sent when a command is executed */

  orxCOMMAND_EVENT_NUMBER,

  orxCOMMAND_EVENT_NONE = orxENUM_NONE

} orxCOMMAND_EVENT;

/** Variable type enum
 */
typedef enum __orxCOMMAND_VAR_TYPE_t
{
  orxCOMMAND_VAR_TYPE_STRING = 0,
  orxCOMMAND_VAR_TYPE_FLOAT,
  orxCOMMAND_VAR_TYPE_S32,
  orxCOMMAND_VAR_TYPE_U32,
  orxCOMMAND_VAR_TYPE_S64,
  orxCOMMAND_VAR_TYPE_U64,
  orxCOMMAND_VAR_TYPE_BOOL,
  orxCOMMAND_VAR_TYPE_VECTOR,

  orxCOMMAND_VAR_TYPE_NUMBER,

  orxCOMMAND_VAR_TYPE_NONE = orxENUM_NONE

} orxCOMMAND_VAR_TYPE;


/** Variable definition structure
 */
typedef struct __orxCOMMAND_VAR_DEF_t
{
  orxSTRING             zName;                        /**< Name : 4 */
  orxCOMMAND_VAR_TYPE   eType;                        /**< Type : 8 */

} orxCOMMAND_VAR_DEF;

/** Variable structure */
typedef struct __orxCOMMAND_VAR_t
{
  union
  {
    orxVECTOR           vValue;                       /**< Vector value : 24 */
    const orxSTRING     zValue;                       /**< String value : 4 */
    orxU32              u32Value;                     /**< U32 value : 4 */
    orxS32              s32Value;                     /**< S32 value : 4 */
    orxU64              u64Value;                     /**< U64 value : 8 */
    orxS64              s64Value;                     /**< S64 value : 8 */
    orxFLOAT            fValue;                       /**< Float value : 4 */
    orxBOOL             bValue;                       /**< Bool value : 4 */
  };

  orxCOMMAND_VAR_TYPE   eType;                        /**< Type : 28 */

} orxCOMMAND_VAR;

/** Command function type */
typedef void (orxFASTCALL *orxCOMMAND_FUNCTION)(orxU32 _u32ArgNumber, const orxCOMMAND_VAR *_astArgList, orxCOMMAND_VAR *_pstResult);


/** Command registration helpers
 */
#define orxCOMMAND_REGISTER_CORE_COMMAND(MODULE, COMMAND, RESULT_NAME, RESULT_TYPE, REQ_PARAM_NUMBER, OPT_PARAM_NUMBER, ...)        \
do                                                                                                                                  \
{                                                                                                                                   \
  orxCOMMAND_VAR_DEF  stResult;                                                                                                     \
  orxCOMMAND_VAR_DEF  astParamList[REQ_PARAM_NUMBER + OPT_PARAM_NUMBER + 1] = {__VA_ARGS__};                                        \
  orxSTATUS           eStatus;                                                                                                      \
  stResult.eType  = RESULT_TYPE;                                                                                                    \
  stResult.zName  = RESULT_NAME;                                                                                                    \
  eStatus         = orxCommand_Register(#MODULE"."#COMMAND, orx##MODULE##_Command##COMMAND, REQ_PARAM_NUMBER, OPT_PARAM_NUMBER, astParamList, &stResult);\
  orxASSERT(eStatus != orxSTATUS_FAILURE);                                                                                          \
} while(orxFALSE)


/** Command module setup
 */
extern orxDLLAPI void orxFASTCALL                     orxCommand_Setup();

/** Inits the command module
 * @return orxSTATUS_SUCCESS / orxSTATUS_FAILURE
 */
extern orxDLLAPI orxSTATUS orxFASTCALL                orxCommand_Init();

/** Exits from the command module
 */
extern orxDLLAPI void orxFASTCALL                     orxCommand_Exit();


/** Registers a command
* @param[in]   _zCommand      Command name
* @param[in]   _pfnFunction   Associated function
* @param[in]   _u32RequiredParamNumber Number of required parameters of the command
* @param[in]   _u32OptionalParamNumber Number of optional parameters of the command
* @param[in]   _astParamList  List of parameters of the command
* @param[in]   _pstResult     Result
* @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
*/
extern orxDLLAPI orxSTATUS orxFASTCALL                orxCommand_Register(const orxSTRING _zCommand, const orxCOMMAND_FUNCTION _pfnFunction, orxU32 _u32RequiredParamNumber, orxU32 _u32OptionalParamNumber, const orxCOMMAND_VAR_DEF *_astParamList, const orxCOMMAND_VAR_DEF *_pstResult);

/** Unregisters a command
* @param[in]   _zCommand      Command name
* @return      orxSTATUS_SUCCESS / orxSTATUS_FAILURE
*/
extern orxDLLAPI orxSTATUS orxFASTCALL                orxCommand_Unregister(const orxSTRING _zCommand);

/** Is a command registered?
* @param[in]   _zCommand      Command name
* @return      orxTRUE / orxFALSE
*/
extern orxDLLAPI orxBOOL orxFASTCALL                  orxCommand_IsRegistered(const orxSTRING _zCommand);


/** Evaluates a command
* @param[in]   _zCommandLine  Command name + arguments
* @param[out]  _pstResult     Variable that will contain the result
* @return      Command result if found, orxNULL otherwise
*/
extern orxDLLAPI orxCOMMAND_VAR *orxFASTCALL          orxCommand_Evaluate(const orxSTRING _zCommandLine, orxCOMMAND_VAR *_pstResult);

/** Executes a command
* @param[in]   _zCommand      Command name
* @param[in]   _u32ArgNumber  Number of arguments sent to the command
* @param[in]   _astArgList    List of arguments sent to the command
* @param[out]  _pstResult     Variable that will contain the result
* @return      Command result if found, orxNULL otherwise
*/
extern orxDLLAPI orxCOMMAND_VAR *orxFASTCALL          orxCommand_Execute(const orxSTRING _zCommand, orxU32 _u32ArgNumber, const orxCOMMAND_VAR *_astArgList, orxCOMMAND_VAR *_pstResult);


#endif /* _orxCOMMAND_H_ */

/** @} */
