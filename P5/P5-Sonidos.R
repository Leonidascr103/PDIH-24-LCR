# install.packages('tuneR', dep=TRUE)
# install.packages('seewave', dep=TRUE)
# install.packages('soundgen', dep=TRUE)

library(tuneR)
library(seewave)
#library(soundgen)
library(audio)

# establecer el path concreto en cada caso a la carpeta de trabajo
setwd("/Users/Leon/OneDrive/Escritorio/2023-2024/PDIH/S5-sonidos/")

#Ejercicios de funciones:

# Leer dos ficheros de sonido (WAV o MP3) de unos pocos segundos de duración cada uno
sonido1 <- readWave('nombre.wav')
sonido2 <- readWave('apellido.wav')

listen(sonido1)
listen(sonido2)

# Dibujar la forma de onda de ambos sonidos
f <- sonido1@samp.rate

oscillo(sonido1,f=f)

f <- sonido2@samp.rate

oscillo(sonido2,f=f)

# Obtener la información de las cabeceras de ambos sonidos
str(sonido1)
str(sonido2)

# Unir ambos sonidos en uno nuevo
sonido_combinado <- pastew(sonido2, sonido1, output="Wave")

# Reproducir la señal obtenida
f <- sonido_combinado@samp.rate
listen(sonido_combinado, f=f)

#Dibujar sonido combinado resultado
oscillo(sonido_combinado,f=f)

#Aplicar el filtrado
sonido_combinado_f <-fir(wave = sonido_combinado,
    from = 1000, # lower bound frequency in Hz
    to = 2000, # upper bound frequency in Hz
    bandpass = TRUE,
    output = "Wave")

#Sacar el espectrograma de comparación
spectro(wave = sonido_combinado)
spectro(wave = sonido_combinado_f)

listen(sonido_combinado, f=f)

oscillo(sonido_combinado,f=f)

listen(sonido_combinado_f, f=f)

oscillo(sonido_combinado_f,f=f)

sonido_combinado_f <-normalize(sonido_combinado_f, unit="16", center = TRUE, level = 1)

# Almacenar la señal combinada como un nuevo fichero WAV, denominado “mezcla.wav”
writeWave(sonido_combinado_f, file.path("mezcla.wav"))

resultado <- readWave('mezcla.wav')

listen(resultado, f=f)

# Cargar un nuevo archivo de sonido
nuevo_sonido <- readWave('oveja.wav')

f <- nuevo_sonido@samp.rate

# Aplicarle eco
nuevo_sonido_eco <- echo(nuevo_sonido, f=f, amp=c(0.8, 0.5, 0.1), delay=c(0.5,1,1.5))

listen(nuevo_sonido_eco, f=f)

# Dibujar el sonido invertido con eco
oscillo(nuevo_sonido_eco, f=f)

# Darle la vuelta al sonido (invertir el sonido)
nuevo_sonido_eco_invertido <- revw(nuevo_sonido_eco, f=nuevo_sonido@samp.rate, output="Wave")

#Normalizarlo
nuevo_sonido_eco_invertido@left <- 10000 * nuevo_sonido_eco_invertido@left

# Dibujar el sonido invertido con eco
oscillo(nuevo_sonido_eco_invertido, f=f)

listen(nuevo_sonido_eco_invertido, f=f)

# Almacenar la señal obtenida como un fichero WAV denominado “alreves.wav”
writeWave(nuevo_sonido_eco_invertido, file.path("alreves.wav"))

resultado2 <- readWave('alreves.wav')

listen(resultado2)

