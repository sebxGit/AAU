import pandas as pd
import matplotlib.pyplot as plt

# for name in ["figure1bTrajectory", "Circadian_RhythmTrajectory", "COVID19_SEIHR__10000Trajectory"]:
for name in ["COVID19_SEIHR__10000Trajectory"]:
    df = pd.read_csv(f"c:/Users/sebas/OneDrive/Billeder/Dokumenter/GitHub/AAU/SelectedTopicsInProgramming/ExamProject/figures/{name}.csv")

    plt.figure(figsize=(10, 6))

    last_column = df.columns[-1]

    if name == "COVID19_SEIHR__10000Trajectory":
        df["H"] = df["H"].apply(lambda x: x*1000)
        df = df.rename(columns={"H": "H*1000"})

    x = df[last_column]

    for column in df.columns[:-1]:
        plt.plot(x, df[column], label=column)

    plt.xlabel('Time')
    plt.ylabel('Value')

    plt.title(name[:-10])

    plt.legend()
    plt.savefig(f"c:/Users/sebas/OneDrive/Billeder/Dokumenter/GitHub/AAU/SelectedTopicsInProgramming/ExamProject/figures/{name}")
    # plt.show()