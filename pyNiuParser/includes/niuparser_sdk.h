/*****************************************************************************************************
* Copyright 2013 Chinese Language Analysis Platform (CLAP) Engine Project
* Revision:0.1
* File Name: clap_engine.h
* Author: Zhu Muhua
* Email: zhumuhua@gmail.com
* Time: Nov.6, 2013
* Create for Chinese Language Analysis Platform Engine.
*****************************************************************************************************/
/* last update: Nov.5, 2013 */

/*****************************************************************************************************
*
* CLAP Engine Head File.
*
*****************************************************************************************************/
#ifndef _NIUPARSER_SDK_DEF_H_
#define _NIUPARSER_SDK_DEF_H_

#include "niuparser_def.h"


//#define DEBUG
//#define  NIUPARSER_EXPORT

#ifndef DEBUG

#ifndef WIN32
	#define NIUPARSER_API
#else

#ifdef NIUPARSER_EXPORT
	#define NIUPARSER_API __declspec(dllexport)
#else
	#pragma comment(lib, "niuparser_sdk_win.lib")
	#define NIUPARSER_API __declspec(dllimport)
#endif

#endif


#else

#define NIUPARSER_API
#endif


#ifdef __cplusplus
extern "C"{
#endif
/*****************************************************************************************************
*Function: Clap_Create_Instance
*Params: init_data_ptr: /IN/ data needed by initialization
*        out_handle:    /OUT/ return handle of one engine instance*
*Return: CLAP_RET_OK:  return normal
*        CLAP_RET_LOAD_DIC_NG: load system dictionary or user dictionary error
*        CLAP_RET_NO_ENOUGH_MEMORY: no enough memory to work
*        CLAP_RET_ERROR: other errors
******************************************************************************************************/
NIUPARSER_API int NiuParser_Create_Instance(Switch_ST & switcher);

/*****************************************************************************************************
*Fucntion: Clap_Release_Instance
*Params: engine_handle:    /IN/
*Return: CLAP_RET_OK:  return normal
*        CLAP_RET_NO_ENGINE_INSTANCE: No such engine instance
*        CLAP_RET_ERROR: other errors
******************************************************************************************************/
NIUPARSER_API int NiuParser_Release_Instance();
NIUPARSER_API int NiuParser_Release_Segment_Memory(Seg_Result_ST & seg_result);
NIUPARSER_API int NiuParser_Release_Pos_Tagger_Memory(Pos_Result_ST & pos_result);
NIUPARSER_API int NiuParser_Release_Name_Entity_Memory(Ner_Result_ST & ner_result);
NIUPARSER_API int NiuParser_Release_Chunking_Memory(Chk_Result_ST & chk_result);
NIUPARSER_API int NiuParser_Release_Constituent_Parser_Memory(Con_Result_ST & con_result);
NIUPARSER_API int NiuParser_Release_Dependency_Parser_Memory(Dep_Result_ST & dep_result);
NIUPARSER_API int NiuParser_Release_Semantic_Role_Label_Memory(Srl_Result_ST & srl_result);
//NIUPARSER_API int NiuParser_Release_Constituent_Parser_Memory(Seg_Result_ST & seg_result);
//NIUPARSER_API int NiuParser_Release_Constituent_Parser_Memory(Seg_Result_ST & seg_result);


/******************************************************************************************************
*Function: Clap_Segmenter_Analyze
*Params: engine_handle:   /IN/
*        request_data_ptr: /IN-OUT/ data will be analyzed and the analysis result
*Return: CLAP_RET_OK:  return normal
*        CLAP_RET_NO_ENGINE_INSTANCE: no such engine instance
*        CLAP_RET_POINTER_NULL: one of parameters is NULL
*        CLAP_RET_SENTENCE_ERROR: sentence error, length of the sentence is out of range or encode is not utf-8
*        CLAP_RET_NO_ENOUGH_MEMORY: no enough memory to work
*        CLAP_RET_NO_ST_DATA: there is no statistical data in engine
*        CLAP_RET_NO_POST_RULE: if need_post_process is set as true and there is no Post Rule loaded
*        CLAP_RET_ERROR: other errors
******************************************************************************************************/
NIUPARSER_API int NiuParser_Segmenter_Sentence(char* input , Seg_Result_ST & seg_result);


/*****************************************************************************************************
*Function: Clap_POS_Tagger_Analyze
*Params: engine_handle:   /IN/
*        pt_data_ptr: /IN-OUT/ data will be analyzed
*Return: CLAP_RET_OK:  return normal
*        CLAP_RET_NO_ENGINE_INSTANCE: no such engine instance
*        CLAP_RET_POINTER_NULL: one of parameters is NULL
*        CLAP_RET_SENTENCE_ERROR: sentence error, length of the sentence is out of range or encode is not utf-8
*        CLAP_RET_NO_ENOUGH_MEMORY: no enough memory to work
*        CLAP_RET_NO_ST_DATA: there is no statistical data in engine
*        CLAP_RET_NO_POST_RULE: if need_post_process is set as true and there is no Post Rule loaded
*        CLAP_RET_ERROR: other errors
******************************************************************************************************/
NIUPARSER_API int NiuParser_POS_Tagger_Sentence(char* input , Pos_Result_ST & pos_result);

/*****************************************************************************************************
*Function: Clap_NE_Recognizer_Analyze
*Params: engine_handle:   /IN/
*        ner_data_ptr: /IN-OUT/ data will be analyzed
*Return: CLAP_RET_OK:  return normal
*        CLAP_RET_NO_ENGINE_INSTANCE: no such engine instance
*        CLAP_RET_POINTER_NULL: one of parameters is NULL
*        CLAP_RET_SENTENCE_ERROR: sentence error, length of the sentence is out of range or encode is not utf-8
*        CLAP_RET_NO_ENOUGH_MEMORY: no enough memory to work
*        CLAP_RET_NO_ST_DATA: there is no statistical data in engine
*        CLAP_RET_NO_POST_RULE: if need_post_process is set as true and there is no Post Rule loaded
*        CLAP_RET_ERROR: other errors
******************************************************************************************************/
NIUPARSER_API int NiuParser_NE_Recognizer_Sentence(char* input , Ner_Result_ST & ner_result);

/*****************************************************************************************************
*Function: Clap_CHK_Recognizer_Analyze
*Params: engine_handle:   /IN/
*        chk_data_ptr: /IN-OUT/ data will be analyzed
*Return: CLAP_RET_OK:  return normal
*        CLAP_RET_NO_ENGINE_INSTANCE: no such engine instance
*        CLAP_RET_POINTER_NULL: one of parameters is NULL
*        CLAP_RET_SENTENCE_ERROR: sentence error, length of the sentence is out of range or encode is not utf-8
*        CLAP_RET_NO_ENOUGH_MEMORY: no enough memory to work
*        CLAP_RET_NO_ST_DATA: there is no statistical data in engine
*        CLAP_RET_NO_POST_RULE: if need_post_process is set as true and there is no Post Rule loaded
*        CLAP_RET_ERROR: other errors
******************************************************************************************************/
NIUPARSER_API int NiuParser_CHK_Recognizer_Sentence(char* input , Chk_Result_ST & chk_result);

/*****************************************************************************************************
*Function: Clap_Constituent_Parser_Analyze
*Params: engine_handle:   /IN/
*        cp_data_ptr: /IN-OUT/ data will be analyzed
*Return: CLAP_RET_OK:  return normal
*        CLAP_RET_NO_ENGINE_INSTANCE: no such engine instance
*        CLAP_RET_POINTER_NULL: one of parameters is NULL
*        CLAP_RET_SENTENCE_ERROR: sentence error, length of the sentence is out of range or encode is not utf-8
*        CLAP_RET_NO_ENOUGH_MEMORY: no enough memory to work
*        CLAP_RET_NO_ST_DATA: there is no statistical data in engine
*        CLAP_RET_NO_POST_RULE: if need_post_process is set as true and there is no Post Rule loaded
*        CLAP_RET_ERROR: other errors
******************************************************************************************************/
NIUPARSER_API int NiuParser_Constituent_Parser_Sentence(char* input , Con_Result_ST & con_result);

/*****************************************************************************************************
*Function: Clap_Dependency_Parser_Analyze
*Params: engine_handle:   /IN/
*        dp_data_ptr: /IN-OUT/ data will be analyzed
*Return: CLAP_RET_OK:  return normal
*        CLAP_RET_NO_ENGINE_INSTANCE: no such engine instance
*        CLAP_RET_POINTER_NULL: one of parameters is NULL
*        CLAP_RET_SENTENCE_ERROR: sentence error, length of the sentence is out of range or encode is not utf-8
*        CLAP_RET_NO_ENOUGH_MEMORY: no enough memory to work
*        CLAP_RET_NO_ST_DATA: there is no statistical data in engine
*        CLAP_RET_NO_POST_RULE: if need_post_process is set as true and there is no Post Rule loaded
*        CLAP_RET_ERROR: other errors
******************************************************************************************************/
NIUPARSER_API int NiuParser_Dependency_Parser_Sentence(char* input , Dep_Result_ST & dep_result);

/*****************************************************************************************************
*Function: Clap_Constituent_SRL_Analyze
*Params: engine_handle:   /IN/
*        csrl_data_ptr: /IN-OUT/ data will be analyzed
*Return: CLAP_RET_OK:  return normal
*        CLAP_RET_NO_ENGINE_INSTANCE: no such engine instance
*        CLAP_RET_POINTER_NULL: one of parameters is NULL
*        CLAP_RET_SENTENCE_ERROR: sentence error, length of the sentence is out of range or encode is not utf-8
*        CLAP_RET_NO_ENOUGH_MEMORY: no enough memory to work
*        CLAP_RET_NO_ST_DATA: there is no statistical data in engine
*        CLAP_RET_NO_POST_RULE: if need_post_process is set as true and there is no Post Rule loaded
*        CLAP_RET_ERROR: other errors
******************************************************************************************************/
NIUPARSER_API int NiuParser_Semantic_Role_Label_Sentence(char* input , Srl_Result_ST & srl_result);


#ifdef __cplusplus
}
#endif

#endif

/* leave blank line to be compatible with some linux platform */

