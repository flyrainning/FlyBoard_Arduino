

class cmd_class{

public:

  static void cmd1(Cmd_Frame &input,Cmd_Frame &output){
    String p=input.data;

    output.out("I'm cmd1");
    output.data+=" receive "+p;
  }


};

void cmd2(Cmd_Frame &input,Cmd_Frame &output){
  String p=input.data;
  output.out("I'm cmd2");
  output.out(" receive "+p);

}
void cmd3(Cmd_Frame &input,Cmd_Frame &output){
  String p=input.data;
  output.out("I'm cmd3");
  output.out(" receive "+p);

}
void callback(Cmd_Frame &input){
  String p=input.data;
  if (p=="something"){
    //do something
  }

}
