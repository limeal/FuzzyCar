import numpy as np

class EnemyCarGame:
    def __init__(self, grid_size=(100, 3), num_enemies=50, player_pos=(0, 1), goal_pos=(100, 3)):
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

