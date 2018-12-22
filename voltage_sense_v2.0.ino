

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int maxValue = 0;
int minValue = 0;
int avgValue = 0;
int rmsValue = 0;
float acVoltage = 0;
int const arr_size = 192; //9600 is default sampling rate
int sample[arr_size]; //array for storing values of every sample

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor and store it in an array:
  int i;
  unsigned long int sum = 0;
  for (i = 0; i < arr_size; i = i + 1)
  {
    sensorValue = analogRead(sensorPin);
    sample[i] = sensorValue;
    sum += sensorValue;
  }
  //    Serial.println(sum); //for displaying sum of array

  Serial.print("Vmax in milli volts: ");
  Serial.println(max_value_in_arr(sample, arr_size)); //print Vmax in milli volts
  Serial.print("Vmin in milli volts: ");
  Serial.println(min_value_in_arr(sample, arr_size)); //print Vmin in milli volts
  Serial.print("Vavg in milli volts: ");
  Serial.println(avg_value_in_arr(sum, arr_size)); //print Vavg in milli volts
  Serial.print("Vrms in milli volts: ");
  Serial.println(rms_value_in_arr(sample, arr_size)); //print Vavg in milli volts
  acVoltage = ((rms_value_in_arr(sample, arr_size) / 1000.0) * 281);
  Serial.print("Ac Voltage : ");
  Serial.println(acVoltage); //print Ac Voltage
  acVoltage = ((maxValue - 2500) / 0.0909) * 18.06932 ; //formula for finding AC RMS Voltage
  Serial.println(acVoltage); //print Ac Voltage
  Serial.println("*************************************************");

  //  delay (1000);
}
///////////////////////////////////////////////////////////function for maximum value in array
int max_value_in_arr(int sample[], int arr_size)
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
  float value = (float)maxValue;
  value /= 1023.0;
  value *= 5000; // convert value in mv between 0 to 5000
  maxValue = (int)value;
  //  Serial.println(maxValue);
  return maxValue;
}
///////////////////////////////////////////////////////////function for minimum value in array
int min_value_in_arr(int sample[], int arr_size)
{
  minValue = sample[0];
  int i = 0;
  for (i = 0; i < arr_size; i++)
  {
    if (sample[i] < minValue)
    {
      minValue = sample[i];
    }
  }
  float value = (float)minValue;
  value /= 1023.0;
  value *= 5000; // convert value in mv between 0 to 5000
  minValue = (int)value;
  //  Serial.println(minValue);
  return minValue;
}
///////////////////////////////////////////////////////////function for average value in array
int avg_value_in_arr(long int sum, int arr_size)
{
  //  Serial.println(sum);
  avgValue = sum / arr_size;
  float value = (float)avgValue ;
  value /= 1023.0;
  value *= 5000; // convert value in mv between 0 to 5000
  avgValue = (int)value;
  //  Serial.println(avgValue );
  return avgValue;
}
//////////////////////////////////////////////////////////function for rms value in array
int rms_value_in_arr(int sample[], int arr_size)
{
  int i = 0;
  float square = 0;
  float mean = 0;
  float root = 0;
  float value = 0;
  for (i = 0; i < 192; i++)
  {
    value = (float)sample[i] / 1023.0;
    value *= 5.0;
    value = value - 2.5;
    square += sq(value);
  }
  //  Serial.println(square);
  mean = square / 192.0;
  root = sqrt(mean);
  value = root;
  value *= 1000.0;
  rmsValue = (int)value;
  //  Serial.println(rmsValue);
  return rmsValue;
}
