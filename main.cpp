#include"pestudy.h"
using namespace std;
int(*ff)();
int main(int argc,char * argv[]) {
	CHAR dest_process[] = "D:\\Program Files (x86)\\workspace\\PE_study\\PE_study\\123.EXE";
	//CHAR dest_process[] = "D:\\Program Files (x86)\\workspace\\PE_study\\PE_study\\PROCS.DLL";
	//dest_process = argv[1];
	//CHAR write_process[] = "LeetCode1.exe";
	PE pe;
	PVOID buffer = NULL;
	if (!Readprocess(dest_process, buffer)) {
		cout << "Open Failed!" << endl;
		//delete[]buffer;
		return 0;
	}
	
	if (!CheckAndSet(buffer, pe)) {
		cout << "������Ч��PE��ʽ��" << endl;
		delete[]buffer;
		return 0;
	}
	
	PrintEverything(pe);//��ӡ�����ֶ�
	DWORD RVA, FA;
	RVA = 0x295DC;
	RVAtoFA(pe, RVA, FA);
	PrintImport(pe);
	PrintExport(pe);
	//AddSection(pe,buffer);

	//����createdll.dll��Ӳ����
	//BYTE Code[] = {0x6A,0x00,0x6A,0x00,0x6A,0x00,0x6A,0x00,0xFF,0x15,0xF4,0xF2,0x42,0x00,
		//0xe9,0x00,0x00,0x00,0x00};//shellcode���ڳ�������ǰ����һ��messagebox


	//BYTE Code[] = { 
	//	//�����ֳ�
	//	0x60,0x9c,
	//	//*******************
	//	//�ؼ�����
	//	0xe8,0x00,0x00,0x00,0x00,0x58,//ͨ��call 0��pop eax����ǰ�ĵ�ַ���뵽eax�У�ִ�к�eax�е�ֵָ��0x58��λ��
	//	0x05,0x15,0x00,0x00,0x00,//eax+���λ�ã�shellcode����֮����Զ�
	//	0x50,//��eaxѹ���ջ
	//	0xb8,0x00,0x00,0x00,0x00,
	//	0xff,0xd0,//call eax����loadlibrary,
	//	//*******************
	//	//�ָ��ֳ�
	//	0x9d,0x61,

	//	0xe9,0x00,0x00,0x00,0x00, //������ֽ�������ת����Ӧ��λ��

	//	//��Ҫʹ�õ����ַ���
	//	'c','r','e','a','t','e','d','l','l','.','d','l','l','\0'//���ص�dll����
	//};
	//HMODULE a = GetModuleHandleA("kernel32.dll");
	//DWORD loadlibrary = (DWORD)GetProcAddress(a, "LoadLibraryA");
	//DWORD *p = (DWORD *)(Code + 15);
	//*p = loadlibrary;
	//DWORD extrodatasize = 14;//���ص�dll���Ƴ���
	//AddCode(pe, Code, sizeof Code, extrodatasize);
	//Writeprocess(write_process, buffer, pe);
	PrintRelocation(pe);
	void * newbuffer = NULL;
	ExaToMem(pe, newbuffer);
	
	ff = (int(*)())((PBYTE)newbuffer+pe.op_header->AddressOfEntryPoint);
	
	HMODULE hker = LoadLibrary(TEXT("Kernel32.dll"));
	DWORD add = (DWORD)GetProcAddress(hker, "GetVersion");
	/*HANDLE h1=GetModuleHandle(0);
	PE nowpe;
	CheckAndSet((PVOID)h1, nowpe);
	DWORD lpflOldProtect;
	VirtualProtect((PVOID)h1, nowpe.op_header->SizeOfImage + 0x20, PAGE_EXECUTE_READWRITE, &lpflOldProtect);
	DWORD tempaddr = nowpe.op_header->DataDirectory[13].VirtualAddress;
	nowpe.op_header->DataDirectory[13].VirtualAddress = pe.op_header->DataDirectory[13].VirtualAddress;*/
	ff();
	//nowpe.op_header->DataDirectory[13].VirtualAddress = tempaddr;
	delete[]newbuffer;
	newbuffer = NULL;
	delete[]buffer;
	buffer = NULL;
	//getchar();
	return 0;
}