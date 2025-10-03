# NeuralNetDuino
Simulación de red neuronal con placa tipo Arduino Uno para uso didáctico.

<html>
<body lang="es-ES" link="#000080" vlink="#800000" dir="ltr">
<h3 class="western">Idea general</h3>
<ul>
	<li><p><strong>Neuronas simuladas en el Arduino</strong>:</p>
	<ul>
		<li><p>Cada &quot;neurona&quot; recibe señales analógicas de
		sensores (ejemplo: potenciómetros, fotorresistencias, sensores de
		temperatura, etc.).</p>
		<li><p>Cada neurona procesa sus entradas con un &quot;peso&quot; y
		un &quot;umbral&quot;.</p>
		<li><p>Si la suma ponderada de las entradas supera el umbral → la
		salida se activa (LED encendido = 1).</p>
		<li><p>Si no → la salida se apaga (LED apagado = 0).</p>
	</ul>
	<li><p><strong>Interconexión</strong>:</p>
	<ul>
		<li><p>La salida de una neurona puede ser usada como entrada
		digital para otra.</p>
		<li><p>Esto simula cómo una red neuronal propaga información.</p>
	</ul>
</ul>
<h3 class="western">Ejemplo práctico</h3>
<p>Supongamos que tenemos <strong>3 neuronas</strong> conectadas:</p>
<ul>
	<li><p><strong>Neurona 1</strong>: recibe señales analógicas de
	dos sensores de luz (A0, A1). Su salida va a un LED en el pin 8 (led
	blanco).</p>
	<li><p><strong>Neurona 2</strong>: recibe señales de un sensor de
	luz (A2) y también de la salida de la Neurona 1. Su salida va al
	LED en pin 9 (led azul).</p>
	<li><p><strong>Neurona 3</strong>: integra las salidas de la Neurona
	1 y 2, y enciende un LED “final” en el pin 10 (led rojo).</p>
</ul>
<h3 class="western">Código Arduino</h3>
<pre class="western"><code class="western">// Simulación de una pequeña red neuronal en Arduino UNO</code>
<code class="western">// Cada neurona recibe entradas, aplica pesos, umbral y produce salida binaria</code>

<code class="western">// Definimos pines de entrada analógica</code>
<code class="western">const int sensor1 = A0;   // Potenciómetro o fotorresistencia</code>
<code class="western">const int sensor2 = A1;  </code>
<code class="western">const int sensor3 = A2;  </code>

<code class="western">// Salidas digitales (LEDs para visualizar actividad de neuronas)</code>
<code class="western">const int ledN1 = 8;      // </code><code class="western">led blanco</code>
<code class="western">const int ledN2 = 9;      // </code><code class="western">led azul</code>
<code class="western">const int ledN3 = 10;     // </code><code class="western">led rojo</code>

<code class="western">// Pesos y umbrales (ajustables para ver comportamientos diferentes)</code>
<code class="western">float w1[] = {0.5, 0.5};  // pesos de Neurona 1</code>
<code class="western">float threshold1 = 300;   </code>

<code class="western">float w2[] = {0.7, 0.4};  // pesos de Neurona 2</code>
<code class="western">float threshold2 = 400;   </code>

<code class="western">float w3[] = {0.6, 0.6};  // pesos de Neurona 3</code>
<code class="western">float threshold3 = 1;     // Como solo recibe señales binarias, umbral bajo</code>

<code class="western">// Variables para salidas de neuronas</code>
<code class="western">int outN1 = 0;</code>
<code class="western">int outN2 = 0;</code>
<code class="western">int outN3 = 0;</code>

<code class="western">void setup() {</code>
<code class="western">  </code><code class="western">pinMode(ledN1, OUTPUT);</code>
<code class="western">  </code><code class="western">pinMode(ledN2, OUTPUT);</code>
<code class="western">  </code><code class="western">pinMode(ledN3, OUTPUT);</code>
<code class="western">  </code><code class="western">Serial.begin(9600);</code>
<code class="western">}</code>

<code class="western">void loop() {</code>
<code class="western">  </code><code class="western">// Lectura de sensores</code>
<code class="western">  </code><code class="western">int s1 = analogRead(sensor1);</code>
<code class="western">  </code><code class="western">int s2 = analogRead(sensor2);</code>
<code class="western">  </code><code class="western">int s3 = analogRead(sensor3);</code>

<code class="western">  </code><code class="western">// --- Neurona 1 ---</code>
<code class="western">  </code><code class="western">float sum1 = s1 * w1[0] + s2 * w1[1];</code>
<code class="western">  </code><code class="western">outN1 = (sum1 &gt; threshold1) ? 1 : 0;</code>
<code class="western">  </code><code class="western">digitalWrite(ledN1, outN1);</code>

<code class="western">  </code><code class="western">// --- Neurona 2 ---</code>
<code class="western">  </code><code class="western">float sum2 = s3 * w2[0] + outN1 * 1023 * w2[1]; // salida de N1 afecta a N2</code>
<code class="western">  </code><code class="western">outN2 = (sum2 &gt; threshold2) ? 1 : 0;</code>
<code class="western">  </code><code class="western">digitalWrite(ledN2, outN2);</code>

<code class="western">  </code><code class="western">// --- Neurona 3 ---</code>
<code class="western">  </code><code class="western">float sum3 = outN1 * w3[0] + outN2 * w3[1];</code>
<code class="western">  </code><code class="western">outN3 = (sum3 &gt; threshold3) ? 1 : 0;</code>
<code class="western">  </code><code class="western">digitalWrite(ledN3, outN3);</code>

<code class="western">  </code><code class="western">// Mostrar en Serial lo que ocurre</code>
<code class="western">  </code><code class="western">Serial.print(&quot;S1:&quot;); Serial.print(s1);</code>
<code class="western">  </code><code class="western">Serial.print(&quot; S2:&quot;); Serial.print(s2);</code>
<code class="western">  </code><code class="western">Serial.print(&quot; S3:&quot;); Serial.print(s3);</code>
<code class="western">  </code><code class="western">Serial.print(&quot; | N1:&quot;); Serial.print(outN1);</code>
<code class="western">  </code><code class="western">Serial.print(&quot; N2:&quot;); Serial.print(outN2);</code>
<code class="western">  </code><code class="western">Serial.print(&quot; N3:&quot;); Serial.println(outN3);</code>

<code class="western">  </code><code class="western">delay(200); // pequeña pausa para </code><code class="western">evitar sobrecargar el controlador</code>
<code class="western">}</code></pre><h3 class="western">
Cómo usarlo</h3>
<ul>
	<li><p>Conecta <strong>3 </strong><strong>fotoresistencias</strong>
	(o potenciómetros, sensores, etc.) en A0, A1 y A2.</p>
	<li><p>Conecta LEDs con resistencias a los pines 8, 9 y 10.</p>
	<li><p>Gira los potenciómetros o cambia la intensidad de luz en los
	sensores → verás cómo los LEDs representan la <strong>activación
	neuronal</strong>.</p>
	<li><p>Puedes cambiar los <strong>pesos y umbrales</strong> en el
	código para experimentar diferentes comportamientos (ej. neuronas
	más “sensibles” o más “exigentes”).</p>
</ul>
<h2 class="western">Materiales</h2>
<ul>
	<li><p>Arduino UNO o clon compatible</p>
	<li><p>3 fotoresistencias (o potenciometros u otros sensores
	analógicos)</p>
	<li><p>3 LEDs con sus resistencias (220 Ω aprox.)</p>
	<li><p>Protoboard y cables</p>
</ul>
<h2 class="western">Conexiones</h2>
<ul>
	<li><p><strong>Entradas</strong>:</p>
	<ul>
		<li><p>fotoresistencia 1 → A0</p>
		<li><p>fotoresistencia 2 → A1</p>
		<li><p>fotoresistencia 3 → A2</p>
	</ul>
	<li><p><strong>Salidas (neuronas)</strong>:</p>
	<ul>
		<li><p>LED Neurona 1 → pin 8</p>
		<li><p>LED Neurona 2 → pin 9</p>
		<li><p>LED Neurona 3 → pin 10</p>
	</ul>
</ul>
<h2 class="western"> Lógica del sistema</h2>
<ol>
	<li><p><strong>Neurona 1</strong>: combina señales de A0 y A1 →
	enciende LED 1 si supera su umbral.</p>
	<li><p><strong>Neurona 2</strong>: combina señal de A2 y la salida
	de N1 → enciende LED 2.</p>
	<li><p><strong>Neurona 3</strong>: integra las salidas de N1 y N2 →
	enciende LED 3 (salida final).</p>
</ol>
<h2 class="western">Explicación visual para la clase</h2>
<ul>
	<li><p>Cambia la intesidad de lud que incide en las
	fotoresistencias:</p>
	<ul>
		<li><p>Los LEDs se encienden solo cuando las entradas <strong>superan
		el umbral</strong> → como una neurona que &quot;dispara&quot; (1)
		o se queda inactiva (0).</p>
	</ul>
	<li><p>Observa cómo <strong>la salida de una neurona influye en
	otra</strong> → simulación simple de red neuronal.</p>
	<li><p>Se ve claro que <strong>las neuronas procesan entradas,
	tienen un umbral y generan una salida binaria</strong>.</p>
</ul>
<p>Con esto ya puedes <strong>mostrar en vivo cómo funciona una red
neuronal básica</strong>:</p>
<ul>
	<li><p>Las entradas se integran,</p>
	<li><p>hay un <strong>umbral</strong> de disparo,</p>
	<li><p>y las <strong>salidas se propagan</strong> a otras neuronas.</p>
</ul>
<p>Seguro que la praćtica le gustará a tus alumnos y les ayudará a
comprender el funcionamiento de una red neural con un ejempo físico.</p>
<p style="line-height: 100%; margin-bottom: 0cm"><br/>

</p>
</body>
</html>
