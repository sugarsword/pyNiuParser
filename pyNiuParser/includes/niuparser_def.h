/****************************************************************************
* Project Name : NiuParser SDK V1.0
* File Name    : niuparser_def.h
* Author       : Wang Qiang
* Email        : wangqiangneu@gmail.com
* Create Time  : 2014/12/11 10:05:57
* Copyright    : Copyright (c) 2014 NEU NLP LAB. All rights reserved.
*
*
*
****************************************************************************/

#ifndef _NIUPARSER_DATA_STRUCTURE_H_
#define _NIUPARSER_DATA_STRUCTURE_H_

#include <string.h>
#include <stdlib.h>

	

#define TAGGER_BUFFER_SIZE 64


// Following is return value definition
#define NIUPARSER_RET_OK 0
#define NIUPARSER_RET_ERROR 1
#define NIUPARSER_RET_POINTER_NULL 2
#define NIUPARSER_RET_CP_FORMAT_ERROR 3
#define NIUPARSER_RET_FUNC_INVALID 4
#define NIUPARSER_RET_LICENSE_ERROR 5
#define NIUPARSER_RET_INPUT_TOO_LONG 6
#define NIUPARSER_RET_FILE_NOT_ACCESS 7
#define NIUPARSER_RET_ENCODING_ERROR 8





typedef struct Switch_ST
{
	bool	m_is_ws_on;
	bool	m_is_pos_on;
	bool	m_is_ner_on;
	bool	m_is_chk_on;
	bool	m_is_cp_on;
	bool	m_is_dp_on;
	bool	m_is_srl_on;
	
	Switch_ST()
		:m_is_ws_on(false),m_is_pos_on(false),m_is_ner_on(false),m_is_chk_on(false),m_is_cp_on(false),m_is_dp_on(false),m_is_srl_on(false){};
	
}Switch_ST;


typedef struct Seg_Result_ST
{
	
	unsigned int m_word_num ;
	char** m_word_array;
	
}Seg_Result_ST;


typedef struct Pos_Cell_ST
{
	char* m_word;
	char m_pos[TAGGER_BUFFER_SIZE];
}Pos_Cell_ST;

typedef struct Pos_Result_ST
{
	unsigned int m_word_num;
	Pos_Cell_ST* m_cell_array;
}Pos_Result_ST;

typedef struct Ner_Cell_ST
{
	int	m_start_pos;
	int	m_length;
	char m_type[TAGGER_BUFFER_SIZE];
}Ner_Cell_ST;

typedef struct Ner_Result_ST
{
	unsigned int m_ne_num;
	Ner_Cell_ST* m_cell_array;
	Seg_Result_ST m_seg_result;
}Ner_Result_ST;

typedef Ner_Cell_ST Chk_Cell_ST;

typedef struct Chk_Result_ST
{
	unsigned int m_chk_num;
	Chk_Cell_ST* m_cell_array;
	Seg_Result_ST m_seg_result;
}Chk_Result_ST;



typedef struct Dep_Cell_ST
{
	char* m_word;
	char m_type[TAGGER_BUFFER_SIZE];
	int	m_center_word_id;
	char m_relation[TAGGER_BUFFER_SIZE];


}Dep_Cell_ST;

typedef struct Dep_Result_ST
{
	unsigned int m_word_num;
	Dep_Cell_ST* m_cell_array;

}Dep_Result_ST;


typedef struct Con_Result_ST
{
	char* m_result;
}Con_Result_ST;

typedef struct Srl_Role_ST
{
	unsigned int m_start_pos;
	unsigned int m_end_pos;
	char	m_label[TAGGER_BUFFER_SIZE];
}Srl_Role_ST;

typedef struct Srl_Cell_ST
{
	unsigned int m_role_num;
	Srl_Role_ST* m_role_array;

}Srl_Cell_ST;



typedef struct Srl_Result_ST
{
	unsigned int m_predict_num;
	Srl_Cell_ST* m_cell_array;
	Seg_Result_ST m_seg_result;
}Srl_Result_ST;




#endif