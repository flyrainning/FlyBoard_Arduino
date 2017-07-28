#ifndef FLYBOARD_DEBUG
#define FLYBOARD_DEBUG

#include <Arduino.h>
#include "../STL/vector"
#include "../STL/map"
#include "../STL/ArduinoSTL.h"
using namespace std;

class Debug
{
public:

  template <class T1=String,class T2=String,class T3=String,class T4=String,class T5=String >
  static void out(T1 msg1="",T2 msg2="",T3 msg3="",T4 msg4="",T5 msg5=""){

      std::cout<<msg1<<" : "<<msg2<<" "<<msg3<<" "<<msg4<<" "<<msg5<<endl;

  }
  template <class T1=String,class T2=String,class T3=String,class T4=String,class T5=String  >
	static void outl(T1 msg1="",T2 msg2="",T3 msg3="",T4 msg4="",T5 msg5=""){

			std::cout<<"  |-- "<<msg1<<" : "<<msg2<<" "<<msg3<<" "<<msg4<<" "<<msg5<<endl;

	}

  template <class T>
  static void out_v(std::vector<T> v,String Split=",")
  {
      int size=v.size();
      for(int i=0; i<size; i++) {
        cout<<v.at(i)<<Split;
      }
      cout<<endl;
  }
  // template <class T,class W>
  // static void out_m(map<T,W> v,String Split=",")
  // {
  //     typename map <T,W>::iterator Iter;
  //     for ( Iter = v.begin(); Iter != v.end(); Iter++ )
  //     {
  //       cout <<Iter->first<<Split<<Iter->second<<endl;
  //     }
  //     cout<<endl;
  //
  // }



};

#endif
