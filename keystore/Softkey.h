#ifndef SOFTKEY_H
#define SOFTKEY_H

#include <QLibrary>
#include <windows.h>
#include <setupapi.h>
#include "hidsdi.h"



class SoftKey
{
public:
    SoftKey();
    virtual ~SoftKey();
public:
    int CheckKeyByFindort_2();
    int CheckKeyByReadEprom();
    int CheckKeyByEncstring();
    int CheckKeyByEncstring_New();
private:
    int ReadStringEx(int addr,char *outstring,char *DevicePath);
    int Sub_CheckKeyByEncstring(char *InString,char *DevicePath);
public:
    //�����İ汾
    int NT_GetIDVersion(int *Version,char *InPath);
    //��ȡ������չ�汾
    int NT_GetVersionEx(int *Version,char *InPath);

    //�㷨����
    int sWrite_2Ex(  DWORD in_data,DWORD *out_data,char *Path);
    int sWriteEx(  DWORD in_data,DWORD *out_data,char *Path);
    int sRead(  DWORD *out_data,char *Path);
    int sWrite(  DWORD in_data,char *Path);
    int sWrite_2(  DWORD in_data,char *Path);

    //дһ���ֽڵ���������
    int YWrite(BYTE InData,short address,char * HKey,char *LKey,char *Path );
    //�Ӽ������ж�ȡһ���ֽ�
    int YRead(BYTE *OutData,short address,char * HKey,char *LKey,char *Path );
    //дһ���ֽڵ���������
    int YWriteEx(BYTE *InData,short address,short len,char *HKey,char *LKey,char *Path );
    //�Ӽ������ж�ȡһ���ֽ�
    int YReadEx(BYTE *OutData,short address,short len,char *HKey,char *LKey,char *Path );

    //����ָ���ļ�������ʹ����ͨ�㷨һ��
    int FindPort_2(  int start,DWORD in_data,DWORD verf_data,char *OutPath);
    //���Ҽ�����
    int FindPort(  int start,char *OutPath);

    //��ȡ����ID
    int GetID(  DWORD *ID_1,DWORD *ID_2,char *InPath);

    //�Ӽ������ж��ַ���
    int YReadString(char *string ,short Address,int len,char * HKey,char *LKey,char *Path );
    //д�ַ�������������
    int YWriteString(char *InString,short Address,char * HKey,char *LKey,char *Path );
    //����д����
    int SetWritePassword(char * W_HKey,char *W_LKey,char * new_HKey,char *new_LKey,char *InPath);
    //���ö�����
    int SetReadPassword(char * W_HKey,char *W_LKey,char * new_HKey,char *new_LKey,char *InPath);

    //������ǿ�㷨��Կһ
    int SetCal_2(char *Key,char *InPath);
    //ʹ����ǿ�㷨һ���ַ������м���
    int EncString(  char *InString,char *OutString,char *Path);
    //ʹ����ǿ�㷨һ�Զ��������ݽ��м���
    int Cal(  BYTE *InBuf,BYTE *OutBuf,char *Path);

    //������ǿ�㷨��Կ��
    int SetCal_New(char *Key,char *InPath);
    //ʹ����ǿ�㷨�����ַ������м���
    int Cal_New(  BYTE *InBuf,BYTE *OutBuf,char *Path);
    //ʹ����ǿ�㷨�����ַ������м���
    int EncString_New(  char *InString,char *OutString,char *Path);

    //ʹ����ǿ�㷨���ַ������н���(ʹ�����)
    void StrDec(  char *InString,char *OutString,char *Key);
    void StrEnc(  char *InString,char *OutString,char *Key);
    void EnCode(   BYTE  * InData,BYTE  * OutData,  char *Key  );
    void DeCode(   BYTE  * InData, BYTE  * OutData, char *Key  );
    //ʹ����ǿ�㷨�Զ��������ݽ��м���(ʹ�����)
    void  DecBySoft(    BYTE  *   aData,   BYTE   *   aKey   )  ;
    void  EncBySoft(   BYTE  *   aData,  BYTE   *   aKey   )   ;

    //�ַ��������������ݵ�ת��
     void HexStringToByteArray(char * InString,BYTE *out_data);
     void ByteArrayToHexString(BYTE *in_data,char * OutString,int len);

     //��ʼ��������,ע�⣬��ʼ���������е�����Ϊ0����д����ҲΪ00000000-00000000����ǿ�㷨���ᱻ��ʼ��
    int ReSet(char *InPath);

    //���º���ֻ���ڴ�U�̵���
    //�����Ƿ���ʾU�̲����̷�����Ϊ��ʾ����Ϊ����ʾ
    int SetHidOnly(  BOOL IsHidOnly,char *InPath);
    //����U�̲���Ϊֻ��״̬��
    int SetUReadOnly( char *InPath);
    //����U�̲����Ƿ�Ϊֻ��״̬����Ϊֻ��
    int IsUReadOnly(BOOL *IsReadOnly,char *InPath);

    //����ָ���ļ�������ʹ����ͨ�㷨һ�������ص���U�̵�·��,��U�̵��̷���ͨ�����·��Ҳ����ֱ�Ӳ�����
    int FindU_2(  int start,DWORD in_data,DWORD verf_data,char *OutPath);
    //���Ҽ����������ص���U�̵�·��,��U�̵��̷���ͨ�����·��Ҳ����ֱ�Ӳ�����
    int FindU(  int start,char *OutPath);

    //���º���ֻ֧������оƬ����
    //����SM2��Կ��
    int YT_GenKeyPair(char* PriKey,char *PubKeyX,char *PubKeyY,char *InPath);
    //����Pin��
    int YtSetPin(char *old_pin,char *new_pin,char *InPath );
    //����SM2��Կ�Լ����
    int Set_SM2_KeyPair(char *PriKey,char *PubKeyX,char *PubKeyY,char *sm2UserName,char *InPath );
    //���ؼ������Ĺ�Կ
    int Get_SM2_PubKey(char *PubKeyX,char *PubKeyY,char *sm2UserName,char *InPath);
    //�Զ��������ݽ���SM2����
    int SM2_EncBuf(BYTE *InBuf,BYTE *OutBuf,int inlen,char *InPath);
    //�Զ��������ݽ���SM2����
    int SM2_DecBuf(BYTE *InBuf,BYTE *OutBuf,int inlen,char* pin,char *InPath);
    //���ַ�������SM2����
    int SM2_EncString(char *InString,char *OutString,char *InPath);
    //���ַ�������SM2����
    int SM2_DecString(char *InString,char *OutString,char* pin,char *InPath);
    //��������Ӳ��оƬΨһID
    int GetChipID( char *OutChipID,char *InPath);
    //�������ĳ�������
    int GetProduceDate(  char *OutDate,char *InPath);
    //����ID����
    int SetID(char * Seed,char *InPath);
    //������ͨ�㷨
    int SetCal(char * W_HKey,char *W_LKey,char * new_HKey,char *new_LKey,char *InPath);
    void SnToProduceDate(char* InSn,char *OutProduceDate);
public:
     BOOL IsLoad;
private:
    BOOL  LoadLib();
    int   Hanldetransfe(HANDLE hUsbDevice,BYTE *array_in,int InLen,BYTE *array_out,int OutLen,char *InPath);
    HANDLE MyOpenPath(char *InPath);
    int NT_GetVersion(int *Version,char *InPath);
    int NT_Read(  BYTE * ele1,BYTE * ele2,BYTE * ele3,BYTE * ele4,char *Path);
    int NT_Write(  BYTE * ele1,BYTE * ele2,BYTE * ele3,BYTE * ele4,char *Path);
    int ReadDword(  DWORD *in_data,char *Path);
    int WriteDword(  DWORD *out_data,char *Path);
    int Y_Write(BYTE *InData,short address,short len,BYTE *password,char *Path );
    int Y_Read(BYTE *OutData,short address ,short len,BYTE *password,char *Path );
    int NT_FindPort_2(  int start,DWORD in_data,DWORD verf_data,char *OutPath);
    int NT_FindPort(  int start,char *OutPath);
    int NT_GetID(  DWORD *ID_1,DWORD *ID_2,char *InPath);
    int NT_Write_2(  BYTE * ele1,BYTE * ele2,BYTE * ele3,BYTE * ele4,char *Path);
    int WriteDword_2(  DWORD *out_data,char *Path);
    int NT_SetCal_2(BYTE *InData,BYTE IsHi,char *Path );
    int NT_Cal(  BYTE * InBuf,BYTE *OutBuf,char *InPath);
    int NT_ReSet(char *Path );
    BOOL isfindmydevice( int pos ,int *count,char *OutPath);
    BOOL SetFeature (HANDLE hDevice,BYTE *array_in,INT in_len);
    BOOL GetFeature (HANDLE hDevice,BYTE *array_out,INT out_len);
    int  F_GetVerEx(int *Version,char *InPath);
    int NT_Cal_New(  BYTE * InBuf,BYTE *OutBuf,char *InPath);
    int NT_SetCal_New(BYTE *InData,BYTE IsHi,char *Path );
    int NT_Set_SM2_KeyPair(BYTE *PriKey,BYTE *PubKeyX,BYTE *PubKeyY,char *sm2UserName,char *Path );
    int NT_Get_SM2_PubKey(BYTE *KGx,BYTE *KGy,char *sm2UserName,char *Path );
    int NT_GenKeyPair(BYTE* PriKey,BYTE *PubKey,char *Path );
    int NT_Set_Pin(char *old_pin,char *new_pin,char *Path );
    int NT_SM2_Enc(BYTE *inbuf,BYTE *outbuf,BYTE inlen,char *Path );
    int NT_SM2_Dec(BYTE *inbuf,BYTE *outbuf,BYTE inlen,char* pin,char *Path );
    int NT_Sign(BYTE *inbuf,BYTE *outbuf,char* pin,char *Path );
    int NT_Sign_2(BYTE *inbuf,BYTE *outbuf,char* pin,char *Path );
    int NT_Verfiy(BYTE *inbuf,BYTE *InSignBuf,BOOL *outbiao,char *Path );
    int  NT_GetChipID(  BYTE *OutChipID,char *InPath);
    int Sub_SetOnly(BOOL IsOnly,BYTE Flag,char *InPath);
    int NT_SetHidOnly(  BOOL IsHidOnly,char *InPath);
    int  NT_SetUReadOnly(char *InPath);
    int NT_SetID(  BYTE * InBuf,char *InPath);
    int Read(BYTE *OutData,short address,BYTE *password,char *Path );
    int Write(BYTE InData,short address,BYTE *password,char *Path );
    int NT_GetProduceDate(  BYTE *OutDate,char *InPath);
    int GetTrashBufLen(char * Path,int *OutLen);
    VOID myconvert(char *hkey,char *lkey,BYTE *out_data);
    DWORD HexToInt(char* s);
    void HexStringToByteArrayEx(char * InString,BYTE *in_data);
    int GetLen(char *InString);
    void SwitchByte2Char(char *outstring,BYTE *inbyte,int inlen);
    void SwitchChar2Byte(char *instring,BYTE *outbyte);
    void SwitchBigInteger2Byte(char *instring,BYTE *outbyte,int *outlen);
    int sFindPort(short pos,char *OutPath);
    int sSetHidOnly(BOOL IsHidOnly,char *KeyPath);
    BOOL Ukey_transfer(HANDLE hDevice,LPVOID lpInBuffer, int inLen,	LPVOID lpOutBuffer,	int OutLen);
    int ReadVerfData(char *InPath);
    int NT_FindU_3(  int start,DWORD in_data,DWORD verf_data,char *OutPath);
    int NT_FindU_2(  int start,DWORD in_data,DWORD verf_data,char *OutPath );
    int NT_IsUReadOnly(BOOL *IsReadOnly,char *InPath);
    int Y_SetCal(BYTE *InData,short address,short len,BYTE *password,char *Path );
private:
    HMODULE hSetApiLib,hHidLib;

};

#endif // SOFTKEY_H
