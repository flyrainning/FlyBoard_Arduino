
#include "GPIO.h"



	GPIO::GPIO(){

	}
	GPIO::GPIO(String &_pin){
		int __pin=_pin.toInt();
		load(__pin);
	}
	GPIO::GPIO(int _pin){
		load(pin);
	}
	void GPIO::load(int _pin){
		pin=_pin;
		output();
	}
	void GPIO::in(){
		input();
	}
	void GPIO::input(){
		dir=INPUT;
		pinMode(pin, dir);
	}
	void GPIO::output(){
		dir=OUTPUT;
		pinMode(pin, dir);
	}
	void GPIO::out(){
		output();
	}
	void GPIO::pullup(){
		input_pullup();
	}
	void GPIO::input_pullup(){
		dir=INPUT_PULLUP;
		pinMode(pin, dir);
	}

	void GPIO::set(char c){
		 if (c=='0'){
			 set(0);
		 }else{
			 set(1);
		 };
	}
	void GPIO::set(String c){
		int _c=c.toInt();
			 set(_c);
	}
	void GPIO::set(int c){
		 if (is_digital){
			 digitalWrite(pin,c);
		 }else{
			 analogWrite(pin,c);
		 }
	}
	int GPIO::get(){
		int res=0;
		if (is_digital){
			res=digitalRead(pin);
		}else{
			res=analogRead(pin);
		}
		return res;
	}
	void GPIO::high(){
			 digitalWrite(pin,HIGH);
	}
	void GPIO::low(){
			 digitalWrite(pin,LOW);
	}
	bool GPIO::isHIGH(){		//是否是高电平
		return (get()==HIGH)?true:false;
	}
	bool GPIO::isLOW(){		//是否是低电平
		return (get()==LOW)?true:false;
	}


	bool GPIO::waitHIGH(long mx){
		return waitFor(HIGH,mx);
	}

	bool GPIO::waitLOW(long mx){
		return waitFor(LOW,mx);
	}
	bool GPIO::waitFor(int wait,long mx){
		bool res=true;
		while(get() != wait){
			//wmsleep(5);
			if (mx>=0){
				mx--;
				if (mx==0){
					res=false;
					break;
				}
			}
		}
		return res;
	}
