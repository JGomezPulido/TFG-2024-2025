import jiwer
import glob
import os

# Directorio donde están los archivos
directory = "path/to/files"  # Cambia esta ruta al directorio donde están los archivos

# Obtener listas de archivos para reference y hypothesis
reference_files = sorted(glob.glob(os.path.join(directory, "*-gt.txt")))
hypothesis_files = sorted(glob.glob(os.path.join(directory, "*.txt")))

# Filtrar los archivos de hipótesis para excluir aquellos que son de referencia
hypothesis_files = [f for f in hypothesis_files if not f.endswith("-gt.txt")]

# Emparejar archivos según el número
cer_results = {}  # Diccionario para almacenar el CER de cada par

for ref_file in reference_files:
    # Obtener el número del archivo de referencia
    file_number = os.path.basename(ref_file).split("-gt.txt")[0]
    # Buscar el archivo de hipótesis correspondiente
    hyp_file = os.path.join(directory, f"{file_number}.txt")

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
        print(f"Archivo de hipótesis no encontrado para {file_number}")

# Mostrar todos los resultados
print("Resultados CER:", cer_results)
