from enum import Enum
import curses
from curses import wrapper
import numpy as np
import dqn
import argparse

import signal
import sys

class GameMode(Enum):
    PRINT = 0
    CURSES = 1
    
enemy_position = [
    (4,2),
    (6,2),
    (7,0),
    (8,0),
    (9,0),
    (9,1),
    (10,0),
    (10,1),
    (11,0),
    (12,0),
    (16,0),
    (16,2),
    (19,1),
    (22,0),
    (22,2),
    (24,0),
    (24,2),
    (25,0),
    (26,0),
    (27,2),
    (28,1),
    (31,0),
    (40,1),
    (42,1),
    (44,2),
    (45,0),
    (45,2),
    (50,2),
    (55,1),
    (60,0),
    (64,1),
    (67,2),
    (68,1),
    (70,0),
    (70,1),
    (71,0),
    (72,2),
    (73,2),
    (74,1),
    (82,1),
    (84,0),
    (84,2),
    (85,2),
    (89,2),
    (92,0),
    (92,1),
    (94,0),
]
    
class CarGame:
    def __init__(self, mode=GameMode.PRINT, grid_size=(100, 3), num_enemies=50, num_players=1, player_pos=(0, 1), goal_pos=(99, 1), enemies=None):
        self.stdscr = None
        self.mode = mode
        self.grid_size = grid_size
        self.num_enemies = len(enemies) if enemies is not None else num_enemies
        self.num_players = num_players
        self.players = [player_pos for i in range(num_players)]
        self.goal_pos = goal_pos
        self.enemies = enemies
        if enemies is None:
            self.enemy_pos = [(np.random.randint(0, grid_size[0]), np.random.randint(0, grid_size[1])) for _ in
                          range(num_enemies)]
        else:
            self.enemy_pos = enemies.copy()
        self.game_over = False
        self.action_space = 3
        self.win = False

    def reset(self):
        self.players = [(0, 1) for i in range(self.num_players)]
        self.enemy_pos = self.enemies.copy() if self.enemies is not None else [(np.random.randint(0, self.grid_size[0]), np.random.randint(0, self.grid_size[1])) for _ in
                          range(self.num_enemies)]
        self.num_enemies = len(self.enemy_pos)
        self.game_over = False
        return self.get_state()

    def get_state(self):
        state = np.zeros(self.grid_size)
        for player in self.players:
            (x, y) = player
            if x >= self.grid_size[0] or y >= self.grid_size[1]:
                continue
            state[x][y] = 1
        for enemy in self.enemy_pos:
            x, y = enemy
            if x >= self.grid_size[0] or y >= self.grid_size[1]:
                continue
            state[x][y] = -1
        return state

    def move_enemies(self):
        to_remove = []
        for i in range(0, self.num_enemies - 1):
            self.enemy_pos[i] = (self.enemy_pos[i][0] - 1, self.enemy_pos[i][1])
            
            if self.enemy_pos[i][0] < 0 or (self.enemy_pos[i][0] < self.get_player_Yrange()[0]):
                # Add enemy position to list of enemies to remove
                to_remove.append(i)
        
        for i in to_remove:
            del self.enemy_pos[i]
            self.num_enemies -= 1
                
    def get_player_Yrange(self):
        minY = self.players[0][0]
        maxY = self.players[0][0]
        for player in self.players:
            if minY > player[0]:
                minY = player[0]
            if maxY < player[0]:
                maxY = player[0]
        return minY, maxY

    def get_reward(self, playerIdx):
        if self.game_over:
            return -10  # penalty for collision
        elif self.goal_pos == self.players[playerIdx]:
            return 10  # reward for reaching the goal
        else:
            return -0.03

    def step(self, playerIdx, action):
        if action == 0:  # move left
            self.players[playerIdx] = (self.players[playerIdx][0] + 1, max(0, self.players[playerIdx][1] - 1))
        elif action == 1:  # stay in the same position
            pass
        elif action == 2:  # move right
            self.players[playerIdx] = (self.players[playerIdx][0] + 1, min(2, self.players[playerIdx][1] + 1))
        else:
            raise ValueError("Invalid action")

        self.move_enemies()

        # Check if the game is over
        for enemy in self.enemy_pos:
            if self.players[playerIdx] == enemy:
                self.game_over = True
                break

        if self.players[playerIdx] == self.goal_pos:
            self.win = True

        return self.get_state(), self.get_reward(playerIdx), self.game_over

    def get_player_pos(self, playerIdx):
        return self.players[playerIdx]

    def is_game_over(self):
        return self.game_over

    
    def render(self, state, start_line=0, stdscr = None, epoch = 0, epoch_reward = 0, best_epoch = 0, best_reward = 0):
        if stdscr is not None:
            stdscr.clear()
            curses.delay_output(200)
        rows, cols = stdscr.getmaxyx()

        stdscr.addstr(0, 0, "Epoch: " + str(epoch))
        stdscr.addstr(1, 0, "Reward: " + str(epoch_reward))
        stdscr.addstr(2, 0, "<----High Score---->")
        stdscr.addstr(3, 0, "Best Epoch: " + str(best_epoch))
        stdscr.addstr(4, 0, "Best Reward: " + str(best_reward))
        stdscr.addstr(5, 0, "<----Entities---->")
        stdscr.addstr(6, 0, "Players: " + str(self.num_players))
        stdscr.addstr(7, 0, "Enemies: " + str(self.num_enemies))
        stdscr.addstr(8, 0, "<---------------->")
        stdscr.addstr(9, 0, "View Range: " + str(start_line) + " ~ " + str(start_line + rows))
        current_row = 0
        
        
        for i in range(start_line, state.shape[0]):
            for j in range(0, state.shape[1]):
                try:
                    current = state.item((i, j))
                    if current == 1:
                        stdscr.addstr(current_row, int(cols / 2) + j, "P", curses.color_pair(21))
                        stdscr.addstr(current_row, int(cols / 2) + 4, "<- " + str(i))
                    elif current == -1:
                        stdscr.addstr(current_row, int(cols / 2) + j, "E", curses.color_pair(10))
                    else:
                        stdscr.addstr(current_row, int(cols / 2) + j, ".")
                except curses.error:
                    pass
            current_row += 1

        stdscr.refresh()

""" def simulate():
    while True:
        for i in range(0, args.player):
            action = agent.select_action(state.flatten())
            next_state, reward, done = game.step(i, action)
        game.render(state, start_line, stdscr, epoch, epoch_reward)
        state = next_state
        if done:
            state = game.reset()
            epoch += 1
            epoch_reward = 0
        else:
            epoch_reward += 0.3
            epoch_reward += reward

    ch = stdscr.getch()
        if ch == ord('q'):
            break;

    if ch == ord('s') and (start_line + stdscr.getmaxyx()[0]) < game.grid_size[0]:
            start_line += 1
            continue

    if ch == ord('w') and start_line > 0:
            start_line -= 1
            continue """

def launch(stdscr = None):
    stdscr.nodelay(True)
    curses.start_color()
    curses.use_default_colors()
    for i in range(0, curses.COLORS):
        curses.init_pair(i + 1, i, -1)

    start_line = 0
    for i in range(0, args.instances):
        state = game.get_state()
        epoch = 0
        epoch_reward = 0
        best_reward = 0
        best_epoch = 0
        
        yPlayer = -1
        while True:
            for i in range(0, args.player):
                action = agent.select_action(state.flatten())
                next_state, reward, done = game.step(i, action)
                yPlayer = game.get_player_pos(i)[0]

            start_line = (yPlayer - 5)
            if start_line < 0:
                start_line = 0
                
            game.render(state, start_line, stdscr, epoch, epoch_reward, best_epoch, best_reward)
            state = next_state
            
            if game.win == True:
                curses.nocbreak()
                curses.echo()
                curses.endwin()
                
                print("You win!")
                
                sys.exit(0)
            
            if done:
                state = game.reset()
                
                if epoch_reward > best_reward:
                    best_epoch = epoch
                    best_reward = epoch_reward
                
                epoch += 1
                epoch_reward = 0
            else:
                epoch_reward += 0.3
                epoch_reward += reward

            ch = stdscr.getch()
            if ch == ord('q'):
                break;

            if ch == ord('s') and (start_line + stdscr.getmaxyx()[0]) < game.grid_size[0]:
                start_line += 1
                continue

            if ch == ord('w') and start_line > 0:
                start_line -= 1
                continue

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    
    parser.add_argument('-m', '--model', dest='model', type=str, help='model file path', default=None)
    parser.add_argument('-s', '--save', dest='save', type=str, help='save model into path', default=None)
    parser.add_argument('-t', '--train', dest='train', type=bool, help='train model', nargs='?', const=True, default=False)
    parser.add_argument('-e', '--episode', dest='episode', type=int, help='episode count', default=1000)
    parser.add_argument('-i', '--instances', dest='instances', type=int, help='instances count', default=1)
    parser.add_argument('-p', '--players', dest='player', type=int, help='players count', default=1)
    
    parser.add_argument('-l', '--learning_rate', dest='learning_rate', type=float, help='learning rate', default=0.001)
    
    
    args = parser.parse_args()
    game = CarGame(GameMode.CURSES, num_enemies=len(enemy_position), enemies=enemy_position, num_players=args.player)

    def signal_handler(sig, frame):
        print('You pressed Ctrl+C!')
        if game.node == GameMode.CURSES and game.stdscr is not None:
            curses.nocbreak()
            curses.echo()
            curses.endwin()
        sys.exit(0)
        
    agent = dqn.DQNAgent(input_size=game.grid_size[0] * game.grid_size[1], output_size=game.action_space, learning_rate=args.learning_rate)

    if args.model is not None:
        agent.load(args.model)
        
    if args.train is True:
        agent = dqn.train(agent, CarGame(GameMode.CURSES, num_enemies=len(enemy_position), enemies=enemy_position, num_players=args.player), args.episode)
    
    if args.save is not None:
        agent.save(args.save)

    if args.train is False and args.model is None:
        raise ValueError("Model file path is required when train is False")

    signal.signal(signal.SIGINT, signal_handler)


    wrapper(launch)