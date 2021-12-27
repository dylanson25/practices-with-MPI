# Producto escalar with MPI

- Elabora un programa en paralelo con MPI en C, que calcule el producto escalar o producto punto de  dos vectores de N números enteros cada uno. 

## Ejemplo

Vector A

` ` `
1 - 3 - 5 - 1 - 9 - 1
` ` `

Vector A

` ` `
1 - 2 - 3 - 4 - 5 - 6
` ` `

Producto escalar se calcula como: 

` ` `
1*1 + 3*2 + 5*3 + 7*4 + 9*5 + 11*6 
` ` `

Resultado final 

` ` `
161 
` ` `

El valor de N (recomendable mayor o igual a 1000 y que sea divisible entre el número de procesos) debe  ser definido al inicio del programa como constante y los números deben ser generados de manera  aleatoria (valores entre 0 y 50).  
Se deberán utilizar funciones para dividir y distribuir los datos a todos los procesos del comunicador  desde el proceso maestro, cada proceso esclavo generará su suma y se la enviarán al proceso maestro. 

## Indicaciones: 

- Para un valor específico de N, ejecutar el programa con al menos 5 diferentes números de  procesadores, tomar el tiempo de ejecución con cada uno y generar una gráfica de Speedup. 
- Realizar el paso anterior con al menos 3 valores diferentes de N 
