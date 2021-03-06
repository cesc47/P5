PAV - P5: síntesis musical polifónica
=====================================

Obtenga su copia del repositorio de la práctica accediendo a [Práctica 5](https://github.com/albino-pav/P5) 
y pulsando sobre el botón `Fork` situado en la esquina superior derecha. A continuación, siga las
instrucciones de la [Práctica 2](https://github.com/albino-pav/P2) para crear una rama con el apellido de
los integrantes del grupo de prácticas, dar de alta al resto de integrantes como colaboradores del proyecto
y crear la copias locales del repositorio.

Como entrega deberá realizar un *pull request* con el contenido de su copia del repositorio. Recuerde que
los ficheros entregados deberán estar en condiciones de ser ejecutados con sólo ejecutar:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.sh
  make release
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A modo de memoria de la práctica, complete, en este mismo documento y usando el formato *markdown*, los
ejercicios indicados.

Ejercicios.
-----------

### Envolvente ADSR.

Tomando como modelo un instrumento sencillo (puede usar el InstrumentDumb), genere cuatro instrumentos que
permitan visualizar el funcionamiento de la curva ADSR.

* Un instrumento con una envolvente ADSR genérica, para el que se aprecie con claridad cada uno de sus
  parámetros: ataque (A), caída (D), mantenimiento (S) y liberación (R).
  
<img src="Img/mostra.png" width="640" align="center">  
  
* Un instrumento *percusivo*, como una guitarra o un piano, en el que el sonido tenga un ataque rápido, no
  haya mantenimiemto y el sonido se apague lentamente.
  - Para un instrumento de este tipo, tenemos dos situaciones posibles:
    * El intérprete mantiene la nota *pulsada* hasta su completa extinción.
    
    
	<img src="Img/piano2.png" width="640" align="center">  
    
    
    
    * El intérprete da por finalizada la nota antes de su completa extinción, iniciándose una disminución
	  abrupta del sonido hasta su finalización.
	
	
	<img src="Img/piano1.png" width="640" align="center">  
	
	
	  
  - Debera representar en esta memoria **ambos** posibles finales de la nota.
* Un instrumento *plano*, como los de cuerdas frotadas (violines y semejantes) o algunos de viento. En
  ellos, el ataque es relativamente rápido hasta alcanzar el nivel de mantenimiento (sin sobrecarga), y la
  liberación también es bastante rápida.


<img src="Img/vent.png" width="640" align="center">  



Para los cuatro casos, deberá incluir una gráfica en la que se visualice claramente la curva ADSR. Deberá
añadir la información necesaria para su correcta interpretación, aunque esa información puede reducirse a
colocar etiquetas y títulos adecuados en la propia gráfica (se valorará positivamente esta alternativa).

<img src="Img/total.png" width="640" align="center">  

### Instrumentos Dumb y Seno.

Implemente el instrumento `Seno` tomando como modelo el `InstrumentDumb`. La señal **deberá** formarse
mediante búsqueda de los valores en una tabla.

- Incluya, a continuación, el código del fichero `seno.cpp` con los métodos de la clase Seno.

**`Antes de mostrar los cambios en los ficheros, vamos a explicar el procedimiento que hemos usado:`**

<img src="Img/formula.png" width="640" align="center">  

**`Con el cálculo de f0 generamos F (frecuencia discreta) y posteriormente lo comparamos con Fn, que representa el incremento de 1/N del step generado en la tabla. Entonces, sabremos en cada momento el incremento que hay aplicar para hacer la búsqueda en la tabla.`**

**`Hemos modificado seno.h para tener acceso a dos variables necesarias para la búsqueda de los valores en la tabla. La variable F0 representará el cálculo de f0 entre fs (frecuencia de muestreo). La variable acumulat representará la suma de incrementos, donde el índice será el redondeo (round) de acumulado.`**

<img src="Img/senoh.png" width="640" align="center">  

**`En command(.) hemos añadido al código anterior el cálculo de f0 y F y la actualización de la variable acumulat (pasan a cero cuando dejamos de pulsar la nota). Lo demás es el código perteneciente a InstrumentDumb pero aplicado a nuestro nuevo instrumento.`**

<img src="Img/seno1.png" width="640" align="center">  

**`En synthesize(.) calculamos para cada muestra el incremento y lo sumamos a acumulat. Posteriormente hacemos el round tal y como hemos comentado antes (ya que al acceder a la tabla, hay que hacerlo con numeros enteros, y lo haremos redondeando al decimal más cercano).`**

<img src="Img/seno2.png" width="640" align="center"> 


- Explique qué método se ha seguido para asignar un valor a la señal a partir de los contenidos en la tabla,
  e incluya una gráfica en la que se vean claramente (use pelotitas en lugar de líneas) los valores de la
  tabla y los de la señal generada.

**`Aquí podemos observar la forma de onda en Instrument_dumb. Podemos observar que se escojen valores de fase equiespaciados 1/N.`**

<img src="Img/contenidos_tabla.png" width="640" align="center"> 

**`Aquí podemos observar la forma de onda en seno. Podemos observar que se escojen valores de fase haciendo el redondeo 'índice', tal y como se ha explicado antes.`**

<img src="Img/Contenidos_tabla_instrumentdumb.png" width="640" align="center"> 

**`Aquí podemos observar la forma de onda en Instrument_dumb. Podemos observar que se escojen valores de fase equiespaciados 1/N.`**


**`Como ampliación, hemos hecho la interpolación con la muestra anterior y posterior. Podemos observar que hay una mejora audible bastante importante.`**

<img src="Img/ampliacion_seno1.png" width="640" align="center"> 

**`Hemos hecho el mismo procedimiento que antes, pero ahora con 'anterior' y 'posterior'. Con esto, hemos conseguido hacer una interpolación.`**

<img src="Img/ampliacion_seno2.png" width="640" align="center"> 
<img src="Img/ampliacion_seno3.png" width="640" align="center"> 



### Efectos sonoros.

- Incluya dos gráficas en las que se vean, claramente, el efecto del trémolo y el vibrato sobre una señal
  sinusoidal. Deberá explicar detalladamente cómo se manifiestan los parámetros del efecto (frecuencia e
  índice de modulación) en la señal generada (se valorará que la explicación esté contenida en las propias
  gráficas, sin necesidad de *literatura*).
  
  **`Podemos aquí observar el efecto del tremolo sobre una señal. Observamos que consiste en la modificación rápida y oscilante del volumen del sonido.`**
  
  <img src="Img/tremolo.png" width="640" align="center"> 
  
  **`En la siguiente imagen podemos observar el contorno de pitch y la señal original. En la primera forma de onda, observamos la señal original sin ningún tipo de modificación. Después en la segunda forma de onda observamos el efecto del tremolo, y en la tercera el vibratto. Podemos aquí observar el efecto del vibrato sobre una señal, que consiste en variar, alternada y rápidamente, la afinación de la nota. Se puede ver que el contorno de pitch varia (solo en el caso del vibratto).`**
  
    <img src="pitch2.png" width="640" align="center"> 

 **`Este es otro ejemplo de tremolo (pero un caso que no es tan exagerado):`**
  
  <img src="Img/tremolo1.png" width="640" align="center"> 

 
 **`Su implementación en el fichero .sco:`**
 
   <img src="Img/doremi2.png" width="640" align="center"> 

  **`Este es un ejemplo donde hemos creado un efecto de vibratto respecto a unas notas que hemos configurado nosotros mismos. Las notas representan la canción 'Tu me dejaste caer' - Autor: Daddy Yankee, de los primeros 10 segundos de la canción. Aquí podemos ver la forma de onda, con su posterior implementación en el fichero .sco. Comentar que el vibratto lo hemos puesto en el canal 7, y hemos hecho servir el instrumento seno:`**
 
   <img src="Img/vibrato1.png" width="640" align="center"> 
   <img src="Img/doremi.png" width="640" align="center"> 
   <img src="Img/1.png" width="640" align="center"> 
   <img src="Img/2.png" width="640" align="center"> 



- Si ha generado algún efecto por su cuenta, explique en qué consiste, cómo lo ha implementado y qué
  resultado ha producido. Incluya, en el directorio `work/ejemplos`, los ficheros necesarios para apreciar
  el efecto, e indique, a continuación, la orden necesaria para generar los ficheros de audio usando el
  programa `synth`.

  **`Aquí podemos ver como hemos hecho el efecto de distorsión. El código es el siguiente:`**

  <img src="Img/distortion_code.png" width="640" align="center"> 

  **`Basicamente lo que hemos hecho es amplificar de tal manera que si superamos un umbral saturamos, provocando armónicos de la frecuencia fundamental, generando así distorsión en la señal.`**

      
  **`Este es el efecto:`**

<img src="distortion.png" width="640" align="center"> 


### Síntesis FM.

Construya un instrumento de síntesis FM, según las explicaciones contenidas en el enunciado y el artículo
de [John M. Chowning](https://ccrma.stanford.edu/sites/default/files/user/jc/fm_synthesispaper-2.pdf). El
instrumento usará como parámetros **básicos** los números `N1` y `N2`, y el índice de modulación `I`, que
deberá venir expresado en semitonos.

**`Cuando usamos síntesis musical, las frecuencias portadora y moduladora se llevan a la gama de las frecuencias audio (20 Hz a 20.000 Hz). Si la frecuencia moduladora es inferior a 8 Hz, el resultado de la modulación es un vibrato, pero cuando esta frecuencia se sitúa alrededor de los 20 Hz, se obtiene una modificación del timbre del sonido modulado, como descubrió Chowning. Entre estas dos frecuencias (8 y 20 Hz), se produce una transición progresiva de un efecto al otro.`**


**`Para hacer los cálculos, hemos seguido las fórmulas del paper de John M. Chowing:`**

<img src="Img/formulas.png" width="640" align="center"> 

**` El índice de modulación (d) es un parámetro que indica la desviación máxima de la frecuencia portadora en función de la moduladora.`**

- Use el instrumento para generar un vibrato de *parámetros razonables* e incluya una gráfica en la que se
  vea, claramente, la correspondencia entre los valores `N1`, `N2` e `I` con la señal obtenida.
 
 **`Para visualizar el elfecto del vibrato, utilizamos el wavesurfer ya que nos permite observar las variaciones del pitch. El resultado ha estado el siguiente:`**
 
 <img src="Img/vibrator_clarinete.png" width="640" align="center"> 
  
- Use el instrumento para generar un sonido tipo clarinete y otro tipo campana. Tome los parámetros del
  sonido (N1, N2 e I) y de la envolvente ADSR del citado artículo. Con estos sonidos, genere sendas escalas
  diatónicas (fichero `doremi.sco`) y ponga el resultado en los ficheros `work/doremi/clarinete.wav` y
  `work/doremi/campana.work`.
  
   **`Al darnos I, N1 y N2 podemos obtener las variables c y m, dando valores razonables a N1 y N2 (en la proporción que queramos para ese instrumento).`**
  
  **`Para generar sonidos variando N1, N2, I hemos adaptado instrument_fm.cpp, de manera que hemos calculado las variables 'c' y 'm' tal y como se ha explicado en las formulas anteriores. Así, hemos podido generar en syntetize la señal de salida. Aquí podemos observar como se ha programado la función command:`**
  
  <img src="Img/command.png" width="640" align="center"> 
  
 **`Aquí podemos observar como se ha programado la función syntetize:`**

<img src="Img/syntetize.png" width="640" align="center"> 

 **`Vamos variando ligeramente las notas, pero manteniendo el valor n1/n2. Aquí podemos observar unos valores como muestra de ejemplo (de aquí el cout que hemos puesto en el código):`**

<img src="Img/valores.png" width="640" align="center"> 

  **`Tal y como dice el artículo para generar un sonido tipo clarienete debemos generar el esquema de a continuación con los valores:`**
  
**` - Frecuencia de modulación = 600 Hz `**

**` - Desviación de la frecuencia de modulación = 4`**

**` - Frecuencia de la portadora = 900 Hz`**

<img src="Img/esquemaclarinete.png" width="640" align="center"> 

**`Por lo tanto podemos concluir que los valores N1, N2 e I son:`**

**` - N1 = 3`**

**` - N2 = 2`**

**` - I = 4`**

<img src="Img/declaracion.png" width="640" align="center"> 

**`Observación: Hemos dejado en el directorio work el .wav de clarinete, para que se pueda observar como suena. También hemos hecho lo mismo para la campana. El procedimiento ha sido el mimsmo, pero con unos diferentes valores de 'c' y 'm' y por lo tanto, una relación distinta entre N1 Y N2, en este caso usando numeros racionales. El resultado, está en el directorio work.`**


* También puede colgar en el directorio work/doremi otras escalas usando sonidos *interesantes*. Por
    ejemplo, violines, pianos, percusiones, espadas láser de la
	[Guerra de las Galaxias](https://www.starwars.com/), etc.
	
	
**`Observación: Hemos dejado en el directorio work el .wav de un bajo, para que se pueda observar como suena.`**

### Orquestación usando el programa synth.

Use el programa `synth` para generar canciones a partir de su partitura MIDI. Como mínimo, deberá incluir la
*orquestación* de la canción *You've got a friend in me* (fichero `ToyStory_A_Friend_in_me.sco`) del genial
[Randy Newman](https://open.spotify.com/artist/3HQyFCFFfJO3KKBlUfZsyW/about).

- En este triste arreglo, la pista 1 corresponde al instrumento solista (puede ser un piano, flautas,
  violines, etc.), y la 2 al bajo (bajo eléctrico, contrabajo, tuba, etc.).

<img src="Img/ins.png" width="640" align="center"> 

- Coloque el resultado, junto con los ficheros necesarios para generarlo, en el directorio `work/music`.
- Indique, a continuación, la orden necesaria para generar la señal (suponiendo que todos los archivos
  necesarios están en directorio indicado).

<img src="Img/term.png" width="640" align="center"> 

También puede orquestar otros temas más complejos, como la banda sonora de *Hawaii5-0* o el villacinco de
John Lennon *Happy Xmas (War Is Over)* (fichero `The_Christmas_Song_Lennon.sco`), o cualquier otra canción
de su agrado o composición. Se valorará la riqueza instrumental, su modelado y el resultado final.

**`Primero de todo, para comprobar el impacto real de hacer esta práctica, hemos creado una partitura en una aplicación (musescore). Sabiendo las notas de la melodia y los acordes, hemos generado la partitura (más o menos decente, ya que sabemos un poco de música pero tampoco demasiado). La canción es city of stars de La la Land. Este es el resultado (bastante pensado para tocar en el piano):`**

<img src="Img/p4.png" width="640" align="center"> 

<img src="Img/p1.png" width="640" align="center"> 

<img src="Img/p2.png" width="640" align="center"> 

<img src="Img/p3.png" width="640" align="center"> 

**`Una vez creada la partitura, la hemos exportado en formato .midi:`**

<img src="Img/exp.png" width="640" align="center"> 

**`La hemos convertido a formato .sco para sintetizarla:`**

<img src="Img/o2.png" width="640" align="center"> 

**`La orden para la creación es la siguiente:`**

<img src="Img/o.png" width="640" align="center"> 

**`Respecto a riqueza musical es bastante pobre, pero queríamos comprobar el real funcionamento. Si buscamos un fichero con más riqueza instrumental podemos instruentar el main theme de Hawaii5-0:`**

**`La orden es:`**

<img src="Img/comandooo.png" width="640" align="center"> 

**`Los instrumentos:`**

<img src="Img/intrumentosHawaii.png" width="640" align="center"> 

- Coloque los ficheros generados, junto a sus ficheros `score`, `instruments` y `efffects`, en el directorio
  `work/music`.
- Indique, a continuación, la orden necesaria para generar cada una de las señales usando los distintos
  ficheros.

