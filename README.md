# 창의공학 양방향 통신 과제

## 아두이노 코드

```ino
void setup(){
    Serial.begin(9600);
    pinMode(13, OUTPUT);
    }

double th(int v) {
    double t;

    t = log(((10240000/v) - 10000));
    t = 1 /(0.001129148 + (0.> 000234125*t) + (0.0000000876741*t*t*t));
    t = t - 273.15;

    return t;
}

int dly;
void loop(){
    int a=analogRead(A0);
    Serial.println(th(a));

    if(Serial.available()>0){
    dly = (Serial.readString()).toInt();
    }

    digitalWrite(13, HIGH);
    delay(dly);
    digitalWrite(13, LOW);
    delay(dly);
}
```

## 프로세싱 코드

```processing
import processing.serial.*;
import processing.net.*;

Serial p;
Server s;
Client c;

void setup() {
    s = new Server(this,12345);
    p = new Serial(this,"COM3",9600);
}

String msg;

void draw() {
    c = s.available();
    if (c!=null) {
        String m = c.readString();
        if (m.indexOf("PUT")==0) {
            int n = m.indexOf("\r\n\r\n")+4;
            m = m.substring(n);
            m += '\n';
            print(m);
            p.write(m);
        }
        else if (m.indexOf("GET")==0) {
            if (msg!=null) {
                c.write("HTTP/1.1 200 OK\r\n");
                c.write("Content-length: " + msg.length() + " \r\n\r\n");
                c.write(msg);
            }
        }
    }
    if (p.available()>0) {
        String m = p.readStringUntil('\n');
        if (m!=null) {
            msg = m;
            print(m);
        }
    }
}
```
