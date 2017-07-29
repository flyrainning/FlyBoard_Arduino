
#include "GPIO.h"



	GPIO::GPIO(){

	}
	GPIO::GPIO(String &_pin){
		int __pin=_pin.toInt();
		bind(__pin);
	}
	GPIO::GPIO(int _pin){
		bind(pin);
	}
	void GPIO::bind(int _pin){
		pin=_pin;
		output();
	}
	void GPIO::A(){
		is_digital=false;
	}
	void GPIO::D(){
		is_digital=true;
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
	bool GPIO::isHigh(){		//是否是高电平
		return (get()==HIGH)?true:false;
	}
	bool GPIO::isLow(){		//是否是低电平
		return (get()==LOW)?true:false;
	}


	bool GPIO::waitHigh(long max_ms){
		return waitFor(HIGH,max_ms);
	}

	bool GPIO::waitLow(long max_ms){
		return waitFor(LOW,max_ms);
	}
	bool GPIO::waitFor(int wait,long max_ms){
		bool res=true;
		while(get() != wait){
			//wmsleep(5);
			if (max_ms>=0){
				max_ms--;
				if (max_ms==0){
					res=false;
					break;
				}
			}
			delay(1);
		}
		return res;
	}
