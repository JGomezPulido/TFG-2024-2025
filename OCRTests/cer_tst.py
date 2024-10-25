import jiwer

reference = ["i can spell", "i hope" , "a"]
hypothesis = ["i ka cpell", "i hop"]

error = jiwer.cer(reference, hypothesis)

# if you also want the alignment
output = jiwer.process_characters(reference, hypothesis)
error = output.cer
print(error)