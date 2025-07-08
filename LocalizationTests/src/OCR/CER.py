import numpy as np

def main():
    str1 = "Zorro"
    str2 = "Zorra" 

    modifications = Levensthein(str1, str2)
    print("Mods: ", modifications)
    print("CER: ", modifications / len(str1))

    print("optimizado: ", Levenshtein_memory(str1, str2))
   
def Levensthein(str1, str2):
    l = np.zeros((len(str1)+1, len(str2)+1), dtype=int)
    for i in range(len(str1)+1):
        l[i][0] = i
    for j in range(len(str2)+1):
        l[0][j] = j

    for i in range(1, len(str1)+1):
        for j in range(1, len(str2)+1):
            if str1[i-1] == str2[j-1]:
                l[i][j] = l[i-1][j-1]
            else:
                l[i][j] = min(l[i-1][j] + 1,    # Deletion
                              l[i][j-1] + 1,    # Insertion
                              l[i-1][j-1] + 1)  # Substitution
    return l[len(str1)][len(str2)]
      
def Levenshtein_memory(str1, str2):
    shape = max(len(str1), len(str2)) + 1
    l = np.zeros(shape, dtype=int)
    for i in range(shape):
        l[i] = i
    
    (short, long) = (str1, str2) if len(str1) < len(str2) else (str2, str1)
    
    for i in range(0,len(short)):
        diag = l[0]
        l[0] = i + 1
        for j in range(1, shape):
            aux = l[j]
            if(short[i] == long[j-1]):
                l[j] = diag
            else:
                l[j] = min(l[j-1] + 1,    # Insertion
                           l[j] + 1,      # Deletion
                           diag + 1)
            diag = aux
    
    return l[shape-1]

def print_table(str1, str2, t):
    print("   # ", end = '')
    for i in str2:
        print(f"{i} ", end = '')
    print()
    print(f"# {t[0]}")
    for i in range(len(str1)):
        print(str1[i], t[i+1])

if __name__ == "__main__":
    main()