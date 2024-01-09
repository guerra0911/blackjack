import matplotlib.pyplot as plt

# Define the players and their corresponding files
players = ['Card Count', 'Optimal Chart', 'Soft 17', 'Hard 17']
files = ['player1Results.csv', 'player2Results.csv', 'player3Results.csv', 'Player4Results.csv']

# Initialize lists to store wins and losses
wins = []
losses = []

# Read each file and extract wins and losses
for file in files:
    with open(file, 'r') as f:
        lines = f.readlines()
        wins.append(int(lines[1].split('=')[1].strip()))
        losses.append(int(lines[2].split('=')[1].strip()))

# Calculate win and loss percentages
total_games = [wins[i] + losses[i] for i in range(len(wins))]
win_percentages = [wins[i]/total_games[i]*100 for i in range(len(wins))]
loss_percentages = [losses[i]/total_games[i]*100 for i in range(len(losses))]

# Define the bar width
bar_width = 0.35

# Define the bar positions
r1 = range(len(wins))
r2 = [x + bar_width for x in r1]

# Create the bars
bars1 = plt.bar(r1, wins, width=bar_width, color='limegreen', edgecolor='grey', label='Players that Left Table After Exceeding a $1000 Balance')
bars2 = plt.bar(r2, losses, width=bar_width, color='red', edgecolor='grey', label='Players that Left Table After not Being Able to Afford Minimum $25 Bet')

# Function to add labels on top of the bars
def add_labels(bars, percentages):
    for bar, percentage in zip(bars, percentages):
        height = bar.get_height()
        plt.text(bar.get_x() + bar.get_width() / 2, height,
                 f'{percentage:.1f}%', ha='center', va='bottom')

# Add labels to the bars
add_labels(bars1, win_percentages)
add_labels(bars2, loss_percentages)

# Add xticks on the middle of the group bars
plt.xlabel('Strategies', fontweight='bold')
plt.ylabel('# of Games', fontweight='bold')
plt.xticks([r + bar_width/2 for r in range(len(wins))], players)

# Create legend & Show graphic
plt.legend()
plt.show()
