import json
def analysis(info_:str):
    info=json.loads(info_)
    print("温度：",info['temperature'],"度，湿度：",info['humidity'],"%")

analysis(info_=input("请输入接收的json文本："))