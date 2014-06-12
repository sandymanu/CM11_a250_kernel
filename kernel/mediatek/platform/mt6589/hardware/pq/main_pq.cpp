#define LOG_TAG "PQ"

#include <cutils/xlog.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>

#include "ddp_drv.h"
#include "ddp_color_index.h"
#include "ddp_tdshp_index.h"

#include <cutils/properties.h>

int drvID = -1;
unsigned long lcmindex = 0; 

 DISP_PQ_PARAM pqparam = 
{
u4SHPGain:0,
u4SatGain:0,
u4HueAdj:{3,3,3,3},
u4SatAdj:{0,9,9,9}
};
/*DISP_PQ_PARAM pqparam = 
{
	u4SHPGain:5,
	u4SatGain:9,
	u4HueAdj:{3,0,6,6},
	u4SatAdj:{0,6,6,6}
};*/

const DISP_PQ_PARAM pqparam_camera =
{
    u4SHPGain:0,
    u4SatGain:0,
    u4HueAdj:{3,3,3,3},
    u4SatAdj:{9,9,9,9}
};



//COLOR_TUNING_INDEX : 10
 unsigned long chrtol(char nptr)
{
	char ret;

	if(nptr>='A' &&nptr<='F')
	{
		ret += nptr-'A'+10;
	}
	else if (nptr>='a' &&nptr<='f')
	{
		ret += nptr-'a'+10;
	}
	else if (nptr>='0' &&nptr<='9')
	{
		ret += nptr-'0';
	}
	else
	{
		XLOGE("PQ: NULL pointer input\n");
	}
	return ret;
}



//DISPLAY_PQ_T pqindex;
int main(int argc, char** argv) 
{
    int actionID=0, RegBase = 0, RegValue = 0, err = 0;
    char fileName[256];

    XLOGD("PQ init start...");


   char data_buff[10];  	  
   property_get("persist.lcd.pq.pqparam", data_buff, "0333999");
   
   pqparam.u4SatGain    = chrtol(data_buff[0]);
   pqparam.u4HueAdj[1] = chrtol(data_buff[1]);
   pqparam.u4HueAdj[2] = chrtol(data_buff[2]); 
   pqparam.u4HueAdj[3] = chrtol(data_buff[3]);
   pqparam.u4SatAdj[1]  = chrtol(data_buff[4]);
   pqparam.u4SatAdj[2]  = chrtol(data_buff[5]);	  
   pqparam.u4SatAdj[3]  = chrtol(data_buff[6]);
 
    XLOGD("PQ Satgain=%d,Hue1=%d,Hue2=%d,Hue3=%d",pqparam.u4SatGain,pqparam.u4HueAdj[1],pqparam.u4HueAdj[2],pqparam.u4HueAdj[3]);
	
    if(drvID == -1) //initial
        drvID = open("/dev/mtk_disp", O_RDONLY, 0);

    XLOGD("PQ test...");
    ioctl(drvID, DISP_IOCTL_SET_PQINDEX, &pqindex);
    ioctl(drvID, DISP_IOCTL_SET_PQPARAM, &pqparam);
    ioctl(drvID, DISP_IOCTL_SET_GAMMALUT, &gammaindex);
    ioctl(drvID, DISP_IOCTL_SET_TDSHPINDEX, &tdshpindex);
    ioctl(drvID, DISP_IOCTL_SET_PQ_CAM_PARAM, &pqparam_camera);
    ioctl(drvID, DISP_IOCTL_SET_PQ_GAL_PARAM, &pqparam);

    XLOGD("PQ init end !");
    return 0;
}
