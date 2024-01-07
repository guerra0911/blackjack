import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

#Player Data Files
csv_files = ['player1Data.csv', 'player2Data.csv', 'player3Data.csv', 'player4Data.csv', 'player5Data.csv',
             'player6Data.csv', 'player7Data.csv', 'player8Data.csv', 'player9Data.csv', 'player10Data.csv',
             'player11Data.csv', 'player12Data.csv', 'player13Data.csv', 'player14Data.csv', 'player15Data.csv',
             'player16Data.csv', 'player17Data.csv', 'player18Data.csv', 'player19Data.csv', 'player20Data.csv',
             'player21Data.csv', 'player22Data.csv', 'player23Data.csv', 'player24Data.csv', 'player25Data.csv']

# Define labels for each player
labels = ['0.604', '0.608', '0.612', '0.616', '0.620', 
          '0.624', '0.628', '0.632', '0.636', '0.640', 
          '0.644', '0.648', '0.652', '0.656', '0.660', 
          '0.664', '0.668', '0.672', '0.676', '0.680', 
          '0.684', '0.688', '0.692', '0.696', '0.700']


# Initialize lists to store dataframes
dfs_avg = []
dfs_turn = []

# Define colors for each player
colors = plt.cm.get_cmap('rainbow', len(csv_files))

# Read each CSV file
for csv_file in csv_files:
    df = pd.read_csv(csv_file, header=None)
    dfs_avg.append(df.iloc[0])  # Store average balance
    dfs_turn.append(df.iloc[1])  # Store frequency of turn

# Plot average balance for all players
plt.figure(figsize=(10, 6))  # Create a new figure for average balance of all players
for i, df_avg in enumerate(dfs_avg):
    plt.plot(df_avg, color=colors(i), label=labels[i])
plt.title('Average Balance for All Players')
plt.xlabel('Turn')
plt.ylabel('Average Balance')
plt.legend()

# Plot frequency of turn for all players
plt.figure(figsize=(10, 6))  # Create a new figure for frequency of turn of all players
for i, df_turn in enumerate(dfs_turn):
    plt.scatter(range(len(df_turn)), df_turn, color=colors(i), label=labels[i], s=10)  # Reduced dot size
plt.title('% Cycles that Reach Turn for All Players')
plt.xlabel('Turn')
plt.ylabel('% Cycles')
plt.legend()

# Display all plots
plt.show()
