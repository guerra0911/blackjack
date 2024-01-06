import pandas as pd
import matplotlib.pyplot as plt

# List of CSV files
csv_files = ['player1Data.csv', 'player2Data.csv', 'player3Data.csv', 'player4Data.csv', 'player5Data.csv']

# Initialize lists to store dataframes
dfs_avg = []
dfs_turn = []

# Define colors for each player
colors = ['red', 'green', 'blue', 'purple', 'orange']

# Define labels for each player
labels = ['Optimal Chart', 'Soft 17', 'Hard 17', 'Card Count @ thresh = 0.6775', 'Card Count @ thresh = 0.685']

# Read each CSV file
for csv_file in csv_files:
    df = pd.read_csv(csv_file, header=None)
    dfs_avg.append(df.iloc[0])  # Store average balance
    dfs_turn.append(df.iloc[1])  # Store frequency of turn

# # Plot average balance and frequency of turn for each player
# for i, (df_avg, df_turn) in enumerate(zip(dfs_avg, dfs_turn)):
#     plt.figure(i*2)  # Create a new figure for average balance
#     plt.plot(df_avg, color=colors[i])
#     plt.title(f'{labels[i]} Average Balance')
#     plt.xlabel('Turn')
#     plt.ylabel('Average Balance')

#     plt.figure(i*2 + 1)  # Create a new figure for frequency of turn
#     plt.scatter(range(len(df_turn)), df_turn, color=colors[i], s=10)  # Reduced dot size
#     plt.title(f'{labels[i]} % of Cycles that Reach Turn')
#     plt.xlabel('Turn')
#     plt.ylabel('% Cycles')

# Plot average balance for all players
plt.figure(len(csv_files)*2)  # Create a new figure for average balance of all players
for i, df_avg in enumerate(dfs_avg):
    plt.plot(df_avg, color=colors[i], label=labels[i])
plt.title('Average Balance for All Players')
plt.xlabel('Turn')
plt.ylabel('Average Balance')
plt.legend()

# Plot frequency of turn for all players
plt.figure(len(csv_files)*2 + 1)  # Create a new figure for frequency of turn of all players
for i, df_turn in enumerate(dfs_turn):
    plt.scatter(range(len(df_turn)), df_turn, color=colors[i], label=labels[i], s=10)  # Reduced dot size
plt.title('% Cycles that Reach Turn for All Players')
plt.xlabel('Turn')
plt.ylabel('% Cycles')
plt.legend()

# Display all plots
plt.show()