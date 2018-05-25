#pragma once
#include<Windows.h>
#include<iostream>
#include<memory.h>
typedef struct PE {
	PIMAGE_DOS_HEADER dos_header;
	PIMAGE_NT_HEADERS nt_headers;
	PIMAGE_FILE_HEADER file_header;
	PIMAGE_OPTIONAL_HEADER op_header;
	PIMAGE_SECTION_HEADER sectionheader;
	//PIMAGE_IMPORT_DESCRIPTOR importdescriptor;
};

BOOL Writeprocess(PCHAR filename,PVOID buffer,PE pe);//д�뵽�ļ���

BOOL RVAtoFA(PE pe, DWORD RVA, DWORD &FA);//����ƫ��ת�ļ�ƫ��

BOOL FAtoRVA(PE pe, DWORD &RVA, DWORD FA);//�ļ�ƫ��ת����ƫ��

BOOL Readprocess(PCHAR dest_process, PVOID & buffer);//��ȡӦ�õ��ֽ��룬���ڶ���(buffer)��������Ҫfree

BOOL CheckAndSet(PVOID buffer, PE &pe);//����Ƿ����pe�ṹ������������򷵻�0������pe�ĸ���ָ��ָ����ȷ��λ��

BOOL PrintEverything(PE &pe);//��ӡ���еĽṹ,��ӡ�ɹ�����true

BOOL PrintImport(PE pe);//��ӡ�����

BOOL PrintExport(PE pe);//��ӡ������

BOOL AddSection(PE &pe,PVOID &buffer);//����һ����