#!/bin/bash

# Define el directorio de entrada y salida
input_dir="images"
output_dir="result"
tessdata_dir="trainingFont/trainedModel"

# Crea el directorio de salida si no existe
mkdir -p "$output_dir"

# Procesa todos los archivos .png en el directorio de entrada
for file in "$input_dir"/*.png; do
    # Extrae el nombre del archivo sin la extensión
    filename=$(basename "$file" .png)
    # Ejecuta Tesseract
    tesseract "$file" "$output_dir/$filename" --tessdata-dir "$tessdata_dir" -l Arial
done
