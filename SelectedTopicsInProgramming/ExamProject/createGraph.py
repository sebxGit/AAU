import pandas as pd
import matplotlib.pyplot as plt

for name in ["trajectory", "trajectory2", "trajectory3"]:
    df = pd.read_csv("c:/Users/sebas/OneDrive/Billeder/Dokumenter/GitHub/AAU/SelectedTopicsInProgramming/ExamProject/{name}.csv")

    plt.figure(figsize=(10, 6))

    last_column = df.columns[-1]

    x = df[last_column]

    for column in df.columns[:-1]:
        plt.plot(x, df[column], label=column)

    plt.xlabel('Time')
    plt.ylabel('Value')

    plt.title('Figure 1b')

    plt.legend()
    plt.savefig(f"c:/Users/sebas/OneDrive/Billeder/Dokumenter/GitHub/AAU/SelectedTopicsInProgramming/ExamProject/{name}")
    # plt.show()