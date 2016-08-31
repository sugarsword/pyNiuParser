/****************************************************************************
*  					 			NiuParser SDK
*
* 				Copyright (c) 2014-2015 NiuParser All rights reserved.
*
*							niuparser@zjyatuo.com
*
****************************************************************************/





#include "niuparser_sdk.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

//�����ִʽ���
void show_seg_result(Seg_Result_ST & seg_result , ofstream & output)
{
	for(unsigned int i=0;i<seg_result.m_word_num;i++)
	{
		output<<seg_result.m_word_array[i]<<" ";
	}
	output<<endl;
}

//�������Ա�ע����
void show_pos_result(Pos_Result_ST & pos_result , ofstream & output)
{
	for(unsigned int i=0;i<pos_result.m_word_num;i++)
	{
		output<<pos_result.m_cell_array[i].m_word<<"/"<<pos_result.m_cell_array[i].m_pos<<" ";
	}
	output<<endl;
}

//��������ʵ��ʶ������
void show_ner_result(Ner_Result_ST& ner_result , ofstream & output)
{
	char buffer[1024] = {0};

	for(unsigned int i=0;i<ner_result.m_ne_num;i++)
	{
		memset(buffer , 0 , 1024*sizeof(char));
		Ner_Cell_ST cell = ner_result.m_cell_array[i];
		for(unsigned int pos=cell.m_start_pos;pos<cell.m_length+cell.m_start_pos;pos++)
		{
			strcat(buffer,ner_result.m_seg_result.m_word_array[pos]);
			strcat(buffer," ");
		}
		buffer[strlen(buffer)-1] = '\0';
		output<<buffer<<" => "<<cell.m_type<<" ";
	}
	output<<"\n";

}

//��������ʶ������
void show_chunk_result(Chk_Result_ST & chunk_result , ofstream & output)
{
	char buffer[1024] = {0};

	for(unsigned int i=0;i<chunk_result.m_chk_num;i++)
	{
		memset(buffer , 0 , 1024*sizeof(char));
		Ner_Cell_ST cell = chunk_result.m_cell_array[i];
		for(unsigned int pos=cell.m_start_pos;pos<cell.m_length+cell.m_start_pos;pos++)
		{
			strcat(buffer,chunk_result.m_seg_result.m_word_array[pos]);
			strcat(buffer," ");
		}
		buffer[strlen(buffer)-1] = '\0';
		output<<buffer<<" => "<<cell.m_type<<" ";
	}
	output<<"\n";

}

//�����ɷ־䷨��������
void show_constituent_result(Con_Result_ST & con_result , ofstream & output)
{
	output<<con_result.m_result<<endl;
}


//���������䷨��������
void show_dep_result(Dep_Result_ST & dep_result , ofstream & output)
{
	for(unsigned int i=0;i<dep_result.m_word_num;i++)
	{
		Dep_Cell_ST cell = dep_result.m_cell_array[i];
		output<<cell.m_word<<"\t"<<cell.m_type<<"\t"<<cell.m_center_word_id<<"\t"<<cell.m_relation<<endl;
	}
}

void get_string(int start_pos , int end_pos , Seg_Result_ST & seg , char* sub)
{
	for(unsigned int i=start_pos;i<end_pos;i++)
	{
		strcat(sub , seg.m_word_array[i]);
		strcat(sub , " ");
	}
	strcat(sub , seg.m_word_array[end_pos]);

}

//����������ɫ��ע����
void show_srl_result(Srl_Result_ST & srl_result , ofstream & output)
{
	for(unsigned int i=0;i<srl_result.m_predict_num;i++)
	{
		Srl_Cell_ST cell = srl_result.m_cell_array[i];
		for(unsigned int j=0;j<cell.m_role_num;j++)
		{
			char buffer[1024] = {0};
			get_string(cell.m_role_array[j].m_start_pos , cell.m_role_array[j].m_end_pos , srl_result.m_seg_result , buffer);
			output<<buffer<<" => "<<cell.m_role_array[j].m_label<<" ";
		}
		output<<endl;
	}
}


int main(void)
{

	Switch_ST switcher; //�������� Ĭ�����й��ܶ��ǹر�״̬

	//�������й���
	switcher.m_is_ws_on = false;
	switcher.m_is_pos_on = false;
	switcher.m_is_ner_on = false;
	switcher.m_is_chk_on = false;
	switcher.m_is_dp_on = true;
	switcher.m_is_cp_on = false;
	switcher.m_is_srl_on = false;

	//��ʱ
	clock_t start_time = clock();

	//��ʼ��NiuParser
	if(NiuParser_Create_Instance(switcher) == NIUPARSER_RET_OK)
		cerr<<"NiuParser Init Successfully ! Use "<<((double)(clock()-start_time)) / CLOCKS_PER_SEC<<" s "<<endl;
	else
	{
		cerr<<"NiuParser Init Failed ! Use "<<endl;
		exit(-1);
	}

	int line_num = 0;
	//�����ļ�
	ifstream input("/dev/stdin");
	if(!input)
	{
		cerr<<"can't read test.utf8 "<<endl;
		return -1;
	}
	//�����ļ�
	ofstream output("/dev/stdout");
	if(!output)
	{
		cerr<<"can't write output.txt"<<endl;
		return -1;
	}


	string line("");

	while(!input.eof() && getline(input , line))
	{
		int ret;
/*		//�ִ��÷�
		Seg_Result_ST seg_result ;
		ret = NiuParser_Segmenter_Sentence((char*)line.c_str(), seg_result);
		if(ret == NIUPARSER_RET_OK)
		{
			show_seg_result(seg_result , output);
			NiuParser_Release_Segment_Memory(seg_result);
		}

		//���Ա�ע�÷�
		Pos_Result_ST pos_result ;
		ret = NiuParser_POS_Tagger_Sentence((char*)line.c_str(),pos_result);
		if(ret == NIUPARSER_RET_OK)
		{
			show_pos_result(pos_result,output);
			NiuParser_Release_Pos_Tagger_Memory(pos_result);
		}

		//����ʵ��ʶ���÷�
		Ner_Result_ST ner_result;
		ret = NiuParser_NE_Recognizer_Sentence((char*)line.c_str(),ner_result);
		if(ret == NIUPARSER_RET_OK)
		{
			show_ner_result(ner_result,output);
			NiuParser_Release_Name_Entity_Memory(ner_result);
		}

		//����ʶ���÷�
		Chk_Result_ST chk_result;
		ret = NiuParser_CHK_Recognizer_Sentence((char*)line.c_str(),chk_result);
		if(ret == NIUPARSER_RET_OK)
		{
			show_chunk_result(chk_result , output);
			NiuParser_Release_Chunking_Memory(chk_result);
		}

		//�ɷ־䷨�����÷�
		Con_Result_ST con_result;
		ret = NiuParser_Constituent_Parser_Sentence((char*)line.c_str() , con_result);
		if(ret == NIUPARSER_RET_OK)
		{
			show_constituent_result(con_result , output);
			NiuParser_Release_Constituent_Parser_Memory(con_result);
		}
*/
		//�����䷨�����÷�
		Dep_Result_ST dep_result;
		ret = NiuParser_Dependency_Parser_Sentence((char*)line.c_str(),dep_result);
		if(ret == NIUPARSER_RET_OK)
		{
			show_dep_result(dep_result , output);
			NiuParser_Release_Dependency_Parser_Memory(dep_result);
		}
/*
		//������ɫ��ע�÷�
		Srl_Result_ST srl_result;
		ret = NiuParser_Semantic_Role_Label_Sentence((char*)line.c_str() , srl_result);
		if(ret == NIUPARSER_RET_OK)
		{
			show_srl_result(srl_result , output);
			NiuParser_Release_Semantic_Role_Label_Memory(srl_result);
		}
*/
	}

	input.close();
	output.close();

	NiuParser_Release_Instance();


	return 0;
}
