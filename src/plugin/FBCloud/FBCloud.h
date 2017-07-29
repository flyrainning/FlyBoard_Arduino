// #ifndef FLYBOARD_CLOUD
// #define FLYBOARD_CLOUD
//
// #include "../FBCmd/FBCmd.h"
//
// #ifndef SN
//   #define SN    "0"
// #endif
// #ifndef IC
//   #define IC    "0"
// #endif
//
// #ifndef FBCLOUD_SERVER
//   #define FBCLOUD_SERVER    ""
// #endif
//
// #ifndef FBCLOUD_PORT
//   #define FBCLOUD_PORT    8018
// #endif
//
// enum Protocol{
// 	TCP=0,
// 	UDP=1
// }
//
// struct Settings_FBCloud:virtual public Settings_FBCmd
// {
//   Protocol protocol=TCP;
// 	char server[32];
// 	int port;
//
// 	void loadDefault(){
// 		this->protocol=TCP;
// 		strcpy(this->server,FBCLOUD_SERVER);
// 		this->port=FBCLOUD_PORT;
// 	};
// };
//
// class FBCloud
// {
//
// public:
//
// 	FBCloud();
//
//
//
//
// };
//
//
//
// #endif
