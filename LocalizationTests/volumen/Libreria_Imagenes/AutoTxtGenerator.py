import os
images_dir = ".\\Imagenes\\"
texts_dir = ".\\Textos\\"

for root, _, files in os.walk(images_dir):
    for filename in files:
        if filename.endswith(".jpg"):
            relative_path = os.path.relpath(root, images_dir)

            target_dir = os.path.join(texts_dir, relative_path)
            os.makedirs(target_dir, exist_ok=True)
            
            txt_filename = os.path.splitext(filename)[0] + ".txt"
            txt_filepath = os.path.join(target_dir, txt_filename)
            
            if not os.path.exists(txt_filepath):
                with open(txt_filepath, 'w') as txt_file:
                    txt_file.write("") 
                print(f"Created: {txt_filepath}")
            else:
                print(f"Already exists: {txt_filepath}")