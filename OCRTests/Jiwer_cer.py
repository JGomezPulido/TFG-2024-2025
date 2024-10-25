import jiwer
import glob
import os
import json

# Directorios donde están los archivos
reference_directory = "path/to/reference_files"  # Cambia esta ruta al directorio de referencia (gt)
hypothesis_directory = "path/to/hypothesis_files"  # Cambia esta ruta al directorio de hipótesis

# Obtener listas de archivos de referencia y de hipótesis
reference_files = sorted(glob.glob(os.path.join(reference_directory, "*-gt.txt")))
hypothesis_files = sorted(glob.glob(os.path.join(hypothesis_directory, "*.txt")))

# Diccionario para almacenar el CER de cada par
cer_results = {}

# Emparejar archivos según el número
for ref_file in reference_files:
    # Obtener el número del archivo de referencia
    file_number = os.path.basename(ref_file).split("-gt.txt")[0]
    # Construir la ruta del archivo de hipótesis correspondiente
    hyp_file = os.path.join(hypothesis_directory, f"{file_number}.txt")

    if hyp_file in hypothesis_files:
        # Leer los contenidos de los archivos
        with open(ref_file, "r", encoding="utf-8") as ref:
            reference = ref.readlines()

        with open(hyp_file, "r", encoding="utf-8") as hyp:
            hypothesis = hyp.readlines()

        # Calcular el CER
        cer = jiwer.cer(reference, hypothesis)
        cer_results[file_number] = cer
        print(f"CER para el archivo {file_number}: {cer}")
    else:
        print(f"No se encontró archivo de hipótesis para {file_number}")

# Guardar los resultados en un archivo JSON
json_file_path = "cer_results.json"  # Nombre del archivo JSON donde se guardarán los resultados
with open(json_file_path, "w", encoding="utf-8") as json_file:
    json.dump(cer_results, json_file, indent=4)

print(f"Resultados CER guardados en {json_file_path}")
