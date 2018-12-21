

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int maxValue = 0;
int minValue = 0;
int const arr_size = 192;
int sample[arr_size];

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);

}

void loop() {
  // read the value from the sensor:
 int i;
  for (i = 0; i < arr_size; i = i + 1) {
  sensorValue = analogRead(sensorPin);

  float value = (float)sensorValue;
  value /= 1023.0;
  value *= 5000; // convert value in mv between 0 to 5000
  sensorValue = (int)value;
  //  Serial.println(sensorValue);

 
    sample[i] = sensorValue;
  }
  Serial.println(max_value_in_arr(sample, arr_size));
  
}

int max_value_in_arr(int sample[], int size)
{ 
  maxValue = sample[0];
  int i = 0;
  for (i = 0; i < arr_size; i++)
  {
    if (sample[i] > maxValue)
    {
      maxValue = sample[i];
    }
  }
  return maxValue;
}
