# OpenMP Basics
Computación Paralela y Distribuida
## ¿Cómo correr?
```bash
docker-compose run --build --rm -it development
```
## Preguntas
### Ejercicio 1
#### ¿Por qué al ejecutar su código los mensajes no están desplegados en orden?
Porque los threads se ejecutan de manera paralela, es decir, no se puede predecir el orden en el que se ejecutarán.