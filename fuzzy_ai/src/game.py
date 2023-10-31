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
    def __init__(self, mode=GameMode.PRINT, grid_size=(100, 3), num_enemies=50, player_pos=(0, 1), goal_pos=(99, 1), enemies=None):
        self.stdscr = None
        self.mode = mode
        self.grid_size = grid_size
        self.num_enemies = len(enemies) if enemies is not None else num_enemies
        self.player_pos = player_pos
        self.goal_pos = goal_pos
        self.enemies = enemies
        if enemies is None:
            self.enemy_pos = [(np.random.randint(0, grid_size[0]), np.random.randint(0, grid_size[1])) for _ in
                          range(num_enemies)]
        else:
            self.enemy_pos = enemies
        self.game_over = False
        self.done = False
        self.action_space = 3

    def reset(self):
        self.player_pos = (0, 1)
        self.enemy_pos = self.enemies if self.enemies is not None else [(np.random.randint(0, self.grid_size[0]), np.random.randint(0, self.grid_size[1])) for _ in
                          range(self.num_enemies)]
        self.game_over = False
        return self.get_state()

    def get_state(self):
        state = np.zeros(self.grid_size)
        state[self.player_pos] = 1
        for enemy in self.enemy_pos:
            x, y = enemy
            state[x][y] = -1
        return state

    def move_enemies(self):
        for i in range(self.num_enemies):
            x, y = self.enemy_pos[i]
            y = (y - 1) % self.grid_size[1] # move randomly up or down
            self.enemy_pos[i] = (x, y)

    def get_reward(self):
        if self.game_over:
            return -10 # penalty for collision
        elif self.player_pos == self.goal_pos:
            return 10  # reward for reaching the goal
        else:
            return -0.3  # penalty for being close to an enemy

    def step(self, action):
        if action == 0:  # move left
            self.player_pos = ( self.player_pos[0]+1,max(0, self.player_pos[1] - 1))
        elif action == 1:  # stay in the same position
            pass
        elif action == 2:  # move right
            self.player_pos = ( self.player_pos[0]+1,min(2, self.player_pos[1] + 1))
        else:
            raise ValueError("Invalid action")

        self.move_enemies()

        # Check if the game is over
        for enemy in self.enemy_pos:
            if self.player_pos == enemy:
                self.game_over = True
                break
        
        if self.player_pos == self.goal_pos:
            done = True

        return self.get_state(), self.get_reward(), self.game_over

    def is_game_over(self):
        return self.game_over

    
    def render(self, state, stdscr = None, epoch = 0, epoch_reward = 0):
        if stdscr is not None:
            stdscr.clear()
            curses.delay_output(200)
        rows, cols = stdscr.getmaxyx()

        stdscr.addstr(0, 0, "Epoch: " + str(epoch))
        stdscr.addstr(10, 0, "Reward: " + str(epoch_reward))
        for i in range(0, state.shape[0]):
            for j in range(0, state.shape[1]):
                try:
                    current = state.item((i, j))
                    if current == 1:
                        stdscr.addstr(i, int(cols / 2) + j, "P")
                    elif current == -1:
                        stdscr.addstr(i, int(cols / 2) + j, "E")
                    else:
                        stdscr.addstr(i, int(cols / 2) + j, ".")
                except curses.error:
                    pass

        stdscr.refresh()


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    game = CarGame(GameMode.CURSES, num_enemies=len(enemy_position), enemies=enemy_position)
    
    parser.add_argument('-m', '--model', dest='model', type=str, help='model file path', default=None)
    parser.add_argument('-s', '--save', dest='save', type=str, help='save model into path', default=None)
    parser.add_argument('-t', '--train', dest='train', type=bool, help='train model', nargs='?', const=True, default=False)
    parser.add_argument('-e', '--episode', dest='episode', type=int, help='episode count', default=1000)
    
    args = parser.parse_args()

    def signal_handler(sig, frame):
        print('You pressed Ctrl+C!')
        if game.node == GameMode.CURSES and game.stdscr is not None:
            curses.nocbreak()
            curses.echo()
            curses.endwin()
        sys.exit(0)
        
    agent = dqn.DQNAgent(input_size=game.grid_size[0] * game.grid_size[1], output_size=game.action_space)

    if args.model is not None:
        agent.load(args.model)
        
    if args.train is True:
        agent = dqn.train(agent, game, args.episode)
    
    if args.save is not None:
        agent.save(args.save)

    if args.train is False:
        if args.model is None:
            raise ValueError("model file path is required")
        signal.signal(signal.SIGINT, signal_handler)

        def launch(stdscr = None):
            stdscr.nodelay(True)
            state = game.get_state()
            epoch = 0
            epoch_reward = 0
            while True:
                action = agent.select_action(state.flatten())
                next_state, reward, done = game.step(action)
                game.render(state, stdscr, epoch, epoch_reward)
                state = next_state
                
                if stdscr.getch() == ord('q'):
                    break;
                
                if done:
                    state = game.reset()
                    epoch += 1
                    
                epoch_reward += reward

        wrapper(launch)