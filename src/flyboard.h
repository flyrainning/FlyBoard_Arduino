#ifndef FLYBOARDHEADER
#define FLYBOARDHEADER true


#include "config.h"


//system
#ifdef modules_system
  #include "modules/System/STL.h"
  #include "modules/System/algorithm/CRC16.h"
	#include "modules/System/FBSettings/FBSettings.h"
	#include "modules/System/ArduinoJson.h"
	#include "modules/System/Debug/Debug.h"
  #include "modules/System/Timer/Timer.h"


#endif


//opencv
#ifdef modules_FBCmd
	#include "modules/FBCmd/FBCmd.h"
  #include "modules/FBCmd/FBCmd_base.h"
#endif


//device
#ifdef modules_device
  #include "modules/Device/GPIO/GPIO.h"


#endif



#endif
