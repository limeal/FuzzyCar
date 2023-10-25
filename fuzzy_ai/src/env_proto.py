import numpy as np


class EnemyCarGame:
    def __init__(self, grid_size=(10, 3), player_pos=(0, 1), enemy_pos=(9, 1)):
        self.grid_size = grid_size
        self.player_pos = player_pos
        self.enemy_pos = enemy_pos
        self.game_over = False

    def reset(self):
        self.player_pos = (0, 1)
        self.enemy_pos = (9, 1)
        self.game_over = False
        return self.get_state()

    def get_state(self):
        state = np.zeros(self.grid_size)
        state[self.player_pos] = 1
        state[self.enemy_pos] = -1
        return state

    def move_player(self, action):
        if action == 0:  # move left
            self.player_pos = (max(0, self.player_pos[0] - 1), self.player_pos[1])
        elif action == 1:  # stay in the same position
            pass
        elif action == 2:  # move right
            self.player_pos = (min(self.grid_size[0] - 1, self.player_pos[0] + 1), self.player_pos[1])
        else:
            raise ValueError("Invalid action")

        # Move enemy car (simple AI for the enemy car)
        if self.enemy_pos[0] > 0:
            self.enemy_pos = (self.enemy_pos[0] - 1, self.enemy_pos[1])
        else:
            self.enemy_pos = (self.grid_size[0] - 1, self.enemy_pos[1])

        # Check if the game is over
        if self.player_pos == self.enemy_pos:
            self.game_over = True

        return self.get_state(), self.get_reward(), self.game_over

    def get_reward(self):
        if self.game_over:
            return -1  # penalty for collision
        else:
            return 0.1  # small reward for surviving

    def is_game_over(self):
        return self.game_over
