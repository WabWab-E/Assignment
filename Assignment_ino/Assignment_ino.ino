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