import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV files
df1 = pd.read_csv('player1Games.csv', header=None)
df2 = pd.read_csv('player5Games.csv', header=None)
# df3 = pd.read_csv('player5Games.csv', header=None)

# Transpose the dataframes
df1 = df1.T
df2 = df2.T
# df3 = df3.T

# Plot the data for Player 1
plt.figure()
plt.plot(df1, color='red')
plt.title('All Games for Optimal Chart')
plt.xlabel('Turn')
plt.ylabel('Balance')

# Plot the data for Player 2
plt.figure()
plt.plot(df2, color='orange')
plt.title('All Games for Card Counting @ thresh = 0.685')
plt.xlabel('Turn')
plt.ylabel('Balance')

# # Plot the data for Player 3
# plt.figure()
# plt.plot(df3, color='orange')
# plt.title('All Games for Card Counting @ thresh = 0.685')
# plt.xlabel('Turn')
# plt.ylabel('Balance')

# Create a new figure for the combined plot
plt.figure()

# Define the dataframes and their corresponding colors and labels
dataframes = [df1, df2]
colors = ['red', 'orange']
labels = ['Optimal Chart', 'Card Count @ thresh = 0.685']

# Plot the data for each player on the same graph
for df, color, label in zip(dataframes, colors, labels):
    for i in range(len(df.columns)):
        if i == 0:
            # Only label the first line of each dataframe
            plt.plot(df.iloc[:, i], color=color, label=label)
        else:
            plt.plot(df.iloc[:, i], color=color)

# Set the title and labels for the combined plot
plt.title('All Games for All Strategies')
plt.xlabel('Turn')
plt.ylabel('Balance')

# Add a legend to the combined plot
plt.legend()

# Show the plots
plt.show()