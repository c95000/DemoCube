#include "SoftKey.h"
#include <QMessageBox>
#include "UKey.h"
#include "KeyDef.h"
#include  <time.h>

#define PID 0X8762
#define VID 0X3689
#define PID_NEW 0X2020
#define VID_NEW 0X3689
#define PID_NEW_2 0X2020
#define VID_NEW_2 0X2020

HDEVINFO  ( _stdcall *l_SetupDiGetClassDevsA)(CONST GUID *,   PCSTR , HWND , IN DWORD  );
BOOL   ( _stdcall *l_SetupDiEnumDeviceInterfaces)(HDEVINFO ,PSP_DEVINFO_DATA ,CONST GUID   *,DWORD,PSP_DEVICE_INTERFACE_DATA);
BOOL  ( _stdcall *l_SetupDiGetDeviceInterfaceDetailA)(HDEVINFO ,PSP_DEVICE_INTERFACE_DATA,PSP_DEVICE_INTERFACE_DETAIL_DATA_A ,    DWORD,PDWORD ,PSP_DEVINFO_DATA  );
BOOL  ( _stdcall *l_SetupDiDestroyDeviceInfoList)(HDEVINFO DeviceInfoSet);

void (_stdcall *l_HidD_GetHidGuid) (LPGUID   HidGuid);
BOOLEAN (_stdcall *l_HidD_SetFeature )(HANDLE   HidDeviceObject,PVOID    ReportBuffer,ULONG    ReportBufferLength);
BOOLEAN (_stdcall *l_HidD_GetFeature )(HANDLE   HidDeviceObject,OUT   PVOID    ReportBuffer,ULONG    ReportBufferLength);
BOOLEAN (_stdcall *l_HidD_GetPreparsedData )(HANDLE  HidDeviceObject,OUT   PHIDP_PREPARSED_DATA  * PreparsedData);
BOOLEAN (_stdcall *l_HidD_GetAttributes) (IN  HANDLE HidDeviceObject,OUT PHIDD_ATTRIBUTES    Attributes);
BOOLEAN (__stdcall *l_HidD_FreePreparsedData )(PHIDP_PREPARSED_DATA PreparsedData);
NTSTATUS (__stdcall *l_HidP_GetCaps) (IN  PHIDP_PREPARSED_DATA  PreparsedData,OUT PHIDP_CAPS Capabilities);

SoftKey::SoftKey()
{
    IsLoad=LoadLib();
}

SoftKey::~SoftKey()
{
    if(hSetApiLib) FreeLibrary(hSetApiLib);
    if(hHidLib) FreeLibrary(hHidLib);
}

int SoftKey::Hanldetransfe(HANDLE hUsbDevice,BYTE *array_in,int InLen,BYTE *array_out,int OutLen,char *InPath)
{
    BOOL IsU=FALSE;
    if(lstrlenA(InPath)>1)
    {
        if(InPath[5]==':')IsU=TRUE;
    }
    if(IsU)
    {
        //注意，这里inlen要加1
        if(!Ukey_transfer(hUsbDevice,array_in,InLen+1,array_out,OutLen)){
            CloseHandle(hUsbDevice);return -93;
        }
    }
    else
    {
        if(InLen>0)if(!SetFeature(hUsbDevice,array_in,InLen)){CloseHandle(hUsbDevice);return -93;}
        if(OutLen>0)if(!GetFeature(hUsbDevice,array_out,OutLen)){CloseHandle(hUsbDevice);return -94;}
    }
    CloseHandle(hUsbDevice);
    return 0;
}

HANDLE SoftKey::MyOpenPath(char *InPath)
{
    BOOL biao;int count=0;
    if(strlen(InPath)<1)
    {
        char OutPath[260];
        biao=isfindmydevice(0,&count,OutPath);
        if(!biao){return INVALID_HANDLE_VALUE;}
        return  CreateFileA(OutPath,GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    }
    else
    {
        return  CreateFileA(InPath,GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    }
}


BOOL  SoftKey::LoadLib()
{
    char SetupApiPath[MAX_PATH*2]="";char HidPath[MAX_PATH*2]="";

    GetSystemDirectoryA(SetupApiPath,MAX_PATH);lstrcatA(SetupApiPath,"\\SetupApi.dll");

    hSetApiLib=LoadLibraryExA(SetupApiPath,NULL,LOAD_WITH_ALTERED_SEARCH_PATH);
    if(hSetApiLib!=NULL)
    {
         l_SetupDiGetClassDevsA=(HDEVINFO ( __stdcall *)(CONST GUID *,   PCSTR , HWND , IN DWORD  ))
                                    GetProcAddress(hSetApiLib,"SetupDiGetClassDevsA");
         l_SetupDiEnumDeviceInterfaces=(BOOL   ( __stdcall *)(HDEVINFO ,PSP_DEVINFO_DATA ,CONST GUID   *,DWORD,PSP_DEVICE_INTERFACE_DATA))
                            GetProcAddress(hSetApiLib,"SetupDiEnumDeviceInterfaces");
         l_SetupDiGetDeviceInterfaceDetailA=(BOOL  ( __stdcall *)(HDEVINFO ,PSP_DEVICE_INTERFACE_DATA,PSP_DEVICE_INTERFACE_DETAIL_DATA_A ,    DWORD,PDWORD ,PSP_DEVINFO_DATA  ))
                            GetProcAddress(hSetApiLib,"SetupDiGetDeviceInterfaceDetailA");
         l_SetupDiDestroyDeviceInfoList=(BOOL  ( __stdcall *)(HDEVINFO DeviceInfoSet))
                        GetProcAddress(hSetApiLib,"SetupDiDestroyDeviceInfoList");

    }
    else
    {
        QMessageBox::warning(NULL, "错误?", "加载SetupApi动态库时错误。", QMessageBox::Close);
        return FALSE;
    }

    GetSystemDirectoryA(HidPath,MAX_PATH);lstrcatA(HidPath,"\\hid.dll");
    hHidLib=LoadLibraryExA(HidPath,NULL,LOAD_WITH_ALTERED_SEARCH_PATH);
    if(hHidLib!=NULL)
    {
        l_HidD_GetHidGuid=(void (__stdcall *) ( LPGUID  ))
                GetProcAddress(hHidLib,"HidD_GetHidGuid");
        l_HidD_SetFeature=(BOOLEAN (__stdcall *)(HANDLE ,PVOID ,ULONG))
                    GetProcAddress(hHidLib,"HidD_SetFeature");
        l_HidD_GetFeature=(BOOLEAN (__stdcall *)( HANDLE ,PVOID  ,ULONG ))
                    GetProcAddress(hHidLib,"HidD_GetFeature");
        l_HidD_GetPreparsedData=(BOOLEAN (__stdcall *)(HANDLE  ,PHIDP_PREPARSED_DATA  * ))
                    GetProcAddress(hHidLib,"HidD_GetPreparsedData");
        l_HidD_GetAttributes=(BOOLEAN (__stdcall *)(HANDLE  ,PHIDD_ATTRIBUTES  ))
                    GetProcAddress(hHidLib,"HidD_GetAttributes");
        l_HidD_FreePreparsedData=(BOOLEAN (__stdcall *)(PHIDP_PREPARSED_DATA ))
                GetProcAddress(hHidLib,"HidD_FreePreparsedData");
        l_HidP_GetCaps=(NTSTATUS (__stdcall *)(PHIDP_PREPARSED_DATA  ,PHIDP_CAPS  ))
                        GetProcAddress(hHidLib,"HidP_GetCaps");
    }
    else
    {
        QMessageBox::warning(NULL, "错误?", "加载hid动态库时错误。", QMessageBox::Close);
        return FALSE;
    }
    return TRUE;
}

BOOL SoftKey::Ukey_transfer(HANDLE hDevice,LPVOID lpInBuffer, int inLen,	LPVOID lpOutBuffer,	int OutLen)
{
    BYTE *dataBuffer=NULL;
    SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER sptdwb;
    ULONG length = 0,returned = 0;
    BOOL status = 0;
    HGLOBAL hglb_1;
    if(inLen>1)
    {

        ZeroMemory(&sptdwb, sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER));
        sptdwb.sptd.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
        //	sptdwb.sptd.PathId = 0;
        sptdwb.sptd.TargetId = 1;
        //	sptdwb.sptd.Lun = 0;
        sptdwb.sptd.CdbLength = 16;
        sptdwb.sptd.SenseInfoLength = 24;
        sptdwb.sptd.DataIn = SCSI_IOCTL_DATA_OUT;
        sptdwb.sptd.DataTransferLength = inLen;
        sptdwb.sptd.TimeOutValue = 100;
        sptdwb.sptd.DataBuffer = lpInBuffer;
        sptdwb.sptd.SenseInfoOffset =
            offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER,ucSenseBuf);
        //CopyMemory(&sptdwb.sptd.Cdb[0],kcw_p,16);

        // CovertBuf(sptdwb.sptd.Cdb);

        sptdwb.sptd.Cdb[0] = 0xdd;
        sptdwb.sptd.Cdb[1] = 0xfe;                         // Data mode
        sptdwb.sptd.Cdb[3] = (BYTE)inLen;
        sptdwb.sptd.Cdb[4] = (BYTE)(inLen>>8);


        length = sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER);
        status = DeviceIoControl(hDevice,
            IOCTL_SCSI_PASS_THROUGH_DIRECT,
            &sptdwb,
            length,
            &sptdwb,
            length,
            &returned,
            FALSE);
        if((sptdwb.sptd.ScsiStatus != 0) || (status == 0) )return FALSE;
    }

    if(OutLen>0)
    {

        //	dataBuffer=new BYTE[kcw_p->dKCWInLength+5];
        hglb_1=GlobalAlloc(GMEM_ZEROINIT|GMEM_MOVEABLE,OutLen);
        dataBuffer=(BYTE *)LocalLock(hglb_1);
        ZeroMemory(&sptdwb, sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER));
        sptdwb.sptd.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
        //	sptdwb.sptd.PathId = 0;
        sptdwb.sptd.TargetId = 1;
        //	sptdwb.sptd.Lun = 0;
        sptdwb.sptd.CdbLength = 16;
        sptdwb.sptd.DataIn = SCSI_IOCTL_DATA_IN;
        sptdwb.sptd.SenseInfoLength = 24;
        sptdwb.sptd.DataTransferLength =OutLen ;
        sptdwb.sptd.TimeOutValue = 100;
        sptdwb.sptd.DataBuffer = dataBuffer;
        sptdwb.sptd.SenseInfoOffset =
            offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER,ucSenseBuf);
        //CopyMemory(&sptdwb.sptd.Cdb[0],kcw_p,16);
        sptdwb.sptd.Cdb[0] = 0xd1;
        sptdwb.sptd.Cdb[1] = 0xfe;
        sptdwb.sptd.Cdb[5] = (BYTE)OutLen;
        sptdwb.sptd.Cdb[6] = (BYTE)(OutLen>>8); // 命令
        length = sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER);
        status = DeviceIoControl(hDevice,
            IOCTL_SCSI_PASS_THROUGH_DIRECT,
            &sptdwb,
            length,
            &sptdwb,
            length,
            &returned,
            FALSE);
        if((sptdwb.sptd.ScsiStatus != 0) || (status == 0) ){GlobalUnlock(hglb_1);LocalFree(hglb_1);return FALSE;}
        CopyMemory(lpOutBuffer,dataBuffer,OutLen);
        GlobalUnlock(hglb_1);LocalFree(hglb_1);
        return TRUE;
    }

    return TRUE;
}


int SoftKey::NT_GetVersion(int *Version,char *InPath)
{
   int ret;
   BYTE array_in[25];BYTE array_out[25];
   HANDLE hUsbDevice=MyOpenPath(InPath);
   if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;
   array_in[1]=GETVERSION;
   ret= Hanldetransfe(hUsbDevice,array_in,1,array_out,1,InPath);
   if(ret!=0)return ret;
   *Version=array_out[0];
   return 0x0;
}

int SoftKey::ReadDword(  DWORD *in_data,char *Path)
{
   BYTE b[4];int result;
   DWORD t[4];
   result= NT_Read(&b[0],&b[1],&b[2],&b[3],Path);
   t[0]=b[0];t[1]=b[1];t[2]=b[2];t[3]=b[3];
   *in_data=t[0]|(t[1]<<8)|(t[2]<<16)|(t[3]<<24);
   return result;
}

int SoftKey::WriteDword(  DWORD *in_data,char *Path)
{
   BYTE b[4];
   b[0]=(BYTE)*in_data;b[1]=(BYTE)(*in_data>>8);
   b[2]=(BYTE)(*in_data>>16);b[3]=(BYTE)(*in_data>>24);
   return NT_Write(&b[0],&b[1],&b[2],&b[3],Path);
}

int SoftKey::WriteDword_2(  DWORD *in_data,char *Path)
{
   BYTE b[4];
   b[0]=(BYTE)*in_data;b[1]=(BYTE)(*in_data>>8);
   b[2]=(BYTE)(*in_data>>16);b[3]=(BYTE)(*in_data>>24);
   return NT_Write_2(&b[0],&b[1],&b[2],&b[3],Path);
}

int SoftKey::NT_Read(  BYTE * ele1,BYTE * ele2,BYTE * ele3,BYTE * ele4,char *Path)
{
   int ret;
   BYTE array_out[25];
   HANDLE hUsbDevice=MyOpenPath(Path);
   if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;
   ret= Hanldetransfe(hUsbDevice,NULL,0,array_out,4,Path);
   if(ret!=0)return ret;
   *ele1=array_out[0];
   *ele2=array_out[1];
   *ele3=array_out[2];
   *ele4=array_out[3];
   return 0;
}

int SoftKey::NT_Write(  BYTE * ele1,BYTE * ele2,BYTE * ele3,BYTE * ele4,char *InPath)
{
   int ret;
   BYTE array_in[25];
   HANDLE hUsbDevice=MyOpenPath(InPath);
   if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;
   array_in[1]=3;array_in[2]=*ele1;array_in[3]=*ele2;array_in[4]=*ele3;array_in[5]=*ele4;//	array_in[1]=*ele1;array_in[2]=*ele2;
   ret= Hanldetransfe(hUsbDevice,array_in,5,NULL,0,InPath);
   return ret;
}


int SoftKey::NT_Write_2(  BYTE * ele1,BYTE * ele2,BYTE * ele3,BYTE * ele4,char *InPath)
{
   int ret;
   BYTE array_in[25];
   HANDLE hUsbDevice=MyOpenPath(InPath);
   if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;
   array_in[1]=4;array_in[2]=*ele1;array_in[3]=*ele2;array_in[4]=*ele3;array_in[5]=*ele4;//	array_in[1]=*ele1;array_in[2]=*ele2;
   ret= Hanldetransfe(hUsbDevice,array_in,5,NULL,0,InPath);
   return ret;
}

int SoftKey::NT_FindPort(  int start,char *OutPath)
{
   int count=0;
   ZeroMemory(OutPath,sizeof(OutPath));
   if(isfindmydevice(start,&count,OutPath))return 0;
   return NotFondKey;
}

int SoftKey::NT_FindPort_2(  int start,DWORD in_data,DWORD verf_data,char *OutPath)
{
   int count=0;
   int pos;DWORD out_data;int ret;
   for(pos=start;pos<127;pos++)
   {
       if(!isfindmydevice(pos,&count,OutPath)){return NotFondKey;}
       ret=WriteDword( &in_data,OutPath);
       if(ret!=0){continue;}
       ret=ReadDword( &out_data,OutPath);
       if(ret!=0){continue;}
       if(out_data==verf_data){return 0;}
   }
   ZeroMemory(OutPath,sizeof(OutPath));
   return NotFondKey;
}

int SoftKey::Read(BYTE *OutData,short address,BYTE *password,char *Path )
{
    BYTE opcode=0x80;
        int ret;
    BYTE array_in[25],array_out[25];int n;
    HANDLE hUsbDevice=MyOpenPath(Path);
    if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;

    if(address>495 || address<0)return ErrAddrOver;
    if(address>255){opcode=0xa0;address=address-256;}

    //array_in[1]要输入的数据长度，array_in[2]要接受的数据长度。array_in[3]指令，
    //array_in[n+3]数据
    array_in[1]=READBYTE;//read 0x10;write 0x11;
    array_in[2]=opcode;//0x01;//read 0x80 ;write 0x40;
    array_in[3]=(BYTE)address;
    for(n=5;n<14;n++)
    {
        array_in[n]=*password;
        password++;
    }
    ret= Hanldetransfe(hUsbDevice,array_in,13,array_out,2,Path);
    if(ret!=0)return ret;
    if(array_out[0]!=0x53 )
    {
        return ErrReadPWD;//表示失败；
    }
    *OutData=array_out[1];
    return 0;
}

 int  SoftKey::Write(BYTE InData,short address,BYTE *password,char *Path )
{
    BYTE opcode=0x40;int ret;

    BYTE array_in[25],array_out[25];int n;
    HANDLE hUsbDevice=MyOpenPath(Path);
    if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;

    if(address>511 || address<0)return ErrAddrOver;
    if(InData<0)return -79;
    if(address>255){opcode=0x60;address=address-256;}

    array_in[1]=WRITEBYTE;//read 0x10;write 0x11;
    array_in[2]=opcode;//0x01;//read 0x80 ;write 0x40;
    array_in[3]=(BYTE)address;
    array_in[4]=InData;
    for(n=5;n<14;n++)
    {
        array_in[n]=*password;
        password++;
    }
    ret= Hanldetransfe(hUsbDevice,array_in,13,array_out,2,Path);
    if(ret!=0)return ret;
    if(array_out[1]!=1 )
    {
        return ErrWritePWD;//表示失败；
    }
    return 0;
}

 int SoftKey::Y_Read(BYTE *OutData,short address ,short len,BYTE *password,char *Path )
{
    short addr_l,addr_h;int n;int ret;

    BYTE array_in[512],array_out[512];
    HANDLE hUsbDevice=MyOpenPath(Path);
    if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;

    if(address>495 || address<0)return ErrAddrOver;
    if( len>255)return -87;
    if(len+address>511)return ErrAddrOver;
    {addr_h=(address>>8)<<1;addr_l=address&0xff;}

    //array_in[1]要输入的数据长度，array_in[2]要接受的数据长度。array_in[3]指令，
    //array_in[n+3]数据
    array_in[1]=YTREADBUF;//read 0x10;write 0x11;
    array_in[2]=(BYTE)addr_h;//0x01;//read 0x80 ;write 0x40;
    array_in[3]=(BYTE)addr_l;
    array_in[4]=(BYTE)len;
    for(n=0;n<8;n++)
    {
        array_in[5+n]=*password;
        password++;
    }
    ret= Hanldetransfe(hUsbDevice,array_in,13,array_out,len+1,Path);
    if(ret!=0)return ret;

    if(array_out[0]!=0x0 )
    {
        return ErrReadPWD;//表示失败；
    }
    for(n=0;n<len;n++)
    {
        *OutData=array_out[n+1];
        OutData++;
    }
    return 0;
}

 int SoftKey::Y_Write(BYTE *InData,short address,short len,BYTE *password,char *Path )
{
    short addr_l,addr_h;int n;int ret;
    BYTE array_in[512],array_out[512];
    HANDLE hUsbDevice=MyOpenPath(Path);
    if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;

    if(len>255)return -87;
    if(address+len-1>511 || address<0)return ErrAddrOver;
    {addr_h=(address>>8)<<1;addr_l=address&0xff;}

    array_in[1]=YTWRITEBUF;//read 0x10;write 0x11;
    array_in[2]=(BYTE)addr_h;//0x01;//read 0x80 ;write 0x40;
    array_in[3]=(BYTE)addr_l;
    array_in[4]=(BYTE )len;
    for(n=0;n<8;n++)
    {
        array_in[5+n]=*password;
        password++;
    }
    for(n=0;n<len;n++)
    {
        array_in[13+n]=*InData;
        InData++;
    }
    ret= Hanldetransfe(hUsbDevice,array_in,13+len,array_out,3,Path);
    if(ret!=0)return ret;

    if(array_out[0]!=0x0)
    {
        return ErrWritePWD;//表示失败；
    }
    return 0;
}

BOOL SoftKey::isfindmydevice( int pos ,int *count,char *OutPath)
{

   HDEVINFO                            hardwareDeviceInfo=NULL;
   SP_INTERFACE_DEVICE_DATA            deviceInfoData;
   ULONG                               i;
   GUID                                hidGuid;
   PSP_INTERFACE_DEVICE_DETAIL_DATA_A    functionClassDeviceData = NULL;
   ULONG                               predictedLength = 0;
   ULONG                               requiredLength = 0;
   HANDLE                              d_handle;
   HIDD_ATTRIBUTES                    Attributes;

   if(!LoadLib())return FALSE;
   *count=0;

   (*l_HidD_GetHidGuid) (&hidGuid);

   hardwareDeviceInfo = (  *l_SetupDiGetClassDevsA ) ( &hidGuid,
                                              NULL, // Define no enumerator (global)
                                              NULL, // Define no
                                              DIGCF_PRESENT | DIGCF_DEVICEINTERFACE); // Function class devices.

  if(hardwareDeviceInfo==INVALID_HANDLE_VALUE)
  {
      return FALSE;
  }
   deviceInfoData.cbSize = sizeof (SP_INTERFACE_DEVICE_DATA);

       for (i=0; (*l_SetupDiEnumDeviceInterfaces) (hardwareDeviceInfo,0,&hidGuid,i,&deviceInfoData); i++)
       {
               if (ERROR_NO_MORE_ITEMS == GetLastError()) break;
               (*l_SetupDiGetDeviceInterfaceDetailA) (hardwareDeviceInfo,&deviceInfoData,NULL,
                       0,&requiredLength,NULL);
               predictedLength = requiredLength;
               functionClassDeviceData =(SP_INTERFACE_DEVICE_DETAIL_DATA_A *) malloc (predictedLength);
               if (functionClassDeviceData)
               {
#ifdef _WIN64
                   functionClassDeviceData->cbSize = sizeof (SP_INTERFACE_DEVICE_DETAIL_DATA_A);
#else
                   functionClassDeviceData->cbSize = 5;
#endif
               }
               else
               {
                   (*l_SetupDiDestroyDeviceInfoList) (hardwareDeviceInfo);
                   return FALSE;
               }

               if (! (*l_SetupDiGetDeviceInterfaceDetailA) (hardwareDeviceInfo,&deviceInfoData,functionClassDeviceData,
                          predictedLength,&requiredLength,NULL))
               {
                   free( functionClassDeviceData);
                   (*l_SetupDiDestroyDeviceInfoList) (hardwareDeviceInfo);
                   return FALSE;
               }
                d_handle = CreateFileA (functionClassDeviceData->DevicePath,  GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL, OPEN_EXISTING, 0,  NULL);
                if (INVALID_HANDLE_VALUE != d_handle)
                {
                    if ((*l_HidD_GetAttributes) (d_handle, &Attributes))
                    {
                        if(((Attributes.ProductID==PID) && (Attributes.VendorID==VID)) ||
                            ((Attributes.ProductID==PID_NEW) && (Attributes.VendorID==VID_NEW)) ||
                               ((Attributes.ProductID==PID_NEW_2) && (Attributes.VendorID==VID_NEW_2)))
                           {
                                   if(pos==*count)
                                   {
                                       lstrcpyA(OutPath,functionClassDeviceData->DevicePath);
                                       free(functionClassDeviceData);
                                       (*l_SetupDiDestroyDeviceInfoList) (hardwareDeviceInfo);
                                        CloseHandle(d_handle);
                                       return TRUE;
                                   }
                                   (*count)++;
                           }
                   }
                    CloseHandle(d_handle);
                }
               free(functionClassDeviceData);
           }
   (*l_SetupDiDestroyDeviceInfoList) (hardwareDeviceInfo);
   return FALSE;

}


BOOL SoftKey::SetFeature (HANDLE hDevice,BYTE *array_in,INT in_len)
/*++
RoutineDescription:
Given a struct _HID_DEVICE, take the information in the HID_DATA array
pack it into multiple reports and send it to the hid device via HidD_SetFeature()
--*/
{

   PHIDP_PREPARSED_DATA Ppd;
   HIDP_CAPS            Caps;
    BOOLEAN   Status;
   BOOLEAN   FeatureStatus;
   DWORD     ErrorCode;
   INT		  i;
   BYTE FeatureReportBuffer[512];

   if (!(*l_HidD_GetPreparsedData) (hDevice, &Ppd)) return FALSE;

   if (!(*l_HidP_GetCaps) (Ppd, &Caps))
   {
           (*l_HidD_FreePreparsedData)(Ppd);
           return FALSE;
   }

   Status = TRUE;

   FeatureReportBuffer[0]=0x02;

   array_in++;
   for(i=1;i<=in_len;i++)
   {
       FeatureReportBuffer[i]=*array_in;
       array_in++;
   }
   FeatureStatus =((*l_HidD_SetFeature)(hDevice,
                                 FeatureReportBuffer,
                                 Caps.FeatureReportByteLength));

   ErrorCode = GetLastError();

   Status = Status && FeatureStatus;
   (*l_HidD_FreePreparsedData)(Ppd);
   return (Status);
}

BOOL SoftKey::GetFeature (HANDLE hDevice,BYTE *array_out,INT out_len)
/*++
RoutineDescription:
  Given a struct _HID_DEVICE, fill in the feature data structures with
  all features on the device.  May issue multiple HidD_GetFeature() calls to
  deal with multiple report IDs.
--*/
{
  // ULONG     Index;
   BOOLEAN   FeatureStatus;
   BOOLEAN   Status;
   INT		  i;
   BYTE      FeatureReportBuffer[512];
   PHIDP_PREPARSED_DATA Ppd;
   HIDP_CAPS            Caps;
   if (!(*l_HidD_GetPreparsedData) (hDevice, &Ppd)) return FALSE;

   if (!(*l_HidP_GetCaps) (Ppd, &Caps))
   {
           (*l_HidD_FreePreparsedData)(Ppd);
           return FALSE;
   }
   /*
   // As with writing data, the IsDataSet value in all the structures should be
   //    set to FALSE to indicate that the value has yet to have been set
   */
   Status = TRUE;

   memset(FeatureReportBuffer, 0x00, 512);

   FeatureReportBuffer[0] = 0x01;

   FeatureStatus = (*l_HidD_GetFeature) (hDevice,
                                     FeatureReportBuffer,
                                     Caps.FeatureReportByteLength);
   if (FeatureStatus)
   {

       if(FeatureStatus)
       {
           for(i=0;i<out_len;i++)
           {
               *array_out=FeatureReportBuffer[i];
               array_out++;
           }
       }
   }

   Status = Status && FeatureStatus;
   (*l_HidD_FreePreparsedData)(Ppd);

  return (Status);
}


int SoftKey::NT_GetID(  DWORD *ID_1,DWORD *ID_2,char *InPath)
{
       DWORD t[8];int ret;
   BYTE array_in[25];BYTE array_out[25];
   HANDLE hUsbDevice=MyOpenPath(InPath);
   if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;
   array_in[1]=GETID;
   ret= Hanldetransfe(hUsbDevice,array_in,1,array_out,8,InPath);
   if(ret!=0)return ret;
   t[0]=array_out[0];t[1]=array_out[1];t[2]=array_out[2];t[3]=array_out[3];
   t[4]=array_out[4];t[5]=array_out[5];t[6]=array_out[6];t[7]=array_out[7];
   *ID_1=t[3]|(t[2]<<8)|(t[1]<<16)|(t[0]<<24);
   *ID_2=t[7]|(t[6]<<8)|(t[5]<<16)|(t[4]<<24);
   return 0;
}

int SoftKey::NT_Cal(  BYTE * InBuf,BYTE *OutBuf,char *InPath)
{
   int n;int ret;
   BYTE array_in[25];BYTE array_out[25];
   HANDLE hUsbDevice=MyOpenPath(InPath);
   if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;
   array_in[1]=CAL_TEA;
   for (n=2;n<10;n++)
   {
       array_in[n]=InBuf[n-2];
   }
   ret= Hanldetransfe(hUsbDevice,array_in,9,array_out,10,InPath);
   if(ret!=0)return ret;
   memcpy(OutBuf,array_out,8);
   if(array_out[8]!=0x55)
   {
       return ErrResult;
   }
   return 0;
}

int SoftKey::NT_SetCal_2(BYTE *InData,BYTE IsHi,char *Path )
{
      int n;int ret;
      BYTE array_in[30],array_out[25];
      BYTE opcode=SET_TEAKEY;
      HANDLE hUsbDevice=MyOpenPath(Path);
      if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;

      array_in[1]=opcode;
      array_in[2]=IsHi;
      for(n=0;n<8;n++)
      {
          array_in[3+n]=*InData;
          InData++;
      }
      ret= Hanldetransfe(hUsbDevice,array_in,11,array_out,3,Path);
      if(ret!=0)return ret;
      if(array_out[0]!=0x0)
      {
          return ErrResult;//表示失败；
      }
      return 0;
}

int SoftKey::NT_ReSet(char *Path )
{

       int ret;
      BYTE array_in[30],array_out[25];
      HANDLE hUsbDevice=MyOpenPath(Path);
      if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;
      array_in[1]=MYRESET;
      ret= Hanldetransfe(hUsbDevice,array_in,2,array_out,1,Path);
      if(ret!=0)return ret;
      if(ret!=0)return ret;
      if(array_out[0]!=0x0)
      {
          return ErrResult;//表示失败；
      }
      return 0;
}

int SoftKey::NT_SetID(  BYTE * InBuf,char *InPath)
{
  int n,ret;
  BYTE array_in[25];BYTE array_out[25];
  HANDLE hUsbDevice=MyOpenPath(InPath);
  if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;
  array_in[1]=SETID;
  for (n=2;n<10;n++)
  {
      array_in[n]=InBuf[n-2];
  }
  ret=Hanldetransfe(hUsbDevice,array_in,9,array_out,1,InPath);
  if(ret!=0)return ret;
  if(array_out[0]!=0x0)
  {
       return ErrResult;//表示失败；
  }
  return 0;
}

int  SoftKey::NT_GetProduceDate(  BYTE *OutDate,char *InPath)
{
       int ret;
    BYTE array_in[25];
    HANDLE hUsbDevice=MyOpenPath(InPath);
    if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;
    array_in[1]=GETSN;
    ret= Hanldetransfe(hUsbDevice,array_in,1,OutDate,8,InPath);
    return ret;
}

int  SoftKey::F_GetVerEx(int *Version,char *InPath)
{
       int ret;
   BYTE array_in[25];BYTE array_out[25];
   HANDLE hUsbDevice=MyOpenPath(InPath);
   if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;

   array_in[1]=GETVEREX;
   ret= Hanldetransfe(hUsbDevice,array_in,1,array_out,1,InPath);
   if(ret!=0)return ret;
   *Version=array_out[0];
   return 0x0;
}


int SoftKey::NT_Cal_New(  BYTE * InBuf,BYTE *OutBuf,char *InPath)
{
   int n,ret;
   BYTE array_in[25];BYTE array_out[25];
   HANDLE hUsbDevice=MyOpenPath(InPath);
   if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;

   array_in[1]=CAL_TEA_2;
   for (n=2;n<10;n++)
   {
       array_in[n]=InBuf[n-2];
   }
   ret= Hanldetransfe(hUsbDevice,array_in,9,array_out,10,InPath);
   if(ret!=0)return ret;
   memcpy(OutBuf,array_out,8);
   if(array_out[8]!=0x55)
   {
       return ErrResult;
   }

   return 0;
}

int SoftKey::NT_SetCal_New(BYTE *InData,BYTE IsHi,char *Path )
{
    int n,ret;
    BYTE array_in[30],array_out[25];
    BYTE opcode=SET_TEAKEY_2;
    HANDLE hUsbDevice=MyOpenPath(Path);
    if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;

    array_in[1]=opcode;
    array_in[2]=IsHi;
    for(n=0;n<8;n++)
    {
      array_in[3+n]=*InData;
      InData++;
    }
    ret= Hanldetransfe(hUsbDevice,array_in,11,array_out,3,Path);
    if(ret!=0)return ret;
    if(array_out[0]!=0x0)
    {
        return ErrResult;//表示失败；
    }
    return 0;
}

int SoftKey::NT_Set_SM2_KeyPair(BYTE *PriKey,BYTE *PubKeyX,BYTE *PubKeyY,char *sm2UserName,char *Path )
{

      int ret;
      BYTE array_in[256],array_out[25];

      HANDLE hUsbDevice=MyOpenPath(Path);
      if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;
      memset(array_in,0,256);

      array_in[1]=SET_ECC_KEY;
      memcpy(&array_in[2+ECC_MAXLEN*0],PriKey,ECC_MAXLEN);
      memcpy(&array_in[2+ECC_MAXLEN*1],PubKeyX,ECC_MAXLEN);
      memcpy(&array_in[2+ECC_MAXLEN*2],PubKeyY,ECC_MAXLEN);
      if(sm2UserName!=0)
      {
          memcpy(&array_in[2+ECC_MAXLEN*3],sm2UserName,USERID_LEN);
      }
      ret= Hanldetransfe(hUsbDevice,array_in,ECC_MAXLEN*3+2+USERID_LEN,array_out,1,Path);
      if(ret!=0)return ret;
      if(array_out[0]!=0x20)return USBStatusFail;

      return 0;
}

int SoftKey::NT_Get_SM2_PubKey(BYTE *KGx,BYTE *KGy,char *sm2UserName,char *Path )
{

      int ret;
      BYTE array_in[256],array_out[256];
      HANDLE hUsbDevice=MyOpenPath(Path);
      array_out[0]=0xfb;
      if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;

      array_in[1]=GET_ECC_KEY;
      ret= Hanldetransfe(hUsbDevice,array_in,2,array_out,ECC_MAXLEN*2+2+USERID_LEN,Path);
      if(ret!=0)return ret;

      if(array_out[0]!=0x20)return USBStatusFail;
      memcpy(KGx,&array_out[1+ECC_MAXLEN*0],ECC_MAXLEN);
      memcpy(KGy,&array_out[1+ECC_MAXLEN*1],ECC_MAXLEN);
      memcpy(sm2UserName,&array_out[1+ECC_MAXLEN*2],USERID_LEN);

      return 0;
}


int SoftKey::NT_GenKeyPair(BYTE* PriKey,BYTE *PubKey,char *Path )
{

      int ret;
      BYTE array_in[256],array_out[256];
      HANDLE hUsbDevice=MyOpenPath(Path);
      array_out[0]=0xfb;
      if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;

      array_in[1]=GEN_KEYPAIR;
      ret= Hanldetransfe(hUsbDevice,array_in,2,array_out,ECC_MAXLEN*3+2,Path);
      if(ret!=0)return ret;

      if(array_out[0]!=0x20)
      {
          return FAILEDGENKEYPAIR;//表示读取失败；
      }
      memcpy(PriKey,&array_out[1+ECC_MAXLEN*0],ECC_MAXLEN);
      memcpy(PubKey,&array_out[1+ECC_MAXLEN*1],ECC_MAXLEN*2+1);
      return 0;
}

int SoftKey::NT_Set_Pin(char *old_pin,char *new_pin,char *Path )
{

      int ret;
      BYTE array_in[256],array_out[25];
      HANDLE hUsbDevice=MyOpenPath(Path);
      if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;

      array_in[1]=SET_PIN;
      memcpy(&array_in[2+PIN_LEN*0],old_pin,PIN_LEN);
      memcpy(&array_in[2+PIN_LEN*1],new_pin,PIN_LEN);

      ret= Hanldetransfe(hUsbDevice,array_in,PIN_LEN*2+2,array_out,2,Path);
      if(ret!=0)return ret;

      if(array_out[0]!=0x20)return USBStatusFail;
      if(array_out[1]!=0x20)return FAILPINPWD;
      return 0;
}


int SoftKey::NT_SM2_Enc(BYTE *inbuf,BYTE *outbuf,BYTE inlen,char *Path )
{

      int n;int ret;
      BYTE array_in[256],array_out[256];

      HANDLE hUsbDevice=MyOpenPath(Path);
      if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;

      array_out[0]=0xfb;
      array_in[1]=MYENC;
      array_in[2]=inlen;
      for(n=0;n<inlen;n++)
      {
        array_in[3+n]=inbuf[n];
      }
      ret= Hanldetransfe(hUsbDevice,array_in,inlen+1+2,array_out,inlen+SM2_ADDBYTE+3,Path);
      if(ret!=0)return ret;

      if(array_out[0]!=0x20)return USBStatusFail;
      if(array_out[1]==0)return FAILENC;

      memcpy(outbuf,&array_out[2],inlen+SM2_ADDBYTE);

      return 0;
}

int SoftKey::NT_SM2_Dec(BYTE *inbuf,BYTE *outbuf,BYTE inlen,char* pin,char *Path )
{

      int n;int ret;
      BYTE array_in[256],array_out[256];

      HANDLE hUsbDevice=MyOpenPath(Path);
      if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;

      array_out[0]=0xfb;
      array_in[1]=MYDEC;
      memcpy(&array_in[2],pin,PIN_LEN);
      array_in[2+PIN_LEN]=inlen;
      for(n=0;n<inlen;n++)
      {
        array_in[2+PIN_LEN+1+n]=inbuf[n];
      }
      ret= Hanldetransfe(hUsbDevice,array_in,inlen+1+2+PIN_LEN,array_out,inlen-SM2_ADDBYTE+4,Path);
      if(ret!=0)return ret;

      if(array_out[2]!=0x20)return FAILPINPWD;
      if(array_out[1]==0) return FAILENC;
      if(array_out[0]!=0x20)return USBStatusFail;
      memcpy(outbuf,&array_out[3],inlen-SM2_ADDBYTE);

      return 0;
}

int SoftKey::NT_Sign(BYTE *inbuf,BYTE *outbuf,char* pin,char *Path )
{

      int n;int ret;
      BYTE array_in[256],array_out[256];
      HANDLE hUsbDevice=MyOpenPath(Path);
      if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;

      array_out[0]=0xfb;
      array_in[1]=YTSIGN;
      memcpy(&array_in[2],pin,PIN_LEN);
      for(n=0;n<32;n++)
      {
        array_in[2+PIN_LEN+n]=inbuf[n];
      }
      ret= Hanldetransfe(hUsbDevice,array_in,32+2+PIN_LEN,array_out,64+2,Path);
      if(ret!=0)return ret;

      if(array_out[1]!=0x20)return FAILPINPWD;
      if(array_out[0]!=0x20)return USBStatusFail;
      memcpy(outbuf,&array_out[2],64);

      return 0;
}

int SoftKey::NT_Sign_2(BYTE *inbuf,BYTE *outbuf,char* pin,char *Path )
{

      int n;int ret;
      BYTE array_in[256],array_out[256];
      HANDLE hUsbDevice=MyOpenPath(Path);
      if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;

      array_out[0]=0xfb;
      array_in[1]=YTSIGN_2;
      memcpy(&array_in[2],pin,PIN_LEN);
      for(n=0;n<32;n++)
      {
        array_in[2+PIN_LEN+n]=inbuf[n];
      }
      ret= Hanldetransfe(hUsbDevice,array_in,32+2+PIN_LEN,array_out,64+2,Path);
      if(ret!=0)return ret;
      if(array_out[1]!=0x20)return FAILPINPWD;
      if(array_out[0]!=0x20)return USBStatusFail;
      memcpy(outbuf,&array_out[2],64);

      return 0;
}

int SoftKey::NT_Verfiy(BYTE *inbuf,BYTE *InSignBuf,BOOL *outbiao,char *Path )
{

      int n;int ret;
      BYTE array_in[256],array_out[256];
      HANDLE hUsbDevice=MyOpenPath(Path);
      if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;

      array_out[0]=0xfb;
      array_in[1]=YTVERIFY;
      for(n=0;n<32;n++)
      {
        array_in[2+n]=inbuf[n];
      }
      for(n=0;n<64;n++)
      {
        array_in[2+32+n]=InSignBuf[n];
      }
      ret= Hanldetransfe(hUsbDevice,array_in,32+2+64,array_out,3,Path);
      if(ret!=0)return ret;
      *outbiao=array_out[1];
      if(array_out[0]!=0x20)return USBStatusFail;

      return 0;
}

int  SoftKey::NT_GetChipID(  BYTE *OutChipID,char *InPath)
{
   int ret;
   BYTE array_in[25];BYTE array_out[25];
   HANDLE hUsbDevice=MyOpenPath(InPath);
   if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;
   array_in[1]=GET_CHIPID;
   ret= Hanldetransfe(hUsbDevice,array_in,1,array_out,17,InPath);
   if(ret!=0)return ret;
   if(array_out[0]!=0x20)return USBStatusFail;
   memcpy(OutChipID,&array_out[1],16);

   return 0;
}

int SoftKey::Sub_SetOnly(BOOL IsOnly,BYTE Flag,char *InPath)
{
   int ret;
   BYTE array_in[25];BYTE array_out[25];
   HANDLE hUsbDevice=MyOpenPath(InPath);
   if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;
   array_in[1]=Flag;
   if(IsOnly)array_in[2]=0;else array_in[2]=0xff;
   ret=Hanldetransfe(hUsbDevice,array_in,3,array_out,1,InPath);
   if(ret!=0)return ret;
   if(array_out[0]!=0x0)
   {
       return ErrResult;//表示失败；
   }
   return 0;
}

int SoftKey::NT_SetHidOnly(  BOOL IsHidOnly,char *InPath)
{
   return Sub_SetOnly(IsHidOnly,SETHIDONLY,InPath);
}

int  SoftKey::NT_SetUReadOnly(char *InPath)
{
   return Sub_SetOnly(TRUE,SETREADONLY,InPath);
}

int SoftKey::GetTrashBufLen(char * Path,int *OutLen)
{
   PHIDP_PREPARSED_DATA Ppd;
   HIDP_CAPS            Caps;
   HANDLE hUsbDevice=MyOpenPath(Path);
   if(hUsbDevice == INVALID_HANDLE_VALUE)return NotFondKey;
   if (!(*l_HidD_GetPreparsedData) (hUsbDevice, &Ppd)) return ErrSendData;
   if (!(*l_HidP_GetCaps) (Ppd, &Caps))
   {
       (*l_HidD_FreePreparsedData)(Ppd);
       return ErrSendData;
   }
   CloseHandle(hUsbDevice);
   *OutLen=Caps.FeatureReportByteLength-5;
    (*l_HidD_FreePreparsedData)(Ppd);
   return 0;
}

int SoftKey::NT_GetIDVersion(int *Version,char *InPath)
{
    int ret;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(NT_GetVersion)(Version,InPath);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;
}

int SoftKey::GetID(  DWORD *ID_1,DWORD *ID_2,char *InPath)
{
    int ret;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(NT_GetID)(ID_1,ID_2,InPath);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;
}

int SoftKey::sRead(  DWORD *in_data,char *Path)
{
    int ret;
    //////////////////////////////////////////////////////////////////////////////////

    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(ReadDword)(in_data,Path);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;
}

int SoftKey::sWrite(  DWORD out_data,char *Path)
{
    int ret;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(WriteDword)(&out_data,Path);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;
}

int SoftKey::YWrite(BYTE InData,short address,char * HKey,char *LKey,char *Path )
{
    if(address>495){return  -81;}
    BYTE ary1[8];
    myconvert(HKey,LKey,ary1);
    int ret;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(Write)(InData,address,ary1,Path);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;
}

 int SoftKey::YRead(BYTE *OutData,short address,char * HKey,char *LKey,char *Path )
{
    if(address>495){return  -81;}
    BYTE ary1[8];
    myconvert(HKey,LKey,ary1);
    int ret;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(Read)(OutData,address,ary1,Path);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;
}

int SoftKey::YWriteEx(BYTE *InData,short Address,short len,char *HKey,char *LKey,char *Path )
{
    int ret;BYTE password[8];int n,trashLen;int temp_leave, leave; HANDLE hsignal;
     if(Address+len-1>495 || Address<0)return -81;

     ret=GetTrashBufLen(Path,&trashLen);
     trashLen=trashLen-8;
     if(ret!=0)return ret;

     myconvert(HKey,LKey,password);

     hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");

     WaitForSingleObject(hsignal,INFINITE);
     temp_leave=Address-Address/trashLen*trashLen; leave=trashLen-temp_leave;
     if(leave>len){leave=len;}
     if(leave>0)
     {
         for(n=0;n<leave/trashLen;n++)
         {
             ret=(Y_Write)(InData+n*trashLen,Address+n*trashLen,trashLen,password,Path);
             if(ret!=0){ReleaseSemaphore(hsignal,1,NULL);CloseHandle(hsignal);return  ret;}
         }
         if(leave-trashLen*n>0)
         {
             ret=(Y_Write)(InData+n*trashLen,Address+n*trashLen,(BYTE)(leave-n*trashLen),password,Path);
             if(ret!=0){ReleaseSemaphore(hsignal,1,NULL);CloseHandle(hsignal);return  ret;}

         }
     }
     len=len-leave;Address=Address+leave;InData=InData+leave;
     if (len>0)
     {
         for(n=0;n<len/trashLen;n++)
         {
             ret=(Y_Write)(InData+n*trashLen,Address+n*trashLen,trashLen,password,Path);
             if(ret!=0){ReleaseSemaphore(hsignal,1,NULL);CloseHandle(hsignal);return ret;}
         }
         if(len-trashLen*n>0)
         {
             ret=(Y_Write)(InData+n*trashLen,Address+n*trashLen,(BYTE)(len-n*trashLen),password,Path);
             if(ret!=0){ReleaseSemaphore(hsignal,1,NULL);CloseHandle(hsignal);return ret;}

         }
     }
     ReleaseSemaphore(hsignal,1,NULL);
     CloseHandle(hsignal);
     return ret;
}

int SoftKey::YReadEx(BYTE *OutData,short Address,short len,char *HKey,char *LKey,char *Path )
{
    int ret;BYTE password[8];int n,trashLen; HANDLE hsignal;
    if(Address+len-1>495 || Address<0)return -81;

    ret=GetTrashBufLen(Path,&trashLen);
    if(ret!=0)return ret;

   myconvert(HKey,LKey,password);

    hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    for(n=0;n<len/trashLen;n++)
    {
        ret=(Y_Read)(OutData+n*trashLen,Address+n*trashLen,trashLen,password,Path);
        if(ret!=0){ReleaseSemaphore(hsignal,1,NULL);CloseHandle(hsignal);return ret;}
    }
    if(len-trashLen*n>0)
    {
        ret=(Y_Read)(OutData+n*trashLen,Address+n*trashLen,(len-trashLen*n),password,Path);
        if(ret!=0){ReleaseSemaphore(hsignal,1,NULL);CloseHandle(hsignal);return ret;}

    }
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;
}

int SoftKey::FindPort_2(  int start,DWORD in_data,DWORD verf_data,char *OutPath)
{
    int ret;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(NT_FindPort_2)(start,in_data,verf_data,OutPath);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;
}

int SoftKey::FindPort(  int start,char *OutPath)
{
    int ret;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(NT_FindPort)(start,OutPath);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;
}

int SoftKey::sWrite_2(  DWORD out_data,char *Path)
{
    int ret;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(WriteDword_2)(&out_data,Path);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;
}

VOID SoftKey::myconvert(char *hkey,char *lkey,BYTE *out_data)
{
    DWORD z,z1;int n;
    z=HexToInt(hkey);
    z1=HexToInt(lkey);
    for(n=0;n<=3;n++)
    {
        *out_data=(BYTE)((z<<(n*8))>>24);
        out_data++;
    }
    for(n=0;n<=3;n++)
    {
        *out_data=(BYTE)((z1<<(n*8))>>24);
        out_data++;
    }
}

DWORD SoftKey::HexToInt(char* s)
{
    char hexch[] = "0123456789ABCDEF";
    size_t i;
   DWORD r,n,k,j;
   char ch;

    k=1; r=0;
    for (i=strlen(s);  i>0; i--) {
    ch = s[i-1]; if (ch > 0x3f) ch &= 0xDF;
    n = 0;
        for (j = 0; j<16; j++)
        if (ch == hexch[j])
            n = j;
        r += (n*k);
        k *= 16;
    }
    return r;
}

int SoftKey::SetReadPassword(char * W_HKey,char *W_LKey,char * new_HKey,char *new_LKey,char *InPath)
{

    BYTE ary1[8];BYTE ary2[8];
    myconvert(W_HKey,W_LKey,ary1);
    myconvert(new_HKey,new_LKey,ary2);
    int ret;int address=0x1f0;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(Y_Write)(ary2,address,8,ary1,InPath);
    if(ret!=0){ReleaseSemaphore(hsignal,1,NULL);return ret;}
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;

}


int SoftKey::SetWritePassword(char * W_HKey,char *W_LKey,char * new_HKey,char *new_LKey,char *InPath)
{
    BYTE ary1[8];BYTE ary2[8];
    myconvert(W_HKey,W_LKey,ary1);
    myconvert(new_HKey,new_LKey,ary2);
    int ret;int address=0x1f8;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(Y_Write)(ary2,address,8,ary1,InPath);
    if(ret!=0){ReleaseSemaphore(hsignal,1,NULL);return ret;}
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;

}

int SoftKey::YWriteString(char *InString,short Address,char * HKey,char *LKey,char *Path )
{
    BYTE ary1[8];int n,trashLen;int ret=0,outlen,total_len;HANDLE hsignal;//int versionex;

    ret=GetTrashBufLen(Path,&trashLen);
    trashLen=trashLen-8;
    if(ret!=0)return ret;

    myconvert(HKey,LKey,ary1);

    outlen=lstrlenA(InString);
    total_len=Address+outlen;
    if(total_len>495){return -47;}

    hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    {
        WaitForSingleObject(hsignal,INFINITE);
        for(n=0;n<outlen/trashLen;n++)
        {
            ret=(Y_Write)((BYTE *)(InString+n*trashLen),Address+n*trashLen,trashLen,ary1,Path);
            if(ret!=0){ReleaseSemaphore(hsignal,1,NULL);CloseHandle(hsignal);return  ret;}
        }
        if(outlen-trashLen*n>0)
        {
            ret=(Y_Write)((BYTE *)(InString+n*trashLen),Address+n*trashLen,(BYTE)(outlen-n*trashLen),ary1,Path);
            if(ret!=0){ReleaseSemaphore(hsignal,1,NULL);CloseHandle(hsignal);return  ret;}

        }
        ReleaseSemaphore(hsignal,1,NULL);
    }
    CloseHandle(hsignal);
    return ret;
}

int SoftKey::YReadString(char *string ,short Address,int len,char * HKey,char *LKey,char *Path )
{
    BYTE ary1[8];int n,trashLen;int ret=0;HANDLE hsignal;int total_len;//DWORD z,z1;int versionex;

        ret=GetTrashBufLen(Path,&trashLen);
        if(ret!=0)return ret;

        myconvert(HKey,LKey,ary1);

        total_len=Address+len;
        if(total_len>495){return -47;}

        hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
        {
            WaitForSingleObject(hsignal,INFINITE);
            for(n=0;n<len/trashLen;n++)
            {
                ret=(Y_Read)((BYTE*)(string+n*trashLen),Address+n*trashLen,trashLen,ary1,Path);
                if(ret!=0)
                {
                    ReleaseSemaphore(hsignal,1,NULL);CloseHandle(hsignal);
                    return ret;
                }
            }
            if(len-trashLen*n>0)
            {
                ret=(Y_Read)((BYTE*)(string+n*trashLen),Address+n*trashLen,(len-trashLen*n),ary1,Path);
                if(ret!=0)
                {
                    ReleaseSemaphore(hsignal,1,NULL);CloseHandle(hsignal);
                    return ret;
                }

            }
            ReleaseSemaphore(hsignal,1,NULL);
        }
        CloseHandle(hsignal);
        return ret;
}

 void SoftKey::ByteArrayToHexString(BYTE *in_data,char * OutString,int len)
{
    memset(OutString,0,len*2);
    char temp[5];int n;
    for (n=1;n<=len;n++)
    {
        wsprintfA(temp,"%02X",*in_data);
        in_data++;
        lstrcatA(OutString,temp);
    }
}

 VOID SoftKey::HexStringToByteArray(char * InString,BYTE *in_data)
{
    int len=lstrlenA(InString);
    char temp[5];int n;
    for (n=1;n<=len;n=n+2)
    {
        ZeroMemory(temp,sizeof(temp));
        lstrcpynA(temp,&InString[n-1],2+1);
        *in_data=(BYTE)HexToInt(temp);
        in_data++;
    }
}

 void SoftKey::HexStringToByteArrayEx(char * InString,BYTE *in_data)
{
    int len=lstrlenA(InString);
    char temp[5];int n;
    if(len>32)len=32;
    for (n=1;n<=len;n=n+2)
    {
        ZeroMemory(temp,sizeof(temp));
        lstrcpynA(temp,&InString[n-1],2+1);
        *in_data=(BYTE)HexToInt(temp);
        in_data++;
    }

}

int SoftKey::SetCal_2(char *Key,char *InPath)
{
    BYTE KeyBuf[16];
    memset(KeyBuf,0,16);
    HexStringToByteArrayEx(Key,KeyBuf);
    //注意，这里是地址互换的
    int ret;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(NT_SetCal_2)(&KeyBuf[8],0,InPath);
    if(ret!=0)goto error1;
    ret=(NT_SetCal_2)(&KeyBuf[0],1,InPath);
error1:
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;

}

int SoftKey::Cal(  BYTE *InBuf,BYTE *OutBuf,char *Path)
{
    int ret;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=NT_Cal(InBuf,OutBuf,Path);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;
}

int SoftKey::GetLen(char *InString)
{
    return lstrlenA(InString)+1;
}

int SoftKey::EncString(  char *InString,char *OutString,char *Path)
{

    int ret;int n;BYTE *outbuf;
    int len=lstrlenA(InString)+1;if(len<8)len=8;
    outbuf=new BYTE[len];
    memset(outbuf,0,len);
    memcpy(outbuf,InString,lstrlenA(InString)+1);
    for(n=0;n<=(len-8);n=n+8)
    {
        ret=Cal((BYTE *)&outbuf[n],&outbuf[n],Path);
        if(ret!=0){delete [] outbuf;return ret;}
    }
    ByteArrayToHexString(outbuf,OutString,len);
    delete [] outbuf;
    return ret;
}

void SoftKey:: EncBySoft(   BYTE  *   aData,  BYTE   *   aKey   )
{
    const   unsigned   long   cnDelta   =   0x9E3779B9;
    register   unsigned   long   y   =   (   (   unsigned   long   *   )aData   )[0],   z   =   (   (   unsigned   long   *   )aData   )[1];
    register   unsigned   long   sum   =   0;
    unsigned   long   a   =   (   (   unsigned   long   *   )aKey   )[0],   b   =   (   (   unsigned   long   *   )aKey   )[1];
    unsigned   long   c   =   (   (   unsigned   long   *   )aKey   )[2],   d   =   (   (   unsigned   long   *   )aKey   )[3];
    int   n   =   32;

    while   (   n--   >   0   )
    {
        sum   +=   cnDelta;
        y   +=   ((   z   <<   4   )   +   a )  ^   (z   +   sum )  ^  ( (   z   >>   5   )   +   b);

        z   +=   ((   y   <<   4   )   +   c )  ^   (y   +   sum )  ^  ( (   y   >>   5   )   +   d);
    }
    (   (   unsigned   long   *   )aData   )[0]   =   y;
    (   (   unsigned   long   *   )aData   )[1]   =   z;
}

void SoftKey:: DecBySoft(    BYTE  *   aData,   BYTE   *   aKey   )
{
    const   unsigned   long   cnDelta   =   0x9E3779B9;
    register   unsigned   long   y   =   (   (   unsigned   long   *   )aData   )[0],   z   =   (   (   unsigned   long   *   )aData   )[1];
    register   unsigned   long   sum   =   0xC6EF3720;
    unsigned   long   a   =   (   (   unsigned   long   *   )aKey   )[0],   b   =   (   (   unsigned   long   *   )aKey   )[1];
    unsigned   long   c   =   (   (   unsigned   long   *   )aKey   )[2],   d   =   (   (   unsigned   long   *   )aKey   )[3];
    int   n   =   32;
    while   (   n--   >   0   )
    {
        z   -=  ( (   y   <<   4   )   +   c )  ^  ( y   +   sum  ) ^ (  (   y   >>   5   )   +   d);
        y   -=  ( (   z   <<   4   )   +   a )  ^  ( z   +   sum  ) ^ (  (   z   >>   5   )   +   b);
        sum   -=   cnDelta;
    }
    (   (   unsigned   long   *   )aData   )[0]   =   y;
    (   (   unsigned   long   *   )aData   )[1]   =   z;
}

int SoftKey::sWriteEx(  DWORD in_data,DWORD *out_data,char *Path)
{
    int ret;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(WriteDword)(&in_data,Path);
    if(ret!=0)goto error1;
    ret=(ReadDword)(out_data,Path);
error1:
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;
}

int SoftKey::sWrite_2Ex(  DWORD in_data,DWORD *out_data,char *Path)
{
    int ret;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(WriteDword_2)(&in_data,Path);
    if(ret!=0)goto error1;
    ret=(ReadDword)(out_data,Path);
error1:
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;
}

int SoftKey::ReSet(char *InPath)
{

    int ret;int Version;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(NT_GetVersion)(&Version,InPath);
    if(ret!=0)goto finish;
    ret=(NT_ReSet)(InPath);
    if(ret!=0)goto finish;
    ret=(NT_ReSet)(InPath);
    if(ret!=0)goto finish;
    ret=(NT_ReSet)(InPath);
    if(ret!=0)goto finish;
    ret=(NT_ReSet)(InPath);
finish:
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;

}

 int SoftKey::NT_GetVersionEx(int *version,char *InPath )
{
    int ret;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(F_GetVerEx)(version,InPath);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;
}

int SoftKey::SetCal_New(char *Key,char *InPath)
{
    BYTE KeyBuf[16];
    memset(KeyBuf,0,16);
    HexStringToByteArrayEx(Key,KeyBuf);
    //注意，这里是地址互换的
    int ret;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(NT_SetCal_New)(&KeyBuf[8],0,InPath);
    if(ret!=0)goto error1;
    ret=(NT_SetCal_New)(&KeyBuf[0],1,InPath);
error1:
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;

}

int SoftKey::Cal_New(  BYTE *InBuf,BYTE *OutBuf,char *Path)
{
    int ret;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=NT_Cal_New(InBuf,OutBuf,Path);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;
}

int SoftKey::EncString_New(  char *InString,char *OutString,char *Path)
{

    int ret;int n;BYTE *outbuf;
    int len=lstrlenA(InString)+1;if(len<8)len=8;
    outbuf=new BYTE[len];
    memset(outbuf,0,len);
    memcpy(outbuf,InString,lstrlenA(InString)+1);
    for(n=0;n<=(len-8);n=n+8)
    {
        ret=Cal_New((BYTE *)&outbuf[n],&outbuf[n],Path);
        if(ret!=0){delete [] outbuf;return ret;}
    }
    ByteArrayToHexString(outbuf,OutString,len);
    delete [] outbuf;
    return ret;
}

void SoftKey::SwitchByte2Char(char *outstring,BYTE *inbyte,int inlen)
{
   int n;char temp[3];
   memset(outstring,0,ECC_MAXLEN*2);
   for(n=0;n<inlen;n++)
   {
        wsprintfA(temp,"%02X",inbyte[n]);
        lstrcatA(outstring,temp);
   }

}

void SoftKey::SwitchChar2Byte(char *instring,BYTE *outbyte)
{
   int n;char temp[3];
   int inlen=lstrlenA(instring)/2;
   for(n=0;n<inlen;n++)
   {
       temp[2]=(char)0;
       lstrcpynA(temp,&instring[n*2],2+1);
        *outbyte=HexToInt(temp);
        outbyte++;
   }

}

int SoftKey::YT_GenKeyPair(char* PriKey,char *PubKeyX,char *PubKeyY,char *InPath)
{

    int ret;BYTE b_PriKey[ECC_MAXLEN],b_PubKey[ECC_MAXLEN*2+1];//其中第一个字节是标志位，忽略
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(NT_GenKeyPair)(b_PriKey,b_PubKey,InPath);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    memset(PriKey,0,2*ECC_MAXLEN+1);
    memset(PubKeyX,0,2*ECC_MAXLEN+1);
    memset(PubKeyY,0,2*ECC_MAXLEN+1);
    SwitchByte2Char(PriKey,b_PriKey,ECC_MAXLEN);
    SwitchByte2Char(PubKeyX,&b_PubKey[1],ECC_MAXLEN);
    SwitchByte2Char(PubKeyY,&b_PubKey[1+ECC_MAXLEN],ECC_MAXLEN);
    return ret;

}

int SoftKey::Set_SM2_KeyPair(char *PriKey,char *PubKeyX,char *PubKeyY,char *sm2UserName,char *InPath )
{

    int ret;BYTE b_PriKey[ECC_MAXLEN],b_PubKeyX[ECC_MAXLEN],b_PubKeyY[ECC_MAXLEN];
    SwitchChar2Byte(PriKey,b_PriKey);
    SwitchChar2Byte(PubKeyX,b_PubKeyX);
    SwitchChar2Byte(PubKeyY,b_PubKeyY);
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(NT_Set_SM2_KeyPair)(b_PriKey,b_PubKeyX,b_PubKeyY,sm2UserName,InPath);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;

}

int SoftKey::Get_SM2_PubKey(char *PubKeyX,char *PubKeyY,char *sm2UserName,char *InPath)
{

    int ret;BYTE b_PubKeyX[ECC_MAXLEN],b_PubKeyY[ECC_MAXLEN];
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(NT_Get_SM2_PubKey)(b_PubKeyX,b_PubKeyY,sm2UserName,InPath);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    memset(PubKeyX,0,2*ECC_MAXLEN+1);
    memset(PubKeyY,0,2*ECC_MAXLEN+1);
    SwitchByte2Char(PubKeyX,b_PubKeyX,ECC_MAXLEN);
    SwitchByte2Char(PubKeyY,b_PubKeyY,ECC_MAXLEN);
    return ret;

}

int SoftKey::SM2_EncBuf(BYTE *InBuf,BYTE *OutBuf,int inlen,char *InPath)
{

    int ret,temp_inlen;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    while(inlen>0)
    {
        if(inlen>MAX_ENCLEN)
            temp_inlen=MAX_ENCLEN;
        else
            temp_inlen=inlen;
        ret=(NT_SM2_Enc)(InBuf,OutBuf,temp_inlen,InPath);
        if(ret!=0)goto err;
        inlen=inlen-MAX_ENCLEN;
        InBuf=InBuf+MAX_ENCLEN;
        OutBuf=OutBuf+MAX_DECLEN;
    }
err:
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;

}

int SoftKey::SM2_DecBuf(BYTE *InBuf,BYTE *OutBuf,int inlen,char* pin,char *InPath)
{

    int ret,temp_inlen;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    while(inlen>0)
    {
        if(inlen>MAX_DECLEN)
            temp_inlen=MAX_DECLEN;
        else
            temp_inlen=inlen;
        ret=(NT_SM2_Dec)(InBuf,OutBuf,temp_inlen,pin,InPath);
        if(ret!=0)goto err;
        inlen=inlen-MAX_DECLEN;
        InBuf=InBuf+MAX_DECLEN;
        OutBuf=OutBuf+MAX_ENCLEN;
    }
err:
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;

}

int SoftKey::SM2_EncString(char *InString,char *OutString,char *InPath)
{

    int inlen=lstrlenA(InString)+1;
    int outlen=(inlen/(MAX_ENCLEN)+1)*SM2_ADDBYTE+inlen;
    BYTE *OutBuf=new BYTE[outlen];
    BYTE *p=OutBuf;
    int ret,temp_inlen;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    while(inlen>0)
    {
        if(inlen>MAX_ENCLEN)
            temp_inlen=MAX_ENCLEN;
        else
            temp_inlen=inlen;
        ret=(NT_SM2_Enc)((BYTE *)InString,OutBuf,temp_inlen,InPath);
        if(ret!=0)goto err;
        inlen=inlen-MAX_ENCLEN;
        InString=InString+MAX_ENCLEN;
        OutBuf=OutBuf+MAX_DECLEN;
    }
err:
    memset(OutString,0,2*outlen+1);
    ByteArrayToHexString(p,OutString,outlen);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    delete [] p;
    return ret;

}

int SoftKey::SM2_DecString(char *InString,char *OutString,char* pin,char *InPath)
{

    int inlen=lstrlenA(InString)/2;
    BYTE *InByte=new BYTE[inlen];
    BYTE *p=InByte;
    int ret,temp_inlen;
    SwitchChar2Byte(InString,InByte);
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    while(inlen>0)
    {
        if(inlen>MAX_DECLEN)
            temp_inlen=MAX_DECLEN;
        else
            temp_inlen=inlen;
        ret=(NT_SM2_Dec)((BYTE *)InByte,(BYTE *)OutString,temp_inlen,pin,InPath);
        if(ret!=0)goto err;
        inlen=inlen-MAX_DECLEN;
        InByte=InByte+MAX_DECLEN;
        OutString=OutString+MAX_ENCLEN;
    }
err:
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    delete [] p;
    return ret;

}

int SoftKey::YtSetPin(char *old_pin,char *new_pin,char *InPath )
{
    int ret;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(NT_Set_Pin)(old_pin,new_pin,InPath);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;
}

void SoftKey::SwitchBigInteger2Byte(char *instring,BYTE *outbyte,int *outlen)
{
    int n;char temp[3];
    int inlen=lstrlenA(instring)/2;
    *outlen=0x20;

    for(n=0;n<inlen;n++)
    {
        temp[2]=(char)0;
        lstrcpynA(temp,&instring[n*2],2+1);
        *outbyte=(BYTE)HexToInt(temp);
        outbyte++;
    }

}


int SoftKey::GetChipID( char *OutChipID,char *InPath)
{
    int ret;BYTE b_OutChipID[16];
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(NT_GetChipID)(b_OutChipID,InPath);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    memset(OutChipID,0,33);
    ByteArrayToHexString(b_OutChipID,OutChipID,16);
    return ret;
}

int SoftKey::SetHidOnly(  BOOL IsHidOnly,char *InPath)
{
    int ret;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=NT_SetHidOnly(IsHidOnly,InPath);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;
}
int SoftKey::SetUReadOnly( char *InPath)
{
    int ret;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=NT_SetUReadOnly(InPath);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;
}

int SoftKey::ReadVerfData(char *InPath)
{
    BYTE dataBuffer[50];HANDLE fileHandle;
    SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER sptdwb;
    ULONG length = 0,returned = 0;
    BOOL status = 0;
    char DevicePath[20];
    lstrcpyA(DevicePath,"\\\\.\\");lstrcatA(DevicePath,InPath);
    fileHandle = CreateFileA(DevicePath,GENERIC_WRITE | GENERIC_READ,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_EXISTING, 0, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE)return OPENUSBFAIL;
    ZeroMemory(&sptdwb, sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER));
    ZeroMemory(dataBuffer, DISK_INF_LEN);
    sptdwb.sptd.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
    sptdwb.sptd.PathId = 0;
    sptdwb.sptd.TargetId = 1;
    sptdwb.sptd.Lun = 0;
    sptdwb.sptd.CdbLength = 6;
    sptdwb.sptd.DataIn = SCSI_IOCTL_DATA_IN;
    sptdwb.sptd.SenseInfoLength = 24;
    sptdwb.sptd.DataTransferLength = DISK_INF_LEN;
    sptdwb.sptd.TimeOutValue = 100;
    sptdwb.sptd.DataBuffer = dataBuffer;
    sptdwb.sptd.SenseInfoOffset =
        offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER,ucSenseBuf);
    sptdwb.sptd.Cdb[0] = 0x12;
    sptdwb.sptd.Cdb[4] = DISK_INF_LEN;                         // 命令
    length = sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER);

    status = DeviceIoControl(fileHandle,
        IOCTL_SCSI_PASS_THROUGH_DIRECT,
        &sptdwb,
        length,
        &sptdwb,
        length,
        &returned,
        FALSE);

    CloseHandle(fileHandle);
    if((sptdwb.sptd.ScsiStatus == 0) && (status != 0) )
    {
        if(memcmp(dataBuffer,DISK_INF,DISK_INF_LEN)==0)
        {
            //MessageBox(NULL,DevicePath,"OK",MB_OK);
            return 0;
        }
    }
    return OPENUSBFAIL;
}

int SoftKey::sFindPort(short pos,char *OutPath)
{
    DWORD   dwBuffer=512*2;   char cdriver[10]="";int  nSize;int len=1;//char temp[30]="";
    char   szBuffer[512*2];
    int count=0;
    DWORD lpSectorsPerCluster;
    DWORD lpBytesPerSector;
    DWORD lpNumberOfFreeClusters;
    DWORD lpTotalNumberOfClusters;
    UINT   nPreErrorMode;

    //ADD 2008-4-5
    ZeroMemory(OutPath,sizeof(OutPath));
    {
        //return isfindmydevice(pos,OutPath,count);
        ZeroMemory(   szBuffer,    dwBuffer   );
        nSize   =   GetLogicalDriveStringsA(   dwBuffer,   szBuffer   );
        while(nSize>=4)
        {
            nSize=nSize-4;
            lstrcpyA(cdriver,&szBuffer[nSize]);
            len=lstrlenA(cdriver);
            cdriver[len-1]=0;
            if((cdriver[0]=='a') || (cdriver[0]=='A') || (cdriver[0]=='b') || (cdriver[0]=='B'))continue;
            if((GetDriveTypeA(cdriver)==DRIVE_CDROM) || (GetDriveTypeA(cdriver)==DRIVE_REMOTE) ||
                (GetDriveTypeA(cdriver)==DRIVE_UNKNOWN))continue;
            //#ifdef _CHECKDISK
            /*add-2010-6-13是否需要这个，注意如果容量改变，这个要改变	*/
            nPreErrorMode   =   ::SetErrorMode(SEM_FAILCRITICALERRORS)   ;
            GetDiskFreeSpaceA(cdriver,&lpSectorsPerCluster,&lpBytesPerSector,&lpNumberOfFreeClusters,&lpTotalNumberOfClusters);
            SetErrorMode(nPreErrorMode) ;
            if(lpTotalNumberOfClusters!=344|| lpSectorsPerCluster!=1 )continue;

            //#endif
            if(ReadVerfData(cdriver)==0)
            {

                if(pos==count)
                {
                    lstrcpyA(OutPath,"\\\\.\\");
                    lstrcatA(OutPath,cdriver);
                    return 0;

                }
                (count)++;
            }
        }
    }
    return NOUSBKEY;
}

int SoftKey::FindU(int pos,char *OutPath)
{
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    int ret=sFindPort(pos,OutPath);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;
}

int  SoftKey::NT_FindU_2(  int start,DWORD in_data,DWORD verf_data,char*OutPath )
{
    int pos;DWORD out_data;int ret;
    for(pos=start;pos<127;pos++)
    {
        if(sFindPort(pos,OutPath)!=0){return -92;}
        ret=WriteDword( &in_data,OutPath);
        if(ret!=0){return ret;}
        ret=ReadDword( &out_data,OutPath);
        if(ret!=0){return ret;}
        if(out_data==verf_data){return 0;}
    }
    ZeroMemory(OutPath,sizeof(OutPath));
    return -92;
}

int SoftKey::FindU_2(  int start,DWORD in_data,DWORD verf_data,char*OutPath)
{
    int ret;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(NT_FindU_2)(start,in_data,verf_data,OutPath);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;
}

int SoftKey::NT_IsUReadOnly(BOOL *IsReadOnly,char *InPath)
{
    BYTE dataBuffer[50];HANDLE fileHandle;
    SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER sptdwb;
    ULONG length = 0,returned = 0;
    BOOL status = 0;
    char DevicePath[20];
    lstrcpyA(DevicePath,"\\\\.\\");lstrcatA(DevicePath,InPath);
    fileHandle = CreateFileA(DevicePath,GENERIC_WRITE | GENERIC_READ,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_EXISTING, 0, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE)return OPENUSBFAIL;
    ZeroMemory(&sptdwb, sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER));
    ZeroMemory(dataBuffer, DISK_SENSE_LEN);
    sptdwb.sptd.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
    sptdwb.sptd.PathId = 0;
    sptdwb.sptd.TargetId = 1;
    sptdwb.sptd.Lun = 0;
    sptdwb.sptd.CdbLength = 6;
    sptdwb.sptd.DataIn = SCSI_IOCTL_DATA_IN;
    sptdwb.sptd.SenseInfoLength = 24;
    sptdwb.sptd.DataTransferLength = DISK_SENSE_LEN;
    sptdwb.sptd.TimeOutValue = 100;
    sptdwb.sptd.DataBuffer = dataBuffer;
    sptdwb.sptd.SenseInfoOffset =
        offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER,ucSenseBuf);
    sptdwb.sptd.Cdb[0] = 0x1a;
    sptdwb.sptd.Cdb[2] = SCSI_MSPGCD_RETALL;
    sptdwb.sptd.Cdb[4] = DISK_SENSE_LEN;                         // 命令
    length = sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER);

    status = DeviceIoControl(fileHandle,
        IOCTL_SCSI_PASS_THROUGH_DIRECT,
        &sptdwb,
        length,
        &sptdwb,
        length,
        &returned,
        FALSE);

    CloseHandle(fileHandle);
    if((sptdwb.sptd.ScsiStatus == 0) && (status != 0) )
    {
        if(dataBuffer[2]==0x80)
        {
            *IsReadOnly=TRUE;
        }
        else
            *IsReadOnly=FALSE;
        return 0;
    }
    return OPENUSBFAIL;
}

int SoftKey::IsUReadOnly(BOOL *IsReadOnly,char *InPath)
{
    int ret;
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=NT_IsUReadOnly(IsReadOnly,InPath);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;
}

void SoftKey::EnCode(   BYTE  * InData,BYTE  * OutData,  char *Key  )
{
    BYTE KeyBuf[16];
    memset(KeyBuf,0,16);
    HexStringToByteArrayEx(Key,KeyBuf);
    memcpy(OutData,InData,8);
    EncBySoft(OutData,KeyBuf);
}

void SoftKey::DeCode(   BYTE  * InData, BYTE  * OutData, char *Key  )
{
    BYTE KeyBuf[16];
    memset(KeyBuf,0,16);
    HexStringToByteArrayEx(Key,KeyBuf);
    memcpy(OutData,InData,8);
    DecBySoft(OutData,KeyBuf);
}

void SoftKey::StrDec(  char *InString,char *OutString,char *Key)
{
  int n;
  int len=lstrlenA(InString)/2;
  BYTE KeyBuf[16];
  memset(KeyBuf,0,16);
  HexStringToByteArrayEx(Key,KeyBuf);
  HexStringToByteArray(InString,(BYTE *)OutString);
  for(n=0;n<=(len-8);n=n+8)
    {
      DecBySoft((BYTE *)&OutString[n],KeyBuf);
    }
  return ;
}

void SoftKey::StrEnc(  char *InString,char *OutString,char *Key)
{
  int n;BYTE *outbuf;
  int len=lstrlenA(InString)+1;if(len<8)len=8;
  BYTE KeyBuf[16];
  memset(KeyBuf,0,16);
  HexStringToByteArrayEx(Key,KeyBuf);
  outbuf=new BYTE[len];
  memset(outbuf,0,len);
  memcpy(outbuf,InString,lstrlenA(InString)+1);
  for(n=0;n<=(len-8);n=n+8)
    {
      EncBySoft(&outbuf[n],KeyBuf);
    }
  ByteArrayToHexString(outbuf,OutString,len);
  delete [] outbuf;
}

int SoftKey::GetProduceDate(  char *OutDate,char *InPath)
{
    int ret;
    BYTE B_OutBDate[8];
    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=(NT_GetProduceDate)(B_OutBDate,InPath);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    ByteArrayToHexString(B_OutBDate,OutDate, 8);
    return ret;
}

int SoftKey::SetID(char * Seed,char *InPath)
{

    int ret;
    BYTE KeyBuf[8];
    memset(KeyBuf,0,8);
    HexStringToByteArray(Seed,KeyBuf);

    HANDLE hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");
    WaitForSingleObject(hsignal,INFINITE);
    ret=NT_SetID(KeyBuf,InPath);
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;

}

int SoftKey::Y_SetCal(BYTE *InData,short address,short len,BYTE *password,char *Path )
{
       short addr_l,addr_h;int n;int ret;
   BYTE array_in[25],array_out[25];
   HANDLE hUsbDevice=MyOpenPath(Path);
    if(hUsbDevice == INVALID_HANDLE_VALUE)return NOUSBKEY;

   if(len>8)return -87;
   if(address+len-1>2047 || address<0)return ErrAddrOver;
   {addr_h=(address>>8)<<1;addr_l=address&0xff;}

   array_in[1]=SETCAL;//read 0x10;write 0x11;
   array_in[2]=(BYTE)addr_h;//0x01;//read 0x80 ;write 0x40;
   array_in[3]=(BYTE)addr_l;
   array_in[4]=(BYTE )len;
   for(n=0;n<8;n++)
   {
       array_in[5+n]=*password;
       password++;
   }
   for(n=0;n<len;n++)
   {
       array_in[13+n]=*InData;
       InData++;
   }
   ret= Hanldetransfe(hUsbDevice,array_in,13+len,array_out,1,Path);
   if(ret!=0)return ret;

   if(array_out[0]!=0x0)
   {
       return ErrWritePWD;//表示写失败；
   }
   return 0;
}


int  SoftKey::SetCal(char * W_HKey,char *W_LKey,char * new_HKey,char *new_LKey,char *InPath)
{

    BYTE ary1[8];BYTE ary2[8];	int ret;short address=0x7f0-8;

    myconvert(W_HKey,W_LKey,ary1);
    myconvert(new_HKey,new_LKey,ary2);

    HANDLE	hsignal=CreateSemaphoreA(NULL,1,1,"ex_sim");

    WaitForSingleObject(hsignal,INFINITE);
    ret=Y_SetCal(ary2,address,8,ary1,InPath);
    if(ret!=0){ReleaseSemaphore(hsignal,1,NULL);return ret;}
    ReleaseSemaphore(hsignal,1,NULL);
    CloseHandle(hsignal);
    return ret;

}

void  SoftKey::SnToProduceDate(char* InSn,char *OutProduceDate)
{

   char temp[5]="";
   memset(temp,0,5);
   lstrcpynA(temp,&InSn[0],2+1);
   int year=2000 + HexToInt(temp);
   lstrcpynA(temp,&InSn[2],2+1);
   int month=  HexToInt(temp);
   lstrcpynA(temp,&InSn[4],2+1);
   int day=  HexToInt(temp);
   lstrcpynA(temp,&InSn[6],2+1);
   int hour=  HexToInt(temp);
   lstrcpynA(temp,&InSn[8],2+1);
   int minutes=  HexToInt(temp);
   lstrcpynA(temp,&InSn[10],2+1);
   int sec=  HexToInt(temp);
   lstrcpynA(temp,&InSn[12],4+1);
   int sn=  HexToInt(temp);
    wsprintfA(OutProduceDate,"%d年%d月%d日%d时%d分%d秒--序号：%d", year,month,day,hour,minutes,sec,sn);
}

//使用普通算法一查找指定的加密锁
int SoftKey::CheckKeyByFindort_2()
{
    char DevicePath[260];
    return FindPort_2(0, 1,  1444877526, DevicePath);
}

//使用带长度的方法从指定的地址读取字符串
int SoftKey::ReadStringEx(int addr,char *outstring,char *DevicePath)
{
    int ret;
    short nlen;
    byte buf[1];
    //先从地址0读到以前写入的字符串的长度
    ret = YReadEx(buf, addr, 1, (char*)"86777864", (char*)"F000134F", DevicePath);
    nlen = buf[0];
    if( ret != 0 )
    {
        return ret;
    }
    memset(outstring,0,nlen+1);//outstring[nlen]=0;//将最后一个字符设置为0，即结束字符串
    //再读取相应长度的字符串
    ret = YReadString(outstring, addr+1, nlen, (char*)"86777864", (char*)"F000134F", DevicePath);
    return ret;

}

 //使用从储存器读取相应数据的方式检查是否存在指定的加密锁
int SoftKey::CheckKeyByReadEprom()
{
    int n,ret;
    char DevicePath[260];
    char outstring[260];
    //@NoUseCode_data return 1;//如果没有使用这个功能，直接返回1
    for(n=0;n<255;n++)
    {
        ret=FindPort(n,DevicePath);
        if(ret!=0)return ret;
        ret=ReadStringEx(0,outstring,DevicePath);
        if((ret==0) && (memcmp(outstring,"xxteck",lstrlenA("xxteck"))==0))return 0;
    }
    return -92;
}

//使用增强算法一检查加密锁，这个方法可以有效地防止仿真
int SoftKey::CheckKeyByEncstring()
{
    //推荐加密方案：生成随机数，让锁做加密运算，同时在程序中端使用代码做同样的加密运算，然后进行比较判断。

    int n,ret;
    char DevicePath[260];
    char InString[20];

    //@NoUseKeyEx return 1;//如果没有使用这个功能，直接返回1

    srand((unsigned)time(NULL));
    wsprintfA(InString,"%X%X",rand(),rand());

    for(n=0;n<255;n++)
    {
        ret=FindPort(n,DevicePath);
        if(ret!=0)return ret;
        if(Sub_CheckKeyByEncstring(InString,DevicePath)==0)return 0;
    }
    return -92;
}

int SoftKey::Sub_CheckKeyByEncstring(char *InString,char *DevicePath)
{
    //'使用增强算法对字符串进行加密
    int ret,nlen;
    char *outstring;
    nlen = lstrlenA(InString) + 1;
    if( nlen < 8 ) nlen = 8;
    outstring = new char[nlen * 2+1];//注意，这里要加1一个长度，用于储存结束学符串
    ret = EncString(InString, outstring, DevicePath);
    if (ret != 0) {  return ret;}
    char *outstring_2;
    outstring_2 = new char[nlen * 2+1];//注意，这里要加1一个长度，用于储存结束学符串
    StrEnc(InString,outstring_2, (char*)"F1C798C50E77F64703C75703CE0D37CF");
    if(memcmp(outstring,outstring_2,lstrlenA(outstring_2))==0)//比较结果是否相符
        ret=0;
    else
        ret=-92;
    delete [] outstring_2;delete [] outstring;
    return ret;

}

//使用增强算法二检查是否存在对应的加密锁
int SoftKey::CheckKeyByEncstring_New()
{
	int n,ret;
	char DevicePath[260];
	char outstring[260];
	int myrnd;
	char EncInString[][50]={"31142","26684","22601","3258","14758","19496","24783","30288","4969","6984","32313","7609","15930","22460","12836","26146","22659","20040","7751","21090","8655","26702","3709","26343","21702","7632","8896","11205","8500","1903",
"6443","20142","17921","4206","14326","25843","19257","18606","22396","19847","23557","22194","3129","13052","16559","2460","28867","11651","30881","2862","4056","1264","29797","12744","28238","4786","28582","29294","13603","17373",
"27436","29379","31598","15139","18147","15111","12395","4821","31700","2077","9587","16102","30249","15749","14335","3816","3885","30564","7083","20492","10056","15482","17456","3877","24581","20522","28520","31396","30222","9334",
"20302","25756","15150","27647","21498","25791","12366","19464","5544","6751","16248","11891","24240","3693","5590","13249","21902","13691","7602","17684","18139","4541","6262","17967","3921","29954","22700","26484","9674","25279",
"7167","6117","17728","4612","1336","5923","14030","3972","13888","10097","15276","32656","2595","24496","5942","28","28426","7524","14565","10935","24639","5805","1619","13973","45","3149","17722","14984","21083","7079",
"9588","3842","5495","12476","27387","20499","15689","6192","14314","32624","3259","12610","30329","18026","20438","16342","25348","22514","13766","24174","13828","29338","19156","4141","28178","662","4715","29393","14827","25525",
"16659","4289","614","17260","5752","21243","5246","8907","22370","4900","27469","30852","26556","19835","6670","29419","1170","29412","22042","23024","7691","23265","8427","4390","20850","21908","4635","14782","817","23998",
"16739","29835","6355","27330","20639","17407","21248","25250","5577","3627","18307","11264","25849","16065","31559","24604","31338","2325","7253","7387","1144","18967","23511","30396","19865","2650","26647","2789","1643","8207",
"1664","12564","12196","28936","19865","19885","9250","21689","32528","17329","17116","5683","429","1732","14573","5670","31577","19749","27535","3303","2849","25016","542","27749","9003","5632","4112","25141","709","21532",
"24322","31111","20565","20689","22701","23854","21353","23934","4332","14748","20136","23080","28598","16098","31198","18287","31528","17075","7156","30870","16764","608","17652","25982","25355","1244","10248","7339","15439","7353",
"5498","21820","12258","2600","5300","8438","4222","15612","7744","15929","11005","13990","30152","2568","28761","3130","9239","4612","16301","2152","4374","18031","20529","28033","15823","19501","15169","22394","7788","28350",
"9814","15844","5175","12869","3338","5617","1947","1411","11031","5234","8736","5083","1623","4057","10353","14158","6340","569","29784","2688","6777","11076","3777","6833","27566","21067","27058","14787","7871","10305",
"14936","28729","8741","18872","29436","3893","2682","24801","23816","25208","31863","26511","21255","613","14073","2356","6818","17917","15607","9441","24226","21732","8077","28488","18675","22873","26611","13501","15518","21057",
"8581","15152","12237","1308","956","17459","9674","4109","15409","12026","18687","7125","22688","14932","9462","11735","20706","26294","90","6677","12530","30768","22259","5424","25320","6261","29613","26218","6400","6359",
"10897","14759","22418","21574","13001","4455","7962","12631","8351","22733","13873","17466","32637","5530","5009","4290","3054","14897","26644","27744","3482","6036","18613","40","20812","28515","30860","27337","17135","9700",
"21204","664","10124","5109","21736","14213","30541","31002","18497","5411","22396","3445","3193","25762","13444","13255","330","28375","31724","19315","4238","24115","30306","8827","22591","16583","16814","1920","29815","10822",
"27321","31684","26993","30209","10128","1324","11654","10476","12634","8245","21296","29590","15970","20997","21257","21555","7186","23132","30154","22677"};
	char EncOutString[][50]={"14300BEEF2EE2C21","0BA29F7274D75385","B38D6673F991B2D6","8743F1CF08C34473","3113450AC5D5345D","2C75C2FD6B240893","3B4954898C16DEA2","166683D00F8B7A71","A1CE837CB892CB35","A782FD7B4878A3EA","3EF8BE081CEED3AA","77A5EE23A71850ED","8992DC2F7AB4C532","C3DD7FF235E917B0","55F03F417E715721","47EDD983CF29A5FE","26EE74EEE15088C2","39AE9F7001234303","E9FDFBA495F81C84","E92A0DE4E6F8EFA1","C75EEF04C52DD9FE","0B31CC977A6007C4","EDA91DD41E69B6B6","478A6A4FFDDCB1B9","1510CBA0F082E8DE","F01C1328F0C1A692","3E9E774C35F4489D","7F33EAF99435383E","2C25E4BA499F2900","AC3B439547D411B3",
"16CB55B24C686ABB","3473579C4A57BD5B","5A0CB58B934E014E","D7128C43F72697E2","11AE09F0B92893BB","4952F48D3D3FB6F9","9E2289E00BA4F761","DF52527AF68E0E8E","ACEC251C50601D47","2C90E8501C3E1D54","76AD9C6A61E9CB30","2E2548FC85011EA8","E2B276095070C627","3CA6637A6D7B813E","C027339CF7419AF8","F8FD4673390AE813","A0529185C8C0A0F8","003A61D790637CBE","B7EEE4894B4E9BC1","A57B5221E50DF612","9DF8DDC18618A5CB","C6871D1B5616FBDC","98BEF2D6FC83118F","0348B193B10722E4","C95E3E0A4CC53015","266B902DE222B05A","E1AAE75950980BC5","B2DB83238A26B8F2","79F69314C0EB00E4","BE3508A2C4FC5DF7",
"BD31D13C2B7131EA","63AF550A0EFABE7B","C4E9D530C97FCF6B","2496719B43AA3DAB","4598CAEC6F069327","998371AA98616936","5B2CA560BF8001A4","6DF53229A36EBF53","9800B213B3AF8764","D3401CDC6928BD20","3ECCE13F5F66E98E","370EE7FBEE0BE455","3BF3CCCDA8209C14","2D7023FC6D660A09","C64EA4C47E7F1638","11EDD3E661AB1EC8","88C8F83885581C16","68154604E8403344","18F87AEED2572D16","59B45764CBE33759","C6BD4293AD17E05C","25220ACC99F25593","E8CCA291BBAC7037","E68DC0196E764187","7BD06CAB9847F49A","3FFEE6C91F3FDB35","394AE2C0615A033C","3A4F51D8E9642FFB","79D07C56D5CC98D6","ECAD32E2B7B3B2CD",
"ED8EB4AA71F70CC6","58796B5763EBF6B8","84998D5BD62A9968","B396D8F4FA7C61EA","C5C969371DAE3130","D3B9CCC6FD1F8AB1","8230442923452FB8","44232E47E4B26198","DE89949FFB190FD5","CCF2E7A3E68A16AA","4EFA2CD407232A6D","F62ADF043A3F7676","C0C13FBF714078B5","7794828E4F24B459","60DE892DD86F3EB0","04D1121EA84DF507","62ED6A9A8EFCB273","7528025568A3EB1B","3BA2353260FCA4EB","879F00E60437CA59","A884BA48D032426D","ADF51BA6AA1BD4B8","9423FD356E0C5B49","8F739012A8DCDD99","A1EFEC2AE103E45C","DFE678BC0FA7A587","442BF0C291458F52","F0BAAF1D31329734","B0D5D48FFDDDB99C","D105CA760E16053D",
"B6046FD5AF262E33","FF09677246C12868","6ECD639A78311003","BD513555E98D2402","FFE1D0DC99EA00D6","789576E109985C24","75CBD5209DA071F3","07C2EE237F4FA707","5C7AAB8D9DCFAFE6","C53A6F1DD86EE56F","6A8113B27A73B513","64EE104B9C34E388","B0C0BD0B2DEC1A43","48376363EBD25BFF","4B59C0E130EF3751","5BB850538B188640","145D3687FAD0C0E1","40A8A767AE752A21","934FDA71825CF806","80C2CC46EA72E010","246C49D6E40CE285","5449309B3A8B22B1","2C7CB20FB44A9E09","10E2D87243B932D4","C710C4E9D857F11E","93F5C92CFDAB79B6","1DF55F47857AAACB","C772243322FA9D37","A55F9529D4C86849","63222D4D96041C5F",
"3BA5B0CC741E211F","4875B5518961B15A","6E20A549C2FF5F5D","FE419C8AE015435F","880EC5B15E4AAC2B","61CE05281E1C93BC","403BA66A837DAAB2","DF08EC0B65E59862","141D06C31589E073","22DB1EB87C1F3EB7","E04CA00850F49739","6FBC238DC879D5E2","57172012102C6320","0A5A0FF19FD196E4","934BD04B47D5C576","C4871CCAE8DB26C0","0F923BA40155968F","390774A9748FED36","DE1A4F04B16AA195","C541490BF3B76CE7","4EA37661FE6F9B18","96F0816C69AB55B8","CFC2636F43FDB3ED","BB83E3F392CB24D2","2C16DD61C4FD2DD4","20807B5C179B3158","905CE51A7CEB1F2B","FE6CBDD55E856E6A","A7583513CAB0BED2","5944C89B3FBB00A7",
"B0BCB05C09932BC3","81C7842EA52CB6E9","8E0B8B9400227EEC","F04613E78CEE6B8A","E54A2E6582F37F51","E69DFDD00A54C04C","381BFD2B12B619EC","4D07E6DD98C9AB2E","A36E45A3F316F070","5D83E831B40F3244","B9B547561F243B12","38B6E7CC2BA8C93E","55ABA159EF6CA86C","08DC690F1A1B6946","18D3AC16AD0647EA","9BF053A9300B2436","49B04801EC1AFC2C","8DB599A2C66CA250","24D5E37422B0AFF4","8F4BD3319AE178F9","B6D8ADC8F6E053DC","56F4FC1CF02CB0A0","D99FB6E342720B90","C313990ED010AFBD","BBCFB73F2304BE84","DAA406A8A58468F9","60038EAE28D32F23","DD3B1E250BB0A3D1","E6ABBC090F59B95F","E454E288EB54C931",
"CAC414096B0CCFA2","FB7F1F3B090071DC","F285342CC2CD4267","33E792DA3F1120D9","94A4FE552B23F70E","6CD63C3C0A04B51E","58816B09D7692458","EFA4D23BD0E8BACC","B2B2CE85FAA8EAE7","01F006799F74BEE4","E612234FBEBEE70C","095F7932C0B1C176","F2DE3743E3C234DA","40A43ED3F868EA03","7208975794F852F2","EECB281834EF36B2","3A8AF44AE3670038","871BFAFEC606B508","0AD92909054564FE","18573C7773526C7E","674392471B1ECED7","93EBDAEB221955CE","2A06933B1E7FC17C","AC62CFE99E484C37","C1F10F9A42786322","F2CC7431C3E6019B","80D12E74DBE11342","7FB539BF21D4A3C7","4A9012C15307CDE4","0C42F146B0755477",
"DB601BCBFFDB520F","703F12704DB8E21F","7E635075B2ABECE0","35579E5DD7B93866","C1F10F9A42786322","ACB21891886CD6BA","EAD1D24812D4306A","60E222B3B64A32F7","08436D0B9F044EF3","3C5B541EC46305F7","57D80C9DBECA6DBF","D8CD3D4A131FAF51","DAAE39B1635CFB26","9A294997990A8172","08D8C7990DA41409","A3ED30B2ED8D542D","5837CF3C1FBF6865","212F9A8A88EB0825","3053A2DD21F042C4","4F7D633F782FD611","B562D5BF5718BFCA","CEA9D82DBD37AC5C","A8AEE47C12695603","03DAAED6FB598BA3","3A409D6369905616","D18A6CDF817FCF16","586B1C122C3A1E4C","0085180003C51EDC","EA4BD574F45DC431","588F9B6DF7731380",
"BB235F039CE07673","93697C779670E854","FAC9191824B78FF0","21C045B9FE5A4D6F","21BBDDAF1FFF6EFF","26A000622BEEEAAB","FEF5BF18F4960DD2","2205E0CC4151E646","A975117EF759ED2E","1CA53F1BB538A79C","C25C4C5A2271B99C","9DEB59CF76173E54","7F8F5015D08C7767","6B3FC372A819F8E6","8981A9CEFE34ED20","C10E6FACC837B385","DA76E79D17CB8CBB","D5BDB4D03A278698","B8C5FA225C184418","7C79D86E9C2D35A6","8194BFE902A8EE49","B610D48010E4C49F","02D49B288D4EA3A9","1E88B4D03E237EE4","4896338BFDDE1906","0922F92DA4273DFC","236869D003E183FB","26CA8A863B6D6FFE","A850C4A11BCC92C7","9660C76506F54D4A",
"0EB7E2113FF15F5C","61994109EEBF9CC3","33940DED877C5A58","5A537FCA6C7D1E9A","0883BCB2A2121EA0","CFB1D2175BF2234C","D528438F76EC1355","5D5EE6B95EC84055","107BF7A860C258B7","7F516B09036EBE34","2FB3CE3FD7CE72A0","3F1F8563B00DB911","837295980985EAF4","23915076CF6AD57D","68A1DF4FB0D33294","B1F649FF65AD315D","79012EA46EE68960","BD513555E98D2402","67A48ED6540A674E","883291A7282BDFD1","57AB4096441B285A","8823090A3EE125F3","E53A1B9BC2EAA82B","4344BEEB24BD89CE","86C71AB7DE99E7C3","C0B840BF3A410244","CD665396FFC7D1B2","C783E1EEF092E62B","8947E25D32F6BD4D","28B0DD023FDC4B17",
"63378238AA73F0EA","7FF026DCCA5CADD1","8C2E3D7BBB020E34","6D222D3F209493E7","7D4E8A8BD8137BB7","D9C83EE156062078","8B6263492FC28D68","4844D6038298A582","F140B8F1BE2E5337","1F294E3969BB2133","CEC6F06E9578CB26","3CF1EFCAFE1B72AA","E8F296F2EEA4B776","B511299B22F69F63","ECD2538CF50CDDB7","89762BAB186C7F2E","7F3BCBC55D2E3587","8F707AAC4A4803E9","751C51C173E568A6","732405D2E839C8B8","B721419FD701320B","32C1D9869B298C64","CEE13476932F7005","1DDCBEA3E0C96901","10E039D60F15C3B8","565B1B17075196E8","0FA2626B65B86575","6AD03C5BB9B102CD","646581EA50BF1582","DA95F5A3F1EE2AAE",
"6CCDB0A9D698647C","DDB0B6D5D526EAC5","D4518D0BA0EC1788","5C57CD1C8C468F0A","70CD79C883C6A702","4A0E559494E88CAA","65E0C87340A859CD","CE9F518449FF5592","1C6914F449D11466","8C31195D9FFF159B","469879106858E6F7","D3499F88EEB0A906","E821EEFFABCF9A38","CD64AE674DEF5D51","439A048C24067A52","1013E5D6D30C780C","DB2D920E938E007A","C1C74EBA97D91638","D508FD5CB86CBAC7","C370C935A5E0F7B3","FAE81441CEA37AF4","18A4093925ECBFA7","C8C8F46C62C9F954","5621A8A2FD8D2B06","291A96F9437FF54C","8A91BC0135A847E4","4C1B5FEC214FC679","83AD0787DA003DAF","C370CCEDF211617D","29CF3A87C5E35DF8",
"29A93F070DA14173","FD40991196C6E874","C515214C302776BF","03B663285DF6E7C2","7FE2C158EFD261C1","62A783638C417ECF","B0D5D48FFDDDB99C","BD56B7C1AC5781DD","3E1C6D0B4CCFF8BB","FF94BBE988200FE6","B9B465C4DF42C90D","6DB1352292F449C1","00404ED08C15FCF4","3012A090762B3859","F1D21370E1DC33EC","ECF20F41F9ACAC48","7C0FDCCDDD428B51","E4E2E7C0D749E848","AA6DECB378A2C1FB","3BF7F3DCEE85A048","DDBFE44A5F067138","D5AA7563623AAE4F","5FB602D7BEC7EBDC","0FFA859849276A5B","BBE575CC24161060","A0ABD5416E7581B1","BFFDA4DF7800336F","6E2E3B045DD2CBF4","0FD80EE913E60238","4F5A8ABFA9CBAF9D",
"F54F1170ED454F53","70F0FE25FA2EEBDC","6B47184090B22F08","3DC216A34D03A0A8","542734F4EFCB9848","1746AD22D8285884","C67F765821CEC5A6","AFE4949C12F3A4CD","0516EEC7F4E8AEDD","EC3CB113584811C2","44570F9A3861DB29","2C956DFA3FFA1ED7","6A120B261B6533F1","B60A8DEE1CBB28CD","E87CAE17ACDE7FAD","90F31E103BD1F6CE","D82372F71803A5D4","9BE36E49B8E3669F","E140AD8EA86C73C4","EE740ED77CAA5A01","20F2E6204AC3A710","78DE83A1123BD121","FA8A37B67FF5C80D","F2A21475005161DF","06AAFE8622AE5154","0B3814B66F2BAD18","D5624E023A3A4FD4","C2F107421508172B","9B87FD597B6B834B","E8709E6FC0FC3767",
"29C6074AD2D762C1","E7DED6B337B70BAE","FF7EADDDFB18C734","4CDAB96F26581C1B","32223DDA729691D7","61FFC5488FC347C9","4EF4A60ED1F9F414","5D11F1ABF1FD471B","DF09DDC14B1E5079","DF518524057C1844","ACEC251C50601D47","FBF5AAA5EDF2526C","8BA18174E76B985F","5D18A73373B35244","5B6AADC70E5033E3","DC770DA17633C8C2","6A2D6B70F1ACD12C","0EAB57846E71AD81","994E5771073AE6EB","F389FB3E6A9ECAC1","57ADC9A7DEC922EF","980C018BF7B62C9C","B19CCAFDC6636131","B4AEEE669277652C","7424F5346E868CB9","28B3BFBD8181E8E1","F3AA1DA9413928C8","70245CC54E91E7B2","858EC74673DB9DC3","493D3A3A49400F1F",
"5145A240FBB51E11","CF19AF5B22E28697","A05A1A8624CD9CDB","44800FF0D0FBDD05","B1DFBADEB0F938A7","16AF0A1DD6FE14D9","33544EC449D72B67","17063498408572E3","D600E62C7A746F39","2278128B14FFF1E8","8C2D9B104CC3E5A6","8A896A86266D567B","3DC8FF2442E22311","2FBD31E2F1A6FA04","F72C0D728C6BAB8D","4D43992A6C29068A","5F1EBA4AB8743A65","ACA862CE0ED1CB9A","3E82ED9930DE4540","0362D74E69C6B9F9"};
	//@NoUseNewKeyEx return 1;//如果没有使用这个功能，直接返回1
	//@NoSupNewKeyEx return 2;//如果该锁不支持这个功能，直接返回2

	srand((unsigned)time(NULL)); 
	myrnd=rand()%500;
	for(n=0;n<255;n++)
	{
		ret=FindPort(n,DevicePath);
		if(ret!=0)return ret;
		ret=EncString_New(EncInString[myrnd], outstring,DevicePath);
		if(memcmp(outstring,EncOutString[myrnd],lstrlenA(EncOutString[myrnd]))==0)return 0;
	}
	return -92;
}

