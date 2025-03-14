import pandas as pd

df = pd.read_csv("file.txt", sep="\s+", skiprows=6, header=None)

selected_columns = df.iloc[:, [4, 3]]  # U2 (5. sütun) ve I_A (4. sütun)

selected_columns.to_csv("file.txt", index=False, header=["U2 (V)", "I_A (nA)"], sep="\t")


