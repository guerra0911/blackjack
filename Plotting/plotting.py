import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV files
df1 = pd.read_csv('player1.csv', header=None, na_values=' NaN')
df2 = pd.read_csv('player2.csv', header=None, na_values=' NaN')
df3 = pd.read_csv('player3.csv', header=None, na_values=' NaN')

# Transpose the dataframes
df1 = df1.T
df2 = df2.T
df3 = df3.T

# Plot the data for Player 1
plt.figure()
plt.plot(df1, color='blue')
plt.title('Player 1: Optimal Chart')
plt.xlabel('Turn')
plt.ylabel('Balance')

# Plot the data for Player 2
plt.figure()
plt.plot(df2, color='green')
plt.title('Player 2: Soft 17')
plt.xlabel('Turn')
plt.ylabel('Balance')

# Plot the data for Player 3
plt.figure()
plt.plot(df3, color='red')
plt.title('Player 3: Hard 17')
plt.xlabel('Turn')
plt.ylabel('Balance')

# AVERAGES
# Create a new figure for the combined plot
plt.figure()

# Define the dataframes and their corresponding colors and labels
dataframes = [df1, df2, df3]
colors = ['blue', 'green', 'red']
labels = ['Optimal Chart', 'Soft 17', 'Hard 17']

# Plot the average balance at each turn for each player
for df, color, label in zip(dataframes, colors, labels):
    # Compute the average balance at each turn
    avg_balance = df.mean(axis=1)
    
    # Plot the average balance
    plt.plot(avg_balance, color=color, label=label)

# Set the title and labels for the combined plot
plt.title('All Strategies')
plt.xlabel('Turn')
plt.ylabel('Average Balance')

# Add a legend to the combined plot
plt.legend()

# Show the plots
plt.show()


# COMBINED DATA
# # Create a new figure for the combined plot
# plt.figure()

# # Plot the data for each player on the same graph
# plt.plot(df1, color='blue', label='Optimal Chart')
# plt.plot(df2, color='green', label='Soft 17')
# plt.plot(df3, color='red', label='Hard 17')

# # Set the title and labels for the combined plot
# plt.title('All Strategies')
# plt.xlabel('Turn')
# plt.ylabel('Balance')

# # Add a legend to the combined plot
# plt.legend()

# # Show the plots
# plt.show()