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
    
class CarGame:
    def __init__(self, mode=GameMode.PRINT, grid_size=(100, 3), num_enemies=50, player_pos=(0, 1), goal_pos=(100, 3)):
        self.stdscr = None
        self.mode = mode
        self.grid_size = grid_size
        self.num_enemies = num_enemies
        self.player_pos = player_pos
        self.goal_pos = goal_pos
        self.enemy_pos = [(np.random.randint(0, grid_size[0]), np.random.randint(0, grid_size[1])) for _ in
                          range(num_enemies)]
        self.game_over = False
        self.action_space = 3

    def reset(self):
        self.player_pos = (0, 1)
        self.enemy_pos = [(np.random.randint(0, self.grid_size[0]), np.random.randint(0, self.grid_size[1])) for _ in
                          range(self.num_enemies)]
        self.game_over = False
        return self.get_state()

    def get_state(self):
        state = np.zeros(self.grid_size)
        state[self.player_pos] = 1
        for enemy in self.enemy_pos:
            state[enemy] = -1
        return state

    def move_enemies(self):
        for i in range(self.num_enemies):
            x, y = self.enemy_pos[i]
            y = (y + np.random.choice([-1, 1])) % self.grid_size[1]  # move randomly up or down
            self.enemy_pos[i] = (x, y)

    def step(self, action):
        if action == 0:  # move left
            self.player_pos = (max(0, self.player_pos[0] - 1), self.player_pos[1])
        elif action == 1:  # stay in the same position
            pass
        elif action == 2:  # move right
            self.player_pos = (min(self.grid_size[0] - 1, self.player_pos[0] + 1), self.player_pos[1])
        else:
            raise ValueError("Invalid action")

        self.move_enemies()

        # Check if the game is over
        for enemy in self.enemy_pos:
            if self.player_pos == enemy:
                self.game_over = True
                break

        return self.get_state(), self.get_reward(), self.game_over

    def get_reward(self):
        if self.game_over:
            return -3  # penalty for collision
        elif self.player_pos == self.goal_pos:
            return 5  # reward for reaching the goal
        elif self.player_pos in self.enemy_pos:
            return -0.3  # penalty for being close to an enemy
        else:
            return -0.01  # penalty for each step

    def is_game_over(self):
        return self.game_over

    
    def render(self, state, stdscr = None):
        if stdscr is not None:
            stdscr.clear()
            curses.delay_output(200)
        rows, cols = stdscr.getmaxyx()

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
    game = CarGame(GameMode.CURSES)
    
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
            state = game.get_state()
            while True:
                action = agent.select_action(state.flatten())
                next_state, reward, done = game.step(action)
                game.render(state, stdscr)
                state = next_state
                """ if done:
                    break; """

        wrapper(launch)