# Cmd_Frame

命令帧

```
struct Cmd_Frame{
  bool result=false;
  uint16_t id=0;
  CMDTYPE type=CMD_SYN;
  String addr_t="0000";
  String addr_s="0000";
  String cmd="";
  String data="";
  int status=0;
  uint16_t crc=0;
  void out(String _d);
};
```

|  名称  | 默认值  |                 功能                 |
| ------ | ------- | ------------------------------------ |
| result | false   | 帧是否有效                           |
| id     | 0       | 帧的id值                             |
| type   | CMD_SYN | CMD_SYN标示命令帧，CMD_ACK标示应答帧 |
| addr_t | "0000"  | 目标地址                             |
| addr_s | "0000"  | 源地址                               |
| cmd    | ""      | 命令                                 |
| data   | ""      | 参数或数据                           |
| status | 0       | 帧状态                               |
| crc    | 0       | crc校验值                            |

> Cmd_Frame提供一个`void out(String _d)`方法，将内容附加到data中
