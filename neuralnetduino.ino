// Simulación de una pequeña red neuronal en Arduino UNO
// Cada neurona recibe entradas, aplica pesos, umbral y produce salida binaria
// Definimos pines de entrada analógica
const int sensor1 = A0;   // Potenciómetro o fotorresistencia
const int sensor2 = A1;  
const int sensor3 = A2;  


// Salidas digitales (LEDs para visualizar actividad de neuronas)
const int ledN1 = 8;      // led blanco
const int ledN2 = 9;      // led azul
const int ledN3 = 10;     // led rojo


// Pesos y umbrales (ajustables para ver comportamientos diferentes)
float w1[] = {0.5, 0.5};  // pesos de Neurona 1
float threshold1 = 300;   


float w2[] = {0.7, 0.4};  // pesos de Neurona 2
float threshold2 = 400;   


float w3[] = {0.6, 0.6};  // pesos de Neurona 3
float threshold3 = 1;     // Como solo recibe señales binarias, umbral bajo


// Variables para salidas de neuronas
int outN1 = 0;
int outN2 = 0;
int outN3 = 0;


void setup() {
  pinMode(ledN1, OUTPUT);
  pinMode(ledN2, OUTPUT);
  pinMode(ledN3, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  // Lectura de sensores
  int s1 = analogRead(sensor1);
  int s2 = analogRead(sensor2);
  int s3 = analogRead(sensor3);


  // --- Neurona 1 ---
  float sum1 = s1 * w1[0] + s2 * w1[1];
  outN1 = (sum1 > threshold1) ? 1 : 0;
  digitalWrite(ledN1, outN1);


  // --- Neurona 2 ---
  float sum2 = s3 * w2[0] + outN1 * 1023 * w2[1]; // salida de N1 afecta a N2
  outN2 = (sum2 > threshold2) ? 1 : 0;
  digitalWrite(ledN2, outN2);


  // --- Neurona 3 ---
  float sum3 = outN1 * w3[0] + outN2 * w3[1];
  outN3 = (sum3 > threshold3) ? 1 : 0;
  digitalWrite(ledN3, outN3);


  // Mostrar en Serial lo que ocurre
  Serial.print("S1:"); Serial.print(s1);
  Serial.print(" S2:"); Serial.print(s2);
  Serial.print(" S3:"); Serial.print(s3);
  Serial.print(" | N1:"); Serial.print(outN1);
  Serial.print(" N2:"); Serial.print(outN2);
  Serial.print(" N3:"); Serial.println(outN3);


  delay(200); // pequeña pausa para evitar sobrecargar el controlador
}
