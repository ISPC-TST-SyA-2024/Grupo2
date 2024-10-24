#line 1 "d:\\Laura\\Carrera Telecomunicaciones\\PRIMER AÑO\\sensores y actuadores\\Grupo2\\Trabajo Practico Nº 8\\Readme.md"

![alt text](https://github.com/ISPC-TST-SyA-2024/Grupo2/blob/main/src/IoT.jpg)

## <p style="text-align: center;">SENSORES Y ACTUADORES</p>

### Profesor: **Ing. Jorge Elías Morales.**

##

### Grupo N° 2:

- Huk, Romina vanesa - [GitHub: RoHu17](https://github.com/RoHu17)
- Brizuela, Laura Analia - [GitHub: gerbena03](https://github.com/gerbena03)
- Roldán, Patricio Leandro -  [GitHub: pleroldan](https://github.com/pleroldan)
- Pantoja, Paola Natalia Alejandra - [GitHub: PaolaaPantoja](https://github.com/PaolaaPantoja)
- Paez, Tiziano Adrian - [GitHub: tpaez](https://github.com/tpaez)
- Paz, Rodolfo: [GitHub: Domi74](https://github.com/Domi74)
- Gutiérrez, Emma: [GitHub: Emygut](https://github.com/Emygut)


--- 



Este proyecto consiste en la simulación de un **Sistema de Riego Inteligente** utilizando una **ESP32** o **Arduino**, implementado en plataformas como **Wokwi** o **Proteus**. El sistema está diseñado para optimizar el uso del agua en función de las condiciones del clima y del suelo.

## Componentes principales

- **Sensor de humedad del suelo resistivo**: (YL-69, HL-69 o FC-28) para medir el nivel de humedad en el suelo.
- **Sensor de humedad del suelo capacitivo**: (V1.2) para una medición precisa de la humedad.
- **Sensor de lluvia resistivo**: (YL-83) para detectar si está lloviendo.
- **Pantalla LCD**: (16x2 o 20x4) para mostrar los valores de los sensores y el estado del sistema.
- **Bomba de agua y electroválvula**: Controladas automáticamente mediante relés u optoacopladores para activar o desactivar el riego.
- **Control de nivel de tanque de agua**: Asegura que el riego funcione solo cuando hay suficiente agua disponible.

## Lógica del sistema

- El sistema activa el riego automáticamente si el nivel de humedad del suelo es bajo y no está lloviendo.
- Si se detecta lluvia, el riego no se activará.
- La bomba y la electroválvula son controladas según las lecturas de los sensores, y el estado del sistema se visualiza en la pantalla LCD.

## Estructura del repositorio

El repositorio sigue una estructura de monorepositorio, donde cada integrante del equipo tiene asignada una tarea específica (issue). A continuación se detalla la organización de carpetas y los archivos principales del proyecto.


- A requisitos: Contiene documentos de requisitos proporcionados por el docente.  
- B investigacion: Investigaciones realizadas por el estudiantes.  
- C prototipo: Implementaciones específicas.  
- D presentacion: descripcion de lo trabajado.
# Sistema de Riego Inteligente

## Referencias

- [Video de referencia 1](https://www.youtube.com/watch?v=cqJ5fXaShP0)
- [Video de referencia 2](https://www.youtube.com/watch?v=6ODn1XrysGw)
- [Video de referencia 3](https://www.youtube.com/watch?v=mH_h1LS9wMo)
- [Video de referencia 4](https://www.youtube.com/watch?v=Wx1Vi0EPhQU)
