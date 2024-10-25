import jiwer

reference = ["i can spell", "i hope"]
hypothesis = ["i can spell", "i hope"]

error = jiwer.cer(reference, hypothesis)
# if you also want the alignment
output = jiwer.process_characters(reference, hypothesis)
error = output.cer
print(error)
